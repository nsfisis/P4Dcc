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

build N: build
    ./p4dcc < main.c > main{{N}}.s
    gcc -Wl,-z,noexecstack -o p4dcc{{N}} main{{N}}.s

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
