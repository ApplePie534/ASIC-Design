![Screenshot from 2024-11-26 16-45-01](https://github.com/user-attachments/assets/7580e15a-d47e-4ad7-b82e-e854f01378bc)# ASIC-Design

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

![385468075-ff705527-2cae-4ada-960a-62f658889fac](https://github.com/user-attachments/assets/6da432ce-0b33-4cc2-8ad2-d5487875032f)



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
Commands to set grid for tkcon window as tracks of locali layer use the following command:
```
grid 0.46um 0.34um 0.23um 0.17um
```
![image](https://github.com/user-attachments/assets/2b9c6117-a9ea-49c6-94c5-e223457bb810)
Save it by giving a custon name

Open it using:
```
magic -T sky130A.tech sky130_ansinv.mag &
```
![image](https://github.com/user-attachments/assets/45f6222d-0595-4aa2-9bde-88e67ca790e9)
Now, type the following command in tkcon window:
```
lef write
```
![image](https://github.com/user-attachments/assets/511bb080-d68b-40e2-bde8-2f0298779b7d)
Copy the newly generated lef and associated required lib files to 'picorv32a' design 'src' directory
```
# Copy lef file
cp sky130_ansinv.lef ~/Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/src/

# List and check whether it's copied
ls ~/Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/src/

# Copy lib files
cp libs/sky130_fd_sc_hd__* ~/Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/src/

# List and check whether it's copied
ls ~/Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/src/
```
![image](https://github.com/user-attachments/assets/52c6f88f-42e3-4efb-be41-2d53e5aed947)

Modify config.tcl:
```
# Design
set ::env(DESIGN_NAME) "picorv32a"

set ::env(VERILOG_FILES) "./designs/picorv32a/src/picorv32a.v"
set ::env(SDC_FILE) "./designs/picorv32a/src/picorv32a.sdc"

set ::env(CLOCK_PERIOD) "5.000"
set ::env(CLOCK_PORT) "clk"

set ::env(CLOCK_NET) $::env(CLOCK_PORT)

set ::env(LIB_SYNTH) "$::env(OPENLANE_ROOT)/designs/picorv32a/src/sky130_fd_sc_hd__typical.lib"
set ::env(LIB_FASTEST) "$::env(OPENLANE_ROOT)/designs/picorv32a/src/sky130_fd_sc_hd__fast.lib"
set ::env(LIB_SLOWEST) "$::env(OPENLANE_ROOT)/designs/picorv32a/src/sky130_fd_sc_hd__slow.lib"
set ::env(LIB_TYPICAL) "$::env(OPENLANE_ROOT)/designs/picorv32a/src/sky130_fd_sc_hd__typical.lib"

set ::env(EXTRA_LEFS) [glob $::env(OPENLANE_ROOT)/designs/$::env(DESIGN_NAME)/src/*.lef]

set filename $::env(OPENLANE_ROOT)/designs/$::env(DESIGN_NAME)/$::env(PDK)_$::env(STD_CELL_LIBRARY)_config.tcl
if { [file exists $filename] == 1 } {
  source $filename
}
```

Now, run openlane flow synthesis:
```
cd Desktop/work/tools/openlane_working_dir/openlane
docker
```
```
./flow.tcl -interactive
package require openlane 0.9
prep -design picorv32a
set lefs [glob $::env(DESIGN_DIR)/src/*.lef]
add_lefs -src $lefs
run_synthesis
```

![image](https://github.com/user-attachments/assets/855c2801-bb82-421a-bce9-f8c2b6d8875f)
![image](https://github.com/user-attachments/assets/3052a331-7ef2-47a4-9c93-d09f1cad160a)
![image](https://github.com/user-attachments/assets/e430b70e-93a4-4def-af21-030f68f0dacd)
![image](https://github.com/user-attachments/assets/1bdc7d03-b068-420b-98a4-5117f17e261a)

### Delay Tables

Delay plays a crucial role in cell timing, impacted by input transition and output load. Cells of the same type can have different delays depending on wire length due to resistance and capacitance variations. To manage this, "delay tables" are created, using 2D arrays with input slew and load capacitance for each buffer size as timing models. Algorithms compute buffer delays from these tables, interpolating where exact data isn’t available to estimate delays accurately, preserving signal integrity across varying load conditions.
![image](https://github.com/user-attachments/assets/4b6ceaba-4e7d-4372-9b0e-4f7609012683)

Fixing slack:
```
./flow.tcl -interactive
package require openlane 0.9
prep -design picorv32a -tag 14-11_14-01 -overwrite
set lefs [glob $::env(DESIGN_DIR)/src/*.lef]
add_lefs -src $lefs
echo $::env(SYNTH_STRATEGY)
set ::env(SYNTH_STRATEGY) "DELAY 3"
echo $::env(SYNTH_BUFFERING
echo $::env(SYNTH_SIZING)
set ::env(SYNTH_SIZING) 1
echo $::env(SYNTH_DRIVING_CELL)
run_synthesis
```
![image](https://github.com/user-attachments/assets/ad9152ce-1093-4f42-9e64-7db58251e062)
![image](https://github.com/user-attachments/assets/4f469547-7219-432d-aca2-da162d2fedb6)
![image](https://github.com/user-attachments/assets/4332139b-a92e-418e-87f7-e30aafa68f70)
![image](https://github.com/user-attachments/assets/52f28c3d-c04e-46af-8848-734292aceede)

```
run_floorplan
```
![image](https://github.com/user-attachments/assets/5467ab5d-c273-4deb-834a-6c8abc92af7f)

Since we are facing unexpected un-explainable error while using run_floorplan command, we can instead use the following set of commands available based on information from `Desktop/work/tools/openlane_working_dir/openlane/scripts/tcl_commands/floorplan.tcl` and also based on Floorplan Commands section in `Desktop/work/tools/openlane_working_dir/openlane/docs/source/OpenLANE_commands.md`
```
init_floorplan
place_io
tap_decap_or
```
Now, do placement
```
run_placement
```
![image](https://github.com/user-attachments/assets/12610a57-dd10-499e-9c0a-ce54814e779b)
Now, open a new terminal and run the below commands to load placement def in magic
```
cd Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/runs/14-11_14-01/results/placement/
magic -T /home/vsduser/Desktop/work/tools/openlane_working_dir/pdks/sky130A/libs.tech/magic/sky130A.tech lef read ../../tmp/merged.lef def read picorv32a.placement.def &
```
![image](https://github.com/user-attachments/assets/8cf5e6e9-f131-47cc-a80c-3798504c6a8d)
Custom inverter inserted in placement def
![image](https://github.com/user-attachments/assets/e594598f-f8d7-4a51-8752-6b9d30d587b2)
Now, select the cell and type expand in tkcon window to view internal layers of cells
![image](https://github.com/user-attachments/assets/dbbb9faf-68bc-4227-a83a-80276e054a38)

### Timing analysis with ideal clocks using openSTA 
Pre-layout STA will include effects of clock buffers and net-delay due to RC parasitics (wire delay will be derived from PDK library wire model).
![image](https://github.com/user-attachments/assets/3f94bc03-674d-4c67-960b-3eb1b600e8ef)

Since we are getting 0 WNS after improved timing run, we will be doing the timing analysis on initial run of synthesis which has lots of violations and no parameters added to improve timing.

Commands to invoke the OpenLANE flow include new lef and perform synthesis:
```
cd Desktop/work/tools/openlane_working_dir/openlane
docker
./flow.tcl -interactive
package require openlane 0.9
prep -design picorv32a
set lefs [glob $::env(DESIGN_DIR)/src/*.lef]
add_lefs -src $lefs
set ::env(SYNTH_SIZING) 1
run_synthesis
```

go to `Desktop/work/tools/openlane_working_dir/openlane` and create a file `pre_sta.conf`. The contents of the file are:
```
set_cmd_units -time ns -capacitance pF -current mA -voltage V -resistance kOhm -distance um
read_liberty -max /home/vsduser/Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/src/sky130_fd_sc_hd__slow.lib
read_liberty -min /home/vsduser/Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/src/sky130_fd_sc_hd__fast.lib
read_verilog /home/vsduser/Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/runs/14-11_14-01/results/synthesis/picorv32a.synthesis.v
link_design picorv32a
read_sdc /home/vsduser/Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/src/my_base.sdc
report_checks -path_delay min_max -fields {slew trans net cap input_pin}
report_tns
report_wns
```

Create `my_base.sdc` for STA analysis in `openlane/designs/picorv32a/src` directory and past the following content:
```
set ::env(CLOCK_PORT) clk
set ::env(CLOCK_PERIOD) 12.000
set ::env(SYNTH_DRIVING_CELL) sky130_fd_sc_hd__inv_8
set ::env(SYNTH_DRIVING_CELL_PIN) Y
set ::env(SYNTH_CAP_LOAD) 17.65
create_clock [get_ports $::env(CLOCK_PORT)]  -name $::env(CLOCK_PORT)  -period $::env(CLOCK_PERIOD)
set IO_PCT  0.2
set input_delay_value [expr $::env(CLOCK_PERIOD) * $IO_PCT]
set output_delay_value [expr $::env(CLOCK_PERIOD) * $IO_PCT]
puts "\[INFO\]: Setting output delay to: $output_delay_value"
puts "\[INFO\]: Setting input delay to: $input_delay_value"


set clk_indx [lsearch [all_inputs] [get_port $::env(CLOCK_PORT)]]
#set rst_indx [lsearch [all_inputs] [get_port resetn]]
set all_inputs_wo_clk [lreplace [all_inputs] $clk_indx $clk_indx]
#set all_inputs_wo_clk_rst [lreplace $all_inputs_wo_clk $rst_indx $rst_indx]
set all_inputs_wo_clk_rst $all_inputs_wo_clk


# correct resetn
set_input_delay $input_delay_value  -clock [get_clocks $::env(CLOCK_PORT)] $all_inputs_wo_clk_rst
#set_input_delay 0.0 -clock [get_clocks $::env(CLOCK_PORT)] {resetn}
set_output_delay $output_delay_value  -clock [get_clocks $::env(CLOCK_PORT)] [all_outputs]

# TODO set this as parameter
set_driving_cell -lib_cell $::env(SYNTH_DRIVING_CELL) -pin $::env(SYNTH_DRIVING_CELL_PIN) [all_inputs]
set cap_load [expr $::env(SYNTH_CAP_LOAD) / 1000.0]
puts "\[INFO\]: Setting load to: $cap_load"
set_load  $cap_load [all_outputs]
```
Commands to run STA:
```
cd Desktop/work/tools/openlane_working_dir/openlane
sta pre_sta.conf
```
![image](https://github.com/user-attachments/assets/581a99bb-19dd-49d6-ba41-575a00e7e8f5)
![image](https://github.com/user-attachments/assets/0eb6df2c-f910-4473-a82f-c3c0ec310540)

We now try to optimise synthesis.

Go to new terminal and run the follwoing commands:
```
cd Desktop/work/tools/openlane_working_dir/openlane
docker
./flow.tcl -interactive
prep -design picorv32a -tag 14-11_14-01 -overwrite
set lefs [glob $::env(DESIGN_DIR)/src/*.lef]
add_lefs -src $lefs
set ::env(SYNTH_SIZING) 1
set ::env(SYNTH_MAX_FANOUT) 4
echo $::env(SYNTH_DRIVING_CELL)
run_synthesis
```
![image](https://github.com/user-attachments/assets/394038fb-6f0b-47f3-b825-fb91942078a1)
Commands to run STA:
```
cd Desktop/work/tools/openlane_working_dir/openlane
sta pre_sta.conf
```
![image](https://github.com/user-attachments/assets/73480525-42dc-4de2-aede-89978ddaa5d9)
![image](https://github.com/user-attachments/assets/1a8b97fc-7a5b-4fd5-9a2c-e97e8df11c55)

Run the following commands to optimise timing:
```
report_net -connections _13111_
replace_cell _16171_ sky130_fd_sc_hd__nor3_2
report_checks -fields {net cap slew input_pins} -digits 4
```
![image](https://github.com/user-attachments/assets/2459eef4-a69e-4f3d-8653-ea75aeb003d3)
The tns has reduced to -402.45 from -403.54 and wns has reduced to -5.44 from -5.59

### Clock tree synthesis TritonCTS and signal integrity
Clock Tree Synthesis (CTS) techniques vary based on design needs:

- Balanced Tree CTS: Uses a balanced binary-like tree for equal path lengths, minimizing clock skew but with moderate power efficiency.

- H-tree CTS: Employs an "H"-shaped structure, good for large areas and power efficiency.
![image](https://github.com/user-attachments/assets/7805156c-54cc-40b0-918d-0632e861c641)



- Star CTS: Distributes the clock from a central point, minimizing skew but requiring more buffers near the source.

- Global-Local CTS: Combines star and tree topologies, with a global tree for clock domains and local trees within domains, balancing global and local timing.

- Mesh CTS: Uses a grid pattern ideal for structured designs, balancing simplicity and skew.

- Adaptive CTS: Dynamically adjusts based on timing and congestion, offering flexibility but with added complexity.

### Crosstalk
Crosstalk is interference from overlapping electromagnetic fields between adjacent circuits, causing unwanted signals. In VLSI, it can lead to data corruption, timing issues, and higher power consumption. Mitigation strategies include optimized layout and routing, shielding, and clock gating to reduce dynamic power and minimize crosstalk effects.
![image](https://github.com/user-attachments/assets/107c8386-a78b-4d77-b081-e07d598e073b)

### Clock Net Shielding

Clock net shielding prevents glitches by isolating the clock network, using shields connected to VDD or GND that don’t switch. It reduces interference by isolating clocks from other signals, often with dedicated routing layers and clock buffers. Additionally, clock domain isolation helps prevent cross-domain interference, avoiding metastability and maintaining synchronization.
![image](https://github.com/user-attachments/assets/96cb6c80-052f-4536-a341-d380a78f5371)

Run the following commands:
```
cd Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/runs/14-11_14-01/results/synthesis/
ls
cp picorv32a.synthesis.v picorv32a.synthesis_old.v
ls
```
```
write_verilog /home/vsduser/Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/runs/14-11_14-01/results/synthesis/picorv32a.synthesis.v
exit
```
Verify that the netlist is overwritten
![image](https://github.com/user-attachments/assets/28a9993e-a2f7-4618-923f-72c2bac2c81c)

Now, run the following commands:
```
cd Desktop/work/tools/openlane_working_dir/openlane
docker
./flow.tcl -interactive
prep -design picorv32a -tag 14-11_14-01 -overwrite
set lefs [glob $::env(DESIGN_DIR)/src/*.lef]
add_lefs -src $lefs
set ::env(SYNTH_STRATEGY) "DELAY 3"
set ::env(SYNTH_SIZING) 1
run_synthesis
init_floorplan
place_io
tap_decap_or
run_placement
run_cts
```
![image](https://github.com/user-attachments/assets/e1b0f0c5-4d94-4cad-bc38-1606ecf15ae1)
![image](https://github.com/user-attachments/assets/14a7887c-b003-41bd-a2ba-9ee53ff474bf)

**Setup timing analysis using real clocks**

A real clock in timing analysis accounts for practical factors like clock skew and clock jitter. Clock skew is the difference in arrival times of the clock signal at different parts of the circuit due to physical delays, which affects setup and hold timing margins. Clock jitter is the variability in the clock period caused by power, temperature, and noise fluctuations, leading to uncertainty in clock edge timing. Both factors are crucial for accurate timing analysis, ensuring the design performs reliably in real-world conditions.
![image](https://github.com/user-attachments/assets/1a36634a-1ac5-4107-88bd-a5f89473c961)
![image](https://github.com/user-attachments/assets/a3c47cb1-3e27-4b2a-a374-cc49b0dcdb6f)

Enter the following commands for Post-CTS OpenROAD timing analysis:
```
openroad
read_lef /openLANE_flow/designs/picorv32a/runs/14-11_14-01/tmp/merged.lef
read_def /openLANE_flow/designs/picorv32a/runs/14-11_14-01/results/cts/picorv32a.cts.def
write_db pico_cts.db
read_db pico_cts.db
read_verilog /openLANE_flow/designs/picorv32a/runs/14-11_14-01/results/synthesis/picorv32a.synthesis_cts.v
read_liberty $::env(LIB_SYNTH_COMPLETE)
link_design picorv32a
read_sdc /openLANE_flow/designs/picorv32a/src/my_base.sdc
set_propagated_clock [all_clocks]
report_checks -path_delay min_max -fields {slew trans net cap input_pins} -format full_clock_expanded -digits 4
exit
```
![image](https://github.com/user-attachments/assets/68792b12-1083-457a-924f-3a57f58ff3d9)

Now, enter the following commands for exploring post-CTS OpenROAD timing analysis by removing 'sky130_fd_sc_hd__clkbuf_1' cell from clock buffer list variable 'CTS_CLK_BUFFER_LIST':
```
echo $::env(CTS_CLK_BUFFER_LIST)
set ::env(CTS_CLK_BUFFER_LIST) [lreplace $::env(CTS_CLK_BUFFER_LIST) 0 0]
echo $::env(CTS_CLK_BUFFER_LIST)
echo $::env(CURRENT_DEF)
set ::env(CURRENT_DEF) /openLANE_flow/designs/picorv32a/runs/14-11_14-01/results/placement/picorv32a.placement.def
run_cts
echo $::env(CTS_CLK_BUFFER_LIST)
openroad
read_lef /openLANE_flow/designs/picorv32a/runs/14-11_14-01/tmp/merged.lef
read_def /openLANE_flow/designs/picorv32a/runs/14-11_14-01/results/cts/picorv32a.cts.def
write_db pico_cts1.db
read_db pico_cts.db
read_verilog /openLANE_flow/designs/picorv32a/runs/14-11_14-01/results/synthesis/picorv32a.synthesis_cts.v
read_liberty $::env(LIB_SYNTH_COMPLETE)
link_design picorv32a
read_sdc /openLANE_flow/designs/picorv32a/src/my_base.sdc
set_propagated_clock [all_clocks]
report_checks -path_delay min_max -fields {slew transd net cap input_pins} -format full_clock_expanded -digits 4
report_clock_skew -hold
report_clock_skew -setup
exit
echo $::env(CTS_CLK_BUFFER_LIST)
set ::env(CTS_CLK_BUFFER_LIST) [linsert $::env(CTS_CLK_BUFFER_LIST) 0 sky130_fd_sc_hd__clkbuf_1]
echo $::env(CTS_CLK_BUFFER_LIST)
```
![image](https://github.com/user-attachments/assets/1c362c8b-aab3-43f6-a884-ae73def66069)
![image](https://github.com/user-attachments/assets/9faad3dd-ccb7-4f34-9dfa-4d295da24103)

## Day 5 - Final steps for RTL2GDS using tritonRoute and openSTA

## Perform generation of Power Distribution Network (PDN) and explore the PDN layout.

Commands to perform all necessary stages up until now
```

cd Desktop/work/tools/openlane_working_dir/openlane
docker

./flow.tcl -interactive
package require openlane 0.9
prep -design picorv32a
set lefs [glob $::env(DESIGN_DIR)/src/*.lef]
add_lefs -src $lefs
set ::env(SYNTH_STRATEGY) "DELAY 3"
set ::env(SYNTH_SIZING) 1
run_synthesis
init_floorplan
place_io
tap_decap_or
run_placement
run_cts
gen_pdn
```
![image](https://github.com/user-attachments/assets/56333146-2054-49b0-aa49-605ea12411c3)

Commands to load PDN def in magic in another terminal
```
cd Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/runs/14-11_18-31/tmp/floorplan/
magic -T /home/vsduser/Desktop/work/tools/openlane_working_dir/pdks/sky130A/libs.tech/magic/sky130A.tech lef read ../../tmp/merged.lef def read 14-pdn.def &
```
![image](https://github.com/user-attachments/assets/3d362b73-1c40-464d-abb4-b1956cb2ddc6)
![image](https://github.com/user-attachments/assets/6e6b1bb3-3c3a-41f5-abbb-8d7e12c5ac5e)

## Perform detailed routing using TritonRoute and explore the routed layout.
Command to perform routing
```
echo $::env(CURRENT_DEF)
echo $::env(ROUTING_STRATEGY)
run_routing
```
![image](https://github.com/user-attachments/assets/e450ae06-56e7-4f44-bb83-6903f45a6674)
![image](https://github.com/user-attachments/assets/74af0b23-6849-4d2c-91fd-91faf81b832d)

Commands to load routed def in magic in another terminal
```
cd Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/runs/14-11_18-31/results/routing/
magic -T /home/vsduser/Desktop/work/tools/openlane_working_dir/pdks/sky130A/libs.tech/magic/sky130A.tech lef read ../../tmp/merged.lef def read picorv32a.def &
```
![image](https://github.com/user-attachments/assets/b14d1a09-ea3c-46c6-b2ee-fac12a622c4b)
![image](https://github.com/user-attachments/assets/ae3bc5b0-59ff-4235-9a42-a4e9dde814d0)
![image](https://github.com/user-attachments/assets/70276d4f-b5e5-4dd9-8ce3-a56df7395a9c)

Screenshot of fast route guide present in `openlane/designs/picorv32a/runs/14-11_18-31/tmp/routing` directory
![image](https://github.com/user-attachments/assets/4e77f64c-1f57-4723-8276-d16d156aa44d)

## Post-Route parasitic extraction using SPEF extractor
Commands for SPEF extraction using external tool
```
cd Desktop/work/tools/openlane_working_dir/openlane/scripts/spef_extractor
python3 main.py -l /home/vsduser/Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/runs/14-11_18-31/tmp/merged.lef -d /home/vsduser/Desktop/work/tools/openlane_working_dir/openlane/designs/picorv32a/runs/14-11_18-31/results/routing/picorv32a.def
```
![image](https://github.com/user-attachments/assets/5702e95c-143c-4ea5-af80-271da324a04a)

## Post-Route OpenSTA timing analysis with the extracted parasitics of the route.
Commands to be run in OpenLANE flow to do OpenROAD timing analysis with integrated OpenSTA in OpenROAD
```
openroad
read_lef /openLANE_flow/designs/picorv32a/runs/14-11_18-31/tmp/merged.lef
read_def /openLANE_flow/designs/picorv32a/runs/14-11_18-31/results/routing/picorv32a.def
write_db pico_route.db
read_db pico_route.db
read_verilog /openLANE_flow/designs/picorv32a/runs/14-11_18-31/results/synthesis/picorv32a.synthesis_preroute.v
read_liberty $::env(LIB_SYNTH_COMPLETE)
link_design picorv32a
read_sdc /openLANE_flow/designs/picorv32a/src/my_base.sdc
set_propagated_clock [all_clocks]
read_spef /openLANE_flow/designs/picorv32a/runs/14-11_18-31/results/routing/picorv32a.spef
report_checks -path_delay min_max -fields {slew trans net cap input_pins} -format full_clock_expanded -digits 4
exit
```
![image](https://github.com/user-attachments/assets/126a519c-df6c-4573-80f5-653d1c157695)


</details>


<details>
  <summary>Lab 15</summary>
	
  ## OpenRoad Physical Design

  ### Path to Zetta-Scale Computing  

1. **Bombe**  
The Bombe, an electro-mechanical machine designed during World War II, was pivotal in decrypting German Enigma-encrypted messages. Refined by Alan Turing and Gordon Welchman at Bletchley Park, UK, it systematically tested rotor settings of the Enigma machine by leveraging known plaintext patterns. By performing logical operations to narrow down possible keys, the Bombe drastically accelerated the decryption process and contributed significantly to the Allied war effort.  

2. **ENIAC (Electronic Numerical Integrator and Computer)**  
Developed during World War II by John Presper Eckert and John Mauchly at the University of Pennsylvania, ENIAC became the first fully electronic, general-purpose digital computer. Completed in 1945, it was primarily designed for calculating artillery firing tables for the U.S. Army. Unlike earlier mechanical or electromechanical systems, ENIAC utilized vacuum tubes. However, it required manual reconfiguration for each new task, as it lacked stored-program capability. Despite its limitations, ENIAC showcased the immense potential of electronic computing for solving large-scale numerical problems.  

3. **EDVAC (Electronic Discrete Variable Automatic Computer)**  
EDVAC, another milestone by Eckert and Mauchly with conceptual contributions from John von Neumann, marked a significant leap forward in computing technology. Completed in 1949, EDVAC introduced the stored-program concept, allowing data and instructions to reside in memory. This innovation simplified programming, utilized binary representation instead of decimal, and formed the foundation of the modern von Neumann architecture.

### 50 Years of Microprocessor Trend Data:
![image](https://github.com/user-attachments/assets/049a47b4-48d8-4ae7-a929-9ed0687153d9)

#### **Key Metrics**  

1. **Transistors (Orange Triangles)**  
   - The number of transistors on microprocessor chips has grown exponentially, following Moore's Law, which predicts a doubling roughly every two years.  
   - This exponential growth enabled increasingly complex processors, reaching billions of transistors by the 2020s.

2. **Single-Thread Performance (Blue Circles)**  
   - Measured using benchmarks like SpecINT, single-thread performance indicates the computational ability of a single processor core.  
   - Performance steadily improved through innovations in architecture, instruction-level parallelism, and clock speeds.  
   - However, growth slowed after 2005 due to physical limits, such as power dissipation and heat.

3. **Frequency (Green Diamonds)**  
   - Processor clock speeds increased consistently until the early 2000s.  
   - Plateaued as inefficiencies and heat dissipation challenges made further increases impractical.

4. **Typical Power (Red Triangles)**  
   - Power consumption grew alongside transistor density and clock speeds.  
   - By the mid-2000s, power efficiency became a critical design constraint to manage thermal limits.

5. **Number of Logical Cores (Black Dots)**  
   - The shift to multi-core processors emerged in the mid-2000s as a solution to the stagnation in single-thread performance.  
   - Increasing core counts facilitated parallel processing, boosting overall performance and efficiency.

---

#### **Key Milestones**  

1. **iPhone Release (~2007)**  
   - Marked the advent of mobile computing, prioritizing power efficiency without compromising performance.  
   - This milestone drove innovations in low-power processor designs and reshaped consumer electronics.

2. **Datacenter-Scale Computing (Post-2010)**  
   - Shifted focus toward energy-efficient, scalable, and parallel architectures.  
   - Addressed the needs of cloud computing and large-scale data centers, shaping the modern computing landscape.
  
### Path to zetta-scale computing

![image](https://github.com/user-attachments/assets/41ff22cc-ef64-4781-8218-9ead3687cb41)


### **The Path to Zettascale Computing**  

Tracing the evolution of computing performance from gigascale in 1984 to the anticipated zettascale by 2035, measured in **FLOPS** (floating-point operations per second), highlights the extraordinary growth in computational capability driven by innovations in high-performance computing (HPC).

---

#### **Key Performance Levels**  

1. **Gigascale (10⁹ FLOPS)**  
   - **Era:** 1984  
   - **Significance:** Represented the computational capability of early supercomputers, laying the groundwork for rapid advancements in performance.  

2. **Terascale (10¹² FLOPS)**  
   - **Era:** ~1997  
   - **Example System:** *Jaguar (Cray XT5)*  
   - **Power Consumption:** 7 MW  
   - **Impact:** Introduced teraflop-level performance, enabling more complex scientific simulations and data processing.

3. **Petascale (10¹⁵ FLOPS)**  
   - **Era:** 2008  
   - **Example System:** *Titan (Cray XK6)*  
   - **Performance:** 27 petaflops  
   - **Power Consumption:** 9 MW  
   - **Advancements:** Marked a leap in HPC, powering breakthroughs in weather modeling, genomics, and physics simulations.  

4. **Exascale (10¹⁸ FLOPS)**  
   - **Era:** 2021  
   - **Example System:** *Frontier (Cray Shasta)*  
   - **Performance:** 1.5 exaflops  
   - **Configuration:** 4 AMD GPUs + 1 AMD CPU  
   - **Power Consumption:** 29 MW  
   - **Applications:** Enabled massive-scale AI workloads, precise simulations for climate, energy, and materials science.  

5. **Zettascale (10²¹ FLOPS)**  
   - **Era:** Expected ~2035  
   - **Projected Applications:** Advanced climate modeling, AI-driven innovations, and global-scale simulations in physics and biology.  
   - **Estimated Power Consumption:** 50–100 MW per machine  
   - **Challenges:** Achieving power efficiency and scalability while balancing the costs and thermal constraints of such massive computational systems.  

### CMOS Evolution and Next-Gen Candidates
![image](https://github.com/user-attachments/assets/67581ec2-2954-4954-b828-e033b62a6225)

### **Evolving CMOS Technology Landscape**  

Advancements in materials, structures, and processes are driving the continued evolution of CMOS technology, addressing the challenges of scaling to the 1nm node and beyond. These innovations ensure improvements in performance, power efficiency, and transistor density.

---

#### **Key Areas of Innovation**  

1. **Channel Material**  
   - **Current Trends:**  
     - *Silicon (Si):* Dominates due to its mature fabrication ecosystem and reliable electrical properties.  
     - *Strained SiGe (Silicon-Germanium):* Enhances carrier mobility for high-speed, high-performance applications.  
   - **Future Materials:**  
     - *2D Materials (e.g., MoS₂):* Extremely thin and efficient, suitable for scaling beyond silicon's physical limits.  
     - *Germanium (Ge):* Offers higher electron mobility, improving switching speed and efficiency.  

2. **Patterning**  
   - **Current Techniques:**  
     - *Deep Ultraviolet (DUV) Lithography:* Commonly uses ArF and KrF lasers to define features at smaller nodes.  
   - **Next-Gen Techniques:**  
     - *Extreme Ultraviolet (EUV) Lithography:* Enables precise patterning at sub-7nm nodes.  
     - *High-NA EUV (High Numerical Aperture EUV):* Further enhances resolution for even smaller feature sizes.  

3. **Gate Stack Material**  
   - **Current Materials:**  
     - *High-K Metal Gates (HKMG):* Reduce leakage current and improve gate control in modern transistors.  
   - **Next-Gen Candidates:**  
     - *NC-FET (Negative Capacitance FET):* Uses ferroelectric materials to reduce power consumption.  
     - *TFET (Tunnel FET):* Leverages quantum tunneling for ultra-low-power applications, ideal for IoT and portable devices.  

4. **Interconnection Material**  
   - **Current Materials:**  
     - *Copper (Cu):* Widely used for its low resistivity, ensuring efficient signal transmission.  
   - **Next-Gen Materials:**  
     - *Ruthenium (Ru):* Reduces resistance at smaller scales, improving reliability.  
     - *Compound Metals and Topological Semi-Metals:* Enhance conductivity for high-performance interconnects.  

5. **Device Structure**  
   - **Current Architectures:**  
     - *FinFET:* 3D design that effectively mitigates short-channel effects and enhances control.  
     - *Planar Transistors:* Simpler structure, still used in cost-sensitive applications.  
   - **Next-Gen Architectures:**  
     - *3DS-FET (3D Stacked FET):* Achieves higher density by stacking transistors vertically.  
     - *MBC-FET (Multi-Bridge Channel FET):* Incorporates multiple channels for improved drive current and efficiency.  
     - *VFET (Vertical FET):* Optimized for higher transistor density and energy efficiency.  

6. **Design Co-Optimization**  
   - **DTCO (Design-Technology Co-Optimization):**  
     - Integrates advanced features like *Backside Interconnects (BSI)* for better signal integrity and reduced latency.  
   - **STCO (System-Technology Co-Optimization):**  
     - Focuses on innovations like *chiplets* to enable modular, scalable designs with reduced complexity and cost.  


### FinFETs
![image](https://github.com/user-attachments/assets/7a610808-c457-4c62-8745-fd868954a6ba)

### **Evolution of Transistor Technology**  

The evolution of transistor architectures reflects the relentless pursuit of performance, power efficiency, and scalability in the face of physical and material challenges. The shift from planar designs to advanced 3D architectures like FinFET and Gate-All-Around (GAA) represents key milestones in semiconductor innovation.

---

#### **Key Milestones**  

1. **Planar Transistor (Traditional)**  
   - **Design:**  
     - Features a flat channel with the gate positioned on one side to control the flow of current.  
   - **Challenges:**  
     - As scaling approaches nanometer nodes, issues like leakage current and poor electrostatic control emerge.  
     - Reduced efficiency and reliability due to limited gate control over the channel.  
   - **Era:** Dominated semiconductor technology until the early 2010s.  

2. **FinFET (Introduced in 2011)**  
   - **Design:**  
     - The channel is shaped like a vertical "fin," allowing the gate to wrap around three sides of the channel.  
   - **Advantages:**  
     - Provides better electrostatic control, reducing leakage current and enabling lower threshold voltages.  
     - Improves performance and power efficiency at smaller scales.  
   - **Applications:**  
     - Became the standard for nodes below 22nm, widely used in CPUs, GPUs, and mobile SoCs.  

3. **Gate-All-Around (GAA) Transistor (Expected ~2025)**  
   - **Design:**  
     - The gate completely surrounds the channel, which can take the form of stacked nanosheets or nanowires.  
   - **Advantages:**  
     - Offers superior electrostatic control compared to FinFETs.  
     - Supports better scalability and efficiency for nodes below 3nm.  
     - Enhances current density and reduces power consumption, meeting the demands of AI and high-performance computing.  
   - **Future Outlook:**  
     - GAA transistors are positioned as the next step in maintaining Moore's Law, with companies like TSMC and Samsung actively developing nanosheet-based technologies.  

---

#### **Impact of Transistor Evolution**  

- **Improved Performance:** Enhanced gate control enables faster switching speeds and greater drive current capability.  
- **Power Efficiency:** Reductions in leakage and better on/off state control improve power consumption.  
- **Miniaturization:** 3D designs like FinFET and GAA allow for continued scaling beyond the limitations of planar transistors.

### Why FinFETs and Gate-All-Around Transistors?
![Screenshot from 2024-11-26 04-32-51](https://github.com/user-attachments/assets/a3c6c82f-3406-494e-9b28-9d49d56d87c4)

### **Advantages of FinFETs and Gate-All-Around (GAA) Transistors Over Planar Structures**

As semiconductor technology advances, FinFETs and Gate-All-Around (GAA) transistors have emerged as pivotal solutions to address the limitations of planar transistors. These advanced architectures provide better performance, power efficiency, and scalability, enabling the continued miniaturization of transistors.

---

#### **Planar Transistors: Challenges**  
- **Sub-Channel Leakage:**  
  - Limited gate control over the channel leads to higher leakage currents, reducing efficiency.  
- **Higher Power Consumption:**  
  - Leakage currents contribute to increased power usage, making planar designs less suitable for modern low-power applications.  

---

#### **FinFET Transistors: Benefits**  

- **Structure:**  
  - The gate wraps around three sides of the channel (fin), significantly enhancing electrostatic control over the channel.  

- **Advantages:**  
  1. **Reduced Sub-Threshold Leakage:**  
     - Stronger gate control minimizes leakage currents, improving power efficiency.  
  2. **Improved Drive Current (I\_{ON}):**  
     - Increased channel control enhances current flow for better performance.  
  3. **Smaller Footprint:**  
     - Efficient design enables high performance within a compact size, facilitating continued scaling to smaller nodes.  

---

#### **Gate-All-Around (GAA) Transistors: Advantages**  

- **Structure:**  
  - The gate completely surrounds the channel, providing even greater electrostatic control than FinFETs.  

- **Advantages:**  
  1. **Improved Short-Channel Performance:**  
     - Better control over drain-induced barrier lowering (DIBL) and reduced drain capacitance improve performance at smaller scales.  
  2. **Enhanced Scaling Efficiency:**  
     - Superior scaling efficiency due to reduced drain capacitance (C\_d) and increased gate capacitance (C\_{ox}):  
       \[
       S \propto (1 + \frac{C_d}{C_{ox}})
       \]  
  3. **Reduced Sub-Threshold Slope:**  
     - Achieves superior performance by minimizing the voltage required to switch the transistor, making it ideal for low-power applications.  

---

#### **Graph Comparison**  
- **Efficiency:**  
  - Both FinFETs and GAA transistors demonstrate significantly lower sub-threshold slopes compared to planar transistors, indicating improved control and efficiency.  
- **Performance:**  
  - FinFETs and GAA transistors outperform planar structures in terms of current drive and scalability, especially at dimensions below 10nm.  


The transition from planar to FinFETs and GAA transistors has been instrumental in overcoming the challenges of leakage, power consumption, and scalability. These advanced architectures enable higher performance and better efficiency, ensuring the sustainability of Moore's Law in modern semiconductor technology.

![Screenshot from 2024-11-26 04-33-51](https://github.com/user-attachments/assets/fb5719fe-54b9-4de9-96f9-355d20ac62af)

### CMOS Technology Inflection Points
### **Advantages of Tri-Gate Transistors and FEOL Innovations**

---

#### **Tri-Gate Transistors**  
Tri-Gate transistors, a type of multi-gate architecture, represent a key leap forward in addressing power and performance challenges as transistor dimensions shrink.  

- **Reduced Leakage:**  
  1. Tri-Gate transistors significantly minimize leakage currents compared to planar transistors operating at the same gate voltage.  
  2. Lower **off-current** reduces power dissipation, resulting in better energy efficiency—a critical factor in modern low-power and mobile devices.  

- **Higher Drive Current:**  
  1. They deliver a higher **drive current (I\_{ON})** while maintaining the same off-current as planar designs, enhancing overall circuit performance.  
  2. This makes them ideal for demanding applications requiring high-speed operation and power efficiency, such as AI accelerators and cloud computing systems.  

---

#### **FEOL (Front-End-Of-Line) Innovations**  
FEOL refers to the foundational processes in semiconductor manufacturing where the active components of a chip are constructed.

- **Definition:**  
  - FEOL involves creating the core building blocks, including transistors, capacitors, and isolation structures, on the silicon wafer.  
  - This phase focuses on forming the **active devices** that dictate the chip's electrical characteristics.

- **Impact:**  
  1. **Enabling Miniaturization:**  
     - Innovations in FEOL processes support the development of smaller, more densely packed transistors, critical for scaling to advanced nodes like 3nm and below.  
  2. **Improved Efficiency:**  
     - Advancements like **strain engineering**, **high-K dielectrics**, and advanced doping techniques enhance device performance while reducing power consumption.  
  3. **Moore's Law Continuation:**  
     - FEOL innovations are vital in pushing the limits of transistor density and functionality, ensuring continued progress in semiconductor technology.  

---

Tri-Gate transistors provide significant advantages in power efficiency and performance, making them a cornerstone of modern electronic design. Meanwhile, FEOL innovations enable these advancements, ensuring that semiconductor manufacturing continues to meet the demands of increasingly sophisticated applications. Combined, these technologies play a pivotal role in sustaining and surpassing the limits of Moore’s Law.
![Screenshot from 2024-11-26 04-36-09](https://github.com/user-attachments/assets/562aa1ae-2626-4cc9-9bc9-d7f447db39fa)

### **Dennard Scaling and Technology Node Innovations**

#### **Dennard Scaling:**
- **Concept:**  
  Dennard Scaling posits that as transistors shrink in size:
  1. Voltage and current scale proportionally, keeping **power density constant**.  
  2. This allows for higher transistor density, faster performance, and lower power consumption in smaller nodes.  

- **Drive Voltage Scaling Graph:**  
  - **Ideal Scaling:** Demonstrates a linear reduction in drive voltage with shrinking gate lengths (log scale).  
  - **Practical Trends:**  
    - Real-world deviations (red for high-performance, green for low-power devices) occur due to:
      - **Leakage currents** at small scales.  
      - Increased **power density**, which limits aggressive voltage scaling.  
  - These challenges signify the **end of pure Dennard Scaling**, necessitating new materials and architectures.

#### **Technology Nodes and Key Innovations:**

- **~1 µm:**  
  Marks the beginning of CMOS miniaturization, overcoming the "end of scaling" for traditional planar devices.  

- **180 nm (Voltage Scaling):**  
  Initiates drive voltage reduction, improving power efficiency and thermal management.  

- **130 nm (Cu BEOL):**  
  Replaces aluminum with **copper interconnects**, reducing resistance and improving performance in Back-End-Of-Line (BEOL) processes.  

- **90 nm (Uniaxial Strained Si NMOS):**  
  Introduces **strained silicon** to boost electron mobility in NMOS transistors, enhancing drive current and switching speed.  

- **65 nm (eSiGe CVD ULK):**  
  Embeds silicon-germanium (SiGe) in PMOS transistors to induce strain, improving hole mobility and device performance.  
  Uses **CVD (Chemical Vapor Deposition)** for precision and **ULK (Ultra-Low-K)** dielectrics for reduced capacitance.  

- **45 nm (HK-first MG-last):**  
  - Introduces **high-k dielectrics** to reduce gate leakage and improve control.  
  - Combines high-k with **metal gates (MG)** to support continued scaling.  

- **32 nm (HKMG with Raised S/D NMOS):**  
  - Advances HKMG technology with **raised source/drain (S/D) regions**, enhancing current drive and reducing parasitics.  

#### **SEM Images Analysis:**

- **Left Image:**  
  - Displays a cross-section of transistors with:  
    - **High-k materials:** Reduce leakage.  
    - **Embedded SiGe:** Induces strain, enhancing PMOS performance by improving hole mobility.  

- **Right Image:**  
  - Highlights raised **source/drain regions** and gate channels in transistors.  
  - Demonstrates how these structures optimize performance and reduce resistive losses at smaller technology nodes.  

Dennard Scaling provided the foundation for decades of transistor miniaturization but reached its limits due to leakage and power density challenges. Innovations at each technology node—such as strained silicon, high-k materials, and copper interconnects—enable continued performance improvements, marking the evolution from early CMOS scaling to advanced sub-10nm technologies.

![Screenshot from 2024-11-26 04-37-26](https://github.com/user-attachments/assets/a8cf6f25-306c-4fb9-9e45-0d0aedf3ad40)

### **Key Technology Nodes and Innovations**

---

#### **22 nm Node**  
1. **FinFET (Tri-Gate) Transistors:**  
   - Transition to 3D architecture with gates wrapping around three sides of the channel.  
   - **Benefits:** Improved gate control, reduced leakage currents, and better scalability.  

2. **Self-Aligned Contacts (SAC) and Copper Interconnects (Co+Cu BEOL):**  
   - SAC ensures precise alignment of contacts, minimizing parasitics.  
   - **Copper interconnects** reduce resistivity, improving overall performance.  

#### **14 nm Node**  
1. **Unidirectional Metal Routing:**  
   - Introduced uniform routing direction to enhance signal integrity and reduce cross-talk.  

2. **Advanced Layout Techniques:**  
   - **SADP (Self-Aligned Double Patterning):** Achieves precise feature definition by breaking lithography limits.  
   - **SDB (Single Diffusion Break):** Isolates transistors efficiently, optimizing density and performance.  


#### **10 nm Node**  
1. **Advanced Patterning Techniques:**  
   - Innovations like **SA-SDB**, **LELELE (Litho-Etch-Litho-Etch-Litho-Etch)**, and **SAQP (Self-Aligned Quadruple Patterning)** overcome lithography constraints for tighter geometries.  

#### **7 nm Node**  
1. **Extreme Ultraviolet Lithography (EUV):**  
   - Simplifies multi-patterning requirements and reduces overlay errors in manufacturing.  
   - Facilitates greater feature precision at smaller scales.  

#### **5 nm Node**  
1. **SiGe Channels for PMOS:**  
   - Incorporation of silicon-germanium channels enhances hole mobility, boosting PMOS transistor performance.  

2. **EUV SA-LELE:**  
   - Refines EUV lithography with Self-Aligned Litho-Etch-Litho-Etch (SA-LELE) for tighter and more precise features.  


#### **3 nm / 2 nm / 1.4 nm Nodes**  
1. **Gate-All-Around (GAA) Transistors:**  
   - Uses **stacked nanosheets** or **nanowires** for enhanced electrostatic control.  
   - **Advantages:** Improved channel control, higher drive current, and better power efficiency compared to FinFETs.  

#### **Sub-1 nm Node**  
1. **CFET (Complementary FET):**  
   - **Vertical stacking** of NMOS over PMOS to maximize area efficiency and improve performance.  

2. **2D Materials (e.g., MoS₂):**  
   - **Atomically thin channels** enable scaling beyond the limitations of silicon, providing high mobility and low leakage.  
   - Ideal for **next-generation 2D FETs** at atomic scales.  

From the 22 nm node to sub-1 nm, each generation incorporates breakthroughs in materials, architectures, and lithographic techniques to sustain the pace of semiconductor scaling. These innovations address challenges of power efficiency, density, and performance while driving the evolution of modern electronics.
![Screenshot from 2024-11-26 04-38-50](https://github.com/user-attachments/assets/9720416b-0860-4556-a3f7-38aa59c71b64)

### **Samsung's Transistor Scaling with Fin Depopulation**

Samsung has employed an innovative approach to transistor scaling using **Fin Depopulation** in their FinFET technology across advanced nodes. This method involves systematically reducing the number of fins per transistor, maintaining consistent **fin width** and optimizing **fin height** to achieve smaller, more efficient transistors without compromising performance.

### **Technology Nodes and Key Details:**

#### **10 nm (High-Density - HD):**
- **Fin Height:** 420 nm  
- **Number of Fins:** 10  

#### **8 nm (Ultra High-Density - UHD):**
- **Fin Height:** 378 nm  
- **Number of Fins:** 9  

#### **7 nm (HD):**
- **Fin Height:** 27 nm  
- **Number of Fins:** 8  

#### **5 nm (UHD):**
- **Fin Height:** 27 nm  
- **Number of Fins:** 7  

### **Key Benefits of Fin Depopulation:**

1. **Transistor Miniaturization:**  
   By reducing the number of fins, the overall size of the transistor shrinks, enabling tighter packing and higher transistor density.  

2. **Performance Retention:**  
   Despite fewer fins, performance metrics like **drive current** and **switching speed** remain optimized, owing to precise control of fin height and other design parameters.  

3. **Improved Power Efficiency:**  
   Smaller transistors inherently consume less power while maintaining operational efficiency, aligning with the demands of modern low-power applications.  

4. **Enabling Advanced Nodes:**  
   This technique facilitates scaling to smaller nodes like 5 nm and beyond, paving the way for enhanced chip capabilities in consumer and enterprise technologies.  

Samsung's **Fin Depopulation** is a critical innovation in advancing FinFET scaling, balancing the trade-offs between size, performance, and efficiency. This strategy not only supports the continuation of Moore's Law but also meets the increasing performance demands of AI, IoT, and next-gen computing workloads.
![Screenshot from 2024-11-26 04-40-04](https://github.com/user-attachments/assets/b203508c-b942-4310-842f-b490e9f1eb03)

### **Key Techniques for Transistor Scaling and Density Improvement**


#### **1. Double Diffusion Break (DDB):**
- **Description:**  
  Creates a gap filled with insulating material between the source and drain regions, effectively reducing the width of the transistor.  
- **Benefit:**  
  - Enables smaller cell sizes, allowing for higher transistor density.  
  - Enhances scalability by optimizing transistor layout.  
- **Illustration:**  
  A cross-sectional view shows the insulating gap separating the source and drain regions.

#### **2. Single Diffusion Break (SDB):**
- **Description:**  
  Introduces an insulating gap only on one side of the transistor. Less aggressive than DDB, providing design flexibility.  
- **Benefit:**  
  - Balances size reduction with retained performance.  
  - Suitable for scenarios requiring moderate density improvements.  
- **Illustration:**  
  Highlights the asymmetry of the gap on one side of the transistor compared to DDB.

#### **3. Contact Over Field Gate (COFG):**
- **Description:**  
  Places the gate contact directly over the field oxide region of a transistor, optimizing layout design.  
- **Benefit:**  
  - Reduces lateral spacing between adjacent transistors.  
  - Allows for smaller cell sizes without significant performance penalties.  
- **Illustration:**  
  A cross-section shows the contact precisely positioned over the field oxide.

#### **4. Contact Over Active Gate (COAG):**
- **Description:**  
  A more advanced method where the gate contact is positioned over the active gate region itself.  
- **Benefit:**  
  - Achieves even smaller cell sizes and higher transistor densities.  
  - Essential for advanced nodes where space is at a premium.  
- **Illustration:**  
  Cross-sectional imagery highlights the aggressive placement of the contact over the active gate.

#### **5. Back-Side Power Delivery Network (BS-PDN):**
- **Description:**  
  Power supply rails are routed on the backside of the chip, separating signal routing from power delivery.  
- **Benefit:**  
  - Reduces standard cell height, freeing up space for more transistors.  
  - Improves power delivery efficiency and reduces resistive losses.  
- **Illustration:**  
  A schematic illustrates the power rails positioned on the chip’s backside, optimizing transistor layout.

These techniques collectively address the challenges of **transistor scaling** and **density improvement** in modern semiconductor technology. From structural innovations like DDB and COAG to routing advancements like BS-PDN, each technique contributes to enabling smaller, faster, and more efficient chips critical for next-generation electronics.

![Screenshot from 2024-11-26 04-42-37](https://github.com/user-attachments/assets/181f72f2-67d7-47e6-be95-52a72b152d09)

### **Key Technology Advances in Threshold Voltage (Vt) Variability**

#### **1. Planar Technology**  
- **Description:**  
  - In planar transistor technology (≥100nm nodes), **threshold voltage (Vt) variability** was a significant challenge, with variations around **130mV**.  
- **Cause of Variability:**  
  - Process variations in doping concentration.  
  - Temperature fluctuations affecting carrier mobility.  
  - Line-edge roughness and gate length inconsistency.  
- **Impact:**  
  - Higher variability led to less predictable performance, especially as technology nodes shrank.

#### **2. FinFET Technology**  
- **Description:**  
  - The transition to **FinFET technology** (~22nm) drastically reduced Vt variability to about **14mV**.  
- **Reasons for Improvement:**  
  - FinFET’s 3D structure provides **superior electrostatic control** over the channel.  
  - Reduced sensitivity to random dopant fluctuations due to the intrinsic thin fin design.  
  - Improved manufacturing precision for channel length and width.  
- **Impact:**  
  - Better stability and power efficiency, allowing for higher performance in smaller nodes.

#### **3. Nanowire (NW) Technology**  
- **Description:**  
  - The most advanced nanowire technologies (≤14nm nodes) reduce Vt variability to as low as **7mV**.  
- **Reasons for Improvement:**  
  - Nanowires allow for **Gate-All-Around (GAA)** architectures, which provide nearly perfect electrostatic control.  
  - Enhanced uniformity in nanowire fabrication leads to minimal process-induced variability.  
  - Negligible impact of random dopant and line-edge effects due to precise geometrical dimensions.  
- **Impact:**  
  - Offers exceptional performance stability and efficiency, even at sub-10nm dimensions.

From planar to nanowire technology, advances in transistor design have continuously reduced **threshold voltage variability**, a critical factor for maintaining consistent performance and power efficiency in modern integrated circuits. Each technological leap reflects the industry's ability to tackle process challenges at increasingly smaller nodes.
![Screenshot from 2024-11-26 04-45-40](https://github.com/user-attachments/assets/b00dfde5-f61b-45ce-b090-398540b9c579)

### **Parasitic Resistance and Its Impact on Transistor Performance**

#### **Understanding Parasitic Resistance (R\_EXT):**  
- Parasitic resistance refers to the unwanted resistance in the regions outside the channel, such as source/drain contacts, metal interconnects, and vias.
- It is an **external resistance** compared to the **channel resistance (R\_ch)**, which is the resistance offered by the conductive channel itself.
- As transistors scale, parasitic resistance becomes increasingly significant relative to channel resistance, impacting performance metrics like drive current and switching speed.


### **Key Differences in Parasitic Resistance Across Transistor Architectures**


#### **1. Planar MOSFETs**  
- **Structure:**  
  - Traditional 2D architecture with the gate located above the flat channel.  
- **Contact-to-Gate Width Ratio ( \( W_C / W_G \)):**  
  - Approximately 1: contact width nearly matches gate width.  
- **Parasitic Resistance ( \( R_{EXT} \ll R_{ch} \)):**  
  - External resistance is much smaller than channel resistance.  
- **Impact on Performance:**  
  - Minimal impact, as parasitic resistance is negligible relative to the channel resistance.  


#### **2. FinFETs**  
- **Structure:**  
  - 3D design with fins acting as the channel, and the gate wrapping around the fin for better electrostatic control.  
- **Contact-to-Gate Width Ratio ( \( W_C / W_G \approx 1/3 \)):**  
  - Contact width is smaller than gate width, leading to increased resistance in smaller transistors.  
- **Parasitic Resistance ( \( R_{EXT} / R_{ch} \approx 1 \)):**  
  - Parasitic resistance is now comparable to the channel resistance.  
- **Impact on Performance:**  
  - Starts to degrade performance, particularly as the fin width shrinks in advanced nodes.  


#### **3. Gate-All-Around (GAA) FETs**  
- **Structure:**  
  - Uses nanosheets or nanowires as channels, with the gate fully surrounding them for superior electrostatic control.  
- **Contact-to-Gate Width Ratio ( \( W_C / W_G \approx 1/6 \)):**  
  - The small contact width increases external resistance significantly.  
- **Parasitic Resistance ( \( R_{EXT} / R_{ch} \approx 3 \)):**  
  - Parasitic resistance becomes much larger than the channel resistance.  
- **Impact on Performance:**  
  - Higher parasitic resistance challenges performance, even though GAA FETs excel in transistor density and electrostatic control.  


#### **4. Complementary FETs (CFETs)**  
- **Structure:**  
  - Vertically stacks NMOS and PMOS transistors, sharing the same footprint for improved density.  
- **Contact-to-Gate Width Ratio:**  
  - Similar to GAA, \( W_C / W_G \) is small, keeping contact width constrained.  
- **Parasitic Resistance ( \( R_{EXT} / R_{ch} \approx 3 \)):**  
  - High parasitic resistance persists due to compact dimensions.  
- **Impact on Performance:**  
  - Faces the same trade-offs as GAA, with density improvements coming at the cost of performance degradation from parasitic resistance.  


### **Challenges and Mitigation Strategies for Parasitic Resistance**
1. **Material Innovations:**  
   - Use of **low-resistance contact materials** (e.g., titanium nitride, cobalt) to reduce \( R_{EXT} \).  
2. **Advanced Contact Engineering:**  
   - Techniques like **self-aligned contacts (SAC)** and optimized via placements.  
3. **Process Refinements:**  
   - Reducing interface resistance through better source/drain doping and silicide formation.  
4. **Backside Power Delivery Networks (BS-PDN):**  
   - Offloads power delivery to the chip's backside, freeing up front-side space for denser, optimized interconnects.
     
As transistor architectures evolve, parasitic resistance increasingly impacts performance. While innovations like GAA and CFETs address electrostatic control and scaling, mitigating parasitic resistance is critical to fully leveraging their potential in advanced semiconductor nodes.
![Screenshot from 2024-11-26 04-46-36](https://github.com/user-attachments/assets/2d53814d-da2e-4770-a03f-16541cceaa7f)

### **Parasitic Resistance Breakdown and Reduction in Transistors**

### **Components of Parasitic Resistance ( \( R_{EXT} \)):**
Parasitic resistance arises from various parts of a transistor and its fabrication processes. The contributors are:

1. **Back-End-Of-Line (BEOL) Resistance ( \( R_{CA-BEOL} \)):**
   - Resistance from the contact metallization in the interconnect layers above the transistor.

2. **Contact Area Resistance ( \( R_{CA} \)):**
   - Resistance at the metal-semiconductor interface in the contact region.

3. **Contact-to-Transition Structure Resistance ( \( R_{CA-TS} \)):**
   - Resistance between the contact and the transition structure leading to the source/drain.

4. **Transition Structure Resistance ( \( R_{TS} \)):**
   - Resistance within the transition layer connecting the active transistor region to the contact.

5. **Middle-Of-Line (MOL) Resistance ( \( R_{MOL} \)):**
   - Includes both lateral and vertical resistance in the MOL stack connecting the contact to BEOL layers.

6. **Contact Resistance ( \( R_C \)):**
   - Resistance at the metal-semiconductor junction.

7. **Epitaxial Layer Resistance ( \( R_{EPI} \)):**
   - Resistance from the epitaxial layer, which spreads current laterally to the contact.

8. **Front-End-Of-Line (FEOL) Resistance ( \( R_{FEOL} \)):**
   - Resistance from the source/drain extensions and the doped regions in the transistor.


### **Initial vs. Improved \( R_{EXT} \) Breakdown:**

#### **NFETs (N-Channel FETs):**

- **Initial Breakdown:**
  - \( R_C \): 63%
  - \( R_{CA-BEOL} \): 31%

- **Improved Breakdown:**
  - \( R_C \): Reduced to 48%
  - \( R_{CA-BEOL} \): Reduced to 12%


#### **PFETs (P-Channel FETs):**

- **Initial Breakdown:**
  - \( R_{FEOL} \): 50%
  - \( R_C \): 45%

- **Improved Breakdown:**
  - \( R_{FEOL} \): Reduced to 78%
  - \( R_C \): Reduced to 16%


### **Key Strategies for Reducing Contact Resistance**

#### **Improving Ohmic/Tunneling Contacts:**

1. **Low Schottky Barrier Height ( \( \phi_b \)):**
   - Lowering \( \phi_b \) reduces the energy barrier for electron or hole injection, improving conductivity.

2. **High Doping Concentration ( \( N_d \)):**
   - Increasing \( N_d \) at the metal-semiconductor interface enhances carrier density, further lowering contact resistance.

#### **Equation for Specific Contact Resistivity ( \( \rho_c \)):**

\[
\rho_c \propto \exp\left(\frac{2\phi_b}{\hbar} \sqrt{\frac{\epsilon_s m_x}{N_d}}\right)
\]

- **\( \phi_b \):** Schottky barrier height (energy barrier for carrier injection).
- **\( \hbar \):** Reduced Planck constant.
- **\( \epsilon_s \):** Semiconductor permittivity.
- **\( m_x \):** Effective carrier mass.
- **\( N_d \):** Doping concentration.

- **Implication:**
  - Reducing \( \phi_b \) (e.g., using low-barrier metals) and increasing \( N_d \) (e.g., through high doping levels) leads to lower \( \rho_c \), thereby minimizing contact resistance.


### **Metal-Semiconductor Energy Diagram:**

The energy diagram illustrates the following:
1. **Schottky Barrier ( \( \phi_b \)):**
   - The energy difference between the metal Fermi level and the conduction/valence band edge of the semiconductor.
2. **Reduced Barrier:**
   - By selecting metals with a compatible work function and increasing doping levels, the barrier height can be lowered.
3. **Carrier Injection:**
   - A lower \( \phi_b \) allows easier injection of carriers (electrons for NMOS, holes for PMOS) into the semiconductor, improving device performance.


Reducing parasitic resistance ( \( R_{EXT} \)) is crucial for advancing transistor performance, especially in scaled technologies. By focusing on improving ohmic contacts, optimizing material selection, and employing advanced doping techniques, manufacturers can mitigate the effects of \( R_{EXT} \) and push the limits of semiconductor scaling.
![Screenshot from 2024-11-26 04-49-03](https://github.com/user-attachments/assets/1ce1a2df-923e-41d1-a7be-c6a0b99923c5)


### **Capacitance Composition Evolution Across Technology Nodes (22nm to 7nm)**

### **Bar Chart Breakdown (Left Side):**

#### **22nm Technology Node:**
- **Fringe Capacitance ( \( C_{fr} \)):**  
  - Largest contributor at **56%**.  
  - Dominates due to the larger physical dimensions and significant coupling effects between interconnects.  
- **Parasitic Capacitance - Contact-Acting ( \( C_{pc-ca} \)):**  
  - Accounts for **25%**.  
  - Arises from the proximity of the contact structures to active regions.  
- **Gate Capacitance ( \( C_g \)):**  
  - Smallest contribution at **19%** due to relatively larger node dimensions.

#### **14nm and 10nm Technology Nodes:**
- **Fringe Capacitance ( \( C_{fr} \)):**  
  - Decreases to **38%** at 14nm and **25%** at 10nm.  
  - Shrinking dimensions and improved manufacturing techniques mitigate fringe effects.  
- **Parasitic Capacitance ( \( C_{pc-ca} \)):**  
  - Becomes more dominant as shrinking dimensions increase the coupling between contacts and the transistor channel.  

#### **7nm Technology Node:**
- **Gate Capacitance ( \( C_g \)):**  
  - Becomes the largest contributor at **45%**, signifying the increasing importance of direct gate-channel interactions as dimensions shrink.  
- **Parasitic and Fringe Capacitance ( \( C_{pc-ca} \) and \( C_{fr} \)):**  
  - Both decrease further due to advanced designs and materials aimed at minimizing unwanted coupling and interactions.


### **Plot Descriptions:**

#### **First Scatter Plot:**
- **Normalized Delay Reduction:**
  - Demonstrates a decrease in delay for a ring oscillator using **SiBCN spacers** compared to traditional **SiN spacers**.  
  - Indicates improved transistor performance, likely due to better control over parasitic capacitance.

#### **Second Scatter Plot:**
- **Effective Capacitance ( \( C_{eff} \)) Reduction:**
  - Highlights an **8% reduction in \( C_{eff} \)** when using SiBCN spacers.  
  - Correlates directly with the improved delay seen in the first plot, emphasizing the importance of material innovation.

### **Spacer Materials Evolution (Rightmost Figure):**

- **Transition from SiOCN to SiCO Spacers:**
  - Early nodes used **SiOCN spacers**, but as dimensions shrank, these were replaced by **SiCO spacers** to minimize gate-contact capacitance.
  - **14nm and Beyond:**
    - Adoption of **low-\( k \)** spacers to decouple parasitic capacitance effects, improving performance and reducing power consumption.

### **TEM View of Transistor with Air Spacers:**

- **Air Spacers:**
  - Utilization of air, with its low dielectric constant (\( k \approx 1 \)), drastically reduces parasitic capacitance.  
  - This is evident in the **15% reduction in \( C_{eff} \)** compared to solid spacers, as shown in the adjacent plot.  

- **Benefits of Air Spacers:**
  - Minimized capacitance enables better performance at reduced power consumption, aligning with the scaling needs of advanced nodes.

- As technology nodes shrink, capacitance compositions shift, with fringe and parasitic capacitances reducing and gate capacitance becoming dominant.  
- Material advancements such as **SiBCN spacers** and the use of **air spacers** play a critical role in managing and reducing \( C_{eff} \), enabling continued performance improvements and scaling.  
- The evolution of spacer materials from SiOCN to low-\( k \) options reflects the industry's drive to address parasitic effects, ensuring efficient transistor operation at advanced nodes.  
![Screenshot from 2024-11-26 04-50-28](https://github.com/user-attachments/assets/49933e6a-9d1a-4171-8aa9-b72dd2f0ec51)


### **Key Properties of 2D Layered Materials (Compared to Silicon)**


#### **1. Uniform Atomic Scale Thickness:**
- **2D Materials (e.g., MoS₂):**
  - **Thickness:** A monolayer of MoS₂ is about **0.65 nm** thick.  
  - This ultra-thin structure makes 2D materials highly scalable and compact, allowing for devices to be scaled down with ease, which is advantageous in modern, miniaturized electronics.  
- **Silicon:**
  - Silicon, in its traditional form, has a much **thicker atomic structure** compared to 2D materials, which limits the scalability of silicon-based devices.

**Impact:**  
The ultra-thin nature of 2D materials like MoS₂ enables better scalability, offering potential for devices to become smaller and more energy-efficient as technology nodes shrink.

#### **2. Higher Effective Mass (\( m^* \)):**
- **2D Materials (MoS₂):**
  - **Effective Mass:** The effective mass of carriers in MoS₂ is about **0.55** times the mass of a free electron (\( m_0 \)).
  - The higher effective mass in MoS₂ can influence **carrier mobility**, affecting electronic transport properties and potentially resulting in lower mobility compared to materials like silicon.
  
- **Silicon:**
  - **Effective Mass:** The effective mass of carriers in silicon is **around 0.22** times the mass of a free electron (\( m_0 \)).
  - Silicon’s lower effective mass contributes to higher **carrier mobility**, enhancing its performance in electronic devices.

**Impact:**  
The higher effective mass in MoS₂ could lead to slower carrier transport and lower mobility compared to silicon, which may limit its performance in certain applications unless addressed with improved device design and material engineering.

#### **3. Bandgap:**
- **2D Materials (MoS₂):**
  - **Monolayer MoS₂:** The bandgap of a monolayer MoS₂ is about **1.85 eV**.  
  - **Bilayer MoS₂:** The bandgap reduces to around **1.5 eV**.
  - The larger bandgap in MoS₂ allows for better control over **current flow**, making it ideal for **electronic switching** and **optical applications** such as photodetectors, light-emitting diodes, and transistors.

- **Silicon:**
  - Silicon has a **smaller bandgap** of around **1.1 eV**.
  - While silicon's smaller bandgap makes it a good material for semiconductor applications, it limits the ability to effectively control current flow at smaller scales and in high-performance devices compared to 2D materials.

**Impact:**  
The larger bandgap of MoS₂ provides better control over electronic behavior, enabling more efficient **transistor switching** and potentially leading to higher **device performance**. This makes MoS₂ and similar 2D materials more attractive for use in high-performance, low-power electronics.

- **Ultra-thin structure** enables **scalability** in electronics.
- **Higher effective mass** impacts carrier mobility, which may require optimization for certain device applications.
- **Larger bandgap** in 2D materials like MoS₂ enhances **control over current flow**, making them ideal for **high-performance and low-power electronic devices**.

These properties make 2D layered materials such as MoS₂ highly promising for next-generation **nanoelectronics**, **optoelectronics**, and **scalable transistor technology**, with the potential to outperform traditional silicon in specific applications.
![Screenshot from 2024-11-26 04-52-49](https://github.com/user-attachments/assets/ac024686-ab02-43b3-9070-64ad31b9840d)
### **Transistor Scaling Challenges and Mitigation Strategies**

---

#### **1. Direct Source-to-Drain Tunneling:**
- **Challenge:**  
  As transistor gate lengths continue to shrink, **quantum tunneling** becomes more significant. Electrons can tunnel directly from the **source to the drain**, bypassing the gate’s control over current flow. This leads to **increased leakage current** and **device failure** when the transistor is supposed to be turned off.
  
- **Mitigation Strategy:**  
  To address tunneling, materials with a **high effective mass** (\( m^* \)) can be used. These materials help **reduce tunneling** by improving the **gate’s control over the channel**, ensuring better **electronic confinement**. Examples include certain **2D materials** like **MoS₂**.

---

#### **2. Surface Roughness and Thickness Variations:**
- **Challenge:**  
  At **atomic scales**, small fluctuations in **surface roughness** and **thickness variations** of the channel material can lead to **performance degradation** due to **variability** in material properties. This impacts **device reliability** and uniformity across chips.
  
- **Solution:**  
  The use of **uniform, atomically thin materials**, such as **2D materials** like **MoS₂** or **Graphene**, can help mitigate these issues. Their uniformity at the atomic scale reduces **thickness variations** and **surface roughness**, ensuring more **consistent performance** in devices.

---

#### **3. Capacitance Ratios (\( C_D \) and \( C_{ox} \)):**
- **Challenge:**  
  The **depletion region capacitance** (\( C_D \)) must remain **low** relative to the **gate oxide capacitance** (\( C_{ox} \)) to ensure proper **gate control** and **switching efficiency**. As devices shrink, maintaining this capacitance ratio becomes increasingly **difficult**.
  
- **Required Materials:**  
  Materials with a **low in-plane dielectric constant** (\( \epsilon \)) are needed to maintain these capacitance ratios at smaller nodes. **High-\( k \)** materials, like **high-\( k \) dielectrics** and **low-\( k \) spacers**, help manage capacitance and prevent **leakage currents**.

---

### **Diagrams Overview**

1. **Left Diagram: Transistor Structure**
   - The cross-sectional view of the transistor includes the following components:
     - **Source**: The region where carriers (electrons or holes) are injected into the channel.
     - **Drain**: The region where the carriers exit the channel.
     - **Gate**: The terminal that controls the flow of current by modulating the potential in the channel.
     - **Oxide**: The insulating layer between the gate and the channel, typically made of silicon dioxide.
     - **Silicon Substrate**: The base material that forms the foundation for the channel and other regions of the transistor.

2. **Right Diagram: Tunneling vs. Thermionic Emission**
   - **Scenario a - Thermionic Emission:**  
     - **Electrons cross the energy barrier** from the **source** to the **drain** as intended in normal transistor operation. This is the typical behavior where the gate controls the current flow effectively.
   
   - **Scenario b - Direct Tunneling:**  
     - At **extremely small gate lengths**, electrons can **tunnel directly** from the source to the drain, bypassing the gate’s control. This results in **leakage current** and **degraded performance**, making it difficult for the device to properly switch off.

- **Direct tunneling** can be mitigated by using materials with **high effective mass**, which improve gate control.
- **Surface roughness** and **thickness variations** can be reduced by using **2D materials** for better uniformity at atomic scales.
- **Capacitance ratios** can be maintained with **low-\( k \)** materials and **high-\( k \)** dielectrics to manage leakage and improve transistor performance at smaller nodes.

These strategies are essential for overcoming the challenges of transistor scaling, enabling continued miniaturization of devices in advanced semiconductor technologies.

![Screenshot from 2024-11-26 04-54-04](https://github.com/user-attachments/assets/96e662e1-456f-4d9b-b130-9af228e468be)

### **Direct Source-to-Drain Tunneling in MOSFETs:**

As the gate length (\(L_G\)) of Metal-Oxide-Semiconductor Field-Effect Transistors (MOSFETs) decreases, **direct source-to-drain tunneling** becomes a significant issue. This occurs when electrons tunnel directly from the source to the drain, bypassing the gate's control over the channel. The result is **increased leakage currents**, which leads to a **loss of efficiency** and degraded **performance** of the transistor, especially in ultra-scaled technologies.

---

### **Key Factors Influencing Tunneling Leakage:**

1. **Effective Mass (\( m^* \)):**
   - The **effective mass** of the channel material influences the **electron mobility** and **tunneling characteristics**. A **higher effective mass** makes it harder for electrons to move through the material, thereby **reducing the likelihood of tunneling**.
   - Materials like **MoS₂** have a **higher effective mass** compared to **silicon**, making them more **effective** in suppressing tunneling leakage. This results in better **control of the channel** by the gate and lower leakage currents, particularly in smaller devices.

2. **Bandgap (\( E_G \)):**
   - The **bandgap** of the material plays a critical role in determining how easy it is for electrons to tunnel through the material. A **larger bandgap** makes it more difficult for electrons to tunnel, as the energy barrier is higher.
   - For example, **MoS₂** has a **bandgap of ~1.85 eV** for a monolayer, which is significantly larger than that of **silicon** (around 1.1 eV). This larger bandgap helps **prevent tunneling** and **reduces leakage currents**, particularly at smaller gate lengths.

3. **Dielectric Constant (\( \epsilon \)):**
   - A material's **dielectric constant** influences its **capacitance**. A **lower dielectric constant** reduces the overall **capacitance** in the device and helps mitigate **leakage currents**.
   - **MoS₂** has a lower dielectric constant compared to silicon, which helps further reduce the **capacitance** and **tunneling leakage**, making it a promising material for next-generation **low-power devices**.

---

### **Graph Description:**

The graph in this context plots the **leakage current** (\( I_{SD, \text{leak}} \)) as a function of **gate length** (\( L_G \)) for different **channel thicknesses** (\( T_{CH} \)).

- **MoS₂** shows **significantly lower leakage** at **smaller gate lengths** compared to **silicon**. Specifically, MoS₂ can achieve up to a **100x reduction** in leakage current at smaller nodes.
- The **reduction in leakage** is attributed to the combined effects of:
  - **Higher effective mass** (\( m^* \)) of MoS₂, which makes electron tunneling more difficult.
  - **Larger bandgap** (\( E_G \)) of MoS₂ (~1.85 eV for monolayer), which provides better resistance to tunneling.
  - **Lower dielectric constant** (\( \epsilon \)) in MoS₂, which reduces capacitance and leakage currents.

This demonstrates how the unique properties of **MoS₂** make it a **better material** for scaling transistors and reducing **tunneling leakage** compared to **silicon** in next-generation semiconductor technologies.

- **Direct tunneling** from the source to drain becomes more problematic as gate lengths shrink.
- **Effective mass**, **bandgap**, and **dielectric constant** are key factors in controlling tunneling leakage.
- **MoS₂** outperforms **silicon** in reducing tunneling leakage, offering up to a **100x reduction** in leakage at smaller gate lengths.


![Screenshot from 2024-11-26 04-55-40](https://github.com/user-attachments/assets/c7d6f047-ff4e-428d-a320-87c6c0ec9225)

### **MoS₂ Transistor with 1 nm Gate Length:**

The MoS₂ transistor with a **1 nm gate length** marks a significant advancement in **transistor miniaturization**. With its ultra-thin **MoS₂ channel** and **nanoscale components**, this design harnesses the unique properties of **2D materials** and **nanotubes**, providing enhanced control and performance at extremely small scales.

---

### **Key Components and Materials:**

1. **MoS₂ Channel:**
   - **MoS₂** is a **2D material** that offers excellent electronic properties such as **high carrier mobility** and **large bandgap**. This allows for **strong gate control** even at small scales, which is essential when reducing the **gate length** to 1 nm.
   - The thin **MoS₂** channel ensures that the transistor can operate efficiently in the **nanoscale regime**, making it ideal for future ultra-scaled electronics.

2. **Single-Walled Carbon Nanotube (SWCNT) Gate Electrode:**
   - The **SWCNT gate** serves as the **ultra-small gate electrode**, offering **high electrical conductivity** and a **large surface area**. This is crucial for effectively modulating the MoS₂ channel at the **nanoscale**.
   - SWCNTs also provide **mechanical flexibility**, which can be beneficial in the fabrication process and device performance at small dimensions.

3. **Zirconium Dioxide (ZrO₂) High-k Dielectric:**
   - **ZrO₂** is used as the **high-k dielectric** material, which helps in **improving gate control** and **reducing leakage currents**. High-k dielectrics like ZrO₂ enhance **capacitance** between the gate and the channel, making it easier to control the transistor’s switching behavior, especially at smaller gate lengths.
   - The **reduction in leakage** is particularly important in advanced transistors to **maintain energy efficiency** and ensure proper functioning at extremely small scales.

4. **SiO₂ Substrate and n⁺ Silicon Back Gate:**
   - The **SiO₂ substrate** provides structural support and isolation for the device.
   - The **n⁺ silicon back gate** offers **additional control** over the MoS₂ channel, improving the **modulation** of the transistor's behavior and enabling **fine-tuning** of the device performance.

---

### **Design and Operation:**

- The **SWCNT gate** modulates the **MoS₂ channel** by depleting a small region, allowing for precise control over the channel's **conductance**. This is key for achieving **on-off switching**, where the transistor needs to turn on and off effectively at the **1 nm gate length**.
  
- The **high-k ZrO₂ dielectric** improves gate control by increasing the **capacitance** between the gate and the channel while reducing leakage currents, ensuring that the transistor performs efficiently at small scales.
  
- The **SiO₂ substrate** and **n⁺ silicon back gate** provide **additional gate control**, which is essential for tuning the transistor’s electrical characteristics, particularly as the gate length shrinks.


This MoS₂ transistor design represents a **breakthrough in nanoscale transistor technology**. By combining the unique properties of **MoS₂**, **SWCNT gate electrodes**, and **high-k dielectrics**, this design pushes the boundaries of transistor miniaturization and lays the groundwork for the development of future **nanoelectronics**. The ability to scale down transistors to **1 nm gate lengths** will be crucial for continuing the **Moore's Law** and advancing the performance of **next-generation electronic devices**.
![Screenshot from 2024-11-26 04-56-23](https://github.com/user-attachments/assets/b2499ec7-f230-4f72-9c74-9d7e5758bce3)

### **All-2D MOSFET: Structure and Fabrication Process**

The **All-2D MOSFET** utilizes **two-dimensional (2D) materials** for all key components, including the **source**, **drain**, **gate**, and **semiconductor channel**. This device takes advantage of the unique properties of 2D materials such as **high conductivity**, **atomic-scale thickness**, and **excellent electrical characteristics**, making it an ideal candidate for **next-generation transistors**. Below is a breakdown of its key components and the fabrication process:

---

### **Key Components:**

1. **Graphene Contacts (S, D, G):**
   - **Graphene** is used as the **source**, **drain**, and **gate electrodes** in this All-2D MOSFET.
   - **Properties:**
     - High **electrical conductivity**.
     - **Atomic thickness** allowing for efficient charge transport.
     - **Low-resistance contacts**, which reduces power loss and increases the overall performance of the transistor.

2. **MoS₂ Channel:**
   - **Molybdenum Disulfide (MoS₂)** is used as the **semiconductor channel** in the device.
   - **Properties:**
     - MoS₂ has an **excellent on/off current ratio**, which is critical for transistor switching behavior.
     - Its **atomic-scale thickness** ensures that the device can be scaled down efficiently, which is essential for future technology nodes.
     - **Bandgap** properties make it ideal for use in MOSFETs, enabling efficient current switching.

3. **h-BN Dielectric:**
   - **Hexagonal Boron Nitride (h-BN)** serves as the **insulating dielectric layer** in the All-2D MOSFET.
   - **Properties:**
     - Excellent **insulating properties**, preventing leakage between the gate and the channel.
     - High **thermal stability**, allowing the device to operate at elevated temperatures.
     - **Atomically thin**, contributing to the overall reduction in the device's size while maintaining excellent performance.

4. **Si/SiO₂ Substrate:**
   - The device is fabricated on a **silicon dioxide (SiO₂)** layer on top of a **silicon substrate**.
   - **Properties:**
     - Provides **mechanical support** for the 2D materials.
     - Acts as a **global back gate**, offering additional control over the transistor's performance.

---

### **Fabrication Process:**

1. **Deposition of Graphene:**
   - A layer of **graphene** is first deposited onto the **SiO₂ substrate**, which will serve as the gate electrode.

2. **Patterning the Graphene:**
   - The graphene is then **patterned** to define the **source** and **drain** regions. This step involves creating **gaps** between the graphene regions where the **MoS₂ channel** will be placed.

3. **Transfer of MoS₂ Channel:**
   - A **monolayer of MoS₂** is **transferred** onto the patterned graphene. This monolayer forms the **channel region** of the MOSFET, where the current will flow between the source and drain.

4. **Addition of h-BN Dielectric:**
   - An **h-BN layer** is added on top of the MoS₂ channel, acting as the **gate dielectric**. The h-BN layer ensures that the graphene gate does not directly contact the MoS₂ channel, which could result in leakage or performance degradation.

5. **Deposition of Top Graphene Gate:**
   - A **top layer of graphene** is then **deposited** and **aligned** over the h-BN layer to form the **gate electrode**. This top gate allows for efficient modulation of the channel conductivity.

6. **Final Contacting:**
   - The device is then contacted using **metallic electrodes** (usually **Ni/Au**) for testing purposes. These electrodes allow for the measurement of the transistor's performance, including current-voltage characteristics.

![Screenshot from 2024-11-26 05-01-18](https://github.com/user-attachments/assets/bbd8b3e7-f47b-41c2-8521-5df489eeb9f2)

The **All-2D MOSFET** demonstrates impressive electrical performance, with key characteristics that highlight the potential of **2D materials** like **MoS₂**, **graphene**, and **h-BN** in advancing transistor technology. Here's a breakdown of the performance:

---

### **1. Transfer Characteristics (Iₖ vs Vₖ):**
   - The **All-2D MOSFET** achieves a high **on/off current ratio (>10⁵)**, which indicates excellent **gate control** over the channel. This high ratio ensures that the transistor can effectively switch between **on** and **off** states, a critical property for efficient switching in logic circuits.
   - The ability to control the current flow with the **gate voltage (Vₖ)** reflects the **good electrostatic control** of the gate over the **MoS₂ channel**, a key advantage of 2D materials that are atomically thin and enable better gate-channel coupling.

---

### **2. Output Characteristics (I(D) vs V(DS)):**
   - The **smooth current modulation** with increasing **V(G)** and **V(DS)** shows that the device exhibits **good output performance**. This indicates that as the drain-source voltage (**V(DS)**) and gate voltage (**V(G)**) increase, the current through the transistor modulates predictably and efficiently, which is essential for analog and digital performance.
   - The smoothness of the output characteristics also reflects that the **graphene** contacts and **MoS₂** channel provide **low-resistance** paths with minimal degradation in performance as the device scales down.

---

### **3. Mobility:**
   - The **field-effect mobility** remains **constant with increasing gate electric field**, suggesting **minimal scattering** and high **interface quality** between the **2D materials**.
   - This property is particularly significant for maintaining **high-speed performance** in transistors. The constant mobility means that as the gate voltage increases, the carriers in the MoS₂ channel can still travel efficiently without being significantly hindered by defects or imperfections, which is often a challenge in traditional semiconductor materials.

![Screenshot from 2024-11-26 05-06-14](https://github.com/user-attachments/assets/fef64bf7-913b-4c35-aee2-722f754b2a61)


### **Key Components:**
1. **Gate:**
   - The gate is responsible for controlling the current flow through the **channel** by modulating the electric field. It regulates the switching of the transistor, turning it on or off depending on the applied voltage.
   
2. **Channel:**
   - The channel is the region between the **source (S)** and **drain (D)**, where current flows when the transistor is turned on. The performance of the transistor heavily depends on the properties of the channel material.
   
3. **Body:**
   - The body is the underlying region that is connected to the **substrate** and provides mechanical support. It can also impact the threshold voltage and other electrical characteristics of the transistor.

4. **STI (Shallow Trench Isolation):**
   - **STI** is used to isolate neighboring devices on a semiconductor wafer. It helps reduce **parasitic capacitance** and prevent electrical interference between adjacent transistors. STI is important in multi-device integrated circuits for ensuring proper device operation.

---

### **Biggest Challenge:**
   - **Formation of Single-Crystalline Semiconductors on Non-Planar Surfaces:**
     - A significant challenge in fabricating **non-planar transistors** is ensuring that the **semiconductor material** forms a **single-crystalline structure** on the non-planar surface. This is because traditional semiconductor fabrication techniques are optimized for **planar** (flat) surfaces, where it is easier to control crystal formation and ensure high-quality, uniform semiconductor layers.
     - On a **non-planar** surface, such as a **FinFET** or other advanced transistor designs, it becomes difficult to form a **single-crystal semiconductor layer** because the material may tend to form **polycrystalline** structures or face **defects** at the boundaries. These defects degrade the **electrical properties** of the transistor, such as mobility and current control.

   - **Mitigation Strategies:**
     - Techniques like **epitaxial growth**, **strained silicon**, or **Germanium-on-Silicon (Ge-on-Si)** may be used to address these challenges and promote **crystalline growth** even on non-planar surfaces.
     - Research is ongoing into **3D semiconductor integration** and **atomic-layer deposition** (ALD) techniques that might overcome these fabrication issues and allow high-quality **single-crystalline** semiconductors to be formed on curved or non-flat surfaces.

![Screenshot from 2024-11-26 05-07-07](https://github.com/user-attachments/assets/7e517f6d-8c21-4b67-a104-3e26bbbd9a5c)

- **Single-Layer CMOS (a):** This is the conventional CMOS design, where both NMOS and PMOS transistors are created on a single layer of silicon. All transistors function within the same plane, with lateral connections between them.

- **Monolithic 3D CMOS (b):** In this design, the NMOS and PMOS transistors are stacked in two distinct layers, offering higher transistor density. The PMOS layer sits atop the NMOS layer, separated by an oxide layer. This configuration minimizes the device footprint and enhances performance through shorter interconnects.

- **Single-Layer CMOS Logic (c):** This illustrates the logic gates (inverter, 2-input NAND, and 2-input NOR) constructed using traditional single-layer CMOS technology. The transistors are arranged horizontally, with the interconnections occupying a larger area.

- **Monolithic 3D CMOS Logic (d):** In this setup, logic gates are created using two layers of transistors (Layer 1 and Layer 2), which reduces the space needed for interconnections. The vertical stacking improves performance by shortening the signal paths, thereby reducing delay.


![Screenshot from 2024-11-26 05-12-08](https://github.com/user-attachments/assets/3c1072a4-96c3-43c3-a4b1-5de09afb9966)

- **Dual Damascene Cu (7nm Technology Node):** This method is used for a 36nm pitch and integrates both vias (vertical connections) and lines (horizontal connections) in one patterning process. Copper (Cu) is the material used for interconnections, but as the dimensions shrink, challenges such as gap filling and maintaining reliability arise.

- **Single Damascene Cu (5nm Technology Node):** This technique, employed for a 28nm pitch, separates the formation of vias and lines into two distinct steps. It tackles the challenges of reduced dimensions by focusing on minimizing resistance (R) in both the lines and vias to ensure optimal performance.

- **Barrier and Via Metal Optimization (3nm Technology Node):** This approach, designed for a 20-24nm pitch, reduces the thickness of barrier layers to lower resistance while maintaining reliable via connections. It plays a crucial role in meeting the performance and scaling demands of advanced technology nodes.

- **Subtractive RIE and Alternative Metals (Sub-18nm Pitch):** At this stage, subtractive Reactive Ion Etching (RIE) is introduced for precise interconnect patterning, and alternative metals like ruthenium (Ru) are used to enhance performance and reliability. These advancements address the challenges of scaling copper interconnects in advanced nodes.

- **Post-Damascene Interconnects (Below 15nm Pitch):** For interconnects at these smaller dimensions, future designs are expected to feature tall, barrier-less structures. This strategy improves electromigration (EM) reliability, ensuring durable and reliable connections as device dimensions continue to shrink, overcoming key scaling challenges.

![Screenshot from 2024-11-26 05-13-18](https://github.com/user-attachments/assets/dc65b024-4aad-429e-b09e-3248324572bd)

The image demonstrates how a selective barrier, typically composed of tantalum nitride (TaN), improves copper interconnects in semiconductor fabrication. This barrier reduces resistance, prevents copper ion migration to enhance reliability, and helps regulate copper thickness. The process involves cleaning the copper surface, applying TaN via atomic layer deposition (ALD), and removing sacrificial layers, making it crucial for ensuring the reliability and performance of advanced semiconductor devices.

![Screenshot from 2024-11-26 05-15-25](https://github.com/user-attachments/assets/e727e173-62cc-4bef-aca3-7e7610718287)
**Back-Side Power Delivery Network (BS-PDN)**

Efficient power delivery is crucial for the performance and reliability of integrated circuits in advanced semiconductor manufacturing. Traditional Front-Side Power Delivery Networks (FS-PDNs) often face significant IR-drop, which can degrade device performance and reliability. To address this, Back-Side Power Delivery Networks (BS-PDNs) offer a more effective solution.

BS-PDNs route the power supply rails to the back of the chip, enabling the use of shorter and wider power lines. This design greatly reduces IR-drop, improving power delivery efficiency. The advantages of BS-PDNs include:

- **Reduced IR-drop:** Lower voltage drops enhance device performance and reliability.
- **Smaller standard cell area:** More efficient power delivery allows for smaller standard cell designs.
- **Improved performance:** The reduced IR-drop leads to faster switching speeds and lower power dissipation.

By adopting BS-PDNs, semiconductor manufacturers can produce high-performance, energy-efficient integrated circuits that meet the demands of modern electronics.

### Setting up ORFS

```
git clone --recursive https://github.com/The-OpenROAD-Project/OpenROAD-flow-scripts
cd OpenROAD-flow-scripts
sudo ./setup.sh
```
![Screenshot from 2024-11-26 04-20-38](https://github.com/user-attachments/assets/8e1b68d9-cef0-444d-9a44-547839edd405)

Build tool on local machine command:
```
./build_openroad.sh --local --threads 2
```
![Screenshot from 2024-11-26 15-38-25](https://github.com/user-attachments/assets/f5c1c076-55f5-4b7d-8072-ec3b830e8ed9)

verify installation
```
source ./env.sh
yosys -help
openroad -help
cd flow
make
make gui_final
```
![Screenshot from 2024-11-26 05-25-50](https://github.com/user-attachments/assets/8fb24c76-05ac-4861-8dea-b871a6090494)
![Screenshot from 2024-11-26 05-29-29](https://github.com/user-attachments/assets/c415ebb8-2530-4c50-ac4c-9f5a2b4a7a93)
![Screenshot from 2024-11-26 05-30-13](https://github.com/user-attachments/assets/eb7b7376-1841-4a63-b9e0-79b7962bed23)

- Create a directory named `vsdbabysoc` inside `OpenROAD-flow-scripts/flow/designs/sky130hd`.

- Copy the `gds`, `include`, `lef`, and `lib` folders from the `VSDBabySoC` folder on your system into the newly created `vsdbabysoc` directory.

- Verify that the following files are included in each respective folder:
  - **`gds` folder:** `avsddac.gds`, `avsdpll.gds`
  - **`include` folder:** `sandpiper.vh`, `sandpiper_gen.vh`, `sp_default.vh`, `sp_verilog.vh`
  - **`lef` folder:** `avsddac.lef`, `avsdpll.lef`
  - **`lib` folder:** `avsddac.lib`, `avsdpll.lib`

- Copy the constraints file `vsdbabysoc_synthesis.sdc` from the `VSDBabySoC` folder into the `vsdbabysoc` directory.

- Also, copy the files `macro.cfg` and `pin_order.cfg` from the `VSDBabySoC` folder into the same `vsdbabysoc` directory.

- Config.mk file:
```
export DESIGN_NICKNAME = vsdbabysoc
export DESIGN_NAME = vsdbabysoc
export PLATFORM    = sky130hd

# export VERILOG_FILES_BLACKBOX = $(DESIGN_HOME)/src/$(DESIGN_NICKNAME)/IPs/*.v
# export VERILOG_FILES = $(sort $(wildcard $(DESIGN_HOME)/src/$(DESIGN_NICKNAME)/*.v))
# Explicitly list the Verilog files for synthesis
export VERILOG_FILES = $(DESIGN_HOME)/src/$(DESIGN_NICKNAME)/vsdbabysoc.v \
                       $(DESIGN_HOME)/src/$(DESIGN_NICKNAME)/rvmyth.v \
                       $(DESIGN_HOME)/src/$(DESIGN_NICKNAME)/clk_gate.v

export SDC_FILE      = $(DESIGN_HOME)/$(PLATFORM)/$(DESIGN_NICKNAME)/vsdbabysoc_synthesis.sdc

export vsdbabysoc_DIR = $(DESIGN_HOME)/$(PLATFORM)/$(DESIGN_NICKNAME)

export VERILOG_INCLUDE_DIRS = $(wildcard $(vsdbabysoc_DIR)/include/)
# export SDC_FILE      = $(wildcard $(vsdbabysoc_DIR)/sdc/*.sdc)
export ADDITIONAL_GDS  = $(wildcard $(vsdbabysoc_DIR)/gds/*.gds.gz)
export ADDITIONAL_LEFS  = $(wildcard $(vsdbabysoc_DIR)/lef/*.lef)
export ADDITIONAL_LIBS = $(wildcard $(vsdbabysoc_DIR)/lib/*.lib)
# export PDN_TCL = $(DESIGN_HOME)/$(PLATFORM)/$(DESIGN_NICKNAME)/pdn.tcl

# Clock Configuration (vsdbabysoc specific)
# export CLOCK_PERIOD = 20.0
export CLOCK_PORT = CLK
export CLOCK_NET = $(CLOCK_PORT)

# Floorplanning Configuration (vsdbabysoc specific)
export FP_PIN_ORDER_CFG = $(wildcard $(DESIGN_DIR)/pin_order.cfg)
# export FP_SIZING = absolute

export DIE_AREA   = 0 0 1600 1600
export CORE_AREA  = 20 20 1590 1590

# Placement Configuration (vsdbabysoc specific)
export MACRO_PLACEMENT_CFG = $(wildcard $(DESIGN_DIR)/macro.cfg)
export PLACE_PINS_ARGS = -exclude left:0-600 -exclude left:1000-1600: -exclude right:* -exclude top:* -exclude bottom:*
# export MACRO_PLACEMENT = $(DESIGN_HOME)/$(PLATFORM)/$(DESIGN_NICKNAME)/macro_placement.cfg

export TNS_END_PERCENT = 100
export REMOVE_ABC_BUFFERS = 1

# Magic Tool Configuration
export MAGIC_ZEROIZE_ORIGIN = 0
export MAGIC_EXT_USE_GDS = 1

# CTS tuning
export CTS_BUF_DISTANCE = 600
export SKIP_GATE_CLONING = 1

# export CORE_UTILIZATION=0.1  # Reduce this value to allow more whitespace for routing.
```

Synthesis reports:
![Screenshot from 2024-11-26 16-09-34](https://github.com/user-attachments/assets/3bb954bb-89de-4a90-9cf0-33660c568024)
![Screenshot from 2024-11-26 16-09-17](https://github.com/user-attachments/assets/ed7ad3ee-285e-40ee-9c11-fe68f55d5492)
![Screenshot from 2024-11-26 16-08-50](https://github.com/user-attachments/assets/b6c16f24-7f4b-412f-82d5-4249bd1001b9)
![Screenshot from 2024-11-26 15-38-25](https://github.com/user-attachments/assets/b440800e-deeb-454d-bb38-42991ab56ae4)
![Screenshot from 2024-11-26 16-47-55](https://github.com/user-attachments/assets/173e03d0-fed5-4ce1-b3c5-a2530a89b621)
![Screenshot from 2024-11-26 16-48-40](https://github.com/user-attachments/assets/5f8cc9d5-a86e-4d7e-b08e-0b78a7850fe5)
![Screenshot from 2024-11-26 16-49-05](https://github.com/user-attachments/assets/978c77bd-00ae-401d-a65f-7e87108834f2)
![Screenshot from 2024-11-26 16-49-21](https://github.com/user-attachments/assets/b49459e1-aa03-4160-ab4b-2f5e4c2939b1)


Commands for floorplan:
```
make DESIGN_CONFIG=./designs/sky130hd/vsdbabysoc/config.mk floorplan
```
[Uploading Screenshot from 2024-11-26 16-45-01.png…]()
![Screenshot from 2024-11-26 16-42-04](https://github.com/user-attachments/assets/1ff801cd-fac8-44e3-a32d-2488ce4d8a62)

```
make DESIGN_CONFIG=./designs/sky130hd/vsdbabysoc/config.mk gui_floorplan
```
![Screenshot from 2024-11-26 16-46-29](https://github.com/user-attachments/assets/b5044344-d5b4-4890-a56c-870324269824)

### Report Screenshots
![Screenshot from 2024-11-26 16-50-13](https://github.com/user-attachments/assets/8dc17593-19e1-410b-864d-6032c9ac9d50)
![Screenshot from 2024-11-26 16-50-51](https://github.com/user-attachments/assets/9dc59204-af06-4551-ae31-dc71f05d65a9)


Commands for Placement:
```
make DESIGN_CONFIG=./designs/sky130hd/vsdbabysoc/config.mk place
```
![Screenshot from 2024-11-26 16-51-58](https://github.com/user-attachments/assets/76d46d48-e300-4086-b468-da4b627e1d38)
![Screenshot from 2024-11-26 16-53-10](https://github.com/user-attachments/assets/88aabd30-03e1-4efe-91b0-d9a65751cede)

```
make DESIGN_CONFIG=./designs/sky130hd/vsdbabysoc/config.mk gui_place
```

</details>







