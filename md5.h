#include <iostream>

class md5
{
public:
    typedef unsigned int size_type;

    md5();

    std::string hex() const; // zwraca liczbe w kodzie hexadecymalnym jako string

private:

    typedef unsigned char uint1; //  8bit
    typedef unsigned int uint4;  // 32bit

    enum {blocksize = 64}; //musi tyle byc enum-typ wyliczeniowy
    bool finalized;
    uint1 buffer[blocksize]; // bajty ktore nie zmiescily sie w 64 ostatnich bitach
    uint4 count[2];   // 64 bitowy licznik liczby bitow (low, high)
    uint4 state[4];   // ABCD
    uint1 digest[16]; // wynik

    void init(); //funkcja inicjalizacycja wyk w konstruktorach
    static void decode(uint4 output[], const uint1 input[], size_type len); //dekodowanie input unsigned char do output uint4, len dlugosc tablicy
    static void encode(uint1 output[], const uint4 input[], size_type len); //odwrotnosc decode
    void transform(const uint1 block[blocksize]); //automat okreslajacy wartosci w poszczegolnych 64 stanach
    void update(const unsigned char *buf, size_type length); //kieruje operacjami wykonywanymi przez algorytm md5
    void update(const char *buf, size_type length); //update dla char bez unsigned
    md5& finalize(); // konczy operacje md5, zapisuje wynik operacji i zeruje dane powstale w  wyniku dzialania algorytmu

    //operacje logiczne
    static inline uint4 F(uint4 x, uint4 y, uint4 z);
    static inline uint4 G(uint4 x, uint4 y, uint4 z);
    static inline uint4 H(uint4 x, uint4 y, uint4 z);
    static inline uint4 I(uint4 x, uint4 y, uint4 z);
    static inline uint4 rotate_left(uint4 x, int n);
    static inline void FF(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac);
    static inline void GG(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac);
    static inline void HH(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac);
    static inline void II(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac);

};
