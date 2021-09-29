#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include<time.h>
#include "Main.h"

#pragma warning(disable : 6031)
#pragma warning(disable:4996)

/*
===========================
Booking Module
Made by: Chew Wei Chung
===========================
*/
void syncFU() {
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
	for (int i = 0; i < counterB; i++) {
		for (int k = 0; k < counterFU; k++) {
			if ((strcmp(existB[i].facilityID, existFU[k].facilityID) == 0) && existB[i].date.day == existFU[k].date.day
				&& existB[i].date.month == existFU[k].date.month && existB[i].date.year == existFU[k].date.year
				&& existB[i].time.shour == existFU[k].timeFrom.hours && existB[i].time.sminute == existFU[k].timeFrom.minutes
				&& existB[i].time.fhour == existFU[k].timeTo.hours && existB[i].time.fminute == existFU[k].timeTo.minutes) {
				empty = 1;
				break;
			}
		}
		if (empty != 1) {
			FILE* fuw = fopen("booking.txt", "a");
			fprintf(fuw, "%d,%d,%d\t%d,%d\t%d,%d\t%s\t%s\t%s\n", existB[i].date.day, existB[i].date.month, existB[i].date.year,
				existB[i].time.shour, existB[i].time.sminute,
				existB[i].time.fhour, existB[i].time.fminute, existB[i].userID, existB[i].facilityID, "booked");
			fclose(fuw);
		}
	}
}
//main menu
void bookingMenu()
{
	struct BOOKING booking;
	srand(time(NULL));
	int selection;
	printf("Welcome to booking module\n");
	printf("===========================\n\n");
	do {

		printf("Booking Menu\n"
			"================\n"
			"1.Add Booking\n"
			"2.Search Booking\n"
			"3.Edit Booking\n"
			"4.Show Booking\n"
			"5.Exit\n"
			"Please enter selection:");
		rewind(stdin);
		scanf("%d", &selection);

		while (selection < 1 || selection > 5)
		{
			printf("Please Reenter selection >");
			scanf("%d", &selection);
		}

		switch (selection)
		{

		case 1:addbooking(); break;
		case 2:searchbooking(); break;
		case 3:editbooking(); break;
		case 4:showbooking(); break;
		case 5: break;

		}
	} while (selection != 5);

}

//add new data into text file
void addbooking()
{
	struct BOOKING booking;
	struct BOOKING exist[40];
	USER user[40];
	int a = 0, i = 0;
	int counter = 0;
	int counter2 = 0;
	int hour, minute;
	int day, month, year;
	int error = 1, error2 = 0;
	SYSTEMTIME t;
	GetLocalTime(&t);
	FILE* fptr = fopen("User Information.bin", "rb");
	if (fptr != NULL) {
		while (fread(&user[counter2], sizeof(user[counter2]), 1, fptr) != 0)
		{
			counter2++;

		}
		fclose(fptr);
	}

	printf("\nAdd Booking\n");
	printf("==============\n");
	FILE* bk = fopen("booking.txt", "a");
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
	fclose(rk);
	do {
		error2 = 0;
		printf("Booking Date (DD MM YYYY):");
		scanf("%d %d %d", &booking.date.day, &booking.date.month, &booking.date.year);
		if (booking.date.day < 1 || booking.date.day>31) {
			error2 = 1;
		}
		if (booking.date.month < 1 || booking.date.month>12) {
			error2 = 1;
		}
		if (booking.date.year < 1900 || booking.date.year>2200) {
			error2 = 1;
		}
		if (error2 == 1) {
			printf("Invalid Date\n");
		}
	} while (error2 == 1);

	do {
		error2 = 0;
		printf("Time (HH MM): ");
		scanf("%d %d", &booking.time.shour, &booking.time.sminute);
		if (booking.time.shour < 0 || booking.time.shour >24) {
			error2 = 1;
		}
		if (booking.time.sminute < 0 || booking.date.month>60) {
			error2 = 1;
		}
		if (error2 == 1) {
			printf("Invalid Time\n");
		}
	} while (error2 == 1);

	do {
		error2 = 0;
		printf("Finish Time(HH MM):");
		scanf("%d %d", &booking.time.fhour, &booking.time.fminute);
		if (booking.time.fhour < 0 || booking.time.fhour >24) {
			error2 = 1;
		}
		if (booking.time.fminute < 0 || booking.date.month>60) {
			error2 = 1;
		}
		if (error2 == 1) {
			printf("Invalid Time\n");
		}
	} while (error2 == 1);


	printf("Facility ID:");
	scanf("%s", &booking.facilityID);
	do {
		printf("User ID:");
		scanf("%s", &booking.userID);
		if (counter2 == 0) {
			error = 0;
		}
		for (int check = 0; check < counter2; check++) {
			if (strcmp(user[check].ID, booking.userID) == 0) {
				error = 0;
			}
		}
		if (error == 1) {
			printf("UserID not found\n");
		}
	} while (error == 1);
	do {
		for (int k = 0; k < 10; k++)
		{
			booking.bookingID[k] = generateID();
		}
		booking.bookingID[10] = '\0';
		for (i = 0; i < counter; i++) {
			if (strcmp(booking.bookingID, exist[i].bookingID) == 0) {
				break;
			}
		}
	} while (strcmp(booking.bookingID, exist[i].bookingID) == 0);
	fprintf(bk, "%s,%d %d %d,%d %d %d,%d:%d - %d:%d,%s,%s\n",
		booking.bookingID,
		t.wDay, t.wMonth, t.wYear,
		booking.date.day, booking.date.month, booking.date.year,
		booking.time.shour, booking.time.sminute,
		booking.time.fhour, booking.time.fminute,
		booking.userID, booking.facilityID);
	FILE* fptr2 = fopen("facility usage.txt", "a");
	fprintf(fptr2, "%d,%d,%d\t%d,%d\t%d,%d\t%s\t%s\t%s\n", booking.date.day, booking.date.month, booking.date.year,
		booking.time.shour, booking.time.sminute,
		booking.time.fhour, booking.time.fminute, booking.userID, booking.facilityID, "booked");
	fclose(fptr2);
	fclose(bk);
}

//searching saving datas from text file
void searchbooking()
{
	char bookingID[11];
	char selection;
	int a = 0, i = 0, counter = 0;
	int day, month, year;
	int hour, minute;
	printf("\nSearch Booking\n");
	printf("===================\n");
	FILE* search = fopen("booking.txt", "r");
	FILE* fptr = fopen("User Information.bin", "rb");
	struct BOOKING booking;
	struct BOOKING exist[100];
	SYSTEMTIME t;
	GetLocalTime(&t);
	printf("Enter Booking ID:");
	scanf("%s", &bookingID);
	while (fscanf(search, "%[^,],%d %d %d,%d %d %d,%d:%d - %d:%d,%[^,],%[^\n]\n",
		&exist[counter].bookingID,
		&exist[counter].currentDate.day, &exist[counter].currentDate.month, &exist[counter].currentDate.year,
		&exist[counter].date.day, &exist[counter].date.month, &exist[counter].date.year,
		&exist[counter].time.shour, &exist[counter].time.sminute,
		&exist[counter].time.fhour, &exist[counter].time.fminute,
		&exist[counter].userID, &exist[counter].facilityID) != EOF)
	{
		counter++;
	}
	fclose(search);
	printf("BookingID\tCurrent Date\tBooking Date\tBooking Time\t User ID\tFacility ID\n");
	for (i = 0; i < counter; i++)
	{
		if (strcmp(bookingID, exist[i].bookingID) == 0)
		{
			printf("%10s\t%02d-%02d-%d\t%02d-%02d-%02d\t%02d:%02d - %02d:%02d\t%11s %9s\n", exist[i].bookingID,
				exist[i].currentDate.day, exist[i].currentDate.month, exist[i].currentDate.year,
				exist[i].date.day, exist[i].date.month, exist[i].date.year,
				exist[i].time.shour, exist[i].time.sminute,
				exist[i].time.fhour, exist[i].time.fminute,
				exist[i].userID, exist[i].facilityID);
		}
	}
	printf("\n");
	rewind(stdin);
	printf("Do you want edit? [Y/N]");
	rewind(stdin);
	scanf("%c", &selection);
	while(selection != 'Y' && selection != 'y' && selection != 'N' && selection != 'n')
	{
		printf("Invaild choice,please reenter:");
		rewind(stdin);
		scanf("%c", &selection);
	}
	if (selection == 'y' || selection == 'Y')
	{
		editbooking();
	}
	else if (selection == 'n' || selection == 'N')
	{
		return;
	}

}

//edit all the saved data being key in
void editbooking()
{
	printf("\nEdit Booking\n");
	printf("=================\n");
	FILE* search = fopen("booking.txt", "r");
	FILE* search2 = fopen("facility usage.txt", "r");
	struct BOOKING booking;
	struct BOOKING exist[40];
	facilityUsage exist2[40];
	int counter = 0;
	int counter2 = 0;
	char bookingID[11];
	SYSTEMTIME t;
	GetLocalTime(&t);
	int k = 0;
	while (fscanf(search, "%[^,],%d %d %d,%d %d %d,%d:%d - %d:%d,%[^,],%[^\n]\n",
		&exist[counter].bookingID,
		&exist[counter].currentDate.day, &exist[counter].currentDate.month, &exist[counter].currentDate.year,
		&exist[counter].date.day, &exist[counter].date.month, &exist[counter].date.year,
		&exist[counter].time.shour, &exist[counter].time.sminute,
		&exist[counter].time.fhour, &exist[counter].time.fminute,
		&exist[counter].userID, &exist[counter].facilityID) != EOF)
	{
		counter++;
	}
	fclose(search);
	while (fscanf(search2, "%d,%d,%d\t%d,%d\t%d,%d\t%s\t%s\t%s\n", &exist2[counter2].date.day, &exist2[counter2].date.month, &exist2[counter2].date.year,
		&exist2[counter2].timeFrom.hours, &exist2[counter2].timeFrom.minutes, &exist2[counter2].timeTo.hours, &exist2[counter2].timeTo.minutes,
		&exist2[counter2].userID, &exist2[counter2].facilityID, &exist2[counter2].usageType) != EOF)
	{
		counter2++;
	}
	fclose(search2);
	do {

		printf("Enter the bookingID that want to modify > ");
		rewind(stdin);
		scanf("%s", &bookingID);
		for (k = 0; k < counter; k++) {
			if (strcmp(exist[k].bookingID, bookingID) == 0) {
				booking = exist[k];
				printf("Enter the new user id > ");
				scanf("%s", booking.userID);
				for (int checkFU = 0; checkFU < counter2; checkFU++) {
					if ((strcmp(exist[k].facilityID, exist2[checkFU].facilityID) == 0) && exist[k].date.day == exist2[checkFU].date.day 
						&& exist[k].date.month == exist2[checkFU].date.month && exist[k].date.year == exist2[checkFU].date.year
						&& exist[k].time.shour == exist2[checkFU].timeFrom.hours && exist[k].time.sminute == exist2[checkFU].timeFrom.minutes
						&& exist[k].time.fhour == exist2[checkFU].timeTo.hours && exist[k].time.fminute == exist2[checkFU].timeTo.minutes) {
						strcpy(exist2[checkFU].userID, booking.userID);
					}
				}
				break;
			}
		}
		if (strcmp(exist[k].bookingID, bookingID) != 0) {
			printf("BookingID not found!\n");
		}
	} while (strcmp(exist[k].bookingID, bookingID) != 0);

	FILE* edit = fopen("booking.txt", "w");
	FILE* fptr2 = fopen("facility usage.txt", "w");
	for (int i = 0; i < counter; i++) {
		if (strcmp(exist[i].bookingID, bookingID) != 0) {
			fprintf(edit, "%s,%d %d %d,%d %d %d,%d:%d - %d:%d,%s,%s\n",
				exist[i].bookingID,
				t.wDay, t.wMonth, t.wYear,
				exist[i].date.day, exist[i].date.month, exist[i].date.year,
				exist[i].time.shour, exist[i].time.sminute,
				exist[i].time.fhour, exist[i].time.fminute,
				exist[i].userID, exist[i].facilityID);
		}
		else {
			fprintf(edit, "%s,%d %d %d,%d %d %d,%d:%d - %d:%d,%s,%s\n",
				booking.bookingID,
				t.wDay, t.wMonth, t.wYear,
				booking.date.day, booking.date.month, booking.date.year,
				booking.time.shour, booking.time.sminute,
				booking.time.fhour, booking.time.fminute,
				booking.userID, booking.facilityID);
		}
	}
	fclose(edit);
	for (int checkFU = 0; checkFU < counter2; checkFU++) {
		fprintf(fptr2, "%d,%d,%d\t%d,%d\t%d,%d\t%s\t%s\t%s\n", exist2[checkFU].date.day, exist2[checkFU].date.month, exist2[checkFU].date.year,
			exist2[checkFU].timeFrom.hours, exist2[checkFU].timeFrom.minutes,
			exist2[checkFU].timeTo.hours, exist2[checkFU].timeTo.minutes, exist2[checkFU].userID, exist2[checkFU].facilityID, "booked");
	}
	fclose(fptr2);

}

//showing all saved datas
void showbooking()
{
	printf("\nShow Booking\n");
	printf("=================\n");
	int a = 0, i = 0;
	struct BOOKING exist;
	SYSTEMTIME t;
	GetLocalTime(&t);
	int day, month, year;
	FILE* bk = fopen("Booking.txt", "r");
	printf("BookingID\tCurrent Date\tBooking Date\tBooking Time\t User ID\tFacility ID\n");
	while (fscanf(bk, "%[^,],%d %d %d,%d %d %d,%d:%d - %d:%d,%[^,],%[^\n]\n",
		&exist.bookingID,
		&exist.currentDate.day, &exist.currentDate.month, &exist.currentDate.year,
		&exist.date.day, &exist.date.month, &exist.date.year,
		&exist.time.shour, &exist.time.sminute,
		&exist.time.fhour, &exist.time.fminute,
		&exist.userID, &exist.facilityID) != EOF)
	{
		printf("%10s\t%02d-%02d-%d\t%02d-%02d-%02d\t%02d:%02d - %02d:%02d\t%11s %9s\n", exist.bookingID,
			exist.currentDate.day, exist.currentDate.month, exist.currentDate.year,
			exist.date.day, exist.date.month, exist.date.year,
			exist.time.shour, exist.time.sminute,
			exist.time.fhour, exist.time.fminute,
			exist.userID, exist.facilityID);
	}
	fclose(bk);
	printf("\n");
}

//generate the bookingID
char generateID()
{
	char ID;

	ID = rand() % (10) + 48;
	return ID;
}

