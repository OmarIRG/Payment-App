#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "../Card/Card.h"
#include "../Server/Server.h"
#include "Application.h"



void appStart(void)
{
	ST_cardData_t card_Data;
	ST_cardData_t* cardData = &card_Data;
	ST_accountsDB_t accountRefrence;
	ST_accountsDB_t* accountRefrenc = &accountRefrence;
	ST_transaction_t transacton_Data;
	ST_transaction_t* trans_Data = &transacton_Data;

	/**
	-----------------------------------------------------
	call get card data functions at first of the program
	-----------------------------------------------------
	**/
	
		if (getCardHolderName(cardData) == WRONG_NAME) // get card holder name and check it
		{
			printf("Wrong Name !\n");
			return WRONG_NAME;

		}
	again:
		// loop until user enter right date
		if (getCardExpiryDate(cardData) == WRONG_EXP_DATE) // get card expiry date and check it
		{
			printf("Wrong Expiry Date !\n");
			goto again;
			return WRONG_EXP_DATE;

		}
	again1:
		// loop until user enter right primary account number
		if (getCardPAN(cardData) == WRONG_PAN) // get card primary account number and check it
		{
			printf("Wrong PAN !\n");
			goto again1;
			return WRONG_PAN;

		}

		ST_terminalData_t terminal_Data;
		ST_terminalData_t* termData = &terminal_Data;

		if (isValidCardPAN(cardData) == INVALID_CARD)        // check luhn algorithm 
		{
			printf("Card is Invalid Please enter right Pan\n");
			return 0;
		}
		else
			printf("                                        Card is valid :\n");

		getTransactionDate(termData);  // check luhn algorithm 

		if (isValidAccount(cardData) == ACCOUNT_NOT_FOUND) {

			printf("account isn't in the database \n");
		
		}

		if (isBlockedAccount(accountRefrenc) == RUNNING) {  // check if card running or blocked
			printf("RUNNING\n");
		}
		if (isBlockedAccount(accountRefrenc) == BLOCKED) {
			printf("your card is BLOCKED try to contact the bank to know why :\n");
		
		}

		if (isCardExpired(card_Data, terminal_Data) == EXPIRED_CARD) // check if card is expired or not
		{
			printf("Your Card is Expired, Try to contact the bank to renew it soon . ");
			return 0;
		}
	again3:

		if (setMaxAmountToTransact(termData) == INVALID_MAX_AMOUNT)
		{
			printf("Invalid Max Amount");
			return 0;
		}

		if (getTransactionAmount(termData) == INVALID_AMOUNT) //get transaction amount from user
		{
			printf("wrong Amount, Please Enter the right Amount \n");
			goto again3;
		}

		if (isBelowMaxAmountToTransact(termData) == EXCEED_MAX_AMOUNT) // check if transaction amount is greater than maximum
		{
			printf("Sorry ,but you entered more than allowed of 5000 ");
			return 0;
		}

		

		trans_Data->cardHolderData = card_Data;
		trans_Data->terminalData = terminal_Data;


		if (recieveTransactionData(trans_Data) == DECLINED_STOLEN_CARD)
		{
			printf("\nTransaction Declined This Card Is Stolen and has been blocked \n");
			saveTransaction(trans_Data);
			return 0;
		}

		if (recieveTransactionData(trans_Data) == FRAUD_CARD)
		{
			printf("\nTransaction Declined This Card Is Fraud, Please Return It To The Nearest bank to check it\n");
			saveTransaction(trans_Data);
			return 0;
		}

		if (recieveTransactionData(trans_Data) == APPROVED)
		{
			printf("\nTransaction was successfull, Have a good day\n");         
			saveTransaction(trans_Data);
			return 0;
		}

		if (recieveTransactionData(trans_Data) == DECLINED_INSUFFECIENT_FUND)
		{
			printf("\nTransaction Declined because you entered more than allowed of balance \n"); 
			saveTransaction(trans_Data);
			return 0;
		}

	
		if (recieveTransactionData(trans_Data) == INTERNAL_SERVER_ERROR) {
			printf("\nTransaction Declined Due To Server Error, Please Try Again Later .. ");
			saveTransaction(trans_Data);
			return 0;
		}

	}
