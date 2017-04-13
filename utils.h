#include <stdint.h>

#ifndef _UTILS_
#define _UTILS_

int is_in_the_box(int x, int y, int bx, int by, int bw, int bh);
float radians_to_degrees(float radians);
long to_int(double val);
long to_long(double val);
uint32_t mix(uint32_t a, uint32_t b, uint32_t c);
uint64_t mix64(uint32_t b, uint32_t c);

#endif

