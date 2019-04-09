#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


int rac_passenger_numbers=0;
typedef enum {FAILURE,SUCCESS} StatusCode;

typedef struct Coach_tag
{
    int coach_number;
    int lower[10];
    int middle[10];
    int upper[10];
    int sidelower[3];
    int rac_sidelower[2];
    int sideupper[5];
    struct Coach_tag *left;
    struct Coach_tag *right;
}Coach_type;

typedef struct Passenger_tag
{
    int coach_num;
    int passengerID;
    char name[50];
    char address[50];
    int phoneNo;
    int age;
    char berth_preferrence[50];
    int trainID;
    int seatnum;
    char trainclass[50];
    struct Passenger_tag *left;
    struct Passenger_tag *right;
}Passenger;

typedef struct Train_tag
{
    int trainID;
    struct Train_tag *next;
    Coach_type *Coach;
}Train_type;

int main()
{
    int flag1=1,fun_num,i,flag2=1;
    int train_id;
    Train_type *train_ptr;
    Coach_type *coach_ptr=NULL,*present_coach_ptr=NULL;
    int numberofpeople;
    int passengerID;
    char name[50][50];
    char address[50];
    int phoneNo;
    int age[50];
    char berth_preferrence[50][50];
    int trainID;
    char trainclass[50];
    Passenger *passptr=NULL;
    train_ptr=InitializeTrains();
    int coach_to_be_printed=0;
    int cancel_coach_num;
    int cancel_passenger_id;

    while(flag1!=0)
    {
         printf("\n1.addCoach\n2.BookTicket\n3.CancelTicket\n4.FreezeBooking\n5.DisplayCoachData\n6.PrintCoachData\n7.PrintPassengerData\n8.PrintRAC\n9.PrintWaiting\n");
         printf("\nEnter the function number:-\n");
         scanf("%d",&fun_num);

         switch(fun_num)
         {
             case 0:flag1=0;
                    break;
             case 1:if(flag2==1)
                    {
                        printf("\nSelect the train:-\n1.Gitanjali Express\n2.Rajdhani Express\n3.Duranto Express\n");
                        scanf("%d",&train_id);
                        coach_ptr=addCoach(train_ptr,train_id,coach_ptr);
                        present_coach_ptr=coach_ptr;
                    }
                    else
                    {
                        printf("\nBooking is freezzed");
                    }
                    break;
             case 2:if(flag2==1)
                    {
                        printf("\nEnter Passenger ID:- ");
                        scanf("%d",&passengerID);
                        printf("\nEnter number of people:- ");
                        scanf("%d",&numberofpeople);
                        printf("\nEnter Names:- ");
                        for(i=0;i<numberofpeople;i++)
                        {
                            scanf("%s",name[i]);
                        }
                        printf("\nEnter Address:- ");
                        scanf("%s",address);
                        printf("\nEnter Phone Number:- ");
                        scanf("%d",&phoneNo);
                        printf("\nEnter Ages:- ");
                        for(i=0;i<numberofpeople;i++)
                        {
                             scanf("%d",&age[i]);
                        }
                        printf("\nEnter Birth Preferences:- ");
                        for(i=0;i<numberofpeople;i++)
                        {
                             scanf("%s",berth_preferrence[i]);
                        }
                        printf("\n1.Gitanjali Express\n2.Rajdhani Express\n3.Duranto Express\n");
                        printf("\nEnter Train ID:- ");
                        scanf("%d",&trainID);
                        printf("\nEnter Train Class:- ");
                        scanf("%s",trainclass);
                        passptr=BookTicket(passengerID,name,address,phoneNo,age,berth_preferrence,trainID,trainclass,numberofpeople,coach_ptr,present_coach_ptr);
                    }
                    else
                    {
                        printf("\nBooking is freezzed");
                    }
                    break;
             case 3:if(flag2==1)
                    {
                        printf("\nEnter Coach number:- ");
                        scanf("%d",&cancel_coach_num);
                        printf("\nEnter passenger id:- ");
                        scanf("%d",&cancel_passenger_id);
                        CancelTicket(cancel_coach_num,cancel_passenger_id,coach_ptr);
                    }
                     else
                    {
                        printf("\nBooking is freezzed");
                    }
                    break;
             case 4:FreezeBooking(coach_ptr);
                    flag2=0;
                    break;
             case 5:printf("\nEnter Coach Number whose data is to be printed :-");
                    scanf("%d",&coach_to_be_printed);
                    DisplayCoach(coach_ptr,passptr,coach_to_be_printed);
                    break;
             case 6:PrintCoach(coach_ptr);
                    break;
             case 7:printf("\nEnter Coach Number whose data is to be printed :-");
                    scanf("%d",&coach_to_be_printed);
                    PrintPassenger(passptr,coach_to_be_printed);
                    break;
             case 8:PrintRAC();
                    break;
             case 9:PrintWaiting();
                    break;
         }
    }
}

Coach_type *addCoach(Train_type *tptr,int train_id,Coach_type *cptr)
{

    /*int i,num,count=0,flag1=1;
    Train_type *ttptr=tptr;
    Coach_type *nptr=cptr,*ptr=cptr,*initializeptr=NULL,*previousnode=NULL;

    while(ttptr!=NULL)
    {
        if(ttptr->trainID==train_id)
        {
            if(cptr==NULL)
            {
                printf("Enter the number of coaches you want to create :- ");
                scanf("%d",&num);

                for(i=0;i<num;i++)
                {
                    nptr=(Coach_type *)malloc(sizeof(Coach_type));
                    nptr->coach_number=num-1-i;
                    nptr->next=cptr;
                    cptr=nptr;
                    if(previousnode!=NULL)
                    {
                        previousnode->prev=nptr;
                    }

                    previousnode=nptr;
                }
                previousnode->prev=NULL;
                Initialize_Lower_Seats(cptr);
                Initialize_Middle_Seats(cptr);
                Initialize_Upper_Seats(cptr);
                Initialize_SideUpper_Seats(cptr);
                Initialize_SideLower_Seats(cptr);
                Initialize_SideLowerRAC_Seats(cptr);

                return cptr;
            }
            else
            {
                printf("Enter the number of coaches you want to add:- ");
                scanf("%d",&num);

                while(nptr->next!=NULL)
                {
                    nptr=nptr->next;
                    count++;
                }

                for(i=0;i<num;i++)
                {
                    ptr=(Coach_type *)malloc(sizeof(Coach_type));
                    ptr->coach_number=count+i+1;
                    nptr->next=ptr;
                    ptr->prev=nptr;
                    nptr=ptr;

                    if(flag1==1)
                    {
                        initializeptr=nptr;
                        flag1=0;
                    }
                }
                nptr->next=NULL;
                Initialize_Lower_Seats(initializeptr);
                Initialize_Middle_Seats(initializeptr);
                Initialize_Upper_Seats(initializeptr);
                Initialize_SideUpper_Seats(initializeptr);
                Initialize_SideLower_Seats(initializeptr);
                Initialize_SideLowerRAC_Seats(initializeptr);
                return cptr;
            }
        }
        else
        {
            ttptr=ttptr->next;
        }
    }
    return cptr;*/
}

void Initialize_Lower_Seats(Coach_type *cptr)
{
    int i;
    Coach_type *nptr=cptr;

    while(nptr!=NULL)
    {
        for(i=0;i<10;i++)
        {
            nptr->lower[i]=0;
        }
        nptr=nptr->next;
    }
}

void Initialize_Middle_Seats(Coach_type *cptr)
{
    int i;
    Coach_type *nptr=cptr;

    while(nptr!=NULL)
    {
        for(i=0;i<10;i++)
        {
            nptr->middle[i]=0;
        }
        nptr=nptr->next;
    }
}

void Initialize_Upper_Seats(Coach_type *cptr)
{
    int i;
    Coach_type *nptr=cptr;

    while(nptr!=NULL)
    {
        for(i=0;i<10;i++)
        {
            nptr->upper[i]=0;
        }
        nptr=nptr->next;
    }
}

void Initialize_SideUpper_Seats(Coach_type *cptr)
{
    int i;
    Coach_type *nptr=cptr;

    while(nptr!=NULL)
    {
        for(i=0;i<5;i++)
        {
            nptr->sideupper[i]=0;
        }
        nptr=nptr->next;
    }

}

void Initialize_SideLower_Seats(Coach_type *cptr)
{
    int i;
    Coach_type *nptr=cptr;

    while(nptr!=NULL)
    {
        for(i=0;i<3;i++)
        {
            nptr->sidelower[i]=0;
        }
        nptr=nptr->next;
    }
}

void Initialize_SideLowerRAC_Seats(Coach_type *cptr)
{
    int i;
    Coach_type *nptr=cptr;

    while(nptr!=NULL)
    {
        for(i=0;i<2;i++)
        {
            nptr->rac_sidelower[i]=0;
        }
        nptr=nptr->next;
    }
}

Train_type *InitializeTrains()
{
    Train_type *tptr,*nptr;
    int i;
    tptr=NULL;
    for(i=3;i>0;i--)
    {
        nptr=(Train_type *)malloc(sizeof(Train_type));
        nptr->trainID=i;
        nptr->next=tptr;
        tptr=nptr;
    }
    return tptr;
}
