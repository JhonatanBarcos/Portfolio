// button.h
#pragma once
#include "image.h"
#include "framework.h";

class Button {
private:
    Image image;
    Vector2 position;

public:
    Button();
    Button(Image img, Vector2 pos);
    ~Button();
    bool IsMouseInside(const Vector2& mousePosition);
};