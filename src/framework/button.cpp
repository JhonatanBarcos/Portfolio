#include "button.h";
#include "button.h"

Button::Button(const Image& img, const Vector2& pos) {
    image = img;
    position = pos;

    }

Button::~Button() {
    // Destructor implementation
}

bool Button::IsMouseInside(const Vector2& mousePosition){
    int width = image.width;
    int height = image.height;

    return mousePosition.x >= position.x &&
           mousePosition.x <= position.x + width &&
           mousePosition.y >= position.y &&
           mousePosition.y <= position.y + height;
}


