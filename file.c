#include <stdio.h>
#include <string.h>
#include "file.h"
#include "populate.h"

void saveContactsToFile(AddressBook *addressBook) {
        FILE *f = fopen("contacts.txt", "w");
        if (!f) {
            printf("Error: Could not open contacts.txt for writing!\n");
            return;
            }
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            Contact *c = &addressBook->contacts[i];
            //write each contact in csv
            fprintf(f,"%s,%s,%s\n",c->name,c->phone,c->email);
        }
        fclose(f);
        printf("✔ Contacts saved successfully to contacts.txt\n");
        
}

void loadContactsFromFile(AddressBook *addressBook) {

    FILE *f = fopen("contacts.txt", "r");
    if (!f) {
        return;  // file doesn't exist, no error
    }

    char line[500];
    addressBook->contactCount = 0;

    while (fgets(line, sizeof(line), f)) {

        line[strcspn(line, "\n")] = '\0';

        char *name  = strtok(line, ",");
        char *phone = strtok(NULL, ",");
        char *email = strtok(NULL, ",");

        if (!name || !phone || !email)
            continue;

        Contact *c = &addressBook->contacts[addressBook->contactCount++];

        strcpy(c->name, name);
        strcpy(c->phone, phone);
        strcpy(c->email, email);
    }

    fclose(f);
    
}
