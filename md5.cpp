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
  return (x&y) | ((~x)&z);
}

inline md5::uint4 md5::G(uint4 x, uint4 y, uint4 z) {
  return (x&z) | (y&(~z));
}

inline md5::uint4 md5::H(uint4 x, uint4 y, uint4 z) {
  return x^y^z;
}

inline md5::uint4 md5::I(uint4 x, uint4 y, uint4 z) {
  return y ^ (x | ~z);
}

// rotate_left przesuwa bity x o n miejsc w lewo
inline md5::uint4 md5::rotate_left(uint4 x, int n) {
  return (x << n) | (x >> (32-n));
}

// FF, GG, HH, II przejscia dla etapow 1, 2, 3, 4.
// Przesuwanie bitow jest oddzielone aby uniknac ponownych obliczen.
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
    finalized = false;

    count[0] = 0;
    count[1] = 0;

    // ustawienie wartosci poczatkowych.
    state[0] = 0x67452301; //A
    state[1] = 0xefcdab89; //B
    state[2] = 0x98badcfe; //C
    state[3] = 0x10325476; //D
}

void md5::decode(uint4 output[], const uint1 input[], size_type len)
{
  for (unsigned int i = 0, j = 0; j < len; i++, j += 4)
    output[i] = ((uint4)input[j]) | (((uint4)input[j+1]) << 8) |
      (((uint4)input[j+2]) << 16) | (((uint4)input[j+3]) << 24);
}

void md5::encode(uint1 output[], const uint4 input[], size_type len)
{
  for (size_type i = 0, j = 0; j < len; i++, j += 4)
  {
    output[j] = input[i] & 0xff;
    output[j+1] = (input[i] >> 8) & 0xff;
    output[j+2] = (input[i] >> 16) & 0xff;
    output[j+3] = (input[i] >> 24) & 0xff;
  }
}
