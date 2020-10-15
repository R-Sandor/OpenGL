#include <stdlib.h>
#include <gl/glew.h>
#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "utility.h"
#include "histogram.h"

 /**
  * Author: Raphael Sandor
  * Date:	9/28/2020
  * 
  * This program will take input data and turn the input
  * data in to probability distribution function with a
  * histogram bar graph.
  */


using namespace std;

/*
	Globals and defaults. 
*/
int  INTERVALS = 30;
int  BORDER = 18;
int  GAP = 40;

// Width and Height of windows
int WIDTH, HEIGHT;
string file			= "normal.dat";
string distribution = "Normal";

double Mu			= 0.0;
double sigma		= 1.0;

Histogram *normHist;
Histogram *expoHist;
Histogram *fNmHist; // first name data histogram
Histogram *lstNmHist;

GLvoid* font_9_by_15		= GLUT_BITMAP_9_BY_15;
GLvoid* font_8_by_13		= GLUT_BITMAP_8_BY_13;
GLvoid* font_helvetica_12	= GLUT_BITMAP_HELVETICA_12;


void display(void)
{
	int probabTxtLocY = HEIGHT - BORDER - 15;
	int maxDenY = HEIGHT - BORDER- GAP - 15;

	/* clear all pixels  */
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(1.0, 1.0, 1.0);
	
	glBegin(GL_LINES);
		glVertex2f(BORDER, HEIGHT - BORDER);
		glVertex2f(BORDER, BORDER);
		glVertex2f(WIDTH - BORDER, BORDER);
		glVertex2f(BORDER, BORDER);
	glEnd();

	double * bins;
	if (INTERVALS == 30)
		bins = normHist->getBins30();
	else if (INTERVALS == 40)
		bins = normHist->getBins40();
	else
		bins = normHist->getBins50();

	// Print Text to the screen. 
	printString(BORDER + 11, maxDenY,
		font_8_by_13, to_string(normHist->getMaxDensity(INTERVALS)));

	printString(BORDER + 7, HEIGHT - BORDER * 2,
		font_8_by_13, "Probability Density");
	printString(WIDTH - BORDER - 21, BORDER + 10,
		font_8_by_13, "Data");
	printString(WIDTH - GAP * 5 - 20, probabTxtLocY,
		font_8_by_13, "File: " + file);

	string str;
	str = to_string(normHist->getMin());
	printString(WIDTH - GAP * 5 - 20, probabTxtLocY - 15,
		font_8_by_13, "Min: " + str.erase(str.find_last_not_of('0') + 1, std::string::npos));

	str = to_string(normHist->getMax());

	printString(WIDTH - GAP * 5 - 20, probabTxtLocY - 30,
		font_8_by_13, "Max: " + str.erase(str.find_last_not_of('0') + 1, std::string::npos));
	printString(WIDTH - GAP * 5 - 20, probabTxtLocY - GAP - 5,
		font_8_by_13, "Num of Intervals: " + to_string(INTERVALS));
	
	if (file == "normal.dat") {
		cout << "Normal.dat" << endl;
		// Draw a line at the max
		// what is the height equiv.
		cout << "Top Bound " << probabTxtLocY << endl;
		


		printString(WIDTH - GAP * 5 - 20, probabTxtLocY - GAP*2,
			font_8_by_13, "Distribution: " + distribution);

		string str = to_string(sigma);
		if (Mu == 0)
			str = "0";

		printString(WIDTH - GAP * 5 - 20, probabTxtLocY - GAP*2 - 17,
			font_8_by_13, "Mu: " + str);
		if (sigma != 1)
			str = str.erase(str.find_last_not_of('0') + 1, std::string::npos);
		else {
			str = "1";
		}
		printString(WIDTH - GAP * 5 - 20, probabTxtLocY - GAP*2 - 35,
			font_8_by_13, "Sigma: " + str);

		glBegin(GL_LINES);
			glVertex2f(BORDER + 7, maxDenY);
			glVertex2f(BORDER, maxDenY);
		glEnd();
		double maxDensity = normHist->getMaxDensity(INTERVALS);
		double width = (WIDTH - BORDER * 4)/INTERVALS;
		double height = 0.0;
		for (int i = 0; i < INTERVALS; i++)
		{
			
			height = ((double)maxDenY- BORDER) * (bins[i] / maxDensity);
			
			cout << "bins[i] " << bins[i] << endl;
			cout <<"maxDenY- BORDER " << (double)maxDenY - BORDER <<   " probabTxtLocY " << probabTxtLocY <<  " height " << height  << " BORDER " << BORDER << " Max Density " << maxDensity<< endl;
			
			

			glBegin(GL_LINE_STRIP);
				glVertex2f(BORDER*3 + width * i, BORDER);
				glVertex2f(BORDER*3 + width * i, BORDER + height);
				glVertex2f(BORDER*3 + width * i + width, BORDER + height);
				glVertex2f(BORDER*3 + width * i + width, BORDER);
			glEnd();
			
		}

	}
	else if (file == "expo.dat") {
		cout << "Working on this " << endl; 
	}
	else if (file == "18.dat") {
		cout << "18.dat" << endl;
	}
	else if (file == "19.dat") {
		cout << "19.dat" << endl;

	}
	glFlush();

}

void init(void)
{
	/* select clearing color 	*/
	glClearColor(0.0, 0.0, 0.0, 0.0);

	/* initialize viewing values  */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();	
}

void myReshape(int w, int h)
{
	cout << "RESHAPE Called" << endl;
	WIDTH = w;
	HEIGHT = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);	
	glLoadIdentity();

	//gluOrtho2D(-100, 1, -10, 1);
	gluOrtho2D(0, w, 0, h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutPostRedisplay();
}

void progMenu(int value)
{
	switch (value) {

	default:
		break;
	}
}

/*
 * Main application.
 * Calls functions to setup min/max
 * Handles drawing historgrams and changing data set mode.
 */
int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	// Create the ifstream
	ifstream normData;	// Normal data set
	ifstream expoData;	// Exponential data set
	ifstream fNmData;	// First name data set
	ifstream lstNmData; // Last name data set

	// simply open & check to make sure all files openend correctly.
	openFiles(&normData, &expoData, &fNmData, &lstNmData);

	//create our historgram's data.
	normHist = new Histogram(&normData);
	expoHist = new Histogram(&expoData);
	fNmHist	 = new Histogram(&fNmData); // first name data histogram
	lstNmHist= new Histogram(&lstNmData); // last name

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 450);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Input Analysis");
	glewInit();

	glutReshapeFunc(myReshape);


	int fileMenu = glutCreateMenu(progMenu);
	glutAddMenuEntry("normal.dat", 30);
	glutAddMenuEntry("expo.dat", 30);

	// Default should start in normal distribution. 
	int distMenu = glutCreateMenu(progMenu);
	glutAddMenuEntry("Normal", 30);
	glutAddMenuEntry("Exponential", 30);
	
	int histMenu = glutCreateMenu(progMenu);
	glutAddMenuEntry("30", 30);
	glutAddMenuEntry("40", 40);
	glutAddMenuEntry("50", 50);

	
	int paramStep = glutCreateMenu(progMenu);
	glutAddMenuEntry("0.01", 30);
	glutAddMenuEntry("0.02", 40);
	glutAddMenuEntry("0.05", 50);


	// Create the main menu
	glutCreateMenu(progMenu);
	glutAddSubMenu("File", fileMenu);
	glutAddSubMenu("Distrubtion", distMenu);
	glutAddSubMenu("Histogram", histMenu);
	glutAddSubMenu("Parameter Step", paramStep);
	glutAddMenuEntry("Exit", 27);

	
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	int mainMenu = glutCreateMenu(progMenu);
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;   
}
