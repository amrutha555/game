#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"prototype.h"

extern coordinator *c_root ;
question_ans question_extraction_from_file(char * , question_ans);
question_ans *QA_root[2] ;

void Disply(question_ans *root)
{

	question_ans *q = root ;
	while(q!=NULL)
	{
		printf("Q_n %d::",q->q_num);
		printf("%s\n",q->question);
		
		
		if(q->check_flag == 1)
		{
			for(int i = 0 ; i < 4 ; i++)
				printf("%c) %s\n",65+i,q->ans_string[i]);
				
		}
		else if(q->check_flag == 2)
		{
			for(int i = 0 ; i < 4 ; i++)
				printf("%c) %d\n",65+i,q->ans_intiger[i]);
		}
		
		
		if(q->ans_int == 1)
			printf("ans:%c\n",'A');
		else if(q->ans_int == 2)
			printf("ans:%c\n",'B');
		else if(q->ans_int == 3)
			printf("ans:%c\n",'c');
		else if(q->ans_int == 4)
			printf("ans:%c\n",'D');
			
		q=q->next;
	}
}
void Coordinator()
{

	int ch , exit_flag = 0;
	char user_id[BUFFER_SIZE];
	char question_str[QUESTION_BUFFER_SIZE];
	
	char *quize_file = "updated_QA_file.txt";
	char *quize_file_2 = "updated_QA_file_second.txt";
	
	design();
	printf("Wellcome to Coordinator \n");
	design();
	
	while(1)
	{
		printf("1) Update his/her details\n");
		printf("2) Add New Quiz\n");
		printf("3) Update Quiz\n");
		printf("4) Delete Quiz\n");
		printf("5) Display question\n");
		printf("6) Exit\n");
		design();
		scanf("%d",&ch);
		
		switch(ch)
		{
			case 1:
				printf("enter user-id \n");
				scanf("%s",user_id);
				if(update_coordinator(user_id , c_root) == NULL)
				{
					printf("user-id is not found please enter correct user id %s\n",user_id);
				}
				else 
					printf("updated succesfully\n");
				break;
			case 2: 
				QA_root[0] = add_new_quiz(QA_root[0],quize_file);
				QA_root[1] = add_new_quiz(QA_root[1],quize_file_2);
				break ;
			case 3: 
				printf("enter 1 for first round\n");
				printf("enter 2 for second round\n");
				scanf("%d",&ch);
				if(ch == 1)
				{
					printf("enter the question \n");
					getchar();
					scanf("%[^\n]",question_str);
					QA_root[0] = update_quiz(QA_root[0] , question_str);
					save_QA_info_into_file(QA_root[0]);
				}
				else if(ch == 2)
				{
					printf("enter the question \n");
					getchar();
					scanf("%[^\n]",question_str);
					QA_root[1] = update_quiz(QA_root[1] , question_str);
					save_QA_info_into_file(QA_root[1]);
					
				}	
				break ;
			case 5:
				printf("enter 1 for first round\n");
				printf("enter 2 for second round\n");
				scanf("%d",&ch);
				if(ch == 1)
				{
					Disply(QA_root[0]);
				}
				else
					Disply(QA_root[1]);
				break;
			case 6:
				exit_flag = 1;
				break;
		}
		
		if(exit_flag == 1)
			break;
	}
}


question_ans *add_new_quiz(question_ans *QA_root , char *quize_file)
{
	
	question_ans q_data ;
	char buffer[100] ;
	FILE *fptr = NULL ;
	int counter = 0 , index  = 0;
	
	fptr = fopen(quize_file,"r");
	if(fptr == NULL)
	{
		printf("%s file is not found plsease check the file\n",quize_file);
		return NULL;
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
					q_data = question_extraction_from_file(buffer , q_data);
					QA_root = create_list_for_QA(QA_root , q_data);
				

				
			}
		}
	}
		
return QA_root ;
}

question_ans  question_extraction_from_file(char *str , question_ans q_a_data)
{
	int i = 0  , str_num = 0;
	
	char temp[2];
	char *piece = NULL;
	int ans_index = 0  , index =0 , c_flag = 0;
	
	//printf("str : %s\n",str);
	
	while( *str != '\0' && *str != '\n')
	{
		while(*str != ',')
		{
			temp[i++] = *str++;
		}
		
		q_a_data.q_num = atoi(temp);
		
		piece = strtok(str,",");
		while(piece !=NULL)
		{
			
			if(ans_index == 0)
			{
				//printf("TEST %s\n",piece);
				strcpy(q_a_data.question , piece);
				//printf("TEST %s\n",q_a_data.question);
				ans_index = 1;
			}
			else if(ans_index == 1)
			{
				str_num = atoi(piece) ;
				if(str_num > 0)
				{
				
					if(c_flag == 1)
						q_a_data.check_flag = 1;
					else
						q_a_data.check_flag = 2;
						
						
					if(index == 4)
					{
						q_a_data.ans_int = str_num;
						//printf("ans is :%d\n",q_a_data.ans_int);
						index = 0;
					}
					else if(index <= 3)
					{
						q_a_data.ans_intiger[index++] = str_num  ;
						//printf("int value: %d and index value %d\n",q_a_data.ans_intiger[index++],index-1);
					}
					
				}
				else if(str_num == 0)
				{
					q_a_data.check_flag = 1;
					c_flag = 1;
					strcpy(q_a_data.ans_string[index++] , piece);
					//printf("str ans is : %s\n",q_a_data.ans_string[index++]);
				}
			}
			piece = strtok(NULL,",");
		}
				
		break;
	}		
		
	return q_a_data ;
	
}


question_ans *create_list_for_QA(question_ans *source ,question_ans QA_DATA )
{
	/*printf("Q_n : %d\n",QA_DATA.q_num);
	printf("question : %s\n",QA_DATA.question);
	
	
	if(QA_DATA.check_flag == 1)
	{
		for(int i = 0 ; i < 4 ; i++)
		printf("ans: %s\n",QA_DATA.ans_string[i]);
	}
	else if(QA_DATA.check_flag == 2)
	{
		for(int i = 0 ; i < 4 ; i++)
		printf("ans_int: %d\n",QA_DATA.ans_intiger[i]);
	}
		
	
	printf("ans_str %s\n",QA_DATA.ans_str);
	
	printf("ans_int : %d\n",QA_DATA.ans_int);
	*/
	
	if(source == NULL)
	{
		source  = (question_ans *)malloc(sizeof(question_ans));
		source->q_num = QA_DATA.q_num;
		strcpy(source->question ,QA_DATA.question);
		
		if(QA_DATA.check_flag == 1)
		{
			source->check_flag = 1;
			for(int i = 0 ; i < 4 ; i++)
			{
			
				strcpy(source->ans_string[i] , QA_DATA.ans_string[i]);
				
			}
			
			strcpy(source->ans_str ,QA_DATA.ans_str) ;
		}
		else if(QA_DATA.check_flag == 2)
		{
			source->check_flag = 2;
			for(int i = 0 ; i < 4 ; i++)
			{
				//printf("ans_int: %d\n",QA_DATA.ans_intiger[i]);
				source->ans_intiger[i] = QA_DATA.ans_intiger[i] ;	
				
			}
			
			
		}
	
		source->ans_int = QA_DATA.ans_int ;
		
		source->next = NULL;
	}
	else 
	{
		question_ans *p = source ;	
		question_ans *temp = (question_ans *) malloc(sizeof(question_ans));
		
		 while(p->next != NULL)
		 {
		 	p = p->next ;
				 	
		 }
		 
		temp->q_num = QA_DATA.q_num;
		strcpy(temp->question , QA_DATA.question);
		
		if(QA_DATA.check_flag == 1)
		{
			for(int i = 0 ; i < 4 ; i++)
			{
			//printf("ans: %s\n",QA_DATA.ans_string[i]);
				temp->check_flag = 1;
				strcpy(temp->ans_string[i] , QA_DATA.ans_string[i]);
			}
			
			strcpy(temp->ans_str ,QA_DATA.ans_str) ;
		}
		else if(QA_DATA.check_flag == 2)
		{
			for(int i = 0 ; i < 4 ; i++)
			{
				//printf("ans_int: %d\n",QA_DATA.ans_intiger[i]);
				temp->check_flag = 2;
				temp->ans_intiger[i] = QA_DATA.ans_intiger[i] ;	
				
			}
			
			
		}
		temp->ans_int = QA_DATA.ans_int ;
		p->next = temp ;
		temp->next = NULL ;
		 
	}

	return source;	
}
int str_check(char *str , char *str2)
{
	for(int i = 0 ; i < strlen(str)-10 ; i++)
	{
		if(str[i] == str2[i])
			continue ;
		else
		{
			return 0;
		}
	}
	
	return 1;
}

question_ans *update_quiz(question_ans *QA_root ,char* question_str)
{
	
	if(QA_root == NULL)
	{
		printf("QA list is empty\n");
		return NULL ;	
	}
	question_ans *p = QA_root ;
	char ch ;
	
	int flag = 0 ;

	while(p!=NULL)
	{
	
		
		if(str_check(question_str ,p->question))
		{
			printf("%s\n",p->question);
			if(p->check_flag == 1)
			{
				for(int i = 0 ; i < 4 ; i++)
				{
					printf("%d) %s\n",i, p->ans_string[i]);
				
				}
				
			}
			else if(p->check_flag == 2)
			{
				for(int i = 0 ; i < 4 ; i++)
				{
					printf("%d) %d\n",i,p->ans_intiger[i]);
				}	
			}
			
			printf("enter y to update the question\n");
			scanf(" %c",&ch);
			if(ch == 'y' || ch == 'Y')
			{
				printf("enter question \n");
				getchar();
				scanf("%[^\n]",p->question);
				
				printf("enter 1) for string options \n");
				printf("enter 2) for intiger options\n");
				scanf("%d",&p->check_flag);
				
				if(p->check_flag == 1)
				{
					printf("enter option in string format only\n");
					for(int i = 0 ; i < 4 ; i++)
					{
						scanf("%s",p->ans_string[i]);	
					}
				}
				else if(p->check_flag == 2)
				{
					printf("enter option in intiger format only\n");
					for(int i = 0 ; i < 4 ; i++)
					{
						scanf("%d",&p->ans_intiger[i]);	
					}
				}
			}
		}
		
		
		p = p->next ;
	}
	
	return QA_root ;
}

void save_QA_info_into_file(question_ans *QA_root)
{
	
	if(QA_root == NULL)
	{
		printf("list is empty\n");
	}
	else
	{
		FILE *fptr = NULL;
		question_ans *p = QA_root ;
		char *qa_csv_file = "updated_QA_file.csv";
		fptr = fopen(qa_csv_file,"w");
		if(fptr == NULL)
		{
			printf("file open is failed\n");
		}
		else
		{
			while(p!=NULL)
			{
				
				if(p->check_flag == 1)
				{
					p->question[strlen(p->question)-2] = '\0';
					fprintf(fptr,"%d,%s,",p->q_num,p->question);
					for(int i = 0 ; i < 4 ; i++)
					{
						
						p->ans_string[i][strlen(p->ans_string[i])-2] = '\0' ;
						fprintf(fptr,"%s,",p->ans_string[i]);
					}
					fprintf(fptr,"%s",p->ans_str);
				}
				else if(p->check_flag == 2)
				{
					fprintf(fptr,"%d,%s,",p->q_num,p->question);
					for(int i = 0 ; i < 4 ; i++)
					{
						fprintf(fptr,"%d,",p->ans_intiger[i]);
					}
					fprintf(fptr,"%d\n",p->ans_int);
					
				}
				p = p->next ;
			}
		}
		fclose(fptr);
	}
}
