#ifndef STR_VIEW_H
#define STR_VIEW_H
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Str_view str_view;

struct Str_view {
  unsigned len;
  char* data;
};

unsigned sv_suffix(str_view sv, str_view suffix);
unsigned sv_equal(str_view a, str_view b);

str_view sv_from_parts(char* data, unsigned len) {
  str_view sv = {.data = data, .len = len};
  return sv;
}

str_view sv_from_cstr(char* data) {
  return sv_from_parts(data, strlen(data));
}

str_view sv_trim_left(str_view sv, unsigned count) {
  return sv_from_parts(sv.data + count, sv.len - count);
}

str_view sv_trim_right(str_view sv, unsigned count) {
  return sv_from_parts(sv.data, sv.len - count);
}

str_view sv_chop_left(str_view sv) {
  int i = 0;
  for(i = 0; i < sv.len && sv.data[i] == ' '; i++)
    ;
  return sv_from_parts(sv.data + i, sv.len - i);
}

str_view sv_chop_right(str_view sv) {
  int i = 0;
  for(i = 0; i < sv.len && sv.data[sv.len - i] == ' '; i++)
    ;
  return sv_from_parts(sv.data, sv.len - i);
}

void sv_print(str_view sv) {
  if(sv.len < 0) {
    return;
  }
  printf("%.*s\n", sv.len, sv.data);
  return;
}

str_view sv_concat(str_view dest, str_view src) {
  str_view cpy;
  cpy.data = (char*)calloc(1, dest.len + src.len);
  memcpy(cpy.data, dest.data, dest.len);
  memcpy(cpy.data + dest.len, src.data, src.len);
  cpy.len = dest.len + src.len;
  return cpy;
}

unsigned sv_prefix(str_view sv, str_view prefix) {
  if(prefix.len <= sv.len) {
    str_view expected = sv_from_parts(sv.data, prefix.len);
    return sv_equal(expected, prefix);
  }
  return 0;
}

unsigned sv_suffix(str_view sv, str_view suffix) {
  if(suffix.len <= sv.len) {
    str_view expected =
        sv_from_parts(sv.data + sv.len - suffix.len, suffix.len);
    return sv_equal(expected, suffix);
  }
  return 0;
}

unsigned sv_equal(str_view a, str_view b) {
  if(a.len != b.len) {
    return 0;
  }
  if(memcmp(a.data, b.data, a.len) == 0) {
    return 1;
  } else {
    return 0;
  }
  return 0;
}

#endif // STR_VIEW_H
