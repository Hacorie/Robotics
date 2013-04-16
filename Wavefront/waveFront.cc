/*
Author: Nathan Perry
Class: Robotics
Assignment: Project 3
Instructor: Li

Purpose: To program a Wavefront algorithm and as memory efficient as possible
*/

#include <iostream>
#include <fstream>
#include <cstdio>

using namespace std;

//Constants
#define     MAX_WIDTH   16
#define     MAX_HEIGHT  8
#define     MAX_SIZE    32

typedef struct
{
    char row;       //keeps track of row in world
    char column;    //keeps track of column in world
    char value;     //0 for not vistied; 1 for wall; 2 for goal; other visited;
}node;

int main(short argc,  char**argv)
{
    if(argc != 2)
    {
        cout << "Usage: ./a.out worldFile\n";
        return -1;
    }

    //world array
    node worldView[MAX_HEIGHT][MAX_WIDTH];

    //array based queue
    node fringe[MAX_SIZE];
    char top = 0;
    char rear = 0;

    //loop variables;
    char i,j;

    //goal variables
    short r, c;
    char item;

    //open the world file
    ifstream ifs;
    ifs.open(argv[1]);

    //Set up World Matrix
    for(i = 0; i < MAX_HEIGHT; i++)
    {
        for(j = 0; j < MAX_WIDTH; j++)
        {
            ifs >> worldView[i][j].value;
            worldView[i][j].value -= '0';
            worldView[i][j].row = i;
            worldView[i][j].column = j;
        }
    }

    //read in goal state
    cout << "Please input the goal state in the form (x,y).\n \
            Remember the max size is 16x8.\n";
    cin >> item >> r >> item >> c >> item;

    //Set up goal state value
    worldView[r][c].value = 2;

    /*
    //make sure world looks right.
    for(i = 0; i < MAX_HEIGHT; i++)
    {
        for(j = 0; j < MAX_WIDTH; j++)
        {
             cout << short(worldView[i][j].value);
        }
        cout << endl;
    }
    */

    //start waveFront algorithm here

    //Push Root onto Fringe (goal)
    fringe[top] = worldView[r][c];
    short num_ele = 1;

    while(num_ele != 0)
    {
        //expand top
        //check top ((row boundry and visited/wall))
        if(fringe[top].row-1 >= 0 && worldView[fringe[top].row-1][fringe[top].column].value == 0)
        {
            //update value in new location
            worldView[fringe[top].row-1][fringe[top].column].value = fringe[top].value + 1;
            //push onto queue; update number of items; update rear
            fringe[(rear+1)%MAX_SIZE] = worldView[fringe[top].row-1][fringe[top].column];
            num_ele += 1;
            rear = (rear+1)%MAX_SIZE;
        }

        //check left
        if(fringe[top].column-1 >= 0 && worldView[fringe[top].row][fringe[top].column-1].value == 0)
        {
            worldView[fringe[top].row][fringe[top].column-1].value = fringe[top].value + 1;
            fringe[(rear+1)%MAX_SIZE] = worldView[fringe[top].row][fringe[top].column-1];
            num_ele += 1;
            rear = (rear+1)%MAX_SIZE;
        }

        //check bottom
        if(fringe[top].row+1 < MAX_HEIGHT && worldView[fringe[top].row+1][fringe[top].column].value == 0)
        {
            worldView[fringe[top].row+1][fringe[top].column].value = fringe[top].value + 1;
            fringe[(rear+1)%MAX_SIZE] = worldView[fringe[top].row+1][fringe[top].column];
            num_ele += 1;
            rear = (rear+1)%MAX_SIZE;
        }

        //check right
        if(fringe[top].column+1 < MAX_WIDTH && worldView[fringe[top].row][fringe[top].column+1].value == 0)
        {
            worldView[fringe[top].row][fringe[top].column+1].value = fringe[top].value + 1;
            fringe[(rear+1)%MAX_SIZE] = worldView[fringe[top].row][fringe[top].column+1];
            num_ele += 1;
            rear = (rear+1)%MAX_SIZE;
        }
        //update first ele and pop
        top = (top + 1) % MAX_SIZE;
        num_ele -= 1;

    }


    printf("Start: [0,0]\nGoal: [%d,%d]\n", r,c);
    printf("The Total Number of Steps: %d\n", worldView[0][0].value-2);
    printf("\nThe Path is: [%d,%d]", 0, 0);

    item = worldView[0][0].value;
    //find Shortest Path
    i = 0; j = 0;
    while(i != r || j != c)
    {
        //check neighbors; take first shortest available
        //check up
        if(i-1 >= 0 && worldView[i-1][j].value != 1 && worldView[i-1][j].value < item)
        {
            item = worldView[i-1][j].value;
            printf(" -> [%d,%d]", i-1, j);
            i-=1;
        }
        //check left
        else if(j-1 >= 0 && worldView[i][j-1].value != 1 && worldView[i][j-1].value < item)
        {
            item = worldView[i][j-1].value;
            printf(" -> [%d,%d]", i, j-1);
            j-=1;
        }
        //check down
        else if(i+1 < MAX_HEIGHT && worldView[i+1][j].value != 1 && worldView[i+1][j].value < item)
        {
            item = worldView[i+1][j].value;
            printf(" -> [%d,%d]", i+1, j);
            i+=1;
        }
        //check right
        else if(j+1 < MAX_WIDTH && worldView[i][j+1].value != 1 && worldView[i][j+1].value < item)
        {
            item = worldView[i][j+1].value;
            printf(" -> [%d,%d]", i, j+1);
            j+=1;
        }
        else
        {
            printf("Should never get here unless all surrounding tiles are the same value\n");
            return -1;
        }
    }
    printf("\n");

    //Print the World
    for(i = 0; i < MAX_HEIGHT; i++)
    {
        for(j = 0; j < MAX_WIDTH; j++)
            printf("%4d",  short(worldView[i][j].value));
        printf("\n");
    }
    return 0;
}
