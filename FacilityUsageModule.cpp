#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>
#include <Windows.h>
#include "Main.h"
#pragma warning (disable:4996)
#pragma warning (disable:6031)
#pragma warning (disable:4101)
#pragma warning (disable:6054)

/*
===========================
Facility Usage Module
Made by: Choo Zhi Yan
===========================
*/
void syncB() {
	facilityUsage existFU[50];
	struct BOOKING existB[50];
	int counterB = 0, counterFU = 0, empty = 0, i2 = 0;
	char bookingID[11];
	SYSTEMTIME t;
	GetLocalTime(&t);
	FILE* br = fopen("booking.txt", "r");
	FILE* fur = fopen("facility usage.txt", "r");
	if (br != NULL) {
		while (fscanf(br, "%[^,],%d %d %d,%d %d %d,%d:%d - %d:%d,%[^,],%[^\n]\n",
			&existB[counterB].bookingID,
			&existB[counterB].currentDate.day, &existB[counterB].currentDate.month, &existB[counterB].currentDate.year,
			&existB[counterB].date.day, &existB[counterB].date.month, &existB[counterB].date.year,
			&existB[counterB].time.shour, &existB[counterB].time.sminute,
			&existB[counterB].time.fhour, &existB[counterB].time.fminute,
			&existB[counterB].userID, &existB[counterB].facilityID) != EOF)
		{
			counterB++;
		}
		fclose(br);
	}
	if (fur != NULL) {
		while (fscanf(fur, "%d,%d,%d\t%d,%d\t%d,%d\t%s\t%s\t%s\n", &existFU[counterFU].date.day, &existFU[counterFU].date.month, &existFU[counterFU].date.year,
			&existFU[counterFU].timeFrom.hours, &existFU[counterFU].timeFrom.minutes,
			&existFU[counterFU].timeTo.hours, &existFU[counterFU].timeTo.minutes,
			&existFU[counterFU].userID, &existFU[counterFU].facilityID, &existFU[counterFU].usageType) != EOF)
		{
			counterFU++;
		}
		fclose(fur);
	}
	for (int i = 0; i < counterFU; i++) {
		for (int k = 0; k < counterB; k++) {
			if ((strcmp(existB[k].facilityID, existFU[i].facilityID) == 0) && existB[k].date.day == existFU[i].date.day
				&& existB[k].date.month == existFU[i].date.month && existB[k].date.year == existFU[i].date.year
				&& existB[k].time.shour == existFU[i].timeFrom.hours && existB[k].time.sminute == existFU[i].timeFrom.minutes
				&& existB[k].time.fhour == existFU[i].timeTo.hours && existB[k].time.fminute == existFU[i].timeTo.minutes) {
				empty = 1;
				break;
			}
		}
		if (empty != 1) {
			if (strcmp(strlwr(existFU[i].usageType), "booked") == 0) {
				do {
					for (int k = 0; k < 10; k++)
					{
						bookingID[k] = generateID();
					}
					bookingID[10] = '\0';
					for (int i2 = 0; i2 < counterB; i++) {
						if (strcmp(bookingID, existB[i2].bookingID) == 0) {
							break;
						}
					}
				} while (strcmp(bookingID, existB[i2].bookingID) == 0);
				FILE* bw = fopen("booking.txt", "a");
				fprintf(bw, "%s,%d %d %d,%d %d %d,%d:%d - %d:%d,%s,%s\n",
					bookingID,
					t.wDay, t.wMonth, t.wYear,
					existFU[i].date.day, existFU[i].date.month, existFU[i].date.year,
					existFU[i].timeFrom.hours, existFU[i].timeFrom.minutes, existFU[i].timeTo.hours, existFU[i].timeTo.minutes,
					existFU[i].userID, existFU[i].facilityID);
				fclose(bw);
			}
		}
	}
}
void fuMenu()
{
	int choice = 0;
	do {
		printf("-----------------------------------\n");
		printf("|                                 |\n");
		printf("|       FACILITY USAGE MENU       |\n");
		printf("|                                 |\n");
		printf("-----------------------------------\n");
		printf("\n");
		printf("1. Display all facility usage details.\n");
		printf("2. Add facility usage.\n");
		printf("3. Search facility usage.\n");
		printf("4. Modify facility usage.\n");
		printf("5. Exit.\n");
		printf("Please select your choice : ");
		rewind(stdin);
		scanf("%d", &choice);
		while (choice > 5 || choice < 1) {
			printf("\nInvalid number, please enter again : ");
			rewind(stdin);
			scanf("%d", &choice);
		}
		switch (choice)
		{
		case 1: displayData(); break;
		case 2: addFU(); break;
		case 3: searchFU(); break;
		case 4: modifyFU(); break;
		case 5: break;
		}
	} while (choice != 5);

}

// READ DATA FROM BOOKING MODULE THEN DISPLAY
void displayData()
{
	FILE* fptr1 = fopen("facility usage.txt", "r");
	facilityUsage displayFU;

	int changes = 0;
	int num = 1;
	int counter = 0;

	if (fptr1 == NULL)
	{
		printf("File not exist\n");
		system("pause");
		exit(-1);
	}

	printf("This is the facility usage details\n");
	printf("-------------------------------------------\n");

	while (fscanf(fptr1, "%d,%d,%d\t%d,%d\t%d,%d\t%s\t%s\t%s\n", &displayFU.date.day, &displayFU.date.month, &displayFU.date.year,
		&displayFU.timeFrom.hours, &displayFU.timeFrom.minutes, &displayFU.timeTo.hours, &displayFU.timeTo.minutes,
		&displayFU.userID, &displayFU.facilityID, &displayFU.usageType) != EOF)
	{
		printf("Record : %d\n", num);
		printf("Date : %2d/%2d/%4d\n", displayFU.date.day, displayFU.date.month, displayFU.date.year);
		printf("Time : %02d:%02d - %02d:%02d\n", displayFU.timeFrom.hours, displayFU.timeFrom.minutes, displayFU.timeTo.hours, displayFU.timeTo.minutes);
		printf("User ID : %s\n", displayFU.userID);
		printf("Facility ID : %s\n", displayFU.facilityID);
		printf("Usage Type : %s\n", displayFU.usageType);
		printf("\n");

		num++;
		counter++;
	}

	printf("%d facility usage details.\n", counter);
	fclose(fptr1);
	do {
		printf("\nDo you want to make changes to the data?\n");
		printf("1. Add data\n");
		printf("2. Modify data\n");
		printf("3. No, exit page\n");
		rewind(stdin);
		printf("Selection : ");
		scanf("%d", &changes);
		rewind(stdin);
		while (changes < 1 || changes > 3)
		{
			rewind(stdin);
			printf("\nInvalid number, please enter again : ");
			scanf("%d", &changes);
		}

		switch (changes)
		{
		case 1: addFU(); break;
		case 2: modifyFU(); break;
		case 3: break;
		}
	} while (changes != 3);



}

//ADD FU
void addFU()
{
	FILE* fptr2 = fopen("facility usage.txt", "a");
	FILE* fptr = fopen("booking.txt", "a");
	char bookingID[11];
	struct BOOKING exist[40];
	facilityUsage addFU;
	SYSTEMTIME t;
	GetLocalTime(&t);
	int check, check2, i, counter = 0, error2 = 0;
	char confirmAdd;
	char anotherAdd;
	FILE* rk = fopen("booking.txt", "r");
	while (fscanf(rk, "%[^,],%d %d %d,%d %d %d,%d:%d - %d:%d,%[^,],%[^\n]\n",
		&exist[counter].bookingID,
		&exist[counter].currentDate.day, &exist[counter].currentDate.month, &exist[counter].currentDate.year,
		&exist[counter].date.day, &exist[counter].date.month, &exist[counter].date.year,
		&exist[counter].time.shour, &exist[counter].time.sminute,
		&exist[counter].time.fhour, &exist[counter].time.fminute,
		&exist[counter].userID, &exist[counter].facilityID) != EOF)
	{
		counter++;
	}
	printf("\n========================\n");
	printf("ADD FACILITY USAGE\n");
	printf("========================\n");
	do
	{
		do
		{
			do {
				error2 = 0;
				rewind(stdin);
				printf("Enter your additional data : \n");
				printf("Date (dd mm yyyy) :");
				scanf("%d %d %d", &addFU.date.day, &addFU.date.month, &addFU.date.year);
				if (addFU.date.day < 1 || addFU.date.day  >31) {
					error2 = 1;
				}
				if (addFU.date.month < 1 || addFU.date.month >12) {
					error2 = 1;
				}
				if (addFU.date.year < 1800 || addFU.date.year >2200) {
					error2 = 1;
				}
				if (error2 == 1) {
					printf("Invalid Date\n");
				}
			} while (error2 == 1);
			

			do
			{
				rewind(stdin);
				printf("Time from (12 00 ,24hours calculation) : ");
				scanf("%d %d", &addFU.timeFrom.hours, &addFU.timeFrom.minutes);
				check = checkTime(addFU.timeFrom.hours, addFU.timeFrom.minutes);
				if (check == 0)
					printf("Invalid time, please enter again\n");
			} while (check == 0);

			do
			{
				rewind(stdin);
				printf("Time to (12 00 ,24hours calculation) : ");
				scanf("%d %d", &addFU.timeTo.hours, &addFU.timeTo.minutes); //rewrite when invalid
				check2 = checkTime(addFU.timeTo.hours, addFU.timeTo.minutes); //while loop + if else
				if (check2 == 0)
					printf("Invalid time, please enter again\n");
			} while (check2 == 0);

			rewind(stdin);
			printf("User ID (19PMD00000): ");
			scanf("%[^\n]", &addFU.userID);

			rewind(stdin);
			printf("Facility ID (F0001): ");
			scanf("%[^\n]", &addFU.facilityID);

			
			do {
				rewind(stdin);
				printf("Usage type (booked/walked-in) : ");
				scanf("%[^\n]", &addFU.usageType);
				strcpy(addFU.usageType,strlwr(addFU.usageType));
				if (strcmp(addFU.usageType, "booked") != 0 && strcmp(addFU.usageType, "walked-in")!=0) {
					printf("Invalid\n");
				}
			} while (strcmp(addFU.usageType, "booked") != 0 && strcmp(addFU.usageType, "walked-in") != 0);

			printf("\nNew data\n");
			printf("===================================\n");
			printf("Date : %2d/%2d/%4d\n", addFU.date.day, addFU.date.month, addFU.date.year);
			printf("Time : %02d:%02d - %02d:%02d\n", addFU.timeFrom.hours, addFU.timeFrom.minutes, addFU.timeTo.hours, addFU.timeTo.minutes);
			printf("User ID : %s\n", addFU.userID);
			printf("Facility ID : %s\n", addFU.facilityID);
			printf("Usage Type : %s\n", addFU.usageType);
			printf("\n");//#

			rewind(stdin);
			printf("Confirm add facility usage ? (Y=yes N=no):");
			scanf("%c", &confirmAdd);

			if (confirmAdd == 'N' || confirmAdd == 'n')
			{
				printf("--------------------------------\n");
				printf("|     Cancelled add data.      |\n");
				printf("--------------------------------\n");
			}
			else
			{
				printf("--------------------------------\n");
				printf("|     Successful add data!     |\n");
				printf("--------------------------------\n");
				fprintf(fptr2, "%d,%d,%d\t%d,%d\t%d,%d\t%s\t%s\t%s\n", addFU.date.day, addFU.date.month, addFU.date.year,
					addFU.timeFrom.hours, addFU.timeFrom.minutes, addFU.timeTo.hours, addFU.timeTo.minutes,
					addFU.userID, addFU.facilityID, addFU.usageType); 
				if (strncmp(addFU.usageType, "booked", 4) == 0) {
					do {
						for (int k = 0; k < 10; k++)
						{
							bookingID[k] = generateID();
						}
						bookingID[10] = '\0';
						for (i = 0; i < counter; i++) {
							if (strcmp(bookingID, exist[i].bookingID) == 0) {
								break;
							}
						}
					} while (strcmp(bookingID, exist[i].bookingID) == 0);
						fprintf(fptr, "%s,%d %d %d,%d %d %d,%d:%d - %d:%d,%s,%s\n",
							bookingID,
							t.wDay, t.wMonth, t.wYear,
							addFU.date.day, addFU.date.month, addFU.date.year,
							addFU.timeFrom.hours, addFU.timeFrom.minutes, addFU.timeTo.hours, addFU.timeTo.minutes,
							addFU.userID, addFU.facilityID);
				}
				
			}
		} while (confirmAdd == 'N' || confirmAdd == 'n');

		rewind(stdin);
		printf("\nDo you want to add another data? (Y=yes N=no): ");
		scanf("%c", &anotherAdd);

	} while (anotherAdd == 'Y' || anotherAdd == 'y');
	fclose(fptr2);
	fclose(fptr);
}

// CHECK TIME 
int checkTime(int timehours, int timeminutes)
{
	if (timehours > 23 || timeminutes > 59)
		return 0;
	else
		return 1;
}

//SELECT WHAT TO DO
void searchFU()
{
	int selection;
	printf("\n==========================\n");
	printf("Search Facility Usage\n");
	printf("==========================\n");

	printf("\nPlease select search for\n");
	printf("1.Number\n");
	printf("2.Date\n");
	printf("3.Time\n");
	printf("4.User ID\n");
	printf("5.Facility ID\n");
	printf("6.Usage Type\n");
	printf("7.Exit\n");
	printf("Selection :");
	scanf("%d", &selection);

	while (selection > 7 || selection < 1)
	{
		rewind(stdin);
		printf("\nInvalid number, please enter again : ");
		scanf("%d", &selection);
	}
	printf("\n");
	switch (selection)
	{
	case 1:searchNum(); break;
	case 2:searchDate(); break;
	case 3:searchTime(); break;
	case 4:searchUserID(); break;
	case 5:searchFacilityID(); break;
	case 6:searchUsageType(); break;
	case 7:break;
	}

}

// DISPLAY SEARCH RECORD
void displaySearch(facilityUsage search)
{
	printf("Date : %2d/%2d/%4d\n", search.date.day, search.date.month, search.date.year);
	printf("Time : %02d:%02d - %02d:%02d\n", search.timeFrom.hours, search.timeFrom.minutes, search.timeTo.hours, search.timeTo.minutes);
	printf("User ID : %s\n", search.userID);
	printf("Facility ID : %s\n", search.facilityID);
	printf("Usage Type : %s\n", search.usageType);
	printf("\n");

}

//SEARCH FOR NUMBER
void searchNum()
{
	FILE* fptr3 = fopen("facility usage.txt", "r");
	facilityUsage search;
	int num = 0, counter = 0;

	printf("Enter the number of record : ");
	scanf("%d", &num);
	printf("\n");
	while (fscanf(fptr3, "%d,%d,%d\t%d,%d\t%d,%d\t%s\t%s\t%s\n", &search.date.day, &search.date.month, &search.date.year,
		&search.timeFrom.hours, &search.timeFrom.minutes, &search.timeTo.hours, &search.timeTo.minutes,
		&search.userID, &search.facilityID, &search.usageType) != EOF) //#
	{
		counter++;
		if (num == counter)
		{
			displaySearch(search);
		}
	}
	fclose(fptr3);
}

// SEARCH FOR FU_DATE
void searchDate()
{
	FILE* fptr3 = fopen("facility usage.txt", "r");

	facilityUsage searchDate;
	int search, searchDay, searchMonth, searchYear;
	int counter = 0;

	rewind(stdin);
	printf("1.Day\n");
	printf("2.Month\n");
	printf("3.Year\n");
	printf("Search for : ");
	scanf("%d", &search);

	while (search > 3)
	{
		rewind(stdin);
		printf("\nInvalid number, please enter again : ");
		scanf("%d", &search);
	}
	printf("\n");
	if (search == 1)
	{
		rewind(stdin);
		printf("Enter search day :");
		scanf("%d", &searchDay);

		while (fscanf(fptr3, "%d,%d,%d\t%d,%d\t%d,%d\t%s\t%s\t%s\n", &searchDate.date.day, &searchDate.date.month, &searchDate.date.year,
			&searchDate.timeFrom.hours, &searchDate.timeFrom.minutes, &searchDate.timeTo.hours, &searchDate.timeTo.minutes,
			&searchDate.userID, &searchDate.facilityID, &searchDate.usageType) != EOF) //#
		{
			if (searchDay == searchDate.date.day)
			{
				displaySearch(searchDate);
				counter++;
			}
		}
		printf("%d records exist.\n", counter);
	}

	else if (search == 2)
	{
		rewind(stdin);
		printf("Enter search month :");
		scanf("%d", &searchMonth);

		while (fscanf(fptr3, "%d,%d,%d\t%d,%d\t%d,%d\t%s\t%s\t%s\n", &searchDate.date.day, &searchDate.date.month, &searchDate.date.year,
			&searchDate.timeFrom.hours, &searchDate.timeFrom.minutes, &searchDate.timeTo.hours, &searchDate.timeTo.minutes,
			&searchDate.userID, &searchDate.facilityID, &searchDate.usageType) != EOF) //#
		{
			if (searchMonth == searchDate.date.month)
			{
				displaySearch(searchDate);
				counter++;
			}
		}
		printf("%d records exist.\n", counter);
	}

	else if (search == 3)
	{
		rewind(stdin);
		printf("Enter search Year :");
		scanf("%d", &searchYear);

		while (fscanf(fptr3, "%d,%d,%d\t%d,%d\t%d,%d\t%s\t%s\t%s\n", &searchDate.date.day, &searchDate.date.month, &searchDate.date.year,
			&searchDate.timeFrom.hours, &searchDate.timeFrom.minutes, &searchDate.timeTo.hours, &searchDate.timeTo.minutes,
			&searchDate.userID, &searchDate.facilityID, &searchDate.usageType) != EOF) //#
		{
			if (searchYear == searchDate.date.year)
			{
				displaySearch(searchDate);
				counter++;
			}
		}
		printf("%d records exist.\n", counter);
	}
	fclose(fptr3);
	askAddOrModify();
}

// SEARCH FOR TIME
void searchTime()
{
	FILE* fptr4 = fopen("facility usage.txt", "r");

	facilityUsage searchTime;
	int search, fromHours, toHours;
	int counter = 0;


	rewind(stdin);
	printf("1.Time from\n");
	printf("2.Time to\n");
	printf("Search for : ");
	scanf("%d", &search);
	printf("\n");
	while (search > 2 || search < 1)
	{
		rewind(stdin);
		printf("\nInvalid number, please enter again : ");
		scanf("%d", &search);
	}

	if (search == 1)
	{
		rewind(stdin);
		printf("Enter search hours of time from :");
		scanf("%d", &fromHours);

		while (fscanf(fptr4, "%d,%d,%d\t%d,%d\t%d,%d\t%s\t%s\t%s\n", &searchTime.date.day, &searchTime.date.month, &searchTime.date.year,
			&searchTime.timeFrom.hours, &searchTime.timeFrom.minutes, &searchTime.timeTo.hours, &searchTime.timeTo.minutes,
			&searchTime.userID, &searchTime.facilityID, &searchTime.usageType) != EOF) //#
		{
			if (fromHours == searchTime.timeFrom.hours)
			{
				displaySearch(searchTime);
				counter++;
			}
		}
		printf("%d records exist.\n", counter);
	}

	else if (search == 2)
	{
		rewind(stdin);
		printf("Enter search hours of time to :");
		scanf("%d", &toHours);

		while (fscanf(fptr4, "%d,%d,%d\t%d,%d\t%d,%d\t%s\t%s\t%s\n", &searchTime.date.day, &searchTime.date.month, &searchTime.date.year,
			&searchTime.timeFrom.hours, &searchTime.timeFrom.minutes, &searchTime.timeTo.hours, &searchTime.timeTo.minutes,
			&searchTime.userID, &searchTime.facilityID, &searchTime.usageType) != EOF) //#
		{
			if (toHours == searchTime.timeTo.hours)
			{
				displaySearch(searchTime);
				counter++;
			}
		}
		printf("%d records exist.\n", counter);
	}

	fclose(fptr4);
	askAddOrModify();
}

// SEARCH FOR USER ID
void searchUserID()
{
	FILE* fptr5 = fopen("facility usage.txt", "r");

	facilityUsage searchUserID;
	char searchID[15];
	int counter = 0;

	rewind(stdin);
	printf("Search for user ID : ");
	scanf("%[^\n]", &searchID);
	printf("\n");
	while (fscanf(fptr5, "%d,%d,%d\t%d,%d\t%d,%d\t%s\t%s\t%s\n", &searchUserID.date.day, &searchUserID.date.month, &searchUserID.date.year,
		&searchUserID.timeFrom.hours, &searchUserID.timeFrom.minutes, &searchUserID.timeTo.hours, &searchUserID.timeTo.minutes,
		&searchUserID.userID, &searchUserID.facilityID, &searchUserID.usageType) != EOF) //#
	{
		if (strcmp(searchID, searchUserID.userID) == 0)
		{
			displaySearch(searchUserID);
			counter++;
		}
	}
	printf("%d records exist.\n", counter);
	fclose(fptr5);
	askAddOrModify();
}

// SEARCH FOR FACILITY ID
void searchFacilityID()
{
	FILE* fptr6 = fopen("facility usage.txt", "r");

	facilityUsage searchFacilityID;
	char searchID[15];
	int counter = 0;

	rewind(stdin);
	printf("Search for facility ID : ");
	scanf("%[^\n]", &searchID);
	printf("\n");
	while (fscanf(fptr6, "%d,%d,%d\t%d,%d\t%d,%d\t%s\t%s\t%s\n", &searchFacilityID.date.day, &searchFacilityID.date.month, &searchFacilityID.date.year,
		&searchFacilityID.timeFrom.hours, &searchFacilityID.timeFrom.minutes, &searchFacilityID.timeTo.hours, &searchFacilityID.timeTo.minutes,
		&searchFacilityID.userID, &searchFacilityID.facilityID, &searchFacilityID.usageType) != EOF) //#
	{
		if (strcmp(searchID, searchFacilityID.facilityID) == 0)
		{
			displaySearch(searchFacilityID);
			counter++;
		}
	}
	printf("%d records exist.\n", counter);
	fclose(fptr6);
	askAddOrModify();
}

// SEARCH FOR USAGE TYPE
void searchUsageType()
{
	FILE* fptr7 = fopen("facility usage.txt", "r");

	facilityUsage searchUsageType;
	int usageType = 0;
	int counter = 0;

	do {
		rewind(stdin);
		printf("1.booked\n");
		printf("2.walked-in\n");
		printf("Search for usage type : ");
		scanf("%d", &usageType);
		if (usageType < 0 || usageType > 2) {
			printf("Invalid number\n");
		}
	} while (usageType < 0 || usageType > 2);
	printf("\n");
	if (usageType == 1)
	{
		while (fscanf(fptr7, "%d,%d,%d\t%d,%d\t%d,%d\t%s\t%s\t%s\n", &searchUsageType.date.day, &searchUsageType.date.month, &searchUsageType.date.year,
			&searchUsageType.timeFrom.hours, &searchUsageType.timeFrom.minutes, &searchUsageType.timeTo.hours, &searchUsageType.timeTo.minutes,
			&searchUsageType.userID, &searchUsageType.facilityID, &searchUsageType.usageType) != EOF) //#
		{
			if (strcmp(searchUsageType.usageType, "booked") == 0)
			{
				displaySearch(searchUsageType);
				counter++;
			}
		}
	}

	else if (usageType == 2)
		while (fscanf(fptr7, "%d,%d,%d\t%d,%d\t%d,%d\t%s\t%s\t%s\n", &searchUsageType.date.day, &searchUsageType.date.month, &searchUsageType.date.year,
			&searchUsageType.timeFrom.hours, &searchUsageType.timeFrom.minutes, &searchUsageType.timeTo.hours, &searchUsageType.timeTo.minutes,
			&searchUsageType.userID, &searchUsageType.facilityID, &searchUsageType.usageType) != EOF) //#
		{
			if (strcmp(searchUsageType.usageType, "walked-in") == 0)
			{
				displaySearch(searchUsageType);
				counter++;
			}
		}
	printf("%d records exist.\n", counter);

	fclose(fptr7);
	askAddOrModify();
}

void askAddOrModify()
{
	int choice = 0;

	rewind(stdin);
	printf("Do you want to add or modify data ? (1=add 2=modify 3=exit) : ");
	scanf("%d", &choice);

	while (choice > 3)
	{
		rewind(stdin);
		printf("\nInvalid number, please enter again : ");
		scanf("%d", &choice);
	}

	if (choice == 1)
		addFU();
	else if (choice == 2)
		modifyFU();
		
}

//MODIFY THE DATA
void modifyFU()
{
	struct BOOKING exist[40];
	facilityUsage edited;
	facilityUsage modifyFU2[100];
	FU_DATE bookingDate;
	FU_TIME timefrom;
	char yesno2;
	SYSTEMTIME t;
	GetLocalTime(&t);
	int counter = 0, counter2 = 0;
	int selection2, yesno, error, error2;

	printf("-----------------------------------\n");
	printf("|                                 |\n");
	printf("|      MODIFY FACILITY USAGE      |\n");
	printf("|                                 |\n");
	printf("-----------------------------------\n");
	printf("\n");

	rewind(stdin);
	printf("Enter booking date to select which file to modify (dd mm yyyy): ");
	scanf("%d %d %d", &bookingDate.day, &bookingDate.month, &bookingDate.year);
	rewind(stdin);
	printf("Enter booking time from (12 00 ,24hours calculation) : ");
	scanf("%d %d", &timefrom.hours, &timefrom.minutes);
	do
	{
		FILE* fptr9 = fopen("facility usage.txt", "r");
		FILE* search = fopen("booking.txt", "r");
		while (fscanf(fptr9, "%d,%d,%d\t%d,%d\t%d,%d\t%s\t%s\t%s\n", &modifyFU2[counter].date.day, &modifyFU2[counter].date.month, &modifyFU2[counter].date.year,
			&modifyFU2[counter].timeFrom.hours, &modifyFU2[counter].timeFrom.minutes, &modifyFU2[counter].timeTo.hours, &modifyFU2[counter].timeTo.minutes,
			&modifyFU2[counter].userID, &modifyFU2[counter].facilityID, &modifyFU2[counter].usageType) != EOF) // #
		{
			counter++;
		}
		while (fscanf(search, "%[^,],%d %d %d,%d %d %d,%d:%d - %d:%d,%[^,],%[^\n]\n",
			&exist[counter2].bookingID,
			&exist[counter2].currentDate.day, &exist[counter2].currentDate.month, &exist[counter2].currentDate.year,
			&exist[counter2].date.day, &exist[counter2].date.month, &exist[counter2].date.year,
			&exist[counter2].time.shour, &exist[counter2].time.sminute,
			&exist[counter2].time.fhour, &exist[counter2].time.fminute,
			&exist[counter2].userID, &exist[counter2].facilityID) != EOF)
		{
			counter2++;
		}
		fclose(fptr9);
		fclose(search);
		error = 0;
		for (int i = 0; i < counter; i++)
		{

			if (bookingDate.day == modifyFU2[i].date.day && bookingDate.month == modifyFU2[i].date.month &&
				bookingDate.year == modifyFU2[i].date.year && timefrom.hours == modifyFU2[i].timeFrom.hours &&
				timefrom.minutes == modifyFU2[i].timeFrom.minutes)
			{
				edited = modifyFU2[i];
				error = 1;
				printf("Date : %2d/%2d/%2d\n", edited.date.day, edited.date.month, edited.date.year);
				printf("Time : %02d:%02d - %02d:%02d\n", edited.timeFrom.hours, edited.timeFrom.minutes, edited.timeTo.hours, edited.timeTo.minutes);
				printf("User ID : %s\n", edited.userID);
				printf("Facility ID : %s\n", edited.facilityID);
				printf("Usage Type : %s\n", edited.usageType);
				printf("\n");
				selection2 = chooseModifyFU();
				if (selection2 == 1)
				{
					do
					{
						do {
							error2 = 0;
							rewind(stdin);
							printf("Enter new date (dd mm yyyy): ");
							scanf("%d %d %d", &edited.date.day, &edited.date.month, &edited.date.year);
							if (edited.date.day < 1 || edited.date.day  >31) {
								error2 = 1;
							}
							if (edited.date.month < 1 || edited.date.month >12) {
								error2 = 1;
							}
							if (edited.date.year < 1800 || edited.date.year >2200) {
								error2 = 1;
							}
							if (error2 == 1) {
								printf("Invalid Date\n");
							}
						} while (error2 == 1);
						printf("New date is %d/%d/%d\n", edited.date.day, edited.date.month, edited.date.year);
						yesno = confirmModify();
					} while (yesno == 2);
				}

				else if (selection2 == 2)
				{
					do
					{
						do {
							error2 = 0;
							rewind(stdin);
							printf("Enter new time from (12 00): ");
							scanf("%d %d", &edited.timeFrom.hours, &edited.timeFrom.minutes);
							if (edited.timeFrom.hours < 0 || edited.timeFrom.hours  >24) {
								error2 = 1;
							}
							if (edited.timeFrom.minutes < 0 || edited.timeFrom.minutes >60) {
								error2 = 1;
							}
							if (error2 == 1) {
								printf("Invalid Time\n");
							}
						} while (error2 == 1);
						do {
							error2 = 0;
							rewind(stdin);
							printf("Enter new time to (12 00): ");
							scanf("%d %d", &edited.timeTo.hours, &edited.timeTo.minutes);
							if (edited.timeTo.hours < 0 || edited.timeTo.hours  >24) {
								error2 = 1;
							}
							if (edited.timeTo.minutes < 0 || edited.timeTo.minutes >60) {
								error2 = 1;
							}
							if (error2 == 1) {
								printf("Invalid Time\n");
							}
						} while (error2 == 1);
						
						printf("New time is %02d:%02d-%02d:%02d\n", edited.timeFrom.hours, edited.timeFrom.minutes, edited.timeTo.hours, edited.timeTo.minutes);
						yesno = confirmModify();
					} while (yesno == 2);
				}

				else if (selection2 == 3)
				{
					do
					{
						do {
							error2 = 0;
							rewind(stdin);
							printf("Enter new date (dd mm yyyy): ");
							scanf("%d %d %d", &edited.date.day, &edited.date.month, &edited.date.year);
							if (edited.date.day < 1 || edited.date.day  >31) {
								error2 = 1;
							}
							if (edited.date.month < 1 || edited.date.month >12) {
								error2 = 1;
							}
							if (edited.date.year < 1800 || edited.date.year >2200) {
								error2 = 1;
							}
							if (error2 == 1) {
								printf("Invalid Date\n");
							}
						} while (error2 == 1);
						printf("New date is %d/%d/%d\n", edited.date.day, edited.date.month, edited.date.year);
						rewind(stdin);
						do {
							error2 = 0;
							rewind(stdin);
							printf("Enter new time from (12 00): ");
							scanf("%d %d", &edited.timeFrom.hours, &edited.timeFrom.minutes);
							if (edited.timeFrom.hours < 0 || edited.timeFrom.hours  >24) {
								error2 = 1;
							}
							if (edited.timeFrom.minutes < 0 || edited.timeFrom.minutes >60) {
								error2 = 1;
							}
							if (error2 == 1) {
								printf("Invalid Time\n");
							}
						} while (error2 == 1);
						do {
							error2 = 0;
							rewind(stdin);
							printf("Enter new time to (12 00): ");
							scanf("%d %d", &edited.timeTo.hours, &edited.timeTo.minutes);
							if (edited.timeTo.hours < 0 || edited.timeTo.hours  >24) {
								error2 = 1;
							}
							if (edited.timeTo.minutes < 0 || edited.timeTo.minutes >60) {
								error2 = 1;
							}
							if (error2 == 1) {
								printf("Invalid Time\n");
							}
						} while (error2 == 1);
						printf("New time is %02d:%02d-%02d:%02d\n", edited.timeFrom.hours, edited.timeFrom.minutes, edited.timeTo.hours, edited.timeTo.minutes);
						yesno = confirmModify();

					} while (yesno == 2);
				}
				else {
					return;
				}
				if (yesno == 1)
				{
					printf("--------------------------------\n");
					printf("|     Succesful modified!      |\n");
					printf("--------------------------------\n");
					FILE* fptr10 = fopen("facility usage.txt", "w");
					FILE* fptr11 = fopen("booking.txt", "w");
					for (int ai = 0; ai < counter; ai++)
					{
						if (ai == i) {
							fprintf(fptr10, "%d,%d,%d\t%d,%d\t%d,%d\t%s\t%s\t%s\n", edited.date.day, edited.date.month, edited.date.year,
								edited.timeFrom.hours, edited.timeFrom.minutes, edited.timeTo.hours, edited.timeTo.minutes,
								edited.userID, edited.facilityID, edited.usageType);
						}
						else {
							fprintf(fptr10, "%d,%d,%d\t%d,%d\t%d,%d\t%s\t%s\t%s\n", modifyFU2[ai].date.day, modifyFU2[ai].date.month, modifyFU2[ai].date.year,
								modifyFU2[ai].timeFrom.hours, modifyFU2[ai].timeFrom.minutes, modifyFU2[ai].timeTo.hours, modifyFU2[ai].timeTo.minutes,
								modifyFU2[ai].userID, modifyFU2[ai].facilityID, modifyFU2[ai].usageType);
						}
					}
					for (int k = 0; k < counter2; k++) {
						if ((strcmp(exist[k].facilityID, modifyFU2[i].facilityID) == 0) && exist[k].date.day == modifyFU2[i].date.day
							&& exist[k].date.month == modifyFU2[i].date.month && exist[k].date.year == modifyFU2[i].date.year
							&& exist[k].time.shour == modifyFU2[i].timeFrom.hours&& exist[k].time.sminute == modifyFU2[i].timeFrom.minutes
							&& exist[k].time.fhour == modifyFU2[i].timeTo.hours && exist[k].time.fminute == modifyFU2[i].timeTo.minutes) {
							fprintf(fptr11, "%s,%d %d %d,%d %d %d,%d:%d - %d:%d,%s,%s\n",
								exist[k].bookingID,
								t.wDay, t.wMonth, t.wYear,
								edited.date.day, edited.date.month, edited.date.year,
								edited.timeFrom.hours, edited.timeFrom.minutes, edited.timeTo.hours, edited.timeTo.minutes,
								edited.userID, edited.facilityID);
						}
						else {
							fprintf(fptr11, "%s,%d %d %d,%d %d %d,%d:%d - %d:%d,%s,%s\n",
								exist[k].bookingID,
								t.wDay, t.wMonth, t.wYear,
								exist[k].date.day, exist[k].date.month, exist[k].date.year,
								exist[k].time.shour, exist[k].time.sminute, exist[k].time.fhour, exist[k].time.fminute,
								exist[k].userID, exist[k].facilityID);
						}
					}
					fclose(fptr10);
					fclose(fptr11);
				}
				else
				{
					printf("--------------------------------\n");
					printf("|       Cancelled modify.      |\n");
					printf("--------------------------------\n");
				}
				break;
			}
		}
		if (error == 0) {
			printf("Invalid data \n");
		}
		rewind(stdin);
		printf("Another modify ? (y=yes n=no) : ");
		scanf("%c", &yesno2);

	} while (yesno2 == 'Y' || yesno2 == 'y');
}

// CHOOSE WHAT TO MODIFY
int chooseModifyFU()
{
	int selection = 0;
	do {
		printf("1.Date\n");
		printf("2.Time\n");
		printf("3.Both\n");
		printf("4.Exit\n");
		printf("Selection : ");
		scanf("%d", &selection);
		if (selection < 0 || selection > 4) {
			printf("Invalid Digit\n");
		}
	} while (selection < 0 || selection > 4);
	

	return selection;
}

// CONFIRM MODIFY DATA
int confirmModify()
{
	int yesno;
	do {
		rewind(stdin);
		printf("Confirm modify ? (1=yes 2=no): ");
		scanf("%d", &yesno);
		if (yesno < 1 || yesno>2)
			printf("Invalid Digit\n");
	} while (yesno < 1 || yesno>2);
	

	return yesno;
}



