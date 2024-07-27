#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "chip8.hpp"
#include <thread>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <rom_path>" << std::endl;
        return -1;
    }

    std::string romPath = argv[1];

    Chip8 ch8{};

    FILE *rom = fopen(romPath.c_str(), "rb");
    if (rom == NULL)
    {
        std::cerr << "Failed to open ROM" << std::endl;
        return -1;
    }

    // Get file size
    fseek(rom, 0, SEEK_END);
    long rom_size = ftell(rom);
    rewind(rom);

    // Allocate memory to store rom
    char *rom_buffer = (char *)malloc(sizeof(char) * rom_size);
    if (rom_buffer == NULL)
    {
        std::cerr << "Failed to allocate memory for ROM" << std::endl;
        return -1;
    }

    // Copy ROM into buffer
    size_t result = fread(rom_buffer, sizeof(char), (size_t)rom_size, rom);
    if (result != rom_size)
    {
        std::cerr << "Failed to read ROM" << std::endl;
        return -1;
    }

    std::fclose(rom);

    if ((4096 - 512) > rom_size)
    {
        for (auto i = 0; i < rom_size; ++i)
        {
            ch8.memory[i + 512] = (uint8_t)rom_buffer[i];
        }
    }

    sf::Clock clock{};
    sf::SoundBuffer buffer;

    if (!buffer.loadFromFile("bruh.mp3"))
    {
        std::cerr << "Failed to load sound" << std::endl;
        return -1;
    }

    sf::Sound sound;
    sound.setBuffer(buffer);

    while (ch8.display.window.isOpen())
    {
        if (clock.getElapsedTime().asMilliseconds() > 16)
        {
            if (ch8.delayTimer > 0)
            {
                --ch8.delayTimer;
            }

            if (ch8.soundTimer > 0)
            {
                if (ch8.soundTimer)
                {
                    sound.play();
                }
                --ch8.soundTimer;
            }
            clock.restart();
        }

        sf::Event event;
        while (ch8.display.window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                ch8.display.window.close();
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Key::Num1)
                {
                    ch8.key[0x1] = 1;
                }
                else if (event.key.code == sf::Keyboard::Key::Num2)
                {
                    ch8.key[0x2] = 1;
                }
                else if (event.key.code == sf::Keyboard::Key::Num3)
                {
                    ch8.key[0x3] = 1;
                }
                else if (event.key.code == sf::Keyboard::Key::Num4)
                {
                    ch8.key[0xC] = 1;
                }
                else if (event.key.code == sf::Keyboard::Key::Q)
                {
                    ch8.key[0x4] = 1;
                }
                else if (event.key.code == sf::Keyboard::Key::W)
                {
                    ch8.key[0x5] = 1;
                }
                else if (event.key.code == sf::Keyboard::Key::E)
                {
                    ch8.key[0x6] = 1;
                }
                else if (event.key.code == sf::Keyboard::Key::R)
                {
                    ch8.key[0xD] = 1;
                }
                else if (event.key.code == sf::Keyboard::Key::A)
                {
                    ch8.key[0x7] = 1;
                }
                else if (event.key.code == sf::Keyboard::Key::S)
                {
                    ch8.key[0x8] = 1;
                }
                else if (event.key.code == sf::Keyboard::Key::D)
                {
                    ch8.key[0x9] = 1;
                }
                else if (event.key.code == sf::Keyboard::Key::F)
                {
                    ch8.key[0xE] = 1;
                }
                else if (event.key.code == sf::Keyboard::Key::Z)
                {
                    ch8.key[0xA] = 1;
                }
                else if (event.key.code == sf::Keyboard::Key::X)
                {
                    ch8.key[0x0] = 1;
                }
                else if (event.key.code == sf::Keyboard::Key::C)
                {
                    ch8.key[0xB] = 1;
                }
                else if (event.key.code == sf::Keyboard::Key::V)
                {
                    ch8.key[0xF] = 1;
                }
            }
            else if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Key::Num1)
                {
                    ch8.key[0x1] = 0;
                }
                else if (event.key.code == sf::Keyboard::Key::Num2)
                {
                    ch8.key[0x2] = 0;
                }
                else if (event.key.code == sf::Keyboard::Key::Num3)
                {
                    ch8.key[0x3] = 0;
                }
                else if (event.key.code == sf::Keyboard::Key::Num4)
                {
                    ch8.key[0xC] = 0;
                }
                else if (event.key.code == sf::Keyboard::Key::Q)
                {
                    ch8.key[0x4] = 0;
                }
                else if (event.key.code == sf::Keyboard::Key::W)
                {
                    ch8.key[0x5] = 0;
                }
                else if (event.key.code == sf::Keyboard::Key::E)
                {
                    ch8.key[0x6] = 0;
                }
                else if (event.key.code == sf::Keyboard::Key::R)
                {
                    ch8.key[0xD] = 0;
                }
                else if (event.key.code == sf::Keyboard::Key::A)
                {
                    ch8.key[0x7] = 0;
                }
                else if (event.key.code == sf::Keyboard::Key::S)
                {
                    ch8.key[0x8] = 0;
                }
                else if (event.key.code == sf::Keyboard::Key::D)
                {
                    ch8.key[0x9] = 0;
                }
                else if (event.key.code == sf::Keyboard::Key::F)
                {
                    ch8.key[0xE] = 0;
                }
                else if (event.key.code == sf::Keyboard::Key::Z)
                {
                    ch8.key[0xA] = 0;
                }
                else if (event.key.code == sf::Keyboard::Key::X)
                {
                    ch8.key[0x0] = 0;
                }
                else if (event.key.code == sf::Keyboard::Key::C)
                {
                    ch8.key[0xB] = 0;
                }
                else if (event.key.code == sf::Keyboard::Key::V)
                {
                    ch8.key[0xF] = 0;
                }
            }
        }

        uint16_t opcode = (ch8.memory[ch8.pc] << 8) + (ch8.memory[ch8.pc + 1]);

        ch8.decode(opcode);

        ch8.display.update();
        std::this_thread::sleep_for(std::chrono::microseconds(400));
    }

    return 0;
}
