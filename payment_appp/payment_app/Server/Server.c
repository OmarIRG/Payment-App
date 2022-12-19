#include <stdio.h>
#include "server.h"
#include <string.h>
#include "../Card/Card.h"

ST_accountsDB_t DataBase[255] =
{   {20000.00 ,RUNNING, "1467938765494732"},
	{10400.00 ,RUNNING, "0077106374661323"},
	{4000.00  ,RUNNING, "5399353562786443"},
	{7000.00  ,BLOCKED, "8989374615436851"},
	{5400.00  ,RUNNING, "6952362058527242"},
	{566.00   ,RUNNING, "4350621408617612"} 
};
ST_transaction_t Transactions[255];
uint32_t count = 0;
ST_transaction_t* list_saved;
EN_transState_t t_state = 0;
uint32_t i = 0;

/*
					   -------------------------------------
							  check if account in data base or not
					   ------------------------------------

*/
EN_serverError_t isValidAccount(ST_cardData_t* cardData)
{
	

	for (i; i < 255; i++)
	{
		if (strcmp((*cardData).primaryAccountNumber, DataBase[i].primaryAccountNumber) == 0)
		{
			return SERVER_OK;
		}
	}
	return ACCOUNT_NOT_FOUND;
}
//---------------------------------------------------------------------------------------------------------------------------------------


/*
					   -------------------------------------
							  check blocked or running
					   ------------------------------------

*/


EN_accountState_t isBlockedAccount(ST_accountsDB_t* accountRefrence)

{

		return DataBase[i].state;
	
}

//---------------------------------------------------------------------------------------------------------------------------------------


/*
					   -------------------------------------------------------------------------
							  check if transaction amount is greater than balance in data base
					   ---------------------------------------------------------------------------

*/

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData)
{
	if ((*termData).transAmount < DataBase[i].balance)
	{
		return SERVER_OK;
	}
	return LOW_BALANCE;
}

EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
	

	if (isValidAccount(&transData->cardHolderData) == ACCOUNT_NOT_FOUND)
	{
		t_state = FRAUD_CARD;
		return FRAUD_CARD;
	}


	if (isBlockedAccount(&transData->transState) == BLOCKED)
	{
		t_state = DECLINED_STOLEN_CARD;
		return DECLINED_STOLEN_CARD;
	}

	if (isAmountAvailable(&transData->terminalData) == LOW_BALANCE)
	{
		t_state = DECLINED_INSUFFECIENT_FUND;
		return DECLINED_INSUFFECIENT_FUND;
	}

	if (saveTransaction(transData) == SAVING_FAILED)
	{
		t_state = INTERNAL_SERVER_ERROR;
		return INTERNAL_SERVER_ERROR;
	}

	t_state = APPROVED;

	printf("\nYour old balance is : %f", DataBase[i].balance);

	DataBase[i].balance = (DataBase[i].balance - (*transData).terminalData.transAmount);

	printf("\nyour new balance is : %f", DataBase[i].balance);
	
	return APPROVED;
}

EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	(*transData).transactionSequenceNumber = count;
	if ((*transData).transactionSequenceNumber < 255)
	{
		transData = transData + count;
		list_saved = transData;
		Transactions[(*transData).transactionSequenceNumber].cardHolderData = (*transData).cardHolderData;
		Transactions[(*transData).transactionSequenceNumber].terminalData = (*transData).terminalData;
		Transactions[transData->transactionSequenceNumber].transState = transData->transState;
		Transactions[(*transData).transactionSequenceNumber].transactionSequenceNumber = (*transData).transactionSequenceNumber + 1;

		
		count++;
		listSavedTransactions();
		
		return SERVER_OK;
	}
	return SAVING_FAILED;
}

void listSavedTransactions(void)
{
	printf("\n\n\n#############################################################\n");
	printf("Transaction Sequence Number: %ld\n", count);
	printf("Transaction Date: %s\n", list_saved->terminalData.transactionDate);
	printf("Transaction Amount: %f\n", list_saved->terminalData.transAmount);
	
	if((t_state) == APPROVED)
		printf("Transaction State is: Approved\n");
	
	if((t_state) == FRAUD_CARD)
		printf("Transaction State is: fraud card\n");
		
	 if ((t_state) == DECLINED_INSUFFECIENT_FUND)
		printf("Transaction State is:  Insufficient fund\n");
		
	 if ((t_state) == INTERNAL_SERVER_ERROR)
		printf("Transaction State is:  Internal Server Error\n");
	 
	 if ((t_state) == DECLINED_STOLEN_CARD)
		printf("Transaction State is:  STOLEN_CARD\n");
		
	
	
	printf("Terminal Max Amount: %f\n", list_saved->terminalData.maxTransAmount);
	
	printf("Cardholder Name: %s\n", list_saved->cardHolderData.cardHolderName);
	
	printf("PAN: %s\n", list_saved->cardHolderData.primaryAccountNumber);
	
	printf("Card Expiration Date: %s\n", list_saved->cardHolderData.cardExpirationDate);
	
	printf("#############################################################\n");
	
}