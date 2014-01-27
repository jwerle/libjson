
/**
 * `test/type.c` - libjson
 *
 * copyright (c) 2014 - joseph werle <joseph.werle@gmail.com>
 */

#include <string.h>
#include <json/test.h>
#include <json.h>
#include <ok.h>

TEST(type) {
  t(0 == strcmp("value", json_typeof(json_value_new((int *) 52))));
  t(0 == strcmp("null", json_typeof(json_null_new())));
  t(0 == strcmp("boolean", json_typeof(json_boolean_new(1))));
  t(0 == strcmp("number", json_typeof(json_number_new(10))));
  t(0 == strcmp("string", json_typeof(json_string_new("1234"))));
  ok("type");
  return 0;
}
