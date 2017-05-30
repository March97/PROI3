#include <iostream>
#include "md5.h"

// stale dla automatu md5
#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21

// F, G, H, I funkcje md5
inline md5::uint4 md5::F(uint4 x, uint4 y, uint4 z) {
  return x&y | ~x&z;
}

inline md5::uint4 md5::G(uint4 x, uint4 y, uint4 z) {
  return x&z | y&~z;
}

inline md5::uint4 md5::H(uint4 x, uint4 y, uint4 z) {
  return x^y^z;
}

inline md5::uint4 md5::I(uint4 x, uint4 y, uint4 z) {
  return y ^ (x | ~z);
}

// rotate_left rotates x left n bits.
inline md5::uint4 md5::rotate_left(uint4 x, int n) {
  return (x << n) | (x >> (32-n));
}

// FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4.
// Rotation is separate from addition to prevent recomputation.
inline void md5::FF(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac) {
  a = rotate_left(a+ F(b,c,d) + x + ac, s) + b;
}

inline void md5::GG(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac) {
  a = rotate_left(a + G(b,c,d) + x + ac, s) + b;
}

inline void md5::HH(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac) {
  a = rotate_left(a + H(b,c,d) + x + ac, s) + b;
}

inline void md5::II(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac) {
  a = rotate_left(a + I(b,c,d) + x + ac, s) + b;
}

md5::md5()
{
    init();
}

void md5::init()
{
    finalized=false;

    count[0] = 0;
    count[1] = 0;

    // ustawienie wartosci poczatkowych.
    state[0] = 0x67452301; //A
    state[1] = 0xefcdab89; //B
    state[2] = 0x98badcfe; //C
    state[3] = 0x10325476; //D
}
