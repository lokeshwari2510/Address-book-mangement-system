#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
// #include "populate.h"
int indexmap[100]; 
int mapcount = 0;   
void listContacts(AddressBook *addressBook) 
{   printf("\n-----------------------------------------------------------------\n");
    printf("%-5s %-20s %-15s %-30s\n", "S.No", "Name", "Phone", "Email");
    printf("-------------------------------------------------------------------\n");
    for(int i = 0; i < addressBook->contactCount; i++)
   
       {
        printf("%-5d %-20s %-15s %-30s\n",
               i+1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }
    printf("-------------------------------------------------------------------\n");
    }
void printcontact(int s,Contact *c){
     printf("%d. Name: %s | Phone: %s | Email: %s\n",s+1,c->name,c->phone,c->email);
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
     saveContactsToFile(addressBook); // Save contacts to file
     exit(EXIT_SUCCESS); // Exit the program
 }
int isvalidname(char *name){
    for(int i=0;name[i]!='\0';i++)
    {
        if(!((name[i]>='A'&&name[i]<='Z')||(name[i]>='a'&&name[i]<='z')||(name[i]=' ')))
        {
            return 0;
        }
    }
   return 1;
}
int isvalidphone(char *phone){
    int len=strlen(phone);
    if(len!=10)
    return 0;
    if(phone[0]<'6'||phone[0]>'9')
    return 0;
    for(int i=0;i<len;i++){
        if(phone[i]<'0'||phone[i]>'9')
        return 0;
    }
    return 1;
}    
int isphoneunique(char *phone, AddressBook *addressBook)
{
    for(int i = 0; i < addressBook->contactCount; i++)
    {if(strcmp(phone, addressBook->contacts[i].phone) == 0)
       return 0;
    }
    return 1;
}
int isvalidemail(char*email){
    int count=0;
    if(email[0]>='0'&& email[0]<='9')
    return 0;
    for(int i=0;email[i]!='\0';i++){
        if(email[i]=='@')
        count++;
        if(email[i]>='A'&&email[i]<='Z')
        return 0;
    }
    if(count!=1)
    return 0;
    char *pos = strstr(email, ".com");
    if(pos == NULL || strcmp(pos, ".com") != 0)
    return 0;
return 1;
}
void createContact(AddressBook *addressBook)
{   Contact newcontact;
    int attempts;
    attempts=0;
    while(attempts<3){
    printf("Enter the Name: ");
    scanf(" %[^\n]",newcontact.name);
    if(isvalidname(newcontact.name))
    break;
    printf("Invalid Name! only alphabets allowed\n");
    attempts++;
    }
    if(attempts==3){
        printf("Too many invalid attempts.creation cancelled\n");
        return;
    }
    attempts=0;
    while(attempts<3){
    printf("Enter phone number: ");
    scanf(" %[^\n]",newcontact.phone);
    if(!(isvalidphone(newcontact.phone)))
    {printf("Invalid phone format!\n");
    }
    else if(!isphoneunique(newcontact.phone, addressBook))
    {printf("phone already exists!\n");
    }
    else
    {break; 
    }
      attempts++;
     }
    if(attempts==3){
        printf("Too many invalid attempts.creation cancelled\n");
        return;
    }
    attempts=0;
    while(attempts<3){
    printf("Enter the email: ");
    scanf(" %[^\n]",newcontact.email);
    if(isvalidemail(newcontact.email))
    break;
    printf("Invalid email!\n");
    attempts++;
    }
    if(attempts==3){
        printf("Too many invalid attempts.creation cancelled\n");
        return;
    }
    addressBook->contacts[addressBook->contactCount]=newcontact;
    addressBook->contactCount++;
    printf("Contact added successfully!\n");
};
void searchContact(AddressBook *addressBook) 
{
    printf("1.search by name.\n");
    printf("2.search by phone no.\n");
    printf("3.search by email.\n");
    int choice;
    printf("Enter the choice:");
    scanf("%d",&choice);
    switch(choice)
    {
        case 1:
            searchbyname(addressBook);
            break;
        case 2:
            searchbyphone(addressBook);
            break;
        case 3:
            searchbyemail(addressBook);
            break;
        default:
            printf("Invalid choice!\n");
    }
}
void searchbyname(AddressBook *addressBook)
{
    char name[50];
    int attempts = 0;
    mapcount = 0;  
    while(attempts < 3)
    {
        printf("Enter Name: ");
        scanf(" %[^\n]", name);
        if(isvalidname(name))
            break;
        printf("Invalid name!\n");
        attempts++;
    }
    if(attempts == 3)
        return;
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(name, addressBook->contacts[i].name) == 0)
        {
            printcontact(mapcount, &addressBook->contacts[i]);
            indexmap[mapcount] = i;
            mapcount++;
        }
    }
    if(mapcount == 0)
        printf("Contact not found!\n");
}
void searchbyphone(AddressBook *addressBook)
{
    char phone[20];
    int attempts = 0;
    mapcount = 0;  
    while(attempts < 3)
    {
        printf("Enter phone no: ");
        scanf(" %[^\n]", phone);

        if(isvalidphone(phone))
            break;
        printf("Invalid phone no!\n");
        attempts++;
    }
    if(attempts == 3)
        return;
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(phone, addressBook->contacts[i].phone) == 0)
        {
            printcontact(mapcount, &addressBook->contacts[i]);
            indexmap[mapcount] = i;
            mapcount++;
        }
    }
    if(mapcount == 0)
        printf("Contact not found!\n");
}
void searchbyemail(AddressBook *addressBook)
{
    char email[50];
    int attempts = 0;
    mapcount = 0;  
    while(attempts < 3)
    {
        printf("Enter email: ");
        scanf(" %[^\n]",email);
        if(isvalidemail(email))
            break;
        printf("Invalid email!\n");
        attempts++;
    }
    if(attempts == 3)
        return;
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(email, addressBook->contacts[i].email) == 0)
        {
            printcontact(mapcount, &addressBook->contacts[i]);
            indexmap[mapcount] = i;
            mapcount++;
        }
    }
    if(mapcount == 0)
        printf("Contact not found!\n");
}
void editContact(AddressBook *addressBook)
{
    searchContact(addressBook);
    if(mapcount==0)
    return; 
    int attempts=0;
    int serial;
    while(attempts<3){
    printf("Enter serial number to edit: ");
        scanf("%d", &serial);
        if(serial >= 1 && serial <= mapcount)
            break;
        printf("Invalid selection!\n");
        attempts++;
    }
    if(attempts == 3)
    {
        printf("Too many invalid attempts!\n");
        return;
    }
    int index = indexmap[serial - 1];
    int choice;
    printf("\nEdit Menu:\n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("4. Exit\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
   attempts=0;
   switch(choice)
   {
    case 1:{
        char name[50];
            while(attempts < 3)
            {
                printf("Enter new name: ");
                scanf(" %[^\n]", name);

                if(isvalidname(name))
                {
                    strcpy(addressBook->contacts[index].name, name);
                    printf("Name updated successfully!\n");
                    return;
                }
                printf("Invalid name!\n");
                attempts++;
            }
            break;
    }
    case 2:{
        char phone[20];
        while(attempts<3)
        {
            printf("enter new phone no: ");
            scanf("%s",phone);
            if(isvalidphone(phone))
            {
                strcpy(addressBook->contacts[index].phone,phone);
                printf("phone no is updated successfully\n");
                return;
            }
            printf("invalid phone no!\n");
        }
        break;
    }
    case 3:{
        char email[50];
            while(attempts < 3)
            {
                printf("Enter new email: ");
                scanf("%s", email);

                if(isvalidemail(email))
                {
                    strcpy(addressBook->contacts[index].email, email);
                    printf("Email updated successfully!\n");
                    return;
                }
                printf("Invalid email!\n");
                attempts++;
            }
            break;
    }
    case 4:
       return;
    default:
     printf("Invalid choice!\n");
      return;
   }
    printf("Too many invalid attempts!\n");    
}
void deleteContact(AddressBook *addressBook)
{
	searchContact(addressBook);
    if(mapcount==0)
    return;
    int serial,attempts=0;
    while(attempts<3){
        printf("enter the serial number to delete: ");
        scanf("%d",&serial);
        if(serial >= 1 && serial <= mapcount)
            break;
        printf("Invalid selection!\n");
        attempts++;
    }
    if(attempts == 3)
    {
        printf("Too many invalid attempts!\n");
        return;
    }
    int index = indexmap[serial - 1];  
    for(int i = index; i < addressBook->contactCount - 1; i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }
    addressBook->contactCount--;
    printf("Contact deleted successfully!\n");
}
