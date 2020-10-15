#pragma once
#include "utility.h"
/**
 * \class Histogram
 * \brief manages all the data of histograms.
 */
class Histogram
{
	private:

		// Min, Max, and Range of data points
		double min		= 100.0;
		double max		= -100.0;
		double range	= 0.00;
		// Each bins max density. 
		// maxDensity[0] is for bins30[]
		// maxDesnity[1] is for bins40[] etc.
		double maxDensity[3] = { 0 };
		// Number of points
		int points		= 0;
		// Read in data set for which the histogram belongs.
		double* dataSet;
		// Calculated bins. 
		double bins30[30] = {0};
		double bins40[40] = {0};
		double bins50[50] = {0};
		int bigest30, bigest40, bigest50 = 0;

	public:

		/**
		 * Constructor that intializes histograms.
		 * Loads the data, and calls functions that set up histograms.
		 * 
		 * \param data - ifstream to data file.
		 */
		Histogram(ifstream *data);

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
		 * Returns the max density..
		 * 
		 * \return the maximum density based on the number of bins.
		 */
		double getMaxDensity(int bins);

		double getMin();

		double getMax();

		double* getBins30();

		double* getBins40();

		double* getBins50();

		int getPoints();

		double getWidth(int binSize);

		
};

