
#include <stdio.h>
/**
 * `tokenizer.c` - libjson
 *
 * copyright (c) 2014 - joseph werle <joseph.werle@gmail.com>
 */

#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <buffer/buffer.h>
#include <json/error.h>
#include <json/null.h>
#include <json/object.h>
#include <json/array.h>
#include <json/string.h>
#include <json/boolean.h>
#include <json/tokenizer.h>

static inline int
next (json_tokenizer_t *self) {
  if (self->offset >= self->src_length) {
    return 0;
  }

  self->offset += 1;
  self->buf = buffer_slice(self->buf, self->offset, buffer_length(self->buf));
  return 1;
}

static inline char
head (json_tokenizer_t *self) {
  json_token_t *token = self->tokens[self->depth];

  if (self->src_length > 0 && self->offset >= self->src_length) {
    if (0 == self->depth &&
        self->state == JSON_TOKENIZER_STATE_WHITESPACE &&
        self->next_state == JSON_TOKENIZER_STATE_END) {
      self->state = JSON_TOKENIZER_STATE_SUCCESS;
    } else {
      self->state = JSON_TOKENIZER_STATE_CONTINUE;
    }
    return 0;
  }

  return self->buf->data[self->offset];
}

json_tokenizer_t *
json_tokenizer_new () {
  json_tokenizer_t *self = NULL;
  self = (json_tokenizer_t *) malloc(sizeof(json_tokenizer_t));

  if (NULL == self) {
    return NULL;
  }

  self->state = JSON_TOKENIZER_STATE_WHITESPACE;
  self->depth = 0;
  self->offset = 0;
  self->src = "";
  self->src_length = 0;
  self->buf = buffer_new();

  return self;
}

json_token_t *
json_token_new () {
  json_token_t *self = (json_token_t *) malloc(sizeof(json_token_t));
  self->state = JSON_TOKENIZER_STATE_WHITESPACE;
  if (NULL == self) {
    return NULL;
  }
  return self;
}

json_value_t *
json_tokenize (json_tokenizer_t *self, const char *src) {
  char ch = 0;
  char quote = 0;
  char uchar = 0;
  int pos = 0;
  const char *tmpsrc = src;
  json_tokenizer_state_t *state = &self->state;
  json_tokenizer_state_t *next_state = &self->next_state;
  json_value_t *current = self->current;
  json_token_t *token = json_token_new();

  self->src = src;
  self->buf = buffer_new_with_copy((char *) src);
  self->src_length = strlen(src);

  *state = JSON_TOKENIZER_STATE_START;

  self->tokens[self->depth] = token;

  while ((ch = head(self))) {
    parse: switch (*state) {
      case JSON_TOKENIZER_STATE_ERROR:
        goto error;
        break;

      case JSON_TOKENIZER_STATE_CONTINUE:
        goto parse;
        break;

      case JSON_TOKENIZER_STATE_SUCCESS:
        goto complete;
        break;

      /**
       * Handles whitespace and goes to
       * complete when buffer is fully read
       */

      case JSON_TOKENIZER_STATE_WHITESPACE:
        while (isspace(ch)) {
          if (!next(self) || !(ch = head(self))) {
            goto complete;
          }
        }

        /**
         * @TODO - handle comments
         */

        state = next_state;
        break;

      /**
       * Peeks at char to determine value
       * type
       */

      case JSON_TOKENIZER_STATE_START:

        printf("%c, ",ch);
        switch (ch) {

          /**
           * Sets state to null, position to 0,
           * and goes back to parse the switch
           */

          case JSON_TOKEN_NULL_CHAR:
            *state = JSON_TOKENIZER_STATE_NULL;
            pos = 0;
            buffer_clear(self->buf);
            goto parse;
            break;

          /**
           * Sets state to parse a string
           * in the case of double or single
           * quotes
           */

          case JSON_TOKEN_SINGLE_QUOTE:
          case JSON_TOKEN_DOUBLE_QUOTE:
            *state = JSON_TOKENIZER_STATE_STRING;
            quote = ch;
            buffer_clear(self->buf);
            break;

          /**
           * Sets state to boolean and position
           * to 0
           */

          case JSON_TOKEN_TRUE_CHAR:
          case JSON_TOKEN_FALSE_CHAR:
            *state = JSON_TOKENIZER_STATE_BOOLEAN;
            pos = 0;
            buffer_clear(self->buf);
            goto parse;
            break;

          /**
           * Sets state to number
           */

          case '0': case '1': case '2': case '3': case '4':
          case '5': case '6': case '7': case '8': case '9':
          case '-':
            *state = JSON_TOKENIZER_STATE_NUMBER;
            buffer_clear(self->buf);
            goto parse;
            break;

          /**
           * Prepares an empty object, sets
           * state to filter whitespace and
           * next state to start parsing the
           * object
           */

          case JSON_TOKEN_OBJECT_LEFT_BRACE:
            *state = JSON_TOKENIZER_STATE_WHITESPACE;
            *next_state = JSON_TOKENIZER_STATE_OBJECT_START;
            current = (json_value_t *) json_object_new();
            break;

          /**
           * Prepares an empty array, sets
           * state to filter whitespace and
           * next state to start parsing the
           * array
           */

          case JSON_TOKEN_ARRAY_LEFT_BRACE:
            *state = JSON_TOKENIZER_STATE_WHITESPACE;
            *next_state = JSON_TOKENIZER_STATE_ARRAY;
            current = (json_value_t *) json_array_new();
            break;

          /**
           * Set the error flag and errno for an unexpected
           * token
           */

          default:
            self->errno = JSON_EUNEXPECTED_TOKEN;

#ifdef JSON_DEBUG
            json_perror(JSON_EUNEXPECTED_TOKEN, ch);
#endif
            goto error;
        }
        break;

      /**
       * Completes parse if depth is 0
       */
      case JSON_TOKENIZER_STATE_END:
        if (0 == self->depth) goto complete;
        self->depth--;
        break;

      /**
       *
       */

      case JSON_TOKENIZER_STATE_NULL:
        buffer_append(self->buf, &ch);

        if (strncmp(JSON_NULL, self->buf->data, strlen(JSON_NULL))) {
          if (pos == strlen(JSON_NULL)) {
            *state = JSON_TOKENIZER_STATE_WHITESPACE;
            *next_state = JSON_TOKENIZER_STATE_END;
            current = (json_value_t *) json_null_new();
            goto parse;
          }
        } else {
          self->errno = JSON_ENULL_PARSE_ERROR;

#ifdef JSON_DEBUG
          json_perror(JSON_ENULL_PARSE_ERROR, ch);
#endif
          goto error;
        }

        pos++;
        break;

      /**
       * @TODO - Handle comments
       */


      /**
       *
       */

      case JSON_TOKENIZER_STATE_STRING:

        tmpsrc = self->buf->data;
        while (1) {
          if (quote == ch) {
            printf("c %c\n", ch);
            *state = JSON_TOKENIZER_STATE_WHITESPACE;
            *next_state = JSON_TOKENIZER_STATE_END;
            current = (json_value_t *) json_string_new(self->buf->data);
            break;
          } else if ('\\' == ch) {
            *state = JSON_TOKENIZER_STATE_STRING_ESCAPE;
            *next_state = JSON_TOKENIZER_STATE_STRING;
            break;
          } else if (!next(self) || !(ch = head(self))) {
            // @TODO
            goto complete;
          }
        }

        break;

      /**
        *
        */

       case JSON_TOKENIZER_STATE_STRING_ESCAPE:
        switch (ch) {
          // handle escaped characters
          case '"': case '\\': case '/':
            buffer_append(self->buf, &ch);
            state = next_state;
            break;

          case 'b':
            buffer_append(self->buf, "\b");
            state = next_state;
            break;
          case 'r':
            buffer_append(self->buf, "\r");
            state = next_state;
            break;
          case 'n':
            buffer_append(self->buf, "\n");
            state = next_state;
            break;
          case 't':
            buffer_append(self->buf, "\t");
            state = next_state;
            break;
          case 'u':
            pos = 0;
            uchar = 0;
            *state = JSON_TOKENIZER_STATE_STRING_UNICODE;
            break;

          default:
          self->errno = JSON_ESTRING_PARSE_ERROR;

#ifdef JSON_DEBUG
          json_perror(JSON_ESTRING_PARSE_ERROR, ch);
#endif

        }
        break;

       case JSON_TOKENIZER_STATE_STRING_UNICODE:

        /**
         * @TODO - handle unicode
         */

        break;

       case JSON_TOKENIZER_STATE_BOOLEAN:
        buffer_append(self->buf, &ch);
        if (0 == strcmp(JSON_TRUE, self->buf->data)) {
          if (pos == strlen(JSON_TRUE)) {
            *state = JSON_TOKENIZER_STATE_WHITESPACE;
            *next_state = JSON_TOKENIZER_STATE_END;
            current = (json_value_t *) json_boolean_new(1);
            goto parse;
          } else if (0 == strcmp(JSON_TRUE, self->buf->data)) {
            if (0 == strcmp(JSON_FALSE, self->buf->data)) {
              *state = JSON_TOKENIZER_STATE_WHITESPACE;
              *next_state = JSON_TOKENIZER_STATE_END;
              current = (json_value_t *) json_boolean_new(0);
              goto parse;
            }
          } else {
            self->errno = JSON_EBOOLEAN_PARSE_ERROR;

#ifdef JSON_DEBUG
            json_perror(JSON_EBOOLEAN_PARSE_ERROR, ch);
#endif
          }
        }
        break;

       case JSON_TOKENIZER_STATE_NUMBER:
        break;

       case JSON_TOKENIZER_STATE_ARRAY:
        break;

       case JSON_TOKENIZER_STATE_ARRAY_PUSH:
        break;

       case JSON_TOKENIZER_STATE_ARRAY_SEP:
        break;

       case JSON_TOKENIZER_STATE_OBJECT_START:
        break;

       case JSON_TOKENIZER_STATE_OBJECT:
        break;

       case JSON_TOKENIZER_STATE_OBJECT_END:
        break;

       case JSON_TOKENIZER_STATE_OBJECT_VALUE_SET:
        break;

       case JSON_TOKENIZER_STATE_OBJECT_VALUE:
        break;

       case JSON_TOKENIZER_STATE_OBJECT_SEP:
        break;
    }

    if (!(ch = next(self))) {
      break;
    }
  }

complete:
  return current;

error:
  return NULL;
}
