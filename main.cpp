#include "GL/freeglut.h"
#include "GL/gl.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <iostream>
#include <unistd.h>
#include <vector>

using namespace std;

int length = 500;
int delay;
int algorithmNumber;
vector <int> array (length);

void createArray()
{
	for(int i = 0; i < length; i++)
	{
		array[i] = rand() % array.size();
	}
}

void printArray(vector<int> v)
{
	for(int i = 0; i < v.size(); i++)
	{
		cout<< v[i] << ", ";

	}

	cout<<endl<<endl;
}

void renderFunction()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	
	float l = (float) length;
	float widthAdder = 1/l;

	for(int i = 0; i < array.size(); i++)
	{
		glBegin(GL_POLYGON);

		float arrayIndexHeightRation = 2*(array[i] + 1)/l;
		float widthIndexAdder = 2*i/l;

		float leftX   = -1 + widthIndexAdder;
		float rightX  = leftX + widthAdder;
		float bottomY = -1;
		float topY    = bottomY + arrayIndexHeightRation;

		glColor3f(0.0, 0.0, 0.0);

		glVertex2f(leftX, bottomY);
		glVertex2f(rightX, bottomY);
		glVertex2f(rightX, topY);
		glVertex2f(leftX, topY);

		glEnd();
	}

	glFlush();
}

void insertionSort()  
{  
    int i, key, j;  
    for (i = 1; i < array.size(); i++) 
    {  
        key = array[i];  
        j = i - 1;  
  
        while (j >= 0 && array[j] > key) 
        {  
            array[j + 1] = array[j];  
            j = j - 1; 
            renderFunction();
            usleep(delay);
            printArray(array); 
        }  
        array[j + 1] = key;
    }  
}

void swap(int *xp, int *yp)  
{  
    int temp = *xp;  
    *xp = *yp;  
    *yp = temp;  
} 

void bubbleSort()  
{  
    int i, j;  
    for (i = 0; i < array.size()-1; i++)
    {
    	for (j = 0; j < array.size()-i-1; j++)
    	{
    		if (array[j] > array[j+1])
    		{
    			swap(&array[j], &array[j+1]);
    			renderFunction();
            	usleep(delay);
            	printArray(array); 
    		}  
    	}  
    }     
} 

void selectionSort()  
{  
    int i, j, min_idx;  
  
    for (i = 0; i < array.size()-1; i++)  
    {   
        min_idx = i;  
        for (j = i+1; j < array.size(); j++)
        {
        	if (array[j] < array[min_idx])  
        	{
            	min_idx = j;
        	} 
        } 
  
        swap(&array[min_idx], &array[i]);
        renderFunction();
        usleep(delay);
        printArray(array);  
    }  
}  

void keyboardEvent(unsigned char c, int x, int y)
{
	if(c == 27)
	{
		exit(0);
	}
	else if(c == 's')
	{
		switch(algorithmNumber){

			case 0: insertionSort(); break;
			case 1: bubbleSort(); break;
			case 2: selectionSort(); break;	
		}
	}
	else if(c == 'r')
	{
			createArray();
			renderFunction();
		
	}
}

int main(int argc, char *argv[])
{
	cin >> delay >> algorithmNumber;

	srand (time(NULL));

	createArray();

	printArray(array);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(length,length);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Sorting Algorithm Visualization");

	glutDisplayFunc(renderFunction);
	glutKeyboardFunc(keyboardEvent);

	glutMainLoop();
		
	return 0;
}