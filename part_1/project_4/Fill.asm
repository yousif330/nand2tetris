// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Fill.asm

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, 
// the screen should be cleared.

//// Replace this comment with your code.


// while (true)
(LOOP0)
// if (key != 0) goto: fill_screen()
    @KBD
    D=M
    @FILL
    D;JNE

// if (key == 0) goto: empty_screen()
    @KBD
    D=M
    @CLEAR
    D;JEQ

// end of loop
    @LOOP0
    0;JMP

// fill_screen()
(FILL)
// index = 0
    @index
    M=0

(LOOP1)
// if (key == 0) goto: main loop
    @KBD
    D=M
    @LOOP0
    D;JEQ

// RAM[SCREEN + i] = -1
    @SCREEN
    D=A
    @index
    D=D+M
    A=D
    M=-1


// index = index + 1
    @index
    M=M+1

// end of fill_loop
    @LOOP1
    0;JMP

// empty_screen()
(CLEAR)
// index = 0
    @index
    M=0

(LOOP2)
// if (key != 0) goto: main loop
    @KBD
    D=M
    @LOOP0
    D;JNE

// RAM[SCREEN + i] = 0
    @SCREEN
    D=A
    @index
    D=D+M
    A=D
    M=0

// index = index + 1
    @index
    M=M+1

// end of fill_loop
    @LOOP2
    0;JMP






