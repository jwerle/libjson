
/**
 * `object.c` - libjson
 *
 * copyright (c) 2014 - joseph werle <joseph.werle@gmail.com>
 */

#include <hash/hash.h>
#include <json/object.h>

json_object_t *
json_object_new () {
  json_object_t *self = (json_object_t *) malloc(sizeof(json_object_t));

  if (NULL == self) {
    return NULL;
  }

  self->name = "object";
  self->type = JSON_TYPE_OBJECT;
  self->hash = hash_new();
  self->data = &self->hash;
  self->to_string = json_object_to_string;

  return self;
}

void
json_object_set (json_object_t *self, const char *key, json_value_t *value) {
  hash_set(self->hash, (char *) key, (void *) value);
}

json_value_t *
json_object_get (json_object_t *self, const char *key) {
  json_value_t *value = NULL;
  value = (json_value_t *) hash_get(self->hash, (char *) key);
  return value;
}

char *
json_object_to_string (json_object_t *self) {
  return (char *) self->name;
}
