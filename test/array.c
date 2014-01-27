
/**
 * `test/array.c` - libjson
 *
 * copyright (c) 2014 - joseph werle <joseph.werle@gmail.com>
 */

#include <string.h>
#include <json/test.h>
#include <json/type.h>
#include <json/string.h>
#include <json/boolean.h>
#include <json/null.h>
#include <json/number.h>
#include <json/object.h>
#include <json/array.h>
#include <ok.h>

TEST(array) {
  json_array_t *array = json_array_new();
  json_object_t *obj = json_object_new();
  json_number_t *num = json_number_new(32);
  json_null_t *null = json_null_new();
  json_boolean_t *t = json_boolean_new(1);
  json_boolean_t *f = json_boolean_new(0);
  json_string_t *foo = json_string_new("foo");
  json_string_t *bar = json_string_new("bar");


  t(json_array_push(array, (json_value_t*) foo));

  t(1 == array->length);
  t(0 == strcmp("foo", json_array_pop(array)->data));
  t(0 == array->length);

  t(json_array_push(array, (json_value_t*) foo));
  t(json_array_unshift(array, (json_value_t*) bar));

  t(2 == array->length);

  t(0 == strcmp("bar", json_array_shift(array)->data));
  t(1 == array->length);
  t(0 == strcmp("foo", json_array_pop(array)->data));
  t(0 == array->length);

  t(json_array_push(array, (json_value_t *) t));
  t(json_array_push(array, (json_value_t *) f));
  t(2 == array->length);

  t(1 == json_array_indexof(array, (json_value_t *) f));
  t(0 == json_array_indexof(array, (json_value_t *) t));

  json_array_each(array, value, {
      t(0 == strcmp("boolean", json_typeof(value)));
  });

  printf("%s\n", json_array_to_string(array));

  ok("array");
  return 0;
}
