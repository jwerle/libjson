
/**
 * `test/string.c` - libjson
 *
 * copyright (c) 2014 - joseph werle <joseph.werle@gmail.com>
 */

#include <json/test.h>
#include <json/string.h>
#include <ok.h>

TEST(string) {
  json_string_t *string = json_string_new("foo biz baz");
  t(string);
  ok("string");
  return 0;
}
