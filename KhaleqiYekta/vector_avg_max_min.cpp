/*
 * Copyright © 2021 Ali Khaleqi Yekta, All Rights Reserved.
 *
 * Author: Ali Khaleqi Yekta [YektaDev]
 * Website: https://Yekta.Dev
 * Email: Me@Yekta.Dev
 */

/**
 * @file vector_avg_max_min.cpp
 * @brief A program which gets some numbers from the user and shows the maximum, minimum, and the average of them.
 */

/** External Libraries **/
#include <string>
#include <vector>
#include "console.hpp"

/** Namespaces **/
using namespace std;

// Program's Entry Point
int main()
{
    /** Define Local Variables **/
    size_t numbersCount;
    vector<int> numbers;
    int sum, max, min;
    float avg;

    clearConsole();

    // Getting the count of numbers
    numbersCount = askForInt("Enter the count of numbers: ");

    // Getting the numbers
    for (size_t i = 0; i < numbersCount; ++i)
    {
        int number = askForInt("Enter number " + to_string(i + 1) + ": ");
        numbers.push_back(number);

        if (i == 0)
        {
            // Init variables
            sum = number;
            min = number;
            max = number;
        }
        else
        {
            // Add to sum
            sum += number;
        }
    }

    // Finding out min and max
    for (int num : numbers)
    {
        if (num > max)
        {
            max = num;
        }
        if (num < min)
        {
            min = num;
        }
    }

    // Calculating the average
    avg = (float) sum / numbersCount;

    // Printing the result
    printLine("Average: " + to_string(avg) + "\tMax: " + to_string(max) + "\tMin: " + to_string(min));

    /** End of the program **/
    pauseConsole();
    return 0;
}
