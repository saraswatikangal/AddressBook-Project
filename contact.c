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
    for(i = 0; name[i] != '\0'; i++)
    {
        if(!((name[i]>='A' && name[i]<='Z') ||
             (name[i]>='a' && name[i]<='z') ||
             (name[i]>='0' && name[i]<='9')))
        {
            return 0;
        }
    }
    return 1;
}
    
int valid_phone(char phone[])
{
        if(strlen(phone)==10 && phone[0]>'5')
        {
            return 1;
        }
        return 0;
}

int valid_email(char email[])
{
        int at = 0;
        int dot = 0;
        int at_count = 0;
        int dot_count = 0;
        int len = strlen(email);
        int i;
        for(i=0;i<len;i++)
        {
            if(email[i]=='@')
            {
                at=i;
                at_count++;
            }
            if(email[i]=='.')
            {
                dot=i;
                dot_count++;
            }
            if(email[i]>='A' && email[i]<='Z')
            {
                return 0;
            }
        }
        if(at_count==1 && dot_count==1 && at>0 && dot>at && len>=4 && email[len-3]=='c' && email[len-2]=='o' && email[len-1]=='m')
        {
            return 1;
        }
         return 0;
}
void createContact(AddressBook *addressBook)
{
    int n;
    int i;
    printf("Enter number of contact: ");
    scanf("%d", &n);
    for(i=0;i<n;i++)
    {
        if(addressBook->contactCount >= MAX_CONTACTS)
        {
            printf("Address Book is full\n");
            return;
        }
        printf("\nContact %d\n",i+1);
        do
        {
            printf("Enter the name: ");
            scanf("%s",addressBook->contacts[addressBook->contactCount].name);
            if(!valid_name(addressBook->contacts[addressBook->contactCount].name))
            {
                printf("Invalid name\n");
            }
        }while(!valid_name(addressBook->contacts[addressBook->contactCount].name));

        do
        {
            printf("Enter the phone: ");
            scanf("%s",addressBook->contacts[addressBook->contactCount].phone);
            if(!valid_phone(addressBook->contacts[addressBook->contactCount].phone))
            {
                printf("Invalid phone number\n");
            }
        }while(!valid_phone(addressBook->contacts[addressBook->contactCount].phone));
        do
        {
            
            printf("Enter the email: ");
            scanf("%s",addressBook->contacts[addressBook->contactCount].email);
            if(!valid_email(addressBook->contacts[addressBook->contactCount].email))
            {
                printf("Invalid email\n");
            }
        }while(!valid_email(addressBook->contacts[addressBook->contactCount].email));
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
                printf("S.No:%d\tName:%s\tContact:%s\tEmail:%s\n",sno,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                sno++;
                flag=1;
            }
        }
        else if(choice==2)
        {
            if(strstr(addressBook->contacts[i].phone,search) != NULL)
            {
                printf("S.No:%d\tName:%s\tContact:%s\tEmail:%s\n",sno,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                sno++;
                flag=1;
            }
        }
        else if(choice==3)
        {
            if(strcasestr(addressBook->contacts[i].email,search) != NULL)
            {
                printf("S.No:%d\tName:%s\tContact:%s\tEmail:%s\n",sno,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
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
	/* Define the logic for Editcontact */
    
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
   
}
