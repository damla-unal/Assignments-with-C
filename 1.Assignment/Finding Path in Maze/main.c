#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#define MAX_SIZE 1000

typedef struct
{
    int maze_row, maze_col, move_dir;
} node;      // struct that will hold the maze coordinates and direciton to be pushed on the stack

typedef struct
{
    int yCoor, xCoor;  //vertical and horizontal direciton
} direction;

direction move[4] =   //it can move four direction
{
    {-1, 0},{1,0},   //  North South
    {0, 1},{0,-1}   //  East West
};

node stack1[MAX_SIZE];  //for keeping the true path

int top = -1;  // now stack is empty
int row;      //for maze row size


// function to push the coordinates of a maze position and direction of movement onto the stack
void push( int *top, node item )
{
    if( *top >= MAX_SIZE-1 )
        printf("Stack is full.");
    else
        stack1[++*top] = item;
}

// function to pop a maze location off of the stack
node pop( int *top )
{
    if( *top < 0 )
        printf("stack is empty.");
    return stack1[(*top)--];
}

// function to find the direction of movement on solution path
char find_direction(int dir_satir,int dir_sutun)
{
    if(dir_satir==1 && dir_sutun==0) //south
        return 'S';
    else if(dir_satir==-1 && dir_sutun==0) // north
        return 'N';
    else if(dir_satir==0 && dir_sutun==-1) // west
        return 'W';
    else                                // east
        return 'E';
}

// function to create solution path from start coordinates to exit coordinates
void finding_path(char maze[][row], int marked[][row], int size, int start_x, int start_y,int end_x, int end_y)
{

    int satir, sutun;          //current row and current column
    int this_row, this_col;    // next row and next column
    int i, direction;
    int isFind = 0; // as boolean variable isFind is false
    node location;


    stack1[0].maze_row = start_x;       // set initial position
    stack1[0].maze_col =start_y;
    stack1[0].move_dir = 0;             // set initial direction

    marked[1][1] = 2; //mark the start location as visited
    top = 0; // moved the first location

    while( top>-1 && !isFind )  // stack is full and exit is found
    {

        location= pop(&top);  //get location info from the stack
        satir = location.maze_row;  // get current row
        sutun = location.maze_col; // get current column
        direction = location.move_dir; // which direction to go

        while( direction<4 && !isFind ) //until isFind is true, get new row and new column
        {
            this_row = satir + move[direction].yCoor;
            this_col = sutun + move[direction].xCoor;

            if( this_row == end_x && this_col == end_y )  //is find exit point
                isFind = 1; // isFind is true


            else if( maze[this_row][this_col]!='1' && marked[this_row][this_col]!=2 && this_row<size && this_col<size && 0<=this_row && 0<=this_col)
            {
                marked[this_row][this_col] = 2;  // marks visited places in the maze as a 2 so the search algorithm doesn't repeat checking
                location.maze_row = satir; // the row came from
                location.maze_col = sutun; // the column came from
                location.move_dir = ++direction; // if go back, look this direction
                push( &top, location );// push the maze location in stack
                satir = this_row; // set new row
                sutun = this_col; // set new column
                direction = 0;  //set the initial loop control value

            }
            else ++direction; // new location cannot move, try other direction
        }
    }
    if( isFind )  // if succeed found exit , print path. but not found , print other message.
    {
        FILE *file_write;
        file_write = fopen("path.txt","w");  // write solution path to the path.txt


        fprintf(file_write,"%s","Start ");

        for( i=0 ; i<=top ; i++ )
        {
            int dir_satir = (int)stack1[i+1].maze_row - (int)stack1[i].maze_row; // in which direction the row has been moved
            int dir_sutun = (int)stack1[i+1].maze_col - (int)stack1[i].maze_col; // in which direction the column has been moved
            fprintf(file_write,"%c ",find_direction(dir_satir,dir_sutun)); // write this direction in path.txt
        }
        int son_satir = satir - (int)stack1[top].maze_row; // made for the end row of the above process
        int son_sutun = sutun - (int)stack1[top].maze_col; // made for the end column of the above process
        fprintf(file_write,"%c ",find_direction(son_satir,son_sutun));

        int cikis_satir = end_x-satir; // move to exit
        int cikis_sutun = end_y-sutun;
        fprintf(file_write,"%c ",find_direction(cikis_satir,cikis_sutun));

        fprintf(file_write,"%s","Exit ");
        fclose(file_write);

    }
    else
        printf("Cannot found exit\n");
}



// function to create a maze , reading from file
void reading_maze(FILE *file1, char maze[][row], int row, int column)
{
    int i,j;
    while(!feof(file1))
    {
        for(i=0; i<row; i++)
        {
            for(j=0; j<column; j++)
            {
                fscanf(file1,"%c",&maze[i][j]); // assigning the elements of the maze
            }
            fscanf(file1,"\n");
        }
    }
}

int main(int argc,char *argv[])
{

    char filename[30];
    strcpy(filename,argv[1]); //copy argv1 to filename
    FILE *f;
    char ch;
    int count=0;
    f=fopen(filename,"r");  // maze.txt opened for reading

    if(f==NULL)
    {
        printf("Cannot open the file %s",filename);

        exit(1);
    }
    while(!feof(f))
    {
        ch=getc(f);
        if(ch=='\n')
            count++;  // for finding row size
    }

    fclose(f);

    row=count+1;
    int column=row; // it is square matrix
    char maze[row][column];
    int marked[row][column];  //for mark visited spaces in the maze as a 2 so the search algorithm doesn't repeat checking
    int start_x, start_y;
    int end_x, end_y;

    FILE *file;
    file=fopen(filename,"r");

    reading_maze(file,maze,row,column);

    int a,b ;
    for(a=0; a<row; a++)
    {
        for(b=0; b<column; b++)
        {
            if(maze[0][b]=='S')  // for finding start position
            {
                start_x=0;
                start_y=b;
            }
            if(maze[row-1][b]=='E') // for finding exit position
            {
                end_x=row-1;
                end_y=b;
            }
        }
    }
    finding_path(maze,marked,row, start_x, start_y, end_x, end_y);
    fclose(file);
    return 0;
}
