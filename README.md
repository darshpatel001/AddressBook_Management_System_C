# Address Book Management System in C

## Overview

The Address Book Management System is a console-based application developed in C that allows users to efficiently manage contact information.

The application provides functionalities such as adding, searching, editing, deleting, listing, and saving contacts using file handling techniques.

This project demonstrates practical implementation of:

* Structures
* File Handling
* Searching Algorithms
* Sorting Algorithms
* Data Management
* Modular Programming
* Command Line Applications

---

## Features

* Add New Contacts
* Edit Existing Contacts
* Delete Contacts
* Search Contacts
* Display All Contacts
* Sort Contacts
* Save Contacts to File
* Persistent Data Storage
* Menu Driven Interface
* Modular C Implementation

---

## Technologies Used

| Technology    | Purpose                 |
| ------------- | ----------------------- |
| C Programming | Core implementation     |
| GCC Compiler  | Compilation             |
| Structures    | Contact storage         |
| File Handling | Data persistence        |
| Linux         | Development environment |

---

## Project Structure

```text
.
├── main.c
├── contact.c
├── contact.h
├── file.c
├── file.h
├── populate.c
├── populate.h
├── contacts.csv
├── README.md
```

---

## Working Principle

### Add Contact

1. Enter contact details.
2. Validate user input.
3. Store information in structure.
4. Save data to file.

### Search Contact

1. Enter search key.
2. Traverse contact records.
3. Display matching results.

### Edit Contact

1. Search existing contact.
2. Update required fields.
3. Save modified record.

### Delete Contact

1. Search contact.
2. Remove selected record.
3. Update database.

### Save Contacts

1. Open file.
2. Write updated records.
3. Close file safely.

---

## Architecture

```text
                +------------------+
                | User Input       |
                +------------------+
                         |
                         v
                +------------------+
                | Menu System      |
                +------------------+
                         |
      ---------------------------------------
      |         |         |         |       |
      v         v         v         v       v

   Add      Search     Edit     Delete   Display

      \         |         |         |      /
       \        |         |         |     /
        ----------------------------------
                         |
                         v
                +------------------+
                | Contact Database |
                +------------------+
                         |
                         v
                +------------------+
                | File Storage     |
                +------------------+
```

---

## Data Structure Used

```c
typedef struct
{
    char name[50];
    char mobile[15];
    char email[50];
} Contact;
```

The structure stores all contact-related information in a single record.

---

## Function Descriptions

### Contact Management Module

#### add_contact()

* Adds a new contact to the address book.
* Validates user input before storing.

#### search_contact()

* Searches contacts by name, phone number, or email.

#### edit_contact()

* Modifies existing contact information.

#### delete_contact()

* Removes a contact from the address book.

#### list_contacts()

* Displays all stored contacts.

#### sort_contacts()

* Sorts contacts alphabetically.

---

### File Handling Module

#### load_contacts()

* Loads contacts from storage file.

#### save_contacts()

* Saves current contact database to file.

#### create_file()

* Creates storage file if not present.

---

### Utility Module

#### validate_name()

* Verifies valid name format.

#### validate_mobile()

* Validates mobile number format.

#### validate_email()

* Validates email address format.

---

## Build Instructions

### Compile

```bash
gcc *.c -o addressbook
```

---

## Usage

### Run Application

```bash
./addressbook
```

---

## Sample Execution

```text
===== ADDRESS BOOK =====

1. Add Contact
2. Search Contact
3. Edit Contact
4. Delete Contact
5. Display Contacts
6. Save Contacts
7. Exit

Enter Choice:
```

---

## Concepts Demonstrated

* C Programming
* Structures
* Arrays
* File Handling
* Searching
* Sorting
* Dynamic Data Management
* Menu Driven Applications
* Modular Programming

---

## Applications

* Personal Contact Management
* Employee Directory Systems
* Student Information Systems
* Customer Databases
* Record Management Systems

---

## Future Improvements

* Password Protected Access
* SQLite Database Integration
* GUI Version
* Contact Import/Export
* Duplicate Contact Detection
* Cloud Synchronization
* Phone Number Validation API

---

## Learning Outcomes

Through this project, I gained practical experience in:

* Structured Programming
* File Processing
* Data Management
* Search and Sort Techniques
* Software Design
* Debugging and Testing
* Linux Development Environment

---

## Author

**Darsh Patel**

Electronics & Communication Engineer

Firmware Engineer | Embedded Systems | IoT Developer

GitHub: https://github.com/darshpatel001

---

## License

This project is licensed under the MIT License.
