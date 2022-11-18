/* -------------------------------------------
Name: Serach Boes
Date: November, 20, 2018
---------------------------------------------- */

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "contactHelpers.h"

#define MAXCONTACTS 5

// Function Definitions

// clearKeyboard:

void clearKeyboard(void)
{
	while (getchar() != '\n'); // empty execution code block on purpose

}

// pause:

void pause(void) {

	printf("(Press Enter to Continue)");
	clearKeyboard();
}

// getInt:

int getInt(void) {

	int value;
	char NL = 'x';
	do {
		scanf("%d%c", &value, &NL);
		if (NL != '\n') {
			clearKeyboard();
			printf("*** INVALID INTEGER *** <Please enter an integer>: ");
		}
	} while (NL != '\n');
	return value;
}


// getIntInRange:

int getIntInRange(int min, int max) {

	int value;
	do {
		value = getInt();
		if (value < min || value > max)
		{
			printf("*** OUT OF RANGE *** <Enter a number between %d and %d>: ", min, max);
		}
	} while (value < min || value > max);
	return value;
}

// yes:

int yes(void) {

	char NL = 'x';
	char letter;
	int value = 2;

	do {
		scanf("%c%c", &letter, &NL);
		if (NL != '\n') {
			clearKeyboard();
			printf("*** INVALID ENTRY *** <Only (Y)es or (N)o are acceptable>: ");
		}
		else if (NL == '\n') {
			if (letter == 'Y' || letter == 'y') {
				value = 1;
			}
			else if (letter == 'N' || letter == 'n') {

				value = 0;
			}
		}
	} while (value != 1 && value != 0);
	return value;
}

// menu:

int menu(void) {

	int value;
	printf("Contact Management System\n");
	printf("-------------------------\n");
	printf("1. Display contacts\n");
	printf("2. Add a contact\n");
	printf("3. Update a contact\n");
	printf("4. Delete a contact\n");
	printf("5. Search contacts by cell phone number\n");
	printf("6. Sort contacts by cell phone number\n");
	printf("0. Exit\n");
	printf("\nSelect an option:> ");
	value = getIntInRange(0, 6);
	return value;
}

// contactManagerSystem:

void contactManagerSystem(void) {

	struct Contact names[MAXCONTACTS] =
	{ { { "Rick",{'\0'},"Grimes" },
		{ 11, "Trailer Park", 0, "A7A 2J2", "King City" },
		{ "4161112222", "4162223333", "4163334444" } },
	{ { "Maggie", "R.", "Greene" },
	{ 55, "Hightop House", 0, "A9A 3K3", "Bolton" },
	{ "9051112222", "9052223333", "9053334444" } },
	{ { "Morgan", "A.", "Jones" },
	{ 77, "Cottage Lane", 0, "C7C 9Q9", "Peterborough" },
	{ "7051112222", "7052223333", "7053334444" } },
	{ { "Sasha", { '\0' }, "Williams" },
	{ 55, "Hightop House", 0, "A9A 3K3", "Bolton" },
	{ "9052223333", "9052223333", "9054445555" } }
	};

	int exit = 1;
	while (exit != 0)
	{
		int selection = menu();
		switch (selection)
		{
		case 0:
			printf("\nExit the program? (Y)es/(N)o: ");
			if (yes() == 1)
			{
				printf("\nContact Management System: terminated\n");
				exit = 0;
			}
			else
			{
				printf("\n");
				exit = 1;
			}
			break;

		case 1:
			displayContacts(names, MAXCONTACTS);
			pause();
			printf("\n");
			break;
		case 2:
			addContact(names, MAXCONTACTS);
			pause();
			printf("\n");
			break;
		case 3:
			updateContact(names, MAXCONTACTS);
			pause();
			printf("\n");
			break;
		case 4:
			deleteContact(names, MAXCONTACTS);
			pause();
			printf("\n");
			break;
		case 5:
			searchContacts(names, MAXCONTACTS);
			pause();
			printf("\n");
			break;
		case 6:
			sortContacts(names, MAXCONTACTS);
			pause();
			printf("\n");
			break;
		}
	}
}

// getTenDigitPhone:

void getTenDigitPhone(char telNum[])
{
	int needInput = 1;
	int letter = 1;
	int i;

	while (needInput == 1 || letter == 0) {

		//validate that entry is only numerical
		for (i = 0; i < strlen(telNum); i++) {
			if (telNum[i] < '0' || telNum[i] > '9')
				letter = 0;
		}

		// (String Length Function: validate entry of 10 characters)
		if (strlen(telNum) == 10 && letter == 1)
			needInput = 0;
		else {
			clearKeyboard();
			printf("Enter a 10-digit phone number: ");
			scanf("%10s", telNum);
			letter = 1;
		}
	}
	clearKeyboard();
}


// findContactIndex:
int findContactIndex(const struct Contact contacts[], int size, const char Cell[])
{
	int i;
	int result = -1;
	for (i = 0; i < size; i++) {
		if (strcmp(contacts[i].numbers.cell, Cell) == 0) {
			result = i;
		}
	}
	return result;
}


// displayContactHeader

void displayContactHeader(void)
{
	printf("\n");
	printf("+-----------------------------------------------------------------------------+\n");
	printf("|                              Contacts Listing                               |\n");
	printf("+-----------------------------------------------------------------------------+\n");
}

// displayContactFooter

void displayContactFooter(int total)
{
	printf("+-----------------------------------------------------------------------------+\n");
	printf("Total contacts: %d\n\n", total);
}

// displayContact:

void displayContact(const struct Contact* ptr)
{
	if ((*ptr).name.middleInitial[0] == '\0') {
		printf(" %s %s\n", (*ptr).name.firstName, (*ptr).name.lastName);
	}
	else {
		printf(" %s %s %s\n", (*ptr).name.firstName, (*ptr).name.middleInitial, (*ptr).name.lastName);
	}
	printf("    C: %-10s   H: %-10s   B: %-10s\n", (*ptr).numbers.cell, (*ptr).numbers.home, (*ptr).numbers.business);
	if ((*ptr).address.apartmentNumber > 0) {
		printf("       %d %s, Apt# %d, %s, %s\n", (*ptr).address.streetNumber, (*ptr).address.street, (*ptr).address.apartmentNumber, (*ptr).address.city, (*ptr).address.postalCode);
	}
	else {
		printf("       %d %s, %s, %s\n", (*ptr).address.streetNumber, (*ptr).address.street, (*ptr).address.city, (*ptr).address.postalCode);
	}
}

// displayContacts:

void displayContacts(const struct Contact contacts[], int size)
{
	int i, validNum = 0;
	displayContactHeader();
	for (i = 0; i < size; i++) {
		if (strcmp(contacts[i].numbers.cell, "") > 0) {
			displayContact(&contacts[i]);
			validNum++;
		}
	}
	displayContactFooter(validNum);
}

// searchContacts:

void searchContacts(const struct Contact contacts[], int size)
{
	int index;
	char Num[11];
	printf("\nEnter the cell number for the contact: ");
	scanf("%10s", Num);
	getTenDigitPhone(Num);
	index = findContactIndex(contacts, size, Num);
	if (index == -1) {
		printf("*** Contact NOT FOUND ***\n");
	}
	else {
		printf("\n");
		displayContact(&contacts[index]);
	}
	printf("\n");
}

// addContact:

void addContact(struct Contact contacts[], int size)
{
	int i, length, counter = 0;
	printf("\n");
	for (i = 0; i < size; i++) {
		length = strlen(contacts[i].numbers.cell);
		if (length == 0) {
			getContact(&contacts[i]);
			counter++;
			printf("--- New contact added! ---\n\n");
		}
		if (i == 4 && counter == 0) {
			printf("*** ERROR: The contact list is full! ***\n\n");
		}
	}
}

// updateContact:

void updateContact(struct Contact contacts[], int size)
{
	char phone[11];
	int i;
	int check = 0;
	printf("\nEnter the cell number for the contact: ");
	scanf("%10s", phone);
	getTenDigitPhone(phone);

	for (i = 0; i < size; i++) {
		if (strcmp(contacts[i].numbers.cell, phone) == 0) {
			printf("\nContact found:\n");
			displayContact(&contacts[i]);
			printf("\nDo you want to update the name? (y or n): ");
			if (yes() == 1) {
				*contacts[i].name.firstName = '\0';
				*contacts[i].name.middleInitial = '\0';
				*contacts[i].name.lastName = '\0';
				getName(&contacts[i].name);
			}

			printf("Do you want to update the address? (y or n): ");
			if (yes() == 1) {
				contacts[i].address.streetNumber = 0;
				*contacts[i].address.street = '\0';
				contacts[i].address.apartmentNumber = 0;
				*contacts[i].address.postalCode = '\0';
				*contacts[i].address.city = '\0';
				getAddress(&contacts[i].address);
			}
			printf("Do you want to update the numbers? (y or n): ");
			if (yes() == 1) {
				*contacts[i].numbers.cell = '\0';
				*contacts[i].numbers.home = '\0';
				*contacts[i].numbers.business = '\0';
				getNumbers(&contacts[i].numbers);
			}

			check++;
			printf("--- Contact Updated! ---\n\n");
		}
	}
	if (check == 0)
		printf("*** Contact NOT FOUND ***\n\n");
}

// deleteContact:

void deleteContact(struct Contact contacts[], int size)
{
	char phone[11];
	int remove;
	printf("\nEnter the cell number for the contact: ");
	scanf("%10s", phone);
	getTenDigitPhone(phone);
	remove = findContactIndex(contacts, 10, phone);
	if (remove == -1)
		printf("*** Contact NOT FOUND ***\n");
	else {
		printf("\nContact found:\n");
		displayContact(&contacts[remove]);
		printf("\nCONFIRM: Delete this contact? (y or n): ");
		int delete = yes();
		if (delete == 1) {
			*contacts[remove].numbers.cell = '\0';
			*contacts[remove].numbers.home = '\0';
			*contacts[remove].numbers.business = '\0';
			printf("--- Contact deleted! ---\n\n");
		}
		else {
			printf("\n");
		}
	}
}
// sortContacts:

void sortContacts(struct Contact contacts[], int h)
{
	printf("\n--- Contacts sorted! ---\n\n");
}
