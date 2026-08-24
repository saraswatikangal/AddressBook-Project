#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"

int valid_name(char name[]);
int valid_phone(char phone[]);
int valid_email(char email[]);
void sortContacts(AddressBook *addressBook);

void sortContacts(AddressBook *addressBook)
{
    int sortCriteria;
    int i, j;
    Contact temp;

    printf("\n1. Sort by Name");
    printf("\n2. Sort by Phone");
    printf("\n3. Sort by Email");
    printf("\nEnter your choice: ");
    scanf("%d", &sortCriteria);

    if(sortCriteria<1 || sortCriteria>3)
    {
        printf("Invalid choice\n");
        return;
    }

    for(i=0;i<addressBook->contactCount-1;i++)
    {
        for(j=i+1;j<addressBook->contactCount;j++)
        {
            int result=0;

            if(sortCriteria==1)
            {
                result=strcmp(addressBook->contacts[i].name,addressBook->contacts[j].name);
            }
            else if(sortCriteria==2)
            {
                result = strcmp(addressBook->contacts[i].phone,addressBook->contacts[j].phone);
            }
            else if(sortCriteria==3)
            {
                result = strcmp(addressBook->contacts[i].email,addressBook->contacts[j].email);
            }

            if(result>0)
            {
                temp = addressBook->contacts[i];
                addressBook->contacts[i] = addressBook->contacts[j];
                addressBook->contacts[j] = temp;
            }
        }
    }
    printf("\nContacts sorted successfully!\n");
}

void listContacts(AddressBook *addressBook) 
{
    int i;
    sortContacts(addressBook);
    for(i=0;i<addressBook->contactCount;i++)
    {
        printf("S.No:%d\tName:%s\tContact:%s\tEmail:%s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount=0;
    
    // Load contacts from file during initialization (After files)
    //loadContactsFromFile(addressBook);
}

/*void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

*/
int valid_name(char name[])
{
    int i;
    if(!((name[0] >= 'A' && name[0] <= 'Z') ||
         (name[0] >= 'a' && name[0] <= 'z')))
    {
        return 0;
    }

    for(i = 1; name[i] != '\0'; i++)
    {
        if(!((name[i] >= 'A' && name[i] <= 'Z') ||
             (name[i] >= 'a' && name[i] <= 'z') ||
             (name[i] >= '0' && name[i] <= '9')))
        {
            return 0;
        }
    }
    return 1;
}
    
int valid_phone(char phone[])
{
    int i;
    if(strlen(phone) != 10)
    {
        return 0;
    }
    if(phone[0] < '6' || phone[0] > '9')
    {
        return 0;
    }
    for(i = 0; i < 10; i++)
    {
        if(phone[i] < '0' || phone[i] > '9')
        {
            return 0;
        }
    }
    return 1;
}

int valid_email(char email[])
{
    int at = 0;
    int dot = 0;
    int at_count = 0;
    int dot_count = 0;
    int len = strlen(email);
    int i;

    for(i = 0; i < len; i++)
    {
        if(email[i] == '@')
        {
            at = i;
            at_count++;
        }

        if(email[i] == '.')
        {
            dot = i;
            dot_count++;
        }
        if(email[i] >= 'A' && email[i] <= 'Z')
        {
            return 0;
        }
    }
    if(at_count == 1 && dot_count == 1 && at > 0 && dot > at && len >= 4 && email[len-3] == 'c' && email[len-2] == 'o' && email[len-1] == 'm')
    {
        return 1;
    }
    return 0;
}

void createContact(AddressBook *addressBook)
{
    int n;
    int i, j;
    int duplicate;
    int valid;

    printf("Enter number of contact: ");
    scanf("%d", &n);

    for(i=0;i<n;i++)
    {
        if(addressBook->contactCount>=MAX_CONTACTS)
        {
            printf("Address Book is full\n");
            return;
        }
        printf("\nContact %d\n", i + 1);

        do
        {
            printf("Enter the name: ");
            scanf("%s", addressBook->contacts[addressBook->contactCount].name);

            if(!valid_name(addressBook->contacts[addressBook->contactCount].name))
            {
                printf("Invalid name\n");
            }

        } while(!valid_name(addressBook->contacts[addressBook->contactCount].name));


        do
        {
            duplicate = 0;
            valid = 1;

            printf("Enter the phone: ");

            scanf("%s",addressBook->contacts[addressBook->contactCount].phone);

            if(!valid_phone(addressBook->contacts[addressBook->contactCount].phone))
            {
                printf("Invalid phone number\n");
                valid = 0;
                continue;
            }

            for(j=0;j<addressBook->contactCount;j++)
            {
                if(strcmp(addressBook->contacts[j].phone,addressBook->contacts[addressBook->contactCount].phone) == 0)
                {
                    duplicate=1;
                }
            }

            if(duplicate==1)
            {
                printf("Phone number already exists\n");
            }

        } while(duplicate==1 || valid==0);


        do
        {
            duplicate=0;
            valid=1;

            printf("Enter the email: ");

            scanf("%s",addressBook->contacts[addressBook->contactCount].email);

            if(!valid_email(addressBook->contacts[addressBook->contactCount].email))
            {
                printf("Invalid email\n");
                valid=0;
                continue;
            }

            for(j=0;j<addressBook->contactCount;j++)
            {
                if(strcmp(addressBook->contacts[j].email,addressBook->contacts[addressBook->contactCount].email) == 0)
                {
                    duplicate=1;
                }
            }

            if(duplicate==1)
            {
                printf("Email already exists\n");
            }

        } while(duplicate==1 || valid==0);
        addressBook->contactCount++;
        printf("Contact added successfully!\n");
    }
}
void searchContact(AddressBook *addressBook) 
{
    int choice;
    int i;
    int flag=0;
    int sno = 1;
    char search[50];

    printf("\n1. Search by Name");
    printf("\n2. Search by Phone");
    printf("\n3. Search by Email");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    printf("Enter search value: ");
    scanf("%s", search);

    for(i=0;i<addressBook->contactCount;i++)
    {
        if(choice==1)
        {
            if(strcasestr(addressBook->contacts[i].name,search) != NULL)
            {
                printf("S.No:%d\tName:%s\t\t\tContact:%s\tEmail:%s\n",sno,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                sno++;
                flag=1;
            }
        }
        else if(choice==2)
        {
            if(strstr(addressBook->contacts[i].phone,search) != NULL)
            {
                printf("S.No:%d\tName:%s\t\t\tContact:%s\tEmail:%s\n",sno,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                sno++;
                flag=1;
            }
        }
        else if(choice==3)
        {
            if(strcasestr(addressBook->contacts[i].email,search) != NULL)
            {
                printf("S.No:%d\tName:%s\t\t\tContact:%s\tEmail:%s\n",sno,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                sno++;
                flag=1;
            }
        }
        else
        {
            printf("Invalid choice\n");
            return;
        }
    }

    if(flag==0)
    {
        printf("\nContact not found\n");
    }
}


void editContact(AddressBook *addressBook)
{
    int choice;
    char search[50];
    int matchingIndex[100];
    int count = 0;
    int i, index;
    int editChoice;

    printf("\nEdit Contact\n");
    printf("1. Search by Name\n");
    printf("2. Search by Phone\n");
    printf("3. Search by Email\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    printf("Enter search value: ");
    scanf("%s", search);

    for(i = 0; i < addressBook->contactCount; i++)
    {
        if(choice == 1 && strcmp(addressBook->contacts[i].name, search) == 0)
        {
            matchingIndex[count] = i;
            count++;
        }
        else if(choice == 2 && strcmp(addressBook->contacts[i].phone, search) == 0)
        {
            matchingIndex[count] = i;
            count++;
        }
        else if(choice == 3 && strcmp(addressBook->contacts[i].email, search) == 0)
        {
            matchingIndex[count] = i;
            count++;
        }
    }

    if(count == 0)
    {
        printf("Contact not found\n");
        return;
    }

    printf("\nMatching contacts:\n");
    for(i = 0; i < count; i++)
    {
        index = matchingIndex[i];

        printf("%d. Name: %s  Phone: %s  Email: %s\n",i+1,addressBook->contacts[index].name,addressBook->contacts[index].phone,addressBook->contacts[index].email);
    }
    printf("Enter contact number to edit: ");
    scanf("%d", &editChoice);

    index = matchingIndex[editChoice - 1];

    printf("\nEdit Options\n");
    printf("1. Edit Name\n");
    printf("2. Edit Phone\n");
    printf("3. Edit Email\n");
    printf("Enter your choice: ");
    scanf("%d", &editChoice);

    if(editChoice == 1)
    {
        printf("Enter new name: ");
        scanf("%s", addressBook->contacts[index].name);

        while(!valid_name(addressBook->contacts[index].name))
        {
            printf("Invalid name\n");
            printf("Enter new name: ");
            scanf("%s", addressBook->contacts[index].name);
        }

        printf("Name updated successfully!\n");
    }

    else if(editChoice == 2)
    {
        printf("Enter new phone: ");
        scanf("%s", addressBook->contacts[index].phone);

        while(!valid_phone(addressBook->contacts[index].phone))
        {
            printf("Invalid phone number\n");
            printf("Enter new phone: ");
            scanf("%s", addressBook->contacts[index].phone);
        }

        printf("Phone updated successfully!\n");
    }

    else if(editChoice == 3)
    {
        printf("Enter new email: ");
        scanf("%s", addressBook->contacts[index].email);

        while(!valid_email(addressBook->contacts[index].email))
        {
            printf("Invalid email\n");
            printf("Enter new email: ");
            scanf("%s", addressBook->contacts[index].email);
        }

        printf("Email updated successfully!\n");
    }

    else
    {
        printf("Invalid choice\n");
    }
}
void deleteContact(AddressBook *addressBook)
{
    int choice;
    char search[50];
    int matchingIndex[100];
    int count = 0;
    int i, index, deleteIndex;

    printf("\nDelete Contact\n");
    printf("1. Search by Name\n");
    printf("2. Search by Phone\n");
    printf("3. Search by Email\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    printf("Enter search value: ");
    scanf("%s", search);

    for(i=0;i<addressBook->contactCount;i++)
    {
        if(choice==1 && strcmp(addressBook->contacts[i].name, search)==0)
        {
            matchingIndex[count]=i;
            count++;
        }
        else if(choice==2 && strcmp(addressBook->contacts[i].phone, search)==0)
        {
            matchingIndex[count]=i;
            count++;
        }
        else if(choice==3 && strcmp(addressBook->contacts[i].email,search)==0)
        {
            matchingIndex[count]=i;
            count++;
        }
    }

    if(count==0)
    {
        printf("Contact not found\n");
        return;
    }
    printf("\nMatching contacts:\n");

    for(i=0;i<count;i++)
    {
        index=matchingIndex[i];

        printf("%d. Name: %s\tPhone: %s\tEmail: %s\n",i+1,addressBook->contacts[index].name,addressBook->contacts[index].phone,addressBook->contacts[index].email);
    }
    printf("Enter contact number to delete: ");
    scanf("%d", &deleteIndex);
    if(deleteIndex < 1 || deleteIndex > count)
    {
        printf("Invalid choice\n");
        return;
    }
    index=matchingIndex[deleteIndex-1];
    for(i=index;i<addressBook->contactCount-1;i++)
    {
        addressBook->contacts[i]=addressBook->contacts[i+1];
    }
    addressBook->contactCount--;
    printf("Contact deleted successfully!\n");
}