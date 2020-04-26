#ifndef KCC_H
#define KCC_H
//------------------------------------------------
#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//------------------------------------------------
//  マクロ定義(Macro definition)
//------------------------------------------------

//------------------------------------------------
//  型定義(Type definition)
//------------------------------------------------
typedef enum {
  TK_RESERVED, // 記号
  TK_NUM,      // 整数トークン
  TK_EOF,      // 入力の終わりを表すトークン
} TokenKind;
// トークン型
typedef struct Token Token;
struct Token {
  TokenKind kind; // トークンの型
  Token *next;    // 次の入力トークン
  int val;        // kindがTK_NUMの場合、その数値
  char *str;      // トークン文字列
  int len;        // トークン文字列長
};
typedef enum {
  ND_ADD, // +
  ND_SUB, // -
  ND_MUL, // *
  ND_DIV, // /
  ND_EQ,  // ==
  ND_NE,  // !=
  ND_LT,  // <
  ND_LE,  // <=
  ND_NUM, // 整数
} NodeKind;
// AST(抽象構文木)のノードの型
typedef struct Node Node;
struct Node {
  NodeKind kind; // ノードの型
  Node *lhs;     // 左辺
  Node *rhs;     // 右辺
  int val;       // kindがND_NUMの場合のみ使う
};

//------------------------------------------------
//  プロトタイプ宣言(Prototype declaration)
//------------------------------------------------
// 入力プログラム
char *user_input;
// 現在着目しているトークン
Token *token;
// エラーを報告するための関数
void error(char *fmt, ...);
// エラー箇所を報告する
void error_at(char *loc, char *fmt, ...);
// 次のトークンが期待している記号の時には、トークンを一つ読み進めて真を返す。それ以外の場合には偽を返す。
bool consume(char *op);
// 次のトークンが期待している記号の時には、トークンを一つ読み進める。それ以外の場合にはエラーを報告する。
void expect(char *op);
// 次のトークンが数値の場合、トークンを1つ読み進めてその数値を返す。それ以外の場合にはエラーを報告する。
int expect_number();
bool at_eof();
// 新しいトークンを作成してcurに繋げる
Token *new_token(TokenKind kind, Token *cur, char *str, int len);
bool startswith(char *p, char *q);
// 入力文字列pを字句解析してそれを返す
Token *tokenize();
Node *new_node(NodeKind kind);
Node *new_binary(NodeKind kind, Node *lhs, Node *rhs);
Node *new_num(int val);
// トークンを構文解析する
Node *expr();
Node *equality();
Node *relational();
Node *add();
Node *mul();
Node *unary();
Node *primary();
// 機械語を生成する
void gen(Node *node);

//------------------------------------------------
#endif
