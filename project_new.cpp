#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
struct queue
{
    char c;
    struct queue *next;
};
int *var;
void rmSpace(char[]);           /**Removes blank spaces from expression*/
int fsize(struct queue *);      /**Finds the size of expression after modification*/
int isOperator(char);           /**Checks whether a character is mathematical operator or not*/
int isDot(char[],int);          /**Checks whether a character is dot(.) or not*/
int isBrace(char);              /**Checks whether a character is bracket or not*/
int isValid(char[]);            /**Checks validity of the expression*/
int checkChar(char[]);          /**Checks presence of invalid characters in the expression*/
int checkOperator(char[]);      /**Checks whether the operators are in proper order or not*/
int checkParenthesis(char[]);   /**Checks whether the parenthesis of the expression is balanced or not*/
int checkDivByZero(char[]);     /**Checks whether there is division by zero in the expression*/
int scanExp(char[]);            /**Scans the number of variables present in the expression*/
struct queue* create(char[]);   /**Creates a queue of the characters present in expression*/
void push(char,char[],int *);   /**Pushes/inserts an element into the stack while converting infix to postfix*/
char pop(char[],int *);         /**Pops/deletes an element from the stack while converting infix to postfix*/
void push(double,double[],int *); /**Pushes/inserts an element into the stack while evaluating postfix*/
double pop(double [],int *);      /**Pops/deletes an element from the stack while evaluating postfix*/
int in_stack_priority(char);    /**Checks the priority of an element present in stack*/
int incoming_priority(char);    /**Checks the priority of current element being processed*/
double evaluate(char[],double[],int);         /**Evaluates the postfix expression*/
void infix_to_postfix(struct queue*,char[]);  /**Converts the infix expression to postfix*/
void EnQueue(struct queue**,struct queue**,char);       /**Inserts element into the queue*/
char DeQueue(struct queue**);                           /**Deletes element from the queue*/
int main()
{
    char exp[100],*postfix;
    int nov,i;
    double ans,*val;
    struct queue* front=NULL;
    printf("Enter any algebraic expression:\n\n");
    gets(exp);
    rmSpace(exp);
    if (!isValid(exp))
    {
        printf("\nInvalid expression!!");
        getch();
        return 0;
    }
    for (i=0;i<strlen(exp);i++)
        {
            exp[i]=tolower(exp[i]);
        }
    nov=scanExp(exp);
    if (nov!=0)
    {
        printf("\nEnter the values of variables ");
        for (i=0;i<nov;i++)
        {
            printf("%c ",var[i]);
        }
        printf("\n");
    }
    val=(double *)malloc(nov*sizeof(double));
    for (i=0;i<nov;i++)
    {
        scanf("%lf",&val[i]);
    }
    front=create(exp);
    postfix=(char *)malloc(fsize(front)*sizeof(char));
    infix_to_postfix(front,postfix);
    ans=evaluate(postfix,val,nov);
    printf("\nThe answer is %g",ans);
    getch();
    free(val);
    free(var);
    free(postfix);
    return 0;
}
void rmSpace(char s[])
{
    int i,l=strlen(s),j,k=0;
    for (i=0;i<l;i++)
    {
        if (s[i]==' ')
        {
            for (j=i;j<l-1;j++)
            {
               s[j]=s[j+1];
            }
        s[l-(++k)]='\0';
        i--;
        }
    }
}
int isValid(char s[])
{
    if (!checkChar(s))
        return 0;
    if (!checkOperator(s))
        return 0;
    if (!checkParenthesis(s))
        return 0;
    if (!checkDivByZero(s))
        return 0;
    return 1;
}
int checkChar(char s[])
{
    int i,l=strlen(s);
    for (i=0;i<l;i++)
    {
        if (!(isalpha(s[i])||isdigit(s[i])||isBrace(s[i])||isOperator(s[i])||isDot(s,i)))
                return 0;
    }
    return 1;
}
int isOperator(char c)
{
    if (c=='+'||c=='-'||c=='*'||c=='/'||c=='^'||c=='%')
        return 1;
    return 0;
}
int isBrace(char c)
{
    if (c=='('||c==')'||c=='{'||c=='}'||c=='['||c==']')
        return 1;
    return 0;
}
int isDot(char s[],int i)
{
    int l=strlen(s),c=0,j;
    if(s[i]=='.')
    {
      if (i==l-1)
        return 0;
        if ((isdigit(s[i-1])&&isdigit(s[i+1]))||(i==0)&&isdigit(s[i+1]))
         {
            for (j=i+2;j<l&&s[j]!='.';j++)
            {
                if (!(isdigit(s[j])))
                    c++;
            }
            if (c==0&&j!=l)
                return 0;
            return 1;
        }
    }
    return 0;
}
int checkOperator(char s[])
{
    int i,l=strlen(s);
    for (i=0;i<l;i++)
    {
        if(isOperator(s[i]))
        {
            if (i==l-1||i==0)
                return 0;
            if (!(isalpha(s[i-1])||isdigit(s[i-1])||s[i-1]==')'||s[i-1]=='}'||s[i-1]==']'))
                return 0;
            if (!(isalpha(s[i+1])||isdigit(s[i+1])||s[i+1]=='('||s[i+1]=='{'||s[i+1]=='['))
                return 0;
        }
    }
}
int checkParenthesis(char s[])
{
    char *c,ch;
    int count=0,l,i,pos=0;
    l=strlen(s);
    for (i=0;i<l;i++)
    {
        if (s[i]=='('||s[i]=='{'||s[i]=='[')
            count++;
    }
    c=(char *)malloc(count*sizeof(char));
    for (i=0;i<l;i++)
    {
        if (s[i]=='('||s[i]=='{'||s[i]=='[')
            push(s[i],c,&pos);
        if (s[i]==')'||s[i]=='}'||s[i]==']')
        {
            if (pos<0)
                return 0;
            ch=pop(c,&pos);
            if (ch=='(')
            {
                if (s[i]!=')')
                    return 0;
            }
            if (ch=='{')
            {
                if (s[i]!='}')
                    return 0;
            }
            if (ch=='[')
            {
                if (s[i]!=']')
                    return 0;
            }
        }
    }
    free(c);
    if (pos!=0)
        return 0;
return 1;
}
int checkDivByZero(char s[])
{
    int i,l;
    l=strlen(s);
    for (i=0;i<l-1;i++)
    {
        if (s[i]=='/'&&s[i+1]=='0')
            return 0;
    }
    return 1;
}
int scanExp(char s[])
{
    int c=0,i,l,k=0;
    l=strlen(s);
    char *t;
    t=(char *)calloc(26,sizeof(char));
    for (i=0;i<l;i++)
    {
        if (isalpha(s[i]))
            t[(int)(s[i])-97]++;
    }
    for (i=0;i<26;i++)
    {
        if (t[i]>0)
            c++;
    }
    var=(int *)malloc(c*sizeof(int));
    for (i=0;i<26;i++)
    {
        if (t[i]>0)
            var[k++]=i+97;
    }
    free(t);
    return c;
}
struct queue* create(char s[])
{
    struct queue *front=NULL,*rear=NULL;
    int i,l,f=0,k=0;
    l=strlen(s);
    for (i=0;i<l;i++)
    {
        if (s[i]=='{'||s[i]=='[')
            s[i]='(';
        else if (s[i]=='}'||s[i]==']')
            s[i]=')';
    }
    if (isdigit(s[0]))
        EnQueue(&front,&rear, '#');
    if (s[0]=='.')
     {
        EnQueue(&front,&rear, '#');
        EnQueue(&front,&rear, '0');
     }
    for (i=0;i<l;i++)
    {
        if(i>0)
        {
            if (isdigit(s[i])&&(!(isdigit(s[i-1])))&&s[i-1]!='.')
                EnQueue(&front,&rear, '#');
            /**if (s[i]=='.'&&(!(isdigit(s[i-1]))))
            {
                EnQueue(&front,&rear, '#');
                EnQueue(&front,&rear, '0');
            }*/
        }
         if (i==l-1)
            break;
        if ((isalpha(s[i])&&isdigit(s[i+1]))||(isdigit(s[i])&&isalpha(s[i+1])))
        {
            EnQueue(&front,&rear, s[i]);
            k=1;
        }
        else if ((isalpha(s[i])&&s[i+1]=='(')||(isdigit(s[i])&&s[i+1]=='('))
        {
            EnQueue(&front,&rear, s[i]);
            k=1;
        }
        else if ((isalpha(s[i+1])&&s[i]==')')||(isdigit(s[i+1])&&s[i]==')'))
        {
            EnQueue(&front,&rear, s[i]);
            k=1;
        }
        else if (isalpha(s[i])&&isalpha(s[i+1]))
        {
            EnQueue(&front,&rear, s[i]);
            k=1;
        }
        else
            EnQueue(&front,&rear,s[i]);
        if (isdigit(s[i])&&(!(isdigit(s[i+1])))&&s[i+1]!='.')
            EnQueue(&front,&rear, '#');
         if (k)
            EnQueue(&front,&rear,'*');
         k=0;
    }
    EnQueue(&front,&rear,s[i]);
    if (isdigit(s[i]))
        EnQueue(&front,&rear, '#');
    return front;
}
void EnQueue(struct queue **front,struct queue **rear,char s)
{
    struct queue* temp=(struct queue*)malloc(sizeof(struct queue));
    temp->c=s;
    temp->next=NULL;
    if (*front==NULL)
    {
        *front=temp;
        *rear=temp;
        return;
    }
    (*rear)->next=temp;
    *rear=temp;
}
char DeQueue(struct queue **front)
{
    struct queue* temp=*front;
    (*front)=(*front)->next;
    char c=temp->c;
    free(temp);
    return c;
}
int fsize(struct queue* front)
{
    struct queue* temp=front;
    int c=0;
    while(temp!=NULL)
    {
        temp=temp->next;
        c++;
    }
    return c;
}
void infix_to_postfix(struct queue* front,char pf[])
{
    int i,TOP=0,m=0;
    char n,k,*stack;
    stack=(char *)malloc(fsize(front)*sizeof(char));
    while (front!=NULL)
    {
        k=DeQueue(&front);
        switch(k)
        {
        case '(':
            push(k,stack,&TOP);
            break;
        case ')':
            while((n=pop(stack,&TOP))!='(')
                    pf[m++]=n;
            break;
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        case '^':
            while(TOP>=-1&&in_stack_priority(stack[TOP])>=incoming_priority(k))
                pf[m++]=pop(stack,&TOP);
            push(k,stack,&TOP);
            break;
        default:
            pf[m++]=k;
        }
    }
    while(TOP!=-1)
        pf[m++]=pop(stack,&TOP);
    pf[m-1]='\0';
    free(stack);
}
void push(char c,char stack[],int *TOP)
{
    stack[++(*TOP)]=c;
}
char pop(char stack[],int *TOP)
{
    return stack[(*TOP)--];
}
int in_stack_priority(char c)
{
    switch(c)
    {
    case '(':
        return 0;
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
    case '%':
        return 2;
    case '^':
        return 3;
    default:
        return 0;
    }
}
int incoming_priority(char c)
{
    switch(c)
    {
    case '(':
        return 0;
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
    case '%':
        return 2;
    case '^':
        return 4;
    default:
        return 0;
    }
}
double evaluate(char s[],double val[],int nov)
{
    double ans,a,b,temp,*stack,m=0;
    int i,l,TOP=-1,flag=0,j=0,f;
    l=strlen(s);
    stack=(double *)malloc(l*sizeof(double));
    for(i=0;i<l;i++)
    {
        if (!(isOperator(s[i])))
        {
            if (isalpha(s[i]))
            {
               for (f=0;f<nov;f++)
                {
                    if (var[f]==(int)s[i])
                        break;
                }
             push(val[f],stack,&TOP);
            }
            else if (s[i]=='#')
            {
               while(s[++i]!='#')
               {
                   if (s[i]=='.')
                   {
                       flag=1;
                       continue;
                   }
                   if (!flag)
                    m=m*10+(int)(s[i]-'0');
                   else
                    m=m+((int)(s[i]-'0'))/pow(10,++j);
               }
               push(m,stack,&TOP);
               flag=0;
               j=0;
               m=0;
            }
        }
        else
        {
            a=pop(stack,&TOP);
            b=pop(stack,&TOP);
            switch(s[i])
            {
            case '+':
                temp=b+a;
                break;
            case '-':
                temp=b-a;
                break;
            case '*':
                temp=b*a;
                break;
            case '/':
                if (a==0)
                {
                    printf("\nCannot divide by zero!!!");
                    getch();
                    exit(0);
                }
                temp=b/a;
                break;
            case '%':
                temp=(int)b%(int)a;
                break;
            case '^':
                temp=pow(b,a);
                break;
            }
            push(temp,stack,&TOP);
        }
    }
    ans=pop(stack,&TOP);
    free(stack);
    return ans;
}
void push(double c,double stack[],int *TOP)
{
    stack[++(*TOP)]=c;
}
double pop(double stack[],int *TOP)
{
    return stack[(*TOP)--];
}
