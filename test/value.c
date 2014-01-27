
/**
 * `test/value.c` - libjson
 *
 * copyright (c) 2014 - joseph werle <joseph.werle@gmail.com>
 */

#include <string.h>
#include <json/test.h>
#include <json/value.h>
#include <ok.h>

TEST(value) {
  json_value_t *value = NULL;

  value = json_value_new("123");
  t(value);
  t(0 == strcmp("123", value->data));

  value = json_value_new((int *) 123);
  t(value);
  t(123 == (int) value->data);

  value = json_value_new(NULL);
  t(value);
  t(NULL == value->data);

  value = json_value_new((char *) 'a');
  t(value);
  t('a' == (char) value->data);

  ok("value");
  return 0;
}
