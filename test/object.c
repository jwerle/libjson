
/**
 * `test/object.c` - libjson
 *
 * copyright (c) 2014 - joseph werle <joseph.werle@gmail.com>
 */

#include <json/test.h>
#include <json/string.h>
#include <json/object.h>
#include <ok.h>

TEST(object) {
  json_object_t *obj = json_object_new();
  t(obj);

  // set
  json_object_set(obj, "foo", (json_value_t *) json_string_new("bar"));

  // get
  t(0 == strcmp("bar",
        ((json_value_t *) json_object_get(obj, "foo"))->data));

  ok("object");
  return 0;
}
