# ASIC-Design

<details>
  <summary>Lab 1</summary>
  <p>Compiling the code using GCC compiler</p>
  <img src="https://github.com/user-attachments/assets/b2636e98-d5af-4fd3-9add-678d7f3f5112" alt="1st Screenshot">
  
  <img src="https://github.com/user-attachments/assets/dd7158f5-54ac-4786-a0a9-b1b78e3c5c46">
</details>

<details>
  <summary>Lab 2</summary>
  <p>Compiling the code using RISC-V compiler.
  Using O1:

  ```riscv64-unknown-elf-gcc -O1 -mabi=lp64 -march=rv64i -o sum1ton.o sum1ton.c```

  ```riscv64-unknown-elf-objdump -d sum1ton.o | less```
  </p>
  <img src="https://github.com/user-attachments/assets/b9d8e9d9-14c4-42fa-9a3a-a31ad482183f" alt="Feature 2 Screenshot">
  <p> The number of instructions is 15 in this case.</p>
  <p>
  Using Ofast:

  ```riscv64-unknown-elf-gcc -Ofast -mabi=lp64 -march=rv64i -o sum1ton.o sum1ton.c```

  ```riscv64-unknown-elf-objdump -d sum1ton.o | less```
  </p>
  <img src="https://github.com/user-attachments/assets/6159556e-237a-4a88-bf30-a0f632a59562">
  <p> The number of instructions is 12 in this case.</p>

  <p> The key differnce between both is that-O1 is a safer, more conservative optimization level suitable for most development work, while -Ofast prioritizes maximum performance, potentially at the cost of strict standard compliance and ease of debugging.</p>
</details>

<details>
  <summary>Lab 3</summary>
  <p><strong>Debugging</strong></p>
  <img src="https://github.com/user-attachments/assets/3f405d71-78e5-4c40-8bea-b114eadd8f47">
  <p>This image shows that we get the same output with both GCC and RISC-V Compilers.<p> 

  <img src="https://github.com/user-attachments/assets/08788d56-5a63-4c35-869f-1fe0a7890610">
  <p>

1. The debugger stops at program counter (pc) value 100b0.

2. "bbl loader" is displayed again, indicating the Berkeley Boot Loader.

3. The debugger then shows a series of instructions being executed:

   a. First instruction:
      - `core  0: 0x0000000000100b0 (0x00001637) lui     a2, 0x1`
      - This loads the upper immediate value 1 into register a2.
      - Before: a2 = 0x0000000000000000
      - After:  a2 = 0x0000000000001000

   b. Second instruction:
      - `core  0: 0x0000000000100b4 (0x00021537) lui     a0, 0x21`
      - This loads the upper immediate value 0x21 into register a0.
      - After:  a0 = 0x0000000000021000

   c. Third instruction:
      - `core  0: 0x0000000000100b8 (0xff010113) addi    sp, sp, -16`
      - This subtracts 16 from the stack pointer (sp).
      - After:  sp = 0x000003fffffffb40

5. The session ends with the user typing 'q' to quit the debugger.
</p>


  <img src="https://github.com/user-attachments/assets/1df33749-c4c7-47af-8783-ddc45e5d05a8" alt="1st Screenshot">
  <p> This is a Debugging session using a tool called Spike.

1. The command being run is `spike -d pk sum1ton.o`, where:
   - `spike` is the debugger
   - `-d` stands for "debug mode"
   - `sum1ton.o` is the object file being debugged

2. The debugger stops at the program counter (pc) value of 100b8.

3. "bbl loader" is a small program that loads and runs the main program.

4. The debugger shows the value of register 0 (which is often used as the stack pointer in RISC-V architecture):
   0x000003fffffffb50

5. The next line shows a core instruction being executed:
   `core  0: 0x0000000000100b8 (0xff010113) addi    sp, sp, -16`
   This is an ADDI (add immediate) instruction that subtracts 16 from the stack pointer.

6. After the instruction execution, the debugger again shows the value of register 0:
   0x000003fffffffb40
</p>

</details>

<details>
  <summary>Lab 4</summary>
  <p>

## Introduction

RISC-V is a free and open ISA that allows anyone to design, manufacture, and sell RISC-V chips and software. Unlike most other ISA designs, the RISC-V ISA is provided under open source licenses that do not require fees to use.

## RISC-V Instruction Format

RISC-V instructions are fixed-length 32-bit instructions (in the base integer ISA). Each instruction type has a unique format, but they all share some common fields:

- `opcode`: Specifies the operation to be performed
- `rd`: Destination register
- `rs1`, `rs2`: Source registers
- `funct3`, `funct7`: Additional operation specifiers

  <img width="772" alt="3808 1535301636" src="https://github.com/user-attachments/assets/74755f83-f475-492b-b24b-6e943441d34a">


## Types of RISC-V Instructions

RISC-V instructions are categorized into six main types:

### R-Type Instructions

R-type instructions are used for register-to-register operations.

Format: `| funct7 | rs2 | rs1 | funct3 | rd | opcode |`

Examples: ADD, SUB, AND, OR, XOR

### I-Type Instructions

I-type instructions are used for immediate and load operations.

Format: `| imm[11:0] | rs1 | funct3 | rd | opcode |`

Examples: ADDI, LWORD, JALR

### S-Type Instructions

S-type instructions are used for store operations.

Format: `| imm[11:5] | rs2 | rs1 | funct3 | imm[4:0] | opcode |`

Examples: SW, SH, SB

### B-Type Instructions

B-type instructions are used for conditional branch operations.

Format: `| imm[12|10:5] | rs2 | rs1 | funct3 | imm[4:1|11] | opcode |`

Examples: BEQ, BNE, BLT, BGE

### U-Type Instructions

U-type instructions are used for operations with upper immediate values.

Format: `| imm[31:12] | rd | opcode |`

Examples: LUI, AUIPC

### J-Type Instructions

J-type instructions are used for unconditional jumps.

Format: `| imm[20|10:1|11|19:12] | rd | opcode |`

Example: JAL

## Common RISC-V Instructions

Here are some common RISC-V instructions and their brief descriptions:

1. `ADD rd, rs1, rs2`: Add contents of rs1 and rs2, store in rd
2. `SUB rd, rs1, rs2`: Subtract rs2 from rs1, store in rd
3. `AND rd, rs1, rs2`: Bitwise AND of rs1 and rs2, store in rd
4. `OR rd, rs1, rs2`: Bitwise OR of rs1 and rs2, store in rd
5. `XOR rd, rs1, rs2`: Bitwise XOR of rs1 and rs2, store in rd
6. `SLL rd, rs1, rs2`: Logical left shift rs1 by rs2, store in rd
7. `SRL rd, rs1, rs2`: Logical right shift rs1 by rs2, store in rd
8. `LW rd, offset(rs1)`: Load word from memory
9. `SW rs2, offset(rs1)`: Store word to memory
10. `BEQ rs1, rs2, offset`: Branch if equal
11. `JAL rd, offset`: Jump and link

---

## Instruction Type Identification and Binary Encoding

Here's the given list of instructions with their corresponding types and 32-bit binary encodings:

1. `ADD r4, r5, r6` - R-type
   - Operation: Register-to-register addition
   - Binary: `0000000 00110 00101 000 00100 0110011`

2. `SUB r6, r4, r5` - R-type
   - Operation: Register-to-register subtraction
   - Binary: `0100000 00101 00100 000 00110 0110011`

3. `AND r5, r4, r6` - R-type
   - Operation: Register-to-register bitwise AND
   - Binary: `0000000 00110 00100 111 00101 0110011`

4. `OR r8, r5, r5` - R-type
   - Operation: Register-to-register bitwise OR
   - Binary: `0000000 00101 00101 110 01000 0110011`

5. `XOR r8, r4, r4` - R-type
   - Operation: Register-to-register bitwise XOR
   - Binary: `0000000 00100 00100 100 01000 0110011`

6. `SLT r10, r2, r4` - R-type
   - Operation: Set Less Than, comparing two registers
   - Binary: `0000000 00100 00010 010 01010 0110011`

7. `ADDI r12, r3, 5` - I-type
   - Operation: Add immediate, adding a constant to a register
   - Binary: `000000000101 00011 000 01100 0010011`

8. `SW r3, r1, 4` - S-type
   - Operation: Store word, storing a value from a register to memory
   - Binary: `0000000 00011 00001 010 00100 0100011`

9. `SRL r16, r11, r2` - R-type
   - Operation: Shift Right Logical, using registers for both value and shift amount
   - Binary: `0000000 00010 01011 101 10000 0110011`

10. `BNE r0, r1, 20` - B-type
    - Operation: Branch if Not Equal, a conditional branch
    - Binary: `0000101 00001 00000 001 00000 1100011`

11. `BEQ r0, r0, 15` - B-type
    - Operation: Branch if Equal, another conditional branch
    - Binary: `0000011 00000 00000 000 11000 1100011`

12. `LW r13, r11, 2` - I-type
    - Operation: Load Word, loading a value from memory into a register
    - Binary: `000000000010 01011 010 01101 0000011`

13. `SLL r15, r11, r2` - R-type
    - Operation: Shift Left Logical, using registers for both value and shift amount
    - Binary: `0000000 00010 01011 001 01111 0110011`
  
</details>


