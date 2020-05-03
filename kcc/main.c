#include "kcc.h"

int main(int argc, char **argv) {
  if (argc != 2)
    error("%s: 引数の個数が正しくありません", argv[0]);

  // 字句解析して構文解析する
  user_input = argv[1];
  token = tokenize();
  Function *prog = program();

  // ローカル変数にオフセットを割り当てる
  int offset = 0;
  for (Var *var = prog->locals; var; var = var->next) {
    offset += 8;
    var->offset = offset;
  }
  prog->stack_size = offset;

  // AST(抽象構文木)からアセンブリプログラムを出力する
  codegen(prog);
  return 0;
}
