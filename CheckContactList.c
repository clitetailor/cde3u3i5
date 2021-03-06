#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>



#include "ContactList.h"

void CommandLineInterface()
{
	ContactList * a;
	
	initializeContactList(&a);
	
	int selection;
	do
	{
		ContactListMenu(a);
		printf("\n\nNhap vao lenh ban muon thuc hien (1-5):");
		
		fflush(stdin);
		scanf("%d", &selection);
		
		if (selection < 1 || selection > 5)
		{
			printf("\nLenh nhap vao khong thoa man!\n");
			continue;
		}
		
		manageContactListCommand(a, selection);
		
		Sleep(500);
	} while (selection != 5);
	
	printf("\nChuong trinh dang thoat! ");
					Sleep(250);
					printf(".");
					Sleep(250);
					printf(".");
					Sleep(250);
					printf(".\n\n");
}

void ContactListMenu(ContactList *a)
{
	int menusize = 5;
	char ** menu;
	
	printf("\nTrong so dia chi co %d dia chi\n", a->size);
	
	printf("\nDanh sach cac lenh:\n");
	
	menu = (char **) malloc(sizeof(char *) * menusize);
	
	menu[0] = "Hien thi so dia chi";
	menu[1] = "Chon dia chi";
	menu[2] = "Them dia chi";
	menu[3] = "Xoa dia chi";
	menu[4] = "Thoat khoi chuong trinh";
	
	int i;
	for (i = 0; i < menusize; ++i)
	{
		printf("\n\t%d, %s", i+1, menu[i]);
	}
	
	printf("\n");
}

void manageContactListCommand(ContactList *a, int command)
{
	switch(command)
	{
		case 1:
				{
					// Print all
					int i;
					Node * currentNode;
					
					printf("\nSo dia chi:\n");
					currentNode = a->head;
					
					for (i = 0; i < a->size; ++i)
					{
						printf("\n\t%d, %s", i+1, getString(currentNode));
						currentNode = currentNode->next;
					}
					
					printf("\n");
					break;
				}
		case 2:
				{
					// Select Contact 
					
					int selection;
					
					if (a->size == 0)
					{
						printf("\nKhong co dia chi nao de chon!\n");
						break;
					}
					
					if (a->size == 1)
					{
						selection = 1;
					}
					else
					{
						printf("\nNhap vao dia chi ban muon chon (1-%d):", a->size);
						
						fflush(stdin);
						scanf("%d", &selection);
					}
					
					Node * selectedNode;
					selectedNode = getNode(a, selection - 1);
					
					if (selectedNode == NULL)
					{
						printf("\nKhong co dia chi ban muon chon!\n");
						break;
					}
					
					Sleep(500);
					do
					{
						ContactMenu();
						printf("\n\nNhap vao lenh ban muon thuc hien (1-9):");
						
						fflush(stdin);
						scanf("%d", &selection);
						
						manageContactCommand( (Contact *) selectedNode->data, selection);
						
						if (selection < 1 || selection > 9)
						{
							printf("\nNhap vao khong hop le!\n");
						}
						
						Sleep(500);
					} while (selection != 9);
					
					break;
				}
		case 3:
				{
					// Add contact
					char name[MAX_STRING_SIZE + 2];
					do
					{
						printf("\nNhap vao ten dia chi:");
						fflush(stdin);
						fgets(name, MAX_STRING_SIZE + 2, stdin);
						
						if ( strlen(name) > MAX_STRING_SIZE )
						{
							printf("\nDo dai vuot qua %d. Yeu cau nhap lai!\n", MAX_STRING_SIZE-1);
						}
						
					} while ( strlen(name) > MAX_STRING_SIZE );
					
					addContact(a, name);
					
					break;
				}
		case 4:
				{
					// Remove contact
					if (a->size == 0)
					{
						printf("\nKhong co dia chi nao de xoa!\n");
						break;
					}
					
					if (a->size == 1)
					{
						char c;
						printf("\nBan co muon xoa dia chi (Y/N):");
						fflush(stdin);
						scanf("%c", &c);
						if (c == 'Y' || c == 'y')
						{
							removeContact(a, 0);
						}
						
						break;
					}
					else
					{
						int i;
						printf("\nNhap vao dia chi ban muon xoa (1-%d):", a->size);
						fflush(stdin);
						scanf("%d", &i);
						
						if (!removeContact(a, i-1))
						{
							printf("\nKhong co dia chi ban muon xoa!\n");
						}
					}
					
					break;
				}
		case 5:
				{
					// Exit
					break;
				}
	}
};



void ContactMenu()
{
	int menusize = 9;
	char ** menu;
	
	printf("\nDanh sach cac lenh:\n");
	
	menu = (char **) malloc(sizeof(char *) * menusize);
	
	menu[0] = "Hien thong tin lien lac";
	menu[1] = "Doi ten";
	menu[2] = "Them email";
	menu[3] = "Xoa email";
	menu[4] = "Them dia chi";
	menu[5] = "Xoa dia chi";
	menu[6] = "Them so dien thoai";
	menu[7] = "Xoa so dien thoai";
	menu[8] = "Thoat";
	
	int i;
	for (i = 0; i < menusize; ++i)
	{
		printf("\n\t%d, %s", i+1, menu[i]);
	}
	
	free(menu);
	
	printf("\n");
}

void manageContactCommand(Contact *a, int command)
{
	switch (command)
	{
		case 1:
				{
					// Print
					printf("\nThong tin dia chi:\n");
					printf("\n\tTen: %s", a->Name);
					
					Node * currentNode;
					int i;
					
					printf("\n\tEmail:\n");
					currentNode = a->Email->head;
					for (i = 0; i < a->Email->size; ++i)
					{
						printf("\n\t\t%d, %s", i+1, getString(currentNode));
						currentNode = currentNode->next;
					}
					
					printf("\n\tAddress:\n");
					currentNode = a->Address->head;
					for (i = 0; i < a->Address->size; ++i)
					{
						printf("\n\t\t%d, %s", i+1, getString(currentNode));
						currentNode = currentNode->next;
					}
					
					printf("\n\tPhone:\n");
					currentNode = a->Phone->head;
					for (i = 0; i < a->Phone->size; ++i)
					{
						printf("\n\t\t%d, %s", i+1, getString(currentNode));
						currentNode = currentNode->next;
					}
					
					break;
				}
		case 2:
				{
					// Change contact name
					char name[MAX_STRING_SIZE + 2];
					do
					{
						printf("\nTen:");
						fflush(stdin);
						fgets(name, MAX_STRING_SIZE + 2, stdin);
						
						if ( strlen(name) > MAX_STRING_SIZE )
						{
							printf("\nDo dai vuot qua %d. Yeu cau nhap lai!\n", MAX_STRING_SIZE-1);
						}
						
					} while ( strlen(name) > MAX_STRING_SIZE );
					
					changeContactName(a, name);
					
					break;
				}
		case 3:
				{
					// Add an email address
					char email[MAX_STRING_SIZE + 2];
					printf("\nEmail:");
					
					do
					{
						fflush(stdin);
						fgets(email, MAX_STRING_SIZE + 2, stdin);
						
						if ( strlen(email) > MAX_STRING_SIZE )
						{
							printf("\nDo dai vuot qua %d. Yeu cau nhap lai!\n", MAX_STRING_SIZE-1);
						}
						
					} while ( strlen(email) > MAX_STRING_SIZE );
					
					addEmail(a, email);
					
					break;
				}
		case 4:
				{
					// Remove an email address
					
					if (a->Email->size == 0)
					{
						printf("\nKhong co email nao de xoa!\n");
					}
					
					if (a->Email->size == 1)
					{
						char c;
						printf("\nBan co muon xoa email (Y/N):");
						fflush(stdin);
						scanf("%c", &c);
						
						if (c == 'Y' || c == 'y')
						{
							removeEmail(a, 0);
						}
						
						break;
					}
					else
					{
						int selection;
						printf("\nNhap vao email ban muon xoa (1-%d):", a->Email->size);
						fflush(stdin);
						scanf("%d", &selection);
						
						if (!removeEmail(a, selection - 1))
						{
							printf("\nKhong co email ban muon xoa!\n");
						}
					}
					
					break;
				}
		case 5:
				{
					// Add an address
					char address[MAX_STRING_SIZE + 2];
					printf("\nAddress:");
					
					do
					{
						fflush(stdin);
						fgets(address, MAX_STRING_SIZE + 2, stdin);
						
						if ( strlen(address) > MAX_STRING_SIZE )
						{
							printf("\nDo dai vuot qua %d. Yeu cau nhap lai!\n", MAX_STRING_SIZE-1);
						}
						
					} while ( strlen(address) > MAX_STRING_SIZE );
					
					addAddress(a, address);
					
					break;
				}
		case 6:
				{
					// Remove an address
					
					if (a->Address->size == 0)
					{
						printf("\nKhong co dia chi nao de xoa!\n");
					}
					
					if (a->Address->size == 1)
					{
						char c;
						printf("\nBan co muon xoa dia chi (Y/N):");
						fflush(stdin);
						scanf("%c", &c);
						
						if (c == 'Y' || c == 'y')
						{
							removeEmail(a, 0);
						}
						
						break;
					}
					else
					{
						int selection;
						printf("\nNhap vao dia chi ban muon xoa (1-%d):", a->Address->size);
						fflush(stdin);
						scanf("%d", &selection);
						
						if (!removeAddress(a, selection - 1))
						{
							printf("\nKhong co dia chi ban muon xoa!\n");
						}
					}
					
					break;
				}
		case 7:
				{
					// Add a phone number
					char phone[MAX_STRING_SIZE + 2];
					
					bool retval;
					do
					{
						printf("\nNumber:");
						fflush(stdin);
						fgets(phone, MAX_STRING_SIZE + 2, stdin);
						
						if ( strlen(phone) > MAX_STRING_SIZE )
						{
							printf("\nDo dai vuot qua %d. Yeu cau nhap lai!\n", MAX_STRING_SIZE-1);
						}
						
						int i;
						retval = true;
						for (i = 0; i < strlen(phone) - 1; ++i)
						{
							if (phone[i] < '0' || phone[i] > '9')
							{
								retval = false;
							}
						}
						
						if (retval == false)
						{
							printf("\nSo dien thoai nhap vao khong hop le. Yeu cau nhap lai!\n");
						}
						
					} while ( strlen(phone) > MAX_STRING_SIZE || retval != true );
					
					addPhone(a, phone);
					break;
				}
		case 8:
				{
					// Remove a phone number
					if (a->Phone->size == 0)
					{
						printf("\nKhong co so dien thoai nao de xoa!\n");
						break;
					}
					
					if (a->Phone->size == 1)
					{
						char c;
						printf("\nBan co muon xoa so dien thoai (Y/N):");
						fflush(stdin);
						scanf("%c", &c);
						
						if (c == 'Y' || c == 'y')
						{
							removePhone(a, 0);
						}
						
						break;
					}
					else
					{
						int selection;
						printf("\nNhap vao dia chi dien thoai ban muon xoa (1-%d):", a->Phone->size);
						fflush(stdin);
						scanf("%d", &selection);
						
						if (!removePhone(a, selection - 1))
						{
							printf("\nKhong co so dien thoai ban muon xoa!\n");
						}
					}
					
					break;
				}
		case 9:
				{
					// Exit
					break;
				}
	}
}

// main()


int main(int argc, char ** argv)
{
	CommandLineInterface();
	
	return 0;
}