#include <iostream>

class md5
{
private:

    enum {blocksize = 64}; //musi tyle byc enum-typ wyliczeniowy
    bool finalized;
    unsigned char buffer[blocksize]; // bajty ktore nie zmiescily sie w 64 ostatnich bitach
    unsigned int count[2];   // 64 bitowy licznik liczby bitow (low, hiigh)
    unsigned int state[4];   // ABCD
    unsigned char digest[16]; // wynik

    void init(); //funkcja inicjalizacycja wyk w konstruktorach

public:

    md5();
};
