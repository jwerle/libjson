#include <stdio.h>
/**
 * `array.c` - libjson
 *
 * copyright (c) 2014 - joseph werle <joseph.werle@gmail.com>
 */

#include <list/list.h>
#include <buffer/buffer.h>
#include <json/array.h>

json_array_t *
json_array_new () {
  json_array_t *self = (json_array_t *) malloc(sizeof(json_array_t));

  if (NULL == self) {
    return NULL;
  }

  self->name = "array";
  self->type = JSON_TYPE_ARRAY;
  self->list = list_new();
  self->data = &self->list;
  self->length = 0;

  return self;
}

int
json_array_push (json_array_t *self, json_value_t *value) {
  list_node_t *node = list_node_new(value);
  list_rpush(self->list, node);
  return (self->length = self->list->len);
}

int
json_array_unshift (json_array_t *self, json_value_t *value) {
  list_node_t *node = list_node_new(value);
  list_lpush(self->list, node);
  return (self->length = self->list->len);
}

json_value_t *
json_array_pop (json_array_t *self) {
  if (0 == self->list->len) {
    return NULL;
  }
  list_node_t *node = list_rpop(self->list);
  if (NULL == node) {
    return NULL;
  }
  self->length = self->list->len;
  return (json_value_t *) node->val;
}

json_value_t *
json_array_shift (json_array_t *self) {
  if (0 == self->list->len) {
    return NULL;
  }
  list_node_t *node = list_lpop(self->list);
  if (NULL == node) {
    return NULL;
  }
  self->length = self->list->len;
  return (json_value_t *) node->val;
}

int
json_array_indexof (json_array_t *self, json_value_t *value) {
  int idx = -1;
  list_iterator_t *it = list_iterator_new(self->list, LIST_HEAD);
  list_node_t *node;

  while ((node = list_iterator_next(it))) {
    idx++;
    if (self->list->match) {
      if (self->list->match(value, node->val)) {
        list_iterator_destroy(it);
        return idx;
      }
    } else {
      if (value == node->val) {
        list_iterator_destroy(it);
        return idx;
      }
    }
  }

  list_iterator_destroy(it);
  return idx;
}

char *
json_array_to_string (json_array_t *self) {
  buffer_t *buf = buffer_new();
  int first = 1;

  // left brace
  buffer_append(buf, "[");

  // elements
  json_array_each(self, value, {
      if (0 == first) {
        buffer_append(buf, ",");
      }
      first = 0;

      printf("%s\n", value->to_string(value));
      //buffer_append(buf, value->to_string(value));
  });

  // right brace
  buffer_append(buf, "]");

  return buf->data;
}
