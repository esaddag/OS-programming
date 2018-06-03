#include <stdio.h>

#define LIST_SIZE 50

struct MailingList {
	char name[50];
	char surname[50];
	char address[50];
};

void printList(struct MailingList *list);
void deleteItem(struct MailingList *list);
void printMenu();


int main()
{
	struct MailingList *mailList = malloc(50*sizeof(struct MailingList));
	int i=0;
	for(i=0; i<LIST_SIZE; i++) {
		(mailList+i)->name[0] = '\0';
		(mailList+i)->surname[0] = '\0';
		(mailList+i)->address[0] = '\0';
	}
	
	while(1)
	{
		printMenu();
		int menuID;
		scanf("%d", &menuID);
		
		switch(menuID){
			
			case 1:
				addNewItem(mailList);
				break;
			case 2:
				deleteItem(mailList);
				break;
			case 3:
				printList(mailList);
				break;
			case 4:
				printf("Ciao!\n");
				exit(0);
			default:
				exit(0);
		}
	}
	system("pause");
	return 0;
}

void printList(struct MailingList *list)
{
	int i=0;
	for(i=0; i<LIST_SIZE; i++)
	{
		if((list+i)->name[0] != '\0') {
			printf("Name: %s\n",(list+i)->name);
			printf("Surname: %s\n",(list+i)->surname);
			printf("Address: %s\n\n",(list+i)->address);
		}
	}
}

void deleteItem(struct MailingList *list)
{
	printf("\nPlease enter the index number you want to delete");
	int index=0;
	scanf("%d",&index);
	if((list+index) != NULL)
	{
		(list+index)->name[0] = '\0';
		(list+index)->surname[0] = '\0';
		(list+index)->address[0] = '\0';
	}
	else
		printf("\nAlready deleted...");
	
}

void addNewItem(struct MailingList *list)
{
	int i=0;
	int counter = 0;
	for(i=0; i<LIST_SIZE; i++)
	{
		if((list+i)->name[0] == '\0')
		{
			printf("Please Enter Name: ");
			scanf("%s",(list+i)->name);
			printf("\nPlease Enter Surame: ");
			scanf("%s",(list+i)->surname);
			printf("\nPlease Enter Address: ");
			scanf("%s",(list+i)->address);
			break;
		}
		else
			counter;
	}
	if(counter == LIST_SIZE)
			printf("Sorry No Empty Slots\n");
}

void printMenu()
{
	printf("\n\t\t\tMENU");
	printf("\n1.\tEnter a New Data.");
	printf("\n2.\tDelete the selected slot.");
	printf("\n3.\tList All Items.");
	printf("\n4.\tEXIT.\n");
	printf("\nPlease enter the number [1-4] for any action given below:");
}
