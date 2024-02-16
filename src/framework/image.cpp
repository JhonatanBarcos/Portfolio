#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "GL/glew.h"
#include "../extra/picopng.h"
#include "image.h"
#include "utils.h"
#include "camera.h"
#include "mesh.h"


Image::Image() {
	width = 0; height = 0;
	pixels = NULL;
}

Image::Image(unsigned int width, unsigned int height)
{
	this->width = width;
	this->height = height;
	pixels = new Color[width*height];
	memset(pixels, 0, width * height * sizeof(Color));
}

// Copy constructor
Image::Image(const Image& c)
{
	pixels = NULL;
	width = c.width;
	height = c.height;
	bytes_per_pixel = c.bytes_per_pixel;
	if(c.pixels)
	{
		pixels = new Color[width*height];
		memcpy(pixels, c.pixels, width*height*bytes_per_pixel);
	}
}

// Assign operator
Image& Image::operator = (const Image& c)
{
	if(pixels) delete pixels;
	pixels = NULL;

	width = c.width;
	height = c.height;
	bytes_per_pixel = c.bytes_per_pixel;

	if(c.pixels)
	{
		pixels = new Color[width*height*bytes_per_pixel];
		memcpy(pixels, c.pixels, width*height*bytes_per_pixel);
	}
	return *this;
}

Image::~Image()
{
	if(pixels) 
		delete pixels;
}

void Image::Render()
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glDrawPixels(width, height, bytes_per_pixel == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, pixels);
}

// Change image size (the old one will remain in the top-left corner)
void Image::Resize(unsigned int width, unsigned int height)
{
	Color* new_pixels = new Color[width*height];
	unsigned int min_width = this->width > width ? width : this->width;
	unsigned int min_height = this->height > height ? height : this->height;

	for(unsigned int x = 0; x < min_width; ++x)
		for(unsigned int y = 0; y < min_height; ++y)
			new_pixels[ y * width + x ] = GetPixel(x,y);

	delete pixels;
	this->width = width;
	this->height = height;
	pixels = new_pixels;
}

// Change image size and scale the content
void Image::Scale(unsigned int width, unsigned int height)
{
	Color* new_pixels = new Color[width*height];

	for(unsigned int x = 0; x < width; ++x)
		for(unsigned int y = 0; y < height; ++y)
			new_pixels[ y * width + x ] = GetPixel((unsigned int)(this->width * (x / (float)width)), (unsigned int)(this->height * (y / (float)height)) );

	delete pixels;
	this->width = width;
	this->height = height;
	pixels = new_pixels;
}

Image Image::GetArea(unsigned int start_x, unsigned int start_y, unsigned int width, unsigned int height)
{
	Image result(width, height);
	for(unsigned int x = 0; x < width; ++x)
		for(unsigned int y = 0; y < height; ++x)
		{
			if( (x + start_x) < this->width && (y + start_y) < this->height) 
				result.SetPixel( x, y, GetPixel(x + start_x,y + start_y) );
		}
	return result;
}

void Image::FlipY()
{
	int row_size = bytes_per_pixel * width;
	Uint8* temp_row = new Uint8[row_size];
#pragma omp simd
	for (int y = 0; y < height * 0.5; y += 1)
	{
		Uint8* pos = (Uint8*)pixels + y * row_size;
		memcpy(temp_row, pos, row_size);
		Uint8* pos2 = (Uint8*)pixels + (height - y - 1) * row_size;
		memcpy(pos, pos2, row_size);
		memcpy(pos2, temp_row, row_size);
	}
	delete[] temp_row;
}

bool Image::LoadPNG(const char* filename, bool flip_y)
{
	std::string sfullPath = absResPath(filename);
	std::ifstream file(sfullPath, std::ios::in | std::ios::binary | std::ios::ate);

	// Get filesize
	std::streamsize size = 0;
	if (file.seekg(0, std::ios::end).good()) size = file.tellg();
	if (file.seekg(0, std::ios::beg).good()) size -= file.tellg();

	if (!size)
		return false;

	std::vector<unsigned char> buffer;

	// Read contents of the file into the vector
	if (size > 0)
	{
		buffer.resize((size_t)size);
		file.read((char*)(&buffer[0]), size);
	}
	else
		buffer.clear();

	std::vector<unsigned char> out_image;

	if (decodePNG(out_image, width, height, buffer.empty() ? 0 : &buffer[0], (unsigned long)buffer.size(), true) != 0)
		return false;

	size_t bufferSize = out_image.size();
	unsigned int originalBytesPerPixel = (unsigned int)bufferSize / (width * height);
	
	// Force 3 channels
	bytes_per_pixel = 3;

	if (originalBytesPerPixel == 3) {
		pixels = new Color[bufferSize];
		memcpy(pixels, &out_image[0], bufferSize);
	}
	else if (originalBytesPerPixel == 4) {

		unsigned int newBufferSize = width * height * bytes_per_pixel;
		pixels = new Color[newBufferSize];

		unsigned int k = 0;
		for (unsigned int i = 0; i < bufferSize; i += originalBytesPerPixel) {
			pixels[k] = Color(out_image[i], out_image[i + 1], out_image[i + 2]);
			k++;
		}
	}

	// Flip pixels in Y
	if (flip_y)
		FlipY();

	return true;
}

// Loads an image from a TGA file
bool Image::LoadTGA(const char* filename, bool flip_y)
{
	unsigned char TGAheader[12] = {0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	unsigned char TGAcompare[12];
	unsigned char header[6];
	unsigned int imageSize;
	unsigned int bytesPerPixel;

    std::string sfullPath = absResPath( filename );

	FILE * file = fopen( sfullPath.c_str(), "rb");
   	if ( file == NULL || fread(TGAcompare, 1, sizeof(TGAcompare), file) != sizeof(TGAcompare) ||
		memcmp(TGAheader, TGAcompare, sizeof(TGAheader)) != 0 ||
		fread(header, 1, sizeof(header), file) != sizeof(header))
	{
		std::cerr << "File not found: " << sfullPath.c_str() << std::endl;
		if (file == NULL)
			return NULL;
		else
		{
			fclose(file);
			return NULL;
		}
	}

	TGAInfo* tgainfo = new TGAInfo;
    
	tgainfo->width = header[1] * 256 + header[0];
	tgainfo->height = header[3] * 256 + header[2];
    
	if (tgainfo->width <= 0 || tgainfo->height <= 0 || (header[4] != 24 && header[4] != 32))
	{
		fclose(file);
		delete tgainfo;
		return NULL;
	}
    
	tgainfo->bpp = header[4];
	bytesPerPixel = tgainfo->bpp / 8;
	imageSize = tgainfo->width * tgainfo->height * bytesPerPixel;
    
	tgainfo->data = new unsigned char[imageSize];
    
	if (tgainfo->data == NULL || fread(tgainfo->data, 1, imageSize, file) != imageSize)
	{
		if (tgainfo->data != NULL)
			delete tgainfo->data;
            
		fclose(file);
		delete tgainfo;
		return false;
	}

	fclose(file);

	// Save info in image
	if(pixels)
		delete pixels;

	width = tgainfo->width;
	height = tgainfo->height;
	pixels = new Color[width*height];

	// Convert to float all pixels
	for (unsigned int y = 0; y < height; ++y) {
		for (unsigned int x = 0; x < width; ++x) {
			unsigned int pos = y * width * bytesPerPixel + x * bytesPerPixel;
			// Make sure we don't access out of memory
			if( (pos < imageSize) && (pos + 1 < imageSize) && (pos + 2 < imageSize))
				SetPixel(x, height - y - 1, Color(tgainfo->data[pos + 2], tgainfo->data[pos + 1], tgainfo->data[pos]));
		}
	}

	// Flip pixels in Y
	if (flip_y)
		FlipY();

	delete tgainfo->data;
	delete tgainfo;

	return true;
}

// Saves the image to a TGA file
bool Image::SaveTGA(const char* filename)
{
	unsigned char TGAheader[12] = {0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	std::string fullPath = absResPath(filename);
	FILE *file = fopen(fullPath.c_str(), "wb");
	if ( file == NULL )
	{
		perror("Failed to open file: ");
		return false;
	}

	unsigned short header_short[3];
	header_short[0] = width;
	header_short[1] = height;
	unsigned char* header = (unsigned char*)header_short;
	header[4] = 24;
	header[5] = 0;

	fwrite(TGAheader, 1, sizeof(TGAheader), file);
	fwrite(header, 1, 6, file);

	// Convert pixels to unsigned char
	unsigned char* bytes = new unsigned char[width*height*3];
	for(unsigned int y = 0; y < height; ++y)
		for(unsigned int x = 0; x < width; ++x)
		{
			Color c = pixels[y*width+x];
			unsigned int pos = (y*width+x)*3;
			bytes[pos+2] = c.r;
			bytes[pos+1] = c.g;
			bytes[pos] = c.b;
		}

	fwrite(bytes, 1, width*height*3, file);
	fclose(file);

	return true;
}

void Image::DrawImage(const Image& image, int x, int y, bool top){
    if (top){
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                SetPixel(x + i, y + j, image.GetPixel(i, j));
            }
        }
    } else {
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                SetPixelSafe(x + i, height - 1 - (y + j), image.GetPixel(i, j));
            }
        }
    }
}

void Image::DrawRectOld(int x, int y, int w, int h, const Color& c)
{
	for (int i = 0; i < w; ++i) {
		SetPixel(x + i, y, c);
		SetPixel(x + i, y + h - 1, c);
	}

	for (int j = 0; j < h; ++j) {
		SetPixel(x, y + j, c);
		SetPixel(x + w - 1, y + j, c);
	}
}

void Image::DrawRect(int x, int y, int w, int h, const Color& borderColor, int borderWidth, bool isFilled, const Color& fillColor){
	if (isFilled){
		// Fill the rectangle
		for( int i = x; i < (x + w); ++i)
		{
			for( int j = y; j < (y + h); ++j)
			{
				SetPixel(i, j, fillColor);
			}
		}

		// Draw the rectangle border
		for (int i = 0; i < w; ++i) {
			//border width loop
			for (int k = 0; k < borderWidth; ++k){
				SetPixel(x + i, y + k, borderColor);
				SetPixel(x + i, y + h - 1 - k, borderColor);
			}
		}

		for (int j = 0; j < h; ++j) {
			//border width loop
			for (int k = 0; k < borderWidth; ++k){
				SetPixel(x + k, y + j, borderColor);
				SetPixel(x + w - 1 - k, y + j, borderColor);
			}
		}
	
	} else {
		// Draw only the rectangle border
		for (int i = 0; i < w; ++i) {
			//border width loop
			for (int k = 0; k < borderWidth; ++k){
				SetPixel(x + i, y + k, borderColor);
				SetPixel(x + i, y + h - 1 - k, borderColor);
			}
		}

		for (int j = 0; j < h; ++j) {
			//border width loop
			for (int k = 0; k < borderWidth; ++k){
				SetPixel(x + k, y + j, borderColor);
				SetPixel(x + w - 1 - k, y + j, borderColor);
			}
		}
	}
}

void Image::DrawLineDDA(int x0, int y0, int x1, int y1, const Color& c){
	float dx = x1-x0;
	float dy = y1-y0;
	float d = std::max(abs(dx), abs(dy));

	if (dx==0 && dy==0){
		SetPixelSafe(x0,y0,c);
	} else {
		float vx = dx/d;
		float vy = dy/d;

		float x = x0;
		float y = y0;

		SetPixelSafe(floor(x),floor(y),c);
		for (int i = 0; i < d; i++){
			x += vx;
			y += vy;
			SetPixelSafe(floor(x),floor(y),c);
		}
	}
}

void Image::DrawCircle(int x_c, int y_c, int r, const Color& borderColor, int borderWidth, bool isFilled, const Color& fillColor){
	int x = 0;
	int y = r;
	int p = 1 - r;

	SetPixel(x_c+x, y_c+y, borderColor);
	SetPixel(x_c+y, y_c+x, borderColor);
	SetPixel(x_c-x, y_c+y, borderColor);
	SetPixel(x_c+x, y_c-y, borderColor);
	SetPixel(x_c-x, y_c-y, borderColor);
	SetPixel(x_c+y, y_c-x, borderColor);
	SetPixel(x_c-y, y_c+x, borderColor);
	SetPixel(x_c-y, y_c-x, borderColor);

	if (isFilled){
		// Fill the circle using x^2+y^2 <= r^2
		for( int i = x_c-r; i < (x_c + r); ++i)
		{
			for( int j = y_c-r; j < (y_c + r); ++j)
			{
				if (pow(i-x_c,2) + pow(j-y_c,2) <= pow(r,2)){
					SetPixel(i, j, fillColor);
				}
			}
		}

		//Border circle using Mid Point algorithm
		while (x<y){
			if (p < 0){
				x = x+1;
				y = y;
				p = p + 2*x + 1;
					SetPixel(x_c+x, y_c+y, borderColor);
					SetPixel(x_c+y, y_c+x, borderColor);
					SetPixel(x_c-x, y_c+y, borderColor);
					SetPixel(x_c+x, y_c-y, borderColor);
					SetPixel(x_c-x, y_c-y, borderColor);
					SetPixel(x_c+y, y_c-x, borderColor);
					SetPixel(x_c-y, y_c+x, borderColor);
					SetPixel(x_c-y, y_c-x, borderColor);
							

			} else if ( p >= 0){
				x = x+1;
				y = y-1;
				p = p + 2*(x-y) + 1;
					SetPixel(x_c+x, y_c+y, borderColor);
					SetPixel(x_c+y, y_c+x, borderColor);
					SetPixel(x_c-x, y_c+y, borderColor);
					SetPixel(x_c+x, y_c-y, borderColor);
					SetPixel(x_c-x, y_c-y, borderColor);
					SetPixel(x_c+y, y_c-x, borderColor);
					SetPixel(x_c-y, y_c+x, borderColor);
					SetPixel(x_c-y, y_c-x, borderColor);
			}
		}
	
	} else if (!isFilled){
		//Border circle using Mid Point algorithm
		while (x<y){
			if (p < 0){
				x = x+1;
				y = y;
				p = p + 2*x + 1;
					SetPixel(x_c+x, y_c+y, borderColor);
					SetPixel(x_c+y, y_c+x, borderColor);
					SetPixel(x_c-x, y_c+y, borderColor);
					SetPixel(x_c+x, y_c-y, borderColor);
					SetPixel(x_c-x, y_c-y, borderColor);
					SetPixel(x_c+y, y_c-x, borderColor);
					SetPixel(x_c-y, y_c+x, borderColor);
					SetPixel(x_c-y, y_c-x, borderColor);

			} else if (p >= 0){
				x = x+1;
				y = y-1;
				p = p + 2*(x-y) + 1;
					SetPixel(x_c+x, y_c+y, borderColor);
					SetPixel(x_c+y, y_c+x, borderColor);
					SetPixel(x_c-x, y_c+y, borderColor);
					SetPixel(x_c+x, y_c-y, borderColor);
					SetPixel(x_c-x, y_c-y, borderColor);
					SetPixel(x_c+y, y_c-x, borderColor);
					SetPixel(x_c-y, y_c+x, borderColor);
					SetPixel(x_c-y, y_c-x, borderColor);
			}
		}
	}
}


void Image::ScanLineDDA(int x0, int y0, int x1, int y1, std::vector<Cell>& table) {

	float dx = x1 - x0;
	#include <algorithm>

	float dy = y1 - y0;

	float d = std::max(abs(dx), abs(dy));
	Vector2 v = Vector2(dx / d, dy / d);
	float x = x0, y = y0;

	for (float i = 0; i <= d; i++) {
		//Update the table only if the calculated y coordinates are within the range of the image
		if (y >= 0 && y < table.size()) {
			table[floor(y)].minX = std::min(static_cast<int>(floor(x)), table[floor(y)].minX);
			table[floor(y)].maxX = std::max(static_cast<int>(floor(x)), table[floor(y)].maxX);
		}
		x += v.x;
		y += v.y;
	}
}

void Image::DrawTriangle(const Vector2& p0, const Vector2& p1, const Vector2& p2, const Color& borderColor, bool isFilled, const Color& fillColor) {

    std::vector<Cell> table(height);

    ScanLineDDA(p0.x, p0.y, p1.x, p1.y, table);
    ScanLineDDA(p1.x, p1.y, p2.x, p2.y, table);
    ScanLineDDA(p2.x, p2.y, p0.x, p0.y, table);

	if (isFilled) {
		//Create table
		std::vector<Cell> table(height);
		//Update table with the min and max x values of the triangle
		ScanLineDDA(p0.x, p0.y, p1.x, p1.y, table);
		ScanLineDDA(p1.x, p1.y, p2.x, p2.y, table);
		ScanLineDDA(p0.x, p0.y, p2.x, p2.y, table);
		//Paint the triangle
		for (int i = 0; i < table.size(); i++) {
			//Paint each row of the triangle from minx to maxx (included)
			for (int j = table[i].minX; j <= table[i].maxX; j++) {
				SetPixelSafe(j, i, fillColor);
			}
		}
	}

	DrawLineDDA(p0.x, p0.y, p1.x, p1.y, borderColor);
	DrawLineDDA(p0.x, p0.y, p2.x, p2.y, borderColor);
	DrawLineDDA(p1.x, p1.y, p2.x, p2.y, borderColor);
}

void Image::DrawTriangleInterpolated(const Vector3& p0, const Vector3& p1, const Vector3& p2, const Color& c0, const Color& c1, const Color& c2) {
	// Calculamos los limites del triángulo encerrado en una caja
	int minX = std::min(p0.x, std::min(p1.x, p2.x));
	int minY = std::min(p0.y, std::min(p1.y, p2.y));
	int maxX = std::max(p0.x, std::max(p1.x, p2.x));
	int maxY = std::max(p0.y, std::max(p1.y, p2.y));

	// Iteramos sobre cada uno de los píxeles
	for (int y = minY; y <= maxY; y++) {
		for (int x = minX; x <= maxX; x++) {
			// Calculamos las coordenadas baricéntricas de cada pixel
			Matrix44 m = CalculateM(Vector2(x, y), p0, p1, p2);
			Vector3 pixelCoords = (x,y,1); 
			Vector3 barycentricCoords = m * pixelCoords;

			barycentricCoords.Clamp(0,1);

			float barycentricCoordsSum = barycentricCoords.x + barycentricCoords.y + barycentricCoords.z;
			barycentricCoords = barycentricCoords / barycentricCoordsSum;

			// Hallamos el color interpolado
			Color interpolatedColor = InterpolateColor(c0, c1, c2, barycentricCoords);

			// Pintamos el pixel
			SetPixelSafe(x, y, interpolatedColor);
			
		}
	}
}


Matrix44 Image::CalculateM(const Vector2& point, const Vector3& p0, const Vector3& p1, const Vector3& p2) {
	std::vector<Cell> table(height);
	Matrix44 m;
	
	ScanLineDDA(p0.x, p0.y, p1.x, p1.y, table);
	ScanLineDDA(p1.x, p1.y, p2.x, p2.y, table);
	ScanLineDDA(p0.x, p0.y, p2.x, p2.y, table);

	m.M[0][0] = p0.x;
	m.M[1][0] = p1.x;
	m.M[2][0] = p2.x;
	m.M[0][1] = p0.y;
	m.M[1][1] = p1.y;
	m.M[2][1] = p2.y;
	m.M[0][2] = 1;
	m.M[1][2] = 1;
	m.M[2][2] = 1;
	m.Inverse();

	return m;
}

Color Image::InterpolateColor(const Color& c0, const Color& c1, const Color& c2, const Vector3& barycentric) {
	// Interpolamos los colores utilizando las coords baricentricas
	float r = c0.r * barycentric.x + c1.r * barycentric.y + c2.r * barycentric.z;
	float g = c0.g * barycentric.x + c1.g * barycentric.y + c2.g * barycentric.z;
	float b = c0.b * barycentric.x + c1.b * barycentric.y + c2.b * barycentric.z;

	return Color(r, g, b);
}
#ifndef IGNORE_LAMBDAS

// You can apply and algorithm for two images and store the result in the first one
// ForEachPixel( img, img2, [](Color a, Color b) { return a + b; } );
template <typename F>
void ForEachPixel(Image& img, const Image& img2, F f) {
	for(unsigned int pos = 0; pos < img.width * img.height; ++pos)
		img.pixels[pos] = f( img.pixels[pos], img2.pixels[pos] );
}

#endif

FloatImage::FloatImage(unsigned int width, unsigned int height)
{
	this->width = width;
	this->height = height;
	pixels = new float[width * height];
	memset(pixels, 0, width * height * sizeof(float));
}

// Copy constructor
FloatImage::FloatImage(const FloatImage& c) {
	pixels = NULL;

	width = c.width;
	height = c.height;
	if (c.pixels)
	{
		pixels = new float[width * height];
		memcpy(pixels, c.pixels, width * height * sizeof(float));
	}
}

// Assign operator
FloatImage& FloatImage::operator = (const FloatImage& c)
{
	if (pixels) delete pixels;
	pixels = NULL;

	width = c.width;
	height = c.height;
	if (c.pixels)
	{
		pixels = new float[width * height * sizeof(float)];
		memcpy(pixels, c.pixels, width * height * sizeof(float));
	}
	return *this;
}

FloatImage::~FloatImage()
{
	if (pixels)
		delete pixels;
}

// Change image size (the old one will remain in the top-left corner)
void FloatImage::Resize(unsigned int width, unsigned int height)
{
	float* new_pixels = new float[width * height];
	unsigned int min_width = this->width > width ? width : this->width;
	unsigned int min_height = this->height > height ? height : this->height;

	for (unsigned int x = 0; x < min_width; ++x)
		for (unsigned int y = 0; y < min_height; ++y)
			new_pixels[y * width + x] = GetPixel(x, y);

	delete pixels;
	this->width = width;
	this->height = height;
	pixels = new_pixels;
}


void ParticleSystem::Init()
{
	
	for (int i = 0; i < MAX_PARTICLES; ++i)
	{
		particles[i].position.x = rand() % 1200;
		particles[i].position.y = rand() % 650;
		particles[i].prevPosition = particles[i].position; 
		
		particles[i].velocity.x = rand() % 10;
		particles[i].velocity.y = rand() % 10;
		
		particles[i].acceleration = rand() % 10;

		int r = rand() % 255;
		int g = rand() % 255;
		int b = rand() % 255;

		particles[i].color = Color(r,g,b);
		particles[i].ttl = rand() % 50;
		particles[i].inactive = false;
	}



}

void ParticleSystem::Render(Image* framebuffer)
{
	
	for (int i = 0; i < MAX_PARTICLES; ++i)
	{
		framebuffer->SetPixelSafe(particles[i].prevPosition.x, particles[i].prevPosition.y, Color::BLACK);
		if (!particles[i].inactive){
			framebuffer->SetPixelSafe(particles[i].position.x, particles[i].position.y, particles[i].color);
		} 
	}

}


void ParticleSystem::Update(float dt)
{
	// Update particles
	for (int i = 0; i < MAX_PARTICLES; ++i)
	{
		particles[i].prevPosition = particles[i].position;
		particles[i].ttl -= dt;

		if (particles[i].ttl <= 0){
			particles[i].inactive = true;
		} else{
			particles[i].position.x += particles[i].velocity.x * dt;
			particles[i].position.y += particles[i].velocity.y * dt;
			particles[i].velocity.x += particles[i].acceleration * dt;
			particles[i].velocity.y += particles[i].acceleration * dt;
		}
	}
}