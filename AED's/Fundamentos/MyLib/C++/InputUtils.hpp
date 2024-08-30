#ifndef InputUtils_hpp
#define InputUtils_hpp

#include <iostream>
#include <limits>
#include <string>

/*
This library includes functions to read integers, floating-point numbers (float and double),
and strings from standard input. Each function ensures that the input is valid and handles
any errors by clearing the input buffer and prompting the user until a valid input is received.

These functions handle input errors by:
 - Clearing the error state of `std::cin`.
 - Ignoring the remaining input in the buffer.
 - Continuously prompting the user until valid input is provided.
*/

int readInt(const std::string& errorMessage)
{
    int x = 0;
    bool valid = false;
    do 
    {
        std::cin >> x;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (std::cin.fail()) 
        {
            std::cerr << errorMessage << std::endl;
            std::cin.clear();
        }
        else
        {
            valid = true;
        }
    } while (!valid);

    return x;
}

float readFloat(const std::string& errorMessage)
{
    float x = 0.0;
    bool valid = false;
    do 
    {
        std::cin >> x;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (std::cin.fail()) 
        {
            std::cerr << errorMessage << std::endl;
            std::cin.clear();
        }
        else
        {
            valid = true;
        }
    } while (!valid);

    return x;
}

double readDouble(const std::string& errorMessage)
{
    double x = 0.0;
    bool valid = false;
    do 
    {
        std::cin >> x;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (std::cin.fail()) 
        {
            std::cerr << errorMessage << std::endl;
            std::cin.clear();
        }
        else
        {
            valid = true;
        }
    } while (!valid);

    return x;
}

std::string readString()
{
    std::string x;
    std::getline(std::cin, x);
    return x;
}


#endif