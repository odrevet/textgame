EXEC=target
CC=gcc
CFLAGS= -W -Wall -ansi -pedantic -std=c99
LDFLAGS=

TARGET	    := $(notdir $(CURDIR))
SOURCEDIR   := .
SOURCE      := $(foreach DIR,$(SOURCEDIR),$(wildcard $(DIR)/*.c)) 

DEBUG=no
ifeq ($(DEBUG),yes)
	CXX += -DDEBUG -g
	CC += -DDEBUG -g
endif

#---------------------------------------------------------------------------------

#inference
%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

#build target
all: $(EXEC)

target: $(OBJ)
	$(CC) $(SOURCE) -o $(TARGET) $^ $(LDFLAGS) $(CFLAGS)

#mingw target
mingw: LDFLAGS := -lmingw32 -static-libgcc $(LDFLAGS)
mingw: TARGET := $(TARGET).exe
mingw: $(EXEC)

#clean and co
.PHONY: clean mrproper

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
