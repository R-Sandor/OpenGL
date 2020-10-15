#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include "histogram.h"

/**
 * Setups up the histogram.
 * 
 * \param data - data
 */
Histogram::Histogram(ifstream* data)
{
    string tmp; // temporary string to hold value read in.
    getline(*data, tmp);
    // Get the size of the exponential data set.
    int size = stoi(tmp, nullptr, 10);

    // Set th number of points in histogram.
    points = size;

    double dataPt = 0.0;
    double sum = 0.0;
    
    dataSet = new double[points];

    for (int i = 0; i < points; i++)
    {
        getline(*data, tmp);
        dataPt = stod(tmp, nullptr);
        dataSet[i] = dataPt;
        sum += dataPt;
    }

    // expected value
    double ev = sum / points;
    cout << "Expected Value: " << ev << endl;

    double stdDev = 0.0;
    double sum2 =0.0;
    for (int i = 0; i < points; i++)
    {
        double k =(double)dataSet[i] - ev;
        double prod = pow(k, 2.0);
        sum2 = sum2 + prod;
    }
    double variance = (double) sum2/ points;
    stdDev = sqrt(variance);
    cout << "varaiance " << variance << endl;
    cout << "std Dev " << stdDev << endl;

     //actuall mergeSort(dataSet, 0, points - 1);
     mergeSort(dataSet, 0, points - 1);
    // Get min/max
    min = dataSet[0];
    // actual max = dataSet[points - 1];
    max = dataSet[points-1];
    range = max - min;
    cout << "range " << range << endl;
    cout << "min " << min << "max " << max << endl;

    // pre calculate the bins before we need them
    calculateBins(bins30, 29, range);
    calculateBins(bins40, 39, range);
    calculateBins(bins50, 49, range);

}

/**
 * Finds the min and max value from data set.
 * 
 * \param data	- data file.
 * \param size	- size of data set.
 * \param min	- min value of data set
 * \param max	- max value of data set
 */
void Histogram::findMinMax(ifstream* data, int size, double &min, double &max)
{
    string tmp = "";
    double newNum = 0.0;
    for (int i = 0; i < size; i++)
    {
        getline(*data, tmp);
        newNum = stod(tmp, nullptr);

        if (newNum < min)
            min = newNum;
        else if (newNum > max)
            max = newNum;
    }
}

void Histogram::calculateBins(double* bin, int sizeOfBins, double range)
{

    double width = range / ((double)sizeOfBins + 1);

    int binIndex = 0;
    double boundary = min + width;
    double test = 0.0;
    for (int i = 0; i < points; i++)
    {
        while (dataSet[i] > boundary && binIndex < (sizeOfBins))
        {
            boundary = boundary + width;
            binIndex++;
        }

        if (dataSet[i] <= boundary)
        {
            bin[binIndex] = bin[binIndex] + 1;
        }
        else if (binIndex == sizeOfBins)
        {
            bin[binIndex] = bin[binIndex] + 1;
        }
    }

    //cout << " boundary" << boundary << endl;
    //cout << "min " << min << endl; 
    //cout << "max " << max << endl;
    //cout << "points " << points << endl;

    int selected; 
    if (sizeOfBins + 1 == 30) { selected = 0; }
    else if (sizeOfBins + 1 == 40) { selected = 1;}
    else { selected = 2; }

   // Calc Max density;
    for (int x = 0; x < sizeOfBins + 1; x++) {
        double binDesnsity = (double)((bin[x] / width) / points);
        if (binDesnsity > maxDensity[selected])
            maxDensity[selected] = binDesnsity;
        bin[x] = binDesnsity;
    }
}

double Histogram::getMaxDensity(int bins) {
    if (bins == 30) {
        return maxDensity[0];
    }
    else if (bins == 40) {
        return maxDensity[1];
    }
    else {
        return maxDensity[2];
    }
}

double Histogram::getMin()
{
    return min;
}

double Histogram::getMax()
{
    return max;
}

double * Histogram::getBins30() {
    return bins30;
}

double* Histogram::getBins40() {
    return bins40;
}

double* Histogram::getBins50() {
    return bins50;
}

int Histogram::getPoints() {
    return points;
}

double Histogram::getWidth(int binSize) {
   return (double) range / binSize;
}

