#include <iostream>
#include <string.h>
#include "md5.h"

int main(int argc, char *argv[])
{
    char Test[13]="Hello World!";

    std::string Temp =  md5str(Test,12);
    std::cout << Temp.c_str() << std::endl;

    return 0;
}

