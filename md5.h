#include <iostream>
/**
*\brief Klasa algorytmu MD5
*
*Klasa implementujaca dzialanie algorytmu MD5 na podstawie RFC 1321.
*/
class md5
{
public:
    typedef unsigned int size_type;

    /**
    *\brief Konstruktor domyslny
    *
    *Konstruktor korzystajacy tylko z metody init()
    */
    md5();

    /**
    *\brief Konstruktor
    *\param text - string od ktorego zostanie utworzony skrot MD5.
    *
    *Konstruktor korzysta z metod init(), update(const char , size_type ), finalize().
    */
    md5(const std::string& text);

    /**
    *\brief Konstruktor
    *\param wskaznik na char (tablica znakow), dlugosc tablicy
    *
    *Konstruktor korzysta z metod init(), update(const char , size_type ), finalize().
    */
    md5(char * Input, long length);

    /**
    *\brief Przetwarza kod heksadecymalny na napis.
    *
    *Gdy finalize==false metoda zwraca pusty string.
    *W przeciwnym wypadku metoda przetwarza reprezantacje heksadecymalna tablicy digest na string.
    */
    std::string hex() const; // zwraca liczbe w kodzie hexadecymalnym jako string


private:

    typedef unsigned char uint1; /*! unsigned char domyslnie 8 bitowy */
    typedef unsigned int uint4;  /*! unsigned int domyslnie 32 bitowy */

    enum {blocksize = 64}; /*! wielkosc ostatniego bloku *///musi tyle byc enum-typ wyliczeniowy
    bool finalized; /*! okresla zakonczenie algorytmu */
    uint1 buffer[blocksize]; /*! bajty ktore nie zmiescily sie w 64 ostatnich bitach */
    uint4 count[2];   /*! 64 bitowy licznik liczby bitow (low, high) */
    uint4 state[4];   /*! bloki ABCD */
    uint1 digest[16]; /*! wynik dzialania algorytmu */

    /**
    *\brief Inicjalizuje zmienne poczatkowe
    *
    *Ustawia wartosci blokow ABCD wg ustalonych wartosci, tablice count na 0 i finalized na false.
    *Wykorzystywany w konstruktorach.
    */
    void init(); //funkcja inicjalizacycja wyk w konstruktorach

    /**
    *\brief Przetwarza wejscie z unsigned char do unsigned int
    *\param wyjscie unsigned int 32bit, wejscie unsigned char 8bit, dlugosc tablicy
    *
    *Z 4 8-bitowych blokow tablicy input[] tworzy 32-bitowy blok w tablicy output[]
    */
    static void decode(uint4 output[], const uint1 input[], size_type len); //dekodowanie input unsigned char do output uint4, len dlugosc tablicy

    /**
    *\brief Przetwarza wejscie z unsigned int do unsigned char
    *\param wyjscie unsigned char 8bit, wejscie unsigned int 32bit, dlugosc tablicy
    *
    *Z 32-bitowego bloku input[] tworzy 8-bitowe bloki unsigned char
    */
    static void encode(uint1 output[], const uint4 input[], size_type len); //odwrotnosc decode

    /**
    *\brief Tablica wartosci bloku w poszczegolnych stanach automatu
    *\param tablica unsigned char
    *
    *Ustawia wartosci poszczegolnych blokow ABCD, oraz dekoduje sygnal wejsciowy za pomoca funkcji decode. Nastepnie wykonuje szereg operacji
    *okreslonych w algorytmie MD5. Dodaje przetworzone wartosci do poszczegolnych blokow i zeruje tablice x[].
    */
    void transform(const uint1 block[blocksize]); //automat okreslajacy wartosci w poszczegolnych 64 stanach

    /**
    *\brief Wykonuje operacje na blokach bitow i wykonuje transform tyle razy ile to mozliwe
    *\param wskaznik na buffer(wejscie), dlugosc buffera
    *
    *Oblicza liczbe bitow modulo 64 i ustawia wartosc licznika (count[]). Oblicza liczbe bitow potrzebnych w bufferze i wykonuje operacje transform
    *tyle razy ile wynosi dlugosc buffera. Kopiuje wynik operacji na wyjscie.
    */
    void update(const unsigned char *buf, size_type length); //kieruje operacjami wykonywanymi przez algorytm md5

    /**
    *\brief Funkcja update dla tablicy char
    *\param wskaznik na buffer(wejscie), dlugosc buffera
    *
    *Wykonuje ta sama operacja co funkcja void update(const unsigned char, size_type) dla typu char.
    */
    void update(const char *buf, size_type length); //update dla char bez unsigned

    /**
    *\brief Zakonczenie pracy algorytmu
    *
    *Operacje na ostatnikm bloku, dodaje ostatnie 64bity, zapisuje stan algorytmu i zeruje zbedne informacje.
    */
    md5& finalize(); // konczy operacje md5, zapisuje wynik operacji i zeruje dane powstale w  wyniku dzialania algorytmu

    //operacje logiczne
    /**
    *\brief Operacje logiczne okreslone w algorytmie MD5
    */
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

    //funkcje do wywolywania algorytmu
    /**
    *\brief Inicjalizacja algorytmu
    *\param napis string
    *
    *Funkcja wywoluje konstruktor, inicjalizujacy prace algorytmu i zwraca przetworzony juz sygnal za pomoca funkcji hex.
    */
    std::string md5str(const std::string str);

    /**
    *\brief Inicjalizacja algorytmu
    *\param referencja na char, dlugosc tablicy
    *
    *Inicjalizacja algorytmu dla tablicy znakow. Funkcja wywoluje konstruktor, inicjalizujacy prace algorytmu i zwraca przetworzony juz sygnal za pomoca funkcji hex.
    */
    std::string md5str(char * Input, long length);
