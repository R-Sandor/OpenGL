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
    expectedValue = sum / points;

    stdDev = 0.0;
    double sum2 =0.0;
    for (int i = 0; i < points; i++)
    {
        double k =(double)dataSet[i] - expectedValue;
        double prod = pow(k, 2.0);
        sum2 = sum2 + prod;
    }
    variance = (double) sum2/ points;
    stdDev = sqrt(variance);

    //actuall mergeSort(dataSet, 0, points - 1);
    mergeSort(dataSet, 0, points - 1);
    
    // Get min/max
    min = dataSet[0];
    
    // actual max = dataSet[points - 1];
    max = dataSet[points-1];
    range = max - min;

    // pre calculate the bins before we need them
    calculateBins(bins30, 29, range);
    calculateBins(bins40, 39, range);
    calculateBins(bins50, 49, range);

}

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
    /// the width of each bin
    double width = range / ((double)sizeOfBins + 1);

    int binIndex = 0;
    /// boundary current point which at start is the smallest point
    /// to the begginning of next interval/bin.
    double boundary = min + width;
    for (int i = 0; i < points; i++)
    {
        while (dataSet[i] > boundary && binIndex < sizeOfBins)
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

    /// Selected picks which bin size we are calculating maxDensity for,
    /// after which, we know which bins to save our calculation.
    /// i.e. we will know what is the maxDensity 
    /// for bins30, bins40, or bins50.
    int selected; 
    if (sizeOfBins + 1 == 30) { selected = 0; }
    else if (sizeOfBins + 1 == 40) { selected = 1;}
    else { selected = 2; }

    /// Calc Max density, also save the density of each bin
    /// in its respective spot
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

double* Histogram::getBins(int interval) {

    if (interval == 30)
       return getBins30();
    else if (interval == 40)
       return getBins40();
    else
       return getBins50();
}

int Histogram::getPoints() {
    return points;
}

double Histogram::getWidth(int binSize) {
   return (double) range / binSize;
}

double Histogram::getStdDev() {
    return stdDev;
}

double Histogram::getMu() {
    return expectedValue;
}

double Histogram::getRange() {
    return range;
}