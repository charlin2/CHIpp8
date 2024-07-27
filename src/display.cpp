#include "display.hpp"
#include <iostream>

Display::Display()
{
    window.create(sf::VideoMode(width * scale, height * scale), "CHIP-8", sf::Style::Close);
}

void Display::clear()
{
    memset(screen, 0, sizeof(screen));
    window.clear(off);
}

void Display::update()
{
    window.clear(off);
    for (auto i = 0; i < height; ++i)
    {
        for (auto j = 0; j < width; ++j)
        {
            if (screen[i][j])
            {
                drawPixel(j, i);
            }
        }
    }
    window.display();
}

void Display::flip(int x, int y)
{
    screen[y][x] = !screen[y][x];
}

void Display::drawPixel(int x, int y)
{
    sf::RectangleShape rect{};
    rect.setSize(sf::Vector2f(scale - 1, scale - 1));
    rect.setPosition(x * scale, y * scale);
    rect.setFillColor(on);
    window.draw(rect);
}
