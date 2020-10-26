#pragma once
#include <string>
#include <gl/glut.h>
#include <fstream>
#include <iostream>
#include <stdarg.h>

using namespace std;

/**
 * Check and open all the files the program needs will open. 
 * 
 * \param norm - normal.dat ifstream
 * \param expo - expo.dat ifstream
 * \param first - First name file ifstream.
 * \param last - Last name file ifstream
 */
void openFiles(ifstream *norm, ifstream *expo, ifstream *first, ifstream *last);

/**
 * Merge part of the merge sort algorithm.
 * \param input	- Data set to sort.
 * \param lft	- Left side
 * \param mid	- middle point
 * \param rt	- Right side
 */
void merge(double input[], int lft, int mid, int rt);

/**
 * Merge sort algorithm.
 *
 * \param input	- Data set to sort.
 * \param lft	- Left side
 * \param rt	- Right side
 */
void mergeSort(double input[], int lft, int rt);

/**
 * Prints at a given x and y location.
 *
 * \param x				- X position.
 * \param y				- Y position.
 * \param font_style	- Font style.
 * \param str			- A temporary string of doubles to str.
 */
void printString(GLuint x, GLuint y, GLvoid* font_style, string str);

/**
 * Removes trailing 0s.
 *
 * \param str   - String input
 * \return      Formatted output
 */
string rmTrail0s(string str);