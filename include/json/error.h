
/**
 * `error.h` - libjson
 *
 * copyright (c) 2014 - joseph werle <joseph.werle@gmail.com>
 */

#ifndef JSON_ERROR_H
#define JSON_ERROR_H

/**
 * Error numbers
 */

#define JSON_EUNEXPECTED_TOKEN 0x0
#define JSON_ENULL_PARSE_ERROR 0x1
#define JSON_ESTRING_PARSE_ERROR 0x2
#define JSON_EBOOLEAN_PARSE_ERROR 0x3

/**
 * Error table
 */

static const char *JSON_ERRORS[][2] = {

#define X(code, type) {code, type " parse error. Unexpected token '%c'"}

  X(JSON_EUNEXPECTED_TOKEN, "Unknown"),
  X(JSON_ENULL_PARSE_ERROR, "`null'"),
  X(JSON_ESTRING_PARSE_ERROR, "String"),
  X(JSON_EBOOLEAN_PARSE_ERROR, "Boolean")

};

#undef X

/**
 * Prints a json error from a given
 * code with an optional message
 */

#define json_perror(code, msg) {              \
  fprintf(stderr, "error: ");                 \
  fprintf(stderr, JSON_ERRORS[code][1], msg); \
  fprintf(stderr, "\n");                      \
}

#endif
