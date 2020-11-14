#include <stdlib.h>
#include <gl/glew.h>
#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "utility.h"
#define _USE_MATH_DEFINES
#include <math.h> 
#include "histogram.h"

/**
 * \file 
 * This the main file for Analysis Input. 
 * \author: Raphael J. Sandor
 * \date:	9/28/2020
 * 
 * \brief This program will take input data and turn the input
 * data in to probability distribution function with a
 * histogram bar graph.
 */

using namespace std;
/*
	\file Globals and defaults.
*/
int  INTERVALS = 30;
int  BORDER = 18;
int  GAP = 40;

/// Width and Height of windows
int WIDTH, HEIGHT;
string FILE_NAME = "normal.dat";
string DISTRIBUTION = "Normal";

double MU = 0.0;
double SIGMA = 1.0;
double STEP = .05;
double LAMBDA = 1.0;

/// \brief histogram pointers
Histogram* normHist;
Histogram* expoHist;
Histogram* fNmHist; 
Histogram* lstNmHist;

///  font styles
GLvoid* font_9_by_15 = GLUT_BITMAP_9_BY_15;
GLvoid* font_8_by_13 = GLUT_BITMAP_8_BY_13;
GLvoid* font_helvetica_12 = GLUT_BITMAP_HELVETICA_12;

/**********  Draw funtions **********/

/**
 * Sets up the text need by the program.
 *
 * \param titleLocY			- Location of the title
 * \param maxDesTxtLocY		- The Y model position of the density text.
 * \param hist				- The histogram for the calculation.
 */
void setupText(int titleLocY, int maxDesTxtLocY, Histogram* hist)
{
	// Print Text to the screen. 
	printString(BORDER + 11, maxDesTxtLocY,
		font_8_by_13, to_string(hist->getMaxDensity(INTERVALS)));

	printString(BORDER + 7, HEIGHT - BORDER * 2,
		font_8_by_13, "Probability Density");

	printString(WIDTH - BORDER - 21, BORDER + 10,
		font_8_by_13, "Data");

	printString(WIDTH - GAP * 5 - 20, titleLocY,
		font_8_by_13, "File: " + FILE_NAME);
	
	char buffer[32];
	memset(buffer, 0, sizeof(buffer));
	snprintf(buffer, sizeof(buffer), "%g", hist->getMin());
	string min(buffer);
	printString(WIDTH - GAP * 5 - 20, titleLocY - 15,
		font_8_by_13, "Min: " + min);

	memset(buffer, 0, sizeof(buffer));
	snprintf(buffer, sizeof(buffer), "%g", hist->getMax());
	string max(buffer);

	printString(WIDTH - GAP * 5 - 20, titleLocY - 30,
		font_8_by_13, "Max: " + max);

	printString(WIDTH - GAP * 5 - 20, titleLocY - GAP - 5,
		font_8_by_13, "Num of Intervals: " + to_string(INTERVALS));
}

/**
 * draw the X and Y cordinate plane.
 *
 * \param maxDensTxtLocY	- The Y model position of the density text
 */
void drawXY(int maxDensTxtLocY)
{
	glBegin(GL_LINES);
	glVertex2f(BORDER, HEIGHT - BORDER);
	glVertex2f(BORDER, BORDER);
	glVertex2f(WIDTH - BORDER, BORDER);
	glVertex2f(BORDER, BORDER);
	glEnd();

	/// Finish up border.
	glBegin(GL_LINES);
	glVertex2f(BORDER + 7, maxDensTxtLocY);
	glVertex2f(BORDER, maxDensTxtLocY);
	glEnd();
}

/**
 * Draw the text for a normal distribution.
 *
 * \param titleLocY - Y model position of the title.
 */
void normalDistTxt(int titleLocY) {
	/// Draw a line at the max
	/// what is the height equiv.	
	glColor3f(.259, .5294, .96078);
	printString(WIDTH - GAP * 5 - 20, titleLocY - GAP * 2,
		font_8_by_13, "Distribution: " + DISTRIBUTION);

	string str = to_string(MU);

	printString(WIDTH - GAP * 5 - 20, titleLocY - GAP * 2 - 17,
		font_8_by_13, "Mu: " + rmTrail0s(str));
	str = to_string(SIGMA);
	
	printString(WIDTH - GAP * 5 - 20, titleLocY - GAP * 2 - 35,
		font_8_by_13, "Sigma: " + rmTrail0s(str));

}

/**
 * Draws the histograms.
 * 
 * \param maxDensity	 - Maximum histogram density.
 * \param maxDensTxtLocY - Maximum density text y location.
 * \param hist			 - Histogram used to calculate bins etc.
 * \param bins			 - The calculated results of each interval 
 *						   in terms of density.
 */
void drawHistogram(double maxDensity, int maxDensTxtLocY,
	Histogram* hist, double* bins)
{
	/** 
	*   Draw our histograms in proportion to the screen space
	 *  within the the borders.
	 */
	double histPxlWidth = (WIDTH - BORDER * 4) / INTERVALS;
	double histPxlHeight = 0.0;
	glColor3f(.941, .521, .0745);
	double normalizedDensity = ceil(maxDensity * 100) / 100;
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < INTERVALS; i++)
	{
		histPxlHeight = ((double)maxDensTxtLocY - BORDER) * (bins[i] / normalizedDensity);
		glVertex2f(BORDER * 3 + histPxlWidth * i, BORDER);
		glVertex2f(BORDER * 3 + histPxlWidth * i, BORDER + histPxlHeight);
		glVertex2f(BORDER * 3 + histPxlWidth * i + histPxlWidth, BORDER + histPxlHeight);
		glVertex2f(BORDER * 3 + histPxlWidth * i + histPxlWidth, BORDER);
	}
	glEnd();
	glColor3f(1.0, 1.0, 1.0);
}

/**
 * Draw exponential distribution text.
 * 
 * \param titleLocY - Y location of the title.
 */
void expDistTxt(int titleLocY) {

	// Draw a line at the max
	// what is the height equiv.		
	glColor3f(.259, .5294, .96078);
	printString(WIDTH - GAP * 5 - 20, titleLocY - GAP * 2,
		font_8_by_13, "Funtion Type: " + DISTRIBUTION);

	string str = to_string(LAMBDA);
	if (LAMBDA == 0)
		str = "0";
	printString(WIDTH - GAP * 5 - 20, titleLocY - GAP * 2 - 17,
		font_8_by_13, "Lambda: " + rmTrail0s(str));
}

/********** Plot calculations **********/
/**
 * Plot the points for the a normal probability distribution.
 *
 * \param x			- This is the random variable.
 * \param stdDev	- Standard deviation.
 * \param mu		- Expected value.
 * \return			- Returns calculation to plot.
 */
double normDist(double x, double stdDev, double mu) {

	double sqrt2Pie = 0.0;
	double denomLft = 0.0;
	double denomRt = 0.0;
	double numRt = 0.0;
	double prodLeft = 0.0;
	double prodRight = 0.0;

	prodLeft = 1 / (stdDev * sqrt(2 * M_PI));

	numRt = -pow((x - mu), 2.0);
	denomRt = 2 * pow(stdDev, 2.0);

	prodRight = exp(numRt / denomRt);
	return prodLeft * prodRight;
}

/**
 * Plot the points for the a exponential probability distribution.
 *
 * \param x	- This is the random variable.
 * \return  - Returns calculation to plot.
 */
double expoDist(double x) {

	double numerator = exp(-x / LAMBDA);
	double denominator = (1 / LAMBDA);
	return  numerator * denominator;
}

/**
 * Draws a normal distribution.
 * 
 * \param maxDensTxtLocY - Maximum density text y location.
 * \param maxDensity	 - Maximum histogram density.
 * \param hist			 - The selected histogram
 */
void drawNormDist(int maxDensTxtLocY, double maxDensity, Histogram* hist) {
	double yLoc = 0.0;
	double width = hist->getWidth(100);
	double widthPxl = (WIDTH - BORDER * 4) / 100;
	glColor3f(.259, .5294, .96078);
	glBegin(GL_LINE_STRIP);
	double minPoint = hist->getMin();

	for (int x = 0; x < 100; x++)
	{
		double normalDist = normDist(x * width + minPoint, SIGMA, MU);
		yLoc = (((double)maxDensTxtLocY - BORDER) / maxDensity) * normalDist;
		glVertex2f(BORDER * 3 + widthPxl * x, yLoc + BORDER);
	}
	glEnd();
	glColor3f(1.0, 1.0, 1.0);
}

/**
 * Draws a exponential distribution.
 * 
 * \param titleLocY		 - Y position the title.
 * \param maxDensTxtLocY - Maximum density text Y location.
 * \param maxDensity	 - Maximum histogram density.
 * \param hist			 - The selected histogram.
 */
void drawExpoDist(int titleLocY, int maxDensTxtLocY, double maxDensity,
	Histogram* hist)
{
	double yLoc = 0.0;
	double width = hist->getWidth(100);
	double widthPxl = (WIDTH - BORDER * 4) / 100;
	double minPoint = hist->getMin();

	glColor3f(.259, .5294, .96078);
	glBegin(GL_LINE_STRIP);
	for (int x = 0; x < 100; x++)
	{
		double exDist = expoDist(x * width + minPoint);
		yLoc = (((double)maxDensTxtLocY - BORDER) / maxDensity) * exDist;
		glVertex2f(BORDER * 3 + widthPxl * x, yLoc + BORDER);
	}
	glEnd();
	glColor3f(1.0, 1.0, 1.0);

}

/**
 * A wrapper to call either drawNormDist or drawExpoDist.
 * 
 * \param titleLocY			- Y model position of the title.
 * \param maxDensTxtLocY	- Maximum density text y location.
 * \param maxDensity		- Maximum density of histogram data set.
 * \param hist				- Histogram pointer, that points to 
 *							  histogram selected.
 */
void drawDist(int titleLocY, int maxDensTxtLocY, double maxDensity,
	Histogram* hist)
{
	if (DISTRIBUTION == "Normal") {
		normalDistTxt(titleLocY);
		drawNormDist(maxDensTxtLocY, maxDensity, hist);
	}
	else {
		expDistTxt(titleLocY);
		drawExpoDist(titleLocY, maxDensTxtLocY, maxDensity, hist);
	}
}

void display(void)
{
	int titleLocY = HEIGHT - BORDER - 15;
	int maxDensTxtLocY = HEIGHT - BORDER- GAP - 15;
	double* bins;
	/// intialize it to something to possible unintialized memory.
	Histogram * hist = normHist; 
	/// clear all pixels  
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(1.0, 1.0, 1.0);
	
	drawXY(maxDensTxtLocY);

	if (FILE_NAME == "normal.dat") 		hist = normHist;
	else if (FILE_NAME == "expo.dat")	hist = expoHist;
	else if (FILE_NAME == "9.dat")		hist = fNmHist;
	else if (FILE_NAME == "20.dat")		hist = lstNmHist;

	bins = hist->getBins(INTERVALS);

	setupText(titleLocY, maxDensTxtLocY, hist);

	double maxDensity = hist->getMaxDensity(INTERVALS);

	drawHistogram(maxDensity, maxDensTxtLocY, hist, bins);

	drawDist(titleLocY, maxDensTxtLocY, maxDensity, hist);
	
	glFlush();

}

/**
* Init opengl for drawing.
*/
void init(void)
{
	/* select clearing color 	*/
	glClearColor(0.0, 0.0, 0.0, 0.0);

	/* initialize viewing values  */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();	
}

/**
 * Reshape function.
 * 
 * \param w	- Window width
 * \param h - Window Height
 */
void myReshape(int w, int h)
{
	WIDTH = w;
	HEIGHT = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);	
	glLoadIdentity();

	gluOrtho2D(0, w, 0, h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutPostRedisplay();
}

/**
 * Handles menu option selection.
 * 
 * \param option - Selection from menu.
 */
void progMenu(int option)
{
	switch (option) {
	case 'norm':
		FILE_NAME = "normal.dat";
		glutPostRedisplay();
		break;
	case 'expo':
		FILE_NAME = "expo.dat";
		glutPostRedisplay();
		break;
	case 'r':
		FILE_NAME = "9.dat";
		glutPostRedisplay();
		break;
	case 's':
		FILE_NAME = "20.dat";
		glutPostRedisplay();
		break;
	case 'n':
		DISTRIBUTION = "Normal";
		glutPostRedisplay();
		break;
	case 'e': 
		DISTRIBUTION = "Exponential";
		glutPostRedisplay();
		break;
	case '3': 
		INTERVALS = 30;
		glutPostRedisplay();
		break;
	case '4':
		INTERVALS = 40; 
		glutPostRedisplay();
		break;
	case '5': 
		INTERVALS = 50;
		glutPostRedisplay();
		break;
	case 's1':
		STEP = .01;
		glutPostRedisplay();
		break;
	case 's2':
		STEP = .02;
		glutPostRedisplay();
		break;
	case 's5':
		STEP = .05;
		glutPostRedisplay();
		break;
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

/**
 * Handle keyboard input.
 * 
 * \param key	- In the inputed key.
 * \param x		- Unused but expected by glut.
 * \param y		- Unused but expected by glut
 */
void keyboard(int key, int x, int y) {
	switch (key)
	{
	case GLUT_KEY_UP:
		if (DISTRIBUTION == "Normal" && (SIGMA + STEP) <= 2.99)
			SIGMA += STEP;
		else
		{
			if ((LAMBDA + STEP) <= 5.99)
				LAMBDA += STEP;
			else
				LAMBDA = 5.99;
		}
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		if (DISTRIBUTION == "Normal")
			if ((SIGMA - STEP) > .02)
				SIGMA -= STEP;
			else SIGMA = .03;
		else
			if ((LAMBDA - STEP) >= .2)
				LAMBDA -= STEP;
			else LAMBDA = .1;
		glutPostRedisplay();
		break;
	case GLUT_KEY_LEFT:
		if (DISTRIBUTION == "Normal")
			if ((MU - STEP) >= 0)
				MU -= STEP;
			else
				MU = 0;
		glutPostRedisplay();
		break;
	case GLUT_KEY_RIGHT:
		if (DISTRIBUTION == "Normal" && (MU + STEP) <= 4.99)
			MU += STEP;
		else MU = 4.99;
		glutPostRedisplay();
		break;
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
	glutAddMenuEntry("normal.dat", 'norm');
	glutAddMenuEntry("expo.dat", 'expo');
	glutAddMenuEntry("r - 9.dat", 'r');
	glutAddMenuEntry("s - 20.dat", 's');

	// Default should start in normal distribution. 
	int distMenu = glutCreateMenu(progMenu);
	glutAddMenuEntry("Normal", 'n');
	glutAddMenuEntry("Exponential", 'e');
	
	int histMenu = glutCreateMenu(progMenu);
	glutAddMenuEntry("30", '3');
	glutAddMenuEntry("40", '4');
	glutAddMenuEntry("50", '5');

	
	int paramStep = glutCreateMenu(progMenu);
	glutAddMenuEntry("0.01", 's1');
	glutAddMenuEntry("0.02", 's2');
	glutAddMenuEntry("0.05", 's5');


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
	glutSpecialFunc(keyboard);
	glutMainLoop();
	return 0;   
}
