
/**
 * `common.h` - libjson
 *
 * copyright (c) 2014 - joseph werle <joseph.werle@gmail.com>
 */

#ifndef JSON_COMMON_H
#define JSON_COMMON_H

#if __GNUC__ >= 4
# define JSON_EXTERN __attribute__((visibility("default")))
#else
# define JSON_EXTERN
#endif

#endif
