/*
 * Copyright © 2021 Ali Khaleqi Yekta, All Rights Reserved.
 *
 * Author: Ali Khaleqi Yekta [YektaDev]
 * Website: https://Yekta.Dev
 * Email: Me@Yekta.Dev
 */

/**
 * @file argument_parser.cpp
 * @brief A program which parses the arguments given to it.
 */

/** External Libraries **/
#include <string>
#include "console.hpp"

/** Namespaces **/
using namespace std;

/** Constants **/
const string errorNoArg = "No Arguments Are Found!";

// Program's Entry Point
int main(int argc, char const *argv[])
{
    clearConsole();

    if (argc <= 1)
    {
        printLine(errorNoArg);
        return 0;
    }

    printLine(to_string(argc - 1) + " Arguments Are Found!");

    for (int i = 1; i < argc; i++)
    {
        printLine("Argument " + to_string(i) + " is: " + argv[i]);
    }
    
    return 0;
}
