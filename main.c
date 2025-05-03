int atoi();
void* calloc();
void exit();
int getchar();
int isalnum();
int isalpha();
int isdigit();
int isspace();
void* malloc();
void* memcpy();
void* memset();
int printf();
int putchar();
int sprintf();
int strcmp();
char* strstr();
long strtol();

int fatal_error(char* msg) {
    printf("%s", msg);
    exit(1);
    return 0;
}

int source_len;
char source[1024*1024];

int read_all() {
    int c;
    int n = 0;
    while ((c = getchar()) != -1) {
        source[n] = c;
        n += 1;
    }
    return n;
}

#define TK_EOF        0
#define TK_K_BREAK    1
#define TK_K_CHAR     2
#define TK_K_CONTINUE 3
#define TK_K_ELSE     4
#define TK_K_FOR      5
#define TK_K_IF       6
#define TK_K_INT      7
#define TK_K_LONG     8
#define TK_K_RETURN   9
#define TK_K_SIZEOF   10
#define TK_K_STRUCT   11
#define TK_K_VOID     12
#define TK_IDENT      13
#define TK_L_INT      14
#define TK_L_STR      15 // TODO
#define TK_PAREN_L    16
#define TK_PAREN_R    17
#define TK_BRACE_L    18
#define TK_BRACE_R    19
#define TK_BRACKET_L  20
#define TK_BRACKET_R  21
#define TK_SEMICOLON  22

struct Token {
    int kind;
    char* value;
    int len;
};
typedef struct Token* TOKEN;

struct Token tokens[1024];
int token_len;

int tokenize(char* src, int len) {
    int pos = 0;
    int token_len = 0;
    while (pos < len) {
        char c = src[pos];
        if (c == '(') {
            pos += 1;
            tokens[token_len].kind = TK_PAREN_L;
            tokens[token_len].value = src + pos - 1;
            tokens[token_len].len = 1;
            token_len += 1;
        } else if (c == ')') {
            pos += 1;
            tokens[token_len].kind = TK_PAREN_R;
            tokens[token_len].value = src + pos - 1;
            tokens[token_len].len = 1;
            token_len += 1;
        } else if (c == '{') {
            pos += 1;
            tokens[token_len].kind = TK_BRACE_L;
            tokens[token_len].value = src + pos - 1;
            tokens[token_len].len = 1;
            token_len += 1;
        } else if (c == '}') {
            pos += 1;
            tokens[token_len].kind = TK_BRACE_R;
            tokens[token_len].value = src + pos - 1;
            tokens[token_len].len = 1;
            token_len += 1;
        } else if (c == '[') {
            pos += 1;
            tokens[token_len].kind = TK_BRACKET_L;
            tokens[token_len].value = src + pos - 1;
            tokens[token_len].len = 1;
            token_len += 1;
        } else if (c == ']') {
            pos += 1;
            tokens[token_len].kind = TK_BRACKET_R;
            tokens[token_len].value = src + pos - 1;
            tokens[token_len].len = 1;
            token_len += 1;
        } else if (c == ';') {
            pos += 1;
            tokens[token_len].kind = TK_SEMICOLON;
            tokens[token_len].value = src + pos - 1;
            tokens[token_len].len = 1;
            token_len += 1;
        } else if (isdigit(c)) {
            int start = pos;
            while (isdigit(src[pos])) {
                pos += 1;
            }
            tokens[token_len].kind = TK_L_INT;
            tokens[token_len].value = src + start;
            tokens[token_len].len = pos - start;
            token_len += 1;
        } else if (isalpha(c)) {
            int start = pos;
            while (isalnum(src[pos])) {
                pos += 1;
            }
            int kind;
            if (strstr(src + start, "break") == src + start) {
                kind = TK_K_BREAK;
            } else if (strstr(src + start, "char") == src + start) {
                kind = TK_K_CHAR;
            } else if (strstr(src + start, "continue") == src + start) {
                kind = TK_K_CONTINUE;
            } else if (strstr(src + start, "else") == src + start) {
                kind = TK_K_ELSE;
            } else if (strstr(src + start, "for") == src + start) {
                kind = TK_K_FOR;
            } else if (strstr(src + start, "if") == src + start) {
                kind = TK_K_IF;
            } else if (strstr(src + start, "int") == src + start) {
                kind = TK_K_INT;
            } else if (strstr(src + start, "long") == src + start) {
                kind = TK_K_LONG;
            } else if (strstr(src + start, "return") == src + start) {
                kind = TK_K_RETURN;
            } else if (strstr(src + start, "sizeof") == src + start) {
                kind = TK_K_SIZEOF;
            } else if (strstr(src + start, "struct") == src + start) {
                kind = TK_K_STRUCT;
            } else {
                kind = TK_IDENT;
            }
            tokens[token_len].kind = kind;
            tokens[token_len].value = src + start;
            tokens[token_len].len = pos - start;
            token_len += 1;
        } else if (isspace(c)) {
            pos += 1;
        } else {
            fatal_error("unknown token");
        }
    }
    return token_len;
}

int token_pos;

#define AST_UNKNOWN      0
#define AST_PROGRAM      1
#define AST_FUNC_DECL    2
#define AST_FUNC_DEF     3
#define AST_TYPE         4
#define AST_BLOCK        5
#define AST_RETURN_STMT  6
#define AST_INT_LIT_EXPR 7

struct AstNode {
    int kind;
    struct AstNode* next;
    struct AstNode* last;
    TOKEN func_name;
    struct AstNode* func_body;
    struct AstNode* expr1;
    int int_value;
};
typedef struct AstNode* AST;

int eof() {
    return token_pos < token_len;
}

TOKEN next_tok() {
    return tokens + token_pos;
}

TOKEN expect(int expected) {
    TOKEN t = next_tok();
    if (t->kind == expected) {
        token_pos += 1;
        return tokens + token_pos - 1;
    } else {
        char buf[1024];
        sprintf(buf, "expected %d, but got %d", expected, t->kind);
        fatal_error(buf);
    }
}

AST parse_expr();

AST parse_primitive_expr() {
    TOKEN t = next_tok();
    if (t->kind == TK_L_INT) {
        token_pos += 1;
        AST e = calloc(1, sizeof(struct AstNode));
        e->kind = AST_INT_LIT_EXPR;
        char buf[1024];
        memcpy(buf, t->value, t->len);
        buf[t->len] = 0;
        e->int_value = atoi(buf);
        return e;
    } else {
        fatal_error("parse_expr");
    }
}

AST parse_expr() {
    return parse_primitive_expr();
}

AST parse_return_stmt() {
    expect(TK_K_RETURN);
    AST expr = parse_expr();
    expect(TK_SEMICOLON);

    AST ret = calloc(1, sizeof(struct AstNode));
    ret->kind = AST_RETURN_STMT;
    ret->expr1 = expr;
    return ret;
}

AST parse_stmt() {
    TOKEN t = next_tok();
    if (t->kind == TK_K_RETURN) {
        return parse_return_stmt();
    } else {
        fatal_error("parse_stmt");
    }
}

AST parse_block_stmt() {
    AST list = calloc(1, sizeof(struct AstNode));
    list->kind = AST_BLOCK;
    list->last = list;
    expect(TK_BRACE_L);
    while (next_tok()->kind != TK_BRACE_R) {
        AST n = parse_stmt();
        list->last->next = n;
        list->last = n;
    }
    expect(TK_BRACE_R);
    return list;
}

AST parse_func_decl_or_def() {
    TOKEN t = next_tok();
    if (t->kind == TK_K_INT) {
        token_pos += 1;
        TOKEN name = expect(TK_IDENT);
        expect(TK_PAREN_L);
        expect(TK_PAREN_R);
        AST body = parse_block_stmt();
        AST func = calloc(1, sizeof(struct AstNode));
        func->kind = AST_FUNC_DEF;
        func->func_name = name;
        func->func_body = body;
        return func;
    } else {
        fatal_error("parse_func_decl_or_def: expect type");
    }
}

AST parse_toplevel() {
    return parse_func_decl_or_def();
}

AST parse() {
    AST list = calloc(1, sizeof(struct AstNode));
    list->kind = AST_PROGRAM;
    list->last = list;
    while (eof()) {
        AST n = parse_toplevel();
        list->last->next = n;
        list->last = n;
    }
    return list;
}

void assert_ast_kind(AST ast, int kind) {
    if (ast->kind != kind) {
        char buf[1024];
        sprintf(buf, "invalid ast kind: expected %d, but got %d", kind, ast->kind);
        fatal_error(buf);
    }
}

void gen_int_lit_expr(AST ast) {
    assert_ast_kind(ast, AST_INT_LIT_EXPR);
    printf("  mov rax, %d\n", ast->int_value);
}

void gen_primitive_expr(AST ast) {
    gen_int_lit_expr(ast);
}

void gen_expr(AST ast) {
    gen_primitive_expr(ast);
}

void gen_return_stmt(AST ast) {
    assert_ast_kind(ast, AST_RETURN_STMT);
    gen_expr(ast->expr1);
    printf("  ret\n");
}

void gen_block_stmt(AST ast) {
    assert_ast_kind(ast, AST_BLOCK);
    gen_return_stmt(ast->next);
}

void gen_stmt(AST ast) {
    gen_block_stmt(ast);
}

void gen_func(AST ast) {
    assert_ast_kind(ast, AST_FUNC_DEF);
    gen_stmt(ast->func_body);
    printf("  ret\n");
}

void gen(AST ast) {
    assert_ast_kind(ast, AST_PROGRAM);
    printf(".intel_syntax noprefix\n");
    printf(".globl main\n");
    printf("main:\n");
    gen_func(ast->next);
}

int main() {
    source_len = read_all();
    token_len = tokenize(source, source_len);

    // for (int i = 0; tokens[i].kind != TK_EOF; i++) {
    //     for (int j = 0; j < tokens[i].len; j++) {
    //         putchar(tokens[i].value[j]);
    //     }
    //     printf("\n");
    // }

    AST ast = parse();
    gen(ast);

    return 0;
}
