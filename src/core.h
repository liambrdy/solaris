#ifndef _CORE_H
#define _CORE_H

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef float f32;
typedef double f64;

typedef bool b32;

#define UNREACHABLE assert(false && "UNREACHABLE")

#if defined(__clang__) || defined(__gcc__)
#define INLINE __attribute__((always_inline)) inline
#define NOINLINE __attribute__((noinline))
#elif defined(_MSC_VER)
#define INLINE __forceinline
#define NOINLINE __declspec(noinline)
#else
#define INLINE static inline
#define NOINLINE
#endif

#endif