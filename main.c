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
    for (0; (c = getchar()) != -1; 0) {
        buf[n] = c;
        n = n + 1;
    }
    return n;
}

#define TK_EOF        0

#define TK_AND        1
#define TK_ANDAND     2
#define TK_ARROW      3
#define TK_ASSIGN     4
#define TK_BRACE_L    5
#define TK_BRACE_R    6
#define TK_BRACKET_L  7
#define TK_BRACKET_R  8
#define TK_COMMA      9
#define TK_DOT        10
#define TK_EQ         11
#define TK_GE         12
#define TK_GT         13
#define TK_IDENT      14
#define TK_K_BREAK    15
#define TK_K_CHAR     16
#define TK_K_CONTINUE 17
#define TK_K_ELSE     18
#define TK_K_FOR      19
#define TK_K_IF       20
#define TK_K_INT      21
#define TK_K_LONG     22
#define TK_K_RETURN   23
#define TK_K_SIZEOF   24
#define TK_K_STRUCT   25
#define TK_K_VOID     26
#define TK_LE         27
#define TK_LT         28
#define TK_L_INT      29
#define TK_L_STR      30
#define TK_MINUS      31
#define TK_NE         32
#define TK_NOT        33
#define TK_OROR       34
#define TK_PAREN_L    35
#define TK_PAREN_R    36
#define TK_PERCENT    37
#define TK_PLUS       38
#define TK_SEMICOLON  39
#define TK_SLASH      40
#define TK_STAR       41

struct Token {
    int kind;
    char* value;
};

struct Define {
    char* from;
    struct Token* to;
};

struct Token* tokenize(char* src, int len) {
    struct Token* tokens = calloc(1024*1024, sizeof(struct Token));
    struct Token* tok = tokens;
    struct Define* defines = calloc(1024, sizeof(struct Define));
    struct Define* def = defines;
    int pos = 0;
    for (0; pos < len; 0) {
        char c = src[pos];
        if (c == '(') {
            pos = pos + 1;
            tok->kind = TK_PAREN_L;
            tok = tok + 1;
        } else if (c == ')') {
            pos = pos + 1;
            tok->kind = TK_PAREN_R;
            tok = tok + 1;
        } else if (c == '{') {
            pos = pos + 1;
            tok->kind = TK_BRACE_L;
            tok = tok + 1;
        } else if (c == '}') {
            pos = pos + 1;
            tok->kind = TK_BRACE_R;
            tok = tok + 1;
        } else if (c == '[') {
            pos = pos + 1;
            tok->kind = TK_BRACKET_L;
            tok = tok + 1;
        } else if (c == ']') {
            pos = pos + 1;
            tok->kind = TK_BRACKET_R;
            tok = tok + 1;
        } else if (c == ',') {
            pos = pos + 1;
            tok->kind = TK_COMMA;
            tok = tok + 1;
        } else if (c == ';') {
            pos = pos + 1;
            tok->kind = TK_SEMICOLON;
            tok = tok + 1;
        } else if (c == '+') {
            pos = pos + 1;
            tok->kind = TK_PLUS;
            tok = tok + 1;
        } else if (c == '|') {
            pos = pos + 2;
            tok->kind = TK_OROR;
            tok = tok + 1;
        } else if (c == '&') {
            pos = pos + 1;
            if (src[pos] == '&') {
                pos = pos + 1;
                tok->kind = TK_ANDAND;
                tok = tok + 1;
            } else {
                tok->kind = TK_AND;
                tok = tok + 1;
            }
        } else if (c == '-') {
            pos = pos + 1;
            if (src[pos] == '>') {
                pos = pos + 1;
                tok->kind = TK_ARROW;
                tok = tok + 1;
            } else {
                tok->kind = TK_MINUS;
                tok = tok + 1;
            }
        } else if (c == '*') {
            pos = pos + 1;
            tok->kind = TK_STAR;
            tok = tok + 1;
        } else if (c == '/') {
            pos = pos + 1;
            tok->kind = TK_SLASH;
            tok = tok + 1;
        } else if (c == '%') {
            pos = pos + 1;
            tok->kind = TK_PERCENT;
            tok = tok + 1;
        } else if (c == '.') {
            pos = pos + 1;
            tok->kind = TK_DOT;
            tok = tok + 1;
        } else if (c == '!') {
            pos = pos + 1;
            if (src[pos] == '=') {
                pos = pos + 1;
                tok->kind = TK_NE;
                tok = tok + 1;
            } else {
                tok->kind = TK_NOT;
                tok = tok + 1;
            }
        } else if (c == '=') {
            pos = pos + 1;
            if (src[pos] == '=') {
                pos = pos + 1;
                tok->kind = TK_EQ;
                tok = tok + 1;
            } else {
                tok->kind = TK_ASSIGN;
                tok = tok + 1;
            }
        } else if (c == '<') {
            pos = pos + 1;
            if (src[pos] == '=') {
                pos = pos + 1;
                tok->kind = TK_LE;
                tok = tok + 1;
            } else {
                tok->kind = TK_LT;
                tok = tok + 1;
            }
        } else if (c == '>') {
            pos = pos + 1;
            if (src[pos] == '=') {
                pos = pos + 1;
                tok->kind = TK_GE;
                tok = tok + 1;
            } else {
                tok->kind = TK_GT;
                tok = tok + 1;
            }
        } else if (c == '\'') {
            pos = pos + 1;
            int ch = src[pos];
            if (ch == '\\') {
                pos = pos + 1;
                ch = src[pos];
                if (ch == 'n') {
                    ch = '\n';
                }
            }
            pos = pos + 2;
            tok->kind = TK_L_INT;
            tok->value = calloc(4, sizeof(char));
            sprintf(tok->value, "%d", ch);
            tok = tok + 1;
        } else if (c == '"') {
            pos = pos + 1;
            int start = pos;
            for (0; 1; 0) {
                int ch = src[pos];
                if (ch == '\\') {
                    pos = pos + 1;
                } else if (ch == '"') {
                    break;
                }
                pos = pos + 1;
            }
            tok->kind = TK_L_STR;
            tok->value = calloc(pos - start + 1, sizeof(char));
            memcpy(tok->value, src + start, pos - start);
            pos = pos + 1;
            tok = tok + 1;
        } else if (isdigit(c)) {
            int start = pos;
            for (0; isdigit(src[pos]); 0) {
                pos = pos + 1;
            }
            tok->kind = TK_L_INT;
            tok->value = calloc(pos - start + 1, sizeof(char));
            memcpy(tok->value, src + start, pos - start);
            tok = tok + 1;
        } else if (isalpha(c)) {
            int start = pos;
            for (0; isalnum(src[pos]) || src[pos] == '_'; 0) {
                pos = pos + 1;
            }
            int len = pos - start;
            if (len == 5 && strstr(src + start, "break") == src + start) {
                tok->kind = TK_K_BREAK;
            } else if (len == 4 && strstr(src + start, "char") == src + start) {
                tok->kind = TK_K_CHAR;
            } else if (len == 8 && strstr(src + start, "continue") == src + start) {
                tok->kind = TK_K_CONTINUE;
            } else if (len == 4 && strstr(src + start, "else") == src + start) {
                tok->kind = TK_K_ELSE;
            } else if (len == 3 && strstr(src + start, "for") == src + start) {
                tok->kind = TK_K_FOR;
            } else if (len == 2 && strstr(src + start, "if") == src + start) {
                tok->kind = TK_K_IF;
            } else if (len == 3 && strstr(src + start, "int") == src + start) {
                tok->kind = TK_K_INT;
            } else if (len == 4 && strstr(src + start, "long") == src + start) {
                tok->kind = TK_K_LONG;
            } else if (len == 6 && strstr(src + start, "return") == src + start) {
                tok->kind = TK_K_RETURN;
            } else if (len == 6 && strstr(src + start, "sizeof") == src + start) {
                tok->kind = TK_K_SIZEOF;
            } else if (len == 6 && strstr(src + start, "struct") == src + start) {
                tok->kind = TK_K_STRUCT;
            } else if (len == 4 && strstr(src + start, "void") == src + start) {
                tok->kind = TK_K_VOID;
            } else {
                tok->value = calloc(len + 1, sizeof(char));
                memcpy(tok->value, src + start, len);
                int i = 0;
                for (0; defines + i != def; 0) {
                    if (strcmp(tok->value, defines[i].from) == 0) {
                        tok->kind = defines[i].to->kind;
                        tok->value = defines[i].to->value;
                        break;
                    }
                    i = i + 1;
                }
                if (defines + i == def) {
                    tok->kind = TK_IDENT;
                }
            }
            tok = tok + 1;
        } else if (isspace(c)) {
            pos = pos + 1;
        } else if (c == '#') {
            pos = pos + 1;
            pos = pos + 6;
            for (0; isspace(src[pos]); 0) {
                pos = pos + 1;
            }
            int start = pos;
            for (0; isalnum(src[pos]) || src[pos] == '_'; 0) {
                pos = pos + 1;
            }
            def->from = calloc(pos - start + 1, sizeof(char));
            memcpy(def->from, src + start, pos - start);
            for (0; isspace(src[pos]); 0) {
                pos = pos + 1;
            }
            int start2 = pos;
            for (0; isdigit(src[pos]); 0) {
                pos = pos + 1;
            }
            def->to = calloc(1, sizeof(struct Token));
            def->to->kind = TK_L_INT;
            def->to->value = calloc(pos - start2 + 1, sizeof(char));
            memcpy(def->to->value, src + start2, pos - start2);
            def = def + 1;
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

struct AstNode;

struct Type {
    int kind;
    struct Type* to;
    struct AstNode* members;
};

struct Type* type_new(int kind) {
    struct Type* ty = calloc(1, sizeof(struct Type));
    ty->kind = kind;
    return ty;
}

struct Type* type_new_ptr(struct Type* to) {
    struct Type* ty = calloc(1, sizeof(struct Type));
    ty->kind = TY_PTR;
    ty->to = to;
    return ty;
}

int type_is_unsized_type(struct Type* ty) {
    return ty->kind != TY_VOID;
}

int type_sizeof_struct(struct Type* ty);
int type_alignof_struct(struct Type* ty);

int type_sizeof(struct Type* ty) {
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
        return type_sizeof_struct(ty);
    }
}

int type_alignof(struct Type* ty) {
    if (!type_is_unsized_type(ty)) {
        fatal_error("type_alignof: type size cannot be determined");
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
        return type_alignof_struct(ty);
    }
}

int type_ptr_shift_width(struct Type* ty) {
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

#define AST_UNKNOWN            0

#define AST_ARG_LIST           1
#define AST_ASSIGN_EXPR        2
#define AST_BINARY_EXPR        3
#define AST_BLOCK              4
#define AST_BREAK_STMT         5
#define AST_CONTINUE_STMT      6
#define AST_DEREF_EXPR         7
#define AST_EXPR_STMT          8
#define AST_FOR_STMT           9
#define AST_FUNC_CALL          10
#define AST_FUNC_DECL          11
#define AST_FUNC_DEF           12
#define AST_IF_STMT            13
#define AST_INT_LIT_EXPR       14
#define AST_LVAR               15
#define AST_OFFSETOF           16
#define AST_PARAM              17
#define AST_PARAM_LIST         18
#define AST_PROGRAM            19
#define AST_REF_EXPR           20
#define AST_RETURN_STMT        21
#define AST_STRUCT_DECL        22
#define AST_STRUCT_DEF         23
#define AST_STRUCT_MEMBER      24
#define AST_STRUCT_MEMBER_LIST 25
#define AST_STR_LIT_EXPR       26
#define AST_TYPE               27
#define AST_UNARY_EXPR         28
#define AST_VAR_DECL           29

struct AstNode {
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
    struct Type* ty;
    int var_index;
    struct AstNode* node1;
    struct AstNode* node2;
    char** str_literals;
};

struct AstNode* ast_new(int kind) {
    struct AstNode* ast = calloc(1, sizeof(struct AstNode));
    ast->kind = kind;
    return ast;
}

struct AstNode* ast_new_list(int kind) {
    if (kind != AST_PROGRAM && kind != AST_BLOCK && kind != AST_ARG_LIST && kind != AST_PARAM_LIST && kind != AST_STRUCT_MEMBER_LIST) {
        fatal_error("ast_new_list: non-list ast");
    }
    struct AstNode* ast = ast_new(kind);
    ast->last = ast;
    return ast;
}

struct AstNode* ast_new_unary_expr(int op, struct AstNode* operand) {
    struct AstNode* e = ast_new(AST_UNARY_EXPR);
    e->op = op;
    e->expr1 = operand;
    return e;
}

struct AstNode* ast_new_binary_expr(int op, struct AstNode* lhs, struct AstNode* rhs) {
    struct AstNode* e = ast_new(AST_BINARY_EXPR);
    e->op = op;
    e->expr1 = lhs;
    e->expr2 = rhs;
    return e;
}

struct AstNode* ast_new_assign_expr(int op, struct AstNode* lhs, struct AstNode* rhs) {
    struct AstNode* e = ast_new(AST_ASSIGN_EXPR);
    e->op = op;
    e->expr1 = lhs;
    e->expr2 = rhs;
    return e;
}

int type_sizeof_struct(struct Type* ty) {
    int next_offset = 0;
    int struct_align = 0;

    struct AstNode* member = ty->members->next;
    for (0; member; 0) {
        int size = type_sizeof(member->ty);
        int align = type_alignof(member->ty);

        if (next_offset % align != 0) {
            int padding = align - next_offset % align;
            next_offset = next_offset + padding;
        }
        next_offset = next_offset + size;
        if (struct_align < align) {
            struct_align = align;
        }

        member = member->next;
    }
    if (next_offset % struct_align != 0) {
        int padding = struct_align - next_offset % struct_align;
        next_offset = next_offset + padding;
    }
    return next_offset;
}

int type_alignof_struct(struct Type* ty) {
    int struct_align = 0;

    struct AstNode* member = ty->members->next;
    for (0; member; 0) {
        int align = type_alignof(member->ty);

        if (struct_align < align) {
            struct_align = align;
        }

        member = member->next;
    }
    return struct_align;
}

int type_offsetof(struct Type* ty, char* name) {
    if (ty->kind != TY_STRUCT) {
        fatal_error("type_offsetof: type is not a struct");
    }

    int next_offset = 0;

    struct AstNode* member = ty->members->next;
    for (0; member; 0) {
        int size = type_sizeof(member->ty);
        int align = type_alignof(member->ty);

        if (next_offset % align != 0) {
            int padding = align - next_offset % align;
            next_offset = next_offset + padding;
        }
        if (strcmp(member->name, name) == 0) {
            return next_offset;
        }
        next_offset = next_offset + size;

        member = member->next;
    }

    fatal_error("type_offsetof: member not found");
}

struct Type* type_member_typeof(struct Type* ty, char* name) {
    if (ty->kind != TY_STRUCT) {
        fatal_error("type_offsetof: type is not a struct");
    }

    struct AstNode* member = ty->members->next;
    for (0; member; 0) {
        if (strcmp(member->name, name) == 0) {
            return member->ty;
        }
        member = member->next;
    }

    fatal_error("type_offsetof: member not found");
}

#define LVAR_MAX 32

struct LVar {
    char* name;
    struct Type* ty;
};

struct Func {
    char* name;
    struct Type* ty;
};

struct Parser {
    struct Token* tokens;
    int pos;
    struct LVar* locals;
    int n_locals;
    struct Func* funcs;
    int n_funcs;
    struct AstNode* structs;
    int n_structs;
    char** str_literals;
    int n_str_literals;
};

struct Parser* parser_new(struct Token* tokens) {
    struct Parser* p = calloc(1, sizeof(struct Parser));
    p->tokens = tokens;
    p->funcs = calloc(128, sizeof(struct Func));
    p->structs = calloc(64, sizeof(struct AstNode));
    p->str_literals = calloc(1024, sizeof(char*));
    return p;
}

struct Token* peek_token(struct Parser* p) {
    return p->tokens + p->pos;
}

struct Token* next_token(struct Parser* p) {
    p->pos = p->pos + 1;
    return p->tokens + p->pos - 1;
}

int eof(struct Parser* p) {
    return peek_token(p)->kind != TK_EOF;
}

struct Token* expect(struct Parser* p, int expected) {
    struct Token* t = next_token(p);
    if (t->kind == expected) {
        return t;
    }

    char* buf = calloc(1024, sizeof(char));
    sprintf(buf, "expected %d, but got %d", expected, t->kind);
    fatal_error(buf);
}

int find_lvar(struct Parser* p, char* name) {
    int i;
    for (i = 0; i < p->n_locals; i = i + 1) {
        if (strcmp(p->locals[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

int find_func(struct Parser* p, char* name) {
    int i;
    for (i = 0; i < p->n_funcs; i = i + 1) {
        if (strcmp(p->funcs[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

struct AstNode* parse_expr(struct Parser* p);
struct AstNode* parse_stmt(struct Parser* p);

char* parse_ident(struct Parser* p) {
    return expect(p, TK_IDENT)->value;
}

int register_str_lit(struct Parser* p, char* s) {
    p->str_literals[p->n_str_literals] = s;
    p->n_str_literals = p->n_str_literals + 1;
    return p->n_str_literals;
}

struct AstNode* parse_primary_expr(struct Parser* p) {
    struct Token* t = next_token(p);
    if (t->kind == TK_L_INT) {
        struct AstNode* e = ast_new(AST_INT_LIT_EXPR);
        e->int_value = atoi(t->value);
        e->ty = type_new(TY_INT);
        return e;
    } else if (t->kind == TK_L_STR) {
        int str_lit_index = register_str_lit(p, t->value);
        struct AstNode* e = ast_new(AST_STR_LIT_EXPR);
        e->int_value = str_lit_index;
        return e;
    } else if (t->kind == TK_PAREN_L) {
        struct AstNode* e = parse_expr(p);
        expect(p, TK_PAREN_R);
        return e;
    } else if (t->kind == TK_IDENT) {
        char* name = t->value;

        if (peek_token(p)->kind == TK_PAREN_L) {
            struct AstNode* e = ast_new(AST_FUNC_CALL);
            int func_index = find_func(p, name);
            if (func_index == -1) {
                char* buf = calloc(1024, sizeof(char));
                sprintf(buf, "undefined function: %s", name);
                fatal_error(buf);
            }
            e->name = name;
            e->ty = p->funcs[func_index].ty;
            return e;
        }

        int var_index = find_lvar(p, name);
        if (var_index == -1) {
            char* buf = calloc(1024, sizeof(char));
            sprintf(buf, "undefined variable: %s", name);
            fatal_error(buf);
        }

        struct AstNode* e = ast_new(AST_LVAR);
        e->name = name;
        e->var_index = var_index;
        e->ty = p->locals[var_index].ty;
        return e;
    } else {
        char* buf = calloc(1024, sizeof(char));
        sprintf(buf, "expected primary expression, but got %d", t->kind);
        fatal_error(buf);
    }
}

struct AstNode* parse_arg_list(struct Parser* p) {
    struct AstNode* list = ast_new_list(AST_ARG_LIST);
    for (0; peek_token(p)->kind != TK_PAREN_R; 0) {
        struct AstNode* arg = parse_expr(p);
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

struct AstNode* parse_postfix_expr(struct Parser* p) {
    struct AstNode* ret = parse_primary_expr(p);
    for (0; 1; 0) {
        int tk = peek_token(p)->kind;
        if (tk == TK_PAREN_L) {
            next_token(p);
            struct AstNode* args = parse_arg_list(p);
            expect(p, TK_PAREN_R);
            ret->expr1 = args;
        } else if (tk == TK_BRACKET_L) {
            next_token(p);
            struct AstNode* idx = parse_expr(p);
            expect(p, TK_BRACKET_R);

            struct AstNode* e = ast_new(AST_DEREF_EXPR);
            struct AstNode* ptr_expr = ast_new_binary_expr(TK_PLUS, ret, idx);
            ptr_expr->ty = ret->ty;
            e->expr1 = ptr_expr;
            e->ty = ret->ty->to;

            ret = e;
        } else if (tk == TK_DOT) {
            next_token(p);
            char* name = parse_ident(p);

            struct AstNode* e = ast_new(AST_DEREF_EXPR);
            struct AstNode* ref_of_ret = ast_new(AST_REF_EXPR);
            ref_of_ret->expr1 = ret;
            ref_of_ret->ty = type_new_ptr(ret->ty);
            int offset = type_offsetof(ret->ty, name);
            struct AstNode* offset_node = ast_new(AST_OFFSETOF);
            offset_node->int_value = offset;
            offset_node->ty = type_new(TY_INT);
            struct AstNode* ptr_expr = ast_new_binary_expr(TK_PLUS, ref_of_ret, offset_node);
            ptr_expr->ty = ref_of_ret->ty;
            e->expr1 = ptr_expr;
            e->ty = type_member_typeof(ret->ty, name);

            ret = e;
        } else if (tk == TK_ARROW) {
            next_token(p);
            char* name = parse_ident(p);

            struct AstNode* e = ast_new(AST_DEREF_EXPR);
            int offset = type_offsetof(ret->ty->to, name);
            struct AstNode* offset_node = ast_new(AST_OFFSETOF);
            offset_node->int_value = offset;
            offset_node->ty = type_new(TY_INT);
            struct AstNode* ptr_expr = ast_new_binary_expr(TK_PLUS, ret, offset_node);
            ptr_expr->ty = ret->ty;
            e->expr1 = ptr_expr;
            e->ty = type_member_typeof(ret->ty->to, name);

            ret = e;
        } else {
            break;
        }
    }
    return ret;
}

int is_type_token(int token_kind) {
    return token_kind == TK_K_INT || token_kind == TK_K_LONG || token_kind == TK_K_CHAR || token_kind == TK_K_VOID || token_kind == TK_K_STRUCT;
}

struct Type* parse_type(struct Parser* p) {
    struct Token* t = next_token(p);
    if (!is_type_token(t->kind)) {
        char* buf = calloc(1024, sizeof(char));
        sprintf(buf, "parse_type: unknown type, %d", t->kind);
        fatal_error(buf);
    }
    struct Type* ty = type_new(TY_UNKNOWN);
    if (t->kind == TK_K_INT) {
        ty->kind = TY_INT;
    } else if (t->kind == TK_K_LONG) {
        ty->kind = TY_LONG;
    } else if (t->kind == TK_K_CHAR) {
        ty->kind = TY_CHAR;
    } else if (t->kind == TK_K_VOID) {
        ty->kind = TY_VOID;
    } else if (t->kind == TK_K_STRUCT) {
        ty->kind = TY_STRUCT;
        char* name = parse_ident(p);
        int struct_index;
        for (struct_index = 0; struct_index < p->n_structs; struct_index = struct_index + 1) {
            if (strcmp(name, p->structs[struct_index].name) == 0) {
                break;
            }
        }
        if (struct_index == p->n_structs) {
            char* buf = calloc(1024, sizeof(char));
            sprintf(buf, "parse_type: unknown struct, %s", name);
            fatal_error(buf);
        }
        ty->members = p->structs[struct_index].node1;
    } else {
        fatal_error("unreachable");
    }
    for (0; 1; 0) {
        struct Token* t2 = peek_token(p);
        if (t2->kind == TK_STAR) {
            next_token(p);
            ty = type_new_ptr(ty);
        } else {
            break;
        }
    }
    return ty;
}

struct AstNode* parse_prefix_expr(struct Parser* p) {
    int op = peek_token(p)->kind;
    if (op == TK_MINUS) {
        next_token(p);
        struct AstNode* operand = parse_prefix_expr(p);
        struct AstNode* lhs = ast_new(AST_INT_LIT_EXPR);
        lhs->int_value = 0;
        lhs->ty = type_new(TY_INT);
        struct AstNode* e = ast_new_binary_expr(op, lhs, operand);
        e->ty = type_new(TY_INT);
        return e;
    } else if (op == TK_NOT) {
        next_token(p);
        struct AstNode* operand = parse_prefix_expr(p);
        struct AstNode* e = ast_new_unary_expr(op, operand);
        e->ty = type_new(TY_INT);
        return e;
    } else if (op == TK_AND) {
        next_token(p);
        struct AstNode* operand = parse_prefix_expr(p);
        struct AstNode* e = ast_new(AST_REF_EXPR);
        e->expr1 = operand;
        e->ty = type_new_ptr(operand->ty);
        return e;
    } else if (op == TK_STAR) {
        next_token(p);
        struct AstNode* operand = parse_prefix_expr(p);
        struct AstNode* e = ast_new(AST_DEREF_EXPR);
        e->expr1 = operand;
        e->ty = operand->ty->to;
        return e;
    } else if (op == TK_K_SIZEOF) {
        next_token(p);
        expect(p, TK_PAREN_L);
        struct Type* ty = parse_type(p);
        expect(p, TK_PAREN_R);
        struct AstNode* e = ast_new(AST_INT_LIT_EXPR);
        e->int_value = type_sizeof(ty);
        e->ty = type_new(TY_INT);
        return e;
    }
    return parse_postfix_expr(p);
}

struct AstNode* parse_multiplicative_expr(struct Parser* p) {
    struct AstNode* lhs = parse_prefix_expr(p);
    for (0; 1; 0) {
        int op = peek_token(p)->kind;
        if (op == TK_STAR || op == TK_SLASH || op == TK_PERCENT) {
            next_token(p);
            struct AstNode* rhs = parse_prefix_expr(p);
            lhs = ast_new_binary_expr(op, lhs, rhs);
            lhs->ty = type_new(TY_INT);
        } else {
            break;
        }
    }
    return lhs;
}

struct AstNode* parse_additive_expr(struct Parser* p) {
    struct AstNode* lhs = parse_multiplicative_expr(p);
    for (0; 1; 0) {
        int op = peek_token(p)->kind;
        if (op == TK_PLUS) {
            next_token(p);
            struct AstNode* rhs = parse_multiplicative_expr(p);
            struct Type* result_type;
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
            struct AstNode* rhs = parse_multiplicative_expr(p);
            struct Type* result_type;
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

struct AstNode* parse_relational_expr(struct Parser* p) {
    struct AstNode* lhs = parse_additive_expr(p);
    for (0; 1; 0) {
        int op = peek_token(p)->kind;
        if (op == TK_LT || op == TK_LE) {
            next_token(p);
            struct AstNode* rhs = parse_additive_expr(p);
            lhs = ast_new_binary_expr(op, lhs, rhs);
            lhs->ty = type_new(TY_INT);
        } else if (op == TK_GT) {
            next_token(p);
            struct AstNode* rhs = parse_additive_expr(p);
            lhs = ast_new_binary_expr(TK_LT, rhs, lhs);
            lhs->ty = type_new(TY_INT);
        } else if (op == TK_GE) {
            next_token(p);
            struct AstNode* rhs = parse_additive_expr(p);
            lhs = ast_new_binary_expr(TK_GE, rhs, lhs);
            lhs->ty = type_new(TY_INT);
        } else {
            break;
        }
    }
    return lhs;
}

struct AstNode* parse_equality_expr(struct Parser* p) {
    struct AstNode* lhs = parse_relational_expr(p);
    for (0; 1; 0) {
        int op = peek_token(p)->kind;
        if (op == TK_EQ || op == TK_NE) {
            next_token(p);
            struct AstNode* rhs = parse_relational_expr(p);
            lhs = ast_new_binary_expr(op, lhs, rhs);
            lhs->ty = type_new(TY_INT);
        } else {
            break;
        }
    }
    return lhs;
}

struct AstNode* parse_logical_and_expr(struct Parser* p) {
    struct AstNode* lhs = parse_equality_expr(p);
    for (0; 1; 0) {
        int op = peek_token(p)->kind;
        if (op == TK_ANDAND) {
            next_token(p);
            struct AstNode* rhs = parse_equality_expr(p);
            lhs = ast_new_binary_expr(op, lhs, rhs);
            lhs->ty = type_new(TY_INT);
        } else {
            break;
        }
    }
    return lhs;
}

struct AstNode* parse_logical_or_expr(struct Parser* p) {
    struct AstNode* lhs = parse_logical_and_expr(p);
    for (0; 1; 0) {
        int op = peek_token(p)->kind;
        if (op == TK_OROR) {
            next_token(p);
            struct AstNode* rhs = parse_logical_and_expr(p);
            lhs = ast_new_binary_expr(op, lhs, rhs);
            lhs->ty = type_new(TY_INT);
        } else {
            break;
        }
    }
    return lhs;
}

struct AstNode* parse_assignment_expr(struct Parser *p) {
    struct AstNode* lhs = parse_logical_or_expr(p);
    for (0; 1; 0) {
        int op = peek_token(p)->kind;
        if (op == TK_ASSIGN) {
            next_token(p);
            struct AstNode* rhs = parse_logical_or_expr(p);
            lhs = ast_new_assign_expr(op, lhs, rhs);
            lhs->ty = rhs->ty;
        } else {
            break;
        }
    }
    return lhs;
}

struct AstNode* parse_expr(struct Parser* p) {
    return parse_assignment_expr(p);
}

struct AstNode* parse_return_stmt(struct Parser* p) {
    expect(p, TK_K_RETURN);
    struct AstNode* expr = parse_expr(p);
    expect(p, TK_SEMICOLON);

    struct AstNode* ret = ast_new(AST_RETURN_STMT);
    ret->expr1 = expr;
    return ret;
}

struct AstNode* parse_if_stmt(struct Parser* p) {
    expect(p, TK_K_IF);
    expect(p, TK_PAREN_L);
    struct AstNode* cond = parse_expr(p);
    expect(p, TK_PAREN_R);
    struct AstNode* then_body = parse_stmt(p);
    struct AstNode* else_body = NULL;
    if (peek_token(p)->kind == TK_K_ELSE) {
        next_token(p);
        else_body = parse_stmt(p);
    }

    struct AstNode* stmt = ast_new(AST_IF_STMT);
    stmt->expr1 = cond;
    stmt->node1 = then_body;
    stmt->node2 = else_body;
    return stmt;
}

struct AstNode* parse_for_stmt(struct Parser* p) {
    expect(p, TK_K_FOR);
    expect(p, TK_PAREN_L);
    struct AstNode* init = parse_expr(p);
    expect(p, TK_SEMICOLON);
    struct AstNode* cond = parse_expr(p);
    expect(p, TK_SEMICOLON);
    struct AstNode* update = parse_expr(p);
    expect(p, TK_PAREN_R);
    struct AstNode* body = parse_stmt(p);

    struct AstNode* stmt = ast_new(AST_FOR_STMT);
    stmt->expr1 = init;
    stmt->expr2 = cond;
    stmt->expr3 = update;
    stmt->node1 = body;
    return stmt;
}

struct AstNode* parse_break_stmt(struct Parser* p) {
    expect(p, TK_K_BREAK);
    expect(p, TK_SEMICOLON);
    return ast_new(AST_BREAK_STMT);
}

struct AstNode* parse_continue_stmt(struct Parser* p) {
    expect(p, TK_K_CONTINUE);
    expect(p, TK_SEMICOLON);
    return ast_new(AST_CONTINUE_STMT);
}

struct AstNode* parse_var_decl(struct Parser* p) {
    struct Type* ty = parse_type(p);
    if (!type_is_unsized_type(ty)) {
        fatal_error("parse_var_decl: invalid type for variable");
    }
    char* name = parse_ident(p);

    struct AstNode* init = NULL;
    if (peek_token(p)->kind == TK_ASSIGN) {
        next_token(p);
        init = parse_expr(p);
    }
    expect(p, TK_SEMICOLON);

    if (find_lvar(p, name) != -1) {
        char* buf = calloc(1024, sizeof(char));
        sprintf(buf, "parse_var_decl: %s redeclared", name);
        fatal_error(buf);
    }
    p->locals[p->n_locals].name = name;
    p->locals[p->n_locals].ty = ty;
    p->n_locals = p->n_locals + 1;

    struct AstNode* ret;
    if (init) {
        struct AstNode* lhs = ast_new(AST_LVAR);
        lhs->name = name;
        lhs->var_index = p->n_locals - 1;
        lhs->ty = ty;
        struct AstNode* assign = ast_new_assign_expr(TK_ASSIGN, lhs, init);
        assign->ty = ty;
        ret = ast_new(AST_EXPR_STMT);
        ret->expr1 = assign;
    } else {
        ret = ast_new(AST_VAR_DECL);
    }
    return ret;
}

struct AstNode* parse_expr_stmt(struct Parser* p) {
    struct AstNode* e = parse_expr(p);
    expect(p, TK_SEMICOLON);
    struct AstNode* stmt = ast_new(AST_EXPR_STMT);
    stmt->expr1 = e;
    return stmt;
}

struct AstNode* parse_block_stmt(struct Parser* p) {
    struct AstNode* list = ast_new_list(AST_BLOCK);
    expect(p, TK_BRACE_L);
    for (0; peek_token(p)->kind != TK_BRACE_R; 0) {
        struct AstNode* stmt = parse_stmt(p);
        list->last->next = stmt;
        list->last = stmt;
    }
    expect(p, TK_BRACE_R);
    return list;
}

struct AstNode* parse_stmt(struct Parser* p) {
    struct Token* t = peek_token(p);
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

void enter_func(struct Parser* p) {
    p->locals = calloc(LVAR_MAX, sizeof(struct LVar));
    p->n_locals = 0;
}

void register_params(struct Parser* p, struct AstNode* params) {
    struct AstNode* param = params->next;
    for (0; param; 0) {
        p->locals[p->n_locals].name = param->name;
        p->locals[p->n_locals].ty = param->ty;
        p->n_locals = p->n_locals + 1;
        param = param->next;
    }
}

void register_func(struct Parser* p, char* name, struct Type* ty) {
    p->funcs[p->n_funcs].name = name;
    p->funcs[p->n_funcs].ty = ty;
    p->n_funcs = p->n_funcs + 1;
}

struct AstNode* parse_param(struct Parser* p) {
    struct Type* ty = parse_type(p);
    if (!type_is_unsized_type(ty)) {
        fatal_error("parse_param: invalid type for variable");
    }
    char* name = parse_ident(p);
    struct AstNode* param = ast_new(AST_PARAM);
    param->ty = ty;
    param->name = name;
    return param;
}

struct AstNode* parse_param_list(struct Parser* p) {
    struct AstNode* list = ast_new_list(AST_PARAM_LIST);
    for (0; peek_token(p)->kind != TK_PAREN_R; 0) {
        struct AstNode* param = parse_param(p);
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

struct AstNode* parse_func_decl_or_def(struct Parser* p) {
    struct Type* ty = parse_type(p);
    char* name = parse_ident(p);
    register_func(p, name, ty);
    expect(p, TK_PAREN_L);
    struct AstNode* params = parse_param_list(p);
    expect(p, TK_PAREN_R);
    if (peek_token(p)->kind == TK_SEMICOLON) {
        next_token(p);
        return ast_new(AST_FUNC_DECL);
    }
    enter_func(p);
    register_params(p, params);
    struct AstNode* body = parse_block_stmt(p);
    struct AstNode* func = ast_new(AST_FUNC_DEF);
    func->ty = ty;
    func->name = name;
    func->func_params = params;
    func->func_body = body;
    return func;
}

struct AstNode* parse_struct_member(struct Parser* p) {
    struct Type* ty = parse_type(p);
    char* name = parse_ident(p);
    expect(p, TK_SEMICOLON);
    struct AstNode* member = ast_new(AST_STRUCT_MEMBER);
    member->name = name;
    member->ty = ty;
    return member;
}

struct AstNode* parse_struct_members(struct Parser* p) {
    struct AstNode* list = ast_new_list(AST_STRUCT_MEMBER_LIST);
    for (0; peek_token(p)->kind != TK_BRACE_R; 0) {
        struct AstNode* member = parse_struct_member(p);
        list->last->next = member;
        list->last = member;
    }
    return list;
}

struct AstNode* parse_struct_decl_or_def(struct Parser* p) {
    expect(p, TK_K_STRUCT);
    char* name = parse_ident(p);

    if (peek_token(p)->kind != TK_SEMICOLON && peek_token(p)->kind != TK_BRACE_L) {
        p->pos = p->pos - 2;
        return parse_func_decl_or_def(p);
    }

    int struct_index;
    for (struct_index = 0; struct_index < p->n_structs; struct_index = struct_index + 1) {
        if (strcmp(name, p->structs[struct_index].name) == 0) {
            break;
        }
    }
    if (struct_index == p->n_structs) {
        p->structs[struct_index].name = name;
        p->n_structs = p->n_structs + 1;
    }
    if (peek_token(p)->kind == TK_SEMICOLON) {
        next_token(p);
        return ast_new(AST_STRUCT_DECL);
    }
    if (p->structs[struct_index].node1) {
        char* buf = calloc(1024, sizeof(char));
        sprintf(buf, "parse_struct_decl_or_def: struct %s redefined", name);
        fatal_error(buf);
    }
    expect(p, TK_BRACE_L);
    struct AstNode* members = parse_struct_members(p);
    expect(p, TK_BRACE_R);
    expect(p, TK_SEMICOLON);
    struct AstNode* s = ast_new(AST_STRUCT_DEF);
    s->name = name;
    s->node1 = members;
    p->structs[struct_index].node1 = members;
    return s;
}

struct AstNode* parse_toplevel(struct Parser* p) {
    if (peek_token(p)->kind == TK_K_STRUCT) {
        return parse_struct_decl_or_def(p);
    } else {
        return parse_func_decl_or_def(p);
    }
}

struct AstNode* parse(struct Parser* p) {
    struct AstNode* list = ast_new_list(AST_PROGRAM);
    for (0; eof(p); 0) {
        struct AstNode* n = parse_toplevel(p);
        list->last->next = n;
        list->last = n;
    }
    list->str_literals = p->str_literals;
    return list;
}

#define GEN_LVAL 0
#define GEN_RVAL 1

struct CodeGen {
    int next_label;
    int* loop_labels;
};

struct CodeGen* codegen_new() {
    struct CodeGen* g = calloc(1, sizeof(struct CodeGen));
    g->next_label = 1;
    g->loop_labels = calloc(1024, sizeof(int));
    return g;
}

void assert_ast_kind(struct AstNode* ast, int kind) {
    if (ast->kind != kind) {
        char* buf = calloc(1024, sizeof(char));
        sprintf(buf, "invalid ast kind: expected %d, but got %d", kind, ast->kind);
        fatal_error(buf);
    }
}

int gen_new_label(struct CodeGen* g) {
    int new_label = g->next_label;
    g->next_label = g->next_label + 1;
    return new_label;
}

void gen_expr(struct CodeGen* g, struct AstNode* ast, int gen_mode);
void gen_stmt(struct CodeGen* g, struct AstNode* ast);

void gen_func_prologue(struct CodeGen* g, struct AstNode* ast) {
    printf("  # gen_func_prologue\n");

    printf("  push rbp\n");
    printf("  mov rbp, rsp\n");
    int param_index = 0;
    struct AstNode* param = ast->func_params->next;
    for (0; param; 0) {
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
        param_index = param_index + 1;
        param = param->next;
    }
    printf("  sub rsp, %d\n", 8 * LVAR_MAX);
}

void gen_func_epilogue(struct CodeGen* g, struct AstNode* ast) {
    printf("  # gen_func_epilogue\n");

    printf("  mov rsp, rbp\n");
    printf("  pop rbp\n");
    printf("  ret\n");
}

void gen_int_lit_expr(struct CodeGen* g, struct AstNode* ast) {
    assert_ast_kind(ast, AST_INT_LIT_EXPR);
    printf("  # gen_int_lit_expr\n");

    printf("  push %d\n", ast->int_value);
}

void gen_offsetof(struct CodeGen* g, struct AstNode* ast) {
    assert_ast_kind(ast, AST_OFFSETOF);
    printf("  # gen_offsetof\n");

    printf("  push %d\n", ast->int_value);
}

void gen_str_lit_expr(struct CodeGen* g, struct AstNode* ast) {
    assert_ast_kind(ast, AST_STR_LIT_EXPR);
    printf("  # gen_str_lit_expr\n");

    printf("  mov rax, OFFSET FLAG:.Lstr__%d\n", ast->int_value);
    printf("  push rax\n");
}

void gen_unary_expr(struct CodeGen* g, struct AstNode* ast) {
    assert_ast_kind(ast, AST_UNARY_EXPR);
    printf("  # gen_unary_expr\n");

    gen_expr(g, ast->expr1, GEN_RVAL);
    if (ast->op == TK_NOT) {
        printf("  pop rax\n");
        printf("  mov rdi, 0\n");
        printf("  cmp rax, rdi\n");
        printf("  sete al\n");
        printf("  movzb rax, al\n");
        printf("  push rax\n");
    } else {
        todo();
    }
}

void gen_ref_expr(struct CodeGen* g, struct AstNode* ast, int gen_mode) {
    assert_ast_kind(ast, AST_REF_EXPR);
    printf("  # gen_ref_expr\n");

    gen_expr(g, ast->expr1, GEN_LVAL);
}

void gen_deref_expr(struct CodeGen* g, struct AstNode* ast, int gen_mode) {
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

void gen_logical_expr(struct CodeGen* g, struct AstNode* ast) {
    assert_ast_kind(ast, AST_BINARY_EXPR);
    printf("  # gen_logical_expr\n");

    int label = gen_new_label(g);

    if (ast->op == TK_ANDAND) {
        gen_expr(g, ast->expr1, GEN_RVAL);
        printf("  pop rax\n");
        printf("  cmp rax, 0\n");
        printf("  je .Lelse%d\n", label);
        gen_expr(g, ast->expr2, GEN_RVAL);
        printf("  jmp .Lend%d\n", label);
        printf(".Lelse%d:\n", label);
        printf("  push 0\n");
        printf(".Lend%d:\n", label);
    } else {
        gen_expr(g, ast->expr1, GEN_RVAL);
        printf("  pop rax\n");
        printf("  cmp rax, 0\n");
        printf("  je .Lelse%d\n", label);
        printf("  push 1\n");
        printf("  jmp .Lend%d\n", label);
        printf(".Lelse%d:\n", label);
        gen_expr(g, ast->expr2, GEN_RVAL);
        printf(".Lend%d:\n", label);
    }
}

void gen_binary_expr(struct CodeGen* g, struct AstNode* ast, int gen_mode) {
    assert_ast_kind(ast, AST_BINARY_EXPR);
    printf("  # gen_binary_expr\n");

    if (ast->op == TK_ANDAND || ast->op == TK_OROR) {
        gen_logical_expr(g, ast);
        return;
    }

    gen_expr(g, ast->expr1, gen_mode);
    gen_expr(g, ast->expr2, gen_mode);
    printf("  pop rdi\n");
    printf("  pop rax\n");
    if (ast->op == TK_PLUS) {
        if (ast->expr1->ty->kind == TY_PTR) {
            if (ast->expr2->kind != AST_OFFSETOF) {
                printf("  shl rdi, %d\n", type_ptr_shift_width(ast->expr1->ty));
            }
            printf("  add rax, rdi\n");
        } else if (ast->expr2->ty->kind == TY_PTR) {
            if (ast->expr1->kind != AST_OFFSETOF) {
                printf("  shl rdi, %d\n", type_ptr_shift_width(ast->expr2->ty));
            }
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

void gen_assign_expr(struct CodeGen* g, struct AstNode* ast) {
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

void gen_func_call(struct CodeGen* g, struct AstNode* ast) {
    assert_ast_kind(ast, AST_FUNC_CALL);
    printf("  # gen_func_call\n");

    char* func_name = ast->name;
    struct AstNode* args = ast->expr1;
    struct AstNode* arg = args->next;
    int n_args = 0;
    for (0; arg; 0) {
        n_args = n_args + 1;
        gen_expr(g, arg, GEN_RVAL);
        arg = arg->next;
    }
    for (int i = n_args - 1; i >= 0; i = i - 1) {
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
    printf("  mov rax, 0\n");
    printf("  call %s\n", func_name);
    printf("  push rax\n");
}

void gen_lvar(struct CodeGen* g, struct AstNode* ast, int gen_mode) {
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

void gen_expr(struct CodeGen* g, struct AstNode* ast, int gen_mode) {
    if (ast->kind == AST_INT_LIT_EXPR) {
        gen_int_lit_expr(g, ast);
    } else if (ast->kind == AST_OFFSETOF) {
        gen_offsetof(g, ast);
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

void gen_return_stmt(struct CodeGen* g, struct AstNode* ast) {
    assert_ast_kind(ast, AST_RETURN_STMT);
    printf("  # gen_return_stmt\n");

    gen_expr(g, ast->expr1, GEN_RVAL);
    printf("  pop rax\n");
    gen_func_epilogue(g, ast);
}

void gen_if_stmt(struct CodeGen* g, struct AstNode* ast) {
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

void gen_for_stmt(struct CodeGen* g, struct AstNode* ast) {
    assert_ast_kind(ast, AST_FOR_STMT);
    printf("  # gen_for_stmt\n");

    int label = gen_new_label(g);
    g->loop_labels = g->loop_labels + 1;
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

    g->loop_labels = g->loop_labels - 1;
}

void gen_break_stmt(struct CodeGen* g, struct AstNode* ast) {
    assert_ast_kind(ast, AST_BREAK_STMT);
    printf("  # gen_break_stmt\n");

    int label = *g->loop_labels;
    printf("  jmp .Lend%d\n", label);
}

void gen_continue_stmt(struct CodeGen* g, struct AstNode* ast) {
    assert_ast_kind(ast, AST_CONTINUE_STMT);
    printf("  # gen_continue_stmt\n");

    int label = *g->loop_labels;
    printf("  jmp .Lcontinue%d\n", label);
}

void gen_expr_stmt(struct CodeGen* g, struct AstNode* ast) {
    gen_expr(g, ast->expr1, GEN_RVAL);
    printf("  pop rax\n");
}

void gen_var_decl(struct CodeGen* g, struct AstNode* ast) {
}

void gen_block_stmt(struct CodeGen* g, struct AstNode* ast) {
    assert_ast_kind(ast, AST_BLOCK);
    struct AstNode* stmt = ast->next;
    for (0; stmt; 0) {
        gen_stmt(g, stmt);
        stmt = stmt->next;
    }
}

void gen_stmt(struct CodeGen* g, struct AstNode* ast) {
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
        char* buf = calloc(1024, sizeof(char));
        sprintf(buf, "gen_stmt: expected statement ast, but got %d", ast->kind);
        fatal_error(buf);
    }
}

void gen_func(struct CodeGen* g, struct AstNode* ast) {
    assert_ast_kind(ast, AST_FUNC_DEF);
    printf("%s:\n", ast->name);

    gen_func_prologue(g, ast);
    gen_stmt(g, ast->func_body);
    gen_func_epilogue(g, ast);
    printf("\n");
}

void gen(struct CodeGen* g, struct AstNode* ast) {
    assert_ast_kind(ast, AST_PROGRAM);

    printf(".intel_syntax noprefix\n\n");

    char** str_lit = ast->str_literals;
    for (0; *str_lit; 0) {
        printf(".Lstr__%d:\n", str_lit - ast->str_literals + 1);
        printf("  .string \"%s\"\n\n", *str_lit);
        str_lit = str_lit + 1;
    }

    printf(".globl main\n\n");

    struct AstNode* func = ast->next;
    for (0; func; 0) {
        if (func->kind == AST_FUNC_DEF) {
            gen_func(g, func);
        }
        func = func->next;
    }
}

int main() {
    char* source = calloc(1024*1024, sizeof(char));
    int source_len = read_all(source);
    struct Token* tokens = tokenize(source, source_len);

    struct Parser* parser = parser_new(tokens);
    struct AstNode* ast = parse(parser);

    struct CodeGen* code_generator = codegen_new();
    gen(code_generator, ast);

    return 0;
}
