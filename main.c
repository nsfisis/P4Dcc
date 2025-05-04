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

#define NULL 0

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

#define TK_AND        1
#define TK_ASSIGN     2
#define TK_BRACE_L    3
#define TK_BRACE_R    4
#define TK_BRACKET_L  5
#define TK_BRACKET_R  6
#define TK_COMMA      7
#define TK_EQ         8
#define TK_GE         9
#define TK_GT         10
#define TK_IDENT      11
#define TK_K_BREAK    12
#define TK_K_CHAR     13
#define TK_K_CONTINUE 14
#define TK_K_ELSE     15
#define TK_K_FOR      16
#define TK_K_IF       17
#define TK_K_INT      18
#define TK_K_LONG     19
#define TK_K_RETURN   20
#define TK_K_SIZEOF   21
#define TK_K_STRUCT   22
#define TK_K_VOID     23
#define TK_LE         24
#define TK_LT         25
#define TK_L_INT      26
#define TK_L_STR      27
#define TK_MINUS      28
#define TK_NE         29
#define TK_NOT        30
#define TK_PAREN_L    31
#define TK_PAREN_R    32
#define TK_PERCENT    33
#define TK_PLUS       34
#define TK_SEMICOLON  35
#define TK_SLASH      36
#define TK_STAR       37

typedef struct Token {
    int kind;
    char* value;
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
            tok += 1;
        } else if (c == ')') {
            pos += 1;
            tok->kind = TK_PAREN_R;
            tok += 1;
        } else if (c == '{') {
            pos += 1;
            tok->kind = TK_BRACE_L;
            tok += 1;
        } else if (c == '}') {
            pos += 1;
            tok->kind = TK_BRACE_R;
            tok += 1;
        } else if (c == '[') {
            pos += 1;
            tok->kind = TK_BRACKET_L;
            tok += 1;
        } else if (c == ']') {
            pos += 1;
            tok->kind = TK_BRACKET_R;
            tok += 1;
        } else if (c == ',') {
            pos += 1;
            tok->kind = TK_COMMA;
            tok += 1;
        } else if (c == ';') {
            pos += 1;
            tok->kind = TK_SEMICOLON;
            tok += 1;
        } else if (c == '+') {
            pos += 1;
            tok->kind = TK_PLUS;
            tok += 1;
        } else if (c == '&') {
            pos += 1;
            tok->kind = TK_AND;
            tok += 1;
        } else if (c == '-') {
            pos += 1;
            tok->kind = TK_MINUS;
            tok += 1;
        } else if (c == '*') {
            pos += 1;
            tok->kind = TK_STAR;
            tok += 1;
        } else if (c == '/') {
            pos += 1;
            tok->kind = TK_SLASH;
            tok += 1;
        } else if (c == '%') {
            pos += 1;
            tok->kind = TK_PERCENT;
            tok += 1;
        } else if (c == '!') {
            pos += 1;
            if (src[pos] == '=') {
                pos += 1;
                tok->kind = TK_NE;
                tok += 1;
            } else {
                tok->kind = TK_NOT;
                tok += 1;
            }
        } else if (c == '=') {
            pos += 1;
            if (src[pos] == '=') {
                pos += 1;
                tok->kind = TK_EQ;
                tok += 1;
            } else {
                tok->kind = TK_ASSIGN;
                tok += 1;
            }
        } else if (c == '<') {
            pos += 1;
            if (src[pos] == '=') {
                pos += 1;
                tok->kind = TK_LE;
                tok += 1;
            } else {
                tok->kind = TK_LT;
                tok += 1;
            }
        } else if (c == '>') {
            pos += 1;
            if (src[pos] == '=') {
                pos += 1;
                tok->kind = TK_GE;
                tok += 1;
            } else {
                tok->kind = TK_GT;
                tok += 1;
            }
        } else if (c == '"') {
            pos += 1;
            int start = pos;
            while (1) {
                int ch = src[pos];
                if (ch == '\\') {
                    pos += 1;
                } else if (ch == '"') {
                    break;
                }
                pos += 1;
            }
            tok->kind = TK_L_STR;
            tok->value = calloc(pos - start + 1, sizeof(char));
            memcpy(tok->value, src + start, pos - start);
            pos += 1;
            tok += 1;
        } else if (isdigit(c)) {
            int start = pos;
            while (isdigit(src[pos])) {
                pos += 1;
            }
            tok->kind = TK_L_INT;
            tok->value = calloc(pos - start + 1, sizeof(char));
            memcpy(tok->value, src + start, pos - start);
            tok += 1;
        } else if (isalpha(c)) {
            int start = pos;
            while (isalnum(src[pos])) {
                pos += 1;
            }
            if (strstr(src + start, "break") == src + start) {
                tok->kind = TK_K_BREAK;
            } else if (strstr(src + start, "char") == src + start) {
                tok->kind = TK_K_CHAR;
            } else if (strstr(src + start, "continue") == src + start) {
                tok->kind = TK_K_CONTINUE;
            } else if (strstr(src + start, "else") == src + start) {
                tok->kind = TK_K_ELSE;
            } else if (strstr(src + start, "for") == src + start) {
                tok->kind = TK_K_FOR;
            } else if (strstr(src + start, "if") == src + start) {
                tok->kind = TK_K_IF;
            } else if (strstr(src + start, "int") == src + start) {
                tok->kind = TK_K_INT;
            } else if (strstr(src + start, "long") == src + start) {
                tok->kind = TK_K_LONG;
            } else if (strstr(src + start, "return") == src + start) {
                tok->kind = TK_K_RETURN;
            } else if (strstr(src + start, "sizeof") == src + start) {
                tok->kind = TK_K_SIZEOF;
            } else if (strstr(src + start, "struct") == src + start) {
                tok->kind = TK_K_STRUCT;
            } else if (strstr(src + start, "void") == src + start) {
                tok->kind = TK_K_VOID;
            } else {
                tok->kind = TK_IDENT;
                tok->value = calloc(pos - start + 1, sizeof(char));
                memcpy(tok->value, src + start, pos - start);
            }
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
#define TY_PTR     5
#define TY_STRUCT  6

typedef struct Type {
    int kind;
    struct Type* to;
} TYPE;

TYPE* type_new(int kind) {
    TYPE* ty = calloc(1, sizeof(TYPE));
    ty->kind = kind;
    return ty;
}

TYPE* type_new_ptr(TYPE* to) {
    TYPE* ty = calloc(1, sizeof(TYPE));
    ty->kind = TY_PTR;
    ty->to = to;
    return ty;
}

int type_is_unsized_type(TYPE* ty) {
    return ty->kind != TY_VOID;
}

int type_sizeof(TYPE* ty) {
    if (!type_is_unsized_type(ty)) {
        fatal_error("type_sizeof: type size cannot be determined");
    }

    if (ty->kind == TY_PTR) {
        return 8;
    } else if (ty->kind == TY_CHAR) {
        return 1;
    } else if (ty->kind == TY_INT) {
        return 4;
    } else if (ty->kind == TY_LONG) {
        return 8;
    } else {
        todo();
    }
}

int type_ptr_shift_width(TYPE* ty) {
    if (ty->kind != TY_PTR) {
        fatal_error("type_ptr_shift_width: type is not a pointer");
    }

    int sz = type_sizeof(ty->to);
    if (sz == 1) {
        return 0;
    } else if (sz == 2) {
        return 1;
    } else if (sz == 4) {
        return 2;
    } else if (sz == 8) {
        return 3;
    } else {
        todo();
    }
}

#define AST_UNKNOWN       0

#define AST_ARG_LIST      1
#define AST_ASSIGN_EXPR   2
#define AST_BINARY_EXPR   3
#define AST_BLOCK         4
#define AST_BREAK_STMT    5
#define AST_CONTINUE_STMT 6
#define AST_DEREF_EXPR    7
#define AST_EXPR_STMT     8
#define AST_FOR_STMT      9
#define AST_FUNC_CALL     10
#define AST_FUNC_DECL     11
#define AST_FUNC_DEF      12
#define AST_IF_STMT       13
#define AST_INT_LIT_EXPR  14
#define AST_LVAR          15
#define AST_PARAM         16
#define AST_PARAM_LIST    17
#define AST_PROGRAM       18
#define AST_REF_EXPR      19
#define AST_RETURN_STMT   20
#define AST_STR_LIT_EXPR  21
#define AST_TYPE          22
#define AST_UNARY_EXPR    23
#define AST_VAR_DECL      24

typedef struct AstNode {
    int kind;
    struct AstNode* next;
    struct AstNode* last;
    char* name;
    struct AstNode* func_params;
    struct AstNode* func_body;
    int int_value;
    struct AstNode* expr1;
    struct AstNode* expr2;
    struct AstNode* expr3;
    int op;
    TYPE* ty;
    int var_index;
    struct AstNode* node1;
    struct AstNode* node2;
    char** str_literals;
} AST;

AST* ast_new(int kind) {
    AST* ast = calloc(1, sizeof(AST));
    ast->kind = kind;
    return ast;
}

AST* ast_new_list(int kind) {
    if (kind != AST_PROGRAM && kind != AST_BLOCK && kind != AST_ARG_LIST && kind != AST_PARAM_LIST) {
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

#define LVAR_MAX 32

typedef struct LVar {
    char* name;
    TYPE* ty;
} LVAR;

typedef struct Func {
    char* name;
    TYPE* ty;
} FUNC;

typedef struct Parser {
    TOKEN* tokens;
    int pos;
    LVAR* locals;
    int n_locals;
    FUNC* funcs;
    int n_funcs;
    char** str_literals;
    int n_str_literals;
} PARSER;

PARSER* parser_new(TOKEN* tokens) {
    PARSER* p = calloc(1, sizeof(PARSER));
    p->tokens = tokens;
    p->funcs = calloc(128, sizeof(FUNC));
    p->str_literals = calloc(1024, sizeof(char*));
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

int find_lvar(PARSER* p, char* name) {
    int i;
    for (i = 0; i < p->n_locals; i++) {
        if (strcmp(p->locals[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

int find_func(PARSER* p, char* name) {
    int i;
    for (i = 0; i < p->n_funcs; i++) {
        if (strcmp(p->funcs[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

AST* parse_expr(PARSER* p);
AST* parse_stmt(PARSER* p);

char* parse_ident(PARSER* p) {
    return expect(p, TK_IDENT)->value;
}

int register_str_lit(PARSER* p, char* s) {
    p->str_literals[p->n_str_literals] = s;
    p->n_str_literals += 1;
    return p->n_str_literals;
}

AST* parse_primary_expr(PARSER* p) {
    TOKEN* t = next_token(p);
    if (t->kind == TK_L_INT) {
        AST* e = ast_new(AST_INT_LIT_EXPR);
        e->int_value = atoi(t->value);
        e->ty = type_new(TY_INT);
        return e;
    } else if (t->kind == TK_L_STR) {
        int str_lit_index = register_str_lit(p, t->value);
        AST* e = ast_new(AST_STR_LIT_EXPR);
        e->int_value = str_lit_index;
        return e;
    } else if (t->kind == TK_PAREN_L) {
        AST* e = parse_expr(p);
        expect(p, TK_PAREN_R);
        return e;
    } else if (t->kind == TK_IDENT) {
        char* name = t->value;

        if (peek_token(p)->kind == TK_PAREN_L) {
            AST* e = ast_new(AST_FUNC_CALL);
            int func_index = find_func(p, name);
            if (func_index == -1) {
                char buf[1024];
                sprintf(buf, "undefined function: %s", name);
                fatal_error(buf);
            }
            e->name = name;
            e->ty = p->funcs[func_index].ty;
            return e;
        }

        int var_index = find_lvar(p, name);
        if (var_index == -1) {
            char buf[1024];
            sprintf(buf, "undefined variable: %s", name);
            fatal_error(buf);
        }

        AST* e = ast_new(AST_LVAR);
        e->name = name;
        e->var_index = var_index;
        e->ty = p->locals[var_index].ty;
        return e;
    } else {
        char buf[1024];
        sprintf(buf, "expected primary expression, but got %d", t->kind);
        fatal_error(buf);
    }
}

AST* parse_arg_list(PARSER* p) {
    AST* list = ast_new_list(AST_ARG_LIST);
    while (peek_token(p)->kind != TK_PAREN_R) {
        AST* arg = parse_expr(p);
        list->last->next = arg;
        list->last = arg;
        int tk = peek_token(p)->kind;
        if (tk == TK_COMMA) {
            next_token(p);
        } else {
            break;
        }
    }
    return list;
}

AST* parse_postfix_expr(PARSER* p) {
    AST* ret = parse_primary_expr(p);
    while (1) {
        int tk = peek_token(p)->kind;
        if (tk == TK_PAREN_L) {
            next_token(p);
            AST* args = parse_arg_list(p);
            expect(p, TK_PAREN_R);
            ret->expr1 = args;
        } else {
            break;
        }
    }
    return ret;
}

int is_type_token(int token_kind) {
    return token_kind == TK_K_INT || token_kind == TK_K_LONG || token_kind == TK_K_CHAR || token_kind == TK_K_VOID;
}

TYPE* parse_type(PARSER* p) {
    TOKEN* t = next_token(p);
    if (!is_type_token(t->kind)) {
        fatal_error("parse_type: unknown type");
    }
    TYPE* ty = type_new(TY_UNKNOWN);
    if (t->kind == TK_K_INT) {
        ty->kind = TY_INT;
    } else if (t->kind == TK_K_LONG) {
        ty->kind = TY_LONG;
    } else if (t->kind == TK_K_CHAR) {
        ty->kind = TY_CHAR;
    } else if (t->kind == TK_K_VOID) {
        ty->kind = TY_VOID;
    }
    while (1) {
        TOKEN* t2 = peek_token(p);
        if (t2->kind == TK_STAR) {
            next_token(p);
            ty = type_new_ptr(ty);
        } else {
            break;
        }
    }
    return ty;
}

AST* parse_prefix_expr(PARSER* p) {
    int op = peek_token(p)->kind;
    if (op == TK_MINUS) {
        next_token(p);
        AST* operand = parse_prefix_expr(p);
        AST* lhs = ast_new(AST_INT_LIT_EXPR);
        lhs->int_value = 0;
        lhs->ty = type_new(TY_INT);
        AST* e = ast_new_binary_expr(op, lhs, operand);
        e->ty = type_new(TY_INT);
        return e;
    } else if (op == TK_AND) {
        next_token(p);
        AST* operand = parse_prefix_expr(p);
        AST* e = ast_new(AST_REF_EXPR);
        e->expr1 = operand;
        e->ty = type_new_ptr(operand->ty);
        return e;
    } else if (op == TK_STAR) {
        next_token(p);
        AST* operand = parse_prefix_expr(p);
        AST* e = ast_new(AST_DEREF_EXPR);
        e->expr1 = operand;
        e->ty = operand->ty->to;
        return e;
    } else if (op == TK_K_SIZEOF) {
        next_token(p);
        expect(p, TK_PAREN_L);
        TYPE* ty = parse_type(p);
        expect(p, TK_PAREN_R);
        AST* e = ast_new(AST_INT_LIT_EXPR);
        e->int_value = type_sizeof(ty);
        e->ty = type_new(TY_INT);
        return e;
    }
    return parse_postfix_expr(p);
}

AST* parse_multiplicative_expr(PARSER* p) {
    AST* lhs = parse_prefix_expr(p);
    while (1) {
        int op = peek_token(p)->kind;
        if (op == TK_STAR || op == TK_SLASH || op == TK_PERCENT) {
            next_token(p);
            AST* rhs = parse_prefix_expr(p);
            lhs = ast_new_binary_expr(op, lhs, rhs);
            lhs->ty = type_new(TY_INT);
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
        if (op == TK_PLUS) {
            next_token(p);
            AST* rhs = parse_multiplicative_expr(p);
            TYPE* result_type;
            if (lhs->ty->kind == TY_PTR) {
                result_type = lhs->ty;
            } else if (rhs->ty->kind == TY_PTR) {
                result_type = rhs->ty;
            } else {
                result_type = type_new(TY_INT);
            }
            lhs = ast_new_binary_expr(op, lhs, rhs);
            lhs->ty = result_type;
        } else if (op == TK_MINUS) {
            next_token(p);
            AST* rhs = parse_multiplicative_expr(p);
            TYPE* result_type;
            if (lhs->ty->kind == TY_PTR) {
                result_type = lhs->ty;
            } else {
                result_type = type_new(TY_INT);
            }
            lhs = ast_new_binary_expr(op, lhs, rhs);
            lhs->ty = result_type;
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
            lhs->ty = type_new(TY_INT);
        } else if (op == TK_GT) {
            next_token(p);
            AST* rhs = parse_additive_expr(p);
            lhs = ast_new_binary_expr(TK_LT, rhs, lhs);
            lhs->ty = type_new(TY_INT);
        } else if (op == TK_GE) {
            next_token(p);
            AST* rhs = parse_additive_expr(p);
            lhs = ast_new_binary_expr(TK_GE, rhs, lhs);
            lhs->ty = type_new(TY_INT);
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
            lhs->ty = type_new(TY_INT);
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
            // TODO: support type coercion?
            lhs->ty = rhs->ty;
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

AST* parse_if_stmt(PARSER* p) {
    expect(p, TK_K_IF);
    expect(p, TK_PAREN_L);
    AST* cond = parse_expr(p);
    expect(p, TK_PAREN_R);
    AST* then_body = parse_stmt(p);
    AST* else_body = NULL;
    if (peek_token(p)->kind == TK_K_ELSE) {
        next_token(p);
        else_body = parse_stmt(p);
    }

    AST* stmt = ast_new(AST_IF_STMT);
    stmt->expr1 = cond;
    stmt->node1 = then_body;
    stmt->node2 = else_body;
    return stmt;
}

AST* parse_for_stmt(PARSER* p) {
    expect(p, TK_K_FOR);
    expect(p, TK_PAREN_L);
    AST* init = parse_expr(p);
    expect(p, TK_SEMICOLON);
    AST* cond = parse_expr(p);
    expect(p, TK_SEMICOLON);
    AST* update = parse_expr(p);
    expect(p, TK_PAREN_R);
    AST* body = parse_stmt(p);

    AST* stmt = ast_new(AST_FOR_STMT);
    stmt->expr1 = init;
    stmt->expr2 = cond;
    stmt->expr3 = update;
    stmt->node1 = body;
    return stmt;
}

AST* parse_break_stmt(PARSER* p) {
    expect(p, TK_K_BREAK);
    expect(p, TK_SEMICOLON);
    return ast_new(AST_BREAK_STMT);
}

AST* parse_continue_stmt(PARSER* p) {
    expect(p, TK_K_CONTINUE);
    expect(p, TK_SEMICOLON);
    return ast_new(AST_CONTINUE_STMT);
}

AST* parse_var_decl(PARSER* p) {
    TYPE* ty = parse_type(p);
    if (!type_is_unsized_type(ty)) {
        fatal_error("parse_var_decl: invalid type for variable");
    }
    char* name = parse_ident(p);
    AST* decl = ast_new(AST_VAR_DECL);
    expect(p, TK_SEMICOLON);
    decl->ty = ty;
    decl->name = name;

    if (find_lvar(p, name) != -1) {
        char buf[1024];
        sprintf(buf, "parse_var_decl: %s redeclared", name);
        fatal_error(buf);
    }
    p->locals[p->n_locals].name = name;
    p->locals[p->n_locals].ty = ty;
    p->n_locals += 1;

    return decl;
}

AST* parse_expr_stmt(PARSER* p) {
    AST* e = parse_expr(p);
    expect(p, TK_SEMICOLON);
    AST* stmt = ast_new(AST_EXPR_STMT);
    stmt->expr1 = e;
    return stmt;
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

AST* parse_stmt(PARSER* p) {
    TOKEN* t = peek_token(p);
    if (t->kind == TK_K_RETURN) {
        return parse_return_stmt(p);
    } else if (t->kind == TK_K_IF) {
        return parse_if_stmt(p);
    } else if (t->kind == TK_K_FOR) {
        return parse_for_stmt(p);
    } else if (t->kind == TK_K_BREAK) {
        return parse_break_stmt(p);
    } else if (t->kind == TK_K_CONTINUE) {
        return parse_continue_stmt(p);
    } else if (t->kind == TK_BRACE_L) {
        return parse_block_stmt(p);
    } else if (is_type_token(t->kind)) {
        return parse_var_decl(p);
    } else {
        return parse_expr_stmt(p);
    }
}

void enter_func(PARSER* p) {
    p->locals = calloc(LVAR_MAX, sizeof(LVAR));
    p->n_locals = 0;
}

void register_params(PARSER* p, AST* params) {
    AST* param = params->next;
    while (param) {
        p->locals[p->n_locals].name = param->name;
        p->locals[p->n_locals].ty = param->ty;
        p->n_locals += 1;
        param = param->next;
    }
}

void register_func(PARSER* p, char* name, TYPE* ty) {
    p->funcs[p->n_funcs].name = name;
    p->funcs[p->n_funcs].ty = ty;
    p->n_funcs += 1;
}

AST* parse_param(PARSER* p) {
    TYPE* ty = parse_type(p);
    if (!type_is_unsized_type(ty)) {
        fatal_error("parse_param: invalid type for variable");
    }
    char* name = parse_ident(p);
    AST* param = ast_new(AST_PARAM);
    param->ty = ty;
    param->name = name;
    return param;
}

AST* parse_param_list(PARSER* p) {
    AST* list = ast_new_list(AST_PARAM_LIST);
    while (peek_token(p)->kind != TK_PAREN_R) {
        AST* param = parse_param(p);
        list->last->next = param;
        list->last = param;
        int tk = peek_token(p)->kind;
        if (tk == TK_COMMA) {
            next_token(p);
        } else {
            break;
        }
    }
    return list;
}

AST* parse_func_decl_or_def(PARSER* p) {
    TYPE* ty = parse_type(p);
    char* name = parse_ident(p);
    register_func(p, name, ty);
    expect(p, TK_PAREN_L);
    AST* params = parse_param_list(p);
    expect(p, TK_PAREN_R);
    if (peek_token(p)->kind == TK_SEMICOLON) {
        next_token(p);
        return ast_new(AST_FUNC_DECL);
    }
    enter_func(p);
    register_params(p, params);
    AST* body = parse_block_stmt(p);
    AST* func = ast_new(AST_FUNC_DEF);
    func->ty = ty;
    func->name = name;
    func->func_params = params;
    func->func_body = body;
    return func;
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
    list->str_literals = p->str_literals;
    return list;
}

#define GEN_LVAL 0
#define GEN_RVAL 1

typedef struct CodeGen {
    int next_label;
    int* loop_labels;
} CODEGEN;

CODEGEN* codegen_new() {
    CODEGEN* g = calloc(1, sizeof(CODEGEN));
    g->next_label = 1;
    g->loop_labels = calloc(1024, sizeof(int));
    return g;
}

void assert_ast_kind(AST* ast, int kind) {
    if (ast->kind != kind) {
        char buf[1024];
        sprintf(buf, "invalid ast kind: expected %d, but got %d", kind, ast->kind);
        fatal_error(buf);
    }
}

int gen_new_label(CODEGEN* g) {
    int new_label = g->next_label;
    g->next_label += 1;
    return new_label;
}

void gen_expr(CODEGEN* g, AST* ast, int gen_mode);
void gen_stmt(CODEGEN* g, AST* ast);

void gen_func_prologue(CODEGEN* g, AST* ast) {
    printf("  # gen_func_prologue\n");

    printf("  push rbp\n");
    printf("  mov rbp, rsp\n");
    int param_index = 0;
    AST* param = ast->func_params->next;
    while (param) {
        if (param_index == 0) {
            printf("  push rdi\n");
        } else if (param_index == 1) {
            printf("  push rsi\n");
        } else if (param_index == 2) {
            printf("  push rdx\n");
        } else if (param_index == 3) {
            printf("  push rcx\n");
        } else if (param_index == 4) {
            printf("  push r8\n");
        } else if (param_index == 5) {
            printf("  push r9\n");
        } else {
            fatal_error("gen_func_prologue: too many params");
        }
        param_index += 1;
        param = param->next;
    }
    printf("  sub rsp, %d\n", 8 * LVAR_MAX);
}

void gen_func_epilogue(CODEGEN* g, AST* ast) {
    printf("  # gen_func_epilogue\n");

    printf("  mov rsp, rbp\n");
    printf("  pop rbp\n");
    printf("  ret\n");
}

void gen_int_lit_expr(CODEGEN* g, AST* ast) {
    assert_ast_kind(ast, AST_INT_LIT_EXPR);
    printf("  # gen_int_lit_expr\n");

    printf("  push %d\n", ast->int_value);
}

void gen_str_lit_expr(CODEGEN* g, AST* ast) {
    assert_ast_kind(ast, AST_STR_LIT_EXPR);
    printf("  # gen_str_lit_expr\n");

    printf("  mov rax, OFFSET FLAG:.Lstr__%d\n", ast->int_value);
    printf("  push rax\n");
}

void gen_unary_expr(CODEGEN* g, AST* ast) {
    assert_ast_kind(ast, AST_UNARY_EXPR);
    printf("  # gen_unary_expr\n");

    todo();
}

void gen_ref_expr(CODEGEN* g, AST* ast, int gen_mode) {
    assert_ast_kind(ast, AST_REF_EXPR);
    printf("  # gen_ref_expr\n");

    gen_expr(g, ast->expr1, GEN_LVAL);
}

void gen_deref_expr(CODEGEN* g, AST* ast, int gen_mode) {
    assert_ast_kind(ast, AST_DEREF_EXPR);
    printf("  # gen_deref_expr\n");

    if (gen_mode == GEN_LVAL) {
        gen_expr(g, ast->expr1, GEN_RVAL);
    } else {
        gen_expr(g, ast->expr1, GEN_RVAL);
        printf("  pop rax\n");
        printf("  push [rax]\n");
    }
}

void gen_binary_expr(CODEGEN* g, AST* ast, int gen_mode) {
    assert_ast_kind(ast, AST_BINARY_EXPR);
    printf("  # gen_binary_expr\n");

    gen_expr(g, ast->expr1, gen_mode);
    gen_expr(g, ast->expr2, gen_mode);
    printf("  pop rdi\n");
    printf("  pop rax\n");
    if (ast->op == TK_PLUS) {
        if (ast->expr1->ty->kind == TY_PTR) {
            printf("  shl rdi, %d\n", type_ptr_shift_width(ast->expr1->ty));
            printf("  add rax, rdi\n");
        } else if (ast->expr2->ty->kind == TY_PTR) {
            printf("  shl rdi, %d\n", type_ptr_shift_width(ast->expr2->ty));
            printf("  add rax, rdi\n");
        } else {
            printf("  add rax, rdi\n");
        }
    } else if (ast->op == TK_MINUS) {
        if (ast->expr2->ty->kind == TY_PTR) {
            printf("  sub rax, rdi\n");
            printf("  shr rax, %d\n", type_ptr_shift_width(ast->expr2->ty));
        } else if (ast->expr1->ty->kind == TY_PTR) {
            printf("  shl rdi, %d\n", type_ptr_shift_width(ast->expr2->ty));
            printf("  sub rax, rdi\n");
        } else {
            printf("  sub rax, rdi\n");
        }
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
    printf("  # gen_assign_expr\n");

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

void gen_func_call(CODEGEN* g, AST* ast) {
    assert_ast_kind(ast, AST_FUNC_CALL);
    printf("  # gen_func_call\n");

    char* func_name = ast->name;
    AST* args = ast->expr1;
    AST* arg = args->next;
    int n_args = 0;
    while (arg) {
        n_args += 1;
        gen_expr(g, arg, GEN_RVAL);
        arg = arg->next;
    }
    for (int i = n_args - 1; i >= 0; i--) {
        if (i == 0) {
            printf("  pop rdi\n");
        } else if (i == 1) {
            printf("  pop rsi\n");
        } else if (i == 2) {
            printf("  pop rdx\n");
        } else if (i == 3) {
            printf("  pop rcx\n");
        } else if (i == 4) {
            printf("  pop r8\n");
        } else if (i == 5) {
            printf("  pop r9\n");
        } else {
            fatal_error("gen_func_call: too many args");
        }
    }
    // TODO: rsp align
    printf("  mov rax, 0\n");
    printf("  call %s\n", func_name);
    printf("  push rax\n");
}

void gen_lvar(CODEGEN* g, AST* ast, int gen_mode) {
    assert_ast_kind(ast, AST_LVAR);
    printf("  # gen_lvar\n");

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
    } else if (ast->kind == AST_STR_LIT_EXPR) {
        gen_str_lit_expr(g, ast);
    } else if (ast->kind == AST_UNARY_EXPR) {
        gen_unary_expr(g, ast);
    } else if (ast->kind == AST_REF_EXPR) {
        gen_ref_expr(g, ast, gen_mode);
    } else if (ast->kind == AST_DEREF_EXPR) {
        gen_deref_expr(g, ast, gen_mode);
    } else if (ast->kind == AST_BINARY_EXPR) {
        gen_binary_expr(g, ast, gen_mode);
    } else if (ast->kind == AST_ASSIGN_EXPR) {
        gen_assign_expr(g, ast);
    } else if (ast->kind == AST_FUNC_CALL) {
        gen_func_call(g, ast);
    } else if (ast->kind == AST_LVAR) {
        gen_lvar(g, ast, gen_mode);
    } else {
        fatal_error("gen_expr: unknown expr");
    }
}

void gen_return_stmt(CODEGEN* g, AST* ast) {
    assert_ast_kind(ast, AST_RETURN_STMT);
    printf("  # gen_return_stmt\n");

    gen_expr(g, ast->expr1, GEN_RVAL);
    printf("  pop rax\n");
    gen_func_epilogue(g, ast);
}

void gen_if_stmt(CODEGEN* g, AST* ast) {
    assert_ast_kind(ast, AST_IF_STMT);
    printf("  # gen_if_stmt\n");

    int label = gen_new_label(g);

    gen_expr(g, ast->expr1, GEN_RVAL);
    printf("  pop rax\n");
    printf("  cmp rax, 0\n");
    printf("  je .Lelse%d\n", label);
    gen_stmt(g, ast->node1);
    printf("  jmp .Lend%d\n", label);
    printf(".Lelse%d:\n", label);
    if (ast->node2) {
        gen_stmt(g, ast->node2);
    }
    printf(".Lend%d:\n", label);
}

void gen_for_stmt(CODEGEN* g, AST* ast) {
    assert_ast_kind(ast, AST_FOR_STMT);
    printf("  # gen_for_stmt\n");

    int label = gen_new_label(g);
    g->loop_labels += 1;
    *g->loop_labels = label;

    gen_expr(g, ast->expr1, GEN_RVAL);
    printf(".Lbegin%d:\n", label);
    gen_expr(g, ast->expr2, GEN_RVAL);
    printf("  pop rax\n");
    printf("  cmp rax, 0\n");
    printf("  je .Lend%d\n", label);
    gen_stmt(g, ast->node1);
    printf(".Lcontinue%d:\n", label);
    gen_expr(g, ast->expr3, GEN_RVAL);
    printf("  pop rax\n");
    printf("  jmp .Lbegin%d\n", label);
    printf(".Lend%d:\n", label);

    g->loop_labels -= 1;
}

void gen_break_stmt(CODEGEN* g, AST* ast) {
    assert_ast_kind(ast, AST_BREAK_STMT);
    printf("  # gen_break_stmt\n");

    int label = *g->loop_labels;
    printf("  jmp .Lend%d\n", label);
}

void gen_continue_stmt(CODEGEN* g, AST* ast) {
    assert_ast_kind(ast, AST_CONTINUE_STMT);
    printf("  # gen_continue_stmt\n");

    int label = *g->loop_labels;
    printf("  jmp .Lcontinue%d\n", label);
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
    } else if (ast->kind == AST_IF_STMT) {
        gen_if_stmt(g, ast);
    } else if (ast->kind == AST_FOR_STMT) {
        gen_for_stmt(g, ast);
    } else if (ast->kind == AST_BREAK_STMT) {
        gen_break_stmt(g, ast);
    } else if (ast->kind == AST_CONTINUE_STMT) {
        gen_continue_stmt(g, ast);
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
    printf("%s:\n", ast->name);

    gen_func_prologue(g, ast);
    gen_stmt(g, ast->func_body);
    gen_func_epilogue(g, ast);
    printf("\n");
}

void gen(CODEGEN* g, AST* ast) {
    assert_ast_kind(ast, AST_PROGRAM);

    printf(".intel_syntax noprefix\n\n");

    char** str_lit = ast->str_literals;
    while (*str_lit) {
        printf(".Lstr__%d:\n", str_lit - ast->str_literals + 1);
        printf("  .string \"%s\"\n\n", *str_lit);
        str_lit += 1;
    }

    printf(".globl main\n\n");

    AST* func = ast->next;
    while (func) {
        if (func->kind == AST_FUNC_DEF) {
            gen_func(g, func);
        }
        func = func->next;
    }
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
