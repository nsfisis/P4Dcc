CFLAGS := "-Wno-builtin-declaration-mismatch"

all: build

build N="1":
    #!/usr/bin/env bash
    if [[ {{N}} = 1 ]]; then
        gcc -g -O0 -o p4dcc main.c {{CFLAGS}}
    else
        ./p4dcc < main.c > main{{N}}.s
        gcc -s -Wl,-z,noexecstack -o p4dcc{{N}} main{{N}}.s
    fi

build-upto-10:
    just build 1
    just build 2
    just build 3
    just build 4
    just build 5
    just build 6
    just build 7
    just build 8
    just build 9
    just build 10

test-self-hosted:
    diff -u ./p4dcc2 ./p4dcc3
    diff -u ./p4dcc3 ./p4dcc4
    diff -u ./p4dcc4 ./p4dcc5
    diff -u ./p4dcc5 ./p4dcc6
    diff -u ./p4dcc6 ./p4dcc7
    diff -u ./p4dcc7 ./p4dcc8
    diff -u ./p4dcc8 ./p4dcc9
    diff -u ./p4dcc9 ./p4dcc10

test TESTCASE="all" $BIN="p4dcc": build
    #!/usr/bin/env bash
    if [[ {{TESTCASE}} = all ]]; then
        bash tests/all.sh
    else
        bash tests/run.sh {{TESTCASE}}
    fi
    if [[ $BIN = p4dcc ]]; then
        just build2
    fi

clean:
    rm p4dcc*
    rm -rf tests/tmp
