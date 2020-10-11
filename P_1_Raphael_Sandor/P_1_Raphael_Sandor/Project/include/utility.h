#pragma once
#include <string>
#include <gl/glut.h>
#include <fstream>
#include <iostream>

using namespace std;

void printString(string str);

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
