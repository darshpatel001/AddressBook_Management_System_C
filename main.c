#include <stdio.h>
#include "contact.h"
#include "file.h"

int main() {
    int choice;
    AddressBook addressBook;

    initialize(&addressBook);            
    loadContactsFromFile(&addressBook);  

    do {
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. Save and Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("\n------------------------------------------\n");

        switch (choice) {
            case 1:
                printf("\n------------------------------------------\n");
                createContact(&addressBook);
                saveContactsToFile(&addressBook);
                break;

            case 2:
                printf("\n------------------------------------------\n");
                searchContact(&addressBook);
                break;

            case 3:
                printf("\n------------------------------------------\n");
                editContact(&addressBook);
                break;

            case 4:
                printf("\n------------------------------------------\n");
                deleteContact(&addressBook);
                break;

            case 5:
                printf("\n------------------------------------------\n");
                printf("Select sort criteria:\n");
                printf("1. Sort by name\n");
                printf("2. Sort by phone\n");
                printf("3. Sort by email\n");
                printf("Enter your choice: ");
                int sortChoice;
                scanf("%d", &sortChoice);
                listContacts(&addressBook, sortChoice);
                break;

            case 6:
                printf("\n------------------------------------------\n");
                printf("Saved and Exiting...\n");
                saveContactsToFile(&addressBook);
                break;

            default:
                printf("\n------------------------------------------\n");
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}
