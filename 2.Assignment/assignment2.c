#include <stdio.h>
#include <stdlib.h>
#include<string.h>


// A structure to represent a queue
typedef struct
{
    int front, rear;
    int MAXSIZE;
    char* kuyruk_arr;
} queue;

// function to create a queue of given size. Used to circular queue
queue* createQueue(int size)
{
    queue* queue1=(queue*) malloc(sizeof(queue));
    queue1->MAXSIZE= size;
    queue1->front = -1;
    queue1->rear = - 1; // This is important, see the enqueue
    queue1->kuyruk_arr = (char*) malloc(queue1->MAXSIZE * sizeof(char));  //this queue keeping char items.
    return queue1;
}
// function to checks whether the queue is empty
int isEmpty(queue* q)
{
    return (q->front == -1 && q->rear == -1) ? 1: 0;
}

// function to checks whether the queue is full
int isFull(queue* q)
{
    return (q->rear+1)%q->MAXSIZE == q->front ? 1 : 0;
}

// Function to add an item to the queue. It changes rear
void enqueue(queue* q, char item)
{
    if(isEmpty(q))
        q->front = q->rear = 0;
    else
        q->rear = (q->rear+1)%q->MAXSIZE;

    q->kuyruk_arr[q->rear] = item;
}

// Function to remove an item from queue. It changes front and size
//function returns the deleted value
char dequeue(queue* q)
{
    if(isEmpty(q))
    {
        return ' ';
    }
    else if(q->front == q->rear)
    {
        int x =q->front;
        q->front =q->rear = -1;
        return q->kuyruk_arr[x];
    }
    else
    {
        int x1=q->front;
        q->front = (q->front+1)%q->MAXSIZE;
        return q->kuyruk_arr[x1];
    }
}

///////////////// A structure to represent a stack
typedef struct
{
    char* stack_arr;
    int MAXSIZE;
    int top;

} stack;

// function to create a stack of given size.
stack* createStack(int stack_size)
{
    stack* stack1 = (stack*) malloc(sizeof(stack));
    stack1->MAXSIZE = stack_size;
    stack1->top = -1;
    stack1->stack_arr = (char*) calloc(stack1->MAXSIZE, sizeof(char)); //which it was initially created an array of zero. about calloc
    return stack1;
}
// Stack is full when top is equal to the last index
int stack_full(stack* stk)
{
    return (stk->top >= stk->MAXSIZE-1 )? 1 : 0;
}
// Stack is empty when top is equal to -1
int stack_empty(stack* stk)
{
    return stk->top==-1 ? 1 : 0 ;
}
// Function to add an item to stack.  It increases top by 1
void push(stack* stk, char item2)
{
    stk->top++;
    stk->stack_arr[stk->top]=item2;
}
// Function to remove an item from stack.  It decreases top by 1
char pop(stack* stk)
{
    if(stack_empty(stk))
        return ' ';
    else
        return stk->stack_arr[stk->top--];
}

// this struct is represent in second text file's functions .
typedef struct
{
    char fonk[5];  // first character in text file  function name
    char client_num[5]; // second character in text file  item number
    char value[5]; // third character in text file adding or deleting value

} input2;

// this struct contains client's and server's queue and stack struct
typedef struct
{
    queue* kuyruk;
    stack* yigin;
} client;

// this struct keeping stack for log history
typedef struct
{
    stack* stk_o;
} output_stk;

// function to perform operations in the second text file
// this function's argument arr_input2 is keeping second text functions, ilk_satir is second text file's row size, satir is first file's row size
//stk_arr is keeping stack for log history , client_arr is keeping client's and server's stacks and queues
void func(input2 *arr_input2,int ilk_satir,int satir,output_stk *stk_arr,client *client_arr){
    int r;
    for(r=0; r<ilk_satir; r++)
    {
        if(arr_input2[r].fonk[0]=='A') // add to character in client's queue
        {
            int numb=atoi(arr_input2[r].client_num)-1; // which client
            if(isFull(client_arr[numb].kuyruk))
                push(stk_arr[numb].stk_o,'1'); // error for client's queue is full
            else
                enqueue(client_arr[numb].kuyruk,arr_input2[r].value[0]); // add to process in client's queue
        }
        else if(arr_input2[r].fonk[0]=='I') // add to character in server's or client's stack
        {
            int numb2=atoi(arr_input2[r].client_num)-1; // client number or server number
            if(stack_full(client_arr[numb2].yigin))
                push(stk_arr[numb2].stk_o,'2'); // error for client's or server's stack is full
            else
                push(client_arr[numb2].yigin,arr_input2[r].value[0]); // add to value in client's or server's queue
        }
        else if(arr_input2[r].fonk[0]=='S') // deleting the character from client's stack or queue and add to character in server's queue
        {
            int numb3=atoi(arr_input2[r].client_num)-1; // which item
            if(isEmpty(client_arr[numb3].kuyruk)&&stack_empty(client_arr[numb3].yigin))  //
                push(stk_arr[numb3].stk_o,'3'); //error for client's stack and queue empty
            else
            {
                if(stack_empty(client_arr[numb3].yigin))
                {
                    char sent=dequeue(client_arr[numb3].kuyruk); // sent value from client's queue
                    push(stk_arr[numb3].stk_o,sent); // add to this value in log history stack
                    if(isFull(client_arr[satir-1].kuyruk))
                        push(stk_arr[satir-1].stk_o,'1'); // error for server's queue is full
                    else
                        enqueue(client_arr[satir-1].kuyruk,sent);
                }
                else
                {
                    char sent=pop(client_arr[numb3].yigin); // sent value from client's stack
                    push(stk_arr[numb3].stk_o,sent); // add to this value in log history stack
                    if(isFull(client_arr[satir-1].kuyruk))
                    {
                        push(stk_arr[satir-1].stk_o,'1');// error for server's queue is full
                    }
                    else
                        enqueue(client_arr[satir-1].kuyruk,sent);
                }
            }
        }
        else if(arr_input2[r].fonk[0]=='O') // delete to character in server's stack or queue
        {
            if(isEmpty(client_arr[satir-1].kuyruk)&&stack_empty(client_arr[satir-1].yigin))
                push(stk_arr[satir-1].stk_o,'3');//error for server's queue and stack empty and add in log history stack
            else
            {
                if(stack_empty(client_arr[satir-1].yigin))
                {
                    char silinen=dequeue(client_arr[satir-1].kuyruk); // delete to character server's queue
                    push(stk_arr[satir-1].stk_o,silinen); // add to this value in server's log history stack
                }
                else
                {
                    char silinen=pop(client_arr[satir-1].yigin); // delete to character server's stack
                    push(stk_arr[satir-1].stk_o,silinen); // add to this value in server's log history stack
                }
            }
        }
    }
}
void free_memory(int satir,int **input1) // function to free memory for 2D array
{
    int i1;
    for( i1 = 0; i1 < satir; i1++ )
    {
        free(input1[i1]);
    }
    free(input1);
}
int main(int argc, char* argv[])
{
    ////////// First Text File //////////////////////////////////////////
    FILE *fp1;
    char birkelime[10]; // to read word for word from text file
    char c_satir[10]; // to read first row. its item size

    char f_name[100];
    strcpy(f_name,argv[1]);
    fp1 = fopen(f_name,"r"); // f_name is a first input file.

    fgets(c_satir,10,fp1); // reading first row
    int satir=atoi(c_satir); // convert to int. satir is item size.

    int **input1;
    input1=(int**)malloc(satir*sizeof(int*));  // for keeping items queue's and stack's size in 2d array.
    int k;
    for(k=0; k<satir; k++)
    {
        input1[k]=malloc(2*sizeof(int));
    }

    int i,j;
    for(i=0; i<satir; i++) //It reads the file until the number of rows.
    {
        for(j=0; j<2; j++)
        {
            fscanf(fp1,"%s",birkelime);
            input1[i][j]=atoi(birkelime); //each word that is read is assigned to the input1 2d array.
        }
    }

    client *client_arr=(client*)malloc(satir*sizeof(client)); //an array of client struct

    int i1,j1;
    // in this loop created stack and queue for client and server
    for(i1=0; i1<satir; i1++)
    {
        for(j1=0; j1<2; j1++)
        {
            int w=input1[i1][j1];
            if(j1==0)
            {
                (client_arr+i1)->kuyruk= createQueue(w);
            }
            if(j1==1)
            {
                (client_arr+i1)->yigin= createStack(w);
            }
        }
    }
/////////// Second Text File///////////////////////////////

    FILE *fp2;
    char f_name2[100];
    strcpy(f_name2,argv[2]);
    fp2 = fopen(f_name2,"r"); //f_name2 is second input file
    char lyne[101]; // for each line

    char *item;
    int reccount = 0;
    char first_row[10]; // for first row
    fgets(first_row,10,fp2); // read to first row
    int ilk_satir=atoi(first_row); // ilk_satir is second text file's row size


    input2 *arr_input2=(input2*)malloc(ilk_satir*sizeof(input2)); // an array of input2 struct

    // Read file line by line
    int x=0;
    for(x=0;x<ilk_satir;x++)
    {
        fgets(lyne,100,fp2);
        item = strtok(lyne," ");
        strcpy(arr_input2[reccount].fonk,item);

        item = strtok(NULL," ");
        strcpy(arr_input2[reccount].client_num,item);

        item = strtok(NULL,"\n");
        strcpy(arr_input2[reccount].value,item);

        reccount++;
    }

    output_stk *stk_arr= (output_stk*)malloc(satir*sizeof(output_stk)); //an array of output_stk struct
    int m;
    for(m=0; m<satir; m++)
    {
        (stk_arr+m)->stk_o=createStack(ilk_satir*2); // for every item created log history stack
    }

    //function is called for the actions in the second text file to occur.
    func(arr_input2,ilk_satir,satir,stk_arr,client_arr);

    //////////// Output Text File/////////////////
    FILE *output;
    char f_output[100];
    strcpy(f_output,argv[3]);
    output = fopen(f_output,"w"); // f_output is output file name.
    int g,s;
    for(g=0; g<satir; g++)
    {
        for(s=0; s<ilk_satir; s++)
            if(stk_arr[g].stk_o->stack_arr[s]!=0)
            {
                fprintf(output,"%c ",stk_arr[g].stk_o->stack_arr[s]); // to write log history in output text file

            }
        fprintf(output,"%c",'\n');
    }
    int h;
    for(h=0; h<satir; h++)
    {
        free(client_arr[h].kuyruk->kuyruk_arr);
        free(client_arr[h].yigin->stack_arr);
        free(client_arr[h].kuyruk);
        free(client_arr[h].yigin);
        free(stk_arr[h].stk_o->stack_arr);
        free(stk_arr[h].stk_o);
    }
    free_memory(satir,input1);
    free(client_arr);
    free(stk_arr);
    free(arr_input2);
    fclose(fp1);
    fclose(fp2);
    fclose(output);
    return 0;
}
