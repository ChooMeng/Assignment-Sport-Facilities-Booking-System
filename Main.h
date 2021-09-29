#include <stdio.h>
#pragma once

/*
===========================
Staff Information Module
Made by: Poh Choo Meng
===========================
*/
typedef struct {
	int day;
	int month;
	int year;
}N_DATE;
typedef struct {
	int hours;
	int minutes;
}TIME;
typedef struct {
	char staffID[6];
	char userName[17];
	char password[17];
	char fullName[31];
	int recoveryQuestionType;
	char recoveryAnswer[31];
	char position[21];
	N_DATE joinDate;
	N_DATE lastLoginDate[10];
	TIME lastLoginTime[10];
}staffAcc;

void install();
int recoveryQuestion(char securityAnswer[31]);
staffAcc login();
void recoveryQuestionValidation(staffAcc existAcc);
void staffMenu(staffAcc currentAcc);
void addAccount();
void removeAccount(staffAcc currentAcc);
void editMenu(staffAcc currentAcc);
void editAccount(int choose, staffAcc currentAcc);
void displayAccount();
void searchMenu();
void searchAccount(int choose);
void viewMenu();
void viewAccount(int choose);
char randomLetter();
char randomNumber();
void updateDB(staffAcc editedAcc);
void removeDB(staffAcc removedAcc);
void lastLogin(staffAcc existAcc);
void displayDetails(staffAcc existAcc);
void sortAcc(staffAcc existAcc[], int counter);

/*
===========================
User Information Module
Made by: William Choong
===========================
*/
typedef struct
{
	int day, month, year;
}UI_date;
typedef struct
{
	int hour, minute, second;
}UI_TIME;
typedef struct {
	char ID[12];
	char name[30];
	char gender;
	char IC[15];
	char contactNumb[15];
	UI_date birthDate, registeredDate;
	UI_TIME registeredTime;
}USER;
void userMenu();
void searchUI();
void addUI();
void modUI();
void editingUI(int choice, USER newData);
void delUI();
void removingUI(USER info);
void dispUI();

/*
===========================
Booking Module
Made by: Chew Wei Chung
===========================
*/
typedef struct
{
	int shour, sminute;
	int fhour, fminute;
}B_TIME;
typedef struct
{
	int year, month, day;
}B_DATE;
struct BOOKING
{
	B_TIME time;
	B_DATE date,currentDate;
	char facilityID[10], bookingID[11], userID[12];
};
void syncFU();
void bookingMenu();
void addbooking();
void searchbooking();
void editbooking();
void showbooking();
char generateID();

/*
===========================
Facility Usage Module
Made by: Choo Zhi Yan
===========================
*/
typedef struct {
	int day;
	int month;
	int year;
}FU_DATE;
typedef struct {
	int hours;
	int minutes;
}FU_TIME;
typedef struct
{
	FU_DATE date;
	FU_TIME timeFrom, timeTo;
	char userID[15];
	char facilityID[7];
	char usageType[15];

}facilityUsage;

void syncB();
void fuMenu();
void displayData();
void addFU();
void displaySearch(facilityUsage search);
void searchFU();
void searchNum();
void searchDate();
void searchTime();
void searchUserID();
void searchFacilityID();
void searchUsageType();
void askAddOrModify();
void modifyFU();
int chooseModifyFU();
int confirmModify();
int checkTime(int timehours, int timeminutes);

/*
===========================
Main Modules
Made by: Poh Choo Meng
===========================
*/
void logo();
void mainMenu(staffAcc currentAcc);
char shutdown();