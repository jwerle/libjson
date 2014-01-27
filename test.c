
/**
 * `test.c` - libjson
 *
 * copyright (c) 2014 - joseph werle <joseph.werle@gmail.com>
 */

#include <json/test.h>
#include <ok.h>

int
main (void) {

  RUN(value);
  RUN(boolean);
  RUN(null);
  RUN(number);
  RUN(string);
  RUN(object);
  RUN(array);

  RUN(type);
  RUN(get);

  RUN(tokenizer);

  ok_done();
  return 0;
}
