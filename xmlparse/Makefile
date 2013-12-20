.SUFFIXES : .cpp .o

CC = g++
CFLAGS = -Wall -g
TARGET = xmltest

SRCS = ./tinystr.cpp \
	   ./tinyxml.cpp \
	   ./tinyxmlerror.cpp \
	   ./tinyxmlparser.cpp \
	   ./xmltest.cpp

OBJS = ./tinystr.o \
	   ./tinyxml.o \
	   ./tinyxmlerror.o \
	   ./tinyxmlparser.o \
	   ./xmltest.o

all: $(OBJS) $(SRCS) Makefile
	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS)

./%.o: ./%.c
	$(CC) -c ./${*F}.cpp -o ./${*F}.o $(CFLAGS)

clean:
	rm -rf ./$(TARGET) $(OBJS)

depend:

