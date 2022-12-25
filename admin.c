#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"header.h"
coordinator *c_root = NULL;
extern contestant *co_root;
int len_list(coordinator *p)
{
	int count = 0;
	while(p!=NULL)
	{
		count++;
		p = p->next;
	}
	return count;
}

void admin()
{
	int ch , exit_flag_1 = 0 , exit_flag_2 = 0 , exit_flag_3 = 0 ;
	static int chek_list_flag = 0 ;
	design();
	printf("Wellcome to Admin \n");
	char user_id[BUFFER_SIZE];
	
	
	while(1)
	{
		design(); 
		printf("1) Manage Coordinator details\n");
		printf("2) Manage Contestant details\n");
		printf("3) Logout and exit\n");
		design();
		scanf("%d",&ch);
		
		switch(ch)
		{
			case 1:
				if(chek_list_flag == 0)
				{ 
					chek_list_flag = 1;
					c_root = new_coordinator(c_root);
				}	
				while(1)
				{
					design();
					printf("1) New Coordinator \n");
					printf("2) Update Coordinator \n");
					printf("3) Delete Coordinator \n");
					printf("4) Display Coordinator list\n");
					printf("5) Back to previous menu\n");
					design();
					
					//save_coordinator_data_into_file(c_root);
					scanf("%d",&ch);
					
					switch(ch)
					{
						case 1:
							adding_new_coordinator_to_file();
							c_root = new_coordinator(c_root);
							break;
						case 2:
							printf("enter user-id \n");
							scanf("%s",user_id);
							if((c_root = update_coordinator(user_id , c_root)) == NULL)
							{
								printf("user-id is not found please enter correct user id %s\n",user_id);
							}
							else 
							{
								save_coordinator_data_into_file(c_root);
								printf("updated succesfully\n");
							}
							
							break;
						case 3:
							printf("enter user-id \n");
							scanf("%s",user_id);
							c_root = delete_coordinator(user_id , c_root);
							save_coordinator_data_into_file(c_root);
							break;
						case 4:
							display_coordinator(c_root);
							break;
						case 5:
							exit_flag_1 =1;
							
					}
					
					if(exit_flag_1 == 1)
						break;
				}	
				break ;
				
			case 2:
				while(1)
				{
					design();
					printf("1) Delete Contestant\n");
					printf("2) View contestant\n");
					printf("3) Back\n");
					design();
					scanf("%d",&ch);
					
					switch(ch)
					{
						case 1:
							delete_contestant();
							break ;
						case 2: view_contestant();
							break;
						case 3:
							exit_flag_2 = 1;	
					}
					
					if(exit_flag_2 == 1)
						break;
				}
				break ;
				
			case 3:
				exit_flag_3 = 1;
				break ;
				
			
		}
		
		if(exit_flag_3 == 1)
			break;
	}
}
coordinator *create_list_for_cordinator(coordinator *source ,coordinator Data )
{
	if(source == NULL)
	{
		source  = (coordinator *)malloc(sizeof(coordinator));
		
		strcpy(source->name ,Data.name);
	
		strcpy(source->userid , Data.userid);
		
		source->phone_num = Data.phone_num;
		
		strcpy(source->Email_id, Data.Email_id);
		
		strcpy(source->pswd , Data.pswd);
		
	
		source->next = NULL;
	}
	else 
	{
		coordinator *p = source ;	
		coordinator *temp = (coordinator *) malloc(sizeof(coordinator));
		
		strcpy(temp->name ,Data.name);
	
		strcpy(temp->userid , Data.userid);
		
		temp->phone_num = Data.phone_num;
		
		strcpy(temp->Email_id, Data.Email_id);
		
		strcpy(temp->pswd , Data.pswd);
		 while(p->next != NULL)
		 {
		 	p = p->next ;
				 	
		 }
		 
		p->next = temp ;
		temp->next = NULL ;
		 
	}
	
return source ;
}
coordinator *new_coordinator(coordinator *source)
{
	char *cordinator_file = "coordinator_info.txt";
	char buffer[QUESTION_BUFFER_SIZE];
	coordinator c_data ;
	
	FILE *fptr = fopen(cordinator_file,"r");
	if(fptr == NULL)
	{
		printf("%s file is not found\n",cordinator_file);
	}
	else 
	{
		while(!feof(fptr))
		{
		
			if(!(fgets(buffer,QUESTION_BUFFER_SIZE,fptr)))
			{
				//printf("string reading is fail\n");
				break ;
			}
			else 
			{		
			 	c_data = data_extraction_from_cordinator_file(buffer ,  c_data);
			 		//printf("cordinator name %s and cordinator -id %s\n",c_data.name ,c_data.userid );
			 	 source = create_list_for_cordinator(source , c_data);
			}
		}
	}
	
	fclose(fptr);	
	return source;	
}	

coordinator *update_coordinator(char *str , coordinator *source)
{

	int flag = 0;
	char ch ;
	//printf("%s\n",str);
	coordinator *p = source ;	
	char buffer[20];
	
	while(p!= NULL)
	{
		if(strcmp(p->userid , str) == 0)
		{
		
		
			flag =1 ;
			
			printf("user-id is %s\n",p->userid);
			printf("name is %s\n",p->name);
			printf("phone number %ld\n",p->phone_num);
			printf("Email-id %s\n",p->Email_id);
			printf("pswd is %s\n",p->pswd);
			
			printf("enter y to update\n");
			scanf(" %c",&ch);
			if(ch == 'y' || ch == 'Y')
			{
			
				printf("enter the user name \n");
				getchar();
				fgets(p->name , 20 , stdin);
				p->name[strlen(p->name)-2] = '\0';

				printf("enter phone number\n");
				scanf("%ld",&p->phone_num);
				
				printf("enter the email-id\n");
				getchar();
				fgets(p->Email_id , 20 , stdin);
				p->Email_id[strlen(p->Email_id)-1] = '\0'; 
				
				printf("enter the password\n");
				scanf("%s",p->pswd);	
			}
			
			break;
		}
		
		p = p->next ;
	}

if(flag == 0)
	return NULL ;
else 
	return source ;
		
}

void display_coordinator(coordinator *source)
{
	while(source != NULL)
	{
		printf("user-name is %s user-id is %s \n",source->name , source->userid);
		
		
		source = source->next ;
	}

}

int* len_of_list_coordinator(coordinator  *source ,int *index)
{
	int count =0 ;
	
	if(source ==  NULL)
	{
		printf("list is empty\n") ;
		return NULL ;
	}
	
	
	coordinator   *p = source ;
	
	while(p!=NULL)
	{
		count ++;	
		p = p->next ;
	}
	
	*index = count ;
	
	return index ;	
}


int *lookup_coordinator(coordinator *source, char *str , int *index )
{
	
	
	 int count = 1 , check_flag = 0;
	 
	 if(source ==  NULL)
	 {
		printf("list is empty\n") ;
		return NULL ;
	  }
	
	coordinator *p = source ;
	
	int i = 0 , j =0;
	
	while(p!=NULL)
	{
		if(strcmp(p->userid ,str) == 0 )
		{
			
			printf("user-id is %s\n",p->userid);
			printf("name is %s\n",p->name);
			check_flag = 1;
			break;
		}
		else 
		{
			count++ ;
				
		}
		p = p->next ;
	}
	
	if(check_flag == 1)
	{
		*index = count ;
	}
	else
		*index = -1;
	
	return index ;
}


coordinator *delete_coordinator(char *str , coordinator *source)
{
	
	printf("delete_coordinator \n");
	
	int position = 0   , len = 0 , link =1;
	
	char ch ;
	
	if(source ==  NULL)
	{
		printf("list is empty\n") ;
		return NULL ;
	 }
	 
	 
	coordinator *p = source ;
	coordinator *temp = source  ;
	
	position = *lookup_coordinator(p,str,&position) ; 
	len = *len_of_list_coordinator(p,&len);
	

	printf("please enter y to delete \n");
	scanf(" %c",&ch);
	
	if((ch == 'y' || ch == 'Y')&&position >0)
	{
		if(position == 1)
		{
			source = temp->next ;
			temp->next = NULL ;
		}
		else if(position < len)
		{
				 
			while(link < position-1)
			{
				temp = temp->next;
				link++ ;
					
			}
			
			coordinator* del = temp->next;
			del->next = del->next ;
			temp->next = del->next ;		
			
		}
		else if(position == len)
		{
			link = 1 ;
			
			
			while(link < position-1)
			{
				temp = temp->next; 
				link++;
			}
			
			temp->next = NULL;
			
		
		}
	}
	else 
	printf("user-id is  not deleted\n");	
	return source;
}

void delete_contestant()
{
	printf("delete_contestant \n");	
}

void view_contestant()
{
	contestant *p = co_root;
	
	while(p!=NULL)
	{
		printf("%s,%s,%s,%s,%s\n",p->user_name ,p->user_id ,p->phone_num ,p->email_id ,p->pswd );
		p=p->next;
	}
}


void adding_new_coordinator_to_file()
{
	char *coordinator_file = "coordinator_info.txt";
	coordinator source ; 
	FILE *fptr = fopen(coordinator_file , "a");
	
	if(fptr == NULL)
	{
		printf("%s file opening is failed \n",coordinator_file);
		return ;
	}
	else 
	{
		printf("enter the user name \n");
		getchar();
		fgets(source.name , 20 , stdin);
		source.name[strlen(source.name)-1] = '\0';

		printf("enter the user-id\n");
		/*getchar();
		fgets(source.userid , 20 , stdin);
		source.userid[strlen(source.userid)-1] = '\0';
		*/
		scanf("%s",source.userid);
		
		printf("enter the phone number\n");
		scanf("%ld",&source.phone_num);
		
		
		printf("enter the email-id\n");
		/*getchar();
		fgets(source.Email_id , 20 , stdin);
		source.userid[strlen(source.Email_id)] = '\0';
		*/
		
		scanf("%s",source.Email_id);
		
		printf("enter the password\n");
		getchar();
		fgets(source.pswd , 20 , stdin);
		source.pswd[strlen(source.pswd)-2] = '\0';
	
		fprintf(fptr,"%s,%s,%ld,%s,%s\n",source.name,source.userid,source.phone_num,source.Email_id,source.pswd);		
				
	}
	
	fclose(fptr);
}


coordinator data_extraction_from_cordinator_file(char *str ,  coordinator Data)
{
	int index = 0;
	
	char *piece ;
		piece = strtok(str,",");
		while(piece !=NULL)
		{
			//printf("str : %s\n",piece);
			if(index == 0)
			{
				strcpy(Data.name ,piece );
				index =1;
			}
			else if(index ==1)
			{
				strcpy(Data.userid ,piece );
				index =2;	
			}
			else if(index == 2)
			{
				//printf("str : %s and %ld\n",piece ,atoi(piece));
				Data.phone_num = atoi(piece);
				index =3;
			}
			else if(index == 3)
			{
				strcpy(Data.Email_id ,piece );
				index =4;		
			}
			else if(index == 4)
			{
				strcpy(Data.pswd ,piece );
				index = 5;	
			}
			piece = strtok(NULL,",");			
		}
return Data ;		
}

void save_coordinator_data_into_file(coordinator *source)
{
	char *coordinator_file = "coordinator_info.txt";
	FILE *fptr = fopen(coordinator_file , "w");
	int count = 0 ;
	if(fptr == NULL)
	{
		printf("%s file opening is failed \n",coordinator_file);
		return ;
	}
	else 
	{
	
		while(source!= NULL)
		{
			//printf("count %d \n",count++);
			fprintf(fptr,"%s,%s,%ld,%s,%s\n",source->name,source->userid,source->phone_num,source->Email_id,source->pswd);
			//printf("%s,%s,%ld,%s,%s\n",source->name,source->userid,source->phone_num,source->Email_id,source->pswd);	
			source = source->next ;
		}
	}
	
	fclose(fptr);
}
