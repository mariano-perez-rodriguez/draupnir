
CC = g++

CFLAGS  = -v
CFLAGS += -fmessage-length=0
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Wconversion
CFLAGS += -pedantic
CFLAGS += -std=gnu++1y

LD = g++

LDFLAGS =

draupnir: main.o
	${LD} ${LDFLAGS} -o "draupnir"  "main.o"

main.o: main.cpp
	${CC} ${CFLAGS} -c -o "main.o"  "main.cpp"


.PHONY: clean
clean:
	-@rm -f *.o draupnir
