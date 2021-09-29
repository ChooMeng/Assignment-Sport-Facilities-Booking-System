#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include "Main.h"
#pragma warning (disable:4996)
#pragma warning (disable:6031)
/*
===========================
Main Modules
Made by: Poh Choo Meng
===========================
*/
void main() {
	logo();
	syncB();
	syncFU();
	srand(time(NULL));
	staffAcc currentAcc;
	install();
	currentAcc = login();
	mainMenu(currentAcc);
	system("pause");
}
void logo() {
	printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
	printf("\tTUNKU ABDUL RAHMAN UNIVERSITY COLLEGE\n");
	printf("\t > Sport Facilities Booking System <\n");
	printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
}
void mainMenu(staffAcc currentAcc) {
	int choose;
	char yesorno = 'y';
	do {
		printf("========================================\n");
		printf("\t\tMain Menu\n");
		printf("========================================\n");
		printf("[1] Staff account menu\n");
		printf("[2] User menu\n");
		printf("[3] Booking menu\n");
		printf("[4] Facility usage menu\n");
		printf("[-1] Shutdown\n");
		printf("Press number for selection > ");
		rewind(stdin);
		scanf("%d", &choose);
		system("cls");
		logo();
		if (choose == 1) {
			staffMenu(currentAcc);
			system("cls");
			logo();
		}
		else if (choose == 2) {
			userMenu();
			system("cls");
			logo();
		}
		else if (choose == 3) {
			bookingMenu();
			system("cls");
			logo();
		}
		else if (choose == 4) {
			fuMenu();
			system("cls");
			logo();
		}
		else if (choose == -1){
			yesorno = shutdown();
		}
		else {
			printf("\n\t        [ERROR]\n");
			printf("\t   X INVALID DIGIT X\n\n");
		}
	}while(choose != -1||yesorno !='y');
	exit(0);
}
char shutdown() {
	char yesorno;
	printf("\n*****************************************************************\n");
	printf(" ###### #     # #     # ####### ######   #####  #   #   # ##    #\n");
	printf("#       #     # #     #    #    #     # #     # #  # #  # # #   #\n");
	printf("######  ####### #     #    #    #     # #     # #  # #  # #  #  #\n");
	printf("      # #     # #     #    #    #     # #     #  # # # #  #   # #\n");
	printf("######  #     #  #####     #    ######   #####    #   #   #    ##\n");
	printf("*****************************************************************\n");
	printf("Do you really want to shut down? (Y= yes)/(N=no) > ");
	rewind(stdin);
	scanf("%c", &yesorno);
	do {
		switch (tolower(yesorno)) {
			case 'y':
				return 'y';
				break;
			case 'n':
				system("cls");
				logo();
				printf("\n\t > CANCELLED SHUTDOWN <\n\n");
				return 'n';
				break;
			default:
				printf("\n\t      [ERROR]\n");
				printf("\t X INVALID SELECTION X\n\n");
		}
	} while (yesorno != 'y' && yesorno != 'n');
}