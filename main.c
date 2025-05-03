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

void fatal_error(char* msg) {
    printf("%s\n", msg);
    exit(1);
}

void todo() {
    fatal_error("todo");
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

#define TK_ASSIGN     1
#define TK_BRACE_L    2
#define TK_BRACE_R    3
#define TK_BRACKET_L  4
#define TK_BRACKET_R  5
#define TK_EQ         6
#define TK_GE         7
#define TK_GT         8
#define TK_IDENT      9
#define TK_K_BREAK    10
#define TK_K_CHAR     11
#define TK_K_CONTINUE 12
#define TK_K_ELSE     13
#define TK_K_FOR      14
#define TK_K_IF       15
#define TK_K_INT      16
#define TK_K_LONG     17
#define TK_K_RETURN   18
#define TK_K_SIZEOF   19
#define TK_K_STRUCT   20
#define TK_K_VOID     21
#define TK_LE         22
#define TK_LT         23
#define TK_L_INT      24
#define TK_L_STR      25
#define TK_MINUS      26
#define TK_NE         27
#define TK_NOT        28
#define TK_PAREN_L    29
#define TK_PAREN_R    30
#define TK_PERCENT    31
#define TK_PLUS       32
#define TK_SEMICOLON  33
#define TK_SLASH      34
#define TK_STAR       35

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
        } else if (c == '!') {
            pos += 1;
            if (src[pos] == '=') {
                pos += 1;
                tok->kind = TK_NE;
                tok->value = src + pos - 2;
                tok->len = 2;
                tok += 1;
            } else {
                tok->kind = TK_NOT;
                tok->value = src + pos - 1;
                tok->len = 1;
                tok += 1;
            }
        } else if (c == '=') {
            pos += 1;
            if (src[pos] == '=') {
                pos += 1;
                tok->kind = TK_EQ;
                tok->value = src + pos - 2;
                tok->len = 2;
                tok += 1;
            } else {
                tok->kind = TK_ASSIGN;
                tok->value = src + pos - 1;
                tok->len = 1;
                tok += 1;
            }
        } else if (c == '<') {
            pos += 1;
            if (src[pos] == '=') {
                pos += 1;
                tok->kind = TK_LE;
                tok->value = src + pos - 2;
                tok->len = 2;
                tok += 1;
            } else {
                tok->kind = TK_LT;
                tok->value = src + pos - 1;
                tok->len = 1;
                tok += 1;
            }
        } else if (c == '>') {
            pos += 1;
            if (src[pos] == '=') {
                pos += 1;
                tok->kind = TK_GE;
                tok->value = src + pos - 2;
                tok->len = 2;
                tok += 1;
            } else {
                tok->kind = TK_GT;
                tok->value = src + pos - 1;
                tok->len = 1;
                tok += 1;
            }
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

#define TY_UNKNOWN 0

#define TY_CHAR    1
#define TY_INT     2
#define TY_LONG    3
#define TY_VOID    4
#define TY_STRUCT  5
#define TY_ARR     6
#define TY_PTR     7

typedef struct Type {
    int kind;
} TYPE;

TYPE* type_new(int kind) {
    TYPE* ty = calloc(1, sizeof(TYPE));
    ty->kind = kind;
    return ty;
}

#define AST_UNKNOWN      0

#define AST_ASSIGN_EXPR  1
#define AST_BINARY_EXPR  2
#define AST_BLOCK        3
#define AST_EXPR_STMT    4
#define AST_FUNC_DECL    5
#define AST_FUNC_DEF     6
#define AST_INT_LIT_EXPR 7
#define AST_LVAR         8
#define AST_PROGRAM      9
#define AST_RETURN_STMT  10
#define AST_TYPE         11
#define AST_UNARY_EXPR   12
#define AST_VAR_DECL     13

typedef struct AstNode {
    int kind;
    struct AstNode* next;
    struct AstNode* last;
    TOKEN* name;
    struct AstNode* func_body;
    int int_value;
    struct AstNode* expr1;
    struct AstNode* expr2;
    struct AstNode* expr3;
    int op;
    TYPE* var_ty;
    int var_index;
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

AST* ast_new_unary_expr(int op, AST* operand) {
    AST* e = ast_new(AST_UNARY_EXPR);
    e->op = op;
    e->expr1 = operand;
    return e;
}

AST* ast_new_binary_expr(int op, AST* lhs, AST* rhs) {
    AST* e = ast_new(AST_BINARY_EXPR);
    e->op = op;
    e->expr1 = lhs;
    e->expr2 = rhs;
    return e;
}

AST* ast_new_assign_expr(int op, AST* lhs, AST* rhs) {
    AST* e = ast_new(AST_ASSIGN_EXPR);
    e->op = op;
    e->expr1 = lhs;
    e->expr2 = rhs;
    return e;
}

typedef struct Parser {
    TOKEN* tokens;
    int pos;
    TOKEN** locals;
    int n_locals;
} PARSER;

PARSER* parser_new(TOKEN* tokens) {
    PARSER* p = calloc(1, sizeof(PARSER));
    p->tokens = tokens;
    return p;
}

TOKEN* peek_token(PARSER* p) {
    return p->tokens + p->pos;
}

TOKEN* next_token(PARSER* p) {
    p->pos += 1;
    return p->tokens + p->pos - 1;
}

int eof(PARSER* p) {
    return peek_token(p)->kind != TK_EOF;
}

TOKEN* expect(PARSER* p, int expected) {
    TOKEN* t = next_token(p);
    if (t->kind == expected) {
        return t;
    }

    char buf[1024];
    sprintf(buf, "expected %d, but got %d", expected, t->kind);
    fatal_error(buf);
}

AST* parse_expr(PARSER* p);

AST* parse_primary_expr(PARSER* p) {
    TOKEN* t = next_token(p);
    if (t->kind == TK_L_INT) {
        AST* e = ast_new(AST_INT_LIT_EXPR);
        char buf[1024];
        memcpy(buf, t->value, t->len);
        buf[t->len] = 0;
        e->int_value = atoi(buf);
        return e;
    } else if (t->kind == TK_PAREN_L) {
        AST* e = parse_expr(p);
        expect(p, TK_PAREN_R);
        return e;
    } else if (t->kind == TK_IDENT) {
        AST* e = ast_new(AST_LVAR);

        int i;
        for (i = 0; i < p->n_locals; i++) {
            char* a = calloc(1024, sizeof(char));
            char* b = calloc(1024, sizeof(char));
            memcpy(a, p->locals[i]->value, p->locals[i]->len);
            memcpy(b, t->value, t->len);
            if (strcmp(a, b) == 0) {
                break;
            }
        }
        if (i == p->n_locals) {
            char buf[1024];
            sprintf(buf, "undefined variable: %s", t->value);
            fatal_error(buf);
        }

        e->name = t;
        e->var_index = i;
        return e;
    } else {
        char buf[1024];
        sprintf(buf, "expected primary expression, but got %d", t->kind);
        fatal_error(buf);
    }
}

AST* parse_prefix_expr(PARSER* p) {
    int op = peek_token(p)->kind;
    if (op == TK_MINUS) {
        next_token(p);
        AST* operand = parse_prefix_expr(p);
        AST* lhs = ast_new(AST_INT_LIT_EXPR);
        lhs->int_value = 0;
        return ast_new_binary_expr(op, lhs, operand);
    }
    return parse_primary_expr(p);
}

AST* parse_multiplicative_expr(PARSER* p) {
    AST* lhs = parse_prefix_expr(p);
    while (1) {
        int op = peek_token(p)->kind;
        if (op == TK_STAR || op == TK_SLASH || op == TK_PERCENT) {
            next_token(p);
            AST* rhs = parse_prefix_expr(p);
            lhs = ast_new_binary_expr(op, lhs, rhs);
        } else {
            break;
        }
    }
    return lhs;
}

AST* parse_additive_expr(PARSER* p) {
    AST* lhs = parse_multiplicative_expr(p);
    while (1) {
        int op = peek_token(p)->kind;
        if (op == TK_PLUS || op == TK_MINUS) {
            next_token(p);
            AST* rhs = parse_multiplicative_expr(p);
            lhs = ast_new_binary_expr(op, lhs, rhs);
        } else {
            break;
        }
    }
    return lhs;
}

AST* parse_relational_expr(PARSER* p) {
    AST* lhs = parse_additive_expr(p);
    while (1) {
        int op = peek_token(p)->kind;
        if (op == TK_LT || op == TK_LE) {
            next_token(p);
            AST* rhs = parse_additive_expr(p);
            lhs = ast_new_binary_expr(op, lhs, rhs);
        } else if (op == TK_GT) {
            next_token(p);
            AST* rhs = parse_additive_expr(p);
            lhs = ast_new_binary_expr(TK_LT, rhs, lhs);
        } else if (op == TK_GE) {
            next_token(p);
            AST* rhs = parse_additive_expr(p);
            lhs = ast_new_binary_expr(TK_GE, rhs, lhs);
        } else {
            break;
        }
    }
    return lhs;
}

AST* parse_equality_expr(PARSER* p) {
    AST* lhs = parse_relational_expr(p);
    while (1) {
        int op = peek_token(p)->kind;
        if (op == TK_EQ || op == TK_NE) {
            next_token(p);
            AST* rhs = parse_relational_expr(p);
            lhs = ast_new_binary_expr(op, lhs, rhs);
        } else {
            break;
        }
    }
    return lhs;
}

AST* parse_assignment_expr(PARSER *p) {
    AST* lhs = parse_equality_expr(p);
    while (1) {
        int op = peek_token(p)->kind;
        if (op == TK_ASSIGN) {
            next_token(p);
            AST* rhs = parse_equality_expr(p);
            lhs = ast_new_assign_expr(op, lhs, rhs);
        } else {
            break;
        }
    }
    return lhs;
}

AST* parse_expr(PARSER* p) {
    return parse_assignment_expr(p);
}

AST* parse_return_stmt(PARSER* p) {
    expect(p, TK_K_RETURN);
    AST* expr = parse_expr(p);
    expect(p, TK_SEMICOLON);

    AST* ret = ast_new(AST_RETURN_STMT);
    ret->expr1 = expr;
    return ret;
}

AST* parse_var_decl(PARSER* p) {
    TOKEN* t = peek_token(p);
    if (t->kind == TK_K_INT) {
        next_token(p);
        TYPE* ty = type_new(TK_K_INT);
        TOKEN* name = expect(p, TK_IDENT);
        AST* decl = ast_new(AST_VAR_DECL);
        expect(p, TK_SEMICOLON);
        decl->var_ty = ty;
        decl->name = name;

        for (int i = 0; i < p->n_locals; i++) {
            if (p->locals[i] == name) {
                char buf[1024];
                sprintf(buf, "parse_var_decl: %s redeclared", name);
                fatal_error(buf);
            }
        }
        p->locals[p->n_locals] = name;
        p->n_locals += 1;

        return decl;
    } else {
        fatal_error("parse_var_decl: unknown type");
    }
}

AST* parse_expr_stmt(PARSER* p) {
    AST* e = parse_expr(p);
    expect(p, TK_SEMICOLON);
    AST* stmt = ast_new(AST_EXPR_STMT);
    stmt->expr1 = e;
    return stmt;
}

AST* parse_stmt(PARSER* p) {
    TOKEN* t = peek_token(p);
    if (t->kind == TK_K_RETURN) {
        return parse_return_stmt(p);
    } else if (t->kind == TK_K_INT) {
        return parse_var_decl(p);
    } else {
        return parse_expr_stmt(p);
    }
}

AST* parse_block_stmt(PARSER* p) {
    AST* list = ast_new_list(AST_BLOCK);
    expect(p, TK_BRACE_L);
    while (peek_token(p)->kind != TK_BRACE_R) {
        AST* stmt = parse_stmt(p);
        list->last->next = stmt;
        list->last = stmt;
    }
    expect(p, TK_BRACE_R);
    return list;
}

void parse_enter_func(PARSER* p) {
    p->locals = calloc(32, sizeof(TOKEN*));
    p->n_locals = 0;
}

AST* parse_func_decl_or_def(PARSER* p) {
    TOKEN* t = peek_token(p);
    if (t->kind == TK_K_INT) {
        next_token(p);
        parse_enter_func(p);
        TOKEN* name = expect(p, TK_IDENT);
        expect(p, TK_PAREN_L);
        expect(p, TK_PAREN_R);
        AST* body = parse_block_stmt(p);
        AST* func = ast_new(AST_FUNC_DEF);
        func->name = name;
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

#define GEN_LVAL 0
#define GEN_RVAL 1

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

void gen_expr(CODEGEN* g, AST* ast, int gen_mode);
void gen_stmt(CODEGEN* g, AST* ast);

void gen_func_prologue(CODEGEN* g, AST* ast) {
    printf("  push rbp\n");
    printf("  mov rbp, rsp\n");
    // TODO 16
    printf("  sub rsp, 16\n");
}

void gen_func_epilogue(CODEGEN* g, AST* ast) {
    printf("  mov rsp, rbp\n");
    printf("  pop rbp\n");
    printf("  ret\n");
}

void gen_int_lit_expr(CODEGEN* g, AST* ast) {
    assert_ast_kind(ast, AST_INT_LIT_EXPR);
    printf("  push %d\n", ast->int_value);
}

void gen_unary_expr(CODEGEN* g, AST* ast) {
    fatal_error("gen_unary_expr: unimplemented");
}

void gen_binary_expr(CODEGEN* g, AST* ast) {
    gen_expr(g, ast->expr1, GEN_RVAL);
    gen_expr(g, ast->expr2, GEN_RVAL);
    printf("  pop rdi\n");
    printf("  pop rax\n");
    if (ast->op == TK_PLUS) {
        printf("  add rax, rdi\n");
    } else if (ast->op == TK_MINUS) {
        printf("  sub rax, rdi\n");
    } else if (ast->op == TK_STAR) {
        printf("  imul rax, rdi\n");
    } else if (ast->op == TK_SLASH) {
        printf("  cqo\n");
        printf("  idiv rdi\n");
    } else if (ast->op == TK_PERCENT) {
        printf("  cqo\n");
        printf("  idiv rdi\n");
        printf("  mov rax, rdx\n");
    } else if (ast->op == TK_EQ) {
        printf("  cmp rax, rdi\n");
        printf("  sete al\n");
        printf("  movzb rax, al\n");
    } else if (ast->op == TK_NE) {
        printf("  cmp rax, rdi\n");
        printf("  setne al\n");
        printf("  movzb rax, al\n");
    } else if (ast->op == TK_LT) {
        printf("  cmp rax, rdi\n");
        printf("  setl al\n");
        printf("  movzb rax, al\n");
    } else if (ast->op == TK_LE) {
        printf("  cmp rax, rdi\n");
        printf("  setle al\n");
        printf("  movzb rax, al\n");
    } else {
        fatal_error("gen_binary_expr: unknown op");
    }
    printf("  push rax\n");
}

void gen_assign_expr(CODEGEN* g, AST* ast) {
    assert_ast_kind(ast, AST_ASSIGN_EXPR);
    gen_expr(g, ast->expr1, GEN_LVAL);
    gen_expr(g, ast->expr2, GEN_RVAL);
    printf("  pop rdi\n");
    printf("  pop rax\n");
    if (ast->op == TK_ASSIGN) {
        printf("  mov [rax], rdi\n");
        printf("  push rdi\n");
    } else {
        todo();
    }
}

void gen_lvar(CODEGEN* g, AST* ast, int gen_mode) {
    assert_ast_kind(ast, AST_LVAR);
    int offset = 8 + ast->var_index * 8;
    printf("  mov rax, rbp\n");
    printf("  sub rax, %d\n", offset);
    printf("  push rax\n");
    if (gen_mode == GEN_RVAL) {
        printf("  pop rax\n");
        printf("  push [rax]\n");
    }
}

void gen_expr(CODEGEN* g, AST* ast, int gen_mode) {
    if (ast->kind == AST_INT_LIT_EXPR) {
        gen_int_lit_expr(g, ast);
    } else if (ast->kind == AST_UNARY_EXPR) {
        gen_unary_expr(g, ast);
    } else if (ast->kind == AST_BINARY_EXPR) {
        gen_binary_expr(g, ast);
    } else if (ast->kind == AST_ASSIGN_EXPR) {
        gen_assign_expr(g, ast);
    } else if (ast->kind == AST_LVAR) {
        gen_lvar(g, ast, gen_mode);
    } else {
        fatal_error("gen_expr: unknown expr");
    }
}

void gen_return_stmt(CODEGEN* g, AST* ast) {
    assert_ast_kind(ast, AST_RETURN_STMT);
    gen_expr(g, ast->expr1, GEN_RVAL);
    printf("  pop rax\n");
    gen_func_epilogue(g, ast);
}

void gen_expr_stmt(CODEGEN* g, AST* ast) {
    gen_expr(g, ast->expr1, GEN_RVAL);
    printf("  pop rax\n");
}

void gen_var_decl(CODEGEN* g, AST* ast) {
}

void gen_block_stmt(CODEGEN* g, AST* ast) {
    assert_ast_kind(ast, AST_BLOCK);
    AST* stmt = ast->next;
    while (stmt) {
        gen_stmt(g, stmt);
        stmt = stmt->next;
    }
}

void gen_stmt(CODEGEN* g, AST* ast) {
    if (ast->kind == AST_BLOCK) {
        gen_block_stmt(g, ast);
    } else if (ast->kind == AST_RETURN_STMT) {
        gen_return_stmt(g, ast);
    } else if (ast->kind == AST_EXPR_STMT) {
        gen_expr_stmt(g, ast);
    } else if (ast->kind == AST_VAR_DECL) {
        gen_var_decl(g, ast);
    } else {
        char buf[1024];
        sprintf(buf, "gen_stmt: expected statement ast, but got %d", ast->kind);
        fatal_error(buf);
    }
}

void gen_func(CODEGEN* g, AST* ast) {
    assert_ast_kind(ast, AST_FUNC_DEF);
    gen_func_prologue(g, ast);
    gen_stmt(g, ast->func_body);
    gen_func_epilogue(g, ast);
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
