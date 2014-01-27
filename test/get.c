
/**
 * `test/get.c` - libjson
 *
 * copyright (c) 2014 - joseph werle <joseph.werle@gmail.com>
 */

#include <string.h>
#include <json/test.h>
#include <json.h>
#include <ok.h>

TEST(get) {
  // value
  json_value_t *value = NULL;
  value = json_value_new((int *) 1234);
  t(1234 == (int) json_get(value));

  value = json_value_new(NULL);
  t(NULL == json_get(value));

  value = json_value_new("beep boop");
  t(0 == strcmp("beep boop", json_get(value)));

  // null
  json_null_t *null = json_null_new();
  t(NULL == json_get(null));

  // boolean
  json_boolean_t *boolean = json_boolean_new(1);
  t(1  == json_get(boolean));

  // number
  json_number_t *number = json_number_new(1.2);
  t(1.2 == json_get(number));

  // string


  // array


  // object


  ok("get");
  return 0;
}
