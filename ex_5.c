/**************************
      * Itay Alter
      * 206132284
      * alterit
      * ex_5
 **************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SPACE 10
#define SIZE 26
#define IDENTICAL 0
#define TRUE 1
#define FALSE 0
#define MAX_SIZE 11

typedef struct Contact {
    char *firstName;
    char *lastName;
    char *phoneNum;
    struct Contact *next;
} Contact;

/************************************************************************
* function name: printMenu *
* The Function operation: prints the options menu *
*************************************************************************/
void printMenu() {
    printf("Welcome to the phone book manager!\nChoose an option:\n"
           "1. Add a new contact to the phone book.\n"
           "2. Delete a contact from the phone book.\n"
           "3. Find a contact in the phone book by phone number.\n"
           "4. Find a contact in the phone book by name.\n"
           "5. Update phone number for a contact.\n"
           "6. Print phone book.\n"
           "7. Exit.\n");
}

/************************************************************************
* function name: isSameNumber *
* The Input: the phone book array and a phone number that the user want to
  insert to the new contact. *
* The Function operation: checks if there is number that is identical to
  the number that the user want to insert to the new contact, if there is
  an identical number it's return "true", if there isn't it returns " false". *
*************************************************************************/
int isSameNumber(Contact *phoneBook[], char *number) {
    Contact *head;
    for (int i = 0; i < SIZE; ++i) {
        head = phoneBook[i];
        while (head != NULL) {
            if (strcmp(head->phoneNum, number) == IDENTICAL) {
                return TRUE;
            }
            head = head->next;
        }
    }
    return FALSE;
}

/************************************************************************
* function name: isSameName *
* The Input: the phone book array and a first and last name that the user
  want to insert to the new contact. *
* The Function operation: checks if there is name that is identical to
  the name that the user want to insert to the new contact, if there is
  an identical name it's return "true", if there isn't it returns " false". *
*************************************************************************/
int isSameName(Contact *phoneBook[], char *firstName, char *lastName) {
    Contact *head = phoneBook[lastName[0] - 'A'];
    while (head != NULL) {
        if ((strcmp(head->lastName, lastName) == IDENTICAL) &&
            (strcmp(head->firstName, firstName) == IDENTICAL)) {
            return TRUE;
        }
        head = head->next;
    }
    return FALSE;


}

/************************************************************************
* function name: addContact *
* The Input: the phone book array. *
* The Function operation: the function allocate memory in the "heap" for a
  new contact ant exit from the program if the allocation failed. if the
  allocation succeeded the user enter the details of the contact that he want
  to add to the phone book and the function insert the details to the phone
  book. If there is a phone number or name that already in the phone book
  that identical to what that the user want to add the function prints an
  error message and frees the memory that allocated. if there isn't identical
  details that already exist, the function adds the contact to the phone book.
  if the phone book is empty the function add the new contact to the first
  place int phone book. If the phone book isn't empty, it adds the new
  contact according to first letter of his last name (A is first, Z is last). *
*************************************************************************/
void addContact(Contact *phoneBook[]) {
    Contact *head;
    int firstNameLen, lastNameLen;
    char firstName[MAX_SIZE], lastName[MAX_SIZE], phoneNumber[MAX_SIZE];
    // ask the user for details of a new contact.
    printf("Enter a contact details (<first name> <last name>"
           " <phone number>): ");
    scanf(" %s %s %s",firstName, lastName, phoneNumber);
    // checks the length of every contact details. (name and number)
    firstNameLen = (int) strlen(firstName);
    lastNameLen = (int) strlen(lastName);

    /*
      allocate memory on the "heap" for the new contact details, according to
      string length.
     */
    Contact *current = (Contact *) malloc(sizeof(Contact));

    /*
       if the allocation failed it prints error message, frees the memory
       that allocated to the new contact, and print the options menu again.
     */
    if (current == NULL) {
        printf("The addition of the contact has failed!");
        return;
    }
    current->firstName = (char *) malloc(sizeof(char) * (firstNameLen+1));
    if (current->firstName == NULL) {
        printf("The addition of the contact has failed!");
        free(current);
        return;
    }
    current->lastName = (char *) malloc(sizeof(char) * (lastNameLen+1));
    if (current->lastName == NULL) {
        printf("The addition of the contact has failed!");
        free(current->firstName);
        free(current);
        return;
    }
    current->phoneNum = (char *) malloc(sizeof(char) * 11);
    if (current->phoneNum == NULL) {
        printf("The addition of the contact has failed!");
        free(current->lastName);
        free(current->firstName);
        free(current);
        return;
    }
    current->next = NULL;
    // insert the data that the user entered into the new contact.
    strcpy(current->firstName, firstName);
    strcpy(current->lastName, lastName);
    strcpy(current->phoneNum, phoneNumber);

    /*
      if there is a contact in the phone book with the same name, the
      function prints an error message and frees the memory that allocated
      for the new contact.
     */
    if (isSameName(phoneBook, current->firstName,
            current->lastName)) {
        printf("The addition of the contact has failed,"
               " since the contact %s %s already exists!\n",
                current->firstName, current->lastName);
        free(current->phoneNum);
        free(current->lastName);
        free(current->firstName);
        free(current);
        return;
    }

    /*
      if three is a contact in the phone book with the same number, the
      function prints an error message and frees the memory that allocated
      for the new contact.
     */
    if (isSameNumber(phoneBook, current->phoneNum)) {
        printf("The addition of the contact has failed, "
               "since the phone number %s already exists!\n",
                current->phoneNum);
        free(current->phoneNum);
        free(current->lastName);
        free(current->firstName);
        free(current);
        return;
    }

    /*
      if the new contact's last name is the first name that starts with this
      letter, the function insert it to the right place in the phone book.
     */
    head = phoneBook[current->lastName[0] - 'A'];
    if (head == NULL) {
        phoneBook[current->lastName[0] - 'A'] = current;
        printf("The contact has been added successfully!\n");
    }

        /*
          if the new contact's last name isn't the first name that starts with
          this letter, the function insert it to the right place in the phone
          book, before the contacts that their last name starts with the same
          letter.
        */
    else {
        current->next = head;
        phoneBook[current->lastName[0] - 'A'] = current;
        printf("The contact has been added successfully!\n");
    }

}

/************************************************************************
* function name: deleteContact *
* The Input: the phone book array. *
* The Function operation: the user enters the name of the contact that he
  wants to delete. The function ask the user if he is sure that he want to
  delete the contact, if the user answers anything but 'y' it cancel the
  deletion. if he answer 'y' the function checks if there is a contact with
  the same name that the name that the user wants to delete, if there isn't
  it prints error message. if there is, the function delete the contact by
  freeing the memory that allocated for the contact*
*************************************************************************/
void deleteContact(Contact *phoneBook[]) {
    char sure, firstName[MAX_SIZE], lastName[MAX_SIZE];
    Contact *current = NULL;
    Contact *prev = NULL;

    /*
      the function asks the user for the name of the contact that he wants to
      delete from the phone book.
    */
    printf("Enter a contact name (<first name> <last name>): ");
    scanf("%s %s", firstName, lastName);

    /*
      the function checks if there is a contact with the same name in the
      phone book, if there isn't it prints an error message.
    */
    if (!isSameName(phoneBook, firstName, lastName)) {
        printf("The deletion of the contact has failed!\n");
        return;
    }

    /*
      the function asks the user if he is sure that he wants to delete the
      contact. if he answers anything other than 'y' or 'Y', the function
      cancels the deletion.
      delete from the phone book.
    */
    printf("Are you sure? (y/n) ");
    scanf(" %c", &sure);
    if ((sure != 'y') && (sure != 'Y')) {
        printf("The deletion of the contact has been canceled.\n");
        return;
    }

    /*
      if there is a contact with the same name, and there is only one contact
      that his last name starts with the same first letter, the function
      delete the contact by freeing the memory that allocated for it, and
      prints that the deletion has been successful.
    */
    current = phoneBook[lastName[0] - 'A'];
    prev = current;
    if ((strcmp(firstName, current->firstName) == IDENTICAL) &&
        strcmp(lastName, current->lastName) == IDENTICAL) {
        phoneBook[lastName[0] - 'A'] = current->next;
        free(current->phoneNum);
        free(current->lastName);
        free(current->firstName);
        free(current);
        printf("The contact has been deleted successfully!\n");
        return;
    }

    /*
     if there is a contact with the same name, and there is more than one
     contact that his last name starts with the same first letter, the function
     make sure that will be a pointer to the contact that after the contact
     that we want to delete on the list and then delete the contact by
     freeing the memory that allocated for it, and prints that the deletion
     has been successful.
   */
    while (current != NULL) {
        if ((strcmp(firstName, current->firstName) == IDENTICAL) &&
            strcmp(lastName, current->lastName) == IDENTICAL) {
            prev->next = current->next;
            free(current->phoneNum);
            free(current->lastName);
            free(current->firstName);
            free(current);
            printf("The contact has been deleted successfully!\n");
            return;
        }
        prev = current;
        current = current->next;
    }
}

/************************************************************************
* function name: searchContactNumber *
* The Input: the phone book array. *
* The Function operation: The user enters the number of the contact that he
  wants search for. The function checks if there is a contact with the same
  number in the phone book. If there isn't contact with the same number it
  prints an error message. if there is it prints the contact details. *
*************************************************************************/
void searchContactNumber(Contact *phoneBook[]) {
    char phoneNumber[MAX_SIZE];
    Contact *current;

    /*
      the function asks the user for the number of the contact that he wants to
      search in the phone book.
    */
    printf("Enter a phone number: ");
    scanf("%s", phoneNumber);

    /*
     The function checks if there is a contact with the same
     number in the phone book.
   */
    for (int i = 0; i < SIZE; ++i) {
        current = phoneBook[i];
        while (current != NULL) {
            if (strcmp(phoneNumber, current->phoneNum) == IDENTICAL) {
                //if there is it prints the contact details.
                printf("The following contact was found: %s %s %s\n"
                       ,current->firstName, current->lastName,
                        current->phoneNum);
                return;
            }
            current = current->next;
        }
    }
    /*
      If there isn't contact with the same number it
      prints an error message.
    */
    printf("No contact with a phone number %s was "
           "found in the phone book\n", phoneNumber);
}

/************************************************************************
* function name: searchContactName *
* The Input: the phone book array. *
* The Function operation: The user enters the name of the contact that he
  wants search for. The function checks if there is a contact with the same
  name in the phone book.the function don't go over all the phone book, only
  over the list of contacts with the same first letter of the last name. If
  there isn't contact with the same name it print an error message. if there
  is it prints the contact details. *
*************************************************************************/
void searchContactName(Contact *phoneBook[]) {
    char firstName[MAX_SIZE], lastName[MAX_SIZE];
    Contact *current = NULL;

    /*
      the function asks the user for the name of the contact that he wants to
      search in the phone book.
    */
    printf("Enter a contact name (<first name> <last name>): ");
    scanf("%s %s", firstName, lastName);
    current = phoneBook[lastName[0] - 'A'];

    /*
      The function checks if there is a contact with the same name in the
      phone book. the function don't go over all the phone book, only over
      the list of contacts with the same first letter of the last name as the
      name  of the contact that the user wants to search for.
     */
    while (current != NULL) {
        if ((strcmp(firstName, current->firstName) == 0) &&
            strcmp(lastName, current->lastName) == 0) {
            //if there is it prints the contact details.
            printf("The following contact was found: %s %s %s\n",
                    current->firstName, current->lastName,
                    current->phoneNum);
            return;
        }
        current = current->next;
    }

    /*
      If there isn't contact with the same name it
      prints an error message.
    */
    printf("No contact with a name %s %s "
           "was found in the phone book\n",
            firstName, lastName);
}

/************************************************************************
* function name: editContact *
* The Input: the phone book array. *
* The Function operation: The user enters the name of the contact that he
  wants edit. The function checks if there is a contact with the same
  name in the phone book.The function don't go over all the phone book, only
  over the list of contacts with the same first letter of the last name. If
  there isn't contact with the same name it print an error message. if there
  is it prints the contact details. The user enter the new number that he
  wants to insert to the contact. The function checks if there is a contact
  with the same number in the phone book. If there is contact with the same
  number it prints an error message. if there isn't, the function copying the
  new number to the contact details. *
*************************************************************************/
void editContact(Contact *phoneBook[]) {
    char firstName[MAX_SIZE], lastName[MAX_SIZE], phoneNumber[MAX_SIZE];
    int flag = 0;
    Contact *current = NULL;

    /*
      the function asks the user for the number of the contact that he wants to
      edit.
    */
    printf("Enter a contact name (<first name> <last name>): ");
    scanf("%s %s", firstName, lastName);
    current = phoneBook[lastName[0] - 'A'];

    /*
     The function checks if there is a contact with the same
     name in the phone book.
   */
    while (current != NULL) {
        if ((strcmp(firstName, current->firstName) == IDENTICAL) &&
            strcmp(lastName, current->lastName) == IDENTICAL) {
            //if there is it prints the contact details.
            printf("The following contact was found: %s %s %s\n",
                    current->firstName, current->lastName,
                    current->phoneNum);
            flag = 1;
            break;
        }
        current = current->next;
    }
    if (flag) {
        /*
          if there is a contact with the same name, the function asks the
          user for the new phone number for this contact.
         */
        printf("Enter the new phone number: ");
        scanf("%s", phoneNumber);
        if (isSameNumber(phoneBook, phoneNumber)) {

            /*
             If there is contact with the same number it
             prints an error message.
           */
            printf("The update of the contact has failed, since the "
                   "phone number %s already exists!\n", phoneNumber);
            return;
        }

        /*
         If there isn't contact with the same number the function updates the
         contact's phone number to the new one and prints a success message.
       */
        strcpy(current->phoneNum, phoneNumber);
        printf("The contact has been updated "
               "successfully!\n");
        return;
    } else {

        /*
          if there isn't a contact with the same name, the function prints an
          error message.
         */
        printf("No contact with a name %s %s "
               "was found in the phone book\n",
                firstName, lastName);
        return;

    }
}

/************************************************************************
* function name: printPhoneBook *
* The Input: the phone book array. *
* The Function operation: prints the the phonebook in order according to the
  letter of the last name of the contacts ('A' is first, 'Z' is last) and in
  every letter the last contact that has been added to the phonebook is
  printed first.  *
*************************************************************************/
void printPhoneBook(Contact *phoneBook[]) {
    Contact *head;
    for (int i = 0; i < SIZE; ++i) {
        head = phoneBook[i];
        while (head != NULL) {
            printf("%-*s %-*s %s\n",SPACE, head->firstName,SPACE,
                    head->lastName,head->phoneNum);

            head = head->next;
        }

    }
}

/************************************************************************
* function name: freeAll *
* The Input: the phone book array. *
* The Function operation: free the memory that allocated for every contact in
  the phonebook. *
*************************************************************************/
void freeAll(Contact *phoneBook[]) {
    Contact *current, *prev;
    for (int i = 0; i < SIZE; ++i) {
        current = phoneBook[i];
        while (current != NULL) {
            prev = current;
            current = current->next;
            free(prev->lastName);
            free(prev->firstName);
            free(prev->phoneNum);
            free(prev);
        }
    }
}

int main() {
    Contact *phoneBook[SIZE];
    // initializes the whole phonebook array.
    for (int i = 0; i < SIZE; ++i) {
        phoneBook[i] = NULL;
    }
    int choice;
    // prints the options menu and ask the user to choose one.
    printMenu();
    scanf("%d", &choice);
    while (choice != 7) {
        switch (choice) {
            case 1:
                addContact(phoneBook);
                break;

            case 2:
                deleteContact(phoneBook);
                break;

            case 3:
                searchContactNumber(phoneBook);
                break;
            case 4:
                searchContactName(phoneBook);
                break;
            case 5:
                editContact(phoneBook);
                break;
            case 6:
                printPhoneBook(phoneBook);
                break;
            default:

                /*
                   if the user entered number that not between 1-7 the
                   program asks the user to try again.
                */
                printf("Wrong option, try again:\n");
                scanf("%d", &choice);
                continue;
        }
        //prints the menu again after the program operated what the user wanted.
        printMenu();
        scanf("%d", &choice);
    }

    /*
       if the user entered '7' the program prints "bye!" and free all the
       memory that allocated for all the contacts.
    */
    printf("Bye!");
    freeAll(phoneBook);
    return 0;
}
