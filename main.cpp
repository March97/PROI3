/**
*\file main.cpp
*\author Dominik Marchewka
*\date 08.06.2017r.
*\brief Weryfikator MD5
*
*Aplikacja dla danego pliku wejsciowego oblicza jego skrot wedlug algorytmu MD5 i zapisuje go do oddzielnego pliku,
*rowniez podanego jako parametr wywolania aplikacji. Drugim zastosowaniem aplikacji jest obliczenie skrotu pliku
*i porownanie go z wczesniej zapisanym juz skrotem. Implementacja algorytmu bazuje na RFC 1321: The MD5 Message-Digest Algorithm,
*dostepnego na stronie: https://www.ietf.org/rfc/rfc1321.txt.
*
*MD5 jest to algorytm kryptograficzny, badacy popularna kryptograficzna funkcja skrotu, która z ciągu danych o dowolnej długości
*generuje 128-bitowy skrót.
*
*Algorytm MD5 jest następujący:
*1. Doklejamy do wiadomości wejściowej bit o wartości 1
*2. Doklejamy tyle zer ile trzeba żeby ciąg składał się z 512-bitowych bloków, i ostatniego niepełnego - 448-bitowego
*3. Doklejamy 64-bitowy (zaczynając od najmniej znaczącego bitu) licznik oznaczający rozmiar wiadomości. W ten sposób otrzymujemy
*wiadomość złożoną z 512-bitowych fragmentów.
*4. Ustawiamy stan początkowy na 67452301efcdab8998badcfe10325476
*5. Uruchamiamy na każdym bloku (jest przynajmniej jeden blok nawet dla pustego wejścia) funkcję zmieniającą stan
*6. Po przetworzeniu ostatniego bloku zwracamy stan jako obliczony skrót wiadomości
*
*Funkcja zmiany stanu ma 4 cykle (64 kroki). Stan jest traktowany jako 4 liczby 32-bitowe. W każdym kroku do jednej z tych liczb
*dodawany jest jeden z 16 32-bitowych fragmentów bloku wejściowego, pewna stała zależna od numeru kroku oraz pewna prosta funkcja boolowska 3 pozostałych liczb. Następnie liczba ta jest obracana (przesuwana cyklicznie z najstarszymi bitami wsuwanymi w najmłodsze pozycje) o liczbę bitów zależną od kroku, oraz jest dodawana do niej jedna z pozostałych liczb.
*Funkcje te to:
*W krokach 1 do 16 (cykl 1) funkcja F(x,y,z) = (x and y) or (neg x and z)
*W krokach 17 do 32 (cykl 2) funkcja G(x,y,z) = (x and z) or (y and neg z)
*W krokach 33 do 48 (cykl 3) funkcja H(x,y,z) = (x xor y xor z)
*W krokach 49 do 64 (cykl 4) funkcja I(x,y,z) = (y xor (x or neg z))
*
*Aby otrzymać wartość stałej w i-tym kroku, należy wziąć 32 najstarsze bity z części ułamkowej wyrażenia | sin ⁡   i |.
*
*Komendy:
*hash - obliczenie skrotu pliku
*compare - porownanie skrotu pliku z istniejacym plikiem
*
*Przyklad uzycia:
*./md5 hash <plik_wejsciowy> <plik_do_zapisu_skrotu>
*./md5 compare <plik_wejsciowy> <plik_do_porownania>
*
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string.h>
#include "md5.h"
#include "files.h"

int main(int argc, char *argv[])
{
    std::string program = argv[0];

    if(argc < 4)
    {
        std::cout << "Not enough arguments" << std::endl;
        exit(0);
    }else
    if(argc > 4)
    {
        std::cout << "Too many arguments" << std::endl;
        exit(0);
    }

    std::string command = argv[1]; //hash lub compare

    std::string Test; // = "Hello World!";
    std::string Test2;

    //std::string Temp =  md5str(Test);
    //std::cout << Temp.c_str() << std::endl;

    std::fstream file1;
    std::fstream file2;
    Files filer;

    if(command == "hash") //argv[2]- plik wejsciowy argv[3]-plik wyjsciowy
    {
        file1.open(argv[2], std::ios::binary | std::ios::in);
        if(file1.good() == false)
        {
            std::cout << "Blad odczytu pliku" << std::endl;
            exit(0);
        }

        //file1 >> Test;
        Test = filer.read(file1);
        std::string Temp =  md5str(Test);

        file2.open(argv[3], std::ios::out);

        file2 << Temp.c_str() << std::endl;

        file1.close();
        file2.close();
    }else
    if(command == "compare")
    {
        file1.open(argv[2], std::ios::binary | std::ios::in);
        if(file1.good() == false)
        {
            std::cout << "Error read the first file." << std::endl;
            exit(0);
        }

        file2.open(argv[3], std::ios::binary | std::ios::in);
        if(file2.good() == false)
        {
            std::cout << "Error read the second file." << std::endl;
            exit(0);
        }

        //file1 >> Test;
        Test = filer.read(file1);
        //file2 >> Test2;
        Test2 = filer.read(file2);

        std::string Temp =  md5str(Test);

        if(Temp.c_str() == Test2)
        {
            std::cout << "File is compatible." << std::endl;
        }else
        {
            std::cout << "File is not compatible." << std::endl;
        }

        file1.close();
        file2.close();

    }else std::cout << "Command not found." << std::endl;

    return 0;
}
