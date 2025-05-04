CFLAGS := "-Wno-builtin-declaration-mismatch"

all: build

build:
    gcc -g -O0 -o p4dcc main.c {{CFLAGS}}

build2: build
    ./p4dcc < main.c > main.s
    gcc -Wl,-z,noexecstack -o p4dcc2 main.s

build3: build2
    ./p4dcc2 < main.c > main.s
    gcc -Wl,-z,noexecstack -o p4cc3 main.s

test TESTCASE="all" $BIN="p4dcc": build
    #!/usr/bin/env bash
    if [[ {{TESTCASE}} = all ]]; then
        bash tests/all.sh
    else
        bash tests/run.sh {{TESTCASE}}
    fi

clean:
    rm p4dcc*
    rm -rf tests/tmp
