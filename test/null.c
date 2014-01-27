
/**
 * `test/null.c` - libjson
 *
 * copyright (c) 2014 - joseph werle <joseph.werle@gmail.com>
 */

#include <json/test.h>
#include <json/null.h>
#include <ok.h>

TEST(null) {
  json_null_t *null = json_null_new();
  t(null);
  t(NULL == null->data);
  ok("null");
  return 0;
}
