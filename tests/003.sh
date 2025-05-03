cat <<'EOF' > main.c
int main() {
    return 2*3+4*5;
}
EOF

"$p4dcc" < main.c > main.s
if [[ $? -ne 0 ]]; then
    cat main.s >&2
    exit 1
fi
gcc -Wl,-z,noexecstack -o a.out main.s
./a.out
exit_code=$?

expected=26

if [[ ! $exit_code -eq $expected ]]; then
    echo "expected $expected, but $exit_code" >&2
    exit 1
fi
