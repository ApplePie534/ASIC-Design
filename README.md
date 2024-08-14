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

Here's the given list of instructions:

```
ADD r4, r5, r6
SUB r6, r4, r5
AND r5, r4, r6
OR r8, r5, r5
XOR r8, r4, r4
SLT r10, r2, r4
ADDI r12, r3, 5
SW r3, r1, 4
SRL r16, r11, r2
BNE r0, r1, 20
BEQ r0, r0, 15
LW r13, r11, 2
SLL r15, r11, r2
```

## 1. ADD r4, r5, r6
Binary: `0000000 00110 00101 000 00100 0110011`
- Opcode (6-0): `0110011` - R-type arithmetic operation
- rd (11-7): `00100` - Destination register r4
- funct3 (14-12): `000` - ADD operation
- rs1 (19-15): `00101` - First source register r5
- rs2 (24-20): `00110` - Second source register r6
- funct7 (31-25): `0000000` - Specifies ADD (vs SUB)

## 2. SUB r6, r4, r5
Binary: `0100000 00101 00100 000 00110 0110011`
- Opcode (6-0): `0110011` - R-type arithmetic operation
- rd (11-7): `00110` - Destination register r6
- funct3 (14-12): `000` - SUB operation
- rs1 (19-15): `00100` - First source register r4
- rs2 (24-20): `00101` - Second source register r5
- funct7 (31-25): `0100000` - Specifies SUB (vs ADD)

## 3. AND r5, r4, r6
Binary: `0000000 00110 00100 111 00101 0110011`
- Opcode (6-0): `0110011` - R-type arithmetic operation
- rd (11-7): `00101` - Destination register r5
- funct3 (14-12): `111` - AND operation
- rs1 (19-15): `00100` - First source register r4
- rs2 (24-20): `00110` - Second source register r6
- funct7 (31-25): `0000000` - Standard R-type

## 4. OR r8, r5, r5
Binary: `0000000 00101 00101 110 01000 0110011`
- Opcode (6-0): `0110011` - R-type arithmetic operation
- rd (11-7): `01000` - Destination register r8
- funct3 (14-12): `110` - OR operation
- rs1 (19-15): `00101` - First source register r5
- rs2 (24-20): `00101` - Second source register r5
- funct7 (31-25): `0000000` - Standard R-type

## 5. XOR r8, r4, r4
Binary: `0000000 00100 00100 100 01000 0110011`
- Opcode (6-0): `0110011` - R-type arithmetic operation
- rd (11-7): `01000` - Destination register r8
- funct3 (14-12): `100` - XOR operation
- rs1 (19-15): `00100` - First source register r4
- rs2 (24-20): `00100` - Second source register r4
- funct7 (31-25): `0000000` - Standard R-type

## 6. SLT r10, r2, r4
Binary: `0000000 00100 00010 010 01010 0110011`
- Opcode (6-0): `0110011` - R-type arithmetic operation
- rd (11-7): `01010` - Destination register r10
- funct3 (14-12): `010` - SLT operation
- rs1 (19-15): `00010` - First source register r2
- rs2 (24-20): `00100` - Second source register r4
- funct7 (31-25): `0000000` - Standard R-type

## 7. ADDI r12, r3, 5
Binary: `000000000101 00011 000 01100 0010011`
- Opcode (6-0): `0010011` - I-type arithmetic operation
- rd (11-7): `01100` - Destination register r12
- funct3 (14-12): `000` - ADDI operation
- rs1 (19-15): `00011` - Source register r3
- imm[11:0] (31-20): `000000000101` - Immediate value 5

## 8. SW r3, r1, 4
Binary: `0000000 00011 00001 010 00100 0100011`
- Opcode (6-0): `0100011` - S-type store operation
- imm[4:0] (11-7): `00100` - Lower bits of offset 4
- funct3 (14-12): `010` - SW operation
- rs1 (19-15): `00001` - Base address register r1
- rs2 (24-20): `00011` - Source register r3
- imm[11:5] (31-25): `0000000` - Upper bits of offset 4

## 9. SRL r16, r11, r2
Binary: `0000000 00010 01011 101 10000 0110011`
- Opcode (6-0): `0110011` - R-type arithmetic operation
- rd (11-7): `10000` - Destination register r16
- funct3 (14-12): `101` - SRL operation
- rs1 (19-15): `01011` - First source register r11
- rs2 (24-20): `00010` - Second source register r2
- funct7 (31-25): `0000000` - Specifies SRL (vs SRA)

## 10. BNE r0, r1, 20
Binary: `0000101 00001 00000 001 00000 1100011`
- Opcode (6-0): `1100011` - B-type branch operation
- imm[4:1|11] (11-7): `00000` - Part of offset 20
- funct3 (14-12): `001` - BNE operation
- rs1 (19-15): `00000` - First source register r0
- rs2 (24-20): `00001` - Second source register r1
- imm[12|10:5] (31-25): `0000101` - Rest of offset 20

## 11. BEQ r0, r0, 15
Binary: `0000011 00000 00000 000 11000 1100011`
- Opcode (6-0): `1100011` - B-type branch operation
- imm[4:1|11] (11-7): `11000` - Part of offset 15
- funct3 (14-12): `000` - BEQ operation
- rs1 (19-15): `00000` - First source register r0
- rs2 (24-20): `00000` - Second source register r0
- imm[12|10:5] (31-25): `0000011` - Rest of offset 15

## 12. LW r13, r11, 2
Binary: `000000000010 01011 010 01101 0000011`
- Opcode (6-0): `0000011` - I-type load operation
- rd (11-7): `01101` - Destination register r13
- funct3 (14-12): `010` - LW operation
- rs1 (19-15): `01011` - Base address register r11
- imm[11:0] (31-20): `000000000010` - Offset 2

## 13. SLL r15, r11, r2
Binary: `0000000 00010 01011 001 01111 0110011`
- Opcode (6-0): `0110011` - R-type arithmetic operation
- rd (11-7): `01111` - Destination register r15
- funct3 (14-12): `001` - SLL operation
- rs1 (19-15): `01011` - First source register r11
- rs2 (24-20): `00010` - Second source register r2
- funct7 (31-25): `0000000` - Standard R-type
  
</details>

<details>
  <summary>Lab 5</summary>

# RISC-V Instruction Waveforms


---

## Generating VCD Files and Viewing Waveforms

### Step 1: Running the Simulation to Generate the VCD File
To generate the VCD file, use the following command in your terminal:

```bash
iverilog -o dump iiitb_rv32i_tb.v iiitb_rv32i.v
./dump
```

This will generate the `iiitb_rv32i.vcd` file, which contains the waveform data.

### Step 2: Viewing the Waveform with GTKWave
Once the VCD file is generated, you can view the waveform using GTKWave. Use the following command:

```bash
gtkwave iiitb_rv32i.vcd
```
  
# RISC-V Operations: Standard ISA vs Hardcoded ISA

This table compares the standard RISC-V ISA with the hardcoded ISA values used in the implementation.

| Operation           | Standard RISC-V ISA | Hardcoded ISA  |
|---------------------|---------------------|----------------|
| ADD R6, R2, R1      | 32'h00110333         | 32'h02208300   |
| SUB R7, R1, R2      | 32'h402083b3         | 32'h02209380   |
| AND R8, R1, R3      | 32'h0030f433         | 32'h0230a400   |
| OR R9, R2, R5       | 32'h005164b3         | 32'h02513480   |
| XOR R10, R1, R4     | 32'h0040c533         | 32'h0240c500   |
| SLT R1, R2, R4      | 32'h0045a0b3         | 32'h02415580   |
| ADDI R12, R4, 5     | 32'h004120b3         | 32'h00520600   |
| BEQ R0, R0, 15      | 32'h00000f63         | 32'h00f00002   |
| SW R3, R1, 2        | 32'h0030a123         | 32'h00209181   |
| LW R13, R1, 2       | 32'h0020a683         | 32'h00208681   |
| SRL R16, R14, R2    | 32'h0030a123         | 32'h00271803   |
| SLL R15, R1, R2     | 32'h002097b3         | 32'h00208783   |


### Output Waveforms

# RISC-V Instruction Waveforms

Each section includes the assembly instruction, its corresponding machine code, and a screenshot of the waveform captured during simulation.

---
## 1. ADD Instruction

### Instruction:
```assembly
add r6, r1, r2  // r6 = r1 + r2
```

### Machine Code:
```assembly
32'h02208300
```

### Waveform:
<img width="772" alt="3808 1535301636" src="https://github.com/user-attachments/assets/40d9e8e4-a268-4f91-b7fb-d9e71aa39bf7">

---

## 2. SUB Instruction

### Instruction:
```assembly
sub r7, r1, r2  // r7 = r1 - r2
```

### Machine Code:
```assembly
32'h02209380
```

### Waveform:
<img width="772" alt="3808 1535301636" src="https://github.com/user-attachments/assets/661b5dd4-a936-4364-8aef-00863f2b4ab1">

---

## 3. AND Instruction

### Instruction:
```assembly
and r8, r1, r3  // r8 = r1 & r3
```

### Machine Code:
```assembly
32'h0230a400
```

### Waveform:
<img width="772" alt="3808 1535301636" src="https://github.com/user-attachments/assets/e386ab8a-aad5-46d8-9a2c-8a7705a78c8c">

---

## 4. OR Instruction

### Instruction:
```assembly
or r9, r2, r5  // r9 = r2 | r5
```

### Machine Code:
```assembly
32'h02513480
```

### Waveform:
<img width="772" alt="3808 1535301636" src="https://github.com/user-attachments/assets/c98d5b6d-09d6-4be5-80b2-7052e55ef249">

---

## 5. XOR Instruction

### Instruction:
```assembly
xor r10, r1, r4  // r10 = r1 ^ r4
```

### Machine Code:
```assembly
32'h0240c500
```

### Waveform:
<img width="772" alt="3808 1535301636" src="https://github.com/user-attachments/assets/78ce298d-12d5-41be-be08-79c7edee7049">

---

## 6. SLT Instruction

### Instruction:
```assembly
slt r11, r2, r4  // r11 = (r2 < r4) ? 1 : 0
```

### Machine Code:
```assembly
32'h02415580
```

### Waveform:
<img width="772" alt="3808 1535301636" src="https://github.com/user-attachments/assets/5f8f9ab8-5269-4df6-a276-703e1381f87c">

---

## 7. ADDI Instruction

### Instruction:
```assembly
addi r12, r4, 5  // r12 = r4 + 5
```

### Machine Code:
```assembly
32'h00520600
```

### Waveform:
<img width="772" alt="3808 1535301636" src="https://github.com/user-attachments/assets/03ae1b1b-f0a8-46e0-aec2-4094d3340c8e">

---

## 8. BEQ Instruction

### Instruction:
```assembly
beq r0, r0, 15  // if (r0 == r0) PC = PC + 15
```

### Machine Code:
```assembly
32'h000f0028
```

### Waveform:
<img width="772" alt="3808 1535301636" src="https://github.com/user-attachments/assets/a6b4f720-db66-4c59-a42b-24fa4993cdc3">

---

## 9. SW Instruction

### Instruction:
```assembly
sw r3, r1, 2  // Store word at memory[r1 + 2] = r3
```

### Machine Code:
```assembly
32'h00209181
```

### Waveform:
<img width="772" alt="3808 1535301636" src="https://github.com/user-attachments/assets/a46dc777-45f4-4b76-b6e3-0a549e9c5597">

---

## 10. LW Instruction

### Instruction:
```assembly
lw r13, r1, 2  // Load word from memory[r1 + 2] to r13
```

### Machine Code:
```assembly
32'h00208681
```

### Waveform:
<img width="772" alt="3808 1535301636" src="https://github.com/user-attachments/assets/dd37fc23-fa59-405a-84c7-a46e9740e830">


  
</details>

<details>
  <summary>Lab 6</summary>

---

# Simple Calendar Program

This is a basic C program that displays a calendar for a given month and year. It has been compiled and tested using both GCC and RISC-V GCC.

## Features

- **Leap Year Calculation:** Determines if a given year is a leap year.
- **Day Calculation:** Calculates the day of the week on which the first day of the month falls.
- **Month Display:** Prints the calendar for any specified month and year, showing the correct days of the week.

## How to Compile

### Using GCC

To compile the program with GCC, use the following command:

```sh
gcc calendar.c
```

### Using RISC-V GCC

To compile the program with RISC-V GCC, use the following command:

```sh
riscv64-unknown-elf-gcc -Ofast -mabi=lp64 -march=rv64i -o calendar.o calendar.c
```

## How to Run

### On Your Local Machine (GCC)

After compiling with GCC:

```sh
./a.out
```
<img width="772" alt="3808 1535301636" src="https://github.com/user-attachments/assets/08140048-f30d-4022-a7ac-2124bffe1b98">

### On a RISC-V Emulator or Hardware (RISC-V GCC)

After compiling with RISC-V GCC, you can run the program using the Spike RISC-V simulator with the following command:

```sh
spike pk calendar.o
```
<img width="772" alt="3808 1535301636" src="https://github.com/user-attachments/assets/f5c57764-e767-47bf-8e5f-e1b64a6bec12">

As we can see, both the compilers give the same output.


## Notes

- The calendar is centered within a width of 28 characters.
- This program assumes a modern terminal environment that supports basic text formatting.
- Alignment may vary slightly based on the terminal emulator or environment.

---

</details>


