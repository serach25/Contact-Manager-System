/* ------------------------------------------------------------------
Name: Serach Boes
Date: November, 18, 2018
---------------------------------------------------------------------
Description: This header file modularizes general helper functions to
help reduce redundant coding for common repetitive tasks.
---------------------------------------------------------------------*/
#include "contacts.h"


// Function Prototypes

// Clear the standard input buffer
// clearKeyboard:

void clearKeyboard(void);

// pause:

void pause(void);

// getInt:

int getInt(void);

// getIntInRange:

int getIntInRange(int, int);

// yes:

int yes(void);

// menu:

int menu(void);

// contactManagerSystem:

void contactManagerSystem(void);


// Generic function to get a ten-digit phone number:
// getTenDigitPhone
void getTenDigitPhone(char[]);

// findContactIndex:
int findContactIndex(const struct Contact[], int, const char[]);


// displayContactHeader:

void displayContactHeader(void);

// displayContactFooter:

void displayContactFooter(int);

// displayContact:

void displayContact(const struct Contact*);

// displayContacts:

void displayContacts(const struct Contact[], int);

// searchContacts:

void searchContacts(const struct Contact[], int);

// addContact:

void addContact(struct Contact[], int);

// updateContact:

void updateContact(struct Contact[], int);

// deleteContact:

void deleteContact(struct Contact[], int);

// sortContacts:

void sortContacts(struct Contact[], int);