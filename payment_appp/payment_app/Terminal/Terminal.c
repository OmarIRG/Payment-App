#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "terminal.h"
#include "../Card/Card.h"
#include <time.h>
#include <string.h>

float MaxAmountToTransact = 5000;
ST_terminalData_t date;


/*
                       -----------------------------------------------------------------------------------------------------------------
                              check if transaction amount is valid or not by this site https://www.geeksforgeeks.org/luhn-algorithm/
                       ------------------------------------------------------------------------------------------------------------------
*/

EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData)
{

    uint32_t count = 0;
    int sum = 0,
        second = 0;
    uint32_t length = strlen((*cardData).primaryAccountNumber);

    for (int i = length - 1; i >= 0; i--)
    {
        count = (*cardData).primaryAccountNumber[i] - '0';
        if (second == 1)
            count = count * 2;

        sum += count / 10;
        sum += count % 10;
        second = !second;

    }
    if (sum % 10 == 0) {
        return OK;
    }
    else {
        return INVALID_CARD;
    }
}
uint8_t day[3];
uint8_t month[3];
uint8_t year[5];


/**

---------------------------------------------------------
now we get date from system
---------------------------------------------------------

**/

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
    time_t t = time(NULL);
    struct tm real_time = *localtime(&t);

    sprintf(day, "%d", real_time.tm_mday);           // Get Day from system and store it in currDay
    sprintf(month, "%d", real_time.tm_mon + 1);        // Get Month from system and store it in currMon 
    sprintf(year, "%d", real_time.tm_year + 1900);

    if (real_time.tm_mday < 10)
    {
        ((*termData).transactionDate[0]) = '0';
        ((*termData).transactionDate[1]) = day[0];
    }
    else {
        ((*termData).transactionDate[0]) = day[0];
        ((*termData).transactionDate[1]) = day[1];
    }

    ((*termData).transactionDate[2]) = '/';

    // Storing MM
    if (month < 10)
    {
        ((*termData).transactionDate[3]) = '0';
        ((*termData).transactionDate[4]) = month[0];

    }
    else {
        ((*termData).transactionDate[3]) = month[0];
        ((*termData).transactionDate[4]) = month[1];
    }

    // Storing YYYY
    ((*termData).transactionDate[5]) = '/';
    ((*termData).transactionDate[6]) = year[0];
    ((*termData).transactionDate[7]) = year[1];
    ((*termData).transactionDate[8]) = year[2];
    ((*termData).transactionDate[9]) = year[3];
    ((*termData).transactionDate[10]) = '\0';

    printf("Date is : %s\n", (*termData).transactionDate);

    return OK;
}
/*
                       ------------------------------------------------------
                              check if card is expired or not
                       ------------------------------------------------------
*/

EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData)
{
    // cardExpirationDate MM/YY      transactionDate DD/MM/YYYY
  

    if (((*cardData).cardExpirationDate[3]) < ((*termData).transactionDate[8]))                    // check year first
        return EXPIRED_CARD;

    if (((*cardData).cardExpirationDate[3]) == ((*termData).transactionDate[8]))
   
        if (((*cardData).cardExpirationDate[4]) < ((*termData).transactionDate[9])) 
            return EXPIRED_CARD;
            
        // ------------------------------------------------------------------------------------------------//
   
    if (((*cardData).cardExpirationDate[0]) < ((*termData).transactionDate[3])) 
                return EXPIRED_CARD;

        if (((*cardData).cardExpirationDate[0]) == ((*termData).transactionDate[3]))
            {
             if (((*cardData).cardExpirationDate[1]) < ((*termData).transactionDate[4])) 
                    return EXPIRED_CARD;
            }
        
    
  
    
        printf("card isn't expired yet \n");
        return OK;
    
}

/*
                       ------------------------------------------------------
                              check if card is valid or not
                       ------------------------------------------------------
*/


EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
    // should be more than 0 to make transaction
    ST_terminalData_t t_amount;
    printf("Please enter the Transaction Amount: ");

    scanf("%f", &t_amount.transAmount);
    termData->transAmount = t_amount.transAmount ;
    if ((*termData).transAmount <= 0)
        return INVALID_AMOUNT;

    printf("Your Transaction Amount is: %f\n", (*termData).transAmount);
    printf("------------------------------------------------------------------\n");

    return OK;
}

/*
                       ---------------------------
                              set max amount
                       ---------------------------

*/
EN_terminalError_t setMaxAmountToTransact(ST_terminalData_t* termData)
{
    // Prints max transaction amount to let user know before typing the transaction

    (*termData).maxTransAmount = MaxAmountToTransact;

    printf("Max Transaction Amount is : %f\n", (*termData).maxTransAmount);

    return OK;
}
/*
                       --------------------------------------------------
                              compare transaction amount to maximum
                       --------------------------------------------------

*/

EN_terminalError_t isBelowMaxAmountToTransact(ST_terminalData_t* termData)
{
    // Check if the Transactions Amount is less than the Max Amount

    if (((*termData).transAmount - (*termData).maxTransAmount) > 0) {
        return EXCEED_MAX_AMOUNT;
    }

    return OK;
}

