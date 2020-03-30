
#include<stdio.h>

#include<unistd.h>

#include<pthread.h>

#include<stdlib.h>

#include<stdio.h>


pthread_mutex_t lockt=PTHREAD_MUTEX_INITIALIZER;
int st0[3];
int st1[3];
int st2[3];

void exit1()

{
	printf("\n\n\n\t Thank you.  \n");
	sleep(2);
	exit(0);
}	

int set(int m,int n)											//Function which prevents students from having same resources
{
	int r=1;
	if(n==0)
	{
		if(st1[m]==1 || st2[m]==1)
		{
			printf("\nTwo students can't have same resource'.");
			exit1();
		}
	}
	if(n==1)
	{
		if(st0[m]==1 || st2[m]==1)
		{
			printf("\nTwo students can't have same resource.");
			exit1();
		}
	}
	if(n==2)
	{
		if(st0[m]==1 || st1[m]==1)
		{
			printf("\nTwo students can't have same resource.");
			exit1();
		}
	}
	return r;
}

void *student0()//Function that takes input for student 1

{
	printf("\nPress 1 for pen, 2 for paper and 3 for question paper\n");
	printf("Enter the item present with 1st student: ");
	int a;
	pthread_mutex_lock(&lockt);	
	scanf("%d",&a);
	if(a==1)
	{
		st0[0]=set(0,0);
	}
	else
		{ if(a==2)
			{
				st0[1]=set(1,0);
			}
		else
			{ if(a==3)
				{
					st0[2]=set(2,0);
				}

			else
				{
			printf(" A student cannot take this.\n");
		}}
	}
	pthread_mutex_unlock(&lockt);
}
void *student1()												//Function that takes input for student 2

{

	printf("\nPress 1 for pen, 2 for paper and 3 for question paper\n");
	printf("Enter the item present with 2nd student: ");
	int a;
	pthread_mutex_lock(&lockt);	
	scanf("%d",&a);
	if(a==1)
	{
		st1[0]=set(0,1);
	}
	else{ if(a==2)
	{
		st1[1]=set(1,1);
	}
	else{ if(a==3)
	{
		st1[2]=set(2,1);
	}
	else
	{
		printf(" A student cannot take this.\n");
	}}}
	pthread_mutex_unlock(&lockt);
}

void *student2()													//Function that takes input for student 3

{
	printf("\nPress 1 for pen, 2 for paper and 3 for question paper\n");
	printf("Enter the item present with 3rd student: ");
	int a;
	pthread_mutex_lock(&lockt);	
	scanf("%d",&a);
	if(a==1)
	{
		st2[0]=set(0,2);
	}
	else{ if(a==2)
		{
			st2[1]=set(1,2);
		}
		else{ if(a==3)
			{
				st2[2]=set(2,2);
			}
		    else
			{
			printf("A student cannot take this.\n");
			}
		  }
	}
	pthread_mutex_unlock(&lockt);
}

int checking(int a,int b)											//Function that assigns items to the student
{   
	int c=0;
	if (a==1 && b==2 || a==2 && b==1)
		{ 										
			c=3;
		}
	else{ if (a==1 && b==3 || a==3 && b==1)
		{
			c=2;
		}
		else{ if (a==2 && b==3 || a==3 && b==2)
			{
				c=1;
			}
			else
			{
				printf("\nPlease check your input; Either your input is wrong or you entered twice\n");
				exit1();
			}
		   }
	}
	return c;
}

void checking1(int c)												//Function that completes a student process accordingly

{

if(st0[c-1]==1)
		{		
		 	printf("1st Student got the last item, he finishes the task and tell the teacher\n\n");
			sleep(1.5);
		}
		else{ if(st1[c-1]==1)
		{
			printf("2nd Student got the last item, he finishes the task and tell the teacher\n");
			sleep(1.5);
		}
		else{ if(st2[c-1]==1)
		{
			printf("3rd Student got the last item, he finishes the task and tell the teacher\n");
			sleep(1.5);
		}
		else { printf("\nStudent having the coreesponding last item has either completed his task\n");}}}return;
}

void *table()												//Function that assign the everything

{

	int r,a,b,c,d,e,f;
		pthread_mutex_lock(&lockt);		
		a=1,b=2;
		printf("\nTeacher put pen and paper on the table\n");
		sleep(2);
		c=checking(a,b);
		checking1(c);
		pthread_mutex_unlock(&lockt);
		pthread_mutex_lock(&lockt);		
		a=2,b=3;
		printf("\nTeacher put question paper and paper on the table\n");
		sleep(2);
		c=checking(a,b);
		checking1(c);
		pthread_mutex_unlock(&lockt);
		pthread_mutex_lock(&lockt);		
		a=1,b=3;
		printf("\nTeacher put pen and question paper on the table\n");
		sleep(2);
		c=checking(a,b);
		checking1(c);
		pthread_mutex_unlock(&lockt);
}

void main()															//MAIN
{
	int a;pthread_t Std0;
	pthread_t Std1;
	pthread_t Std2;
	pthread_t Tea1;
	printf("$$$$$$$$$$$$$$$$$$$  OS SIMULATION $$$$$$$$$$$$$$$$$$$$$$$\n");
	system("clear");	
printf("We have TWO scenes.\nSCENE 1:At Exam Hall \nSCENE 2:At Library\nSCENE 3:There is an optimised solution implemented for the SCENE 2 which is  ideal..... \n  Please proceed accordingly by choosing one :-   ");
	scanf("%d",&a);
switch(a)
{
	case 1:
		printf("\nScene Illustration: \nThere are 3 studentprocesses and 1 teaher process. Students are supposed to do their assignments and they need 3 things for that- pen,paper and question paper. The teacher has an infinite supply of all the three things. One student has pen, another has paper and another has question paper. The teacher places two things on a shared table and the student having the third complementary thing makes the assignment and tells the teacher on completion. The teacher then places two things out of three and again the student having the third thing makes the assignment and tells the teacher on completion. This cycle continues.\n\n");
		pthread_create(&Std0,NULL,student0,NULL);
		pthread_join(Std0,NULL);
		pthread_create(&Std1,NULL,student1,NULL);
		pthread_join(Std1,NULL);	
		pthread_create(&Std2,NULL,student2,NULL);
		pthread_join(Std2,NULL);
		pthread_create(&Tea1,NULL,table,NULL);
		pthread_join(Tea1,NULL);
		printf("\n\nScene 1 at Exam Hall is complete\n");
		int a;
		printf("\nPress 0 for any other scenario else any :  ");
		scanf("%d",&a);
		if (a==0)
		{
			main();
		}
		else {exit1();}
		break;
	case 2:
		{printf("\nScene Illustration: \nTwo people can enter library pupil and Teacher then they go and search for the book to get it issued. To get them issued they go to computer where there are two lines one for teacher and one for students. If a student is present and a teacher arrives , he would be the next person to get service (PRIORITY - non preemtive). If two teachers arrive at the same time, they will stand in their queue to get service first come and served.\n\n");
		int p[30],pr[30],bt[30],temporary,maxi,wt[30],ta[30],sum=0,r,j,n;
		int c=0,d=0;
		wt[0]=0;
		printf("Enter the number of persons=");
		scanf("%d",&n);
		printf("Enter the value 0 for teacher and 1 for student\n");
		for(r=0;r<n;r++)
		{													//set
			p[r]=r+1;
			bt[r]=1;
			printf("Who arrived %d? =",r+1);
			scanf("%d",&pr[r]);
		}
		for(r=0;r<n;r++)
		{													//Priority Queue sorting done here
		   	maxi=r;
			for(j=r+1;j<n;j++)
			{
				if(pr[j] <pr[maxi])
				maxi=j;
			}
			temporary=pr[maxi];
			pr[maxi]=pr[r];
			pr[r]=temporary;
			temporary=bt[maxi];
			bt[maxi]=bt[r];
			bt[r]=temporary;
			temporary=p[maxi];
			p[maxi]=p[r];
			p[r]=temporary;
		}
		for(r=0;r<n;r++)
		{     										
			wt[r+1]=bt[r]+wt[r];
			ta[r]=bt[r]+wt[r];
			sum+=ta[r];
		}
		for(r=0;r<n;r++)
		{												
			printf("\nWaiting time for %d person is =%d",p[r],wt[r]);
		}
	
		printf("\n\nScene 2 is complete\n");
		int a;
		printf("\nPress 0 for other scenario else any :  ");
		scanf("%d",&a);
		if (a==0)
		{
			main();
		}
		else {exit1();}
		break;
		}
	case 3:
		{printf("\nScene Illustration:\nIf two teachers are standing in line and other teachers come then he would be the one to get serviced. This is might led to students to get more and more waiting which our program times us.\n\n");
		int p[30],pr[30],bt[30],temporary,maxi,wt[30],ta[30],sum=0,r,j,n;
		int c=0,d=0;
		wt[0]=0;
		printf("Enter the no. of persons=");
		scanf("%d",&n);
		printf("Enter 0 for teacher and 1 for student\n");
		for(r=0;r<n;r++)
		{
			p[r]=r+1;
			bt[r]=1;
			printf("\t Which one arrives %d? =",r+1);
			scanf("%d",&pr[r]);
			if(pr[r]==0)
			{												//set with ageing conditions
				c=c+1;
	
			}
			if(pr[r]==0 && d==1)
			{
				
				pr[r]=pr[r]+1;
				d=0;
			}
			if(c==3)
			{
				c=0;
				d=1;
				continue;
			}
		}
		for(r=0;r<n;r++)
		{													//Priority Queue sorting
	   		maxi=r;
			for(j=r+1;j<n;j++)
			{
				if(pr[j] <pr[maxi])
				maxi=j;
			}
			temporary=pr[maxi];
			pr[maxi]=pr[r];
			pr[r]=temporary;
			temporary=bt[maxi];
			bt[maxi]=bt[r];
			bt[r]=temporary;
			temporary=p[maxi];
			p[maxi]=p[r];
			p[r]=temporary;
		}
		for(r=0;r<n;r++)
		{     															
			wt[r+1]=bt[r]+wt[r];
			ta[r]=bt[r]+wt[r];
			sum+=ta[r];
		}
		for(r=0;r<n;r++)
		{															//Output
			printf("\nWaiting time for person %d is =%d",p[r],wt[r]);
			//printf("\t turn around time for p[%d]=%d",p[r],ta[r]);
		}
		//printf("\n\naverage turn around=%d",sum/n);
		printf("\n\nScene 3 is complete\n");		
		int a;
		printf("\nPress 0 for other scenario else any:  ");
		scanf("%d",&a);
		if (a==0)
		{
			main();
		}
		else {exit1();}
		break;
	}
default:

	printf("Do not match");exit1();
}
}
