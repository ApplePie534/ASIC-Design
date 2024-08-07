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


