#include <SFML/Graphics.hpp>

class Display
{
public:
    Display();

    void clear();

    void update();

    sf::Color on{sf::Color(230, 230, 230, 230)};
    sf::Color off{sf::Color(20, 20, 20, 255)};

    static const int height{32};
    static const int width{64};
    static const int scale{20};
    
    int screen[height][width]{};

    sf::RenderWindow window{};

    void flip(int x, int y);

    void drawPixel(int x, int y);
};