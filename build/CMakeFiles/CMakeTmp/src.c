
#include <udunits2.h>

int main(int argc, char **argv) {
  ut_system *s = ut_read_xml(NULL);
  ut_free_system(s);
  return 0;
}

