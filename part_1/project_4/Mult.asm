// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
// The algorithm is based on repetitive addition.

//// Replace this comment with your code.

// sum = 0
@sum
M=0

// i = 0
@i
M=0

// while (i < R1)
(LOOP)
@R1
D=M
@i
D=M-D
@STOP
D;JEQ

// sum = sum + R0
@sum
D=M
@R0
D=D+M
@sum
M=D

// i = i + 1
@i
M=M+1

// end of loop
@LOOP
0;JMP
(STOP)

//R2 = sum
@sum
D=M
@R2
M=D

// END
(END)
@END
0;JMP
