/*
Author: Nathan Perry
Class: Robotics
Assignment: Project 3
Instructor: Li

Purpose: To program a Wavefront algorithm and as memory efficient as possible
*/

#include <iostream>
#include <fstream>

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
    char rear = MAX_SIZE-1;

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
            //cout << world[i][j];
        }
        //cout << endl;
    }

    //read in goal state
    cout << "Please input the goal state in the form (x,y).\n \
            Remember the max size is 16x8.\n";
    cin >> item >> r >> item >> c >> item;

    //Set up goal state value
    worldView[r][c].value = 2;

    //make sure world looks right.
    for(i = 0; i < MAX_HEIGHT; i++)
    {
        for(j = 0; j < MAX_WIDTH; j++)
        {
             cout << short(worldView[i][j].value);
        }
        cout << endl;
    }

    //start waveFront algorithm here

    //Push Root onto Fringe (goal)
    fringe[top] = worldView[r][c];
    short num_ele = 1;

    while(num_ele != 0)
    {
        cout << "Here" << endl;
        //expand top
        //check top ((row boundry and visited/wall))
        if(fringe[top].row-1 >= 0 && worldView[fringe[top].row-1][fringe[top].column].value == 0)
        {
            //update value in new location
            worldView[fringe[top].row-1][fringe[top].column].value = fringe[top].value + 1;
            //push onto queue
            fringe[(num_ele+1)%MAX_SIZE] = worldView[fringe[top].row-1][fringe[top].column];
            num_ele += 1;
        }

        //check left
        if(fringe[top].column-1 >= 0 && worldView[fringe[top].row][fringe[top].column-1].value == 0)
        {
            worldView[fringe[top].row][fringe[top].column-1].value = fringe[top].value + 1;
            fringe[(num_ele+1)%MAX_SIZE] = worldView[fringe[top].row][fringe[top].column-1];
            num_ele += 1;
        }

        //check bottom
        if(fringe[top].row+1 < MAX_HEIGHT && worldView[fringe[top].row+1][fringe[top].column].value == 0)
        {
            worldView[fringe[top].row+1][fringe[top].column].value = fringe[top].value + 1;
            fringe[(num_ele+1)%MAX_SIZE] = worldView[fringe[top].row+1][fringe[top].column];
            num_ele += 1;
        }

        //check right
        if(fringe[top].column+1 < MAX_WIDTH && worldView[fringe[top].row][fringe[top].column+1].value == 0)
        {
            worldView[fringe[top].row][fringe[top].column+1].value = fringe[top].value + 1;
            fringe[(num_ele+1)%MAX_SIZE] = worldView[fringe[top].row][fringe[top].column+1];
            num_ele += 1;
        }

    for(i = top; i <=num_ele; i++)
    {
        cout << short(fringe[i].row) << " " << short(fringe[i].column) << " " << short(fringe[i].value) << endl;
    }
        top = (top + 1) % MAX_SIZE;
        num_ele -= 1;
    
    for(i = 0; i < MAX_HEIGHT; i++)
    {
        for(j = 0; j < MAX_WIDTH; j++)
        {
             cout << short(worldView[i][j].value) << " ";
        }
        cout << endl;
    }
    cout << endl << endl;

    }

    //fringe[top] = NULL;
    return 0;

}
