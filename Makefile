# Rules for building each .o
part2: part2.c
	gcc -g -o part2 part2.c assign3p2Driver.c assign3p2.h
