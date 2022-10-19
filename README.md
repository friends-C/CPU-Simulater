# CPU-Simulater

This project simulates the work of CPU.

There are 10 registers in this Fake CPU` r1, r2, r3, r4, r5, r6, r7, r8, r9, r10.

The program gets an input assembly file with ".myasm" extension and executes the instructions.

Instructions allowed` Mov, Add, Sub, Mul, Div, And, Or, Not, Xor, Test, Cmp, Jmp(je, jg, jle, jge, jz, jnz, jnle...)

To Compile print` make

To Run print` ./CPU "file_name"