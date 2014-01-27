
/**
 * `type.c` - libjson
 *
 * copyright (c) 2014 - joseph werle <joseph.werle@gmail.com>
 */

#include <json/type.h>
#include <json/value.h>

const char *
json_typeof (void *value) {
  return ((json_value_t *) value)->name;
}
