
#ifndef CARD_H
#define CARD_H

typedef unsigned char       uint8_t;
typedef signed char         int8_t;
typedef unsigned short      uint16_t;
typedef unsigned int		uint32_t;

typedef struct ST_cardData_t                  //get data from user and store it here
{
	uint8_t cardHolderName[25];
	uint8_t primaryAccountNumber[20];
	uint8_t cardExpirationDate[6];
}ST_cardData_t;



typedef enum EN_cardError_t                  
{
	Card_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN

}EN_cardError_t;

EN_cardError_t getCardHolderName(ST_cardData_t* cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData);
EN_cardError_t getCardPAN(ST_cardData_t* cardData);


#endif 
