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

int main(int argc,  char**argv)
{
    if(argc != 2)
    {
        cout << "Useage: ./a.out worldFile\n";
        return -1;
    }

    //world array
    char world[MAX_HEIGHT][MAX_WIDTH];

    //loop variables;
    int i,j;

    //goal variables
    string item;
    int r, c;

    //open the world file
    ifstream ifs;
    ifs.open(argv[1]);

    //Set up World Matrix
    for(i = 0; i < MAX_HEIGHT; i++)
    {
        for(j = 0; j < MAX_WIDTH; j++)
        {
            ifs >> world[i][j];
            //cout << world[i][j];
        }
        //cout << endl;
    }

    cout << "Please input the goal state in the form (x,y).\n \
            Remember the max size is 16x8.\n";

    cin >> item;
    if(item.length() != 5)
    {
        cout << "Goal State must be in the form (x,y)\n";
        return -1;
    }


    r = int(item[3]) - 49;
    c = int(item[1]) - 49;
    world[r][c] = '2';

    for(i = 0; i < MAX_HEIGHT; i++)
    {
        for(j = 0; j < MAX_WIDTH; j++)
        {
             cout << world[i][j];
        }
        cout << endl;
    }

    //start waveFront algorithm here

    return 0;

}
