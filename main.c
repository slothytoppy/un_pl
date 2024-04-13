#include "deps/str_view.h"
#include "lexer.h"

int main(int argc, char** argv) {
  if(argc <= 1) {
    printf("usage: %s <file>\n", argv[0]);
    return 1;
  }
  struct stat fi;
  stat(argv[1], &fi);
  str_view view = {0};
  int fd = open(argv[1], O_RDONLY);
  char* file = mmap(file, fi.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
  view = sv_from_cstr(file);
  for(int i = 0; i < fi.st_size; i++) {
    int tok = get_token(view);
  }
}
