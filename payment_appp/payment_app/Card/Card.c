#define _CRT_SECURE_NO_WARNINGS // to solve scanf error  

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "card.h"
uint32_t check_digit = 0;
ST_cardData_t card_data;
/*
                       -------------------------------------
                              get name from user
                       ------------------------------------

*/
EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
    
    printf("Please enter Card Holder's Name: ");

    gets(card_data.cardHolderName); //get holder name from user
    strcpy(cardData->cardHolderName, card_data.cardHolderName);
    // Check on the Card Holder's Name format
    if(strlen(card_data.cardHolderName) < 16 || NULL == (card_data.cardHolderName) || strlen(card_data.cardHolderName) > 25)
    {
            return WRONG_NAME;
    }
    for (check_digit ; check_digit < 26; check_digit++) {
        if (isdigit(cardData->cardHolderName[check_digit])) {
            return WRONG_NAME;
        }
       }

   
        printf("Hello:  %s\n", (*cardData).cardHolderName);

        return Card_OK;
   
}

/*
                       -------------------------------------
                              get pan from user
                       ------------------------------------

*/

EN_cardError_t getCardPAN(ST_cardData_t* cardData) // get card pan from user
{

    printf("Please enter primary account number : ");

    
   
    int length, i;

    scanf("%s", card_data.primaryAccountNumber);
    strcpy(cardData->primaryAccountNumber, card_data.primaryAccountNumber);
    length = strlen(card_data.primaryAccountNumber);

   

    // Check on the Card PAN format
    if (strlen(card_data.primaryAccountNumber) < 16 || strlen(card_data.primaryAccountNumber) > 19 || (card_data.primaryAccountNumber) == NULL) // check if its less than 16 and more than 19
    {
        return WRONG_PAN;
    }

    for (i = 0; i < length; i++)
        if (!isdigit(card_data.primaryAccountNumber[i]))
        {
            printf("Entered input is not a number\n");
            return WRONG_PAN;
        }

   
        printf("Card PAN number is: %s\n", (*cardData).primaryAccountNumber);
        printf("-----------------------------------------------------------\n");
        return Card_OK;
   
}

/*
                       ---------------------------------------------
                              get date of espiration from user
                       --------------------------------------------

*/


EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)  //get expiry date from user at format MM/YY
{
    printf("Please enter card Expiry Date in the format of MM/YY: ");


    gets(card_data.cardExpirationDate);

    strcpy(cardData->cardExpirationDate , card_data.cardExpirationDate);


    char first_month = cardData->cardExpirationDate[1];
    char second_month = cardData->cardExpirationDate[0];

   
    if (strlen(card_data.cardExpirationDate) != 5 || (card_data.cardExpirationDate) == NULL) 
        return WRONG_EXP_DATE;

        if(!isdigit(card_data.cardExpirationDate[0]) || !isdigit(card_data.cardExpirationDate[1]))
            return WRONG_EXP_DATE;

        if (((*cardData).cardExpirationDate[2]) != '/')
            return WRONG_EXP_DATE;

        if (!isdigit(card_data.cardExpirationDate[3]) || !isdigit(card_data.cardExpirationDate[4]))
            return WRONG_EXP_DATE;

        if (((*cardData).cardExpirationDate[0] == '0') && ((*cardData).cardExpirationDate[1]) == '0')
            return WRONG_EXP_DATE;

        if (((*cardData).cardExpirationDate[4] == '0') && ((*cardData).cardExpirationDate[3]) == '0')
            return WRONG_EXP_DATE;

        if (first_month > '2') {
            if (second_month >= '1')
                return WRONG_EXP_DATE;
        }

       
        printf("The Expiry Date is: %s\n", (*cardData).cardExpirationDate);
        return Card_OK;
    
}