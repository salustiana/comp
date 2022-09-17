CC = gcc
OBJS = main.o cradle.o
TESTOBJS = test.c cradle.o
CFLAGS = -Wall -Wextra -pedantic -std=c99
INCLUDES = -I ./includes
#LIBS = -lGL -lglfw -ldl -lm -lmi

a.out: ${OBJS} ./includes
	${CC} ${OBJS} ${INCLUDES} ${CFLAGS} #${LIBS}

main.o: main.c
	${CC} -c main.c ${INCLUDES}

cradle.o: cradle.c
	${CC} -c cradle.c ${INCLUDES}

test.out: ${OBJS} ./includes
	${CC} -o test.out ${TESTOBJS} ${INCLUDES} ${CFLAGS} #${LIBS}
