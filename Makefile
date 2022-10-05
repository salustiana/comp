CC = gcc
OBJS = main.c parser.c cradle.c data.c message.c
CFLAGS = -Wall -Wextra -pedantic -std=c99
INCLUDES = -I ./includes
src = src.l
#LIBS = -lGL -lglfw -ldl -lm -lmi

a.out: ${OBJS} ./includes
	${CC} ${OBJS} ${INCLUDES} ${CFLAGS} #${LIBS}

compile: ${OBJS} ${src} ./includes
	${CC} ${OBJS} ${INCLUDES} ${CFLAGS} #${LIBS}
	cat ${src} | ./a.out > lout.s && as --32 lout.s -o lout.o && ld -m elf_i386 lout.o -o lout
