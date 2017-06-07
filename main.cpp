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
    files filer;

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

    }else std::cout << "Command not found." << std::endl;

    /*file1.open(name_file + ".txt", std::ios::binary | std::ios::in);
    if(file1.good() == false)
    {
        std::cout << "Blad odczytu pliku" << std::endl;
        exit(0);
    }

    file1 >> Test;
    std::string Temp =  md5str(Test);

    std::cout << "Podaj nazwe pliku wyjsciowego:"; std::cin >> name_file;

    file2.open(name_file + ".txt", std::ios::out);

    file2 << Temp.c_str() << std::endl;

    file2.close();*/

    return 0;
}
