CFLAGS := "-Wno-builtin-declaration-mismatch"

all: build

build:
    gcc main.c {{CFLAGS}}

clean:
    rm a.out
