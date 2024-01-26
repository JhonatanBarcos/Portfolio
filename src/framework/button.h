// button.h
#pragma once
#include "image.h"
#include "framework.h";

class Button {
private:
    Image image;
    Vector2 position;

public:
    Button(const Image& image, const Vector2& position);
    bool IsMouseInside(const Vector2& mousePosition);
};