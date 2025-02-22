HackAssembler: main.o parser.o code.o hashtable.o
	gcc -g main.o parser.o code.o hashtable.o -o HackAssembler
	
main.o:
	gcc -g -c src/main.c -o main.o

parser.o:
	gcc -g -o src/parser.c -o parser.o

hashtable.o:
	gcc -g -c src/hashtable.c -o hashtable.o

code.o:
	gcc -g -o src/code.c -o code.o





parser_test:
	gcc -c -g src/parser.c -o parser.o
	gcc -c -g test/test_parser.c -o test_parser.o
	gcc -g test_parser.o parser.o -o test_parser 
	rm parser.o test_parser.o

code_test:
	gcc -c -g src/code.c -o code.o
	gcc -c -g test/test_code.c -o test_code.o
	gcc -g test_code.o code.o -o test_code
	rm test_code.o code.o
