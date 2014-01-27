
/**
 * `test/boolean.c` - libjson
 *
 * copyright (c) 2014 - joseph werle <joseph.werle@gmail.com>
 */

#include <stdbool.h>
#include <json/test.h>
#include <json/boolean.h>
#include <ok.h>

TEST(boolean) {
  json_boolean_t *boolean = json_boolean_new(0);
  t(boolean);
  t(0 == boolean->data);
  t(false == boolean->data);
  ok("boolean");
  return 0;
}
