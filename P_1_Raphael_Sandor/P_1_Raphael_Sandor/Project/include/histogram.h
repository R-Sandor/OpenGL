#pragma once
#include "utility.h"
/**
 * \class Histogram
 * \brief manages all the data of histograms.
 */
class Histogram
{
	private:
		double min		= 100.0;
		double max		= -100.0;
		double range	= 0.00;
		int points		= 0;
		double* dataSet;
		double bins30[30] = {0};
		double bins40[40] = {0};
		double bins50[50] = {0};

	public:

		/**
		 * Loads the data.
		 * 
		 * \param data - ifstream to data file.
		 */
		Histogram::Histogram(ifstream *data);

		/**
		 * Finds min and max for data set.
		 * 
		 * \param data	-	data file.
		 * \param size	-	size of file
		 * \param min	-	minimum value of the data set
		 * \param max	-	maximum value of the data set
		 */
		void findMinMax(ifstream* data, int size, double &min, double &max);

		/**
		 * Calculate the bins of the histogram, number of points in each bin.
		 * Calculate the density of each bin.
		 * 
		 * \param data	- data file
		 * \param bin	- array of doubles
		 * \sizeOfBin	- number of elements in array.
		 * \param range	- range of the data.
		 */
		void calculateBins(double* bin, int sizeOfBin, double range);

		/**
		 * A divide and conquer algorithm to find which index to put the point.
		 * 
		 * \param bins
		 * \param dataPt
		 * \param size
		 * \return 
		 */
		int divideAndConquer(double * bins, double dataPt, int left, int right);
};

