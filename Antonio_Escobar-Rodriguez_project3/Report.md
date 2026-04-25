# Programming Project 3 Report

## How to run code
1. Open the terminal and type in “make”
2. To the program type in. “./ARM”

## How the code works
The program grabs a line from the input file, and extracts the operation, "S" (if there's any) or a condition and operands. Once the line is extracted the program will perform a calculation depending on what operation it is, then it will print out the register array & memory array. if there is "S" in front of the operation, it will update the flags, or if there is a condition like "LT" it will perform the execution if conditions are meet.

## Operations
- ADD (): adds two operands together and send the result to the destination register.
- SUB (): subtracts two operands together & send the result to the destination register.
- AND (): compares the bits of the two operands, returns 1 if both bits are 1 and send the result to the destination register.
- ORR (): compares the bits of the two operands, returns 1 if one of the bits are 1 and send the result to the destination register.
- EOR (): compares the bits of the two operands, returns 1 if both bits are not the same and send the result to the destination register.
- CMP (): subtracts two operands, updates flags.
- MOV (): moves value to the destination register.
- LDR (): load a value from memory to a register.
- STR (): store a value from register to memory.
- LSL (): shifts each bit left by one bit positon, shift into the LSB.
- LSR (): logical shift right, shifts each bit right by one bit positon, shift 0 into the MSB.
- MVN (): same as MOV, but inverts the bits

## Flags & conditions

- N: If the 31st bit of the result is set, this flag becomes 1.
- Z: If the result of the operaton is 0, this flag becomes 1.
- C: This flag becomes 1 if there is a carry out of the MSB for addition. As for Substraction the flag becomes 1 when the result has no borrow.
- V: In addition if the signs of the operands are the same, but the result has a opposite sign, this flag becomes 1.

| Condition | Execution Condition |
|-----------|---------------------|
| GT (Greater Than) | Z == 0 && N == V |
| GE (Greater Equal) | N == V |
| LT (Less Than) | N != V |
| LE (Less Equal) | Z == 1 or N != V |
| EQ (Equal) | Z == 1 |
| NE (Not Equal) | Z == 0 |

```txt
MOV R0,#0x14
MOV R1,#0xA
CMP R0, R1
ADDGT R2, R0, R1
ADDEQ R3, R0, R1
SUBLT R4, R0, R1
ADDS R0,R1,R2
CMP R2, #50 
ANDGT R3, R2, #1
ORREQ R4, R2, #2
EORLT R5, R2, #3
ORRS R3,R2,#15
CMP R5, #0x1D
LSRGE R7, R5, #2
LSLNE R8, R5, #3
CMP R8, R9
MOVGT R10, R8
MVNEQ R11, R8
MOV R6,#0x104
CMP R7, R2 
LDRGT R3, [R6] 
STRNE R3, [R6] 
CMP R2, R7
LDRGT R9, [R6]
STRNE R3, [R6]
```