
#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


#include "Stm32_F103C6_gpio_driver.h"
#include "Stm32_F103C6_USART_driver.h"
#include "KPD_interface.h"
#include "Lcd.h"
#include "PIR.h"
#include "LED.h"
#include "Stm32_F103C6_TIMER_driver.h"
#include "Servo.h"



#define RFID_Entry_USART	USART1
#define RFID_Exit_USART		USART2

#define ADMIN_LCD	LCD_Instant_1
#define USER_LCD	LCD_Instant_2

uint8_t KeyPressed;


uint8_t PIR1_Reading=0,PIR2_Reading=0;


// 4 ids each one with 5 digits including '\0'
uint8_t AllowedIDs[4][5] = {0};


// Dump variable to read 'enter' pressed by the user
uint8_t dump=0;

volatile uint8_t EntryReceived=0,ExitReceived=0;

volatile static uint8_t EntryCounter=0,ExitCounter=0;
uint8_t temp_EntryCard[6]={0},temp_ExitCard[6]={0};

uint8_t EntryCard[4]={0},ExitCard[4]={0};


void clearArray(uint8_t arr[], uint8_t size)
{
	for(uint8_t i=0;i<size;i++){
		arr[i] = 0;
	}
}


void ShowIDs(uint8_t arr[][5], uint8_t row)
{
	for(uint8_t i=0;i<row;i++){
		LCD_ES_tGoTo(ADMIN_LCD, i, 0);
		Lcd_ES_tdisplayNum(ADMIN_LCD, i);
		Lcd_ES_tsendString(ADMIN_LCD, "- ");
		Lcd_ES_tsendString(ADMIN_LCD, arr[i]);
	}
}


void CopyArray(uint8_t destination[], uint8_t source[]){
	uint8_t i = 0;
	while(source[i]!='\0'){
		destination[i] = source[i];
		i++;
	}
}


volatile static uint8_t availableSlots = 3;


// Comparing between the passed card and the database

uint8_t CompareWithDataBase(uint8_t EnteredCard[],uint8_t arr[][5])
{
	uint8_t i=0,j=0,counter=0;
	while(j<4){
		for(i=0;i<4;i++){
			if(EnteredCard[i]==arr[j][i]){
				counter++;
			}
		}

		//		counter = 0;
		j++;
	}
	if((counter%4 == 0) && (counter!=0)){
		return 1;
	}else{
		return 0;
	}
}


typedef enum{
	ADMIN_CREDENTIALS,
	ADMIN_OPTIONS,
	DELETE_ID,
	ADD_ID_INDEX,
	ADD_ID
}WHICH_STATE;

WHICH_STATE currentState = ADMIN_CREDENTIALS;

uint8_t gettingOption = 0,userDisplayed = 0,adminDisplayed = 0;


void UART_RecieverEntry_CallBack(void)
{
	LED_OFF(G_LED);
	LED_OFF(R_LED);
	if(EntryCounter==0){
		MCAL_UART_ReceiveData(RFID_Entry_USART, &temp_EntryCard[0], Disable);EntryCounter++;}
	else if(EntryCounter==1){
		MCAL_UART_ReceiveData(RFID_Entry_USART, &temp_EntryCard[1], Disable);EntryCounter++;}
	else if(EntryCounter==2){
		MCAL_UART_ReceiveData(RFID_Entry_USART, &temp_EntryCard[2], Disable);EntryCounter++;}
	else if(EntryCounter==3){
		MCAL_UART_ReceiveData(RFID_Entry_USART, &temp_EntryCard[3], Disable);EntryCounter++;}
	else if(EntryCounter==4){
		temp_EntryCard[4] = '\0';
		MCAL_UART_ReceiveData(RFID_Entry_USART, &dump, Disable);
		EntryCounter=0;
		EntryReceived=1;
		MCAL_UART_SendString(RFID_Entry_USART, "Your ID: ", Enable);
		MCAL_UART_SendString(RFID_Entry_USART, temp_EntryCard, Enable);
		if(CompareWithDataBase(temp_EntryCard,AllowedIDs)){
			if(availableSlots>0)
				availableSlots--;
			lcd_ES_tclear(USER_LCD);
			Lcd_ES_tsendString(USER_LCD, "Eligible ID");
			LED_ON(G_LED);
			Servo_Move(Servo_Entry, UP);
			PIR_Read(PIR_1, &PIR1_Reading);
			while(PIR1_Reading){
				PIR_Read(PIR_1, &PIR1_Reading);
				Delay_ms(3);
			}
			Servo_Move(Servo_Entry, DOWN);
			LED_OFF(G_LED);
		}else{
			lcd_ES_tclear(USER_LCD);
			Lcd_ES_tsendString(USER_LCD, "Unregistered ID");
			LED_ON(R_LED);
		}
		clearArray(temp_EntryCard,5);
	}else{
		EntryCounter=-1;
	}
	gettingOption = 0;
	userDisplayed = 0;
	adminDisplayed = 0;
	lcd_ES_tclear(USER_LCD);
	currentState = ADMIN_OPTIONS;
}





void UART_RecieverExit_CallBack(void)
{
	if(ExitCounter==0){
		MCAL_UART_ReceiveData(RFID_Exit_USART, &temp_ExitCard[0], Disable);ExitCounter++;}
	else if(ExitCounter==1){
		MCAL_UART_ReceiveData(RFID_Exit_USART, &temp_ExitCard[1], Disable);ExitCounter++;}
	else if(ExitCounter==2){
		MCAL_UART_ReceiveData(RFID_Exit_USART, &temp_ExitCard[2], Disable);ExitCounter++;}
	else if(ExitCounter==3){
		MCAL_UART_ReceiveData(RFID_Exit_USART, &temp_ExitCard[3], Disable);ExitCounter++;}
	else if(ExitCounter==4){
		temp_ExitCard[4] = '\0';
		// To receive the enter in a dump variable
		MCAL_UART_ReceiveData(RFID_Exit_USART, &dump, Disable);
		ExitCounter=0;
		ExitReceived=1;
		MCAL_UART_SendString(RFID_Exit_USART, "Your ID: ", Enable);
		MCAL_UART_SendString(RFID_Exit_USART, temp_ExitCard, Enable);
		if(CompareWithDataBase(temp_ExitCard,AllowedIDs)){
			if(availableSlots<3)
				availableSlots++;
			lcd_ES_tclear(USER_LCD);
			Lcd_ES_tsendString(USER_LCD, "Eligible ID");
			Servo_Move(Servo_Exit, UP);
			PIR_Read(PIR_2, &PIR2_Reading);
			while(PIR2_Reading){
				PIR_Read(PIR_2, &PIR2_Reading);
				Delay_ms(3);
			}
			Servo_Move(Servo_Exit, DOWN);
		}else{
			lcd_ES_tclear(USER_LCD);
			Lcd_ES_tsendString(USER_LCD, "Unregistered ID");
		}
		clearArray(temp_ExitCard,5);
	}else{
		ExitCounter=0;
	}
	gettingOption = 0;
	userDisplayed = 0;
	adminDisplayed = 0;
	lcd_ES_tclear(USER_LCD);
	currentState = ADMIN_OPTIONS;
}








void clock_init()
{
	// Enable clock for GPIOA (bit 2)
	RCC_GPIOA_CLK_EN();
	// Enable clock for GPIOB (bit 3)
	RCC_GPIOB_CLK_EN();

	RCC_AFIO_CLK_EN();
}


int main(void)
{
	clock_init();
	Lcd_ES_tInit(LCD_Instant_1);
	lcd_ES_tclear(LCD_Instant_1);
	Lcd_ES_tInit(LCD_Instant_2);
	lcd_ES_tclear(LCD_Instant_2);
	KPD_init();
	PIR_Init();
	LED_Init();
	TIMER2_Init();
	Servo_Init(Servo_Entry);
	Servo_Init(Servo_Exit);

	Servo_Move(Servo_Entry, DOWN);
	Servo_Move(Servo_Exit, DOWN);




	// Both USARTs tested


	// Initialization of USART
	UART_Config UART_EntryCfg;
	UART_EntryCfg.BaudRate = UART_BaudRate_115200;
	UART_EntryCfg.HWFlowCtrl = UART_HWFlowCtrl_NONE;
	UART_EntryCfg.IRQ_Enable = UART_IRQ_Enable_RXNE;
	UART_EntryCfg.P_IRQ_CallBack = UART_RecieverEntry_CallBack;
	UART_EntryCfg.Parity = UART_Parity_NONE;
	UART_EntryCfg.Payload_length = UART_Payload_Length_8B;
	UART_EntryCfg.StopBits = UART_StopBits_1;
	UART_EntryCfg.USART_Mode = UART_Mode_Tx_Rx;
	MCAL_UART_Init(RFID_Entry_USART, &UART_EntryCfg);
	MCAL_UART_GPIO_SetPins(RFID_Entry_USART);


	UART_Config UART_ExitCfg;
	UART_ExitCfg.BaudRate = UART_BaudRate_115200;
	UART_ExitCfg.HWFlowCtrl = UART_HWFlowCtrl_NONE;
	UART_ExitCfg.IRQ_Enable = UART_IRQ_Enable_RXNE;
	UART_ExitCfg.P_IRQ_CallBack = UART_RecieverExit_CallBack;
	UART_ExitCfg.Parity = UART_Parity_NONE;
	UART_ExitCfg.Payload_length = UART_Payload_Length_8B;
	UART_ExitCfg.StopBits = UART_StopBits_1;
	UART_ExitCfg.USART_Mode = UART_Mode_Tx_Rx;
	MCAL_UART_Init(RFID_Exit_USART, &UART_ExitCfg);
	MCAL_UART_GPIO_SetPins(RFID_Exit_USART);


	// Admin LCD
	Lcd_ES_tsendString(ADMIN_LCD, "Hello Admin");
	LCD_ES_tGoTo(ADMIN_LCD, 1, 0);
	Lcd_ES_tsendString(ADMIN_LCD, "Enter Password: ");
	LCD_ES_tGoTo(ADMIN_LCD, 2, 0);


	lcd_ES_tclear(USER_LCD);
	LCD_ES_tGoTo(USER_LCD, 0, 0);
	Lcd_ES_tsendString(USER_LCD, "Welcome to our");
	LCD_ES_tGoTo(USER_LCD, 1, 0);
	Lcd_ES_tsendString(USER_LCD, "Parking :)");
	LCD_ES_tGoTo(USER_LCD, 2, 0);
	Lcd_ES_tsendString(USER_LCD, "Empty Slots:");
	LCD_ES_tGoTo(USER_LCD, 3, 0);
	Lcd_ES_tsendString(USER_LCD, "Pass your card");
	LCD_ES_tGoTo(USER_LCD, 2, 14);
	Lcd_ES_tdisplayNum(USER_LCD, availableSlots);






	// Try to send and receive strings using USART
	// Done using interrupts(CallBack functions above)


	uint8_t password[] = "1234";

	uint8_t enteredPassword[5] = {'\0'};
	uint8_t enteringIndex = 0;

	uint8_t enteredOption = 0;





	uint8_t DeleteIndex = 0;
	uint8_t AddIndex = 0;

	uint8_t inputIndex = 0;


	uint8_t PressedID_Digit = 0;

	uint8_t IDFlag = 0, IndexFlag = 0, DelteIndex = 0;



	while(1)
	{




		switch(currentState){
		case ADMIN_CREDENTIALS:
		{


			//PIR_Read(PIR_2, &PIR2_Reading);
			// Make password four items
			KPD_ES_tGetKeyPressed(&KeyPressed);
			if(KeyPressed!=KPD_U8_NOT_PRESSED)
			{
				LCD_ES_tGoTo(ADMIN_LCD, 2, enteringIndex+3);
				Lcd_ES_tsendChar(ADMIN_LCD, '*');
				enteredPassword[enteringIndex] = KeyPressed;
				enteringIndex++;
				if(enteringIndex>=4){
					// Comparing between two passwords
					if(strcmp(enteredPassword,password) == 0){
						// Password is correct
						lcd_ES_tclear(ADMIN_LCD);
						LCD_ES_tGoTo(ADMIN_LCD, 2, 0);
						Lcd_ES_tsendString(ADMIN_LCD, "Correct Password");
						Delay_ms(100);
						lcd_ES_tclear(ADMIN_LCD);
						gettingOption = 0;
						userDisplayed = 0;
						adminDisplayed = 0;
						currentState = ADMIN_OPTIONS;
					}else{
						// Password is wrong
						lcd_ES_tclear(ADMIN_LCD);
						LCD_ES_tGoTo(ADMIN_LCD, 2, 0);
						Lcd_ES_tsendString(ADMIN_LCD, "Wrong Password");
					}
					enteringIndex = 0;
				}
			}
			break;
		}
		case ADMIN_OPTIONS:
		{
			// Ask the user for his desired action
			// 1- display id    2- delete id    3- add id      4- delete all Ids   (Each id is 4 digit)
			if(!userDisplayed){
				lcd_ES_tclear(USER_LCD);
				LCD_ES_tGoTo(USER_LCD, 0, 0);
				Lcd_ES_tsendString(USER_LCD, "Welcome to our");
				LCD_ES_tGoTo(USER_LCD, 1, 0);
				Lcd_ES_tsendString(USER_LCD, "Parking :)");
				LCD_ES_tGoTo(USER_LCD, 2, 0);
				Lcd_ES_tsendString(USER_LCD, "Empty Slots:");
				LCD_ES_tGoTo(USER_LCD, 3, 0);
				Lcd_ES_tsendString(USER_LCD, "Pass your card");
				LCD_ES_tGoTo(USER_LCD, 2, 14);
				Lcd_ES_tdisplayNum(USER_LCD, availableSlots);
				userDisplayed = 1;
			}


			IDFlag = 0;
			IndexFlag = 0;
			DelteIndex = 0;

			if(!adminDisplayed){
				LCD_ES_tGoTo(ADMIN_LCD, 0, 0);
				Lcd_ES_tsendString(ADMIN_LCD, "1- Display IDs");
				LCD_ES_tGoTo(ADMIN_LCD, 1, 0);
				Lcd_ES_tsendString(ADMIN_LCD, "2- Delete ID");
				LCD_ES_tGoTo(ADMIN_LCD, 2, 0);
				Lcd_ES_tsendString(ADMIN_LCD, "3- Add ID");
				LCD_ES_tGoTo(ADMIN_LCD, 3, 0);
				Lcd_ES_tsendString(ADMIN_LCD, "4- Delete all");
				adminDisplayed = 1;
			}


			if(!gettingOption){
				// Getting option from user
				KPD_ES_tGetKeyPressed(&enteredOption);
				if(enteredOption!=KPD_U8_NOT_PRESSED){
					gettingOption = 1;
					switch(enteredOption){
					case '1':  // Display IDs
					{
						lcd_ES_tclear(ADMIN_LCD);
						ShowIDs(AllowedIDs,4);
						Delay_ms(50);
						gettingOption = 0;
						userDisplayed = 0;
						adminDisplayed = 0;
						break;
					}
					case '2':   // Delete an ID
					{
						currentState = DELETE_ID;
						break;
					}
					case '3':   // Choose the index he want to add to
					{
						currentState = ADD_ID_INDEX;
						break;
					}
					case '4':  // Delete All
					{
						lcd_ES_tclear(ADMIN_LCD);
						Lcd_ES_tsendString(ADMIN_LCD, "IDs deleted");
						LCD_ES_tGoTo(ADMIN_LCD, 1, 0);
						Lcd_ES_tsendString(ADMIN_LCD, "Successfully");
						Delay_ms(200);
						uint8_t j=0;
						for(j=0;j<4;j++){
							clearArray(AllowedIDs[j], 5);
						}
						gettingOption = 0;
						userDisplayed = 0;
						adminDisplayed = 0;
						break;
					}
					default:
					{
						lcd_ES_tclear(ADMIN_LCD);
						Lcd_ES_tsendString(ADMIN_LCD, "Invalid Option");
						gettingOption = 0;
						userDisplayed = 0;
						adminDisplayed = 0;
					}
					}

				}
			}



			break;
		}
		case ADD_ID_INDEX:
		{
			lcd_ES_tclear(ADMIN_LCD);
			Lcd_ES_tsendString(ADMIN_LCD, "Enter Index: ");
			while(!IndexFlag){
				KPD_ES_tGetKeyPressed(&AddIndex);
				if(AddIndex!=KPD_U8_NOT_PRESSED){
					// Getting the input from the ADMIN
					IndexFlag = 1;
					currentState = ADD_ID;
				}
			}
			break;
		}



		case ADD_ID:
		{
			lcd_ES_tclear(ADMIN_LCD);
			Lcd_ES_tsendString(ADMIN_LCD, "Enter ID: ");
			//Lcd_ES_tdisplayNum(ADMIN_LCD, inputIndex);
			while(!IDFlag){
				KPD_ES_tGetKeyPressed(&PressedID_Digit);
				if(PressedID_Digit!=KPD_U8_NOT_PRESSED){
					AllowedIDs[AddIndex-'0'][inputIndex] = PressedID_Digit;
					//inputID[inputIndex] = PressedID_Digit;
					Lcd_ES_tsendChar(ADMIN_LCD, PressedID_Digit);
					inputIndex++;
					if(inputIndex>=4){
						lcd_ES_tclear(ADMIN_LCD);
						LCD_ES_tGoTo(ADMIN_LCD, 0, 0);
						Lcd_ES_tsendString(ADMIN_LCD, "Entered ID");
						LCD_ES_tGoTo(ADMIN_LCD, 1, 0);
						//Lcd_ES_tsendString(ADMIN_LCD, AllowedIDs[AddIndex-'0']);
						inputIndex = 0;
						IDFlag = 1;
						lcd_ES_tclear(ADMIN_LCD);
						gettingOption = 0;
						userDisplayed = 0;
						adminDisplayed = 0;
						currentState = ADMIN_OPTIONS;
					}
				}
			}
			break;
		}


		case DELETE_ID:
		{
			lcd_ES_tclear(ADMIN_LCD);
			Lcd_ES_tsendString(ADMIN_LCD, "Enter Index: ");
			while(!DelteIndex){
				// Choose the index of the ID, he want to delete
				KPD_ES_tGetKeyPressed(&DeleteIndex);
				if(DeleteIndex!=KPD_U8_NOT_PRESSED){
					uint8_t i=0;
					for(i=0;i<4;i++){
						AllowedIDs[DeleteIndex-'0'][i] = 0;
					}

					lcd_ES_tclear(ADMIN_LCD);
					DelteIndex = 1;
					gettingOption = 0;
					userDisplayed = 0;
					adminDisplayed = 0;
					currentState = ADMIN_OPTIONS;
				}
			}
			break;
		}
		}

	}
}
