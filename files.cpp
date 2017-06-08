#include <iostream>
#include <fstream>
#include <string.h>
#include "files.h"

std::string Files::read(std::fstream &file)
{
    std::string StringOut = "", Temp = "";

    while(!file.eof())
    {
        StringOut += Temp;
        file >> Temp;

    }
    //std::cout << StringOut << std::endl;
    return StringOut;
}
