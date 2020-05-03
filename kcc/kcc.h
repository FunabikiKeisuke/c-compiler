#ifndef KCC_H
#define KCC_H
//------------------------------------------------
#define _GNU_SOURCE
#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//------------------------------------------------
// tokenize.c
//------------------------------------------------

//
//  マクロ定義(Macro definition)
//

//
//  型定義(Type definition)
//

// トークン
typedef enum {
  TK_RESERVED, // 記号
  TK_IDENT,    // 識別子
  TK_NUM,      // 整数トークン
  TK_EOF,      // 入力の終わりを表すトークン
} TokenKind;

// トークン型
typedef struct Token Token;
struct Token {
  TokenKind kind; // トークンの型
  Token *next;    // 次の入力トークン
  long val;       // kindがTK_NUMの場合、その数値
  char *str;      // トークン文字列
  int len;        // トークン文字列長
};

//
//  プロトタイプ宣言(Prototype declaration)
//

void error(char *fmt, ...);
void error_at(char *loc, char *fmt, ...);
bool consume(char *op);
Token *consume_ident(void);
void expect(char *op);
long expect_number(void);
bool at_eof(void);
Token *tokenize(void);

extern char *user_input;
extern Token *token;


//------------------------------------------------
// parse.c
//------------------------------------------------

//
//  マクロ定義(Macro definition)
//

//
//  型定義(Type definition)
//

// ローカル変数
typedef struct Var Var;
struct Var {
  Var *next;
  char *name; // 変数名
  int offset; // RBPからのオフセット
};

// ASTノード
typedef enum {
  ND_ADD,       // +
  ND_SUB,       // -
  ND_MUL,       // *
  ND_DIV,       // /
  ND_EQ,        // ==
  ND_NE,        // !=
  ND_LT,        // <
  ND_LE,        // <=
  ND_ASSIGN,    // =
  ND_RETURN,    // "return"
  ND_EXPR_STMT, // 式ステートメント
  ND_VAR,       // 変数
  ND_NUM,       // 整数
} NodeKind;

// AST(抽象構文木)のノードの型
typedef struct Node Node;
struct Node {
  NodeKind kind; // ノードの型
  Node *next;    // 次の入力ノード
  Node *lhs;     // 左辺
  Node *rhs;     // 右辺
  Var *var;     // kindがND_VARの場合のみ使う
  long val;      // kindがND_NUMの場合のみ使う
};

//
//  プロトタイプ宣言(Prototype declaration)
//

typedef struct Function Function;
struct Function {
  Node *node;
  Var *locals;
  int stack_size;
};

Function *program(void);


//------------------------------------------------
// codegen.c
//------------------------------------------------

//
//  マクロ定義(Macro definition)
//

//
//  型定義(Type definition)
//

//
//  プロトタイプ宣言(Prototype declaration)
//

void codegen(Function *prog);

//------------------------------------------------
#endif
