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
		int points				= 0;

		// standard deviation for data set.
		double stdDev			= 0.0;
		double variance			= 0.0;

		// expected value from data set.
		double expectedValue	= 0.0;

		// Read in data set for which the histogram belongs.
		double* dataSet;

		// Calculated bins. 
		double bins30[30] = {0};
		double bins40[40] = {0};
		double bins50[50] = {0};

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
		 * \param bin		- array of doubles
		 * \param sizeOfBin	- number of elements in array.
		 * \param range		- range of the data.
		 */
		void calculateBins(double* bin, int sizeOfBin, double range);

		/**
		 * Returns the max density..
		 * 
		 * \param bins	- Number of bins. Used to determine which 
		 *				  data set to return the max density from.
		 * \return The maximum density based on the number of bins.
		 */
		double getMaxDensity(int bins);

		/**
		 * Returns the smallest value from data set.
		 * 
		 * \return Minimum point from data set.
		 */
		double getMin();

		/**
		 * Get the maximum point from the data set.
		 * 
		 * \return Maximum point from data set. 
		 */
		double getMax();

		/**
		 * Get the range of the data set.
		 * 
		 * \return Range
		 */
		double getRange();

		/**
		 * Get bin30 array.
		 * 
		 * \return bins30.
		 */
		double* getBins30();

		/**
		 * Get bin40 array.
		 * 
		 * \return bins40.
		 */
		double* getBins40();

		/**
		 * Get bin50 array.
		 * 
		 * \return bins50.
		 */
		double* getBins50();

		/**
		 * Wrapper funtion that gets the right
		 * bins based on the provided interval.
		 * 
		 * \param interval - the number of bins.
		 * \return		     The bins to the number of intervals.
		 *                   that is if the interval is 30, then 
		 *					 bins30 is returned.
		 */
		double* getBins(int interval);

		/**
		 * Returns the number of points from data set for 
		 * a particular histogram.
		 * 
		 * \return Number of points.
		 */
		int getPoints();

		/**
		 * Gets the width based on the number of intervals.
		 * The width is the range / number of bins.
		 * 
		 * \param binSize	- number of bins;
		 * \return			  Range / (Number of bins)
		 */
		double getWidth(int binSize);

		/**
		 * Get the standard deviation for a data set.
		 * 
		 * \return Standard deviation.
		 */
		double getStdDev();

		/**
		 * Get the expected/MU value.
		 * 
		 * \return Mu.
		 */
		double getMu();
};

