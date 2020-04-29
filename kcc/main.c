#include "kcc.h"

int main(int argc, char **argv) {
  if (argc != 2)
    error("%s: 引数の個数が正しくありません", argv[0]);

  // 字句解析して構文解析する
  user_input = argv[1];
  token = tokenize();
  Node *node = program();

  // AST(抽象構文木)からアセンブリプログラムを出力する
  codegen(node);
  return 0;
}
