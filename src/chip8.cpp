#include "chip8.hpp"

Chip8::Chip8()
{
    std::vector<uint8_t> font = {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };

    // Load font into memory
    for (auto i = 0; i < font.size(); ++i)
    {
        memory[i] = font[i];
    }
}

void Chip8::decode(uint16_t opcode)
{
    uint8_t b3 = (opcode & 0xF000) >> 12;
    uint8_t b0 = opcode & 0x000F;

    switch (b3)
    {
    case 0:
    {
        if (b0 == 0)
        {
            op_00E0();
        }
        else if (b0 == 0xE)
        {
            op_00EE(opcode);
        }
        break;
    }
    case 1:
    {
        op_1NNN(opcode);
        break;
    }
    case 2:
    {
        op_2NNN(opcode);
        break;
    }
    case 3:
    {
        op_3XNN(opcode);
        break;
    }
    case 4:
    {
        op_4XNN(opcode);
        break;
    }
    case 5:
    {
        op_5XY0(opcode);
        break;
    }
    case 6:
    {
        op_6XNN(opcode);
        break;
    }
    case 7:
    {
        op_7XNN(opcode);
        break;
    }
    case 8:
    {
        switch (b0)
        {
        case 0:
        {
            op_8XY0(opcode);
            break;
        }
        case 1:
        {
            op_8XY1(opcode);
            break;
        }
        case 2:
        {
            op_8XY2(opcode);
            break;
        }
        case 3:
        {
            op_8XY3(opcode);
            break;
        }
        case 4:
        {
            op_8XY4(opcode);
            break;
        }
        case 5:
        {
            op_8XY5(opcode);
            break;
        }
        case 6:
        {
            op_8XY6(opcode);
            break;
        }
        case 7:
        {
            op_8XY7(opcode);
            break;
        }
        case 0xE:
        {
            op_8XYE(opcode);
            break;
        }
        default:
            break;
        }
        break;
    }
    case 9:
    {
        op_9XY0(opcode);
        break;
    }
    case 0xA:
    {
        op_ANNN(opcode);
        break;
    }
    case 0xB:
    {
        op_BNNN(opcode);
        break;
    }
    case 0xC:
    {
        op_CXNN(opcode);
        break;
    }
    case 0xD:
    {
        op_DXYN(opcode);
        break;
    }
    case 0xE:
    {
        if ((opcode & 0x00FF) == 0x9E)
        {
            op_EX9E(opcode);
        }
        else if ((opcode & 0x00FF) == 0xA1)
        {
            op_EXA1(opcode);
        }
        break;
    }
    case 0xF:
    {
        switch (opcode & 0x00FF)
        {
        case 0x07:
        {
            op_FX07(opcode);
            break;
        }
        case 0x0A:
        {
            op_FX0A(opcode);
            break;
        }
        case 0x15:
        {
            op_FX15(opcode);
            break;
        }
        case 0x18:
        {
            op_FX18(opcode);
            break;
        }
        case 0x1E:
        {
            op_FX1E(opcode);
            break;
        }
        case 0x29:
        {
            op_FX29(opcode);
            break;
        }
        case 0x33:
        {
            op_FX33(opcode);
            break;
        }
        case 0x55:
        {
            op_FX55(opcode);
            break;
        }
        case 0x65:
        {
            op_FX65(opcode);
            break;
        }
        default:
            break;
        }
    }
    default:
        break;
    }

    pc += 2;
}

void Chip8::op_00E0()
{
    display.clear();
}

void Chip8::op_1NNN(uint16_t opcode)
{
    uint16_t adr = opcode & 0x0FFF;
    pc = adr - 2;
}

void Chip8::op_2NNN(uint16_t opcode)
{
    uint16_t adr = opcode & 0x0FFF;
    stack.push(pc);
    pc = adr - 2;
}

void Chip8::op_00EE(uint16_t opcode)
{
    pc = stack.top();
    stack.pop();
}

void Chip8::op_3XNN(uint16_t opcode)
{
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t nn = opcode & 0x00FF;

    if (V[x] == nn)
    {
        pc += 2;
    }
}

void Chip8::op_4XNN(uint16_t opcode)
{
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t nn = opcode & 0x00FF;

    if (V[x] != nn)
    {
        pc += 2;
    }
}

void Chip8::op_5XY0(uint16_t opcode)
{
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t y = (opcode & 0x00F0) >> 4;

    if (V[x] == V[y])
    {
        pc += 2;
    }
}

void Chip8::op_6XNN(uint16_t opcode)
{
    uint8_t reg = (opcode & 0x0F00) >> 8;
    uint8_t val = opcode & 0x00FF;

    V[reg] = val;
}

void Chip8::op_7XNN(uint16_t opcode)
{
    uint8_t reg = (opcode & 0x0F00) >> 8;
    uint8_t val = opcode & 0x00FF;

    V[reg] += val;
}

void Chip8::op_8XY0(uint16_t opcode)
{
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t y = (opcode & 0x00F0) >> 4;

    V[x] = V[y];
}

void Chip8::op_8XY1(uint16_t opcode)
{
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t y = (opcode & 0x00F0) >> 4;

    V[x] |= V[y];
}

void Chip8::op_8XY2(uint16_t opcode)
{
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t y = (opcode & 0x00F0) >> 4;

    V[x] &= V[y];
}

void Chip8::op_8XY3(uint16_t opcode)
{
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t y = (opcode & 0x00F0) >> 4;

    V[x] ^= V[y];
}

void Chip8::op_8XY4(uint16_t opcode)
{
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t y = (opcode & 0x00F0) >> 4;

    if ((int)x + (int)y > 0xFF)
    {
        V[0xF] = 1;
    }

    V[x] += V[y];
}

void Chip8::op_8XY5(uint16_t opcode)
{
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t y = (opcode & 0x00F0) >> 4;

    V[0xF] = 1;

    if (V[x] < V[y])
    {
        V[0xF] = 0;
    }

    V[x] -= V[y];
}

void Chip8::op_8XY6(uint16_t opcode)
{
    uint8_t x = (opcode & 0x0F00) >> 8;

    V[0xF] = V[x] & 0x1;
    V[x] >>= 1;
}

void Chip8::op_8XY7(uint16_t opcode)
{
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t y = (opcode & 0x00F0) >> 4;

    V[0xF] = 1;

    if (V[x] > V[y])
    {
        V[0xF] = 0;
    }

    V[x] = V[y] - V[x];
}

void Chip8::op_8XYE(uint16_t opcode)
{
    uint8_t x = (opcode & 0x0F00) >> 8;

    uint8_t msb = V[x] >> 7;
    V[0xF] = msb;
    V[x] <<= 1;
}

void Chip8::op_9XY0(uint16_t opcode)
{
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t y = (opcode & 0x00F0) >> 4;

    if (V[x] != V[y])
    {
        pc += 2;
    }
}

void Chip8::op_ANNN(uint16_t opcode)
{
    uint16_t adr = opcode & 0x0FFF;

    I = adr;
}

void Chip8::op_BNNN(uint16_t opcode)
{
    uint16_t adr = opcode & 0x0FFF;

    pc = adr + V[0] - 2;
}

void Chip8::op_CXNN(uint16_t opcode)
{
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t nn = opcode & 0x00FF;

    V[x] = (std::rand() % 256) & nn;
}

void Chip8::op_DXYN(uint16_t opcode)
{
    uint8_t n = opcode & 0x000F;
    uint8_t b1 = (opcode & 0x00F0) >> 4;
    uint8_t b2 = (opcode & 0x0F00) >> 8;
    uint8_t x = V[b2] % 64;
    uint8_t y = V[b1] % 32;

    V[0xF] = 0;

    for (auto i = 0; i < n; ++i)
    {
        uint8_t line = memory[I + i];
        if (y + i < display.height)
        {
            for (auto j = 0; j < 8; ++j)
            {
                if (x + j < display.width)
                {
                    uint8_t pixel = ((0x1 << (7 - j)) & line) >> (7 - j);
                    if (pixel)
                    {
                        if (display.screen[y + i][x + j] && pixel)
                        {
                            V[0xF] = 1;
                        }

                        display.flip(x + j, y + i);
                    }
                }
            }
        }
    }
}

void Chip8::op_EX9E(uint16_t opcode)
{
    uint8_t x = (opcode & 0x0F00) >> 8;
    if (key[V[x]])
    {
        pc += 2;
    }
}

void Chip8::op_EXA1(uint16_t opcode)
{
    uint8_t x = (opcode & 0x0F00) >> 8;
    if (!key[V[x]])
    {
        pc += 2;
    }
}

void Chip8::op_FX07(uint16_t opcode)
{
    uint8_t x = (opcode & 0x0F00) >> 8;
    V[x] = delayTimer;
}

void Chip8::op_FX0A(uint16_t opcode)
{
    uint8_t x = (opcode & 0x0F00) >> 8;
    bool keyPress = false;

    for (auto i = 0; i < 16; ++i)
    {
        if (key[i])
        {
            V[x] = i;
            keyPress = true;
        }
    }

    if (!keyPress)
    {
        pc -= 2;
    }
}

void Chip8::op_FX15(uint16_t opcode)
{
    uint8_t x = (opcode & 0x0F00) >> 8;
    delayTimer = V[x];
}

void Chip8::op_FX18(uint16_t opcode)
{
    uint8_t x = (opcode & 0x0F00) >> 8;
    soundTimer = V[x];
}

void Chip8::op_FX1E(uint16_t opcode)
{
    uint8_t x = (opcode & 0x0F00) >> 8;
    I += V[x];
}

void Chip8::op_FX29(uint16_t opcode)
{
    uint8_t x = (opcode & 0x0F00) >> 8;
    I = V[x] * 5;
}

void Chip8::op_FX33(uint16_t opcode)
{
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t val = V[x];

    memory[I] = val / 100;
    memory[I + 1] = (val / 10) % 10;
    memory[I + 2] = val % 10;
}

void Chip8::op_FX55(uint16_t opcode)
{
    uint8_t x = (opcode & 0x0F00) >> 8;

    for (auto i = 0; i <= x; ++i)
    {
        memory[I + i] = V[i];
    }
}

void Chip8::op_FX65(uint16_t opcode)
{
    uint8_t x = (opcode & 0x0F00) >> 8;

    for (auto i = 0; i <= x; ++i)
    {
        V[i] = memory[I + i];
    }
}