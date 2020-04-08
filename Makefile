# Rules for building each .o
all: part1 part2

part1: part1.c
	gcc -g -o part1 part1.c
part2: part2.c
	gcc -g -o part2 part2.c assign3p2Driver.c assign3p2.h
