#include "utility.h"

/* 
 * Borrowed from OpenGL 1.4
 * Cite: Nate Robins
 */


using namespace std;
void printString(GLuint x, GLuint y, GLvoid* font_style, string str)
{
    glRasterPos2i(x, y);
	for (int i = 0; i < str.length(); i++)
		glutBitmapCharacter(font_style, str[i]);
}


/**  
 * Draws a string on screen.
 * 
 * \param x         - x cordinate
 * \param y         - y cordinate
 * \param format    - string to be displayed
 * \param ...       - vargs aditional formating information
 * Used code from text book.
 * Works Cited: Nate Robin OpenGL 1.4 Source code
 */
void 
drawstr(GLuint x, GLuint y, GLvoid *font_style, string text, ...)
{
    va_list args;
    char buffer[255];

    //va_start(args, text);
   // vsprintf_s(buffer, text, args);
   // va_end(args);
    
    glRasterPos2i(x, y);
    for (int i = 0; text.length()-1; i++)
        glutBitmapCharacter(font_style, text[i]);
}



/**
 * Opens and checks files. 
 * 
 * \param norm	- normal data set.
 * \param expo	- exponential data set.
 * \param first	- first name data set.
 * \param last	- last name data set.
 */
void openFiles(ifstream *norm, ifstream *expo, ifstream *first, ifstream *last) 
{
	// The first file number = Your First Name Initial % 10 + 1
	// R - 18th position in alphabet
	int r = 18 % 10 + 1;

	//The second file number = Your Last Name Initial % 10 + 11
	// S - 19th position in alphabet
	int s = 19 % 10 + 11;

	norm->open(".\\data\\normal.dat");
	expo->open(".\\data\\expo.dat");
	first->open(".\\data\\" + to_string(r) + ".dat");
	last->open(".\\data\\" + to_string(s) + ".dat");

	// Check if files are open. Exit with an error if files are not present.
	if ( !(norm->is_open() && expo->is_open() && first->is_open() && last->is_open() ) )
	{
		cout << "Data error. Check the project folder for the data directory.\n";
		cout << "expo.dat and normal.dat required\n";

		char tmp[1];
		cin.getline(tmp, 1);

		exit(1);
	}
}


/*
*/
void merge(double input[], int lft, int mid, int rt)
{
    int i, j, k;
    int lftIndex = mid - lft + 1;
    int rtIndex = rt - mid;

    /* create temp arrays */
    double* lftArray = new double[lftIndex];
    double* rtArray = new double[rtIndex];

    /* Copy the data from left/right arrays */
    for (i = 0; i < lftIndex; i++)
        lftArray[i] = input[lft + i];
    for (j = 0; j < rtIndex; j++)
        rtArray[j] = input[mid + 1 + j];

    /* Merge back temp arrays*/
    i = 0; // Initial index of first subarray 
    j = 0; // Initial index of second subarray 
    k = lft; // Initial index of merged subarray 
    while (i < lftIndex && j < rtIndex)
    {
        if (lftArray[i] <= rtArray[j])
        {
            input[k] = lftArray[i];
            i++;
        }
        else
        {
            input[k] = rtArray[j];
            j++;
        }
        k++;
    }

    /*
    * Handle if there are any remain elements that need to be added to the end.
    */
    while (i < lftIndex)
    {
        input[k] = lftArray[i];
        i++;
        k++;
    }
    while (j < rtIndex)
    {
        input[k] = rtArray[j];
        j++;
        k++;
    }

    // clean up arrays
    delete[]  lftArray, rtArray;
}

/**
 * .
 *
 * \param input
 * \param lft
 * \param rt
 */
void mergeSort(double input[], int lft, int rt)
{

    if (lft < rt)
    {
        int m = (lft + rt)/ 2;

        // Divide and conquer. 
        mergeSort(input, lft, m);
        mergeSort(input, m + 1, rt);

        merge(input, lft, m, rt);
    }
}