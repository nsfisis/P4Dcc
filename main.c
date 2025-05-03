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
    printf("%s\n", msg);
    exit(1);
    return 0;
}

int read_all(char* buf) {
    int c;
    int n = 0;
    while ((c = getchar()) != -1) {
        buf[n] = c;
        n += 1;
    }
    return n;
}

#define TK_EOF        0

#define TK_BRACE_L    1
#define TK_BRACE_R    2
#define TK_BRACKET_L  3
#define TK_BRACKET_R  4
#define TK_IDENT      5
#define TK_K_BREAK    6
#define TK_K_CHAR     7
#define TK_K_CONTINUE 8
#define TK_K_ELSE     9
#define TK_K_FOR      10
#define TK_K_IF       11
#define TK_K_INT      12
#define TK_K_LONG     13
#define TK_K_RETURN   14
#define TK_K_SIZEOF   15
#define TK_K_STRUCT   16
#define TK_K_VOID     17
#define TK_L_INT      18
#define TK_L_STR      19
#define TK_MINUS      20
#define TK_PAREN_L    21
#define TK_PAREN_R    22
#define TK_PERCENT    23
#define TK_PLUS       24
#define TK_SEMICOLON  25
#define TK_SLASH      26
#define TK_STAR       27

typedef struct Token {
    int kind;
    char* value;
    int len;
} TOKEN;

TOKEN* tokenize(char* src, int len) {
    TOKEN* tokens = calloc(1024*1024, sizeof(TOKEN));
    TOKEN* tok = tokens;
    int pos = 0;
    while (pos < len) {
        char c = src[pos];
        if (c == '(') {
            pos += 1;
            tok->kind = TK_PAREN_L;
            tok->value = src + pos - 1;
            tok->len = 1;
            tok += 1;
        } else if (c == ')') {
            pos += 1;
            tok->kind = TK_PAREN_R;
            tok->value = src + pos - 1;
            tok->len = 1;
            tok += 1;
        } else if (c == '{') {
            pos += 1;
            tok->kind = TK_BRACE_L;
            tok->value = src + pos - 1;
            tok->len = 1;
            tok += 1;
        } else if (c == '}') {
            pos += 1;
            tok->kind = TK_BRACE_R;
            tok->value = src + pos - 1;
            tok->len = 1;
            tok += 1;
        } else if (c == '[') {
            pos += 1;
            tok->kind = TK_BRACKET_L;
            tok->value = src + pos - 1;
            tok->len = 1;
            tok += 1;
        } else if (c == ']') {
            pos += 1;
            tok->kind = TK_BRACKET_R;
            tok->value = src + pos - 1;
            tok->len = 1;
            tok += 1;
        } else if (c == ';') {
            pos += 1;
            tok->kind = TK_SEMICOLON;
            tok->value = src + pos - 1;
            tok->len = 1;
            tok += 1;
        } else if (c == '+') {
            pos += 1;
            tok->kind = TK_PLUS;
            tok->value = src + pos - 1;
            tok->len = 1;
            tok += 1;
        } else if (c == '-') {
            pos += 1;
            tok->kind = TK_MINUS;
            tok->value = src + pos - 1;
            tok->len = 1;
            tok += 1;
        } else if (c == '*') {
            pos += 1;
            tok->kind = TK_STAR;
            tok->value = src + pos - 1;
            tok->len = 1;
            tok += 1;
        } else if (c == '/') {
            pos += 1;
            tok->kind = TK_SLASH;
            tok->value = src + pos - 1;
            tok->len = 1;
            tok += 1;
        } else if (c == '%') {
            pos += 1;
            tok->kind = TK_PERCENT;
            tok->value = src + pos - 1;
            tok->len = 1;
            tok += 1;
        } else if (isdigit(c)) {
            int start = pos;
            while (isdigit(src[pos])) {
                pos += 1;
            }
            tok->kind = TK_L_INT;
            tok->value = src + start;
            tok->len = pos - start;
            tok += 1;
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
            tok->kind = kind;
            tok->value = src + start;
            tok->len = pos - start;
            tok += 1;
        } else if (isspace(c)) {
            pos += 1;
        } else {
            fatal_error("unknown token");
        }
    }
    return tokens;
}

#define AST_UNKNOWN      0

#define AST_BLOCK        1
#define AST_BINARY_EXPR  2
#define AST_UNARY_EXPR   3
#define AST_FUNC_DECL    4
#define AST_FUNC_DEF     5
#define AST_INT_LIT_EXPR 6
#define AST_PROGRAM      7
#define AST_RETURN_STMT  8
#define AST_TYPE         9

typedef struct AstNode {
    int kind;
    struct AstNode* next;
    struct AstNode* last;
    TOKEN* func_name;
    struct AstNode* func_body;
    int int_value;
    struct AstNode* lhs;
    struct AstNode* rhs;
    int op;
} AST;

AST* ast_new(int kind) {
    AST* ast = calloc(1, sizeof(AST));
    ast->kind = kind;
    return ast;
}

AST* ast_new_list(int kind) {
    if (kind != AST_PROGRAM && kind != AST_BLOCK) {
        fatal_error("ast_new_list: non-list ast");
    }
    AST* ast = ast_new(kind);
    ast->last = ast;
    return ast;
}

typedef struct Parser {
    TOKEN* tokens;
    int pos;
} PARSER;

PARSER* parser_new(TOKEN* tokens) {
    PARSER* p = calloc(1, sizeof(PARSER));
    p->tokens = tokens;
    return p;
}

TOKEN* current_token(PARSER* p) {
    return p->tokens + p->pos;
}

void next_token(PARSER* p) {
    p->pos += 1;
}

int eof(PARSER* p) {
    return current_token(p)->kind != TK_EOF;
}

TOKEN* expect(PARSER*p, int expected) {
    TOKEN* t = current_token(p);
    if (t->kind == expected) {
        next_token(p);
        return p->tokens + p->pos - 1;
    } else {
        char buf[1024];
        sprintf(buf, "expected %d, but got %d", expected, t->kind);
        fatal_error(buf);
    }
}

AST* parse_expr(PARSER* p);

AST* parse_primitive_expr(PARSER* p) {
    TOKEN* t = current_token(p);
    if (t->kind == TK_L_INT) {
        next_token(p);
        AST* e = ast_new(AST_INT_LIT_EXPR);
        char buf[1024];
        memcpy(buf, t->value, t->len);
        buf[t->len] = 0;
        e->int_value = atoi(buf);
        return e;
    } else if (t->kind == TK_PAREN_L) {
        next_token(p);
        AST* e = parse_expr(p);
        expect(p, TK_PAREN_R);
        return e;
    } else {
        fatal_error("parse_expr");
    }
}

AST* parse_multiplicative_expr(PARSER* p) {
    AST* lhs = parse_primitive_expr(p);
    while (1) {
        int op = current_token(p)->kind;
        if (op == TK_STAR || op == TK_SLASH || op == TK_PERCENT) {
            next_token(p);
            AST* rhs = parse_primitive_expr(p);
            AST* tmp = ast_new(AST_BINARY_EXPR);
            tmp->lhs = lhs;
            tmp->op = op;
            tmp->rhs = rhs;
            lhs = tmp;
        } else {
            break;
        }
    }
    return lhs;
}

AST* parse_additive_expr(PARSER* p) {
    AST* lhs = parse_multiplicative_expr(p);
    while (1) {
        int op = current_token(p)->kind;
        if (op == TK_PLUS || op == TK_MINUS) {
            next_token(p);
            AST* rhs = parse_multiplicative_expr(p);
            AST* tmp = ast_new(AST_BINARY_EXPR);
            tmp->lhs = lhs;
            tmp->op = op;
            tmp->rhs = rhs;
            lhs = tmp;
        } else {
            break;
        }
    }
    return lhs;
}

AST* parse_expr(PARSER* p) {
    return parse_additive_expr(p);
}

AST* parse_return_stmt(PARSER* p) {
    expect(p, TK_K_RETURN);
    AST* expr = parse_expr(p);
    expect(p, TK_SEMICOLON);

    AST* ret = ast_new(AST_RETURN_STMT);
    ret->lhs = expr;
    return ret;
}

AST* parse_stmt(PARSER* p) {
    TOKEN* t = current_token(p);
    if (t->kind == TK_K_RETURN) {
        return parse_return_stmt(p);
    } else {
        fatal_error("parse_stmt");
    }
}

AST* parse_block_stmt(PARSER* p) {
    AST* list = ast_new_list(AST_BLOCK);
    expect(p, TK_BRACE_L);
    while (current_token(p)->kind != TK_BRACE_R) {
        AST* n = parse_stmt(p);
        list->last->next = n;
        list->last = n;
    }
    expect(p, TK_BRACE_R);
    return list;
}

AST* parse_func_decl_or_def(PARSER* p) {
    TOKEN* t = current_token(p);
    if (t->kind == TK_K_INT) {
        next_token(p);
        TOKEN* name = expect(p, TK_IDENT);
        expect(p, TK_PAREN_L);
        expect(p, TK_PAREN_R);
        AST* body = parse_block_stmt(p);
        AST* func = ast_new(AST_FUNC_DEF);
        func->func_name = name;
        func->func_body = body;
        return func;
    } else {
        fatal_error("parse_func_decl_or_def: expect type");
    }
}

AST* parse_toplevel(PARSER* p) {
    return parse_func_decl_or_def(p);
}

AST* parse(PARSER* p) {
    AST* list = ast_new_list(AST_PROGRAM);
    while (eof(p)) {
        AST* n = parse_toplevel(p);
        list->last->next = n;
        list->last = n;
    }
    return list;
}

typedef struct CodeGen {
} CODEGEN;

CODEGEN* codegen_new() {
    CODEGEN* g = calloc(1, sizeof(CODEGEN));
    return g;
}

void assert_ast_kind(AST* ast, int kind) {
    if (ast->kind != kind) {
        char buf[1024];
        sprintf(buf, "invalid ast kind: expected %d, but got %d", kind, ast->kind);
        fatal_error(buf);
    }
}

void gen_expr(CODEGEN* g, AST* ast);

void gen_int_lit_expr(CODEGEN* g, AST* ast) {
    assert_ast_kind(ast, AST_INT_LIT_EXPR);
    printf("  push %d\n", ast->int_value);
}

void gen_unary_expr(CODEGEN* g, AST* ast) {
    fatal_error("gen_unary_expr: unimplemented");
}

void gen_binary_expr(CODEGEN* g, AST* ast) {
    gen_expr(g, ast->lhs);
    gen_expr(g, ast->rhs);
    printf("  pop rdi\n");
    printf("  pop rax\n");
    if (ast->op == TK_PLUS) {
        printf("  add rax, rdi\n");
        printf("  push rax\n");
    } else if (ast->op == TK_MINUS) {
        printf("  sub rax, rdi\n");
        printf("  push rax\n");
    } else if (ast->op == TK_STAR) {
        printf("  imul rax, rdi\n");
        printf("  push rax\n");
    } else if (ast->op == TK_SLASH) {
        printf("  cqo\n");
        printf("  idiv rdi\n");
        printf("  push rax\n");
    } else if (ast->op == TK_PERCENT) {
        printf("  cqo\n");
        printf("  idiv rdi\n");
        printf("  push rdx\n");
    } else {
        fatal_error("gen_binary_expr: unknown op");
    }
}

void gen_expr(CODEGEN* g, AST* ast) {
    if (ast->kind == AST_INT_LIT_EXPR) {
        gen_int_lit_expr(g, ast);
    } else if (ast->kind == AST_UNARY_EXPR) {
        gen_unary_expr(g, ast);
    } else if (ast->kind == AST_BINARY_EXPR) {
        gen_binary_expr(g, ast);
    } else {
        fatal_error("gen_expr: unknown expr");
    }
}

void gen_return_stmt(CODEGEN* g, AST* ast) {
    assert_ast_kind(ast, AST_RETURN_STMT);
    gen_expr(g, ast->lhs);
    printf("  pop rax\n");
    printf("  ret\n");
}

void gen_block_stmt(CODEGEN* g, AST* ast) {
    assert_ast_kind(ast, AST_BLOCK);
    gen_return_stmt(g, ast->next);
}

void gen_stmt(CODEGEN* g, AST* ast) {
    gen_block_stmt(g, ast);
}

void gen_func(CODEGEN* g, AST* ast) {
    assert_ast_kind(ast, AST_FUNC_DEF);
    gen_stmt(g, ast->func_body);
    printf("  ret\n");
}

void gen(CODEGEN* g, AST* ast) {
    assert_ast_kind(ast, AST_PROGRAM);
    printf(".intel_syntax noprefix\n");
    printf(".globl main\n");
    printf("main:\n");
    gen_func(g, ast->next);
}

int main() {
    char source[1024*1024];
    memset(source, 0, sizeof(source));
    int source_len = read_all(source);
    TOKEN* tokens = tokenize(source, source_len);

    // for (int i = 0; tokens[i].kind != TK_EOF; i++) {
    //     for (int j = 0; j < tokens[i].len; j++) {
    //         putchar(tokens[i].value[j]);
    //     }
    //     printf("\n");
    // }

    PARSER* parser = parser_new(tokens);
    AST* ast = parse(parser);

    CODEGEN* code_generator = codegen_new();
    gen(code_generator, ast);

    return 0;
}
