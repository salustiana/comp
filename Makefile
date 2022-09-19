CC = gcc
OBJS = main.o cradle.o hashtable.o
TESTOBJS = test.c cradle.o hashtable.o
CFLAGS = -Wall -Wextra -pedantic -std=c99
INCLUDES = -I ./includes
#LIBS = -lGL -lglfw -ldl -lm -lmi

a.out: ${OBJS} ./includes
	${CC} ${OBJS} ${INCLUDES} ${CFLAGS} #${LIBS}

main.o: main.c
	${CC} -c main.c ${INCLUDES}

cradle.o: cradle.c
	${CC} -c cradle.c ${INCLUDES}

hashtable.o: hashtable.c
	${CC} -c hashtable.c ${INCLUDES}

test.out: ${TESTOBJS} ./includes
	${CC} -o test.out ${TESTOBJS} ${INCLUDES} ${CFLAGS} #${LIBS}
