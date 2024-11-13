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

## Source Code
- The source code can be found [here](calendar.c).

## Notes

- The calendar is centered within a width of 28 characters.
- This program assumes a modern terminal environment that supports basic text formatting.
- Alignment may vary slightly based on the terminal emulator or environment.

---

</details>

<details>
  <summary>Lab 7</summary>
  
  ## Day 3 Digital Logic with TL-Verilog and Makerchip

  ### Multiplexer Using Ternary Operator:
  2:1 Multiplexer: This Verilog code uses a ternary operator to implement a 2:1 multiplexer. The output f follows x1 when s is high (1) and x0 when s is low (0).
  ```
  assign f = s ? x1 : x0;
  ```
<img src="https://github.com/user-attachments/assets/1d8fa40e-0e65-4803-91c1-976724d09e7f">

4:1 Multiplexer: A higher-bit multiplexer can be realized using nested ternary operators, as shown in the Verilog code below:

```
assign f = sel[0] ? a : (sel[1] ? b : (sel[2] ? c : d));
```
<img src="https://github.com/user-attachments/assets/b9259d46-0a4d-4497-9222-043b629d6747">

### TL-Verilog
TL-Verilog (Transaction-Level Verilog) is a high-level hardware description language that simplifies the design and verification of digital systems, particularly CPUs and pipelines. Unlike traditional Verilog, TL-Verilog introduces transaction-level abstractions that help manage complexity, improve design readability, and enhance productivity by minimizing low-level control signals and boilerplate code. This results in faster design iterations and easier debugging, especially for pipelined architectures.

### Makerchip IDE
It is a cloud-based platform tailored for developing digital circuits using TL-Verilog. It offers an intuitive interface for writing, simulating, and visualizing TL-Verilog code. Makerchip provides real-time feedback, waveform visualizations, and integration with RISC-V and other processor design projects, making it an excellent tool for both learning and professional hardware development. Its user-friendly approach streamlines the hardware design process, from conception to validation.

### Basic Combinational Circuits using TL Verilog:

### 1. Inverter
 ```
 $out = ! $in;
 ```
<img src="https://github.com/user-attachments/assets/ea27e2c7-ea84-42d9-a646-4bbee39f943b">

### 2. Arithmetic Operation on Vectors
```
$out[4:0] = $in1[3:0] + $in2[3:0];
```
<img src="https://github.com/user-attachments/assets/f4bac631-d533-4813-a9a2-f71748ffb7d1">

### 3. 2-Input And Gate
```
$out = $in1 && $in2;
```
<img src="https://github.com/user-attachments/assets/cd42028a-6848-4725-88c6-4ffa03cb2f08">

### 4. 2-Input OR Gate
```
$out = $in1 || $in2;
```
<img src="https://github.com/user-attachments/assets/9e6d6955-c226-49f3-b719-501011854bbb">

### 5. 2-Input XOR Gate
```
$out = $in1 ^ $in2;
```
<img src = "https://github.com/user-attachments/assets/888db502-e3a4-4554-9910-0f5fb106c19c">

### 6. 2:1 MUX
```
$out[11:0] = $sel ? $in1[11:0] : $in0[11:0];
```
<img src="https://github.com/user-attachments/assets/6d553a28-5611-4431-a708-b42333e07ba8">

### 7. Combinational Calculator
```
$val1[31:0] = $rand1[3:0];
$val2[31:0] = $rand2[3:0];

$sum[31:0]  = $val1[31:0] + $val2[31:0];
$diff[31:0] = $val1[31:0] - $val2[31:0];
$prod[31:0] = $val1[31:0] * $val2[31:0];
$quot[31:0] = $val1[31:0] / $val2[31:0];

$out[31:0] = ($sel[1:0] == 2'b00) ? $sum[31:0]:
             ($sel[1:0] == 2'b01) ? $diff[31:0]:
             ($sel[1:0] == 2'b10) ? $prod[31:0]:
                                    $quot[31:0];
```
In this code snippet, two random 4-bit values, `$rand1[3:0]` and `$rand2[3:0]`, are assigned to the 32-bit variables `$val1[31:0]` and `$val2[31:0]`, respectively. The calculator then performs four arithmetic operations on these values:

The result of one of these operations is selected by a multiplexer (MUX), controlled by the selection bits `$sel[1:0]`. The MUX determines which operation's output is assigned to `$out[31:0]`.

<img src="https://github.com/user-attachments/assets/2130918d-3d8f-4b18-88a0-d1f412cc3be4">

## Sequential Circuits

---

A sequential circuit is a digital circuit that uses memory components to retain data, allowing it to generate outputs based on both current inputs and the circuit's previous state. Unlike combinational circuits, which depend only on present inputs, sequential circuits use feedback loops and storage elements like flip-flops or registers to track their internal state. This internal state, along with current inputs, influences the circuit's behavior, enabling tasks that require input history, such as counting, data storage, or event sequencing.

### 1. Fibbonacci Series:
```   
$num[31:0] = $reset ? 1 : (>>1$num + >>2$num);
```
<img src="https://github.com/user-attachments/assets/8e58adef-ce9c-4d90-afe3-513d51a71785">
<img src="https://github.com/user-attachments/assets/4b1fef26-edde-41c8-8b34-7750c5964381">

### 2. Counter Series:

```
$cnt[31:0] = $reset ? 0 : (>>1$cnt + 1);
```
<img src="https://github.com/user-attachments/assets/dd159d7a-bfa6-483d-8172-346035fa94f3">
<img src="https://github.com/user-attachments/assets/877073fd-8801-4c9c-94d6-afcefb16a0df">

#### 3. Sequential Calculator:
```

   $val1[31:0] = >>2$out;
   $val2[31:0] = $rand2[3:0];

   $sum[31:0]  = $val1[31:0] + $val2[31:0];
   $diff[31:0] = $val1[31:0] - $val2[31:0];
   $prod[31:0] = $val1[31:0] * $val2[31:0];
   $quot[31:0] = $val1[31:0] / $val2[31:0];

   $nxt[31:0] = ($sel[1:0] == 2'b00) ? $sum[31:0]:
                ($sel[1:0] == 2'b01) ? $diff[31:0]:
                ($sel[1:0] == 2'b10) ? $prod[31:0]:
                                       $quot[31:0];
   
   $out[31:0] = $reset ? 32'h0 : $nxt;
```
<img src="https://github.com/user-attachments/assets/f1b49683-b8ff-4f09-8ec9-a5c3363486f2">
<img src="https://github.com/user-attachments/assets/a33c41f3-aafc-4fc1-bee2-3b72f0f492c9">

## Pipelined Logic:

---
### 1. Recereating the design:
In Transaction-Level Verilog (TL-Verilog), pipelined logic is efficiently expressed using pipeline constructs that represent data flow across design stages, each corresponding to a clock cycle. This approach simplifies the modeling of sequential logic by automatically handling state propagation and enabling clear, concise descriptions of complex, multi-stage operations, improving both design clarity and maintainability.
```
|pipe
  @1
    $err1 = $bad_input || $illegal_op;
  @3
    $err2 = $over_flow || $err1;
  @6
    $err3 = $div_by_zero || $err2;
```
![image](https://github.com/user-attachments/assets/d0e8776f-ed04-4034-a728-d69b3a68efec)

### 2. Pipelined Calculator:
![image](https://github.com/user-attachments/assets/5556fa5e-606a-442b-81b8-6df8cb8e069c)


```
   |cal
      @1
         $reset = *reset;
         $clk_kar = *clk;

         $valid[31:0] = $reset ? 0 : (>>1$valid + 1);
         $valid_or_reset = $reset | ~$valid;
         
         $val1[31:0] = >>2$out;
         $val2[31:0] = $rand2[3:0];

         $sum[31:0]  = $val1[31:0] + $val2[31:0];
         $diff[31:0] = $val1[31:0] - $val2[31:0];
         $prod[31:0] = $val1[31:0] * $val2[31:0];
         $quot[31:0] = $val1[31:0] / $val2[31:0];
         
      @2
         $nxt[31:0] = ($sel[1:0] == 2'b00) ? $sum[31:0]:
                      ($sel[1:0] == 2'b01) ? $diff[31:0]:
                      ($sel[1:0] == 2'b10) ? $prod[31:0]:
                                             $quot[31:0];
        
         
         $out[31:0] = $valid_or_reset ? 32'h0 : $nxt;
         
```
![image](https://github.com/user-attachments/assets/5d050d5e-b9d6-48b7-b3e8-23e9c142c839)

### 3. Cycle Calculator with validity:
```

   $reset = *reset;
   $clk_kar = *clk;
   
   |cal
      @1
         $reset = *reset;
         $clk_kar = *clk;
         
         $cnt[31:0] = $reset ? 0 : (>>1$cnt + 1);
         $valid = $cnt;
         $valid_or_reset = ($reset | $valid);
         
      
      ?$valid
         @1
            $val1[31:0] = >>2$out;
            $val2[31:0] = $rand2[3:0];
            
            $sum[31:0]  = $val1[31:0] + $val2[31:0];
            $diff[31:0] = $val1[31:0] - $val2[31:0];
            $prod[31:0] = $val1[31:0] * $val2[31:0];
            $quot[31:0] = $val1[31:0] / $val2[31:0];
            
         @2
            $nxt[31:0] = ($sel[1:0] == 2'b00) ? $sum[31:0]:
                         ($sel[1:0] == 2'b01) ? $diff[31:0]:
                         ($sel[1:0] == 2'b10) ? $prod[31:0]:
                                                $quot[31:0];
            
            $out[31:0] = $valid_or_reset ? 32'h0 : $nxt;
            
            
            
```
![image](https://github.com/user-attachments/assets/e3cb7228-7d39-4d53-a8bb-fc357194ccd1)





















 
  ## Day 4 Basic RISC-V Microarchitecture

## Overview
This project implements a simple RISC-V instruction decoder, arithmetic logic unit (ALU), register file read and write operations, branch instructions, and a basic program to compute the sum of integers from 1 to 9 using TL-Verilog. The project is structured into several key sections, each performing a specific task in the CPU pipeline.

<img src="https://github.com/user-attachments/assets/b0db15f1-a725-4ca5-bb05-943e4bbf8d53">

---

## Steps

### 1. **Program Counter (PC) Implementation**
We initialize the program counter (PC) and update it to increment by 4 after every instruction. On reset, the PC is set to 0.

```verilog
$pc[31:0] = $reset ? '0 : >>1$pc + 32'd4;
```
<img src="https://github.com/user-attachments/assets/a9afc723-052f-4224-9579-89e8617a0eb2">

### 2. **Instruction Fetch**
- The instruction memory (`imem`) is read based on the current value of the PC.
- The read enable (`$imem_rd_en`) and read address (`$imem_rd_addr`) are set up using the PC.

<img src="https://github.com/user-attachments/assets/9399741a-8cff-4407-960b-15fbcd42ef8a">

### 3. **Instruction Decode**
- The instruction is decoded to identify the instruction type (I, R, S, B, J, U).
- Immediate values (`$imm`) and registers (`$rs1`, `$rs2`, `$rd`) are extracted based on the instruction type.

```verilog
$is_i_instr = $instr[6:2] ==? 5'b0000x || ...;
$imm[31:0] = $is_i_instr ? {{21{$instr[31]}}, $instr[30:20]} : ... ;
```
<img src="https://github.com/user-attachments/assets/959426a1-0855-475a-8664-a4664e55c54e">

### 4. **Register File Read**
- Register indices for reading (`$rs1`, `$rs2`) are set based on the decoded instruction.
- Data is read from the register file (`$rf_rd_data1`, `$rf_rd_data2`).

```verilog
$src1_value[31:0] = $rf_rd_data1;
$src2_value[31:0] = $rf_rd_data2;
```
<img src="https://github.com/user-attachments/assets/d4be976d-2034-4a78-9b24-73b0d5b052f0">

### 5. **ALU Operations**
- The Arithmetic Logic Unit (ALU) performs addition operations based on the instruction.
- For example, it computes the result of ADDI and ADD instructions:

```verilog
$result[31:0] = $is_addi ? $src1_value + $imm :
                $is_add ? $src1_value + $src2_value : 32'bx;
```
<img src="https://github.com/user-attachments/assets/5c73cc4f-2869-4ff5-9e78-5b7f4911dc2c">

### 6. **Register File Write**
- After an operation is completed, the result is written back to the register file.
- If the destination register (`$rd`) is valid, the write enable (`$rf_wr_en`) is activated and the result is written to the register.

```verilog
$rf_wr_en = $rd_valid && $rd != 5'b0;
$rf_wr_data[31:0] = $result;
```
<img src="https://github.com/user-attachments/assets/ab51554c-d669-4ef9-9673-fc29d497b268">

### 7. **Branch Instructions**
- Branch decisions are made based on the values of the source registers and the type of branch instruction (BEQ, BNE, etc.).
- If a branch is taken, the PC is updated to the target address.

```verilog
$taken_branch = $is_beq ? ($src1_value == $src2_value) :
                $is_bne ? ($src1_value != $src2_value) : ... ;
br_target_pc[31:0] = $pc + $imm;
```
<img src="https://github.com/user-attachments/assets/b06b091c-c48b-467c-869a-075ab07aacb1">

### 8. **Summation Program**
- We implemented a small RISC-V program to calculate the sum of integers from 1 to 9.
- The program increments the value of **r10** (x10) with each of the numbers.
- After the program completes, **x10** should contain **45** (the sum of 1 to 9).

### 9. **Waveform Check**
- At the end of the simulation, **x10** should hold **45**. This is verified using the following comparison:

```verilog
*passed = |cpu/xreg[10]>>5$value == (1+2+3+4+5+6+7+8+9);
```
<img src="https://github.com/user-attachments/assets/69836dcc-9a54-4e73-b37e-11bdb03ad1b8">

- As we can see, the simulation is successful.
![image](https://github.com/user-attachments/assets/716ab179-f212-4207-8e2a-5f79eeaae700)
- The value increases gradually till 45.

### CLK:
![image](https://github.com/user-attachments/assets/ab825bae-3aff-44d0-93db-f12724285efa)


### Reset:
![image](https://github.com/user-attachments/assets/8033e921-0102-4471-b1a2-109b7db0ce6f)



---
## Day 5 Pipelined RISC-V Microarchitecture

## Introduction
Pipelining is a key technique in processor design that allows multiple instructions to overlap in execution. This increases throughput by ensuring the processor is working on multiple stages of different instructions simultaneously. This README explains how the RISC-V processor design we implemented in TL-Verilog can be pipelined, and outlines the benefits of pipelining. Pipelining introduces hazards, notably the "branch instruction hazard," or "branch penalty." This occurs because branch instructions determine execution sequence changes, creating uncertainties. Hazards include:

    - Structural Hazards: Resource conflicts like shared execution units, causing pipeline stalls until resolved.

    - Data Hazards: Dependencies on previous instruction results, risking incorrect outcomes if data isn't ready.

    - Control Hazards (Branch Hazards): Uncertainty over branch outcomes delays confirmation until execution, potentially leading to incorrect instruction fetches and performance penalties due to pipeline flushing.




## Pipeline Stages
In a basic RISC-V processor, we can break down the instruction execution into **5 typical stages**:

1. **Instruction Fetch (IF)**: Fetch the instruction from memory using the Program Counter (PC).
2. **Instruction Decode (ID)**: Decode the fetched instruction, identifying the type of instruction, extracting immediate values, and reading registers.
3. **Execute (EX)**: Perform the operation (e.g., addition, branch comparison, etc.).
4. **Memory Access (MEM)**: If the instruction involves memory (like load or store), perform the memory access.
5. **Write Back (WB)**: Write the result back to the register file if necessary (e.g., result from ALU).



## Advantages of Pipelining

### 1. **Increased Throughput**
Pipelining allows multiple instructions to be in different stages of execution simultaneously. This increases the instruction throughput (number of instructions executed per unit time), as each instruction moves to the next stage in every clock cycle.

- Without pipelining, each instruction must complete all stages before the next one begins.
- With pipelining, while one instruction is being decoded, another is being fetched, and another is being executed.

### 2. **Higher Clock Frequency**
By breaking the execution into smaller steps (stages), each individual stage is simpler and takes less time to complete. This can enable the processor to run at a **higher clock frequency**, as each stage can be completed in one clock cycle.

### 3. **Better Resource Utilization**
All components of the CPU (ALU, registers, memory) are kept busy in different pipeline stages, making the design more **efficient**. For example, while the ALU is executing an instruction, the instruction fetch unit can fetch the next instruction, so there’s no idle time.

### 4. **Scalability**
Pipelining is a scalable approach, meaning additional pipeline stages can be added as needed to balance the workload. For example, a more complex instruction set might require additional decode or execution stages to handle specific operations, but the overall throughput remains high.

### 5. **Improved Performance per Area**
Pipelining can lead to better **performance per area** in hardware designs. By keeping functional units busy at all times, we avoid wasting silicon area on idle units, thus improving the utilization and overall performance of the processor.

### Valid signal:

The TL-Verilog code to introduce valid signal for pipelined logic is given below :

```
$start = >>1$reset && !$reset;
$valid = $reset ? 1'b0 : ($start || >>3$valid);
$valid_or_reset = $valid || $reset;
$rs1_or_funct3_valid    = $is_r_instr || $is_i_instr || $is_s_instr || $is_b_instr;
$rs2_valid              = $is_r_instr || $is_s_instr || $is_b_instr;
$rd_valid               = $is_r_instr || $is_i_instr || $is_u_instr || $is_j_instr;
$funct7_valid           = $is_r_instr;
 ```        
### Handling Data Hazards in Register File with Bypassing:
```
$src1_value[31:0] = $rs1_bypass ? >>1$result[31:0] : $rf_rd_data1[31:0];
$src2_value[31:0] = $rs2_bypass ? >>1$result[31:0] : $rf_rd_data2[31:0];
```

### Correcting branch target path:
```
   //Current instruction is valid if one of the previous 2 instructions were not (taken_branch or load or jump)
   $valid = ~(>>1$valid_taken_br || >>2$valid_taken_br || >>1$is_load || >>2$is_load || >>2$jump_valid 	|| >>1$jump_valid);
         
   //Current instruction is valid & is a taken branch
   $valid_taken_br = $valid && $taken_br;
         
   //Current instruction is valid & is a load
   $valid_load = $valid && $is_load;
         
   //Current instruction is valid & is jump
   $jump_valid = $valid && $is_jump;
   $jal_valid  = $valid && $is_jal;
   $jalr_valid = $valid && $is_jalr;
    
    *passed = |cpu/xreg[14]>>5$value == (1+2+3+4+5+6+7+8+9+10);
```

### Final 5 Stage Pipelined Logic:
```
\m4_TLV_version 1d: tl-x.org
\SV
   // Template code can be found in: https://github.com/stevehoover/RISC-V_MYTH_Workshop
   
   m4_include_lib(['https://raw.githubusercontent.com/BalaDhinesh/RISC-V_MYTH_Workshop/master/tlv_lib/risc-v_shell_lib.tlv'])

\SV
   m4_makerchip_module   // (Expanded in Nav-TLV pane.)
\TLV

   // /====================\
   // | Sum 0 to 10 Program |
   // \====================/
   //
   // Add 0,1,2,3,...,10 (in that order).
   //
   // Regs:
   //  r10 (a0): In: 0, Out: final sum
   //  r12 (a2): 10
   //  r13 (a3): 1..10
   //  r14 (a4): Sum
   // 
   // External to function:
   m4_asm(ADD, r10, r0, r0)             // Initialize r10 (a0) to 0.
   // Function:
   m4_asm(ADD, r14, r10, r0)            // Initialize sum register a4 with 0x0
   m4_asm(ADDI, r12, r10, 1011)         // Store count of 10 in register a2.
   m4_asm(ADD, r13, r10, r0)            // Initialize intermediate sum register a3 with 0
   // Loop:
   m4_asm(ADD, r14, r13, r14)           // Incremental addition
   m4_asm(ADDI, r13, r13, 1)            // Increment intermediate register by 1
   m4_asm(BLT, r13, r12, 1111111111000) // If a3 is less than a2, branch to label named <loop>
   m4_asm(ADD, r10, r14, r0)            // Store final result to register a0 so that it can be read by main program
   m4_asm(SW, r0, r10, 10000)           // Store r10 result in dmem
   m4_asm(LW, r17, r0, 10000)           // Load contents of dmem to r17
   m4_asm(JAL, r7, 00000000000000000000) // Done. Jump to itself (infinite loop). (Up to 20-bit signed immediate plus implicit 0 bit (unlike JALR) provides byte address; last immediate bit should also be 0)
   m4_define_hier(['M4_IMEM'], M4_NUM_INSTRS)

   |cpu
      @0
         $reset = *reset;
         $clk_ans = *clk;
         
         //PC fetch - branch, jumps and loads introduce 2 cycle bubbles in this pipeline
         $pc[31:0] = >>1$reset ? '0 : (>>3$valid_taken_br ? >>3$br_tgt_pc :
                                       >>3$valid_load     ? >>3$inc_pc[31:0] :
                                       >>3$jal_valid      ? >>3$br_tgt_pc :
                                       >>3$jalr_valid     ? >>3$jalr_tgt_pc :
                                                     (>>1$inc_pc[31:0]));
         // Access instruction memory using PC
         $imem_rd_en = ~ $reset;
         $imem_rd_addr[31:0] = $pc[M4_IMEM_INDEX_CNT+1:2];
         
         
      @1
         //Getting instruction from IMem
         $instr[31:0] = $imem_rd_data[31:0];
         
         //Increment PC
         $inc_pc[31:0] = $pc[31:0] + 32'h4;
         
         //Decoding I,R,S,U,B,J type of instructions based on opcode [6:0]
         //Only [6:2] is used here because this implementation is for RV64I which does not use [1:0]
         $is_i_instr = $instr[6:2] ==? 5'b0000x ||
                       $instr[6:2] ==? 5'b001x0 ||
                       $instr[6:2] == 5'b11001;
         
         $is_r_instr = $instr[6:2] == 5'b01011 ||
                       $instr[6:2] ==? 5'b011x0 ||
                       $instr[6:2] == 5'b10100;
         
         $is_s_instr = $instr[6:2] ==? 5'b0100x;
         
         $is_u_instr = $instr[6:2] ==? 5'b0x101;
         
         $is_b_instr = $instr[6:2] == 5'b11000;
         
         $is_j_instr = $instr[6:2] == 5'b11011;
         
         //Immediate value decode
         $imm[31:0] = $is_i_instr ? { {21{$instr[31]}} , $instr[30:20]} :
                      $is_s_instr ? { {21{$instr[31]}} , $instr[30:25] , $instr[11:8] , $instr[7]} :
                      $is_b_instr ? { {20{$instr[31]}} , $instr[7] , $instr[30:25] , $instr[11:8] , 1'b0} :
                      $is_u_instr ? { $instr[31] , $instr[30:12] , { 12{1'b0}} } :
                      $is_j_instr ? { {12{$instr[31]}} , $instr[19:12] , $instr[20] , $instr[30:21] , 1'b0} :
                      >>1$imm[31:0];
         
         //Generate valid signals for each instruction fields
         $rs1_or_funct3_valid    = $is_r_instr || $is_i_instr || $is_s_instr || $is_b_instr;
         $rs2_valid              = $is_r_instr || $is_s_instr || $is_b_instr;
         $rd_valid               = $is_r_instr || $is_i_instr || $is_u_instr || $is_j_instr;
         $funct7_valid           = $is_r_instr;
         
         //Decode other fields of instruction - source and destination registers, funct, opcode
         ?$rs1_or_funct3_valid
            $rs1[4:0]    = $instr[19:15];
            $funct3[2:0] = $instr[14:12];
         
         ?$rs2_valid
            $rs2[4:0]    = $instr[24:20];
         
         ?$rd_valid
            $rd[4:0]     = $instr[11:7];
         
         ?$funct7_valid
            $funct7[6:0] = $instr[31:25];
         
         $opcode[6:0] = $instr[6:0];
         
         //Decode instruction in subset of base instruction set based on RISC-V 32I
         $dec_bits[10:0] = {$funct7[5],$funct3,$opcode};
         
         //Branch instructions
         $is_beq   = $dec_bits ==? 11'bx_000_1100011;
         $is_bne   = $dec_bits ==? 11'bx_001_1100011;
         $is_blt   = $dec_bits ==? 11'bx_100_1100011;
         $is_bge   = $dec_bits ==? 11'bx_101_1100011;
         $is_bltu  = $dec_bits ==? 11'bx_110_1100011;
         $is_bgeu  = $dec_bits ==? 11'bx_111_1100011;
         
         //Jump instructions
         $is_auipc = $dec_bits ==? 11'bx_xxx_0010111;
         $is_jal   = $dec_bits ==? 11'bx_xxx_1101111;
         $is_jalr  = $dec_bits ==? 11'bx_000_1100111;
         
         //Arithmetic instructions
         $is_addi  = $dec_bits ==? 11'bx_000_0010011;
         $is_add   = $dec_bits ==? 11'b0_000_0110011;
         $is_lui   = $dec_bits ==? 11'bx_xxx_0110111;
         $is_slti  = $dec_bits ==? 11'bx_010_0010011;
         $is_sltiu = $dec_bits ==? 11'bx_011_0010011;
         $is_xori  = $dec_bits ==? 11'bx_100_0010011;
         $is_ori   = $dec_bits ==? 11'bx_110_0010011;
         $is_andi  = $dec_bits ==? 11'bx_111_0010011;
         $is_slli  = $dec_bits ==? 11'b0_001_0010011;
         $is_srli  = $dec_bits ==? 11'b0_101_0010011;
         $is_srai  = $dec_bits ==? 11'b1_101_0010011;
         $is_sub   = $dec_bits ==? 11'b1_000_0110011;
         $is_sll   = $dec_bits ==? 11'b0_001_0110011;
         $is_slt   = $dec_bits ==? 11'b0_010_0110011;
         $is_sltu  = $dec_bits ==? 11'b0_011_0110011;
         $is_xor   = $dec_bits ==? 11'b0_100_0110011;
         $is_srl   = $dec_bits ==? 11'b0_101_0110011;
         $is_sra   = $dec_bits ==? 11'b1_101_0110011;
         $is_or    = $dec_bits ==? 11'b0_110_0110011;
         $is_and   = $dec_bits ==? 11'b0_111_0110011;
         
         //Store instructions
         $is_sb    = $dec_bits ==? 11'bx_000_0100011;
         $is_sh    = $dec_bits ==? 11'bx_001_0100011;
         $is_sw    = $dec_bits ==? 11'bx_010_0100011;
         
         //Load instructions - support only 4 byte load
         $is_load  = $dec_bits ==? 11'bx_xxx_0000011;
         
         $is_jump = $is_jal || $is_jalr;
         
      @2
         //Get Source register values from reg file
         $rf_rd_en1 = $rs1_or_funct3_valid;
         $rf_rd_en2 = $rs2_valid;
         
         $rf_rd_index1[4:0] = $rs1[4:0];
         $rf_rd_index2[4:0] = $rs2[4:0];
         
         //Register file bypass logic - data forwarding from ALU to resolve RAW dependence
         $src1_value[31:0] = $rs1_bypass ? >>1$result[31:0] : $rf_rd_data1[31:0];
         $src2_value[31:0] = $rs2_bypass ? >>1$result[31:0] : $rf_rd_data2[31:0];
         
         //Branch target PC computation for branches and JAL
         $br_tgt_pc[31:0] = $imm[31:0] + $pc[31:0];
         
         $rs1_bypass = >>1$rf_wr_en && (>>1$rd == $rs1);
         $rs2_bypass = >>1$rf_wr_en && (>>1$rd == $rs2);
         
      @3
         //ALU implementation
         $result[31:0] = $is_addi  ? $src1_value +  $imm :
                         $is_add   ? $src1_value +  $src2_value :
                         $is_andi  ? $src1_value &  $imm :
                         $is_ori   ? $src1_value |  $imm :
                         $is_xori  ? $src1_value ^  $imm :
                         $is_slli  ? $src1_value << $imm[5:0]:
                         $is_srli  ? $src1_value >> $imm[5:0]:
                         $is_and   ? $src1_value &  $src2_value:
                         $is_or    ? $src1_value |  $src2_value:
                         $is_xor   ? $src1_value ^  $src2_value:
                         $is_sub   ? $src1_value -  $src2_value:
                         $is_sll   ? $src1_value << $src2_value:
                         $is_srl   ? $src1_value >> $src2_value:
                         $is_sltu  ? $sltu_rslt[31:0]:
                         $is_sltiu ? $sltiu_rslt[31:0]:
                         $is_lui   ? {$imm[31:12], 12'b0}:
                         $is_auipc ? $pc + $imm:
                         $is_jal   ? $pc + 4:
                         $is_jalr  ? $pc + 4:
                         $is_srai  ? ({ {32{$src1_value[31]}} , $src1_value} >> $imm[4:0]) :
                         $is_slt   ? (($src1_value[31] == $src2_value[31]) ? $sltu_rslt : {31'b0, $src1_value[31]}):
                         $is_slti  ? (($src1_value[31] == $imm[31]) ? $sltiu_rslt : {31'b0, $src1_value[31]}) :
                         $is_sra   ? ({ {32{$src1_value[31]}}, $src1_value} >> $src2_value[4:0]) :
                         $is_load  ? $src1_value +  $imm :
                         $is_s_instr ? $src1_value + $imm :
                                    32'bx;
         
         $sltu_rslt[31:0]  = $src1_value <  $src2_value;
         $sltiu_rslt[31:0] = $src1_value <  $imm;
         
         //Jump instruction target PC computation
         $jalr_tgt_pc[31:0] = $imm[31:0] + $src1_value[31:0]; 
         
         //Branch equations
         $taken_br = $is_beq ? ($src1_value == $src2_value) :
                     $is_bne ? ($src1_value != $src2_value) :
                     $is_blt ? (($src1_value < $src2_value) ^ ($src1_value[31] != $src2_value[31])) :
                     $is_bge ? (($src1_value >= $src2_value) ^ ($src1_value[31] != $src2_value[31])) :
                     $is_bltu ? ($src1_value < $src2_value) :
                     $is_bgeu ? ($src1_value >= $src2_value) :
                     1'b0;
         
         $valid = ~(>>1$valid_taken_br || >>2$valid_taken_br || >>1$is_load || >>2$is_load || >>2$jump_valid || >>1$jump_valid);
         
         //Current instruction is valid & is a taken branch
         $valid_taken_br = $valid && $taken_br;
         
         //Current instruction is valid & is a load
         $valid_load = $valid && $is_load;
         
         //Current instruction is valid & is jump
         $jump_valid = $valid && $is_jump;
         $jal_valid  = $valid && $is_jal;
         $jalr_valid = $valid && $is_jalr;
         
         //Destination register update - ALU result or load result depending on instruction
         $rf_wr_en = (($rd != '0) && $rd_valid && $valid) || >>2$valid_load;
         $rf_wr_index[4:0] = $valid ? $rd[4:0] : >>2$rd[4:0];
         $rf_wr_data[31:0] = $valid ? $result[31:0] : >>2$ld_data[31:0];
         
      @4
         //Data memory access for load, store
         $dmem_addr[3:0]     =  $result[5:2];
         $dmem_wr_en         =  $valid && $is_s_instr;
         $dmem_wr_data[31:0] =  $src2_value[31:0];
         $dmem_rd_en         =  $valid_load;
         
         //Write back data read from load instruction to register
         $ld_data[31:0]      =  $dmem_rd_data[31:0];
         
      
   *passed = |cpu/xreg[14]>>10$value == (1+2+3+4+5+6+7+8+9+10);
   //Run for 80 cycles without any checks
   *passed = *cyc_cnt > 80;
   *failed = 1'b0;
   
   // Macro instantiations for:
   //  o instruction memory
   //  o register file
   //  o data memory
   //  o CPU visualization
   |cpu
      m4+imem(@1)    // Args: (read stage)
      m4+rf(@2, @3)  // Args: (read stage, write stage) - if equal, no register bypass is required
      m4+dmem(@4)    // Args: (read/write stage)
   
   m4+cpu_viz(@4)    // For visualisation, argument should be at least equal to the last stage of CPU logic
                       // @4 would work for all labs
\SV
   endmodule
```
### Block diagram:
<image src="https://github.com/user-attachments/assets/bf8efb5b-2c4a-4c12-a281-6c868623d543">

### CLK:
<image src="https://github.com/user-attachments/assets/d2e34b69-736e-437a-9110-d9ded9a2dbde">

### Reset:
<image src="https://github.com/user-attachments/assets/d73e8484-0fd6-4346-9d7a-de5d6ecb2570">

### Gradual increase of sum:
<image src="https://github.com/user-attachments/assets/d6784de4-fe9b-4737-abe1-b783439afc5d">

### Viz Diagram:
- As seen here, reg 10 and reg 14 reach 55 after 64 cycles.
<image src="https://github.com/user-attachments/assets/a41c0360-916d-4679-b0cd-c598abd48cae">



---
</details>
<details>
  <summary>Lab 8</summary>

---

## Comparision of RISC-V Pre-Synthesis Simulation outputs using Iverilog GTKwave and Makerchip

### Overview

This project involves working with the VSDBabySoC, a small RISC-V System-on-Chip (SoC) design. The goal is to simulate and analyze the design using Icarus Verilog and GTKWave. Additionally, we will compare the results with those obtained from Makerchip, a cloud-based RISC-V design and simulation tool.


To install the required tools, run:

```bash
sudo apt install make python python3 python3-pip git iverilog gtkwave docker.io
sudo chmod 666 /var/run/docker.sock
pip3 install pyyaml click sandpiper-saas
```

## Setting Up the Project

1. **Clone the VSDBabySoC Repository:**

   Navigate to your home directory and clone the repository:

   ```bash
   cd ~
   git clone https://github.com/manili/VSDBabySoC.git
   cd VSDBabySoC
   ```

2. **Replace the `rvmyth.tlv` File:**

   Replace the `rvmyth.tlv` file in the `VSDBabySoC/src/module` folder with your RISC-V design from Makerchip.

3. **Update the Testbench:**

   Modify the testbench in the `VSDBabySoC/src/module` folder to match your design from Makerchip.

4. **Convert TL-Verilog to Verilog:**

   Use SandPiper-SaaS to translate the `.tlv` file to a Verilog `.v` file:

   ```bash
   sandpiper-saas -i ./src/module/rvmyth.tlv -o rvmyth.v --bestsv --noline -p verilog --outdir ./src/module/
   ```

## Running the Pre-Synthesis Simulation

1. **Compile the Verilog Code:**

   Use Icarus Verilog to compile the Verilog code and the testbench:

   ```bash
   iverilog -o output/pre_synth_sim.out -DPRE_SYNTH_SIM src/module/testbench.v -I src/include -I src/module
   ```

2. **Run the Simulation:**

   Navigate to the `output` directory and run the simulation:

   ```bash
   cd output
   ./pre_synth_sim.out
   ```

   This will generate a `.vcd` file that logs signal transitions during the simulation.

3. **View the Waveform:**

   Use GTKWave to analyze the waveform and verify the design's behavior:

   ```bash
   gtkwave pre_synth_sim.vcd
   ```
   ![image](https://github.com/user-attachments/assets/d4d138d8-a828-4610-9fa4-11d1eff535ee)
  ![image](https://github.com/user-attachments/assets/358cdf75-0bc4-43f6-b66e-fe612e37d716)
  ![image](https://github.com/user-attachments/assets/d803d370-bdbc-4714-a311-b54eef499199)

## Comparing with Makerchip Results

After obtaining the results from the pre-synthesis simulation using Icarus Verilog and GTKWave, we compared them with the results from Makerchip.

## GTKWave Simulation waveforms:
### CLK
 ![image](https://github.com/user-attachments/assets/c004cd55-0490-4b84-a549-add185e66726)
 ### Reset
  ![image](https://github.com/user-attachments/assets/9d003a44-2a83-4a34-b326-164df73642cb)
  ### Output 
  ![image](https://github.com/user-attachments/assets/4b9e9ecb-a66b-4f0a-b4db-37abb43bbda7)

## Makerchip IDE simulation results for comparison
### CLK
![360146103-ab825bae-3aff-44d0-93db-f12724285efa](https://github.com/user-attachments/assets/39d1d84e-11f6-4544-b7aa-727d45342c4d)
### Reset
![360145566-8033e921-0102-4471-b1a2-109b7db0ce6f](https://github.com/user-attachments/assets/1d7debd8-e953-4f54-b0ce-722ed668a784)
### Output
![360144599-716ab179-f212-4207-8e2a-5f79eeaae700](https://github.com/user-attachments/assets/47ea1fba-55ac-493c-82d1-928f66744d78)

---

## Conclusion

This lab demonstrates the process of simulating a RISC-V design using traditional simulation tools (Icarus Verilog and GTKWave) and compares the results with a cloud-based simulation tool (Makerchip).

---
  


  
</details>

<details>
  <summary>Lab 9</summary>
  
  ### To generate waveform for DAC and PLL peripheral

  The VSDBabySoC is a compact yet powerful SoC based on the RISCV architecture. It was designed with the primary goal of testing three open-source IP cores together for the first time and calibrating the analog components. The SoC includes an RVMYTH microprocessor, an 8x-PLL for stable clock generation, and a 10-bit DAC for communication with other analog devices.

  ![image](https://github.com/user-attachments/assets/313d5791-4a03-4f1c-a402-e4f0021cf430)

  ### BabySoC Simulation
  Developing and simulating the complete micro-architecture of a RISC-V CPU is a complex task. For this simulation, we'll focus on incorporating two key IP blocks: PLL and DAC.

### PLL (Phase-Locked Loop)

A **Phase-Locked Loop (PLL)** is a control system used to synchronize the phase of an output signal with a reference signal. It’s commonly used in various applications like:

- **Clock Generation and Synchronization**: In digital circuits, PLLs are used to generate a stable clock signal or synchronize different clock signals.
- **Frequency Synthesis**: PLLs can create a new frequency signal that is a multiple or fraction of a reference frequency.
- **Signal Demodulation**: In communication systems, PLLs can demodulate signals by locking onto the phase of the incoming signal.

A basic PLL consists of three main components:
1. **Phase Detector (PD)**: Compares the phase of the input signal with the phase of the output signal.
2. **Low Pass Filter (LPF)**: Smooths out the output of the phase detector to remove high-frequency components.
3. **Voltage-Controlled Oscillator (VCO)**: Generates the output signal whose frequency is adjusted based on the output of the low pass filter.

### DAC (Digital-to-Analog Converter)

A **Digital-to-Analog Converter (DAC)** is a device that converts digital data (usually binary) into an analog signal. DACs are used in a variety of applications, such as:

- **Audio Systems**: Converting digital audio signals (from CDs, computers, etc.) into analog signals that can be amplified and played through speakers.
- **Signal Generation**: Producing analog signals for testing and control purposes.
- **Video Systems**: Converting digital video signals into analog signals for display on analog monitors or TVs.

DACs work by taking discrete digital values and converting them into a continuous voltage or current. The quality of a DAC is often measured by its resolution (the number of bits it uses to represent the digital value) and its sampling rate.
  
# Simulation Steps

1. Clone this repo: https://github.com/Subhasis-Sahu/BabySoC_Simulation.git using the following command.

   ```
   git clone https://github.com/Subhasis-Sahu/BabySoC_Simulation.git
   ```
   
   ```
   cd BabySoC_Simulation
   ```

3. Change the rvmyth.v file.
   ![image](https://github.com/user-attachments/assets/495285bb-1203-4103-ae71-067ecd63c14e)

   ![image](https://github.com/user-attachments/assets/1e9868a5-7a09-45cd-9289-1313b1bdd34b)

4. Use the following commands
   ```
   iverilog -o ./pre_synth_sim.out -DPRE_SYNTH_SIM src/module/testbench.v -I src/include -I src/module/
   ```
   ```
   ./pre_synth_sim.out
   ```
   ![image](https://github.com/user-attachments/assets/6d0ba390-d209-4f6d-b559-141901085170)

6. Open GTKWave
   ```
   gtkwave pre_synth_sim.vcd
   ```

### Waveforms
![image](https://github.com/user-attachments/assets/dc3e9210-0bb4-4911-b7d7-9bfb4160c315)

</details>

<details>
  <summary>Lab 10</summary>
  
  ### RTL Design using verilog

  # Day  1

  RTL (Register-Transfer Level) design models synchronous digital circuits by outlining how data moves between hardware registers and the logic operations performed on signals. Verilog is often used to write these hardware descriptions at a high level.

To verify the functionality of the design, simulation tools like Verilog are employed. Simulators monitor the input signals, and whenever changes occur, they compute the corresponding output signals based on the circuit design. A key part of testing the design is creating a test bench, which applies test vectors (input patterns) to the circuit to confirm it behaves according to the specifications.

Once the simulation is complete, the results are stored in a VCD (Value Change Dump) file. This file tracks how the signals change over time and can be loaded into GTKWave, a waveform viewer. GTKWave allows designers to inspect signal interactions, timing, and overall circuit behavior. By analyzing the waveforms, designers can debug and validate that the circuit is operating correctly and meets the required specifications.

A test bench serves as a simulation framework used to verify digital circuit designs. It provides input stimuli (test vectors) to the design and monitors the output responses to ensure the circuit functions as expected. Test benches, typically written in the same hardware description language as the design (like Verilog), are critical for debugging and validating RTL designs.

![image](https://github.com/user-attachments/assets/67f2ef39-5140-4b4d-85be-d3ed537bcf3f)
![image](https://github.com/user-attachments/assets/28a9273b-3953-4e40-aaf2-a3534289ce8f)

```
mkdir VLSI
cd VLSI
```

```
git clone https://github.com/kunalg123/vsdflow.git
git clone https://github.com/kunalg123/sky130RTLDesignAndSynthesisWorkshop.git
```

![image](https://github.com/user-attachments/assets/6bc6599a-75ce-48be-9d08-3710b2a3fc3e)

### Simulation using iverilog simulator - 2:1 multiplexer rtl design

Compile the verilog and testbench file using the command and open GTKwave
```
iverilog good_mux.v tb_good_mux.v
./a.out
gtkwave tb_good_mux.vcd
```

![image](https://github.com/user-attachments/assets/cc83cf9e-8506-4098-ae7d-a51412eadf13)

To see the contents of the file :

```
vim tb_good_mux.v -o good_mux.v
```

![image](https://github.com/user-attachments/assets/4f509470-d31b-4f7c-a14b-dbae124938e7)

### Yosys

![image](https://github.com/user-attachments/assets/d073d4e7-2563-4081-88c8-09289c7f2849)

![image](https://github.com/user-attachments/assets/88c3b3e3-3cfc-497e-8a79-439b01589bbe)

Synthesis is the process of converting an RTL (Register-Transfer Level) design, written in a hardware description language like Verilog, into a gate-level version that can be physically implemented. This gate-level model is known as a netlist, which represents the design using interconnected logic gates. The synthesis process involves several steps:

1. **RTL to Gate-Level Translation**: The RTL code is transformed into a netlist, which is essentially a collection of logic gates and their connections. The inputs and outputs in this netlist remain consistent with the original RTL design, allowing the same test bench from the simulation phase to verify the synthesized design.

2. **Liberty (.lib) File**: This is a library file containing descriptions of various logic gates, such as AND, OR, and NOT. These gates come in different forms—some are designed for high speed, while others are optimized for low power or small area. The synthesis tool chooses from these gates depending on the design requirements.

    - **Fast Cells**: These gates prioritize speed, allowing for quicker signal transitions. However, they consume more power and take up more area due to their larger transistor sizes. Fast cells are used when performance is a critical factor.
    
    - **Slow Cells**: These gates are more energy-efficient and smaller in size, but they operate slower. They are useful in scenarios where reducing power consumption or area is more important than speed and help fix timing issues like hold-time violations.

3. **Constraints**: During synthesis, constraint files play a vital role by instructing the tool on how to balance performance, power, and area. These files define the desired timing and performance goals, helping the synthesis tool make trade-offs in cell selection to ensure the design meets the required specifications for speed, power efficiency, and chip area.

### Synthesis Commands

```
yosys
```

![image](https://github.com/user-attachments/assets/571caa55-b371-4951-8b78-282a2ac6ced8)

```
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
read_verilog good_mux.v
synth -top good_mux
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
show
```

![image](https://github.com/user-attachments/assets/ab6d791b-43a2-4eef-9efe-365ca11829be)

```
write_verilog -noattr good_mux_netlist.v
!vim good_mux_netlist.v
```

![image](https://github.com/user-attachments/assets/352d981c-4a68-4eae-b7c1-dfbe719d1891)


# Day 2

Command to open the libary file
```
$ vim ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
```
To shut off the background colors/ syntax off:
```
: syn off
```
To enable the line numbers
```
: se nu
```
![image](https://github.com/user-attachments/assets/ea25e36e-cd4b-432f-bcfd-eb172b8fdd3d)

For a design to work, there are three important parameters that determines how the Silicon works: Process (Variations due to Fabrications), Voltage (Changes in the behavior of the circuit) and Temperature (Sensitivity of semiconductors). Libraries are characterized to model these variations.

### .lib(liberty) File contents

The timing data of standard cells is provided in the liberty format. Every .lib file will provide timing, power, noise, area information for a single corner ie process,voltage, temperature etc.

1. Library
     - general information common to all cells in the library.
2. Cell
    - specific information about each standard cell.
3. Pin
    - Timing, power, capacitance, leakage functionality etc characteristics for each pin in each cell. 

![image](https://github.com/user-attachments/assets/c13391db-a17c-4cf0-a701-f7af921f02cb)

### Hierarchial synthesis vs Flat synthesis

Open file
```
vim multiple_modules.v
```
Use yosys
```
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
read_verilog multiple_modules.v
synth -top multiple_modules
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
show multiple_modules
write_verilog -noattr multiple_modules_hier.v
!vim multiple_modules_hier.v
```
### Multiple Modules:
![image](https://github.com/user-attachments/assets/3e262a05-34dd-417f-bd92-a218529eca3d)

### Logic:
![image](https://github.com/user-attachments/assets/e6c3dc0c-db04-4bf6-8b12-e3137ed0f1cb)

### Netlist:
![image](https://github.com/user-attachments/assets/bf64f6aa-7fea-4f4e-9876-93c83370f8f5)


## Flat Synthesis

Merges all hierarchical modules in the design into a single module to create a flat netlist

To flatten the netlist
```
flatten
```
Writing the netlist in a crisp manner and to view it
```
write_verilog -noattr multiple_modules_flat.v
!vim multiple_modules_flat.v
```
![image](https://github.com/user-attachments/assets/4f1418d9-1774-4d20-9375-382032449c50)

![image](https://github.com/user-attachments/assets/5ffa65ee-da96-42e5-b184-3b64d44e0fa2)

### Module Level Synthesis

This method is preferred when multiple instances of same module are used. The synthesis is carried out once and is replicate multiple times, and the multiple instances of the same module are stitched together in the top module.

```
1. yosys
2. read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
3. read_verilog multiple_modules.v
4. synth -top sub_module1
5. abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
6. show
```

![image](https://github.com/user-attachments/assets/9fb8c1ef-95f0-4540-b0bb-bc6a50ee4929)


## Various Flop coding styles and optimization

When an input signal changes in a digital design, the output shifts after a certain propagation delay. Every logic gate introduces some delay to signals, and these delays can cause both expected and unexpected transitions in the output. These unexpected transitions, known as *glitches*, occur when the output momentarily differs from the expected value. Glitches often happen when delays along different signal paths vary, causing incorrect outputs when these signals meet at an output gate. In general, the more combinational logic present, the more glitch-prone the output becomes, leading to instability until the output value settles.

### Flip-Flop Overview

A D flip-flop is a sequential element that captures the input value (denoted by `d`) at a specific clock edge. It’s a key component in digital logic circuits. D flip-flops come in two variations: **Rising-Edge D Flip-Flop** (triggered on the clock's rising edge) and **Falling-Edge D Flip-Flop** (triggered on the clock's falling edge).

Each flip-flop needs to start with an initial state, otherwise the combinational logic feeding into it might produce invalid (garbage) values. To manage this, control pins like *Set* and *Reset* are included in flip-flops, and these controls can operate either *synchronously* or *asynchronously*.

### Asynchronous Reset

In asynchronous reset, the flip-flop's always block is evaluated whenever there’s a change in the clock or a change in the set/reset signals. The circuit is triggered by the clock's positive edge, but when the reset or set signal is activated, the output `q` immediately changes—regardless of the clock’s state. This means that the reset or set takes effect instantly, without waiting for the next clock edge.

### Synchronous Reset
In a synchronous reset, the control signals (set/reset) only take effect at the active edge of the clock (rising or falling, depending on the flip-flop design). Unlike asynchronous reset, the flip-flop waits for the clock edge to trigger any changes. When the clock edge occurs, if the reset signal is active, the output will be reset to the specified state. This method ensures that set/reset behavior is tied to the timing of the clock, which can simplify the timing analysis and prevent glitches or other timing issues in the circuit.

## FLIP FLOP SIMULATION

Steps Followed for analysing Asynchronous behavior:

1. Load the design in iVerilog by giving the verilog and testbench file names
```
iverilog dff_asyncres.v tb_dff_asyncres.v 
```
2. List so as to ensure that it has been added to the simulator
```
ls
```
4. To dump the VCD file
```
./a.out
```
6. To load the VCD file in GTKwaveform
```
gtkwave tb_dff_asyncres.vcd
```
![image](https://github.com/user-attachments/assets/6011bba5-bd98-4468-b261-6444b5974100)

### Asynchronus reset:
![image](https://github.com/user-attachments/assets/037c8cce-e122-4f88-91fa-3d8a611d726f)

### Asynchronous set:
![image](https://github.com/user-attachments/assets/7f1c623c-31d2-40ef-a36e-ba09c3edc83a)

### Synchronous reset:
![image](https://github.com/user-attachments/assets/76d4d4ac-46c1-49b1-84d0-4b0831c76716)

## FLIP FLOP SYNTHESIS


```bash
1. Invoke Yosys
yosys

2. Read library 
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

3. Read Design
read_verilog dff_asyncres.v

4. Synthesize Design - this controls which module to synthesize
synth -top dff_asyncres

5. There will be a separate flop library under a standard library, but here we point back to the same library and tool looks only for DFF instead of all cells
dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

6. Generate Netlist
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

7. Realizing Graphical Version of Logic for single modules
show  
```
![image](https://github.com/user-attachments/assets/859af59d-1e62-492a-838c-11fc31d4d3c6)
![image](https://github.com/user-attachments/assets/c867ea43-2451-4e2b-adb8-53d328acb11a)

### Statistics of D FLipflop with Asynchronous set

![image](https://github.com/user-attachments/assets/7f466349-579f-4a03-8441-15eaa847edb1)
![image](https://github.com/user-attachments/assets/4d373f92-074a-44ed-bf11-c725d33d90fa)

### Statistics of D FLipflop with Synchronous Reset
![image](https://github.com/user-attachments/assets/6217aff7-cd93-4bb1-b08a-df10fba68564)
![image](https://github.com/user-attachments/assets/ef2a0bde-b714-4f9a-99f2-0784416c49e6)

## Interesting Optimizations

```bash
# Open the modules using vim
vim mult_*.v -o

# Invoke Yosys
yosys

# Read library
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

# Read Design
read_verilog mult_2.v

# Synthesize Design - this controls which module to synthesize
synth -top mul2

# Generate Netlist
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

# Realizing Graphical Version of Logic for single modules
show 

# Writing the netlist in a crisp manner
write_verilog -noattr mult_2.v

# Open the netlist in vim
!vim mult_2.v
```
### (i) mult_2.v
![image](https://github.com/user-attachments/assets/101e75e2-8c85-4109-9fc0-f00bfa715771)
![image](https://github.com/user-attachments/assets/78f1a737-9798-41a7-8fb9-fcb40a0ffd45)
![image](https://github.com/user-attachments/assets/d72b06ce-4da0-4cc0-94d1-b838262fd77c)
![image](https://github.com/user-attachments/assets/77ad4583-945d-47a3-a7d1-59f5c78cf4b3)

### (ii) mult_8.v
![image](https://github.com/user-attachments/assets/2d916528-f48d-4aa9-99fe-09b6b18fa94a)
![image](https://github.com/user-attachments/assets/f522980d-da5b-4723-a72d-360d3eb43081)
![image](https://github.com/user-attachments/assets/4bb44e57-4de8-4aff-8ee6-f10184e3ca36)


# Day 3

### Logic Circuits

Combinational circuits are time-independent, meaning they don’t rely on previous inputs to produce an output. In contrast, sequential circuits depend on clock cycles and consider both present and past inputs to generate their outputs.

### 3.1. Introduction to Logic Optimizations

#### Combinational Logic Optimization

**Why is combinational logic optimization important?**
- The main goal is to reduce logic complexity and create a more efficient design.
  - Optimized designs lead to significant savings in both area and power consumption.

**Types of Combinational Optimizations:**

1. **Constant Propagation**
   - A straightforward optimization technique.
  
2. **Boolean Logic Optimization**
   - Techniques like Karnaugh Maps and Quine-McCluskey are used to simplify logic.

---

#### Constant Propagation

In constant propagation, inputs that don’t affect the output are ignored or simplified. This reduces the complexity of the combinational logic, leading to area and power savings.

Example:

Y = ((AB) + C)'

If A = 0, then:

Y = (0 + C)' = C'

---

#### Boolean Logic Optimization

Boolean logic optimization simplifies complex boolean expressions using the laws of boolean algebra.

For instance:

```verilog
assign y = a ? (b ? c : (c ? a : 0)) : (!c)
```

can be simplified as:

```verilog
y = a'c' + abc + ab'c
y = a'c' + ac(b + b')
y = a'c' + ac
y = a XNOR c
```

---

### Sequential Logic Optimization

**Types of Sequential Optimizations:**

1. **Basic Techniques:**
   - Sequential Constant Propagation.

2. **Advanced Techniques:**
   - State Optimization.
   - Retiming.
   - Sequential Logic Cloning (Floorplan-Aware Synthesis).
  
### COMBINATIONAL LOGIC OPTIMIZATION

## Design infers 2 input AND Gate:
```
1. yosys
2. read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
3. read_verilog opt_check.v
4. synth -top opt_check
5. abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
6. opt_clean -purge
7. show
```

![image](https://github.com/user-attachments/assets/e5bb7446-7bc7-478b-b0aa-b7184be0131c)
![image](https://github.com/user-attachments/assets/79c494ff-bddd-4faf-9045-b23426bd8f46)
![image](https://github.com/user-attachments/assets/71e9d336-2d18-4ade-bef2-1c71ab6a2646)

## Design infers 2 input OR Gate:
```
1. yosys
2. read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
3. read_verilog opt_check2.v
4. synth -top opt_check2
5. abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
6. opt_clean -purge
7. show
```

![image](https://github.com/user-attachments/assets/e573791f-25ec-45e3-8fe6-99c0983b581f)
![image](https://github.com/user-attachments/assets/dee55aeb-b5c4-494b-835a-76c7d96f3904)
![image](https://github.com/user-attachments/assets/51dec145-c1a4-407c-8111-718f6193da51)

## Design infers 3 input AND Gate:

```
1. yosys
2. read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
3. read_verilog opt_check3.v
4. synth -top opt_check3
5. abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
6. opt_clean -purge
7. show
```
![image](https://github.com/user-attachments/assets/877c5266-8211-4c91-a1bb-22cca030904f)
![image](https://github.com/user-attachments/assets/c2268dba-7e2b-4fa2-b0b7-bfe3966de6c4)
![image](https://github.com/user-attachments/assets/4b408588-6b1e-4d35-8321-7439c753346f)

## Design infers 2 input XNOR Gate (3 input Boolean Logic)
```
1. yosys
2. read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
3. read_verilog opt_check4.v
4. synth -top opt_check4
5. abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
6. opt_clean -purge
7. show
```
![image](https://github.com/user-attachments/assets/96221d03-7b9c-4a06-a333-2c0a895225f8)
![image](https://github.com/user-attachments/assets/6634b36d-73b1-45a0-9826-01bd2492951a)
![image](https://github.com/user-attachments/assets/f81bb4ce-3bdb-4e72-83f1-9f7a4acf3cb6)

## Sequential Logic Optimizations
### Example 1:

Verilog code:
```
module dff_const1(input clk, input reset, output reg q);
always @(posedge clk, posedge reset)
begin
	if(reset)
		q <= 1'b0;
	else
		q <= 1'b1;
end
endmodule
```

For netlist:
```
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
read_verilog dff_const1.v
synth -top dff_const1
dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
show
write_verilog -noattr dff_const1_net.v
```
![image](https://github.com/user-attachments/assets/544c3667-0bae-48ce-8aa4-a2abdeb85e78)
![image](https://github.com/user-attachments/assets/97a10b0a-e86b-4390-abba-3c3a40364509)
![image](https://github.com/user-attachments/assets/2d3578ff-f790-4ec3-b724-0af20183edf4)

GTKWave Output:
```
iverilog dff_const1.v tb_dff_const1.v
./a.out
gtkwave tb_dff_const1.vcd
```
![image](https://github.com/user-attachments/assets/adcba227-d956-4584-a846-5ca9560f3cd8)

### Example 2:

Verilog code:

```
module dff_const2(input clk, input reset, output reg q);
always @(posedge clk, posedge reset)
begin
	if(reset)
		q <= 1'b1;
	else
		q <= 1'b1;
end
endmodule
```
For netlist:
```
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
read_verilog dff_const2.v
synth -top dff_const2
dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
show
write_verilog -noattr dff_const2_net.v
```

![image](https://github.com/user-attachments/assets/3a686361-0579-46a9-95c3-0308652a8b3e)
![image](https://github.com/user-attachments/assets/7d2f77f7-8706-46db-8ac5-51bb23353458)
![image](https://github.com/user-attachments/assets/b433b1f4-8ddc-4f27-8191-48a18fe39604)

GTKWave Output:
```
iverilog dff_const2.v tb_dff_const2.v
./a.out
gtkwave tb_dff_const2.vcd
```
![image](https://github.com/user-attachments/assets/08502db5-7fd8-4c1f-bbb0-9e4e84923c91)

### Example 3:

Verilog code:

```
module dff_const3(input clk, input reset, output reg q);
reg q1;

always @(posedge clk, posedge reset)
begin
	if(reset)
	begin
		q <= 1'b1;
		q1 <= 1'b0;
	end
	else
	begin
		q1 <= 1'b1;
		q <= q1;
	end
end
endmodule
```
For netlist:
```
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
read_verilog dff_const3.v
synth -top dff_const3
dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
show
write_verilog -noattr dff_const3_net.v
```
![image](https://github.com/user-attachments/assets/9afa20ea-967f-4120-b651-c49dccebccf8)
![image](https://github.com/user-attachments/assets/419bce34-7849-488b-a77a-731c9256edcb)
![image](https://github.com/user-attachments/assets/8a4be240-026a-497c-a210-e821c15becd7)

GTKWave Output:
```
iverilog dff_const3.v tb_dff_const3.v
./a.out
gtkwave tb_dff_const3.vcd
```
![image](https://github.com/user-attachments/assets/a061704a-b042-4b38-949d-91d4e7baf66c)

### Example 4:

Verilog code:

```
module dff_const4(input clk, input reset, output reg q);
reg q1;

always @(posedge clk, posedge reset)
begin
	if(reset)
	begin
		q <= 1'b1;
		q1 <= 1'b1;
	end
else
	begin
		q1 <= 1'b1;
		q <= q1;
	end
end
endmodule
```
For netlist:
```
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
read_verilog dff_const4.v
synth -top dff_const4
dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
show
write_verilog -noattr dff_const4_net.v
```
![image](https://github.com/user-attachments/assets/d631da6a-da8d-4934-9341-6bf9dd7105ea)
![image](https://github.com/user-attachments/assets/26b3def2-16eb-4155-9112-eccfcee3a5ae)
![image](https://github.com/user-attachments/assets/bb8f5c32-9500-478f-b832-da15d33f97f9)

GTKWave Output:
```
iverilog dff_const4.v tb_dff_const4.v
./a.out
gtkwave tb_dff_const4.vcd
```

![image](https://github.com/user-attachments/assets/34cdbb2d-e2b5-4d25-a362-6895f68a9e5f)

## Example 5:

Verilog code:
```
module dff_const5(input clk, input reset, output reg q);
reg q1;
always @(posedge clk, posedge reset)
	begin
		if(reset)
		begin
			q <= 1'b0;
			q1 <= 1'b0;
		end
	else
		begin
			q1 <= 1'b1;
			q <= q1;
		end
	end
endmodule
```

For netlist:

```
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
read_verilog dff_const5.v
synth -top dff_const5
dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
show
write_verilog -noattr dff_const5_net.v
```

![image](https://github.com/user-attachments/assets/70f8b83e-b904-4513-8070-1b37ab5422a5)
![image](https://github.com/user-attachments/assets/b99b3dbc-f202-4b03-81d5-cb637d3f8fd4)
![image](https://github.com/user-attachments/assets/8d7d4ce9-31ff-482c-8d86-18e272fc1516)

GTKWave Output:

```
iverilog dff_const5.v tb_dff_const5.v
./a.out
gtkwave tb_dff_const5.vcd
```

![image](https://github.com/user-attachments/assets/34d60ea6-b149-4d26-89aa-5baa0f370320)

## Sequential Logic Optimizations for unused outputs

### Example 1:
Verilog code:

```
module counter_opt (input clk , input reset , output q);
reg [2:0] count;
assign q = count[0];
always @(posedge clk ,posedge reset)
begin
	if(reset)
		count <= 3'b000;
	else
		count <= count + 1;
end
endmodule
```

Run the below code for netlist:

```
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
read_verilog counter_opt.v
synth -top counter_opt
dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
show
write_verilog -noattr counter_opt_net.v
```

![image](https://github.com/user-attachments/assets/ba4b7135-1dce-4de4-84e4-552c74318a43)
![image](https://github.com/user-attachments/assets/6e905ba0-3605-4c7f-846a-1d5a1ca73fc2)
![image](https://github.com/user-attachments/assets/aab0d571-cdf5-41e1-8872-ec38b8f4b005)

GTKWave Output:

```
iverilog counter_opt.v tb_counter_opt.v
./a.out
gtkwave tb_counter_opt.vcd
```

![image](https://github.com/user-attachments/assets/d15f4800-297a-416b-9f43-80136d7a6ea8)

### Modified counter logic:

Verilog code:

```
module counter_opt (input clk , input reset , output q);
reg [2:0] count;
assign q = {count[2:0]==3'b100};
always @(posedge clk ,posedge reset)
begin
if(reset)
	count <= 3'b000;
else
	count <= count + 1;
end
endmodule
```
Run the below code for netlist:
```
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
read_verilog counter_opt.v
synth -top counter_opt
dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib
show
write_verilog -noattr counter_opt_net.v
```

![image](https://github.com/user-attachments/assets/2a428be4-b20b-4ce8-a6a8-da191654e5fa)
![image](https://github.com/user-attachments/assets/181366fb-52d5-43fb-93ff-43cb3b0fc3a0)
![image](https://github.com/user-attachments/assets/cfdd627b-693b-4ad0-8ee0-4efc6c8aac96)

GTKWave Output:
```
iverilog counter_opt.v tb_counter_opt.v
./a.out
gtkwave tb_counter_opt.vcd
```
![image](https://github.com/user-attachments/assets/3a610b6f-23b3-4e4d-ab99-2840f1e871ed)


# Day 4

Gate Level Simulation (GLS) is an important verification step in digital circuit design. It involves simulating the synthesized netlist, which is a more detailed, lower-level version of the design. A testbench is used to verify both the logic and timing behavior of the netlist. By comparing the simulated outputs with the expected results, GLS helps ensure that the synthesis process has not introduced any errors and that the design satisfies its performance and timing requirements.

<img width="855" alt="1" src="https://github.com/user-attachments/assets/e860bad0-240f-49c3-96cb-5d578bca2761">

Sensitivity lists are vital for ensuring correct circuit behavior. An incomplete sensitivity list can result in unintended latches. The execution behavior of blocking and non-blocking assignments in always blocks differs. Misusing blocking assignments may inadvertently generate latches, leading to mismatches between synthesis and simulation. To prevent these problems, it's important to thoroughly assess circuit behavior and verify that both the sensitivity list and assignments correspond to the intended functionality.

## GLS Simulation

## Example 1:

Verilog code:
```
module ternary_operator_mux (input i0 , input i1 , input sel , output y);
assign y = sel?i1:i0;
endmodule
```
Simulation:
```
iverilog ternary_operator_mux.v tb_ternary_operator_mux.v
./a.out
gtkwave tb_ternary_operator_mux.vcd
```
![image](https://github.com/user-attachments/assets/18a2ac81-a5f9-45e5-88a0-ed3ae3e92cdc)

Netlist:
```
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib  
read_verilog ternary_operator_mux.v
synth -top ternary_operator_mux
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib 
show
write_verilog -noattr ternary_operator_mux_net.v
```
![image](https://github.com/user-attachments/assets/7bfe5b77-4248-42e4-bf54-6ca2d718a7f7)
![image](https://github.com/user-attachments/assets/3f82ed5a-947d-4b31-ab86-9a3791730a19)
![image](https://github.com/user-attachments/assets/06cb8af4-93e2-4acf-b290-33697598986d)

GLS:
```
iverilog ../my_lib/verilog_model/primitives.v ../my_lib/verilog_model/sky130_fd_sc_hd.v ternary_operator_mux_net.v tb_ternary_operator_mux.v
./a.out
gtkwave tb_ternary_operator_mux.vcd
```
![image](https://github.com/user-attachments/assets/bbcafd9f-c8d3-425d-a209-1f2cc6bfdbc9)

In this case there is no mismatch between the waveforms before and after synthesis

### Example 2:

Verilog code:
```
module bad_mux (input i0 , input i1 , input sel , output reg y);
always @ (sel)
begin
	if(sel)
		y <= i1;
	else 
		y <= i0;
end
endmodule
```
Simulation:
```
iverilog bad_mux.v tb_bad_mux.v
./a.out
gtkwave tb_bad_mux.vcd
```

![image](https://github.com/user-attachments/assets/f73206b8-c31d-4fbf-a933-f24fe52d94f1)

Netlist:
```
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib  
read_verilog bad_mux.v
synth -top bad_mux
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib 
show
write_verilog -noattr bad_mux_net.v
```

![image](https://github.com/user-attachments/assets/68e4e734-4a74-48ec-9b2a-aec30f8bea10)
![image](https://github.com/user-attachments/assets/572c31dd-25b1-4b5a-a022-31916008e713)
![image](https://github.com/user-attachments/assets/d9838a7f-1db9-4b7c-bf50-0f0726594afb)

GLS:
```
iverilog ../my_lib/verilog_model/primitives.v ../my_lib/verilog_model/sky130_fd_sc_hd.v bad_mux_net.v tb_bad_mux.v
./a.out
gtkwave tb_bad_mux.vcd
```
![image](https://github.com/user-attachments/assets/5d87cd32-608a-453d-87ef-b3a7032aefd6)

In this case there is a synthesis and simulation mismatch. While performing synthesis yosys has corrected the sensitivity list error.

## Labs on Synthesis-Simulation mismatch for blocking statements

Verilog code:
```
module blocking_caveat (input a , input b , input  c, output reg d); 
reg x;
always @ (*)
begin
d = x & c;
x = a | b;
end
endmodule
```
Simulation:
```
iverilog blocking_caveat.v tb_blocking_caveat.v
./a.out
gtkwave tb_blocking_caveat.vcd
```
![image](https://github.com/user-attachments/assets/895af03e-ac83-4199-8bb3-6bfd1b852ae8)

Netlist:
```
yosys
read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib  
read_verilog blocking_caveat.v
synth -top blocking_caveat
abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib 
show
write_verilog -noattr blocking_caveat_net.v
```
![image](https://github.com/user-attachments/assets/d9ee6a40-b01b-42b5-88e1-1007d7958c01)
![image](https://github.com/user-attachments/assets/448bea87-de96-4d4f-a3d3-11b4d9844f7f)
![image](https://github.com/user-attachments/assets/939222e6-81fc-47cc-ae39-154445e5e5ad)

GLS:
```
iverilog ../my_lib/verilog_model/primitives.v ../my_lib/verilog_model/sky130_fd_sc_hd.v blocking_caveat_net.v tb_blocking_caveat.v
./a.out
gtkwave tb_blocking_caveat.vcd
```

![image](https://github.com/user-attachments/assets/2c68bd93-3c6c-4707-a7f1-3edeb93bc182)

In this case there is a synthesis and simulation mismatch. While performing synthesis yosys has corrected the latch error.



</details>

<details>
  <summary>Lab 11</summary>

  ## Synthesizing RISC-V and comparing output with functional simulation.

  Copy the `src` folder from your `BabySoC` folder to your `sky130RTLDesignAndSynthesisWorkshop` folder in your VLSI folder from previous lab.

Now go the following Directory:

```
cd /home/anshu/VLSI/sky130RTLDesignAndSynthesisWorkshop/src/module
```

## Synthesis:

```
yosys

read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

read_verilog clk_gate.v

read_verilog rvmyth.v

synth -top rvmyth

abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

write_verilog -noattr rvmyth_net.v

!gedit rvmyth_net.v

exit
```
  
![image](https://github.com/user-attachments/assets/123a9572-bc14-46d5-bbf4-7ab3d37492dd)

![image](https://github.com/user-attachments/assets/f33b7649-15e4-4922-9dd9-13067a01ef13)
  
Now to observe the output waveform of synthesised RISC-V

```
iverilog ../../my_lib/verilog_model/primitives.v ../../my_lib/verilog_model/sky130_fd_sc_hd.v rvmyth.v testbench.v vsdbabysoc.v avsddac.v avsdpll.v clk_gate.v

./a.out

gtkwave dump.vcd
```
![image](https://github.com/user-attachments/assets/11e30120-f2d3-4d61-b790-23d4ccb5c2df)
![image](https://github.com/user-attachments/assets/6ac9f822-7172-4e79-adb9-428e53039bee)

## RTL Simulations

```
cd BabySoC

iverilog -o ./pre_synth_sim.out -DPRE_SYNTH_SIM src/module/testbench.v -I src/include -I src/module/

./pre_synth_sim.out

gtkwave pre_synth_sim.vcd
```

![Screenshot from 2024-10-24 02-47-46](https://github.com/user-attachments/assets/3047f5ac-db8f-48f1-9f16-716102cd51a5)

![Screenshot from 2024-10-24 02-52-45](https://github.com/user-attachments/assets/00bb913e-dcf9-4f81-9114-7602eccb6d48)

It can be observed that the waveforms before (pre_synth_sim) and after (post_synth_sim) Yosys synthesis are the same.

</details>

<details>
  <summary>Lab 12</summary>
	
  # Post Synthesis Static Timing Analysis using OpenSTA

  Below is the contents of `VSDBabySoc/src/sdc/vsdbabysoc_synthesis.sdc`
  ```
  set PERIOD 10.8

set_units -time ns
create_clock [get_pins {pll/CLK}] -name clk -period $PERIOD
set_clock_uncertainty -setup  [expr $PERIOD * 0.05] [get_clocks clk]
set_clock_transition [expr $PERIOD * 0.05] [get_clocks clk]
set_clock_uncertainty -hold [expr $PERIOD * 0.08] [get_clocks clk]
set_input_transition [expr $PERIOD * 0.08] [get_ports ENb_CP]
set_input_transition [expr $PERIOD * 0.08] [get_ports ENb_VCO]
set_input_transition [expr $PERIOD * 0.08] [get_ports REF]
set_input_transition [expr $PERIOD * 0.08] [get_ports VCO_IN]
set_input_transition [expr $PERIOD * 0.08] [get_ports VREFH]
```

Run the following commands:
```
cd VSDBabySoc/src
sta
read_liberty -min ./lib/sky130_fd_sc_hd__tt_025C_1v80.lib
read_liberty -min ./lib/avsdpll.lib
read_liberty -min ./lib/avsddac.lib
read_liberty -max ./lib/sky130_fd_sc_hd__tt_025C_1v80.lib
read_liberty -max ./lib/avsdpll.lib
read_liberty -max ./lib/avsddac.lib
read_verilog ../output/synth/vsdbabysoc.synth.v
link_design vsdbabysoc
read_sdc ./sdc/vsdbabysoc_synthesis.sdc
report_checks -path_delay min_max -format full_clock_expanded -digits 4

```
![WhatsApp Image 2024-10-28 at 21 06 02_519180c2-fotor-2024102823953](https://github.com/user-attachments/assets/6dc5e997-1c41-4bea-83d4-4eae6f13bf89)
![WhatsApp Image 2024-10-28 at 21 06 03_9c73653d](https://github.com/user-attachments/assets/abd78c33-d988-47fc-974b-f2dc9e33541c)
![WhatsApp Image 2024-10-28 at 21 06 03_774b7f99](https://github.com/user-attachments/assets/aa863119-d97e-4665-8bf4-258e53a68da0)

  
</details>

<details>
  <summary>Lab 13</summary>
	
  ## Post Synthesis Static Timing Analysis using OpenSTA for all the sky130 lib files

```
set PERIOD 10.8
set_units -time ns
create_clock [get_pins {pll/CLK}] -name clk -period $PERIOD
set_clock_uncertainty -setup  [expr $PERIOD * 0.05] [get_clocks clk]
set_clock_transition [expr $PERIOD * 0.05] [get_clocks clk]
set_clock_uncertainty -hold [expr $PERIOD * 0.08] [get_clocks clk]
set_input_transition [expr $PERIOD * 0.08] [get_ports ENb_CP]
set_input_transition [expr $PERIOD * 0.08] [get_ports ENb_VCO]
set_input_transition [expr $PERIOD * 0.08] [get_ports REF]
set_input_transition [expr $PERIOD * 0.08] [get_ports VCO_IN]
set_input_transition [expr $PERIOD * 0.08] [get_ports VREFH]
```
![Screenshot 2024-11-04 235539](https://github.com/user-attachments/assets/e5a3887c-0ab8-4831-9a2d-d5d76722453d)

Store all the lib files in a folder named `timing_libs` and place it in the `VSDBabySoC/src` directory.

Next, create a sta_pvt.tcl file and copy the below content in that file using gedit.

```
set list_of_lib_files(1) "sky130_fd_sc_hd__ff_100C_1v65.lib"
set list_of_lib_files(2) "sky130_fd_sc_hd__ff_100C_1v95.lib"
set list_of_lib_files(3) "sky130_fd_sc_hd__ff_n40C_1v56.lib"
set list_of_lib_files(4) "sky130_fd_sc_hd__ff_n40C_1v65.lib"
set list_of_lib_files(5) "sky130_fd_sc_hd__ff_n40C_1v76.lib"
set list_of_lib_files(6) "sky130_fd_sc_hd__ff_n40C_1v95.lib"
set list_of_lib_files(7) "sky130_fd_sc_hd__ff_n40C_1v95_ccsnoise.lib.part1"
set list_of_lib_files(8) "sky130_fd_sc_hd__ff_n40C_1v95_ccsnoise.lib.part2"
set list_of_lib_files(9) "sky130_fd_sc_hd__ff_n40C_1v95_ccsnoise.lib.part3"
set list_of_lib_files(10) "sky130_fd_sc_hd__ss_100C_1v40.lib"
set list_of_lib_files(11) "sky130_fd_sc_hd__ss_100C_1v60.lib"
set list_of_lib_files(12) "sky130_fd_sc_hd__ss_n40C_1v28.lib"
set list_of_lib_files(13) "sky130_fd_sc_hd__ss_n40C_1v35.lib"
set list_of_lib_files(14) "sky130_fd_sc_hd__ss_n40C_1v40.lib"
set list_of_lib_files(15) "sky130_fd_sc_hd__ss_n40C_1v44.lib"
set list_of_lib_files(16) "sky130_fd_sc_hd__ss_n40C_1v60.lib"
set list_of_lib_files(17) "sky130_fd_sc_hd__ss_n40C_1v60_ccsnoise.lib.part1"
set list_of_lib_files(18) "sky130_fd_sc_hd__ss_n40C_1v60_ccsnoise.lib.part2"
set list_of_lib_files(19) "sky130_fd_sc_hd__ss_n40C_1v60_ccsnoise.lib.part3"
set list_of_lib_files(20) "sky130_fd_sc_hd__ss_n40C_1v76.lib"
set list_of_lib_files(21) "sky130_fd_sc_hd__tt_025C_1v80.lib"
set list_of_lib_files(22) "sky130_fd_sc_hd__tt_100C_1v80.lib"

for {set i 1} {$i <= [array size list_of_lib_files]} {incr i} {
read_liberty ./timing_libs/$list_of_lib_files($i)
read_verilog ../output/synth/vsdbabysoc.synth.v
link_design vsdbabysoc
read_sdc ./sdc/vsdbabysoc_synthesis.sdc
check_setup -verbose
report_checks -path_delay min_max -fields {nets cap slew input_pins fanout} -digits {4} > ./sta_output/min_max_$list_of_lib_files($i).txt

}

```

Create a folder named `sta_output` in VSDBabySoC/src. Then run the following commands:
```
cd VSDBabySoC/src
sta
source sta_pvt.tcl
````
![Screenshot 2024-11-05 011736](https://github.com/user-attachments/assets/bf5b56bd-4cf8-43c0-9c5c-1a80b1f34bbe)
![image](https://github.com/user-attachments/assets/9271043e-d881-448d-a3ac-6e0123966f82)
![image](https://github.com/user-attachments/assets/a89d5a4b-84b2-4922-9701-fd2fc8728b57)

![image](https://github.com/user-attachments/assets/c37b09d5-3c8d-452d-836a-f0382052c89a)






  
</details>

<details>
	<summary>Lab 14</summary>

# Advanced Physical Design using Openlane

## Day 1 - Inception of open-source EDA, OpenLANE and Sky130 PDK

### Package
The package in an embedded board serves as the protective enclosure for the actual silicon chip, providing structural support and shielding it from physical damage. The package also routes signals through connections, commonly using wire bonding to link the internal chip to external pins or contacts, enabling integration with the circuit board.

![image](https://github.com/user-attachments/assets/ff705527-2cae-4ada-960a-62f658889fac)


### Chip
A chip, also known as an integrated circuit (IC), is a miniaturized assembly of electronic circuits on a silicon substrate. It combines various components like processors, memory blocks, and I/O controllers to perform complex functions required in modern electronics, catering to applications ranging from simple processing tasks to high-performance computing.
![image](https://github.com/user-attachments/assets/ccaeed9f-cdc0-474f-9423-4d0b090c3a8e)

### Pads
Pads are small metal regions located on either the chip or the package, designed as connection points for wiring or bonding. They enable the interface between the IC’s internal circuits and the outside world, facilitating power, ground, and data signal transfers across the system.

### Core
The core is the main functional area within a chip, where critical processing takes place. It contains the primary logic circuitry and computational units, typically optimized to achieve specific goals such as minimizing power usage or maximizing processing speed and efficiency.

### Die
A die is an individual chip cut from a larger silicon wafer, containing the integrated circuits before being encased in a package. It houses all of the necessary active elements and structures that allow the chip to function according to its design specifications.
![384578427-cfa2c482-59c5-4ad5-b74c-a027bfdf16b8](https://github.com/user-attachments/assets/49ff0164-ffec-4c0a-941e-7ee613b748d2)
### IPs (Intellectual Properties)
IPs, or Intellectual Properties, are reusable, pre-configured blocks of circuitry within a chip design, such as interfaces for USB, memory, or communication protocols. Licensing and reusing IPs help streamline the design process, allowing engineers to incorporate tested functionalities quickly without needing to create these elements from scratch.
![image](https://github.com/user-attachments/assets/74c20964-0174-48ba-8bcb-d2e0b49106c8)

### Software to Hardware Flow

To execute an application on hardware, a series of steps occur to prepare the code for the hardware's understanding. Initially, the application passes through a layer called system software, which converts the program into binary format—the language that hardware comprehends. The main components involved in this process are the Operating System (OS), Compiler, and Assembler.

First, the OS organizes the application’s functions, typically written in high-level languages like C, C++, Java, or Python, and directs them to an appropriate compiler. The compiler then translates these high-level functions into low-level instructions specifically designed to align with the underlying hardware architecture.

Following this, an assembler steps in to convert these architecture-specific instructions into binary machine code. This binary code is finally sent to the hardware, which executes the instructions and performs the tasks defined in the application.

![image](https://github.com/user-attachments/assets/4a98150e-2feb-4159-ab4e-7ed021e6ff66)

For example, consider a app running on a RISC-V core. Here, the OS might generate a small function in C, which is then passed to a compiler. The compiler outputs RISC-V-specific instructions, tailored to the architecture. These instructions are subsequently processed by the assembler, which converts them into binary code. This binary code then flows into the chip layout, where the hardware executes the desired functionality.

![image](https://github.com/user-attachments/assets/c662b794-4805-4f93-8b76-1e441a564425)

The compiler generates architecture-specific instructions, while the assembler produces the corresponding binary patterns. To execute these instructions on hardware, an RTL (written in a Hardware Description Language) is used to interpret and implement the instructions. This RTL design is then synthesized into a netlist, represented as interconnected logic gates. Finally, the netlist undergoes physical design implementation to be fabricated onto the chip.

![image](https://github.com/user-attachments/assets/c06eeb7d-00ec-4ea1-8c7a-937cd1e61869)

### Components of ASIC Design


For open-source ASIC design implemantation, we require the following enablers to be readily available as open-source versions. They are

- RTL Designs
- EDA Tools
- PDK Data

### Simplified RTL to GDS flow
![image](https://github.com/user-attachments/assets/9819c522-6e88-470a-afe8-f2fa04276b39)
**RTL Design:** This stage involves describing the intended behavior of the circuit using Hardware Description Languages (HDLs) like Verilog or VHDL. RTL (Register Transfer Level) code defines the logic, data paths, and signal flow of the circuit.

**RTL Synthesis:** In synthesis, the RTL code is translated into a gate-level netlist, which is a network of standard cells like AND gates, flip-flops, and multiplexers. The synthesis tool maps the design to these cells, optimizing for area, power, and timing requirements.

**Floor and Power Planning:** This step partitions the chip’s area, places key components, and establishes a power grid and I/O layout. The layout is organized to optimize signal flow and power distribution, balancing area usage while minimizing power consumption and enhancing signal integrity through strategic placement of I/O pads and power cells.

**Placement:** Here, the physical locations of the standard cells are assigned. The placement tool arranges cells to minimize wire length, reduce signal delays, and meet design constraints, balancing chip performance and efficient area use.

**Clock Tree Synthesis (CTS):** Clock Tree Synthesis builds an optimized network to distribute the clock signal across the design. CTS ensures that all flip-flops and registers receive the clock signal evenly, reducing clock skew and enhancing timing consistency across the chip.

**Routing:** After placement, routing establishes connections between components based on their locations. Routing tools optimize wire paths to maintain signal integrity, reduce congestion, and ensure adherence to design rules.

**Sign-off:** This final verification stage ensures that the design meets all functionality, performance, power, and reliability requirements. Timing analysis checks for setup and hold time compliance, power analysis confirms power limits are respected, and physical verification validates that the layout adheres to manufacturing specifications. This step confirms that the design is fabrication-ready.

**GDSII File Generation:** The finalized design is stored in a GDSII file, which includes all layout details for chip fabrication. This file acts as the blueprint used by manufacturers to create the photomasks needed for production, effectively transitioning the design into the physical chip manufacturing stage. 

### OpenLane ASIC Flow
![image](https://github.com/user-attachments/assets/050fb928-3fde-45d1-870c-a2041a80ea94)


**RTL Synthesis, Technology Mapping, and Formal Verification:**  
- **Tools:** Yosys (for RTL synthesis), ABC (for technology mapping and formal verification)

**Static Timing Analysis (STA):**  
- **Tools:** OpenSTA (for timing analysis)

**Floor Planning:**  
- **Tools:** init_fp (initial floorplanning), ioPlacer (I/O placement), pdn (power network planning), tapcell (tap cell insertion)

**Placement:**  
- **Tools:** RePLace (global placement), Resizer (optional cell resizing), OpenDP (detailed placement), OpenPhySyn (previously used for placement)

**Clock Tree Synthesis (CTS):**  
- **Tools:** TritonCTS (for clock tree synthesis)

**Fill Insertion:**  
- **Tools:** OpenDP (for filler placement)

**Routing:**  
- **Tools:** FastRoute (global routing), TritonRoute (detailed routing); previously, CU-GR was used for global routing and DR-CU for detailed routing.

**SPEF Extraction (Standard Parasitic Exchange Format):**  
- **Tools:** OpenRCX (for SPEF extraction), with SPEF-Extractor used previously

**GDSII Streaming Out:**  
- **Tools:** Magic, KLayout (for viewing, editing, and generating GDSII files)

**Design Rule Checking (DRC):**  
- **Tools:** Magic, KLayout (for DRC checks)

**Layout vs. Schematic (LVS) Check:**  
- **Tools:** Netgen (for LVS checks)

**Antenna Checks:**  
- **Tools:** Magic (for checking antenna effects)

### OpenLANE Directory structure
```
├── OOpenLane             -> directory where the tool can be invoked (run docker first)
│   ├── designs          -> All designs must be extracted from this folder
│   │   │   ├── picorv32a -> Design used as case study for this workshop
│   |   |   ├── ...
|   |   ├── ...
├── pdks                 -> contains pdk related files 
│   ├── skywater-pdk     -> all Skywater 130nm PDKs
│   ├── open-pdks        -> contains scripts that makes the commerical PDK (which is normally just compatible to commercial tools) to also be compatible with the open-source EDA tool
│   ├── sky130A          -> pdk variant made especially compatible for open-source tools
│   │   │  ├── libs.ref  -> files specific to node process (timing lib, cell lef, tech lef) for example is `sky130_fd_sc_hd` (Sky130nm Foundry Standard Cell High Density)  
│   │   │  ├── libs.tech -> files specific for the tool (klayout,netgen,magic...) 
```
### Synthesis in Openlane

Run the following in VSD Virtual Box:
```
cd Desktop/work/tools/openlane_working_dir/openlane
docker
./flow.tcl -interactive
package require openlane 0.9
prep -design picorv32a
run_synthesis
```


![image](https://github.com/user-attachments/assets/7e5c684c-612c-476f-89c7-adc9675cc269)

To view the netlist, use the following commands:
```
cd designs/picorv32a/runs/13-11_08-57/results/synthesis
gedit picorv32a.synthesis.v
```
![image](https://github.com/user-attachments/assets/5c189b5d-1bdf-461a-b877-c7fa3be4e6b1)

For yosys report
```
cd ../..
cd reports/synthesis
gedit 1-yosys_4.stat.rpt
```
![image](https://github.com/user-attachments/assets/4bf6b79c-ea1d-42ca-8c02-5d12b3fcd136)

Report:
```
28. Printing statistics.

=== picorv32a ===

   Number of wires:              14596
   Number of wire bits:          14978
   Number of public wires:        1565
   Number of public wire bits:    1947
   Number of memories:               0
   Number of memory bits:            0
   Number of processes:              0
   Number of cells:              14876
     sky130_fd_sc_hd__a2111o_2       1
     sky130_fd_sc_hd__a211o_2       35
     sky130_fd_sc_hd__a211oi_2      60
     sky130_fd_sc_hd__a21bo_2      149
     sky130_fd_sc_hd__a21boi_2       8
     sky130_fd_sc_hd__a21o_2        57
     sky130_fd_sc_hd__a21oi_2      244
     sky130_fd_sc_hd__a221o_2       86
     sky130_fd_sc_hd__a22o_2      1013
     sky130_fd_sc_hd__a2bb2o_2    1748
     sky130_fd_sc_hd__a2bb2oi_2     81
     sky130_fd_sc_hd__a311o_2        2
     sky130_fd_sc_hd__a31o_2        49
     sky130_fd_sc_hd__a31oi_2        7
     sky130_fd_sc_hd__a32o_2        46
     sky130_fd_sc_hd__a41o_2         1
     sky130_fd_sc_hd__and2_2       157
     sky130_fd_sc_hd__and3_2        58
     sky130_fd_sc_hd__and4_2       345
     sky130_fd_sc_hd__and4b_2        1
     sky130_fd_sc_hd__buf_1       1656
     sky130_fd_sc_hd__buf_2          8
     sky130_fd_sc_hd__conb_1        42
     sky130_fd_sc_hd__dfxtp_2     1613
     sky130_fd_sc_hd__inv_2       1615
     sky130_fd_sc_hd__mux2_1      1224
     sky130_fd_sc_hd__mux2_2         2
     sky130_fd_sc_hd__mux4_1       221
     sky130_fd_sc_hd__nand2_2       78
     sky130_fd_sc_hd__nor2_2       524
     sky130_fd_sc_hd__nor2b_2        1
     sky130_fd_sc_hd__nor3_2        42
     sky130_fd_sc_hd__nor4_2         1
     sky130_fd_sc_hd__o2111a_2       2
     sky130_fd_sc_hd__o211a_2       69
     sky130_fd_sc_hd__o211ai_2       6
     sky130_fd_sc_hd__o21a_2        54
     sky130_fd_sc_hd__o21ai_2      141
     sky130_fd_sc_hd__o21ba_2      209
     sky130_fd_sc_hd__o21bai_2       1
     sky130_fd_sc_hd__o221a_2      204
     sky130_fd_sc_hd__o221ai_2       7
     sky130_fd_sc_hd__o22a_2      1312
     sky130_fd_sc_hd__o22ai_2       59
     sky130_fd_sc_hd__o2bb2a_2     119
     sky130_fd_sc_hd__o2bb2ai_2     92
     sky130_fd_sc_hd__o311a_2        8
     sky130_fd_sc_hd__o31a_2        19
     sky130_fd_sc_hd__o31ai_2        1
     sky130_fd_sc_hd__o32a_2       109
     sky130_fd_sc_hd__o41a_2         2
     sky130_fd_sc_hd__or2_2       1088
     sky130_fd_sc_hd__or2b_2        25
     sky130_fd_sc_hd__or3_2         68
     sky130_fd_sc_hd__or3b_2         5
     sky130_fd_sc_hd__or4_2         93
     sky130_fd_sc_hd__or4b_2         6
     sky130_fd_sc_hd__or4bb_2        2

   Chip area for module '\picorv32a': 147712.918400
```

```
Flop ratio = Number of D Flip flops = 1613  = 0.1084
             ______________________   _____
             Total Number of cells    14876
```

## Day 2: Good floorplan vs bad floorplan and introduction to library cells

**Utilization Factor and Aspect Ratio**: In IC floor planning, utilization factor and aspect ratio are key parameters. The utilization factor is the ratio of the area occupied by the netlist to the total core area. While a perfect utilization of 1 (100%) is ideal, practical designs target a factor of 0.5 to 0.6 to allow space for buffer zones, routing channels, and future adjustments. The aspect ratio, defined as height divided by width, indicates the chip’s shape; an aspect ratio of 1 denotes a square, while other values result in a rectangular layout. The aspect ratio is chosen based on functional, packaging, and manufacturing needs.

```
Utilisation Factor =  Area occupied by netlist
                     __________________________
                         Total area of core
                         

Aspect Ratio =  Height
               ________
                Width
```

**Pre-placed cells :** Pre-placed cells are essential functional blocks, such as memory, custom processors, and analog circuits, positioned manually in fixed locations. These blocks are crucial for the chip’s performance and remain fixed during placement and routing to preserve their functionality and layout integrity.

**Decoupling Capacitors :** Decoupling capacitors are placed near logic circuits to stabilize power supply voltages during transient events. Acting as local energy reserves, they help reduce voltage fluctuations, crosstalk, and electromagnetic interference (EMI), ensuring reliable power delivery to sensitive circuits.

**Power Planning:** A robust power planning strategy includes creating a power and ground mesh to distribute VDD and VSS evenly across the chip. This setup ensures stable power delivery, minimizes voltage drops, and improves overall efficiency. Multiple power and ground points reduce the risk of instability and voltage drop issues, supporting the design’s power needs effectively.

**Pin Placement:** Pin placement (I/O planning) is crucial for functionality and reliability. Strategic pin assignment minimizes signal degradation, preserves data integrity, and helps manage heat dissipation. Proper positioning of power and ground pins supports thermal management and enhances signal strength, contributing to overall system stability and manufacturability.

## Floorplaning using OpenLANE

Run the following commands
```
cd Desktop/work/tools/openlane_working_dir/openlane
docker
```
```
./flow.tcl -interactive
package require openlane 0.9
prep -design picorv32a
run_synthesis
run_floorplan
```

![image](https://github.com/user-attachments/assets/91c7c185-3408-471e-a8fe-e9e3198b4971)

Run the following in a new terminal:
```
cd Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/runs/13-11_13-28/results/floorplan
gedit picorv32a.floorplan.def
```
![image](https://github.com/user-attachments/assets/94e952f3-a7fb-486e-9165-22257fa36512)

According to floorplan definition:

1000 Unit Distance = 1 Micron

Die width in unit distance = 660685−0 = 660685

Die height in unit distance = 671405−0 = 671405

Distance in microns = Value in Unit Distance/1000

​Die width in microns = 660685/1000 = 660.685 Microns

Die height in microns = 671405/1000 = 671.405 Microns

Area of die in microns = 660.685 × 671.405 = 443587.212425 Square Microns

To view the floorplan in magic. Open a new terminal and run the below commands

```
cd Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/runs/13-11_13-28/results/floorplan/
magic -T /home/vsduser/Desktop/work/tools/openlane_working_dir/pdks/sky130A/libs.tech/magic/sky130A.tech lef read ../../tmp/merged.lef def read picorv32a.floorplan.def &
```
![image](https://github.com/user-attachments/assets/e60eeaf7-1fc6-48b2-98aa-7cf2d054a1a1)
Decap and Tap Cells:
![image](https://github.com/user-attachments/assets/eadc6210-c13d-4f6a-b06b-e6d8eba75d75)
Unplaced standard cells at origin:
![image](https://github.com/user-attachments/assets/05e2bf70-eb91-4cec-b7b0-37c1e308fb1c)

 To run placement
```
run_placement
```
![image](https://github.com/user-attachments/assets/cd8e6119-6396-4980-bad0-73ead3285f67)

To view the placement:
```
cd Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/runs/13-11_15-17/results/placement/
magic -T /home/vsduser/Desktop/work/tools/openlane_working_dir/pdks/sky130A/libs.tech/magic/sky130A.tech lef read ../../tmp/merged.lef def read picorv32a.placement.def &
```
![image](https://github.com/user-attachments/assets/476edae9-3f9e-4e5d-8d23-d7b69f4f5d8f)
![image](https://github.com/user-attachments/assets/99bd40e2-58de-4ba8-98ef-543710fbe387)

### Cell design and Characterization Flow
In the industry, a typical standard cell characterization flow generally includes these steps:

1. Import the models and technology files.
2. Load the extracted SPICE netlist.
3. Identify the cell behavior.
4. Read in the subcircuits.
5. Connect power sources.
6. Apply stimulus to the characterization setup.
7. Specify the necessary output capacitance loads.
8. Provide essential simulation commands.

### Timing parameters

| Timing Definition       | Value     |
|-------------------------|-----------|
| slew_low_rise_thr       | 20% value |
| slew_high_rise_thr      | 80% value |
| slew_low_fall_thr       | 20% value |
| slew_high_fall_thr      | 80% value |
| in_rise_thr             | 50% value |
| in_fall_thr             | 50% value |
| out_rise_thr            | 50% value |
| out_fall_thr            | 50% value |

### Propagation Delay
It refers to the time it takes for a change in an input signal to reach 50% of its final value to produce a corresponding change in the output signal to reach 50% of its final value of a digital circuit.

```
rise delay =  time(out_fall_thr) - time(in_rise_thr)
```

### Transistion time

The time it takes the signal to move between states is the transition time , where the time is measured between 10% and 90% or 20% to 80% of the signal levels.
```
Fall transition time: time(slew_high_fall_thr) - time(slew_low_fall_thr)
Rise transition time: time(slew_high_rise_thr) - time(slew_low_rise_thr)
```

## Day 3: Design library cell using Magic Layout and ngspice characterization

### CMOS inverter ngspice simulations

1. **Netlist Creation**: Define the connections for the CMOS inverter circuit by creating a netlist. Label each node, such as input, output, ground, and supply nodes, to facilitate easy identification during SPICE simulation.

2. **Device Sizing**: Specify the width-to-length (W/L) ratios for the PMOS and NMOS transistors. To achieve balanced drive strength, set the PMOS width typically 2x to 3x larger than the NMOS width.

3. **Voltage Levels**: Assign gate and supply voltage values, often using multiples of the transistor length to ensure correct operation.

4. **Node Naming**: Label each connection point with meaningful names like VDD, GND, IN, and OUT. This clear node naming helps SPICE identify components and run an effective simulation of the circuit.
![image](https://github.com/user-attachments/assets/67e3e783-c0a5-4cfa-9ad2-c390c3809f0e)

**Syntax for PMOS and NMOS desription**
`[component name] [drain] [gate] [source] [substrate] [transistor type] W=[width] L=[length]`

 **Simulation commands**
 ```
.op --- is the start of SPICE simulation operation where Vin sweeps from 0 to 2.5 with 0.5 steps
tsmc_025um_model.mod  ----  model file which contains the technological parameters for the 0.25um NMOS and PMOS 
```
Commands to simulate in SPICE:
```
source [filename].cir
run
setplot 
dc1 
plot out vs in
```
![image](https://github.com/user-attachments/assets/aa3ef802-3f00-4fab-b8c4-8efbb0e622aa)

The switching threshold Vm is like a critical voltage level for a component called a CMOS inverter. It's the point at which this inverter switches between sending out a "0" or a "1" in a computer chip. This the point where both PMOS and NMOS is in saturation or kind of turned on, and leakage current is high. If PMOS is thicker than NMOS, the CMOS will have higher switching threshold (1.2V vs 1V) while threshold will be lower when NMOS becomes thicker.

At this point, both the transistors are in saturation region, means both are turned on and have high chances of current flowing directly from VDD to Ground called Leakage current.

To find the switching threshold:
```
Vin in 0 2.5
*** Simulation Command ***
.op
.dc Vin 0 2.5 0.05
```
![image](https://github.com/user-attachments/assets/325202f2-c3c1-42b1-9f24-0b033b2f3d77)
Transient analysis is used for finding propagation delay.

The simulation commands:
```
Vin in 0 0 pulse 0 2.5 0 10p 10p 1n 2n 
*** Simulation Command ***
.op
.tran 10p 4n
```
Result of SPICE simulation for transient analysis:
![image](https://github.com/user-attachments/assets/baeb5ae4-1612-42f1-8368-07f0b1ab45d4)

Now, clone the custom inverter
```
cd Desktop/work/tools/openlane_working_dir/openlane
git clone https://github.com/nickson-jose/vsdstdcelldesign.git
cd vsdstdcelldesign
cp /home/vsduser/Desktop/work/tools/openlane_working_dir/pdks/sky130A/libs.tech/magic/sky130A.tech .
ls
magic -T sky130A.tech sky130_inv.mag &
```
![image](https://github.com/user-attachments/assets/0e850d40-9f08-4b61-8697-d345e2117c8f)

### CMOS Fabrication Process Overview

The 16-mask CMOS layout fabrication process involves these key steps:

1. **Substrate Preparation**: Begins with preparing a silicon wafer as the base substrate for the circuit.

2. **N-Well Formation**: N-well regions are created by adding impurities, usually phosphorus, via ion implantation or diffusion.

3. **P-Well Formation**: P-well regions are similarly created using boron or other dopants.

4. **Gate Oxide Deposition**: A thin silicon dioxide layer is deposited to form the gate oxide, insulating the gate from the channel.

5. **Poly-Silicon Deposition**: Polysilicon is deposited over the gate oxide to serve as the gate electrode.

6. **Poly-Silicon Masking and Etching**: A photoresist mask outlines areas where polysilicon should remain, and etching removes unmasked portions.

7. **N-Well Masking and Implantation**: A mask defines N-well regions for preservation, and phosphorus impurities are implanted in exposed areas.

8. **P-Well Masking and Implantation**: Similarly, a mask defines P-well regions for preservation, and boron impurities are implanted.

9. **Source/Drain Implantation**: Using masks, dopants (e.g., arsenic for NMOS, boron for PMOS) are implanted to form source and drain regions.

10. **Gate Formation**: The gate electrode is shaped by etching the polysilicon layer using a photoresist mask.

11. **Source/Drain Masking and Etching**: A mask defines source and drain areas, and etching removes the oxide layer in these regions.

12. **Contact/Via Formation**: Holes or vias are etched through the oxide to expose regions like source/drain or polysilicon gates.

13. **Metal Deposition**: Metal, usually aluminum or copper, is deposited to form interconnections.

14. **Metal Masking and Etching**: A photoresist mask outlines the interconnects, and etching removes exposed metal, leaving the pattern.

15. **Passivation Layer Deposition**: A protective silicon dioxide or nitride layer is added to isolate and shield the metal interconnects.

16. **Final Testing and Packaging**: The fabricated wafer undergoes testing to ensure functionality, and working chips are separated, packaged, and readied for various electronic applications.

![image](https://github.com/user-attachments/assets/2d41ce0a-3873-48b8-a021-7a1f24daa9e9)

### Inverter layout:

Identify NMOS:
![image](https://github.com/user-attachments/assets/d8751316-4c43-40e0-a842-717b3cfadb01)
Identify PMOS:
![image](https://github.com/user-attachments/assets/964f7425-520d-4005-910b-15292c606bc2)
Output Y:
![image](https://github.com/user-attachments/assets/f6421cc0-a8ba-46bd-a517-dcf26ba770a4)
PMOS source connected to VDD:
![image](https://github.com/user-attachments/assets/96b55d78-41d0-4011-b2b3-a3355bd9076d)
NMOS source connected to VSS:
![image](https://github.com/user-attachments/assets/b06f48d6-cd29-479c-8264-db3be7778d5f)

Spice extraction of inverter in Magic. Run these in the tkcon window:
```
# Check current directory
pwd
extract all
ext2spice cthresh 0 rthresh 0
ext2spice
```
![image](https://github.com/user-attachments/assets/88c8f4a2-440d-41b6-8eb2-9e90baf8c8d0)
To view the spice file:
![image](https://github.com/user-attachments/assets/f56f0510-ac72-4ab0-8b37-e750063971d7)

![image](https://github.com/user-attachments/assets/07c68c55-8238-4a45-8e64-2bf3979cfd17)

contents of the spice file:
```
* SPICE3 file created from sky130_inv.ext - technology: sky130A

.option scale=10m

.subckt sky130_inv A Y VPWR VGND
X0 Y A VGND VGND sky130_fd_pr__nfet_01v8 ad=1.44n pd=0.152m as=1.37n ps=0.148m w=35 l=23
X1 Y A VPWR VPWR sky130_fd_pr__pfet_01v8 ad=1.44n pd=0.152m as=1.52n ps=0.156m w=37 l=23
C0 Y A 0.0754f
C1 VPWR A 0.0774f
C2 Y VPWR 0.117f
C3 Y VGND 0.279f
C4 A VGND 0.45f
C5 VPWR VGND 0.781f
.ends
```

Now modify the `sky130_inv.spice` file to find the transient response:

```
* SPICE3 file created from sky130_inv.ext - technology: sky130A

.option scale=0.01u
.include ./libs/pshort.lib
.include ./libs/nshort.lib

//.subckt sky130_inv A Y VPWR VGND
M1000 Y A VGND VGND nshort_model.0 w=35 l=23
+  ad=1.44n pd=0.152m as=1.37n ps=0.148m
M1001 Y A VPWR VPWR pshort_model.0 w=37 l=23
+  ad=1.44n pd=0.152m as=1.52n ps=0.156m

VDD VPWR 0 3.3V
VSS VGND 0 0V
Va A VGND PULSE(0V 3.3V 0 0.1ns 0.1ns 2ns 4ns)

C0 A VPWR 0.0774f
C1 VPWR Y 0.117f
C2 A Y 0.0754f
C3 Y VGND 2f
C4 A VGND 0.45f
C5 VPWR VGND 0.781f
//.ends

.tran 1n 20n
.control
run
.endc
.end
```
Now, simulate the spice netlist
```
ngspice sky130_inv.spice
```
![image](https://github.com/user-attachments/assets/3fde4b01-baf7-45ff-9e47-b147fd1cf97e)
To plot the waveform:
```
plot y vs time a
```
![image](https://github.com/user-attachments/assets/9f57455b-c12b-4f3a-b3a6-6ecb09422917)
Using this transient response, we will now characterize the cell's slew rate and propagation delay:

Rise Transition: Time taken for the output to rise from 20% to 80% of max value Fall Transition: Time taken for the output to fall from 80% to 20% of max value Cell Rise delay: difference in time(50% output rise) to time(50% input fall) Cell Fall delay: difference in time(50% output fall) to time(50% input rise)
```
Rise Transition : 2.24638 - 2.18242 =  0.06396 ns = 63.96 ps
Fall Transition : 4.0955 - 4.05536 =  0.0419 ns = 41.9 ps
Cell Rise Delay : 2.21144 - 2.15008 = 0.06136 ns = 61.36 ps
Cell Fall Delay : 4.07807 - 4.05 =0.02 ns = 20 ps
```
Magic Tool options and DRC Rules:

Now, go to home directory and run the below commands:
```
cd
wget http://opencircuitdesign.com/open_pdks/archive/drc_tests.tgz
tar xfz drc_tests.tgz
cd drc_tests
ls -al
gvim .magicrc
magic -d XR &
```
![image](https://github.com/user-attachments/assets/7ecaf9c9-5a84-4ed8-a69e-d7814c56aa1a)
load the poly file by load poly.mag on tkcon window.'
![image](https://github.com/user-attachments/assets/0cec04ff-5faa-4531-afbd-fea0f93ac60e)

We can see that Poly.9 is incorrect.

Add the below commands in the sky130A.tech
![image](https://github.com/user-attachments/assets/cec35a04-d6a9-45b7-80b0-e67ea6c0e167)
![image](https://github.com/user-attachments/assets/0dc3c5ef-dfc8-4158-8c94-e50e701911fd)
Run the commands in tkcon window:
```
tech load sky130A.tech
drc check
drc why
```
![image](https://github.com/user-attachments/assets/9627b5da-19f3-4c8d-8c10-6c1476fecdbd)

## Day 4: Pre-layout timing analysis and importance of good clock tree

Extract tracks.info file:
```
cd Desktop/work/tools/openlane_working_dir/openlane/vsdstdcelldesign
cd ../../pdks/sky130A/libs.tech/openlane/sky130_fd_sc_hd/
less tracks.info
```
![image](https://github.com/user-attachments/assets/df24416d-8ff9-4078-b235-711127760411)


</details>






