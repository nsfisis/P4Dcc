CFLAGS := "-Wno-builtin-declaration-mismatch"

all: build

build:
    gcc -o p4dcc main.c {{CFLAGS}}

test TESTCASE="all": build
    #!/usr/bin/env bash
    if [[ {{TESTCASE}} = all ]]; then
        bash tests/all.sh
    else
        bash tests/run.sh {{TESTCASE}}
    fi

clean:
    rm p4dcc
    rm -rf tests/tmp
