/**
 * @file assignment1.c
 * @author Elis Engström (elis.engstrom@yaelev.se)
 * @brief Checks if a swedish personal number has a valid last number.
 * It takes an input of "YYMMDD-NNNC" Where C is the number getting validated.
 * It also checks if the date is correct input.
 * @version 0.1
 * @date 2024-11-17
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 12
#define EXPECTED_LENGHT 11
#define YEAR_TENS 0
#define YEAR_DIGIT 1
#define MONTH_TENS 2
#define MONTH_DIGIT 3
#define DAY_TENS 4
#define DAY_DIGIT 5
#define DASH 6
#define SERIAl_THOUSAND 7
#define SERIAL_HUNDRED 8
#define SERIAL_TENS 9
#define CONTROLL_NR 10
#define JANUARY 1
#define FEBRUARY 2
#define MARCH 3
#define APRIL 4
#define MAY 5
#define JUNE 6
#define JULY 7
#define AUGUST 8
#define SEPTEMBER 9
#define OCTOBER 10
#define NOVEMBER 11
#define DECEMBER 12
#define ODD_MONTHS 7
#define ODD_DAYS 31
#define EVEN_DAYS 30
#define LEAP_DAY 29
#define FEBRUAR_DAYS 28
#define INVALID_INPUT 1
#define INVALID_DAY 2
#define INVALID_CHECK_NUMBER 3
#define NO_ERROR 0
#define ODD 1
#define EVEN 2
#define NO_CHECK_NUMBER 9
#define NINETENHUNDRED 1900
#define TWOTHUSAND 2000
#define MAX_CHECK 9
#define TEN 10
/**
 * @brief Main function that checks if the input is correct. Returns an int that shows if there was an error or correct input.
 *
 * @param nr
 * @return int
 */
int checkPersonalNr(char nr[]);
/**
 * @brief Check if a year is a leapyear to make sure that february 29 can be valid.
 *
 * @param year
 * @return true
 * @return false
 */
bool leapYear(int year);
/**
 * @brief Checks if the input date is valid.
 *
 * @param year
 * @param month
 * @param day
 * @return true
 * @return false
 */
bool validDay(int year, int month, int day);
/**
 * @brief Final calculation of the controll number.
 *
 * @param nr
 * @return true
 * @return false
 */
bool checkNumber(char nr[]);

/**
 * @brief Main function, where user inputs a personal number.
 *
 * @return int
 */
int main(void)
{

    char inputString[SIZE];
    (void)printf("Enter a personal number in format YYMMDD-NNNN: ");
    (void)scanf("%11s", inputString);
    if (strlen(inputString) != EXPECTED_LENGHT || inputString[DASH] != '-')
    {
        printf("Invalid input!\n");
    }
    else
    {
        int correctNumber = checkPersonalNr(inputString);
        if (correctNumber == NO_ERROR)
        {
            (void)printf("The personal number %s is valid.\n", inputString);
        }
        else
        {
            (void)printf("Error: %s\n", 
            (correctNumber == INVALID_INPUT)? "Invalid input.":
            (correctNumber == INVALID_DAY)? "Invalid date.":
            (correctNumber == INVALID_CHECK_NUMBER)? "Invalid check number.":
            "No error");
        }
    }
    return 0;
}

int checkPersonalNr(char nr[])
{
    int returnNr = NO_ERROR;
    
    // The "- '0'" is to convert char to int
    int year = ((nr[YEAR_TENS] - '0') * TEN) + (nr[YEAR_DIGIT] - '0');
    int month = ((nr[MONTH_TENS] - '0') * TEN) + (nr[MONTH_DIGIT] - '0');
    int day = ((nr[DAY_TENS] - '0') * TEN) + (nr[DAY_DIGIT] - '0');
    if (year < 0 || month > DECEMBER || month < JANUARY || day > ODD_DAYS || day < 1)
    {
        returnNr = INVALID_INPUT;
    }
    if (returnNr == NO_ERROR)
    {
        if (validDay(year, month, day))
        {
            if (checkNumber(nr))
            {
                returnNr = NO_ERROR;
            }
            else
            {
                returnNr = INVALID_CHECK_NUMBER;
            }
        }
        else
        {
            returnNr = INVALID_DAY;
        }
    }

    return returnNr;
}

bool leapYear(int year)
{
    bool leapYear = false;
    int ninteenHundred = NINETENHUNDRED + year;
    int twoThusnads = TWOTHUSAND + year;
    if ((ninteenHundred % 100 != 0 && ninteenHundred % 4 == 0) || (ninteenHundred % 400 == 0))
    {
        leapYear = true;
    }
    else if ((twoThusnads % 100 != 0 && twoThusnads % 4 == 0) || (twoThusnads % 400 == 0))
    {
    }
    return leapYear;
}

bool validDay(int year, int month, int day)
{
    const int oddMonths[ODD_MONTHS] = {JANUARY, MARCH, MAY, JULY, AUGUST, OCTOBER, DECEMBER};
    bool correctDate = false;
    if (day < 31 && month != FEBRUARY)
    {
        correctDate = true;
    }
    else if (month == FEBRUARY)
    {
        if (leapYear(year))
        {
            if (day <= LEAP_DAY)
            {
                correctDate = true;
            }
        }
        else
        {
            if (day <= FEBRUAR_DAYS)
            {
                correctDate = true;
            }
        }
    }
    else if (day > EVEN_DAYS)
    {
        bool odd = false;
        for (int i = 0; i < ODD_MONTHS && !odd; i++)
        {
            if (month == oddMonths[i])
            {
                odd = true;
                if (day == ODD_DAYS)
                {
                    correctDate = true;
                }
            }
        }
    }
    return correctDate;
}

bool checkNumber(char nr[])
{
    bool correctNr = false;
    // The "- '0'" is to convert char to int
    int yearTens = (nr[YEAR_TENS] - '0') * EVEN; 
    int yearDigit = (nr[YEAR_DIGIT] - '0') * ODD;
    int monthTens = (nr[MONTH_TENS] - '0') * EVEN;
    int monthDigit = (nr[MONTH_DIGIT] - '0') * ODD;
    int dayTens = (nr[DAY_TENS] - '0') * EVEN;
    int dayDigit = (nr[DAY_DIGIT] - '0') * ODD;
    int serialThousand = (nr[SERIAl_THOUSAND] - '0') * EVEN;
    int serialHundred = (nr[SERIAL_HUNDRED] - '0') * ODD;
    int serialTens = (nr[SERIAL_TENS] - '0') * EVEN;
    int fixNumbers[NO_CHECK_NUMBER] = {yearTens, yearDigit, monthTens, monthDigit, dayTens, dayDigit, serialThousand, serialHundred, serialTens};
    int lastNumber = 0;
    for (int i = 0; i < NO_CHECK_NUMBER; i++)
    {
        if (fixNumbers[i] > MAX_CHECK)
        {
            fixNumbers[i] = fixNumbers[i] % TEN + fixNumbers[i] / TEN;
        }
        lastNumber += fixNumbers[i];
    }
    int controllNr = (TEN - (lastNumber % TEN)) % TEN;
    if (controllNr == (nr[CONTROLL_NR] - '0'))
    {
        correctNr = true;
    }
    return correctNr;
}
