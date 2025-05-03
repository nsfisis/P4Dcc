cat <<'EOF' > main.c
int main() {
    return 42;
}
EOF

"$p4dcc" < main.c > main.s
gcc -o a.out main.s
set +e
./a.out
exit_code=$?
set -e

test $exit_code -eq 42
