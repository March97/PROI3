#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string.h>
#include "md5.h"

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

    //std::string Temp =  md5str(Test);
    //std::cout << Temp.c_str() << std::endl;

    std::fstream file1;
    std::fstream file2;

    if(command == "hash")
    {
        file1.open(argv[2], std::ios::binary | std::ios::in);
        if(file1.good() == false)
        {
            std::cout << "Blad odczytu pliku" << std::endl;
            exit(0);
        }

        file1 >> Test;
        std::string Temp =  md5str(Test);

        file2.open(argv[3], std::ios::out);

        file2 << Temp.c_str() << std::endl;

        file1.close();
        file2.close();
    }else
    if(command == "compare")
    {

    }

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
