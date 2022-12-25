//Declaring headers
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include"header.h"

//To make the code optimized for designing we use this function
void design()
{	
	int i;
	for(i=0;i<90;i++)
		printf("*");
	printf("\n");
}
//Main menu of the quiz game
int main_menu()
{
	int ch,admin_pswd_flag = 0;
	char user[20];
	char password[20];
	admin_data admin_root ;
	while(1)
	{
		//selection of user type
		printf("1) Admin\n");
		printf("2) Coordinator\n");
		printf("3) Contestant\n");
		scanf("%d",&ch);
		switch(ch)
		{
			case ADMIN: 
				admin_root = read_admin_file(admin_root);
				while(1)
				{
					printf("enter the user name \n");
					getchar();
					fgets(user,20,stdin);
					user[strlen(user)-1] = '\0';
					strcpy(password,getpass("Enter Password: "));
					if(strcmp(admin_root.user_name,user) == 0)
					{
						if(strcmp(admin_root.pswd,password ) == 0)
						{
							admin();
							break;
						}
					}
					else 
					{
						admin_pswd_flag++;
						printf("please enter correct Password \n");
					}
					
					if(admin_pswd_flag == 3)
					{
						printf("Too many attempts please try again\n");
						break;
					}
				}
				break;
			case COORDINATOR:
				Coordinator() ;
				break;
			case CONTESTANT: 
				Contestant();
				break;	
			default: printf("\nInvalid Choice");
		}
	}	
}
//Admin data reading from file
admin_data read_admin_file(admin_data source)
{
	char *str = "admin_info.txt";
	FILE *fptr = NULL ;
	char *piece ;
	char buffer[QUESTION_BUFFER_SIZE];
	int index = 1;
	fptr = fopen(str,"r");
	if(fptr == NULL)
	{
		printf("%s file opening error\n",str);
	}	
	else 
	{
		while(!feof(fptr))
		{
			if(!(fgets(buffer,QUESTION_BUFFER_SIZE,fptr)))
			{
				break ;
			}
			else 
			{
				piece = strtok(buffer,",");
				while(piece !=NULL)
				{
					if(index == 1)
					{
						strcpy(source.user_name ,piece );
						source.user_name[strlen(source.user_name)] = '\0';
						index = 2;	
					}
					else if(index == 2)
					{
						strcpy(source.pswd ,piece );
						source.pswd[strlen(source.pswd)-1] = '\0';
					}
					piece = strtok(NULL,",");
				}
			}	
			
		}
	}
	return source ;	
}	

