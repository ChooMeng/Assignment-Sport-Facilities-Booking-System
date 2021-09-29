#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<windows.h>
#include "Main.h"
#pragma warning (disable : 4996)
#pragma warning (disable : 6031)

/*
===========================
User Information Module
Made by: William Choong
===========================
*/
void userMenu()
{
	int choices;
	do
	{
		printf("=======================\n");
		printf("*                     *\n");
		printf("USER Information Module\n");
		printf("*                     *\n");
		printf("=======================\n");
		printf("1. Search user Information\n2. Add user Information\n3. Modify user Information\n"
			"4. Delete user Information\n5. Display user Information\n\n");
		printf("Press 0 to back to main menu\n\nEnter the digit to continue... > ");
		scanf("%d", &choices);
		rewind(stdin);
		while (choices < -1 || choices > 5)
		{
			printf("\nInvalid digits plaease reenter again!!!		>	");
			scanf("%d", &choices);
			rewind(stdin);
		}

		switch (choices)
		{
		case 1: searchUI(); break;
		case 2: addUI(); break;
		case 3: modUI(); break;
		case 4: delUI(); break;
		case 5: dispUI(); break;
		}
	} while (choices != 0);

}

void searchUI()
{
	USER exist[50];
	int choices, i, counter = 0, error = 0, error2 = 0;
	int day, month, year;
	char ID[12], name[30], gender, IC[15], contactNumb[15];
	FILE* search = fopen("USER Information.bin", "rb");
	printf("\nSearching user information\n");
	if (search == NULL)
	{
		printf("\n\n<<Sorry, the file cannot open!!>>\n\n");
		exit(-1);
	}
	while (fread(&exist[counter], sizeof(exist[counter]), 1, search))
	{
		counter++;
	}
	printf("Search the user according to their\n1. ID\n2. Name\n3. Gender\n4. IC\n5. Contact Number\n6. Birth Date\n\n");
	printf("If you wish to return to the upper menu, please enter 0.\n");
	printf("Please enter your choices	>	");
	scanf("%d", &choices);
	rewind(stdin);
	while (choices < -1 || choices > 7)
	{
		printf("\nInvalid digits plaease reenter again!!!	>	");
		scanf("%d", &choices);
		rewind(stdin);
	}
	switch (choices)
	{
	case 1: {
		error = 0;
		printf("Please enter the ID > ");
		scanf("%s", &ID);
		rewind(stdin);
		printf("%-15s %-30s %-10s %-15s %-15s BIRTH DATE   REGISTRATION DATE \n", "ID", "NAME", "GENDER", "IC", "CONTACT NUMBER");
		for (i = 0; i < counter; i++)
		{
			if (strncmp(exist[i].ID, ID, 4) == 0)
			{
				printf("%-15s %-30s %-10c %-15s %-15s %02d/%02d/%d   %d/%02d/%02d %02d:%02d:%02d\n"
					, exist[i].ID, exist[i].name, toupper(exist[i].gender),
					exist[i].IC, exist[i].contactNumb,
					exist[i].birthDate.day, exist[i].birthDate.month, exist[i].birthDate.year,
					exist[i].registeredDate.year, exist[i].registeredDate.month, exist[i].registeredDate.day,
					exist[i].registeredTime.hour, exist[i].registeredTime.minute, exist[i].registeredTime.second);
				error = 1;
			}
			
		}
		if (error == 0) {
			printf("No Result found\n");
		}
		break;
	}
	case 2: {
		error = 0;
		printf("Please enter the name > ");
		scanf("%[^\n]", &name);
		rewind(stdin);
		printf("%-15s %-30s %-10s %-15s %-15s BIRTH DATE   REGISTRATION DATE \n", "ID", "NAME", "GENDER", "IC", "CONTACT NUMBER");
		for (i = 0; i < counter; i++)
		{
			
			if (strncmp(exist[i].name, name, 4) == 0)
			{

				printf("%-15s %-30s %-10c %-15s %-15s %02d/%02d/%d   %d/%02d/%02d %02d:%02d:%02d\n"
					, exist[i].ID, exist[i].name, toupper(exist[i].gender),
					exist[i].IC, exist[i].contactNumb,
					exist[i].birthDate.day, exist[i].birthDate.month, exist[i].birthDate.year,
					exist[i].registeredDate.year, exist[i].registeredDate.month, exist[i].registeredDate.day,
					exist[i].registeredTime.hour, exist[i].registeredTime.minute, exist[i].registeredTime.second);
				error = 1;
			}
		}
		if (error == 0) {
			printf("No Result found\n");
		}
		break;
	}
	case 3: {
		printf("Please enter the gender > ");
		scanf("%c", &gender);
		rewind(stdin);
		while (gender != 'F' && gender != 'f' && gender != 'M' && gender != 'm')
		{
			printf("Invalid character!!\nPlease reenter again > ");
			scanf("%c", &gender);
			rewind(stdin);
		}
		printf("%-15s %-30s %-10s %-15s %-15s BIRTH DATE REGISTRATION DATE \n", "ID", "NAME", "GENDER", "IC", "CONTACT NUMBER");
		for (i = 0; i < counter; i++)
		{
			if ((exist[i].gender == toupper(gender)))
			{
				printf("%-15s %-30s %-10c %-15s %-15s %02d/%02d/%d   %d/%02d/%02d %02d:%02d:%02d\n"
					, exist[i].ID, exist[i].name, toupper(exist[i].gender),
					exist[i].IC, exist[i].contactNumb,
					exist[i].birthDate.day, exist[i].birthDate.month, exist[i].birthDate.year,
					exist[i].registeredDate.year, exist[i].registeredDate.month, exist[i].registeredDate.day,
					exist[i].registeredTime.hour, exist[i].registeredTime.minute, exist[i].registeredTime.second);
				error = 1;
			}

		}
		if (error == 0) {
			printf("No Result found\n");
		}
		break;
	}
	case 4: {
		printf("Please enter the IC > ");
		scanf("%s", &IC);
		rewind(stdin);
		printf("%-15s %-30s %-10s %-15s %-15s BIRTH DATE REGISTRATION DATE \n", "ID", "NAME", "GENDER", "IC", "CONTACT NUMBER");
		for (i = 0; i < counter; i++)
		{
			if (strncmp(exist[i].IC, IC, 4) == 0)
			{
				printf("%-15s %-30s %-10c %-15s %-15s %02d/%02d/%d   %0d/%02d/%02d %02d:%02d:%02d\n"
					, exist[i].ID, exist[i].name, toupper(exist[i].gender),
					exist[i].IC, exist[i].contactNumb,
					exist[i].birthDate.day, exist[i].birthDate.month, exist[i].birthDate.year,
					exist[i].registeredDate.year, exist[i].registeredDate.month, exist[i].registeredDate.day,
					exist[i].registeredTime.hour, exist[i].registeredTime.minute, exist[i].registeredTime.second);
				error = 1;
			}

		}
		if (error == 0) {
			printf("No Result found\n");
		}
		break;
	}
	case 5: {	printf("Please enter the contact number > ");
		scanf("%s", &contactNumb);
		rewind(stdin);
		printf("%-15s %-30s %-10s %-15s %-15s BIRTH DATE REGISTRATION DATE \n", "ID", "NAME", "GENDER", "IC", "CONTACT NUMBER");
		for (i = 0; i < counter; i++)
		{
			if (strncmp(exist[i].contactNumb, contactNumb, 4) == 0)
			{

				printf("%-15s %-30s %-10c %-15s %-15s %02d/%02d/%d   %d/%02d/%02d %02d:%02d:%02d\n"
					, exist[i].ID, exist[i].name, toupper(exist[i].gender),
					exist[i].IC, exist[i].contactNumb,
					exist[i].birthDate.day, exist[i].birthDate.month, exist[i].birthDate.year,
					exist[i].registeredDate.year, exist[i].registeredDate.month, exist[i].registeredDate.day,
					exist[i].registeredTime.hour, exist[i].registeredTime.minute, exist[i].registeredTime.second);
				error = 1;
			}

		}
		if (error == 0) {
			printf("No Result found\n");
		}
		break;
	}
	case 6: {
		do {
			printf("Please enter the birth date > ");
			scanf("%d %d %d", &day, &month, &year);
			rewind(stdin);
			if (day < 1 || day > 31) {
				error2 = 1;
			}
			if (month < 1 || month > 12) {
				error2 = 1;
			}
			if (year < 1800 || day > 2200) {
				error2 = 1;
			}
			if (error2 == 1) {
				printf("Invalid Date");
			}
		} while (error2 == 1);
		printf("%-15s %-30s %-10s %-15s %-15s BIRTH DATE REGISTRATION DATE \n", "ID", "NAME", "GENDER", "IC", "CONTACT NUMBER");
		for (i = 0; i < counter; i++)
		{
			if (exist[i].birthDate.day == day)
			{
				if (exist[i].birthDate.month == month)
				{
					if (exist[i].birthDate.year == year)
					{
						printf("%-15s %-30s %-10c %-15s %-15s %02d/%02d/%d   %02d/%02d/%d %02d:%02d:%02d\n"
							, exist[i].ID, exist[i].name, toupper(exist[i].gender),
							exist[i].IC, exist[i].contactNumb,
							exist[i].birthDate.day, exist[i].birthDate.month, exist[i].birthDate.year,
							exist[i].registeredDate.year, exist[i].registeredDate.month, exist[i].registeredDate.day,
							exist[i].registeredTime.hour, exist[i].registeredTime.minute, exist[i].registeredTime.second);
						error = 1;
					}
				}
			}
		}
		if (error == 0) {
			printf("No Result found\n");
		}
		break; 
	}
	case 0: {return; break; }
	}
	rewind(stdin);
	fclose(search);
}

void addUI()
{
	SYSTEMTIME t;
	GetLocalTime(&t);
	USER addUSER;
	USER used[50];
	char confirm, again;
	int exist;
	int i = 0, counter = 0, error2 = 0;

	printf("\nAdding a new USER\n");

	FILE* reused = fopen("USER Information.bin", "rb");
	if (reused != NULL) {
		while (fread(&used[counter], sizeof(used[counter]), 1, reused) != 0) {
			counter++;
		}
	}

	do
	{
		FILE* add = fopen("USER Information.bin", "ab");
		if (add == NULL)
		{
			printf("\n\n<<Sorry, the file cannot open!!>>\n\n");
			exit(-1);
		}
		do {
			exist = 0;
			printf("\nEnter the USER ID > ");
			scanf("%s", &addUSER.ID);
			rewind(stdin);
			for (int i = 0; i < counter; i++)
			{
				if (strcmp(used[i].ID, addUSER.ID) == 0)
				{
					exist++;
					printf("\nError!!!\nThe ID you entered is already exist.\n");
				}
			}
			rewind(stdin);
		} while (exist == 1);
		do {
			exist = 0;
			printf("Enter the USER NAME > ");
			rewind(stdin);
			scanf("%[^\n]", &addUSER.name);
			for (int i = 0; i < counter; i++)
			{
				if (strcmp(used[i].name, addUSER.name) == 0)
				{
					exist++;
					printf("\nError!!!\nThe name you entered is already exist");
				}
			}
			rewind(stdin);
		} while (exist == 1);
		printf("Enter the USER's gender (F/M) > ");
		scanf("%c", &addUSER.gender);
		rewind(stdin);
		while (addUSER.gender != 'F' && addUSER.gender != 'f' && addUSER.gender != 'M' && addUSER.gender != 'm')
		{
			printf("Invalid character!!\nPlease reenter again > ");
			scanf("%c", &addUSER.gender);
			rewind(stdin);
		}
		do {
			exist = 0;
			printf("Enter the USER's IC > ");
			scanf("%s", &addUSER.IC);
			rewind(stdin);
			for (int i = 0; i < counter; i++)
			{
				if (strcmp(used[i].IC, addUSER.IC) == 0)
				{
					exist++;
					printf("\nError!!!\nThe IC you entered is already exist\n");
				}
			}
			rewind(stdin);
		} while (exist == 1);
		do {
			exist = 0;
			printf("Enter the USER's CONTACT NUMBER > ");
			scanf("%s", &addUSER.contactNumb);
			rewind(stdin);
			for (int i = 0; i < counter; i++)
			{
				if (strcmp(used[i].contactNumb, addUSER.contactNumb) == 0)
				{
					exist++;
					printf("\nError!!!\nThe contact number you entered is already exist\n");
				}
			}
		} while (exist == 1);
		do {
			printf("Enter your birth date (DD MM YYYY) > ");
			scanf("%d %d %d", &addUSER.birthDate.day, &addUSER.birthDate.month, &addUSER.birthDate.year);
			rewind(stdin);
			if (addUSER.birthDate.day < 1 || addUSER.birthDate.day > 31) {
				error2 = 1;
			}
			if (addUSER.birthDate.month < 1 || addUSER.birthDate.month > 12) {
				error2 = 1;
			}
			if (addUSER.birthDate.year < 1800 || addUSER.birthDate.day > 2200) {
				error2 = 1;
			}
			if (error2 == 1) {
				printf("Invalid Date\n");
			}
		} while (error2 == 1);
		
		printf("Are you sure you would like to add %s into the list? (Y/N)", addUSER.name);
		scanf("%c", &confirm);
		rewind(stdin);
		while (confirm != 'Y' && confirm != 'y' && confirm != 'N' && confirm != 'n')
		{
			printf("Invalid input!!\nPlease reenter again > ");
			scanf("%c", &confirm);
			rewind(stdin);
		}
		if (confirm == 'Y' || confirm == 'y')
		{
			addUSER.registeredDate.year = t.wYear;
			addUSER.registeredDate.month = t.wMonth;
			addUSER.registeredDate.day = t.wDay;
			addUSER.registeredTime.hour = t.wHour;
			addUSER.registeredTime.minute = t.wMinute;
			addUSER.registeredTime.second = t.wSecond;
			fwrite(&addUSER, sizeof(addUSER), 1, add);
			printf("The information of %s has been saved\n\n", addUSER.name);
			fclose(add);
		}
		else if (confirm == 'N' || confirm == 'n')
		{
			printf("The information of %s has not been added into the list.\n\n\n", addUSER.name);
		}
		printf("Would you like to continue to add a new user?? (Y/N) > ");
		scanf("%c", &again);
		rewind(stdin);
		while (again != 'Y' && again != 'y' && again != 'N' && again != 'n')
		{
			printf("Invalid input!!\nPlease reenter again > ");
			scanf("%c", &again);
			rewind(stdin);
		}
		if (again == 'N' || again == 'n')
		{
			printf("\nBack to the main page of the user information section\n\n");
			return;
			break;
		}
	} while (again == 'Y' || again == 'y');

}

void modUI()
{
	int choices;
	char ID[12], name[30], gender, IC[15], contactNumb[15];
	int day, month, year;
	int i = 0, counter = 0, error2 = 0, error = 0;
	USER mdf;
	USER exist[50];
	FILE* mod = fopen("USER Information.bin", "rb");
	printf("\nChanging for a existed USER information\n");
	printf("1. ID\n2.Name\n3.Gender\n4. IC\n5. Contact Number\n6. Birth Date\n\n");
	printf("Please enter the ways you want to search and change for the USER > ");
	scanf("%d", &choices);
	rewind(stdin);
	while (choices < -1 || choices > 6)
	{
		printf("Invalid choices!!\nPlease reenter yuor choices again from 1 to 5 : ");
		scanf("%d", &choices);
		rewind(stdin);
	}

	while (fread(&exist[counter], sizeof(exist[counter]), 1, mod)) {
		counter++;
	}

	switch (choices)
	{
	case 1: {
		printf("Please enter the ID > ");
		scanf("%s", &ID);
		rewind(stdin);
		printf("%-15s %-30s %-10s %-15s %-15s BIRTH DATE REGISTRATION DATE \n", "ID", "NAME", "GENDER", "IC", "CONTACT NUMBER");
		for (i = 0; i < counter; i++)
		{
			if (strcmp(exist[i].ID, ID) == 0)
			{
				printf("%-15s %-30s %-10c %-15s %-15s %02d/%02d/%d   %02d/%02d/%d %02d:%02d:%02d\n"
					, exist[i].ID, exist[i].name, toupper(exist[i].gender),
					exist[i].IC, exist[i].contactNumb,
					exist[i].birthDate.day, exist[i].birthDate.month, exist[i].birthDate.year,
					exist[i].registeredDate.year, exist[i].registeredDate.month, exist[i].registeredDate.day,
					exist[i].registeredTime.hour, exist[i].registeredTime.minute, exist[i].registeredTime.second);
				editingUI(choices, exist[i]);
				error = 1;
				break;
			}

		}
		if (error == 0) {
			printf("No Result found\n");
		}
		break;
	}
	case 2: {
		printf("Please enter the name > ");
		scanf("%[^\n]", &name);
		rewind(stdin);
		printf("%-15s %-30s %-10s %-15s %-15s BIRTH DATE REGISTRATION DATE \n", "ID", "NAME", "GENDER", "IC", "CONTACT NUMBER");
		for (i = 0; i < counter; i++)
		{
			
			if (strncmp(exist[i].name, name, 4) == 0)
			{

				
				printf("%-15s %-30s %-10c %-15s %-15s %02d/%02d/%d   %02d/%02d/%d %02d:%02d:%02d\n"
					, exist[i].ID, exist[i].name, toupper(exist[i].gender),
					exist[i].IC, exist[i].contactNumb,
					exist[i].birthDate.day, exist[i].birthDate.month, exist[i].birthDate.year,
					exist[i].registeredDate.year, exist[i].registeredDate.month, exist[i].registeredDate.day,
					exist[i].registeredTime.hour, exist[i].registeredTime.minute, exist[i].registeredTime.second);
				editingUI(choices, exist[i]);
				error = 1;
				break;
			}

		}
		if (error == 0) {
			printf("No Result found\n");
		}
		break;
	}
	case 3: {
		printf("Please enter the user's ID > ");
		scanf("%s", &ID);
		rewind(stdin);
		printf("%-15s %-30s %-10s %-15s %-15s BIRTH DATE REGISTRATION DATE \n", "ID", "NAME", "GENDER", "IC", "CONTACT NUMBER");
		for (i = 0; i < counter; i++)
		{
			if (strcmp(exist[i].ID, ID) == 0)
			{

				
				printf("%-15s %-30s %-10c %-15s %-15s %02d/%02d/%d   %02d/%02d/%d %02d:%02d:%02d\n"
					, exist[i].ID, exist[i].name, toupper(exist[i].gender),
					exist[i].IC, exist[i].contactNumb,
					exist[i].birthDate.day, exist[i].birthDate.month, exist[i].birthDate.year,
					exist[i].registeredDate.year, exist[i].registeredDate.month, exist[i].registeredDate.day,
					exist[i].registeredTime.hour, exist[i].registeredTime.minute, exist[i].registeredTime.second);
				editingUI(choices, exist[i]);
				error = 1;
				break;
			}

		}
		if (error == 0) {
			printf("No Result found\n");
		}
		break;
	}
	case 4: {
		printf("Please enter the IC > ");
		scanf("%s", &IC);
		rewind(stdin);
		printf("%-15s %-30s %-10s %-15s %-15s BIRTH DATE REGISTRATION DATE \n", "ID", "IC", "GENDER", "IC", "CONTACT NUMBER");
		for (i = 0; i < counter; i++)
		{
			if (strcmp(exist[i].IC, IC) == 0)
			{

				
				printf("%-15s %-30s %-10c %-15s %-15s %02d/%02d/%d   %02d/%02d/%d %02d:%02d:%02d\n"
					, exist[i].ID, exist[i].name, toupper(exist[i].gender),
					exist[i].IC, exist[i].contactNumb,
					exist[i].birthDate.day, exist[i].birthDate.month, exist[i].birthDate.year,
					exist[i].registeredDate.year, exist[i].registeredDate.month, exist[i].registeredDate.day,
					exist[i].registeredTime.hour, exist[i].registeredTime.minute, exist[i].registeredTime.second);
				editingUI(choices, exist[i]);
				error = 1;
				break;
			}

		}
		if (error == 0) {
			printf("No Result found\n");
		}
		break;
	}
	case 5: {
		printf("Please enter the contact number > ");
		scanf("%s", &contactNumb);
		rewind(stdin);
		printf("%-15s %-30s %-10s %-15s %-15s BIRTH DATE REGISTRATION DATE \n", "ID", "NAME", "GENDER", "IC", "CONTACT NUMBER");
		for (i = 0; i < counter; i++)
		{
			if (strcmp(exist[i].contactNumb, contactNumb) == 0)
			{

			
				printf("%-15s %-30s %-10c %-15s %-15s %02d/%02d/%d   %02d/%02d/%d %02d:%02d:%02d\n"
					, exist[i].ID, exist[i].name, toupper(exist[i].gender),
					exist[i].IC, exist[i].contactNumb,
					exist[i].birthDate.day, exist[i].birthDate.month, exist[i].birthDate.year,
					exist[i].registeredDate.year, exist[i].registeredDate.month, exist[i].registeredDate.day,
					exist[i].registeredTime.hour, exist[i].registeredTime.minute, exist[i].registeredTime.second);
				editingUI(choices, exist[i]);
				error = 1;
				break;
			}
		}
		if (error == 0) {
			printf("No Result found\n");
		}
		break;
	}
	case 6: {
		do {
			printf("Please enter the birth date > ");
			scanf("%d %d %d", &day, &month, &year);
			rewind(stdin);
			if (day < 1 || day > 31) {
				error2 = 1;
			}
			if (month < 1 || month > 12) {
				error2 = 1;
			}
			if (year < 1800 || day > 2200) {
				error2 = 1;
			}
			if (error2 == 1) {
				printf("Invalid Date");
			}
		} while (error2 == 1);
		printf("%-15s %-30s %-10s %-15s %-15s BIRTH DATE REGISTRATION DATE \n", "ID", "NAME", "GENDER", "IC", "CONTACT NUMBER");
		for (i = 0; i < counter; i++)
		{
			if (exist[i].birthDate.day == day)
			{
				if (exist[i].birthDate.month == month)
				{
					if (exist[i].birthDate.year == year)
					{
						
						printf("%-15s %-30s %-10c %-15s %-15s %02d/%02d/%d   %02d/%02d/%d %02d:%02d:%02d\n"
							, exist[i].ID, exist[i].name, toupper(exist[i].gender),
							exist[i].IC, exist[i].contactNumb,
							exist[i].birthDate.day, exist[i].birthDate.month, exist[i].birthDate.year,
							exist[i].registeredDate.year, exist[i].registeredDate.month, exist[i].registeredDate.day,
							exist[i].registeredTime.hour, exist[i].registeredTime.minute, exist[i].registeredTime.second);
						editingUI(choices, exist[i]);
						error = 1;
						break;
					}
				}
			}
		}
		if (error == 0) {
			printf("No Result found\n");
		}
		break; }
	case 0: {
		return; printf("\n\n");  break;
	}
	}
	fclose(mod);
}

void editingUI(int choice, USER newData)
{
	FILE* edit = fopen("USER Information.bin", "rb");
	USER exist[50];
	char applyChange;
	char ID[12], name[30], change, IC[15], contactNumb[15];
	int day, month, year;
	int counter = 0;
	int alreadyHaveLiao;
	while (fread(&exist[counter], sizeof(exist[counter]), 1, edit)) {
		counter++;
	}
	switch (choice)
	{
	case 1: {
		printf("Please enter the new ID : ");
		scanf("%s", &ID);
		do {
			alreadyHaveLiao = 0;
			for (int i = 0; i < counter; i++)
			{
				if (strcmp(exist[i].ID, ID) == 0)
				{
					alreadyHaveLiao++;
					printf("\nError!!!\nThe ID you entered is already exist.\n");
				}
			}
			rewind(stdin);
		} while (alreadyHaveLiao == 1);
		rewind(stdin);

		break;
	}
	case 2: {
		printf("Please enter your new name : ");
		scanf("%[^\n]", &name);
		do {
			alreadyHaveLiao = 0;

			for (int i = 0; i < counter; i++)
			{
				if (strcmp(exist[i].name, name) == 0)
				{
					alreadyHaveLiao++;
					printf("\nError!!!\nThe name you entered is already exist");
				}
			}
			rewind(stdin);
		} while (alreadyHaveLiao == 1);
		rewind(stdin);
		break;
	}
	case 3: {
		printf("Do you want to switch to another gender??? (Y/N) : ");
		scanf("%c", &change);
		rewind(stdin);
		while (change != 'Y' && change != 'y' && change != 'N' && change != 'n')
		{
			printf("Invalid character!!\nPlease reenter again > ");
			scanf("%c", &change);
			rewind(stdin);
		}
		break;
	}
	case 4: {
		printf("Please enter your new IC : ");
		scanf("%s", &IC);
		rewind(stdin);
		do {
			alreadyHaveLiao = 0;
			for (int i = 0; i < counter; i++)
			{
				if (strcmp(exist[i].IC, IC) == 0)
				{
					alreadyHaveLiao++;
					printf("\nError!!!\nThe IC you entered is already exist\n");
				}
			}
			rewind(stdin);
		} while (alreadyHaveLiao == 1);
		break;
	}
	case 5: {
		printf("Please enter your new contact number : ");
		scanf("%s", &contactNumb);
		rewind(stdin);
		do {
			alreadyHaveLiao = 0;
			for (int i = 0; i < counter; i++)
			{
				if (strcmp(exist[i].contactNumb, contactNumb) == 0)
				{
					alreadyHaveLiao++;
					printf("\nError!!!\nThe contact number you entered is already exist\n");
				}
			}
		} while (alreadyHaveLiao == 1);

		break;
	}
	case 6: {
		printf("Please enter your new birth date : ");
		scanf("%d %d %d", &day, &month, &year);
		rewind(stdin);
		break;
	}
	}
	printf("Do you want to apply changes for this data??? (Y/N) : ");
	scanf("%c", &applyChange);
	rewind(stdin);
	if (applyChange == 'Y' || applyChange == 'y')
	{
		printf("You have apply your changes for your new data!!!\n");
		FILE* mod = fopen("USER Information.bin", "wb");
		for (int i = 0; i < counter; i++) {
			if (strcmp(newData.ID, exist[i].ID) == 0) {
				switch (choice)
				{
				case 1:
				{
					strcpy(exist[i].ID, ID);
					break;
				}
				case 2:
				{
					strcpy(exist[i].name, name);
					break;
				}
				case 3:
				{
					if (tolower(change == 'y')) {
						if (tolower(exist[i].gender) == 'm') {
							exist[i].gender = 'F';
						}
						else {
							exist[i].gender = 'M';
						}
					}
					break;
				}
				case 4:
				{
					strcpy(exist[i].IC, IC);
					break;
				}
				case 5:
				{
					strcpy(exist[i].contactNumb, contactNumb);
					break;
				}
				case 6: {
					exist[i].birthDate.day = day;
					exist[i].birthDate.month = month;
					exist[i].birthDate.year = year;
					break;
				}
				}
			}
			fwrite(&exist[i], sizeof(exist[i]), 1, mod);
		}
		fclose(mod);

	}
	else
	{
		printf("You haven't apply changes for your new data!!!\n");
		exit;
	}
	fclose(edit);

}

void delUI()
{
	int choices;
	USER dlt;
	USER exist[50];
	char ID[12], name[30], gender, IC[15], contactNumb[15];
	char removeOrNot;
	int day, month, year;
	int i, counter = 0, error = 0, error2 = 0;
	printf("\nRemoving the user information\n");
	FILE* del = fopen("USER Information.bin", "rb");
	if (del == NULL) {
		printf("\n\n<<Sorry, the file cannot open!!>>\n\n");
		exit(-1);
	}
	while (fread(&exist[counter], sizeof(exist[counter]), 1, del)) {
		counter++;
	}
	fclose(del);
	printf("Search the USER according to their\n1. ID\n2. Name\n3. IC\n4. Contact Number");
	printf("If you wish to return to the upper menu, please enter 0.\n");
	printf("Please enter your choices	>	");
	scanf("%d", &choices);
	rewind(stdin);
	
	while (choices < -1 || choices > 4) {
		printf("\nInvalid digits plaease reenter again!!!	>	");
		scanf("%d", &choices);
		rewind(stdin);
	}
	switch (choices)
	{
	case 1: {
		printf("Please enter the ID > ");
		scanf("%s", &ID);
		rewind(stdin);
		printf("%-15s %-30s %-10s %-15s %-15s BIRTH DATE REGISTRATION DATE \n", "ID", "NAME", "GENDER", "IC", "CONTACT NUMBER");
		for (i = 0; i < counter; i++)
		{
			if (strcmp(exist[i].ID, ID) == 0)
			{

				
				printf("%-15s %-30s %-10c %-15s %-15s %02d/%02d/%d   %02d/%02d/%d %02d:%02d:%02d\n"
					, exist[i].ID, exist[i].name, toupper(exist[i].gender),
					exist[i].IC, exist[i].contactNumb,
					exist[i].birthDate.day, exist[i].birthDate.month, exist[i].birthDate.year,
					exist[i].registeredDate.year, exist[i].registeredDate.month, exist[i].registeredDate.day,
					exist[i].registeredTime.hour, exist[i].registeredTime.minute, exist[i].registeredTime.second);
				removingUI(exist[i]);
				error = 1;
				break;
			}

		}
		if (error == 0) {
			printf("No Result found\n");
		}
		break;
	}
	case 2: {
		printf("Please enter the name > ");
		scanf("%[^\n]", &name);
		rewind(stdin);
		printf("%-15s %-30s %-10s %-15s %-15s BIRTH DATE REGISTRATION DATE \n", "ID", "NAME", "GENDER", "IC", "CONTACT NUMBER");
		for (i = 0; i < counter; i++)
		{

			if (strcmp(exist[i].name, name) == 0)
			{

				
				printf("%-15s %-30s %-10c %-15s %-15s %02d/%02d/%d   %02d/%02d/%d %02d:%02d:%02d\n"
					, exist[i].ID, exist[i].name, toupper(exist[i].gender),
					exist[i].IC, exist[i].contactNumb,
					exist[i].birthDate.day, exist[i].birthDate.month, exist[i].birthDate.year,
					exist[i].registeredDate.year, exist[i].registeredDate.month, exist[i].registeredDate.day,
					exist[i].registeredTime.hour, exist[i].registeredTime.minute, exist[i].registeredTime.second);
				removingUI(exist[i]);
				error = 1;
				break;
			}

		}
		if (error == 0) {
			printf("No Result found\n");
		}
		break;
	}
	case 3: {
		printf("Please enter the IC > ");
		scanf("%s", &IC);
		rewind(stdin);
		printf("%-15s %-30s %-10s %-15s %-15s BIRTH DATE REGISTRATION DATE \n", "ID", "NAME", "GENDER", "IC", "CONTACT NUMBER");
		for (i = 0; i < counter; i++)
		{
			if (strcmp(exist[i].IC, IC) == 0)
			{

				
				printf("%-15s %-30s %-10c %-15s %-15s %02d/%02d/%d   %02d/%02d/%d %02d:%02d:%02d\n"
					, exist[i].ID, exist[i].name, toupper(exist[i].gender),
					exist[i].IC, exist[i].contactNumb,
					exist[i].birthDate.day, exist[i].birthDate.month, exist[i].birthDate.year,
					exist[i].registeredDate.year, exist[i].registeredDate.month, exist[i].registeredDate.day,
					exist[i].registeredTime.hour, exist[i].registeredTime.minute, exist[i].registeredTime.second);
				removingUI(exist[i]);
				error = 1;
				break;
			}

		}
		if (error == 0) {
			printf("No Result found\n");
		}
		break;
	}
	case 4: {
		printf("Please enter the contact number > ");
		scanf("%s", &contactNumb);
		rewind(stdin);
		printf("%-15s %-30s %-10s %-15s %-15s BIRTH DATE REGISTRATION DATE \n", "ID", "NAME", "GENDER", "IC", "CONTACT NUMBER");
		for (i = 0; i < counter; i++)
		{
			if (strcmp(exist[i].contactNumb, contactNumb) == 0)
			{

				
				printf("%-15s %-30s %-10c %-15s %-15s %02d/%02d/%d   %02d/%02d/%d %02d:%02d:%02d\n"
					, exist[i].ID, exist[i].name, toupper(exist[i].gender),
					exist[i].IC, exist[i].contactNumb,
					exist[i].birthDate.day, exist[i].birthDate.month, exist[i].birthDate.year,
					exist[i].registeredDate.year, exist[i].registeredDate.month, exist[i].registeredDate.day,
					exist[i].registeredTime.hour, exist[i].registeredTime.minute, exist[i].registeredTime.second);
				removingUI(exist[i]);
				error = 1;
				break;
			}

		}
		if (error == 0) {
			printf("No Result found\n");
		}
		break;
		}
	
	}
}

void removingUI(USER info)
{
	FILE* removing = fopen("User Information.bin", "rb");
	int counter = 0;
	char yOrn;
	USER exist[100];
	while (fread(&exist[counter], sizeof(USER), 1, removing) != 0) {
		counter++;
	}
	fclose(removing);
	printf("Are you sure do you want to remove the information of %s??? (Y/N)", info.name);
	scanf("%c", &yOrn);
	rewind(stdin);
	while (yOrn != 'Y' && yOrn != 'y' && yOrn != 'N' && yOrn != 'n')
	{
		printf("Invalid character!!!\nPlease enter Y or N only : ");
		scanf("%c", &yOrn);
		rewind(stdin);
	}
	if (yOrn == 'Y' || yOrn == 'y')
	{
		FILE* removed = fopen("User Information.bin", "wb");
		for (int i = 0; i < counter; i++) {
			if (!(strcmp(info.ID, exist[i].ID) == 0)) {
				fwrite(&exist[i], sizeof(exist[i]), 1, removed);
			}
		}
		printf("\nThe user information of %s has been removed!!!\n", info.name);
		fclose(removed);
	}
	else if (yOrn == 'N' || yOrn == 'n')
	{
		printf("\nThe user information of %s has not removed!!!\n", info.name);

	}
	fclose(removing);
}

void dispUI()
{
	int i = 0;
	USER display;
	FILE* disp = fopen("USER information.bin", "rb");
	if (disp == NULL)
	{
		printf("Cannot open the file!!\n");
		exit;
	}
	else
	{
		printf("\nDisplaying the list of the user information\n");
		printf("%-15s %-30s %-10s %-15s %-15s BIRTH DATE REGISTRATION DATE \n", "ID", "NAME", "GENDER", "IC", "CONTACT NUMBER");

		while (fread(&display, sizeof(display), 1, disp) != 0)
		{

			printf("%-15s %-30s %-10c %-15s %-15s %02d/%02d/%d %d/%02d/%02d %02d:%02d:%02d\n"
				, display.ID, display.name, toupper(display.gender),
				display.IC, display.contactNumb,
				display.birthDate.day, display.birthDate.month, display.birthDate.year,
				display.registeredDate.year, display.registeredDate.month, display.registeredDate.day,
				display.registeredTime.hour, display.registeredTime.minute, display.registeredTime.second);
			i++;
		}
		fclose(disp);
		printf("\n\n");
	}

}

