#include <stdio.h>
#include <string.h>

#define MAX 100

struct Contact
{
    char name[50];
    char phone[30];
    char email[50];
};
struct Contact contact[MAX];
int total = 0;
void merge(int left, int mid, int right)
{
    int i = left;
    int j = mid + 1;
    int k = 0;
    struct Contact temp[MAX];

    while(i <= mid && j <= right)
    {
        if(strcmp(contact[i].name, contact[j].name) < 0)
        {
            temp[k++] = contact[i++];
        }
        else
        {
            temp[k++] = contact[j++];
        }
    }

    while(i <= mid)
    {
        temp[k++] = contact[i++];
    }

    while(j <= right)
    {
        temp[k++] = contact[j++];
    }

    for(i = left, k = 0; i <= right; i++, k++)
    {
        contact[i] = temp[k];
    }
}

void mergeSort(int left, int right)
{
    if(left < right)
    {
        int mid = (left + right) / 2;

        mergeSort(left, mid);
        mergeSort(mid + 1, right);

        merge(left, mid, right);
    }
}
int binarySearch(char key[])
{
    int low = 0;
    int high = total - 1;

    while(low <= high)
    {
        int mid = (low + high) / 2;

        int cmp = strcmp(contact[mid].name, key);

        if(cmp == 0)
        {
            return mid;
        }
        else if(cmp < 0)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    return -1;
}
int searchByPhone(char phone[])
{
    for(int i = 0; i < total; i++)
    {
        if(strcmp(contact[i].phone, phone) == 0)
        {
            return i;
        }
    }

    return -1;
}
int searchByEmail(char email[])
{
    for(int i = 0; i < total; i++)
    {
        if(strcmp(contact[i].email, email) == 0)
        {
            return i;
        }
    }

    return -1;
}
int validPhone(char phone[])
{
    int i = 0;
    if(strcmp(phone, "0") == 0)
    {
        return 1;
    }
    if(phone[0] == '+')
    {
        i = 1;
    }
    if(phone[i] == '\0')
    {
        return 0;
    }
    for(; phone[i] != '\0'; i++)
    {
        if(phone[i] < '0' || phone[i] > '9')
        {
            return 0;
        }
    }

    return 1;
}
int validEmail(char email[])
{
    int at = 0, dot = 0;

    if(strcmp(email,"0")==0)
        return 1;

    for(int i=0; email[i]!='\0'; i++)
    {
        if(email[i]=='@')
            at++;

        if(email[i]=='.')
            dot++;
    }

    if(at==1 && dot>=1)
        return 1;

    return 0;
}
void addContact()
{
    if(total == MAX)
    {
        printf("\nPhonebook Full!\n");
        return;
    }
    char name[50];
    char phone[30];
    char email[50];
    printf("\nEnter Name : ");
    fflush(stdout);
    scanf(" %[^\n]", name);

    printf("Enter Phone (or 0 to skip): ");
    fflush(stdout);
    scanf(" %[^\n]", phone);

    printf("Enter Email (or 0 to skip): ");
    fflush(stdout);
    scanf(" %[^\n]", email);
    int phoneOk = validPhone(phone);
    int emailOk = validEmail(email);
    if(!phoneOk)
    {
        strcpy(phone, "0");
    }
    if(!emailOk)
    {
        strcpy(email, "0");
    }
    if(strcmp(phone, "0") == 0 && strcmp(email, "0") == 0)
    {
        printf("\nInvalid Contact! Enter at least a valid Phone Number or Email Address.\n");
        return;
    }
    for(int i = 0; i < total; i++)
    {
        if(strcmp(contact[i].name, name) == 0)
        {
            printf("\nDuplicate Contact Name!\n");
            return;
        }
        if(strcmp(phone, "0") != 0 &&
                strcmp(contact[i].phone, phone) == 0)
        {
            printf("\nDuplicate Phone Number!\n");
            return;
        }
        if(strcmp(email, "0") != 0 &&
                strcmp(contact[i].email, email) == 0)
        {
            printf("\nDuplicate Email Address!\n");
            return;
        }
    }

    strcpy(contact[total].name, name);
    strcpy(contact[total].phone, phone);
    strcpy(contact[total].email, email);

    total++;

    printf("\nContact Added Successfully!\n");
}
void display()
{
    if(total == 0)
    {
        printf("\nNo Contacts Available.\n");
        return;
    }

    printf("\n----------------------------------------------------------------------\n");
    printf("%-5s %-20s %-20s %-25s\n","No.","Name","Phone","Email");
    printf("----------------------------------------------------------------------\n");

    for(int i = 0; i < total; i++)
    {
        printf("%-5d %-20s %-20s %-25s\n",
               i + 1,
               contact[i].name,
               contact[i].phone,
               contact[i].email);
    }

    printf("----------------------------------------------------------------------\n");
}
void sortContacts()
{
    if(total == 0)
    {
        printf("\nNo Contacts.\n");
        return;
    }

    mergeSort(0, total - 1);

    printf("\nContacts Sorted Successfully.\n");
}
void searchContact()
{
    if(total == 0)
    {
        printf("\nNo Contacts Available.\n");
        return;
    }

    int choice;
    int index = -1;

    printf("\nSearch Contact By\n");
    printf("1. Name\n");
    printf("2. Phone Number\n");
    printf("3. Email\n");
    printf("Enter Choice : ");
    fflush(stdout);

// Added non-integer input protection
    if (scanf("%d", &choice) != 1)
    {
        while (getchar() != '\n');
        printf("\nInvalid Input!\n");
        return;
    }

    if(choice == 1)
    {
        mergeSort(0, total - 1);

        char name[50];
        printf("\nEnter Name : ");
        fflush(stdout);
        scanf(" %[^\n]", name);

        index = binarySearch(name);
    }
    else if(choice == 2)
    {
        char phone[30];

        printf("\nEnter Phone Number : ");
        scanf(" %[^\n]", phone);

        index = searchByPhone(phone);
    }
    else if(choice == 3)
    {
        char email[50];

        printf("\nEnter Email : ");
        scanf(" %[^\n]", email);

        index = searchByEmail(email);
    }
    else
    {
        printf("\nInvalid Choice!\n");
        return;
    }

    if(index == -1)
    {
        printf("\nContact Not Found.\n");
    }
    else
    {
        printf("\nContact Found\n");
        printf("------------------------------\n");
        printf("Name  : %s\n", contact[index].name);
        printf("Phone : %s\n", contact[index].phone);
        printf("Email : %s\n", contact[index].email);
    }
}
void updateContact()
{
    if(total == 0)
    {
        printf("\nNo Contacts Available.\n");
        return;
    }
    int searchChoice;
    int updateChoice;
    int index = -1;
    char name[50];
    char phone[30];
    char email[50];
   printf("\nFind Contact By\n");
printf("1. Name\n");
printf("2. Phone Number\n");
printf("3. Email\n");
printf("Enter Choice : ");
fflush(stdout);

if (scanf("%d", &searchChoice) != 1)
{
    while (getchar() != '\n');
    printf("\nInvalid Input!\n");
    return;
}
    if(searchChoice == 1)
    {
        mergeSort(0,total-1);

        printf("\nEnter Name : ");
        scanf(" %[^\n]",name);

        index = binarySearch(name);
    }
    else if(searchChoice == 2)
    {
        printf("\nEnter Phone Number : ");
        scanf(" %[^\n]",phone);

        index = searchByPhone(phone);
    }
    else if(searchChoice == 3)
    {
        printf("\nEnter Email : ");
        scanf(" %[^\n]",email);
        index = searchByEmail(email);
    }
    else
    {
        printf("\nInvalid Choice!\n");
        return;
    }
    if(index == -1)
    {
        printf("\nContact Not Found.\n");
        return;
    }
    printf("\nUpdate");
    printf("\n1. Phone Number");
    printf("\n2. Email");
    printf("\n3. Both");
    printf("\nEnter Choice : ");
    scanf("%d",&updateChoice);
    switch(updateChoice)
    {
    case 1:
        printf("Enter New Phone : ");
        scanf(" %[^\n]",phone);
        if(strcmp(phone,"0")==0 &&
                strcmp(contact[index].email,"0")==0)
        {
            printf("\nA contact must have Phone or Email.\n");
            return;
        }
        for(int i=0; i<total; i++)
        {
            if(i!=index &&
                    strcmp(phone,"0")!=0 &&
                    strcmp(contact[i].phone,phone)==0)
            {
                printf("\nDuplicate Phone Number!\n");
                return;
            }
        }
        strcpy(contact[index].phone,phone);
        printf("\nPhone Updated Successfully!\n");
        break;
    case 2:
        printf("Enter New Email : ");
        scanf(" %[^\n]",email);
        if(strcmp(email,"0")==0 &&
                strcmp(contact[index].phone,"0")==0)
        {
            printf("\nA contact must have Phone or Email.\n");
            return;
        }
        for(int i=0; i<total; i++)
        {
            if(i!=index &&
                    strcmp(email,"0")!=0 &&
                    strcmp(contact[i].email,email)==0)
            {
                printf("\nDuplicate Email Address!\n");
                return;
            }
        }
        strcpy(contact[index].email,email);

        printf("\nEmail Updated Successfully!\n");
        break;
    case 3:
        printf("Enter New Phone : ");
        scanf(" %[^\n]",phone);
        printf("Enter New Email : ");
        scanf(" %[^\n]",email);
        if(strcmp(phone,"0")==0 &&
                strcmp(email,"0")==0)
        {
            printf("\nA contact must have Phone or Email.\n");
            return;
        }
        for(int i=0; i<total; i++)
        {
            if(i!=index &&
                    strcmp(phone,"0")!=0 &&
                    strcmp(contact[i].phone,phone)==0)
            {
                printf("\nDuplicate Phone Number!\n");
                return;
            }
            if(i!=index &&
                    strcmp(email,"0")!=0 &&
                    strcmp(contact[i].email,email)==0)
            {
                printf("\nDuplicate Email Address!\n");
                return;
            }
        }
        strcpy(contact[index].phone,phone);
        strcpy(contact[index].email,email);
        printf("\nContact Updated Successfully!\n");
        break;
    default:
        printf("\nInvalid Choice!\n");
    }
}
void deleteContact()
{
    if(total == 0)
    {
        printf("\nNo Contacts Available.\n");
        return;
    }
    int choice;
    int index = -1;
    char name[50];
    char phone[30];
    char email[50];
    printf("\nDelete Contact By\n");
    printf("1. Name\n");
    printf("2. Phone Number\n");
    printf("3. Email\n");
    printf("Enter Choice : ");
    scanf("%d",&choice);
    if(choice == 1)
    {
        mergeSort(0,total-1);
        printf("\nEnter Name : ");
        scanf(" %[^\n]",name);
        index = binarySearch(name);
    }
    else if(choice == 2)
    {
        printf("\nEnter Phone Number : ");
        scanf(" %[^\n]",phone);

        index = searchByPhone(phone);
    }
    else if(choice == 3)
    {
        printf("\nEnter Email : ");
        scanf(" %[^\n]",email);
        index = searchByEmail(email);
    }
    else
    {
        printf("\nInvalid Choice!\n");
        return;
    }
    if(index == -1)
    {
        printf("\nContact Not Found.\n");
        return;
    }
    for(int i = index; i < total - 1; i++)
    {
        contact[i] = contact[i + 1];
    }
    total--;
    printf("\nContact Deleted Successfully!\n");
}
int main()
{
    int choice = 0;

    while(1)
    {
        printf("\n");
        printf("=========================================\n");
        printf("              PHONEBOOK APP              \n");
        printf("=========================================\n");
        printf("1. Add Contact\n");
        printf("2. Display Contacts\n");
        printf("3. Sort Contacts\n");
        printf("4. Search Contact\n");
        printf("5. Update Contact\n");
        printf("6. Delete Contact\n");
        printf("7. Exit\n");
        printf("=========================================\n");
        printf("Enter Choice : ");
        fflush(stdout);

        if (scanf("%d", &choice) != 1)
        {
            printf("\nInvalid Input! Please enter a number between 1 and 7.\n");


            while (getchar() != '\n');
            continue;
        }

        switch(choice)
        {
        case 1:
            addContact();
            break;

        case 2:
            display();
            break;

        case 3:
            sortContacts();
            break;

        case 4:
            searchContact();
            break;

        case 5:
            updateContact();
            break;

        case 6:
            deleteContact();
            break;

        case 7:
            printf("\nThank You for Using Phonebook App.\n");
            return 0; // Exits main function and stops the program loop

        default:
            printf("\nInvalid Choice! Please choose a number from 1 to 7.\n");
        }
    }

    return 0;
}

