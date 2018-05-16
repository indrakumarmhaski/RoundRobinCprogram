#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<dos.h>

struct process
{
     struct process *prev;
     struct process *next;
     int inst;
     int id;
};

struct process *START=NULL;

int num_of_process = 0;

struct process* CreateProcess()
{
    struct process *n;
    n=(struct process *)malloc(sizeof(struct process)*2);
    printf("\nEnter the process ID: ");
    scanf("%d",&n->id);
    printf("\nEnter the num of inst. : ");
    scanf("%d",&n->inst);
    n->prev = NULL;
    n->next = NULL;
    return(n);
}

void CreateListOfProcess(int n_process)
{
    struct process *first;
    first = CreateProcess();
    START = first;
    num_of_process++;
    struct process *temp;

    while(num_of_process <= n_process-1)
    {
       struct process *n;
       n = CreateProcess();
       temp = START;
       while(temp->next!=NULL)
       {
	 temp = temp->next;
       }
       temp->next = n;
       n->prev = temp;
       if(num_of_process == n_process-1)
	{
	   n->next = START;
	   START->prev = n;
	}
       num_of_process++;
    }
}

void testTraverse()
{
   struct process *temp;
   temp = START;
   for(int i = 1; i<= num_of_process; i++)
   {
      printf("\nProcess id: %d,Num of total instructions: %d",temp->id,temp->inst);
      temp = temp->next;
   }
}

void Exicution()
{
   printf("\n Exicuting: ");
   struct process *temp;
   temp = START;
   while(num_of_process != 0)
   {
     if(temp->inst == 0)
     {
       if(num_of_process == 1)
       {
	  num_of_process = 0;
       }
       else if(num_of_process == 2)
       {
	 temp->prev->next = temp->prev;
	 temp->prev->prev = temp->prev;
	 temp = temp->next;
	 num_of_process--;
       }
       else
       {
	 temp->prev->next = temp->next;
	 temp->next->prev = temp->prev;
	 temp = temp->next;
	 num_of_process--;
       }
     }
     else
     {
	 printf("\nProcess_ID: %d,Current Instructions, Instructions left: %d",temp->id,temp->inst,temp->inst-1);
	 sleep(1);
	 temp->inst--;
	 temp = temp->next;
     }
  }
}


void main()
{

  clrscr();

  CreateListOfProcess(4);      // 4 = Explicitly inserted num of process
  testTraverse();
  Exicution();
  getch();
}

