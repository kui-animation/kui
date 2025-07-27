#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

// define integers

typedef int_fast8_t t_int8;
typedef int_fast16_t t_int16;
typedef int_fast32_t t_int32;
typedef int_fast64_t t_int64;

// define floating point numbers

typedef float t_float_32;
typedef double t_float_64;

// define unsinged integers

typedef uint_fast8_t t_uint8;
typedef uint_fast16_t t_uint16;
typedef uint_fast32_t t_uint32;
typedef uint_fast64_t t_uint64;

// define vectors

typedef struct t_vec2d {
    t_int32 a;
    t_int32 b;
} vec2d;

typedef struct t_vec3d {
    t_int32 a;
    t_int32 b;
    t_int32 c;
} vec3d;

#ifndef KUI_SYS
    #ifdef _WIN32
        #define KUI_SYS 1
    #elif __linux__
        #define KUI_SYS 2
    #elif __APPLE__
        #define KUI_SYS 3
    #else
        #define KUI_SYS 0
    #endif
#endif

#define KUI_WINDOWS_SYS 1
#define KUI_LINUX_SYS 2
#define KUI_APPLE_SYS 3
#define KUI_NO_SYS 0

#endif
