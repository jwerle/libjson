
/**
 * `test/number.c` - libjson
 *
 * copyright (c) 2014 - joseph werle <joseph.werle@gmail.com>
 */

#include <json/test.h>
#include <json/number.h>
#include <ok.h>

TEST(number) {
  json_number_t *number = json_number_new(22.3);
  t(number);
  t(22.3 == number->data);
  ok("number");
  return 0;
}
