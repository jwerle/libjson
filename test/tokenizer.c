
/**
 * `test/tokenizer.c` - libjson
 *
 * copyright (c) 2014 - joseph werle <joseph.werle@gmail.com>
 */

#include <json/test.h>
#include <json/object.h>
#include <json/tokenizer.h>
#include <ok.h>

TEST(tokenizer) {
  json_tokenizer_t *tokenizer = json_tokenizer_new();
  t(tokenizer);

  json_object_t *obj = (json_object_t *) json_tokenize(tokenizer, "{"
      "\"foo\": \"bar\","
      "\"123\": 456"
  "}");
  t(obj);

  ok("tokenizer");
  return 0;
}
