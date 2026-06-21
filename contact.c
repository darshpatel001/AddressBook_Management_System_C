#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

int cmpName(const void *a, const void *b)
{
    return strcasecmp(((Contact *)a)->name, ((Contact *)b)->name);
}

int cmpPhone(const void *a, const void *b)
{
    return strcmp(((Contact *)a)->phone, ((Contact *)b)->phone);
}

int cmpEmail(const void *a, const void *b)
{
    return strcasecmp(((Contact *)a)->email, ((Contact *)b)->email);
}

void listContacts(AddressBook *addressBook, int sortCriteria)
{
    FILE *f = fopen("contacts.txt", "r");
    if (!f)
    {
        printf("\n------------------------------------------\n");
        printf("contacts.txt not found!\n");
        return;
    }

    Contact temp[MAX_CONTACTS];
    int count = 0;
    char line[500];

    // ---------- READ ALL CONTACTS ----------
    while (fgets(line, sizeof(line), f) && count < MAX_CONTACTS)
    {
        line[strcspn(line, "\n")] = '\0';

        char *name = strtok(line, ",");
        char *phone = strtok(NULL, ",");
        char *email = strtok(NULL, ",");

        if (!name)
            continue;

        strncpy(temp[count].name, name, sizeof(temp[count].name));
        strncpy(temp[count].phone, phone ? phone : "", sizeof(temp[count].phone));
        strncpy(temp[count].email, email ? email : "", sizeof(temp[count].email));

        count++;
    }
    fclose(f);

    if (count == 0)
    {
        printf("\n------------------------------------------\n");
        printf("No contacts found.\n");
        return;
    }

    // ---------- SORT -------------------------------------------------

    if (sortCriteria == 1)
        qsort(temp, count, sizeof(Contact), cmpName);
    else if (sortCriteria == 2)
        qsort(temp, count, sizeof(Contact), cmpPhone);
    else if (sortCriteria == 3)
        qsort(temp, count, sizeof(Contact), cmpEmail);
    else
        printf("Invalid sort choice! Listing unsorted...\n");

    // ---------- PRINT RESULTS ----------
    printf("\n------------------------------------------\n");
    printf("\n--- Contact List ---\n");
    for (int i = 0; i < count; i++)
    {
        printf("\nContact %d:\n", i + 1);
        printf("Name  : %s\n", temp[i].name);
        printf("Phone : %s\n", temp[i].phone);
        printf("Email : %s\n", temp[i].email);
    }

    printf("\nTotal Contacts: %d\n", count);
    printf("\n------------------------------------------\n");
}

void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;
    // Load dummy contacts
    //  populateAddressBook(addressBook); //done

    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook); // done
}

void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS);              // Exit the program
}

void createContact(AddressBook *addressBook)
{
    if (addressBook->contactCount >= MAX_CONTACTS)
    {
        printf("Address Book is FULL! Cannot add more contacts.\n");
        return;
    }
    Contact c;

    getchar();
    printf("Enter Name : ");
    fgets(c.name, sizeof(c.name), stdin);
    c.name[strcspn(c.name, "\n")] = '\0';

    printf("Enter Phone : ");
    fgets(c.phone, sizeof(c.phone), stdin);
    c.phone[strcspn(c.phone, "\n")] = '\0';

    printf("Enter Email : ");
    fgets(c.email, sizeof(c.email), stdin);
    c.email[strcspn(c.email, "\n")] = '\0';

    // store the new contact into the array
    addressBook->contacts[addressBook->contactCount] = c;
    addressBook->contactCount++;

    // printf("\nContact Added Successfully!\n");
}

void searchContact(AddressBook *addressBook)
{
    FILE *f = fopen("contacts.txt", "r");
    if (!f)
    {
        printf("No contacts.txt file found!\n");
        return;
    }

    getchar();

    char query[100];
    printf("Enter name to search: ");
    fgets(query, sizeof(query), stdin);
    query[strcspn(query, "\n")] = '\0';

    char line[500];
    int found = 0;

    printf("\n---------- Search Results ----------\n");

    while (fgets(line, sizeof(line), f))
    {
        line[strcspn(line, "\n")] = '\0';

        // Tokenize the csv
        char *name = strtok(line, ",");
        char *phone = strtok(NULL, ",");
        char *email = strtok(NULL, ",");

        if (!name)
            continue;

        if (strcasestr(name, query))
        {
            printf("\nName  : %s\n", name);
            printf("Phone : %s\n", phone ? phone : "N/A");
            printf("Email : %s\n", email ? email : "N/A");
            found++;
        }
    }
    fclose(f);

    if (found == 0)
        printf("\nNo matching contacts found.\n");
    else
        printf("\n%d contact(s) found.\n", found);

    printf("\n---------- Search Results ----------\n");
}

void editContact(AddressBook *addressBook)
{
    FILE *f = fopen("contacts.txt", "r");
    if (!f)
    {
        printf("contacts.txt not found!\n");
        return;
    }

    getchar();

    char query[100];
    printf("Enter name to edit: ");
    fgets(query, sizeof(query), stdin);
    query[strcspn(query, "\n")] = '\0';

    Contact temp[MAX_CONTACTS];
    int count = 0;

    char line[500];
    int targetIndex = -1;

    // ---------- READ from file ----------
    while (fgets(line, sizeof(line), f) && count < MAX_CONTACTS)
    {
        line[strcspn(line, "\n")] = '\0';

        char *name = strtok(line, ",");
        char *phone = strtok(NULL, ",");
        char *email = strtok(NULL, ",");

        if (!name)
            continue;

        strncpy(temp[count].name, name, sizeof(temp[count].name));
        strncpy(temp[count].phone, phone ? phone : "", sizeof(temp[count].phone));
        strncpy(temp[count].email, email ? email : "", sizeof(temp[count].email));

        if (strcasestr(name, query))
            targetIndex = count;

        count++;
    }
    fclose(f);

    if (targetIndex == -1)
    {
        printf("No matching contact found.\n");
        return;
    }

    // ---------- SHOW CURRENT CONTACT ----------
    printf("\nEditing Contact:\n");
    printf("Name  : %s\nPhone : %s\nEmail : %s\n",
           temp[targetIndex].name,
           temp[targetIndex].phone,
           temp[targetIndex].email);

    // ---------- ASK USER FOR NEW VALUES ----------
    char newValue[100];
    getchar(); // flush

    printf("\nEnter new name (leave empty to keep same): ");
    fgets(newValue, sizeof(newValue), stdin);
    newValue[strcspn(newValue, "\n")] = '\0';
    if (strlen(newValue) != 0)
        strcpy(temp[targetIndex].name, newValue);

    printf("Enter new phone (leave empty to keep same): ");
    fgets(newValue, sizeof(newValue), stdin);
    newValue[strcspn(newValue, "\n")] = '\0';
    if (strlen(newValue) != 0)
        strcpy(temp[targetIndex].phone, newValue);

    printf("Enter new email (leave empty to keep same): ");
    fgets(newValue, sizeof(newValue), stdin);
    newValue[strcspn(newValue, "\n")] = '\0';
    if (strlen(newValue) != 0)
        strcpy(temp[targetIndex].email, newValue);

    // ---------- WRITE UPDATED CONTACTS BACK ----------
    f = fopen("contacts.txt", "w");
    if (!f)
    {
        printf("Error opening contacts.txt for writing!\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        fprintf(f, "%s,%s,%s\n",
                temp[i].name,
                temp[i].phone,
                temp[i].email);
    }

    fclose(f);
    // Update in-memory addressBook
    addressBook->contactCount = count;
    for (int i = 0; i < count; i++)
    {
        addressBook->contacts[i] = temp[i];
    }

    printf("\n✔ Contact updated successfully.\n");
}

void deleteContact(AddressBook *addressBook)
{
    FILE *f = fopen("contacts.txt", "r");
    if (!f)
    {
        printf("contacts.txt not found!\n");
        return;
    }

    getchar(); // clear leftover newline

    char query[100];
    printf("Enter name to delete: ");
    fgets(query, sizeof(query), stdin);
    query[strcspn(query, "\n")] = '\0';

    Contact temp[MAX_CONTACTS];
    int count = 0;

    char line[500];
    int targetIndex = -1;

    // ---------- READ ALL CONTACTS ----------
    while (fgets(line, sizeof(line), f) && count < MAX_CONTACTS)
    {
        line[strcspn(line, "\n")] = '\0';

        char *name = strtok(line, ",");
        char *phone = strtok(NULL, ",");
        char *email = strtok(NULL, ",");

        if (!name)
            continue;

        strncpy(temp[count].name, name, sizeof(temp[count].name));
        strncpy(temp[count].phone, phone ? phone : "", sizeof(temp[count].phone));
        strncpy(temp[count].email, email ? email : "", sizeof(temp[count].email));

        // Find the first matching contact
        if (strcasestr(name, query))
            targetIndex = count;

        count++;
    }
    fclose(f);

    if (targetIndex == -1)
    {
        printf("No matching contact found.\n");
        return;
    }

    // ---------- CONFIRM DELETE ----------
    printf("\nFound Contact:\n");
    printf("Name  : %s\nPhone : %s\nEmail : %s\n",
           temp[targetIndex].name,
           temp[targetIndex].phone,
           temp[targetIndex].email);

    char confirm;
    printf("\nAre you sure you want to delete this contact? (y/n): ");
    scanf(" %c", &confirm);

    if (confirm != 'y' && confirm != 'Y')
    {
        printf("Deletion cancelled.\n");
        return;
    }

    // ---------- SHIFT LEFT TO REMOVE CONTACT ----------
    for (int i = targetIndex; i < count - 1; i++)
    {
        temp[i] = temp[i + 1]; // overwrite deleted contact
    }
    count--; // contact removed

    // ---------- WRITE UPDATED LIST BACK TO FILE ----------
    f = fopen("contacts.txt", "w");
    if (!f)
    {
        printf("Error opening contacts.txt for writing!\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        fprintf(f, "%s,%s,%s\n",
                temp[i].name,
                temp[i].phone,
                temp[i].email);
    }

    fclose(f);
    // Update in-memory addressBook
    addressBook->contactCount = count;
    for (int i = 0; i < count; i++)
    {
        addressBook->contacts[i] = temp[i];
    }

    printf("\n✔ Contact deleted successfully.\n");
}
