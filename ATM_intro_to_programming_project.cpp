
////(ALERT) ON SOME VERSION THERE WILL BE COMPILATION ERROR
/*
Press Alt-F7 or right click in solution explorer and select "Properties"

Configurations:All Configurations

Click on the Preprocessor Definitions line to invoke its editor

Choose Edit...

Copy "_CRT_SECURE_NO_WARNINGS" into the Preprocessor Definitions white box on the top.

*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

#include <time.h>
//time.h is a library used to get the date of the day to implement (maximum deposit per day ) task

#include<string.h>
// a function contain strcmp and strcpy functions

#include<stdlib.h>
// function that contain atoi function which convert string to int ;


/// <summary>
/*
Atm App (group 2)-->(Abdelrahman Hamdy),(Marawan Tarek),(Hussien Badie))
App is divided into  2 sections
first cardless seriveces
the user enter the credintials written in (Wallet) file in the program file ,you can deposit , withdraw,transfer from the card(there must be a card first);

Second
Card services
it is like registration system
you have first to activate  the card before dealing with it so it is stored in the database file
you can deposit,withdraw,dontate to charities,paying bills,take a loan and so on .
paying bills requre ID which is written in paying bills file in the program folder
in card services you cannot deposit more than 6000 per day
*/


//struct for the cardservices user explained in power point
struct UserData
{
	int ID;
	char userCardID[17];
	char userPassword[5];
	int moneyInTheBank;
	int moneyOnLoan;
	int moneyDepositedToday;
	int lastDayDeposited[2];
	char userName[200];
	char bankName[200];
};

//struct for wallet user explained in power point
struct UserDataWallet
{
	int ID;
	char userCardID[17];
	char userPassword[5];
	int moneyInTheBank;
};

const int SIZE_OF_WALLET = 4;


///prototypes of all functions used in the program 
int checkRelationBewteenPasswordAndCardNumber(struct UserData data[], char cardNumber[], char password[], int size);
int checkRelationBewteenPasswordAndCardNumberWallet(struct UserDataWallet data[], char cardNumber[], char password[], int size);
int  alreadyEntered(char cardId[], struct UserData arr[], int size);
int readNumberOfUsers();
void writeNumberOfUser(int id);
void writeFile(struct UserData userData, int id, struct UserData data[]);
void readFromTheFile(struct UserData s[], int num);
void newUserRegister(struct UserData arr[], int id);
void oldUser(struct UserData arr[], int size);
int withdrawMoney(int id, struct UserData arr[], int flag);
int withdrawMoneyFromWallet(int id, struct UserDataWallet arr[]);
void updateFile(struct UserData data[], int size);
void depositMoney(int id, struct UserData arr[]);
void depositMoneyToWallet(int id, struct UserDataWallet arr[]);
void bankStatement(int id, struct UserData arr[]);
void donate(int id, struct UserData arr[]);
void payBills(int id, struct UserData arr[]);
void wantToTakeLoan(int id, struct UserData arr[]);
void payOffLoanInstallment(int id, struct UserData arr[]);
void askForTheReceipt(int id, struct UserData arr[], int op, int money);
void askForTheReceiptWallet(int id, struct UserDataWallet arrWallet[], int op, int money);
int readFromBillsFile(int idOfBill);
void writeToTheBills();
void readFromTheWallet(struct UserDataWallet arr[]);
void updateFileWallet(struct UserDataWallet data[]);
void depositFromCard(int id, struct UserDataWallet arrWallet[], int size, struct UserData arr[]);
void writeToTheWallet();

int main() {

	///checking user input whether he has a card or not 
	char firstChoiceAtAll[50];
	writeToTheWallet();
	writeToTheBills();
	do {

		printf("for cardless service press 1 for operation with card press 2\n");
		gets(firstChoiceAtAll);

		//strcmp function return 0 when the 2 strings are equal
		if (!((strcmp(firstChoiceAtAll, "1") == 0) || strcmp(firstChoiceAtAll, "2") == 0)) {

			printf("please enter valid answer\n");

		}

	} while (strcmp(firstChoiceAtAll, "1") != 0 && strcmp(firstChoiceAtAll, "2") != 0);


	int size = 0;
	int readNumberOfUser = readNumberOfUsers();
	struct UserData arr[150];
	if (readNumberOfUser) {
		/// reading number of users in the database to implement for loop properly 
		size = readNumberOfUser;
		readFromTheFile(arr, size);

	}

	/// checking if he has already activated the 
	char choiceOfBeingNewUserOrNot[30];
	if (strcmp(firstChoiceAtAll, "1") == 0) {
		struct UserDataWallet arrWallet[50];
		readFromTheWallet(arrWallet);

		char number[40];
		char password[40];


		printf("Please Enter your wallet number \n");
		//gets function get the whole line not like scanf 
		gets(number);

		do {

			if (!alreadyEnteredWallet(number, arrWallet, SIZE_OF_WALLET))
			{

				printf("Please Enter a valid wallet number\n");
				gets(number);

			}
		} while (!alreadyEnteredWallet(number, arrWallet, SIZE_OF_WALLET));



		do {
			printf("Please Enter your Password\n");

			gets(password);
			if (!(checkRelationBewteenPasswordAndCardNumberWallet(arrWallet, number, password, SIZE_OF_WALLET) + 1)) {

				printf("Password is wrong\ntry again \n");

			}

		} while (!(checkRelationBewteenPasswordAndCardNumberWallet(arrWallet, number, password, SIZE_OF_WALLET) + 1));


		printf("\n----------------------------\n");

		printf("Welcome our user");
		char choice = 'y';

		char oldUserChoice = '0';
		do {
			//asking user options
			printf("\nWhat do you want to do?\n");
			printf("----------------------------\n");
			printf("\n1)WithdrawMoney\n2)deposit money\n3)deposit from the card\n");

			printf("----------------------------\n");
			scanf(" %c", &oldUserChoice);
			if (getchar() == '\n') {
				switch (oldUserChoice)
				{


				case '1':
					withdrawMoneyFromWallet(checkRelationBewteenPasswordAndCardNumberWallet(arrWallet, number, password, SIZE_OF_WALLET), arrWallet);
					oldUserChoice = 't';

					break;

				case '2':
					depositMoneyToWallet(checkRelationBewteenPasswordAndCardNumberWallet(arrWallet, number, password, SIZE_OF_WALLET), arrWallet);
					oldUserChoice = 't';

					break;

				case '3':
					depositFromCard(checkRelationBewteenPasswordAndCardNumberWallet(arrWallet, number, password, SIZE_OF_WALLET), arrWallet, size, arr);
					oldUserChoice = 't';

					break;

				default:
					printf("please enter a number from those shown\n");
					oldUserChoice = 'f';

				}


				choice = '0';
				while (choice != 'y' && choice != 'n' && oldUserChoice != 'f')
				{

					printf("Do you want to do some thing else 'y' or 'n' \n");

					scanf(" %c", &choice);

				}
			}
			else {
				while (getchar() != '\n');

				printf("please enter a number from those shown\n");
				oldUserChoice = 'f';


			}

		} while (choice == 'y' || oldUserChoice != 't');
	}

	else {

		char c = 'f';
		do {
			// second option
			printf("If you want to activate your card press 1,if you have already activated press 2\n");
			gets(choiceOfBeingNewUserOrNot);

			if (strcmp(choiceOfBeingNewUserOrNot, "1") == 0) {

				c = 't';
				newUserRegister(arr, size);
			}
			else {
				if (strcmp(choiceOfBeingNewUserOrNot, "2") == 0) {
					c = 't';
					oldUser(arr, size);
				}
				else {
					printf("Please Enter from 1 and 2\n");
					c = 'f';
				}
			}
		} while (c != 't');
	}
}
///////////////////////////////////////////////////
//A function to check if the password is correct for this card number or not 
//////////////////////////////////////////////////
int checkRelationBewteenPasswordAndCardNumber(struct UserData data[], char cardNumber[], char password[], int size) {

	for (int i = 0; i < size; i++) {

		if (strcmp(cardNumber, data[i].userCardID) == 0 && strcmp(password, data[i].userPassword) == 0) {
			return data[i].ID;

		}

	}
	return -1;

}

//A function to check if the password is correct for this card number or not 
int checkRelationBewteenPasswordAndCardNumberWallet(struct UserDataWallet data[], char cardNumber[], char password[], int size)
{

	for (int i = 0; i < size; i++) {

		if (strcmp(cardNumber, data[i].userCardID) == 0 && strcmp(password, data[i].userPassword) == 0) {
			return data[i].ID;

		}

	}
	return -1;


}

///////////////////////////////////////////////////

//we write the new number of user to the database whenever a new user register to implement for loop properly 
void writeNumberOfUser(int id) {

	//writing number of users to a  file after every activation to handle the for loop properly
	FILE* out_file;

	out_file = fopen("number_of_users", "w"); //append to the file

	fprintf(out_file, "%d", id + 1);

}

//////////////////////////////////////////////////

// it is just the anti operation of the function above 
int readNumberOfUsers() {

	//reading number of users to handle the for loop properly when reading the users data
	FILE* out_file;

	out_file = fopen("number_of_users", "r"); //append to the file

	int numberOfUsers;
	if (out_file == NULL) {
		return 0;
	}
	fscanf(out_file, "%d", &numberOfUsers);

	return numberOfUsers;
}

///////////////////////////////////////////////////
// here we write the data of the new user him self when some one register 
void writeFile(struct UserData userData, int id, struct UserData data[]) {


	FILE* out_file;
	data[id] = userData;

	out_file = fopen("data_base_file", "a"); //append to the file

	fprintf(out_file, "%d", userData.ID);
	fputs(" ", out_file);
	fputs(userData.userName, out_file);
	fputs(" ", out_file);
	fputs(userData.bankName, out_file);
	fputs(" ", out_file);
	fputs(userData.userCardID, out_file);
	fputs(" ", out_file);
	fputs(userData.userPassword, out_file);
	fputs(" ", out_file);
	fprintf(out_file, "%d ", userData.moneyInTheBank);
	fprintf(out_file, "%d", userData.moneyOnLoan);
	fputs(" ", out_file);
	fprintf(out_file, "%d", userData.moneyDepositedToday);
	fputs(" ", out_file);
	fprintf(out_file, "%d ", userData.lastDayDeposited[0]);
	fprintf(out_file, "%d\n", userData.lastDayDeposited[1]);
	fclose(out_file);


	writeNumberOfUser(id);
}

///////////////////////////////////////////////////
//the anti function of the above one 
void readFromTheFile(struct UserData s[], int size) {

	//reading from the database file
	int   id, money, loan, moneyDepositedDay;
	char  cardNumber[17];
	char  cardPassword[5];
	int arrOfDate[2];
	char userName[20];
	char bankName[10];

	FILE* in_file;


	in_file = fopen("data_base_file", "r"); // read only 

	for (int i = 0; i < size; i++) {
		fscanf(in_file, "%d %s %s %s %s %d %d %d %d %d", &id, &userName, &bankName, &cardNumber, &cardPassword, &money, &loan, &moneyDepositedDay, &arrOfDate[0], &arrOfDate[1]);
		struct UserData u;
		u.ID = id;
		u.moneyInTheBank = money;
		u.moneyOnLoan = loan;
		u.lastDayDeposited[0] = arrOfDate[0];
		u.lastDayDeposited[1] = arrOfDate[1];
		u.moneyDepositedToday = moneyDepositedDay;
		strcpy(u.userPassword, cardPassword);
		strcpy(u.userName, userName);
		strcpy(u.bankName, bankName);
		strcpy(u.userCardID, cardNumber);
		s[i] = u;
	}

}

///////////////////////////////////////////////////
//here we check when the user want to activate the card but he has already activated it 
int  alreadyEntered(char cardId[], struct UserData arr[], int size) {

	// check if he has already activiated this wallet before or not
	for (int i = 0; i < size; i++) {
		if (strcmp(cardId, arr[i].userCardID) == 0)
		{
			return 1;
		}

	}

	return 0;
}
//the same but for the wallet
int  alreadyEnteredWallet(char cardId[], struct UserDataWallet arr[], int size) {


	for (int i = 0; i < size; i++) {

		if (strcmp(cardId, arr[i].userCardID) == 0) {

			return 1;

		}

	}

	return 0;
}

///////////////////////////////////////////////////
// asking the new user who want to activate the card for the card number and password
void newUserRegister(struct UserData arr[], int id) {


	char bankName[18];
	char userName[180];
	char number[30];
	char password[100];


	printf("Please enter your card number\n");


	gets(number);

	while (number[16] != '\0' || alreadyEntered(number, arr, id)) {

		printf("Please enter a valid card ID\nor you have already activated your card\nnote:The Card number is 16 digits\n");

		number[16] = 'n';
		gets(number);
	}

	if (number[0] == '1') {

		strcpy(bankName, "CIB");
	}
	else {
		if (number[0] == '2') {
			strcpy(bankName, "QNB");
		}
		else {
			strcpy(bankName, "AlAhly");
		}
	}

	printf("Please enter a 4 digits card password\n");

	gets(password);

	while (password[4] != '\0') {

		printf("Please enter a 4 digits card password\n");

		gets(password);

	}
	printf("Please Enter Your name \n");
	scanf("%s", &userName);

	printf("\aThank you for joining us!\n");
	struct UserData user;
	user.ID = id;
	strcpy(user.userCardID, number);
	user.moneyInTheBank = 0;
	strcpy(user.userName, userName);
	user.moneyOnLoan = 0;
	user.moneyDepositedToday = 0;
	user.lastDayDeposited[0] = -1;
	user.lastDayDeposited[1] = -1;
	strcpy(user.bankName, bankName);
	strcpy(user.userPassword, password);
	writeFile(user, id, arr);

};


///////////////////////////////////////////////////

// checking the data of the old user 
void oldUser(struct UserData arr[], int size) {

	char number[30];
	char password[30];



	printf("Please Enter your card Number\n");
	gets(number);

	do {
		if (number[16] != '\0' || !alreadyEntered(number, arr, size))
		{


			printf("Please Enter a valid Card Number\n");
			gets(number);

		}
	} while (!alreadyEntered(number, arr, size));


	printf("Please Enter your Password\n");
	gets(password);


	do {

		if (!(checkRelationBewteenPasswordAndCardNumber(arr, number, password, size) + 1)) {

			printf("Password is wrong\ntry again\n");
			gets(password);

		}

	} while (!(checkRelationBewteenPasswordAndCardNumber(arr, number, password, size) + 1));




	printf("\n----------------------------\n");
	int isTemp = checkRelationBewteenPasswordAndCardNumber(arr, number, password, size);
	printf("Welcome %s\n", arr[isTemp].userName);
	printf("\n----------------------------\n");
	printf("Bank %s \n", arr[isTemp].bankName);



	char choice = 'f';
	char oldUserChoice = '0';

	do {

		printf("\nWhat do you want to do?\n");
		printf("----------------------------\n");
		printf("\n1)WithdrawMoney\n2)deposit money\n3)pay Off Loan installment \n4)pay bills \n5)donate to charities\n6)take a loan \n7)show account statment\n");

		printf("----------------------------\n");

		scanf(" %c", &oldUserChoice);

		if (getchar() == '\n') {

			switch (oldUserChoice)
			{
			case '1':
				withdrawMoney(checkRelationBewteenPasswordAndCardNumber(arr, number, password, size), arr, 2);
				oldUserChoice = 't';
				break;

			case '2':
				depositMoney(checkRelationBewteenPasswordAndCardNumber(arr, number, password, size), arr);
				oldUserChoice = 't';
				break;

			case '3':
				payOffLoanInstallment(checkRelationBewteenPasswordAndCardNumber(arr, number, password, size), arr);
				oldUserChoice = 't';
				break;

			case '4':
				payBills(checkRelationBewteenPasswordAndCardNumber(arr, number, password, size), arr);
				oldUserChoice = 't';
				break;
			case '5':
				donate(checkRelationBewteenPasswordAndCardNumber(arr, number, password, size), arr);
				oldUserChoice = 't';
				break;
			case'6':
				wantToTakeLoan(checkRelationBewteenPasswordAndCardNumber(arr, number, password, size), arr);
				oldUserChoice = 't';
				break;
			case '7':
				bankStatement(checkRelationBewteenPasswordAndCardNumber(arr, number, password, size), arr);
				oldUserChoice = 't';
				break;
			default:
				printf("please enter a number from those shown\n");
				oldUserChoice = 'f';
			}


			choice = '0';
			while (choice != 'y' && choice != 'n' && oldUserChoice != 'f') {
				printf("Do you want to do some thing else 'y' or 'n' \n");

				scanf(" %c", &choice);

			}

		}
		else {


			printf("please enter a number from those shown\n");
			oldUserChoice = 'f';
			while (getchar() != '\n');
		}



	} while (choice == 'y' || oldUserChoice != 't');

}

///////////////////////////////////////////////////

///function that withdraw money then it remove this money from the user's account and write that to the database 
int withdrawMoney(int id, struct UserData arr[], int flag) {
	int amountOfMoneyHeWant = 0;
	char  amountOfMoneyHeWantAsChar[50];
	while (amountOfMoneyHeWant == 0) {
		printf("How much you want to withdraw?\n");
		gets(amountOfMoneyHeWantAsChar);
		//atoi function convert the string to int and if the string cannot be converted it returns 0 ;
		amountOfMoneyHeWant = atoi(amountOfMoneyHeWantAsChar);
		if (amountOfMoneyHeWant == 0) {
			printf("Please enter valid number\n");

		}
	}

	if (arr[id].moneyInTheBank > amountOfMoneyHeWant) {

		arr[id].moneyInTheBank -= amountOfMoneyHeWant;

		updateFile(arr, id);

		if (flag == 2) {
			printf("you have withdrawed money succefully\n");

			askForTheReceipt(id, arr, 1, amountOfMoneyHeWant);
		}
		return amountOfMoneyHeWant;
	}
	else {

		printf("Sorry you don't have enough money\n");
		return 0;

	}

}

//withdrawing money from the wallet function 
int withdrawMoneyFromWallet(int id, struct UserDataWallet arrWallet[])
{
	int amountOfMoneyHeWant = 0;
	char  amountOfMoneyHeWantAsChar[50];
	while (amountOfMoneyHeWant == 0) {
		printf("How much you want to withdraw?\n");
		gets(amountOfMoneyHeWantAsChar);
		amountOfMoneyHeWant = atoi(amountOfMoneyHeWantAsChar);
		if (amountOfMoneyHeWant == 0) {
			printf("Please enter valid number\n");

		}
	}





	if (arrWallet[id].moneyInTheBank > amountOfMoneyHeWant) {

		arrWallet[id].moneyInTheBank -= amountOfMoneyHeWant;

		updateFileWallet(arrWallet);


		printf("you have withdrawed money succefully\n");


		askForTheReceiptWallet(id, arrWallet, 1, amountOfMoneyHeWant);
		return amountOfMoneyHeWant;

	}
	else {

		printf("Sorry you don't have enough money\n");
		return 0;

	}


}

///////////////////////////////////////////////////
/// a function called after each transaction for the old user to change his balance or loan 
void updateFile(struct UserData data[], int size) {



	FILE* out_file = fopen("data_base_file", "w"); //write to a file
	size = readNumberOfUsers();



	for (int i = 0; i < size; i++) {


		fprintf(out_file, "%d", data[i].ID);
		fputs(" ", out_file);
		fputs(data[i].userName, out_file);
		fputs(" ", out_file);
		fputs(data[i].bankName, out_file);
		fputs(" ", out_file);
		fputs(data[i].userCardID, out_file);
		fputs(" ", out_file);
		fputs(data[i].userPassword, out_file);
		fputs(" ", out_file);
		fprintf(out_file, "%d ", data[i].moneyInTheBank);
		fprintf(out_file, "%d", data[i].moneyOnLoan);
		fputs(" ", out_file);
		fprintf(out_file, "%d", data[i].moneyDepositedToday);
		fputs(" ", out_file);
		fprintf(out_file, "%d ", data[i].lastDayDeposited[0]);
		fprintf(out_file, "%d\n", data[i].lastDayDeposited[1]);
	}
	fclose(out_file);

}

///////////////////////////////////////////////////
///function that deposit money then it add this money to the user's account and write that to the database 
void depositMoney(int id, struct UserData arr[]) {

	if (checkIfHeCanDepositToday(id, arr, 0)) {

		int amountOfMoneyHeWant;

		int category = 0;
		char categoryAsChar[40];

		int numberOfPapers = 0;
		char numberOfPapesAsChar[40];
		while (category == 0) {
			printf("what is the category of the card?\n");
			gets(categoryAsChar);
			category = atoi(categoryAsChar);
			if (category == 0) {
				printf("please enter valid category\n");

			}
		}

		while (numberOfPapers == 0) {
			printf("what is the number of papers?\n");
			gets(numberOfPapesAsChar);
			numberOfPapers = atoi(numberOfPapesAsChar);
			if (numberOfPapers == 0) {

				printf("please enter a valid number\n");

			}


		}

		amountOfMoneyHeWant = category * numberOfPapers;

		if (checkIfHeCanDepositToday(id, arr, amountOfMoneyHeWant)) {


			arr[id].moneyInTheBank += amountOfMoneyHeWant;

			updateFile(arr, id);

			printf("you deposited successfully\n");


			askForTheReceipt(id, arr, 2, amountOfMoneyHeWant);
		}
		else {

			printf("sorry but you are only allowed to deposit maximum of 6000 per day\n and you have already deposited %d \nand you want to deposit %d\n", arr[id].moneyDepositedToday, amountOfMoneyHeWant);

		}
	}
	else {

	}


}

void depositMoneyToWallet(int id, struct  UserDataWallet arrWallet[])
{


	char amountOfMoneyHeWantChar[40];
	int amountOfMoneyHeWant = 0;
	while (amountOfMoneyHeWant == 0) {
		printf("How much money you want to deposit?\n");
		gets(amountOfMoneyHeWantChar);
		amountOfMoneyHeWant = atoi(amountOfMoneyHeWantChar);
		if (amountOfMoneyHeWant == 0) {
			printf("please enter valid answer\n");

		}
	}



	arrWallet[id].moneyInTheBank += amountOfMoneyHeWant;

	updateFileWallet(arrWallet);

	printf("you deposited successfully\n");



	askForTheReceiptWallet(id, arrWallet, 2, amountOfMoneyHeWant);


}

// this function is used when I tranfer money from the card to wallet
depositMoneyDirectlyToWallet(int id, struct  UserDataWallet arrWallet[], int money) {



	arrWallet[id].moneyInTheBank += money;

	updateFileWallet(arrWallet);

	printf("you deposited successfully to your wallet succefully\n");

	askForTheReceiptWallet(id, arrWallet, 3, money);

}

///////////////////////////////////////////////////
//  it gives quick information about the user
void bankStatement(int id, struct UserData arr[])
{

	printf("your id is %d \nyour card ID: %s \nyour money is %d \nyour loan is %d \n", arr[id].ID, arr[id].userCardID, arr[id].moneyInTheBank
		, arr[id].moneyOnLoan);


}

void bankStatementWallet(int id, struct UserDataWallet arr[])
{

	printf("your id is %d \nyour card ID: %s \nyour money is %d \n", arr[id].ID, arr[id].userCardID, arr[id].moneyInTheBank);


}

///////////////////////////////////////////////////

///function that donate money then it remove this money from the user's account and write that to the database 
void donate(int id, struct UserData arr[])
{

	char amountOfMoneyHeWantChar[40];
	int amountOfMoneyHeWant = 0;
	while (amountOfMoneyHeWant == 0) {
		printf("how much do you want to donate to charities\n");
		gets(amountOfMoneyHeWantChar);
		amountOfMoneyHeWant = atoi(amountOfMoneyHeWantChar);
		if (amountOfMoneyHeWant == 0) {
			printf("please enter valid answer");

		}

	}




	if (arr[id].moneyInTheBank > amountOfMoneyHeWant) {

		arr[id].moneyInTheBank -= amountOfMoneyHeWant;
		updateFile(arr, id);
		printf("you donated successfully\n");
		askForTheReceipt(id, arr, 3, amountOfMoneyHeWant);
	}

	else {
		printf("Sorry you don't have enough money\n");
	}

}

///////////////////////////////////////////////////
///function that pay bills by a transaction id wrote in the data base . Each id has a certain fee 
void payBills(int id, struct UserData arr[])
{
	int amountOfMoneyOfBill = 0;

	do {

		int idOfTheBill = 0;
		char idOfTheBillChar[40];
		while (idOfTheBill == 0) {
			printf("Please Enter The Bill ID\n");
			gets(idOfTheBillChar);
			idOfTheBill = atoi(idOfTheBillChar);
		}
		amountOfMoneyOfBill = readFromBillsFile(idOfTheBill);
	} while (!amountOfMoneyOfBill);
	printf("it is a %d pounds bill\n", amountOfMoneyOfBill);

	if (arr[id].moneyInTheBank > amountOfMoneyOfBill) {

		arr[id].moneyInTheBank -= amountOfMoneyOfBill;
		updateFile(arr, id);
		printf("you payed the bill successfully\n");
		askForTheReceipt(id, arr, 4, amountOfMoneyOfBill);
	}
	else {
		printf("Sorry you don't have enough money\n");
	}

}

///////////////////////////////////////////////////
// function that loan the user money as  it deposit the entered money to user's account but it loan him for this amount 
void wantToTakeLoan(int id, struct UserData arr[])
{
	int amountOfMoneyHeWantToLoan = 0;
	char amountOfMoneyHeWantToLoanChar[40];

	while (amountOfMoneyHeWantToLoan == 0) {
		printf("How much money you want to loan?\n");
		gets(amountOfMoneyHeWantToLoanChar);
		amountOfMoneyHeWantToLoan = atoi(amountOfMoneyHeWantToLoanChar);
		if (amountOfMoneyHeWantToLoan == 0) {
			printf("please enter a valid number\n");

		}
	}
	arr[id].moneyOnLoan += amountOfMoneyHeWantToLoan;
	arr[id].moneyInTheBank += amountOfMoneyHeWantToLoan;
	updateFile(arr, id);
	printf("you have a loan of %d\n", amountOfMoneyHeWantToLoan);
	askForTheReceipt(id, arr, 5, amountOfMoneyHeWantToLoan);

}

///////////////////////////////////////////////////

// function that is used to pay the loan or part from the loan 
void payOffLoanInstallment(int id, struct UserData arr[]) {

	int amountOfMoneyHeWantToPay = 0;
	char amountOfMoneyHeWantToPayChar[40];
	while (amountOfMoneyHeWantToPay == 0)
	{
		printf("How much do you want to pay to the loan from your money \n");
		gets(amountOfMoneyHeWantToPayChar);
		amountOfMoneyHeWantToPay = atoi(amountOfMoneyHeWantToPayChar);
		if (amountOfMoneyHeWantToPay == 0) {
			printf("Please enter a valid number \n");

		}

	}



	if (amountOfMoneyHeWantToPay > arr[id].moneyInTheBank) {

		printf("sorry you don't have enough money \n");

	}
	else {

		// if he want to pay more tha the loan 
		if (amountOfMoneyHeWantToPay > arr[id].moneyOnLoan) {

			printf("you just have a loan of %d \n", arr[id].moneyOnLoan);
		}
		else {
			arr[id].moneyInTheBank -= amountOfMoneyHeWantToPay;
			arr[id].moneyOnLoan -= amountOfMoneyHeWantToPay;
			updateFile(arr, id);
			printf("you payed a loan installment successfully \n");
			askForTheReceipt(id, arr, 6, amountOfMoneyHeWantToPay);

		}
	}



}
/// we are asking for the reciept after each transaction except showing bank statment
void askForTheReceipt(int id, struct UserData arr[], int op, int money) {

	char askForReceipt;
	printf("if you want recipt press 1 if not press 2 \n");
	scanf(" %c", &askForReceipt);
	while (askForReceipt != '1' && askForReceipt != '2') {

		printf("please enter a valid choice 1 or 2 ");

		scanf(" %c", &askForReceipt);


	}
	if (askForReceipt == '1') {
		printf("\n--------------------------\n");
		switch (op)
		{
		case 1:
			printf("you have just withdrawed %d\n", money);
			break;
		case 2:
			printf("you have just deposited %d\n", money);
			break;
		case 3:
			printf("you have just donated %d\n", money);
			break;
		case 4:
			printf("you have just payed bills for %d\n", money);
			break;
		case 5:
			printf("you have just took a loan of  %d\n", money);
			break;
		case 6:
			printf("you have just payed a loan of %d\n", money);
			break;

		}

		bankStatement(id, arr);


		printf("\n--------------------------\n");

	}
}

void askForTheReceiptWallet(int id, struct UserDataWallet arrWallet[], int op, int money) {


	char askForReceipt;
	printf("if you want recipt press 1 if not press 2 \n");
	scanf(" %c", &askForReceipt);
	while (askForReceipt != '1' && askForReceipt != '2') {

		printf("please enter a valid choice 1 or 2 ");

		scanf(" %c", &askForReceipt);


	}
	if (askForReceipt == '1') {
		printf("\n--------------------------\n");
		switch (op)
		{
		case 1:
			printf("you have just withdrawed %d\n", money);
			break;
		case 2:
			printf("you have just deposited %d\n", money);
			break;
		case 3:
			printf("you have just transferd %d from the card\n", money);
			break;
		}


		bankStatementWallet(id, arrWallet);
		printf("\n--------------------------\n");

	}
}

// we read from bills file (notepad file)as it contains the ids with the price of each transaction 
int readFromBillsFile(int idOfBill) {
	FILE* on_file = fopen("Bills_file.txt", "r"); // read only 
	int isItFound = 0;
	if (on_file == NULL) {

		writeToTheBills();

	}


	FILE* in_file = fopen("Bills_file.txt", "r"); // read only 
	for (int i = 0; i < 3; i++) {

		fscanf(in_file, "%d", &isItFound);
		if (isItFound != idOfBill) {

			fscanf(in_file, "%d", &isItFound);
			isItFound = 0;
		}
		else {

			fscanf(in_file, "%d", &isItFound);
			break;
		}


	}
	fclose(in_file);
	if (!isItFound) {

		printf("Please Enter a valid ID\n");
	}




	return isItFound;
}
/// function that get the date of the day (used to check maximum deposit)
void getDate(int date[]) {

	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	date[0] = tm.tm_mon;
	date[1] = tm.tm_mday;

}
//check maximum deposit per day which is 6000 in the CARD
int checkIfHeCanDepositToday(int id, struct UserData arr[], int money) {
	int arrDate[2];
	getDate(arrDate);
	if (arr[id].lastDayDeposited[0] == arrDate[0] && arr[id].lastDayDeposited[1] == arrDate[1]) {


		if (arr[id].moneyDepositedToday + money > 6000) {

			return 0;

		}
		else {
			arr[id].moneyDepositedToday += money;
			return 1;
		}

	}
	else {
		arr[id].lastDayDeposited[0] = arrDate[0];
		arr[id].lastDayDeposited[1] = arrDate[1];
		arr[id].moneyDepositedToday = money;
		return 1;
	}
}


//for the first time the program run if  there is no bills file we create it;
void writeToTheBills() {
	FILE* on_file = fopen("Bills_file.txt", "r"); // read only 

	int isItFound = 0;
	if (on_file != NULL) {
		fclose(on_file);
		return;

	}



	FILE* out_file = fopen("Bills_file.txt", "a"); //append to the file

	fputs("300 500\n", out_file);
	fputs("301 600\n", out_file);
	fputs("302 700\n", out_file);

	fclose(out_file);
}

void updateFileWallet(struct UserDataWallet data[])
{

	//write to a file
	FILE* out_file = fopen("Wallet.txt", "w");
	for (int i = 0; i < SIZE_OF_WALLET; i++) {
		fprintf(out_file, "%d", data[i].ID);
		fputs(" ", out_file);
		fputs(data[i].userCardID, out_file);
		fputs(" ", out_file);
		fputs(data[i].userPassword, out_file);
		fputs(" ", out_file);
		fprintf(out_file, "%d\n", data[i].moneyInTheBank);
	}
	fclose(out_file);


}



void readFromTheWallet(struct UserDataWallet arrW[])
{



	int   id, money, loan, moneyDepositedDay;
	char  userName[20];
	char  cardPassword[5];
	int arrOfDate[2];


	FILE* in_file = fopen("Wallet.txt", "r"); // read only 
	if (in_file == NULL) {

		writeToTheWallet();
	}
	FILE* in_file2 = fopen("Wallet.txt", "r");

	for (int i = 0; i < SIZE_OF_WALLET; i++) {
		fscanf(in_file2, "%d %s %s %d ", &id, &userName, &cardPassword, &money);
		struct UserDataWallet u;
		u.ID = id;
		u.moneyInTheBank = money;
		strcpy(u.userPassword, cardPassword);
		strcpy(u.userCardID, userName);
		arrW[i] = u;
	}
	fclose(in_file2);
}


void depositFromCard(int id, struct UserDataWallet arrWallet[], int size, struct UserData arr[]) {

	char number[40];
	char password[40];



	printf("Please Enter your card Number\n");
	gets(number);
	do {
		if (number[16] != '\0' || !alreadyEntered(number, arr, size)) {

			printf("Please Enter a valid Card Number\n");
			gets(number);
		}

	} while (!alreadyEntered(number, arr, size));

	do {

		printf("Please Enter your Password\n");
		gets(password);

		if (!(checkRelationBewteenPasswordAndCardNumber(arr, number, password, size) + 1)) {
			printf("Password is wrong\ntry again \n");

		}

	} while (!(checkRelationBewteenPasswordAndCardNumber(arr, number, password, size) + 1));

	int withdraw = withdrawMoney(checkRelationBewteenPasswordAndCardNumber(arr, number, password, size), arr, 1);
	if (withdraw) {
		depositMoneyDirectlyToWallet(id, arrWallet, withdraw);
	}
}



//first time the program run if there is no wallet file we create it ;
void writeToTheWallet() {

	FILE* in_file = fopen("Wallet.txt", "r"); // read only 
	if (in_file != NULL) {
		return;

	}

	FILE* out_file = fopen("Wallet.txt", "a"); //append to the file

	fputs("0 789789789 1234 0\n", out_file);
	fputs("1 235235235 2468 0\n", out_file);
	fputs("2 452452452 1357 0\n", out_file);
	fputs("3 268267268 8642 0\n", out_file);

	fclose(out_file);
}