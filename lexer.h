#include "./common_headers.h"
#include "deps/str_view.h"

enum tkind {
  INVALID = 0,
  RETURN = 1,
  INT = 2,
  STRING = 3,
  ASSIGNMENT = 4,
  TOTAL_KINDS = 5,
};

char* keywords[] = {"return", "int", "string", "="};

struct lexer {
  enum tkind tkind;
  char* value;
  int error_loc;
};

int get_token(str_view view) {
  view = sv_chop_left(view);
  view = sv_trim_right(view, 1);
  sv_print(view);
  return INVALID;
  for(int i = 0; i < TOTAL_KINDS; i++) {
    if(strncmp(view.data, keywords[i], strlen(keywords[i])) == 0) {
      printf("%s %d\n", keywords[i], i);
      return i;
    }
  }
  return INVALID;
}
