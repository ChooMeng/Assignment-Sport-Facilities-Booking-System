#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <Windows.h>
#include "Main.h"
#pragma warning (disable:4996)
#pragma warning (disable:6031)
#pragma warning (disable:4101)
#pragma warning (disable:6054)

/*
===========================
Staff Information Module
Made by: Poh Choo Meng
===========================
*/
void install() {
	FILE* fOut = fopen("account.bin", "rb");
	if (fOut == NULL) {
		printf("========================================\n");
		printf("\t   First Usage Setup\n");
		printf("========================================\n");
		addAccount();
	}
	else {
		fclose(fOut);
	}
}
// No ERROR AND BUG
int recoveryQuestion(char securityAnswer[31]) {
	int questionType;
	printf("========================================\n");
	printf("\t   Recovery Question\n");
	printf("========================================\n");
	printf("1. Your father middle name\n");
	printf("2. Your mother middle name\n");
	printf("3. Your secondary School\n");
	printf("4. Animal you like the most\n");
	printf("5. Your best friend middle name\n");
	printf("Press number for recovery question type > ");
	scanf("%d", &questionType);
	rewind(stdin);
	while (questionType < 1 || questionType > 5) {
		printf("\n[ERROR] Invalid recovery question type!\n\n");
		printf("Press number for recovery question type > ");
		scanf("%d", &questionType);
		rewind(stdin);
	}
	do {
		switch (questionType) {
		case 1:
			printf("Enter your father middle name > ");
			break;
		case 2:
			printf("Enter your mother middle name > ");
			break;
		case 3:
			printf("Enter your secondary school > ");
			break;
		case 4:
			printf("Enter animal you like the most > ");
			break;
		case 5:
			printf("Enter your best friend middle name > ");
			break;
		}
		scanf("%[^\n]",securityAnswer);
		rewind(stdin);
		if (strlen(securityAnswer) > 30) {
			printf("\n[ERROR] StaffID exceed maximum length(Max Length: 30)\n\n");
		}
	} while (strlen(securityAnswer) > 30);
	return questionType;
}
// No ERROR AND BUG
staffAcc login() {
	char userName[17], password[17], yesorno = 0;
	int error, encryptKey = 21, wrongCounter;
	staffAcc existAcc;
	printf("========================================\n");
	printf("\t\tStaff Login\n");
	printf("========================================\n");
	do {
		FILE* fOut = fopen("account.bin", "rb");
		error = 1;
		printf("Enter UserName to login (Case Sensitive) > ");
		scanf("%[^\n]", &userName);
		rewind(stdin);
		printf("Enter password to login (Case Sensitive) > ");
		scanf("%[^\n]", &password);
		rewind(stdin);
		while (fread(&existAcc, sizeof(existAcc), 1, fOut) != 0) {
			// Validate availability of account
			if (strcmp(existAcc.userName, userName) == 0) {
				error = 0;
				// Encrypt input password
				for (int i = 0; i < strlen(password); i++) {
					password[i] = password[i] ^ encryptKey;
				}
				// Compare input password and exist account password
				if (strcmp(existAcc.password, password) == 0) {
					lastLogin(existAcc);
					system("cls");
					logo();
					printf("\n\t\t--------------------\n");
					printf("\t\t> Login Succesful <\n");
					printf("\t\t--------------------\n\n");
					return existAcc;
				}
				else {
					printf("\n[ERROR] Incorrect Password\n\n");
					printf("Forget password ? (y=yes/n=no) > ");
					scanf("%c", &yesorno);
					rewind(stdin);
					while (tolower(yesorno) != 'y' && tolower(yesorno) != 'n') {
						printf("Forget password ? (y=yes/n=no) > ");
						scanf("%c", &yesorno);
						rewind(stdin);
					}
					if (yesorno == 'y') {
						recoveryQuestionValidation(existAcc);
					}
					error = 2;
				}
			}
		}
		if (error == 1) {
			printf("\n[ERROR] Incorrect UserName\n\n");
		}
		fclose(fOut);
	} while (error > 0);
}
// NO ERROR AND BUG
void recoveryQuestionValidation(staffAcc existAcc) {
	char securityAnswer[31], newPassword[17];
	int questionType, error = 0, wrongCounter = 0, encryptKey = 21, num;
	do {
		error = 0;
		if (wrongCounter > 4) {
			printf("\n[ERROR] Exceed Limit of trying to recover user!\n\n");
			return;
		}
		printf("========================================\n");
		printf("\tRecovery Question\n");
		printf("========================================\n");
		printf("1. Your father middle name\n");
		printf("2. Your mother middle name\n");
		printf("3. Your secondary School\n");
		printf("4. Animal you like the most\n");
		printf("5. Your best friend middle name\n");
		printf("Press number for recovery question type > ");
		scanf("%d", &questionType);
		rewind(stdin);
		while (questionType < 1 || questionType > 5) {
			printf("\n[ERROR] Invalid recovery question type!\n\n");
			printf("Press number for recovery question type > ");
			scanf("%d", &questionType);
			rewind(stdin);
		}
		do {
			switch (questionType) {
			case 1:
				printf("Enter your father middle name > ");
				break;
			case 2:
				printf("Enter your mother middle name > ");
				break;
			case 3:
				printf("Enter your secondary school > ");
				break;
			case 4:
				printf("Enter animal you like the most > ");
				break;
			case 5:
				printf("Enter your best friend middle name > ");
				break;
			}
			scanf("%[^\n]", securityAnswer);
			rewind(stdin);
			if (strlen(securityAnswer) > 30) {
				printf("\n[ERROR] StaffID exceed maximum length(Max Length: 30)\n\n");
			}
		} while (strlen(securityAnswer) > 30);
		if (existAcc.recoveryQuestionType == questionType) {
			for (int i = 0; i < strlen(securityAnswer); i++) {
				securityAnswer[i] = securityAnswer[i] ^ encryptKey;
			}
			if (strcmp(existAcc.recoveryAnswer, securityAnswer) == 0) {
				for (int i = 0; i < 12; i++) {
					num = rand() % (2) + 1;
					if (num == 1) {
						newPassword[i] = randomLetter();
					}
					else {
						newPassword[i] = randomNumber();
					}
				}
				newPassword[12] = '\0';
				printf("Your New Password > %s\n", newPassword);
				for (int i = 0; i < strlen(newPassword); i++) {
					newPassword[i] = newPassword[i] ^ encryptKey;
				}
				strcpy(existAcc.password, newPassword);
				updateDB(existAcc);
				break;
			}
		}
		error = 1;
		wrongCounter++;
		printf("\n[ERROR] Invalid recovery question type/answer!\n\n");
	} while (error > 0);

}
// NO ERROR AND BUG
void staffMenu(staffAcc currentAcc) {
	int choose;
	do {
		printf("========================================\n");
		printf("\t   Staff Account Menu\n");
		printf("========================================\n");
		printf("[1] Add staff account.\n");
		printf("[2] Remove staff account.\n");
		printf("[3] Edit staff account.\n");
		printf("[4] Display all staff account.\n");
		printf("[5] Search staff account.\n");
		printf("[6] View staff account details.\n");
		printf("[-1] Back to main menu.\n");
		printf("Press number for selection > ");
		rewind(stdin);
		scanf("%d", &choose);
		if ((choose <= 0 || choose >= 7) && choose != -1) {
			system("cls");
			logo();
			printf("\n[ERROR] Invalid digit!\n\n");
		}
		system("cls");
		logo();
		switch (choose) {
		case 1:
			printf("========================================\n");
			printf("\t     Account Create\n");
			printf("========================================\n");
			addAccount();
			break;
		case 2:
			removeAccount(currentAcc);
			break;
		case 3:
			editMenu(currentAcc);
			break;
		case 4:
			displayAccount();
			break;
		case 5:
			searchMenu();
			break;
		case 6:
			viewMenu();
			break;
		case -1:
			break;
		}
	} while (choose != -1);
}
// NO ERROR AND BUG
void addAccount() {
	staffAcc newAcc, existAcc[45];
	int counter = 0, error = 0, encryptKey = 21;
	char securityAnswer[31];
	FILE* fOut = fopen("account.bin", "rb");
	if (fOut != NULL) {
		while (fread(&existAcc[counter], sizeof(staffAcc), 1, fOut) != 0) {
			counter++;
		}
		fclose(fOut);
	}
	do {
		error = 0;
		rewind(stdin);
		printf("Enter new account StaffID (S****) > ");
		scanf("%[^\n]", &newAcc.staffID);
		rewind(stdin);
		while (strlen(newAcc.staffID) > 5) {
			printf("\n[ERROR] StaffID exceed maximum length(Max Length: 5)\n\n");
			printf("Enter new account StaffID (S****) > ");
			scanf("%[^\n]", &newAcc.staffID);
			rewind(stdin);
		}
		for (int i = 0; i < counter; i++) {
			if (strcmp(existAcc[i].staffID, newAcc.staffID) == 0) {
				error = 1;
				break;
			}
		}
		if (error == 1) {
			printf("\n[ERROR] That StaffID already exist.\n\n");
		}
	} while (error == 1);
	do {
		error = 0;
		printf("Enter new account UserName > ");
		rewind(stdin);
		scanf("%[^\n]", &newAcc.userName);
		rewind(stdin);
		while (strlen(newAcc.userName) > 16) {
			printf("\n[ERROR] UserName exceed maximum length(Max Length: 16)\n\n");
			printf("Enter new account UserName > ");
			scanf("%[^\n]", &newAcc.userName);
			rewind(stdin);
		}
		for (int i = 0; i < counter; i++) {
			if (strcmp(existAcc[i].userName, newAcc.userName) == 0) {
				error = 1;
				break;
			}
		}
		if (error == 1) {
			printf("\n[ERROR] That Staff UserName already exist.\n\n");
		}
	} while (error == 1);
	do {
		printf("Enter new account Password > ");
		rewind(stdin);
		scanf("%[^\n]", &newAcc.password);
		rewind(stdin);
		if (strlen(newAcc.password) > 16) {
			printf("\n[ERROR] Password exceed maximum length(Max Length: 16)\n\n");
		}
	} while (strlen(newAcc.password) > 16);
	do {
		printf("Enter staff full name > ");
		scanf("%[^\n]", &newAcc.fullName);
		rewind(stdin);
		if (strlen(newAcc.fullName) > 30) {
			printf("\n[ERROR] Fullname exceed maximum length(Max Length: 30)\n\n");
		}
	} while (strlen(newAcc.fullName) > 30);
	do {
		error = 0;
		printf("Enter staff join date (dd/mm/yyyy) > ");
		rewind(stdin);
		scanf("%d/%d/%d", &newAcc.joinDate.day, &newAcc.joinDate.month, &newAcc.joinDate.year);
		rewind(stdin);
		if (newAcc.joinDate.day < 1 || newAcc.joinDate.day > 31) {
			error = 1;
		}
		if (newAcc.joinDate.month < 1 || newAcc.joinDate.month > 12) {
			error = 1;
		}
		if (newAcc.joinDate.year < 1500 || newAcc.joinDate.year > 2200) {
			error = 1;
		}
		if (error == 1) {
			printf("\n[ERROR] Invalid date.\n\n");
		}
	} while (error == 1);
	do {
		printf("Enter new account Position > ");
		rewind(stdin);
		scanf("%[^\n]", &newAcc.position);
		rewind(stdin);
		if (strlen(newAcc.position) > 20) {
			printf("\n[ERROR] Position exceed maximum length(Max Length: 20)\n\n");
		}
	} while (strlen(newAcc.position) > 20);
	// Recovery Security Question System
	newAcc.recoveryQuestionType = recoveryQuestion(securityAnswer);
	// Encrypt new staff login account security answer
	for (int i = 0; i < strlen(securityAnswer); i++) {
		securityAnswer[i] = securityAnswer[i] ^ encryptKey;
	}
	strcpy(newAcc.recoveryAnswer, securityAnswer);
	// Encrypt new staff login account password
	for (int i = 0; i < strlen(newAcc.password); i++) {
		newAcc.password[i] = newAcc.password[i] ^ encryptKey;
	}
	newAcc.lastLoginDate[0].day = 0;
	FILE* fIn = fopen("account.bin", "ab");
	fwrite(&newAcc, sizeof(newAcc), 1, fIn);
	fclose(fIn);
	system("cls");
	logo();
	printf("\n> New account succesful created <\n\n");
}
// NO ERROR AND BUG
void removeAccount(staffAcc currentAcc) {
	char staffID[6], confirmation;
	int counter = 0, error;
	staffAcc existAcc[45];
	FILE* fOut = fopen("account.bin", "rb");
	while (fread(&existAcc[counter], sizeof(staffAcc), 1, fOut) != 0) {
		counter++;
	}
	fclose(fOut);
	printf("========================================\n");
	printf("\t     Account Remove\n");
	printf("========================================\n");
	do {
		error = 1;
		printf("Enter Staff ID of the account to be deleted (-1 to cancel) > ");
		rewind(stdin);
		scanf("%[^\n]", &staffID);
		rewind(stdin);
		while (strlen(staffID) > 5) {
			printf("\n[ERROR] StaffID exceed maximum length(Max Length: 5)\n\n");
			printf("Enter Staff ID of the account to be deleted (-1 to cancel) > ");
			scanf("%[^\n]", &staffID);
			rewind(stdin);
		}
		if (strcmp(staffID, "-1") == 0) {
			system("cls");
			logo();
			printf("\n> Cancelled account removing <\n\n");
			return;
		}
		if (strcmp(currentAcc.staffID, staffID) == 0) {
			error = 2;
		}
		if (error == 1) {
			for (int i = 0; i < counter; i++) {
				if (strcmp(existAcc[i].staffID, staffID) == 0) {
					error = 0;
					printf("Are you sure you want delete this account? (Y=yes/N=no) > ");
					scanf("%c", &confirmation);
					rewind(stdin);
					while (tolower(confirmation) != 'y' && tolower(confirmation) != 'n') {
						printf("\n[ERROR] Invalid! Type (Y=yes/N=no)\n\n");
						printf("Are you sure you want delete this account? (Y=yes/N=no) > ");
						scanf("%c", &confirmation);
						rewind(stdin);
					}
					if (tolower(confirmation) == 'y') {
						removeDB(existAcc[i]);
						system("cls");
						logo();
						printf("\n> Account succesful removed <\n\n");
					}
					if (tolower(confirmation) == 'n') {
						system("cls");
						logo();
						printf("\n> Cancelled account removing <\n\n");
					}
					break;
				}
			}
		}
		if (error == 1) {
			printf("\n[ERROR] That StaffID not exist.\n\n");
		}
		if (error == 2) {
			printf("\n[ERROR] You cannot remove your own account.\n\n");
		}
	} while (error > 0);

}
// NO ERROR AND BUG
void editMenu(staffAcc currentAcc) {
	int choose;
	do {
		printf("========================================\n");
		printf("\t    Edit Account Menu\n");
		printf("========================================\n");
		printf("[1] Edit UserName\n");
		printf("[2] Edit Password\n");
		printf("[3] Edit FullName\n");
		printf("[4] Edit Join Date\n");
		printf("[5] Edit Recovery Question\n");
		printf("[6] Edit Position\n");
		printf("[7] Edit All\n");
		printf("[-1] Back to staff account menu\n");
		printf("Press number for selection > ");
		rewind(stdin);
		scanf("%d", &choose);
		if (choose > 0 && choose < 8) {
			system("cls");
			logo();
			editAccount(choose, currentAcc);
		}
		else if (choose != -1) {
			system("cls");
			logo();
			printf("\n[ERROR] Invalid digit.\n\n");
		}
	} while (choose != -1);
	system("cls");
	logo();
}
// NO ERROR AND BUG
void editAccount(int choose, staffAcc currentAcc) {
	char staffID[6], confirmation, securityAnswer[31];
	staffAcc modifyAcc, existAcc[45];
	int counter = 0, error, encryptKey = 21;
	FILE* fOut = fopen("account.bin", "rb");
	while (fread(&existAcc[counter], sizeof(staffAcc), 1, fOut) != 0) {
		counter++;
	}
	rewind(stdin);
	do {
		error = 1;
		printf("Enter Staff ID of the account to be modified (-1 to cancel) > ");
		rewind(stdin);
		scanf("%[^\n]", &staffID);
		rewind(stdin);
		while (strlen(staffID) > 5) {
			printf("\n[ERROR] StaffID exceed maximum length(Max Length: 5)\n\n");
			printf("Enter Staff ID of the account to be modified (-1 to cancel) > ");
			scanf("%[^\n]", &staffID);
			rewind(stdin);
		}
		if (strcmp(staffID, "-1") == 0) {
			system("cls");
			logo();
			printf("\n> Cancelled account modifying.<\n\n");
			return;
		}
		if (error == 1) {
			for (int i = 0; i < counter; i++) {
				if (strcmp(existAcc[i].staffID, staffID) == 0) {
					modifyAcc = existAcc[i];
					error = 0;
					break;
				}
			}
		}
		if (error == 1) {
			printf("\n[ERROR] That StaffID not exist.\n\n");
		}
	} while (error > 0);
	if (choose == 1 || choose == 7) {
		do {
			error = 0;
			printf("Enter new Username (-1 to cancel) > ");
			scanf("%[^\n]", modifyAcc.userName);
			rewind(stdin);
			while (strlen(modifyAcc.userName) > 16) {
				printf("\n[ERROR] Username exceed maximum length(Max Length: 16)\n\n");
				printf("Enter new Username (-1 to cancel) > ");
				scanf("%[^\n]", modifyAcc.userName);
				rewind(stdin);
			}
			if (strcmp(modifyAcc.userName, "-1") == 0) {
				system("cls");
				logo();
				printf("\n> Cancelled account modifying.<\n\n");
				return;
			}
			for (int i = 0; i < counter; i++) {
				if (strcmp(existAcc[i].userName, modifyAcc.userName) == 0) {
					error = 1;
					break;
				}
			}
			if (error == 1) {
				printf("\n[ERROR] That Staff UserName already exist.\n\n");
			}
		} while (error == 1);
	}
	if (choose == 2 || choose == 7) {
		printf("Enter new Password (-1 to cancel) > ");
		scanf("%[^\n]", modifyAcc.password);
		rewind(stdin);
		// Check the length of password
		while (strlen(modifyAcc.password) > 16) {
			printf("\n[ERROR] Password exceed maximum length(Max Length: 16)\n\n");
			printf("Enter new account Password (-1 to cancel) > ");
			scanf("%[^\n]", &modifyAcc.password);
			rewind(stdin);
		}
		if (strcmp(modifyAcc.password, "-1") == 0) {
			system("cls");
			logo();
			printf("\n> Cancelled account modifying.<\n\n");
			return;
		}
		// Encrypt account password
		for (int i = 0; i < strlen(modifyAcc.password); i++) {
			modifyAcc.password[i] = modifyAcc.password[i] ^ encryptKey;
		}

	}
	if (choose == 3 || choose == 7) {
		printf("Enter new staff FullName (-1 to cancel) > ");
		scanf("%[^\n]", modifyAcc.fullName);
		rewind(stdin);
		while (strlen(modifyAcc.fullName) > 30) {
			printf("\n[ERROR] FullName exceed maximum length(Max Length: 30)\n\n");
			printf("Enter new staff FullName (-1 to cancel) > ");
			scanf("%[^\n]", &modifyAcc.fullName);
			rewind(stdin);
		}
		if (strcmp(modifyAcc.fullName, "-1") == 0) {
			system("cls");
			logo();
			printf("\n> Cancelled account modifying.<\n\n");
			return;
		}

	}
	if (choose == 4 || choose == 7) {
		do {
			error = 0;
			printf("Enter new JoinDate (dd/mm/yyyy) (-1 to cancel) > ");
			rewind(stdin);
			scanf("%d/%d/%d", &modifyAcc.joinDate.day, &modifyAcc.joinDate.month, &modifyAcc.joinDate.year);
			rewind(stdin);
			if (modifyAcc.joinDate.day == -1) {
				system("cls");
				logo();
				printf("\n> Cancelled account modifying.<\n\n");
				return;
			}
			if (modifyAcc.joinDate.day < 1 || modifyAcc.joinDate.day > 31) {
				error = 1;
			}
			if (modifyAcc.joinDate.month < 1 || modifyAcc.joinDate.month > 12) {
				error = 1;
			}
			if (modifyAcc.joinDate.year < 1500 || modifyAcc.joinDate.year > 2200) {
				error = 1;
			}
			if (error == 1) {
				printf("\n[ERROR] Invalid date.\n\n");
			}
		} while (error == 1);

	}
	if (choose == 5 || choose == 7) {
		// Recovery Security Question System
		modifyAcc.recoveryQuestionType = recoveryQuestion(securityAnswer);
		// Encrypt security question answer
		for (int i = 0; i < strlen(securityAnswer); i++) {
			securityAnswer[i] = securityAnswer[i] ^ encryptKey;
		}
		strcpy(modifyAcc.recoveryAnswer, securityAnswer);
		rewind(stdin);
	}
	if (choose == 6 || choose == 7) {
		do {
			printf("Enter new account Position (-1 to cancel) > ");
			scanf("%[^\n]", &modifyAcc.position);
			rewind(stdin);
			if (strlen(modifyAcc.position) > 20) {
				printf("\n[ERROR] Position exceed maximum length(Max Length: 20)\n\n");
			}
		} while (strlen(modifyAcc.position) > 20);
		if (strcmp(modifyAcc.position, "-1") == 0) {
			system("cls");
			logo();
			printf("\n> Cancelled account modifying.<\n\n");
			return;
		}
	}
	updateDB(modifyAcc);
	system("cls");
	logo();
	printf("\n> Account succesful modified <\n\n");
	fclose(fOut);
}
// NO ERROR AND BUG
void displayAccount() {
	FILE* fOut = fopen("account.bin", "rb");
	staffAcc existAcc[45];
	int counter = 0;
	while (fread(&existAcc[counter], sizeof(existAcc[counter]), 1, fOut) != 0) {
		counter++;
	}
	fclose(fOut);
	sortAcc(existAcc, counter);
	printf("---------------------------------------------------------------------------------------------------------------------\n");
	printf("StaffID\t|User Name\t\t|Full Name\t\t\t|Position\t        |Join Date  |Last Login\n");
	printf("---------------------------------------------------------------------------------------------------------------------\n");
	for (int i = 0; i < counter; i++) {
		printf(" %-5s\t|%-16s\t|%-30s\t|%-20s\t|%02d/%02d/%d |", existAcc[i].staffID, existAcc[i].userName, existAcc[i].fullName, existAcc[i].position,
			existAcc[i].joinDate.day, existAcc[i].joinDate.month, existAcc[i].joinDate.year);
		if (existAcc[i].lastLoginDate[0].day == 0) {
			printf("No Login Before\n");
		}
		else {
			printf("%02d/%02d/%d %02d:%02d\n", existAcc[i].lastLoginDate[0].day, existAcc[i].lastLoginDate[0].month,
				existAcc[i].lastLoginDate[0].year, existAcc[i].lastLoginTime[0].hours, existAcc[i].lastLoginTime[0].minutes);
		}
	}
	printf("---------------------------------------------------------------------------------------------------------------------\n");
	system("pause");
	system("cls");
	logo();
}
void searchMenu() {
	int choose;
	do {
		printf("========================================\n");
		printf("\t   Search Account Menu\n");
		printf("========================================\n");
		printf("[1] Search by join date\n");
		printf("[2] Search by recovery question type\n");
		printf("[3] Search by position\n");
		printf("[4] Search by last login\n");
		printf("[-1] Back to staff account menu\n");
		printf("Press number for selection > ");
		scanf("%d", &choose);
		rewind(stdin);
		if (choose > 0 && choose < 5) {
			system("cls");
			logo();
			searchAccount(choose);
		}
		else if (choose != -1) {
			system("cls");
			logo();
			printf("\n[ERROR] Invalid digit.\n\n");
		}
	} while (choose != -1);
	system("cls");
	logo();
}
void searchAccount(int choose) {
	char position[21];
	N_DATE joinDate, lastLoginDate;
	int recoveryQuestionType;
	staffAcc existAcc[45];
	int counter = 0;
	int error = 0;
	FILE* fOut = fopen("account.bin", "rb");
	while (fread(&existAcc[counter], sizeof(staffAcc), 1, fOut) != 0) {
		counter++;
	}
	fclose(fOut);
	switch (choose) {
	case 1:
		do {
			error = 0;
			printf("Join Date to search (mm/yyyy) (-1 to cancel) > ");
			rewind(stdin);
			scanf("%d/%d", &joinDate.month, &joinDate.year);
			rewind(stdin);
			if (joinDate.month == -1) {
				printf("\n> Cancelled account searching.<\n\n");
				return;
			}
			error = 0;
			if (joinDate.month < 1 || joinDate.month > 12) {
				error = 1;
			}
			if (joinDate.year < 1500 || joinDate.year > 2200) {
				error = 1;
			}
			if (error == 1) {
				printf("\n[ERROR] Invalid date.\n\n");
			}
		} while (error == 1);
		error = 0;
		sortAcc(existAcc, counter);
		printf("---------------------------------------------------------------------------------------------------------------------\n");
		printf("StaffID\t|User Name\t\t|Full Name\t\t\t|Position\t        |Join Date  |Last Login\n");
		printf("---------------------------------------------------------------------------------------------------------------------\n");
		for (int i = 0; i < counter; i++) {
			if (existAcc[i].joinDate.month == joinDate.month && existAcc[i].joinDate.year == joinDate.year) {
				printf(" %-5s\t|%-16s\t|%-30s\t|%-20s\t|%02d/%02d/%d |", existAcc[i].staffID, existAcc[i].userName, existAcc[i].fullName, existAcc[i].position,
					existAcc[i].joinDate.day, existAcc[i].joinDate.month, existAcc[i].joinDate.year);
				if (existAcc[i].lastLoginDate[0].day == 0) {
					printf("No Login Before\n");
				}
				else {
					printf("%02d/%02d/%d %02d:%02d\n", existAcc[i].lastLoginDate[0].day, existAcc[i].lastLoginDate[0].month,
						existAcc[i].lastLoginDate[0].year, existAcc[i].lastLoginTime[0].hours, existAcc[i].lastLoginTime[0].minutes);
				}
				error = 1;
			}
		}
		if (error == 0) {
			printf("\t\t\t\t        > NO RESULT FOUND <       \t\t\t\t\n");
		}
		printf("---------------------------------------------------------------------------------------------------------------------\n");
		system("pause");
		break;
	case 2:
		printf("1. Your father middle name\n");
		printf("2. Your mother middle name\n");
		printf("3. Your secondary School\n");
		printf("4. Animal you like the most\n");
		printf("5. Your best friend middle name\n");
		printf("Recovery question type to search (-1 to cancel) > ");
		rewind(stdin);
		scanf("%d", &recoveryQuestionType);
		while (recoveryQuestionType < 1 || recoveryQuestionType > 5) {
			printf("\n[ERROR] Invalid recovery question type!\n\n");
			printf("Recovery question type to search (-1 to cancel) > ");
			scanf("%d", &recoveryQuestionType);
			rewind(stdin);
		}
		if (recoveryQuestionType == -1) {
			printf("\n> Cancelled account searching.<\n\n");
			return;
		}
		sortAcc(existAcc, counter);
		printf("---------------------------------------------------------------------------------------------------------------------\n");
		printf("StaffID\t|User Name\t\t|Full Name\t\t\t|Position\t        |Join Date  |Last Login\n");
		printf("---------------------------------------------------------------------------------------------------------------------\n");
		for (int i = 0; i < counter; i++) {
			if (existAcc[i].recoveryQuestionType == recoveryQuestionType) {
				printf(" %-5s\t|%-16s\t|%-30s\t|%-20s\t|%02d/%02d/%d |", existAcc[i].staffID, existAcc[i].userName, existAcc[i].fullName, existAcc[i].position,
					existAcc[i].joinDate.day, existAcc[i].joinDate.month, existAcc[i].joinDate.year);
				if (existAcc[i].lastLoginDate[0].day == 0) {
					printf("No Login Before\n");
				}
				else {
					printf("%02d/%02d/%d %02d:%02d\n", existAcc[i].lastLoginDate[0].day, existAcc[i].lastLoginDate[0].month,
						existAcc[i].lastLoginDate[0].year, existAcc[i].lastLoginTime[0].hours, existAcc[i].lastLoginTime[0].minutes);
				}
				error = 1;
			}
		}
		if (error == 0) {
			printf("\t\t\t\t       > NO RESULT FOUND <       \t\t\t\t\n");
		}
		printf("---------------------------------------------------------------------------------------------------------------------\n");
		system("pause");
		break;
	case 3:
		do {
			printf("Position to search (-1 to cancel) > ");
			rewind(stdin);
			scanf("%[^\n]", position);
			rewind(stdin);
			if (strlen(position) > 20) {
				printf("\n[ERROR] Position exceed maximum length(Max Length: 20)\n\n");
				printf("Position to search (-1 to cancel) > ");
				scanf("%[^\n]", position);
				rewind(stdin);
			}
			if (strcmp(position, "-1") == 0) {
				printf("\n> Cancelled account searching.<\n\n");
				return;
			}
		} while (strlen(position) > 20);
		sortAcc(existAcc, counter);
		printf("---------------------------------------------------------------------------------------------------------------------\n");
		printf("StaffID\t|User Name\t\t|Full Name\t\t\t|Position\t        |Join Date  |Last Login\n");
		printf("---------------------------------------------------------------------------------------------------------------------\n");
		for (int i = 0; i < counter; i++) {
			if (strcmp(existAcc[i].position, position) == 0) {
				printf(" %-5s\t|%-16s\t|%-30s\t|%-20s\t|%02d/%02d/%d |", existAcc[i].staffID, existAcc[i].userName, existAcc[i].fullName, existAcc[i].position,
					existAcc[i].joinDate.day, existAcc[i].joinDate.month, existAcc[i].joinDate.year);
				if (existAcc[i].lastLoginDate[0].day == 0) {
					printf("No Login Before\n");
				}
				else {
					printf("%02d/%02d/%d %02d:%02d\n", existAcc[i].lastLoginDate[0].day, existAcc[i].lastLoginDate[0].month,
						existAcc[i].lastLoginDate[0].year, existAcc[i].lastLoginTime[0].hours, existAcc[i].lastLoginTime[0].minutes);
				}
				error = 1;
			}
		}
		if (error == 0) {
			printf("\t\t\t\t       > NO RESULT FOUND <       \t\t\t\t\n");
		}
		printf("---------------------------------------------------------------------------------------------------------------------\n");
		system("pause");
		break;
	case 4:
		do {
			printf("Last Login to search (mm/yyyy) (-1 to cancel) > ");
			rewind(stdin);
			scanf("%d/%d", &lastLoginDate.month, &lastLoginDate.year);
			rewind(stdin);
			sortAcc(existAcc, counter);
			if (lastLoginDate.month == -1) {
				printf("\n> Cancelled account searching.<\n\n");
				return;
			}
			error = 0;
			if (lastLoginDate.month < 1 || lastLoginDate.month > 12) {
				error = 1;
			}
			if (lastLoginDate.year < 1500 || lastLoginDate.year > 2200) {
				error = 1;
			}
			if (error == 1) {
				printf("\n[ERROR] Invalid date.\n\n");
			}
		} while (error == 1);
		printf("---------------------------------------------------------------------------------------------------------------------\n");
		printf("StaffID\t|User Name\t\t|Full Name\t\t\t|Position\t        |Join Date  |Last Login\n");
		printf("---------------------------------------------------------------------------------------------------------------------\n");
		for (int i = 0; i < counter; i++) {
			if (existAcc[i].lastLoginDate[0].month == lastLoginDate.month && existAcc[i].lastLoginDate[0].year == lastLoginDate.year) {
				printf(" %-5s\t|%-16s\t|%-30s\t|%-20s\t|%02d/%02d/%d |", existAcc[i].staffID, existAcc[i].userName, existAcc[i].fullName, existAcc[i].position,
					existAcc[i].joinDate.day, existAcc[i].joinDate.month, existAcc[i].joinDate.year);
				if (existAcc[i].lastLoginDate[0].day == 0) {
					printf("No Login Before\n");
				}
				else {
					printf("%02d/%02d/%d %02d:%02d\n", existAcc[i].lastLoginDate[0].day, existAcc[i].lastLoginDate[0].month,
						existAcc[i].lastLoginDate[0].year, existAcc[i].lastLoginTime[0].hours, existAcc[i].lastLoginTime[0].minutes);
				}
				error = 1;
			}
		}
		if (error == 0) {
			printf("\t\t\t\t       > NO RESULT FOUND <       \t\t\t\t\n");
		}
		printf("---------------------------------------------------------------------------------------------------------------------\n");
		system("pause");
		break;
	case -1:
		system("cls");
		logo();
		return;
		break;
	}
	system("cls");
	logo();
}
void viewMenu() {
	int choose;
	do {
		printf("========================================\n");
		printf("\t   View Account Menu\n");
		printf("========================================\n");
		printf("[1] View by StaffID\n");
		printf("[2] View by UserName\n");
		printf("[3] View by FullName\n");
		printf("[-1] Back to staff account menu\n");
		printf("Press number for selection > ");
		scanf("%d", &choose);
		rewind(stdin);
		if (choose > 0 && choose < 4) {
			system("cls");
			logo();
			viewAccount(choose);
		}
		else if (choose != -1) {
			system("cls");
			logo();
			printf("\n[ERROR] Invalid digit.\n\n");
		}
	} while (choose != -1);
	system("cls");
	logo();
}
void viewAccount(int choose) {
	char staffID[6], userName[17], fullName[31];
	staffAcc existAcc[45];
	int counter = 0, error = 0;
	FILE* fOut = fopen("account.bin", "rb");
	while (fread(&existAcc[counter], sizeof(staffAcc), 1, fOut) != 0) {
		counter++;
	}
	fclose(fOut);
	if (choose == 1) {
		rewind(stdin);
		printf("Enter Staff ID to view (-1 to cancel) > ");
		scanf("%[^\n]", &staffID);
		rewind(stdin);
		while (strlen(staffID) > 5) {
			printf("\n[ERROR] StaffID exceed maximum length(Max Length: 5)\n\n");
			printf("Enter Staff ID to view (-1 to cancel) > ");
			scanf("%[^\n]", &staffID);
			rewind(stdin);
		}
		if (strcmp(staffID, "-1") == 0) {
			system("cls");
			logo();
			printf("\n> Cancelled account viewing <\n\n");
			return;
		}
		for (int i = 0; i < counter; i++) {
			if (strcmp(existAcc[i].staffID, staffID) == 0) {
				system("cls");
				logo();
				displayDetails(existAcc[i]);
				return;
			}
		}
	}
	else if (choose == 2) {
		printf("Enter UserName to view (-1 to cancel) > ");
		rewind(stdin);
		scanf("%[^\n]", &userName);
		rewind(stdin);
		while (strlen(userName) > 16) {
			printf("\n[ERROR] UserName exceed maximum length(Max Length: 16)\n\n");
			printf("Enter UserName to view (-1 to cancel) > ");
			scanf("%[^\n]", &userName);
			rewind(stdin);
		}
		if (strcmp(userName, "-1") == 0) {
			system("cls");
			logo();
			printf("\n> Cancelled account viewing <\n\n");
			return;
		}
		for (int i = 0; i < counter; i++) {
			if (strcmp(existAcc[i].userName, userName) == 0) {
				system("cls");
				logo();
				displayDetails(existAcc[i]);
				return;
			}
		}
	}
	else {
		do {
			printf("Enter Staff FullName to view (-1 to cancel) > ");
			rewind(stdin);
			scanf("%[^\n]", &fullName);
			rewind(stdin);
			if (strlen(fullName) > 30) {
				printf("\n[ERROR] Fullname exceed maximum length(Max Length: 30)\n\n");
			}
		} while (strlen(fullName) > 30);
		if (strcmp(fullName, "-1") == 0) {
			system("cls");
			logo();
			printf("\n> Cancelled account viewing <\n\n");
			return;
		}
		for (int i = 0; i < counter; i++) {
			if (strcmp(existAcc[i].fullName, fullName) == 0) {
				system("cls");
				logo();
				displayDetails(existAcc[i]);
				return;
			}
		}
	}
	if (error == 0) {
		system("cls");
		logo();
		printf("\n[ERROR] Result not found.\n\n");
	}
}

/*
======================
	  Sub System
======================
*/
// Generate random letter
char randomLetter() {
	char letter;
	letter = rand() % (26) + 97;
	return letter;
}
// Generate random number
char randomNumber() {
	char letter;
	letter = rand() % (10) + 48;
	return letter;
}
// Update database for modified data
void updateDB(staffAcc editedAcc) {
	FILE* pOut = fopen("account.bin", "rb");
	int counter = 0;
	staffAcc backupAcc[45];
	while (fread(&backupAcc[counter], sizeof(backupAcc[counter]), 1, pOut) != 0) {
		counter++;
	}
	fclose(pOut);
	FILE* pIn = fopen("account.bin", "wb");
	for (int i = 0; i < counter; i++) {
		if (strcmp(editedAcc.staffID, backupAcc[i].staffID) == 0) {
			backupAcc[i] = editedAcc;
		}
		fwrite(&backupAcc[i], sizeof(backupAcc[i]), 1, pIn);
	}
	fclose(pIn);
}
// Remove data from database
void removeDB(staffAcc removedAcc) {
	FILE* pOut = fopen("account.bin", "rb");
	int counter = 0;
	staffAcc backupAcc[45];
	while (fread(&backupAcc[counter], sizeof(staffAcc), 1, pOut) != 0) {
		counter++;
	}
	fclose(pOut);
	FILE* pIn = fopen("account.bin", "wb");
	for (int i = 0; i < counter; i++) {
		if (!(strcmp(removedAcc.staffID, backupAcc[i].staffID) == 0)) {
			fwrite(&backupAcc[i], sizeof(backupAcc[i]), 1, pIn);
		}
	}
	fclose(pIn);
}
void lastLogin(staffAcc existAcc) {
	SYSTEMTIME t;
	staffAcc modifyAcc = existAcc;
	GetLocalTime(&t);
	for (int i = 0; existAcc.lastLoginDate[i].day > 0 && i < 8 && existAcc.lastLoginDate[i].day < 32; i++) {
		modifyAcc.lastLoginDate[i + 1].day = existAcc.lastLoginDate[i].day;
		modifyAcc.lastLoginDate[i + 1].month = existAcc.lastLoginDate[i].month;
		modifyAcc.lastLoginDate[i + 1].year = existAcc.lastLoginDate[i].year;
		modifyAcc.lastLoginTime[i + 1].hours = existAcc.lastLoginTime[i].hours;
		modifyAcc.lastLoginTime[i + 1].minutes = existAcc.lastLoginTime[i].minutes;
	}
	modifyAcc.lastLoginDate[0].day = t.wDay;
	modifyAcc.lastLoginDate[0].month = t.wMonth;
	modifyAcc.lastLoginDate[0].year = t.wYear;
	modifyAcc.lastLoginTime[0].hours = t.wHour;
	modifyAcc.lastLoginTime[0].minutes = t.wMinute;
	updateDB(modifyAcc);
}
void displayDetails(staffAcc existAcc) {
	int encryptKey = 21;
	printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
	printf("\t\t   Account Details\n");
	printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
	printf("\tStaff ID\t\t: %s\n", existAcc.staffID);
	printf("\tStaff UserName\t\t: %s\n", existAcc.userName);
	printf("\tStaff FullName\t\t: %s\n", existAcc.fullName);
	printf("\tStaff Position\t\t: %s\n", existAcc.position);
	printf("\tRecovery Question Type\t: ");
	switch (existAcc.recoveryQuestionType) {
	case 1:
		printf("Father Middle Name\n");
		break;
	case 2:
		printf("Mother Middle Name\n");
		break;
	case 3:
		printf("Secondary School\n");
		break;
	case 4:
		printf("Animal Type\n");
		break;
	case 5:
		printf("Best Friend Middle Name\n");
		break;
	}
	for (int i = 0; i < strlen(existAcc.recoveryAnswer); i++) {
		existAcc.recoveryAnswer[i] = existAcc.recoveryAnswer[i] ^ encryptKey;
	}
	printf("\tRecovery Question Answer: %s\n", existAcc.recoveryAnswer);
	printf("\tJoin Date\t\t: %0d-%0d-%d\n", existAcc.joinDate.day, existAcc.joinDate.month, existAcc.joinDate.year);
	printf("\tLogin Log\t\t: \n");
	for (int i = 8; existAcc.lastLoginDate[i].day > 0 && i > -1 && existAcc.lastLoginDate[i].day < 32; i--) {
		printf("\t- %02d/%02d/%d %02d:%02d\n", existAcc.lastLoginDate[i].day, existAcc.lastLoginDate[i].month,
			existAcc.lastLoginDate[i].year, existAcc.lastLoginTime[i].hours, existAcc.lastLoginTime[i].minutes);
	}
	printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
	system("pause");
	system("cls");
	logo();
}
void sortAcc(staffAcc existAcc[], int counter) {
	staffAcc temp;
	char tempStaffID[6], tempName[31], tempPosition[23];
	int choose;
	do {
		printf("========================================\n");
		printf("\t    Select Sort Type\n");
		printf("========================================\n");
		printf("[1] Sort by StaffID\n");
		printf("[2] Sort by UserName\n");
		printf("[3] Sort by FullName\n");
		printf("[4] Sort by Position\n");
		printf("[5] Sort by Join Date\n");
		printf("[-1] Do not sort\n");
		printf("Press number for selection > ");
		rewind(stdin);
		scanf("%d", &choose);
		if (choose > 0 && choose < 6) {
			for (int i = 0; i < counter - 1; i++) {
				for (int i2 = i + 1; i2 < counter; i2++) {
					if (choose == 1) {
						if (strcmp(existAcc[i2].staffID, existAcc[i].staffID) < 0) {
							temp = existAcc[i];
							existAcc[i] = existAcc[i2];
							existAcc[i2] = temp;
						}
					}
					else if (choose == 2) {
						if (strcmp(existAcc[i2].userName, existAcc[i].userName) < 0) {
							temp = existAcc[i];
							existAcc[i] = existAcc[i2];
							existAcc[i2] = temp;
						}
					}
					else if (choose == 3) {
						if (strcmp(existAcc[i2].fullName, existAcc[i].fullName) < 0) {
							temp = existAcc[i];
							existAcc[i] = existAcc[i2];
							existAcc[i2] = temp;
						}
					}
					else if (choose == 4) {
						if (strcmp(existAcc[i2].position, existAcc[i].position) < 0) {
							temp = existAcc[i];
							existAcc[i] = existAcc[i2];
							existAcc[i2] = temp;
						}
					}
					else if (choose == 5) {
						if (existAcc[i2].joinDate.day < existAcc[i].joinDate.day) {
							temp = existAcc[i];
							existAcc[i] = existAcc[i2];
							existAcc[i2] = temp;
						}
						if (existAcc[i2].joinDate.month < existAcc[i].joinDate.month) {
							temp = existAcc[i];
							existAcc[i] = existAcc[i2];
							existAcc[i2] = temp;
						}
						if (existAcc[i2].joinDate.year < existAcc[i].joinDate.year) {
							temp = existAcc[i];
							existAcc[i] = existAcc[i2];
							existAcc[i2] = temp;
						}
					}
				}
			}
		}
		else if (choose != -1) {
			system("cls");
			logo();
			printf("[ERROR] Invalid digit.\n");
		}
	} while (!(choose == -1 || (choose > 0 && choose < 6)));
	system("cls");
	logo();
}
