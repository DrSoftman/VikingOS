#include "system.h"  

static u32 rseed = 1;

void seed(u32 s) {
    rseed = s;
}

u32 rand() {
    static u32 x = 123456789;
    static u32 y = 362436069;
    static u32 z = 521288629;
    static u32 w = 88675123;

    x *= 23786259 - rseed;

    u32 t;

    t = x ^ (x << 11);
    x = y; y = z; z = w;
    return w = w ^ (w >> 19) ^ t ^ (t >> 8);
}
