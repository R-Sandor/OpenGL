#pragma once
#include <string>
#include <gl/glut.h>
#include <fstream>
#include <iostream>
#include <stdarg.h>


using namespace std;

void printString(GLuint x, GLuint y, GLvoid* font_style, string str);

/**
 * Check and open all the files the program needs will open. 
 * 
 * \param norm - normal.dat ifstream
 * \param expo - expo.dat ifstream
 * \param fist - first name file ifstream.
 * \param last - last name file ifstream
 */
void openFiles(ifstream *norm, ifstream *expo, ifstream *first, ifstream *last);

void merge(double input[], int lft, int mid, int rt);
void mergeSort(double input[], int lft, int rt);

/**
 * Draws a string on screen.
 *
 * \param x         - x cordinate
 * \param y         - y cordinate
 * \param text    - string to be formated
 * \param ...       - vargs aditional formating information
 * Used code from text book.
 * Works Cited: Nate Robin OpenGL 1.4 Source code
 */
void drawstr(GLuint x, GLuint y, string text, ...);
