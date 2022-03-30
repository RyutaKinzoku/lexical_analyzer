#Compile the compiler
compiler: lexical_analyzer.c
	gcc -o lexical_analyzer lexical_analyzer.c

#Compile & Run the x86 code
x86: x86code.s
	nasm -f elf64 -o x86code.o x86code.s
	ld -o exe x86code.o