#include <iostream>
#include <fstream>

/**
*\brief Klasa zawierajaca operacje na plikach
*/
class Files
{
public:

    /**
    *\brief Odczytuje plik
    *\param referencja na plik
    *
    *Funkcja sluzaca do czytania pliku, wykorzystujaca operator strumieniowy. Czyta plik bez bialych znakow np. dla "Hello World!",
    *zostanie odczytane jako "HelloWorld!".
    */
    std::string read(std::fstream &file);
};
