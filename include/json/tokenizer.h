
/**
 * `tokenizer.h` - libjson
 *
 * copyright (c) 2014 - joseph werle <joseph.werle@gmail.com>
 */

#ifndef JSON_TOKENIZER_H
#define JSON_TOKENIZER_H

#include <buffer/buffer.h>
#include "common.h"
#include "value.h"

#define JSON_TOKENIZER_MAX_DEPTH 32

/**
 * Parsing states
 */

typedef enum {

  JSON_TOKENIZER_STATE_START,
  JSON_TOKENIZER_STATE_END,
  JSON_TOKENIZER_STATE_WHITESPACE,
  JSON_TOKENIZER_STATE_SUCCESS,
  JSON_TOKENIZER_STATE_CONTINUE,
  JSON_TOKENIZER_STATE_ERROR,

  JSON_TOKENIZER_STATE_NULL,
  JSON_TOKENIZER_STATE_BOOLEAN,
  JSON_TOKENIZER_STATE_NUMBER,

  JSON_TOKENIZER_STATE_STRING,
  JSON_TOKENIZER_STATE_STRING_ESCAPE,
  JSON_TOKENIZER_STATE_STRING_UNICODE,

  JSON_TOKENIZER_STATE_ARRAY,
  JSON_TOKENIZER_STATE_ARRAY_PUSH,
  JSON_TOKENIZER_STATE_ARRAY_SEP,

  JSON_TOKENIZER_STATE_OBJECT,
  JSON_TOKENIZER_STATE_OBJECT_START,
  JSON_TOKENIZER_STATE_OBJECT_END,
  JSON_TOKENIZER_STATE_OBJECT_SEP,
  JSON_TOKENIZER_STATE_OBJECT_VALUE,
  JSON_TOKENIZER_STATE_OBJECT_VALUE_SET,

} json_tokenizer_state_t;

/**
 * Token char types
 */

#define JSON_TOKEN_OBJECT_LEFT_BRACE '{'
#define JSON_TOKEN_ARRAY_LEFT_BRACE '['
#define JSON_TOKEN_NULL_CHAR 'n'
#define JSON_TOKEN_TRUE_CHAR 't'
#define JSON_TOKEN_FALSE_CHAR 'f'
#define JSON_TOKEN_DOUBLE_QUOTE '"'
#define JSON_TOKEN_SINGLE_QUOTE '\''

/**
 * Represents a parsed token
 */

typedef struct json_token_s {

  /**
   * Token name
   */

  char *name;

  /**
   * Current state for token
   */

  json_tokenizer_state_t state;

  /**
   * Previous state for token
   */

  json_tokenizer_state_t prev_state;

  /**
   * Token value
   */

  json_value_t *value;

} json_token_t;

/**
 * Represents a json tokenizer
 */

typedef struct json_tokenizer_s {

  /**
   * Original JSON source string
   */

  const char *src;

  /**
   * Source buffer
   */

  buffer_t *buf;

  /**
   * Length of the source string
   */

  int src_length;

  /**
   * Represents the current parse char offset
   */

  int offset;

  /**
   * Token depth
   */

  int depth;

  /**
   * Set when an error occurs which can be
   * used with `json_perror(code, message)`
   */

  int errno;

  /**
   * Represents the current object being parsed
   */

  json_value_t *current;

  /**
   * Represents the current state of the
   * tokenizer
   */

  json_tokenizer_state_t state;

  /**
   * Next state for tokenizer
   */

  json_tokenizer_state_t next_state;

  /**
   * Token stack
   */

  json_token_t *tokens[JSON_TOKENIZER_MAX_DEPTH];

} json_tokenizer_t;

/**
 * Allocates a new `json_tokenizer_t`
 */

JSON_EXTERN json_tokenizer_t *
json_tokenizer_new ();

/**
 * Allocates a new `json_token_t`
 */

JSON_EXTERN json_token_t *
json_token_new ();

/**
 * Parses a string with a given `json_tokenizer_t`
 */

JSON_EXTERN json_value_t *
json_tokenize (json_tokenizer_t *, const char *);

#endif
