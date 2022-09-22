CC = gcc
OBJS = main.c cradle.c data.c message.c
CFLAGS = -Wall -Wextra -pedantic -std=c99
INCLUDES = -I ./includes
#LIBS = -lGL -lglfw -ldl -lm -lmi

a.out: ${OBJS} ./includes
	${CC} ${OBJS} ${INCLUDES} ${CFLAGS} #${LIBS}
