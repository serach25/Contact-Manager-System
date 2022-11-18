/* -------------------------------------------
Name: Serach Boes
Date: November, 20, 2018
---------------------------------------------- */

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include "contacts.h"
#include "contactHelpers.h"

// getName:

void getName(struct Name* a) {

	printf("Please enter the contact's first name: ");
	scanf("%30[^\n]", a->firstName);
	clearKeyboard();

	printf("Do you want to enter a middle initial(s)? (y or n): ");

	if (yes() == 1) {

		printf("Please enter the contact's middle initial(s): ");
		scanf("%6[^\n]", a->middleInitial);
		clearKeyboard(); // Need this to empty the buffer
	}

	printf("Please enter the contact's last name: ");
	scanf("%35[^\n]", a->lastName);
	clearKeyboard();

}

// getAddress:

void getAddress(struct Address* b) {

	int num;

	printf("Please enter the contact's street number: ");
	num = getInt();
	while (num <= 0) {
		printf("Please enter the contact's street number: ");
		num = getInt();
	}
	b->streetNumber = num;

	printf("Please enter the contact's street name: ");
	scanf("%40[^\n]", b->street);
	clearKeyboard();

	printf("Do you want to enter an apartment number? (y or n): ");

	if (yes() == 1) {

		printf("Please enter the contact's apartment number: ");
		num = getInt();
		while (num <= 0) {
			printf("Please enter the contact's apartment number: ");
			num = getInt();
		}
		b->apartmentNumber = num;
	}

	printf("Please enter the contact's postal code: ");
	scanf("%7[^\n]", b->postalCode);
	clearKeyboard();

	printf("Please enter the contact's city: ");
	scanf("%40[^\n]", b->city);
	clearKeyboard();
}


// getNumbers:
void getNumbers(struct Numbers* c) {

	printf("Please enter the contact's cell phone number: ");
	scanf("%10[^\n]", c->cell);
	getTenDigitPhone(c->cell);


	printf("Do you want to enter a home phone number? (y or n): ");

	if (yes() == 1) {

		printf("Please enter the contact's home phone number: ");
		scanf("%10[^\n]", c->home);
		getTenDigitPhone(c->home);

	}

	printf("Do you want to enter a business phone number? (y or n): ");

	if (yes() == 1) {

		printf("Please enter the contact's business phone number: ");
		scanf("%10[^\n]", c->business);
		getTenDigitPhone(c->business);

	}
}

// getContact

void getContact(struct Contact* d) {

	getName(&d->name);
	getAddress(&d->address);
	getNumbers(&d->numbers);

}