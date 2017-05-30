#include <iostream>
#include "md5.h"

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
