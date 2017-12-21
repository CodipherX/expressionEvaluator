#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

struct node
{
    int data ;
    struct node *next ;

}*top , *top1 ,*temp;

int count =0 ;

void create ();
int top_element () ;
void push (int data ) ;
void pop () ;
void empty () ;
void display () ;
void destroy () ;
void stack_count() ;

int main ()
{
    int no , ch , e ;
    printf("\n 1- push ");
    printf(" \n2- pop  ");
    printf("\n 3- top_element");
    printf("\n 4- display ");
    printf("\n 5- destroy ");
    printf("\n 6- stack_count");
    printf("\n 7- exit ");
    printf("\n 8- empty ");
    create();


    while(1)
    {
        printf("\n enter choice ");
        scan("%d",&ch );
        switch (ch )
        {
        case 1:
            printf(" \n enter data ");
            scanf("")
        }
    }
}


void main ()
{

}
