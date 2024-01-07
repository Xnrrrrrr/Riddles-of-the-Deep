ifeq ($(OS),Windows_NT)
	RUN = start
	KILL = wmic process where "name='RotD.exe'" delete || true
	EXE = .exe
else
	RUN = wine
	KILL = pkill RotD || true
	EXE =
endif

CC = gcc
CFLAGS = -Wall -o
LIBS = -LC:/msys64/mingw64/lib -lncursesw

all: clean compile start

compile:
	$(CC) $(CFLAGS) RotD$(EXE) islands.c test.c $(LIBS)

start:
	$(RUN) RotD$(EXE)

clean:
	$(KILL)