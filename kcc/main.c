#include "kcc.h"

int main(int argc, char **argv) {
  if (argc != 2)
    error("%s: 引数の個数が正しくありません", argv[0]);

  // 字句解析して構文解析する
  user_input = argv[1];
  token = tokenize();
  Node *node = expr();

  // アセンブリの前半部分を出力
  printf(".intel_syntax noprefix\n");
  printf(".global main\n");
  printf("main:\n");

  // AST(抽象構文木)を下りながらコード生成
  gen(node);

  // スタックトップに式全体の値が残っているはずなので
  // それをRAXにロードして関数からの返り値とする
  printf("  pop rax\n");
  printf("  ret\n");
  return 0;
}
