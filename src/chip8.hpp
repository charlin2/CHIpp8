#include <cstdint>
#include <cstdlib>
#include <stack>
#include <vector>
#include "display.hpp"
#include <iostream>

class Chip8
{
public:
    Chip8();

    uint8_t memory[4096]{};
    std::stack<uint16_t> stack{};
    uint16_t pc{0x200};
    Display display{};
    uint8_t V[16]{0};
    uint16_t I{0};
    uint8_t delayTimer{0};
    uint8_t soundTimer{0};
    uint8_t key[16]{0};

    void decode(uint16_t opcode);


private:
    /* ------OPCODES------ */
    // Clear screen
    void op_00E0();

    // Jump to address
    void op_1NNN(uint16_t opcode);

    // Call subroutine
    void op_2NNN(uint16_t opcode);

    // Return from subroutine
    void op_00EE(uint16_t opcode);

    // Skip next instruction if Vx == NN
    void op_3XNN(uint16_t opcode);

    // Skip next instruction if Vx != NN
    void op_4XNN(uint16_t opcode);

    // Skip next instruction if Vx == Vy
    void op_5XY0(uint16_t opcode);

    // Set Vx = NN
    void op_6XNN(uint16_t opcode);

    // Set Vx = Vx + NN
    void op_7XNN(uint16_t opcode);

    // Set Vx = Vy
    void op_8XY0(uint16_t opcode);

    // Set Vx = Vx OR Vy
    void op_8XY1(uint16_t opcode);

    // Set Vx = Vx AND Vy
    void op_8XY2(uint16_t opcode);

    // Set Vx = Vx XOR Vy
    void op_8XY3(uint16_t opcode);

    // Set Vx = Vx + Vy, set VF = carry
    void op_8XY4(uint16_t opcode);

    // Set Vx = Vx - Vy, set VF = NOT borrow
    void op_8XY5(uint16_t opcode);

    // Set Vx = Vx SHR 1
    void op_8XY6(uint16_t opcode);

    // Set Vx = Vy - Vx, set VF = NOT borrow
    void op_8XY7(uint16_t opcode);

    // Set Vx = Vx SHL 1
    void op_8XYE(uint16_t opcode);

    // Skip next instruction if Vx != Vy
    void op_9XY0(uint16_t opcode);

    // Set I = NNN
    void op_ANNN(uint16_t opcode);

    // Jump to location NNN + V0
    void op_BNNN(uint16_t opcode);

    // Set Vx = random byte AND NN
    void op_CXNN(uint16_t opcode);

    // Display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision
    void op_DXYN(uint16_t opcode);

    // Skip next instruction if key with the value of Vx is pressed
    void op_EX9E(uint16_t opcode);

    // Skip next instruction if key with the value of Vx is not pressed
    void op_EXA1(uint16_t opcode);

    // Set Vx = delay timer value
    void op_FX07(uint16_t opcode);

    // Wait for a key press, store the value of the key in Vx
    void op_FX0A(uint16_t opcode);

    // Set delay timer = Vx
    void op_FX15(uint16_t opcode);

    // Set sound timer = Vx
    void op_FX18(uint16_t opcode);

    // Set I = I + Vx
    void op_FX1E(uint16_t opcode);

    // Set I = location of sprite for digit Vx
    void op_FX29(uint16_t opcode);

    // Store BCD representation of Vx in memory locations I, I+1, and I+2
    void op_FX33(uint16_t opcode);

    // Store registers V0 through Vx in memory starting at location I
    void op_FX55(uint16_t opcode);

    // Read registers V0 through Vx from memory starting at location I
    void op_FX65(uint16_t opcode); 
};