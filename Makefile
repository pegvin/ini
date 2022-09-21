CC := gcc
CFLAGS := -Isrc/ --std=c99
LFLAGS :=
binFile := test.elf
ARGS :=

ifeq ($(OS),Windows_NT)
	binFile := test.exe
else
	# If Using GCC Use Address Sanitizers
	ifeq (CC, gcc)
		CFLAGS += -fsanitize=address -fsanitize=undefined
		LFLAGS += -lasan -lubsan
	endif
endif

all:
	clang -o $(binFile) $(CFLAGS) $(LFLAGS) test.c src/ini.c

run: all
	./$(binFile) $(ARGS)
