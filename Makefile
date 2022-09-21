CC:= gcc
CXX:= g++
CCFLAGS:=-Isrc/ -O3
CFLAGS:=--std=c99
CXXFLAGS:=--std=c++17
LFLAGS:=
cBinFile:=
cppBinFile:=
ARGS:=

ifeq ($(OS),Windows_NT)
	cBinFile+=./test.c.exe
	cppBinFile+=./test.cpp.exe
else
	cBinFile+=./test.c.elf
	cppBinFile+=./test.cpp.elf
	# If Using GCC Use Address Sanitizers
	ifeq (CC, gcc)
		CFLAGS+=-fsanitize=address -fsanitize=undefined
		LFLAGS+=-lasan -lubsan
	endif
endif

all:
	$(CC) -o $(cBinFile) $(CCFLAGS) $(CFLAGS) $(LFLAGS) test.c src/ini.c
	$(CXX) -o $(cppBinFile) $(CCFLAGS) $(CXXFLAGS) $(LFLAGS) test.cpp src/ini.c

run: all
	$(cBinFile) $(ARGS)
	$(cppBinFile) $(ARGS)
