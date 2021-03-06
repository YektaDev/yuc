/*
 * Copyright © 2021 Ali Khaleqi Yekta, All Rights Reserved.
 *
 * Author: Ali Khaleqi Yekta [YektaDev]
 * Website: https://Yekta.Dev
 * Email: Me@Yekta.Dev
 */

/**
 * @file check.cpp
 * @brief A check management program in which
 * the user can view, add, delete, and search his/her checks.
 */

//Made with love in +10 hours!

/** External Libraries **/
#include <string>
#include <list>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "check.hpp"

using namespace std;

CheckList checks;
fstream file;

/** Function Declarations **/
void newCheck();
void editCheck();
void deleteCheck();
void searchByNum();
void searchByName();
void searchByDate();
void listChecks();
void error(const string &err);
void info(const string &inf);
bool importData();
bool writeChecksToFile();

/**
 * Program's Entry Point
 */
int main()
{
    int operationCode;

    console::printMainPage();
    operationCode = console::askInt(nl + nl + strSelectOption);

    while (true)
    {
        if (!importData())
        {
            console::clear();
            console::print(errParseFile + nl, console::B_RED);
            console::pause();
            return 0;
        }

        switch (operationCode)
        {
            case 1:
                newCheck(); // New check
                break;

            case 2:
                editCheck(); // Edit check
                break;

            case 3:
                deleteCheck(); // Delete check
                break;

            case 4:
                searchByNum(); // Search check by number
                break;

            case 5:
                searchByName(); // Search check by name
                break;

            case 6:
                searchByDate(); // Search check by date
                break;

            case 7:
                listChecks(); // List All checks
                break;

            case 8:
                return 0; // Exit

            default:
                error(errInvalidInput); //Invalid input
                break;
        }

        operationCode = console::askInt(strSelectOption);
    }
}

/**
 * Creates a new check and adds it to list.
 */
void newCheck()
{
    Check check = console::askCheck();

    if (checkExists(checks, check.number))
    {
        error(errCheckAlreadyAdded);
        return;
    }

    checks.push_back(check);
    if (!writeChecksToFile())
    {
        error(errSaveFile);
        return;
    }

    info(infCheckAdded);
}

/**
 * Finds a check by its number and edits it.
 */
void editCheck()
{
    if (checks.empty())
    {
        error(errNoChecks);
        return;
    }

    int checkNumber;
    int opt;
    vector<string> items;

    items.emplace_back(optEditCheck);
    items.emplace_back(optGoBack);

    console::clear();
    checkNumber = console::askInt(strEnterCheckNum);

    try
    {
        Check &check = getCheckByNum(checks, checkNumber);

        console::printCheck(check);
        console::printMenuItems(items);

        opt = console::askInt(nl + nl + strSelectOption);

        if (opt == 1)
        {
            check = console::askCheck();
            if (!writeChecksToFile())
            {
                error(errSaveFile);
                return;
            }

            info(infCheckUpdated);
        }
        else if (opt == 2)
        {
            console::printMainPage();
            console::println();
            return;
        }
        else
        {
            error(errInvalidInput);
        }
    }
    catch (nested_exception &e)
    {
        error(errCheckNotFound);
    }
}

/**
 * Finds a check by its number and deletes it after the user confirmation.
 */
void deleteCheck()
{
    if (checks.empty())
    {
        error(errNoChecks);
        return;
    }

    int checkNumber;
    int opt;
    vector<string> items;

    // In here, emplace_back is equivalent to push_back.
    items.emplace_back(optDeleteCheck);
    items.emplace_back(optGoBack);

    console::clear();

    checkNumber = console::askInt(strEnterCheckNum);
    console::clear();

    if (!checkExists(checks, checkNumber))
    {
        error(errCheckNotFound);
        return;
    }

    try
    {
        console::printMenuItems(items);
        opt = console::askInt(strSelectOption);

        if (opt == 1)
        {
            deleteCheckByNum(checks, checkNumber);

            if (!writeChecksToFile())
            {
                error(errSaveFile);
                return;
            }
            info(infCheckDeleted);
        }
        else if (opt == 2)
        {
            console::printMainPage();
            console::println();
            return;
        }
        else
        {
            error(errInvalidInput);
        }
    }
    catch (nested_exception &e)
    {
        error(errCheckNotFound);
    }
}

/**
 * Finds a check by its number and shows it.
 */
void searchByNum()
{
    if (checks.empty())
    {
        error(errNoChecks);
        return;
    }

    int checkNumber;

    console::clear();
    checkNumber = console::askInt(strEnterCheckNum);
    console::clear();

    if (checkExists(checks, checkNumber))
    {
        console::printCheck(getCheckByNum(checks, checkNumber));
        console::pause();
        console::printMainPage();
        console::println();
    }
    else
    {
        error(errCheckNotFound);
    }
}

/**
 * Gets a name and prints the check which contains that name.
 */
void searchByName()
{
    if (checks.empty())
    {
        error(errNoChecks);
        return;
    }

    string name;

    console::clear();
    name = console::askString(strEnterPersonName);
    console::clear();

    try
    {
        console::printCheck(getCheckByName(checks, name));
        console::pause();
        console::printMainPage();
        console::println();
    }
    catch (nested_exception &e)
    {
        error(errCheckNotFound);
    }
}

/**
 * Prints the list of the checks which are in the selected date range sorted by date.
 */
void searchByDate()
{
    if (checks.empty())
    {
        error(errNoChecks);
        return;
    }

    Date startDate, endDate;
    CheckList list;

    console::clear();

    console::print(strStartDate + nl);
    startDate = console::askDate();
    console::clear();

    console::print(strEndDate + nl);
    endDate = console::askDate();
    console::clear();

    try
    {
        list = getChecksByDateRange(checks, startDate, endDate);

        if (list.empty())
        {
            error(errNoChecksInDateRange);
            return;
        }

        sortList(list);

        console::printChecks(list);
        console::pause();
        console::printMainPage();
        console::println();
    }
    catch (nested_exception &e)
    {
        error(errNoChecksInDateRange);
    }
}

/**
 * Prints the list of all of the checks sorted by date.
 */
void listChecks()
{
    if (checks.empty())
    {
        error(errNoChecks);
        return;
    }

    sortList(checks);

    console::clear();
    console::printChecks(checks);
    console::pause();
    console::printMainPage();
    console::println();
}

/**
 * Prints the main menu and an error message.
 *
 * @param err The error message.
 */
void error(const string &err)
{
    console::printMainPage();
    console::println();
    console::printError(err);
}

/**
 * Prints the main menu and an info message.
 *
 * @param inf The info message.
 */
void info(const string &inf)
{
    console::printMainPage();
    console::println();
    console::printInfo(inf);
}

/**
 * Imports the data from text file.
 *
 * @return Whether the operation was successful or not.
 */
bool importData()
{
    string line;
    Check c;
    Date d{};

    // Create the file if doesn't exists
    file.open(strFileName, ios::out | ios_base::app);
    file.close();

    file.open(strFileName, ios::in);
    if (!file.is_open())
    {
        return false;
    }

    checks.clear();

    for (int i = 0; getline(file, line); ++i)
    {
        if (file.fail())
        {
            return false;
        }

        if (i % 6 == 0)
        {
            c.number = stoi(line);
        }
        else if (i % 6 == 1)
        {
            d.year = stoi(line);
        }
        else if (i % 6 == 2)
        {
            d.month = stoi(line);
        }
        else if (i % 6 == 3)
        {
            d.day = stoi(line);
            c.date = d;
        }
        else if (i % 6 == 4)
        {
            c.personName = line;
        }
        else
        {
            c.amount = atol(line.c_str());
            checks.push_back(c);
        }
    }

    file.close();

    return true;
}

/**
 * Write checks data to the text file.
 *
 * @return Whether the operation was successful or not.
 */
bool writeChecksToFile()
{
    string lines;
    Check c;
    Date d;

    file.open(strFileName, ios::out);

    for (int i = 0; i < checks.size(); ++i)
    {
        c = getCheckByIndex(checks, i);
        d = c.date;

        lines += to_string(c.number) + nl; // Number
        lines += to_string(d.year) + nl;   // Date -> Year
        lines += to_string(d.month) + nl;  // Date -> Month
        lines += to_string(d.day) + nl;    // Date -> Day
        lines += c.personName + nl;        // Name
        lines += to_string(c.amount) + nl; // Amount
    }

    file << lines;
    if (file.fail())
    {
        return false;
    }

    checks.clear();
    file.close();

    return true;
}
