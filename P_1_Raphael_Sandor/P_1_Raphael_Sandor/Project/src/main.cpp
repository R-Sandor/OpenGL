/*
 * Copyright (c) 1993-2003, Silicon Graphics, Inc.
 * All Rights Reserved
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose and without fee is hereby granted, provided that the above
 * copyright notice appear in all copies and that both the copyright
 * notice and this permission notice appear in supporting documentation,
 * and that the name of Silicon Graphics, Inc. not be used in
 * advertising or publicity pertaining to distribution of the software
 * without specific, written prior permission.
 *
 * THE MATERIAL EMBODIED ON THIS SOFTWARE IS PROVIDED TO YOU "AS-IS" AND
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS, IMPLIED OR OTHERWISE,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY OR
 * FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL SILICON
 * GRAPHICS, INC.  BE LIABLE TO YOU OR ANYONE ELSE FOR ANY DIRECT,
 * SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY KIND,
 * OR ANY DAMAGES WHATSOEVER, INCLUDING WITHOUT LIMITATION, LOSS OF
 * PROFIT, LOSS OF USE, SAVINGS OR REVENUE, OR THE CLAIMS OF THIRD
 * PARTIES, WHETHER OR NOT SILICON GRAPHICS, INC.  HAS BEEN ADVISED OF
 * THE POSSIBILITY OF SUCH LOSS, HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE POSSESSION, USE
 * OR PERFORMANCE OF THIS SOFTWARE.
 *
 * US Government Users Restricted Rights
 * Use, duplication, or disclosure by the Government is subject to
 * restrictions set forth in FAR 52.227.19(c)(2) or subparagraph
 * (c)(1)(ii) of the Rights in Technical Data and Computer Software
 * clause at DFARS 252.227-7013 and/or in similar or successor clauses
 * in the FAR or the DOD or NASA FAR Supplement.  Unpublished - rights
 * reserved under the copyright laws of the United States.
 *
 * Contractor/manufacturer is:
 *	Silicon Graphics, Inc.
 *	1500 Crittenden Lane
 *	Mountain View, CA  94043
 *	United State of America
 *
 * OpenGL(R) is a registered trademark of Silicon Graphics, Inc.
 */

 /**
  * Author: Raphael Sandor
  * Date:	9/28/2020
  * 
  * This program will take input data and turn the input
  * data in to probability distribution function with a
  * histogram bar graph.
  */

#include <stdlib.h>
#include <gl/glew.h>
#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "utility.h"
#include "histogram.h"

using namespace std;
int static INTERVALS = 30;

void display(void)
{
	/* clear all pixels  */
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(-2.0, 0.25, 0.0);
	glVertex3f(0-.75, 0.25, 0.0);
	glVertex3f(0-.75, 0.75, 0.0);
	glVertex3f(0-.25, 0.75, 0.0);
	glEnd();

	glFlush();
}

void init(void)
{
	/* select clearing color 	*/
	glClearColor(0.0, 0.0, 0.0, 0.0);

	/* initialize viewing values  */
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();	
}

void myReshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-2.0, 2.0, -2.0 * (GLfloat)h / (GLfloat)w,
			2.0 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
	else
		glOrtho(-2.0 * (GLfloat)w / (GLfloat)h,
			2.0 * (GLfloat)w / (GLfloat)h, -2.0, 2.0, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}

void progMenu(int value)
{
	switch (value) {

	default:
		break;
	}
}

void progMenu2(int value)
{
	glutAddMenuEntry("Testing2", 30);
	glutAddMenuEntry("Testing3", 30);
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
	Histogram normHist(&normData);
	//Histogram expoHist(&expoData);
	//Histogram fNmHist(&fNmData); // first name data histogram
	//Histogram lstNmHist(&lstNmData); // last name


	
	// Bins are determined by the user the default intervals is 30.
	//normHist.divideIntoBins(&expoData)

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
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