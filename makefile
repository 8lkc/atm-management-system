launch: build
	./atm.exe

build:
	gcc library/source/*.c main.c -o atm.exe
