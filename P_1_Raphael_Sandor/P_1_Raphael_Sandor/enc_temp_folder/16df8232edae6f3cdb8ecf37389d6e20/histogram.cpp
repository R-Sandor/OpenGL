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
    //  cout << "done calc" << endl;
    //calculateBins(data, bins50, 50, range);

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

/**
 * Handles the data for each bin of the histogram.
 * 
 * \param bin	- array of doubles
 * \sizeOfBin	- number of elements in array.
 * \param range	- range of the data.
 */
/*
void Histogram::calculateBins(double *bin, int sizeOfBins, double range)
{
    int bktIdx = 0;
    double width = range / ((double)sizeOfBins + 1 );
    cout << "width  " << width << endl;
    double bucket;
    double test = 0.0;

    for (int i = 0; i < points; i++)
    {
        double pt = dataSet[i];
        bucket = min + (double)(width * bktIdx);

        if ( pt >=  bucket && pt < bucket + width) 
        {
            bin[bktIdx] = bin[bktIdx] + 1;
        }
        else
        {
            while (pt > bucket && pt >= bucket + width)
            {
                bucket = bucket + width;
                bktIdx++;
            }
            bin[bktIdx] = bin[bktIdx] + 1;
        }
       
    }
    
    // recalc density;
    //cout << " boundary" << boundary << endl;
    //cout << "min " << min << endl; 
    //cout << "max " << max << endl;
    //cout << "points " << points << endl;
    for (int x = 0; x < sizeOfBins+1; x++) {
       // test = test + bin[x];
       cout << x << " " << min+(width*x) << " " <<  bin[x] <<endl;
    }   
}*/


void Histogram::calculateBins(double* bin, int sizeOfBins, double range)
{

    double width = range / ((double)sizeOfBins + 1);
    cout << "width  " << width << endl;

    int binIndex = 0;
    double boundary = min + width;
    double test = 0.0;
    for (int i = 0; i < points; i++)
    {
        while (dataSet[i] > boundary && binIndex < (sizeOfBins))
        {
            boundary = boundary + width;
            binIndex++;
            // cout << "Data " << dataSet[i] << " boundary " << boundary << endl;;

        }
        // cout << "binIndex " << binIndex << endl;

        if (dataSet[i] <= boundary)
        {
            //cout << "HERE" << endl;
            bin[binIndex] = bin[binIndex] + 1;

        }
        else if (binIndex == sizeOfBins)
        {
            cout << "HERE2" << endl;
            bin[binIndex] = bin[binIndex] + 1;

        }
    }

    // recalc density;
    //cout << " boundary" << boundary << endl;
    //cout << "min " << min << endl; 
    //cout << "max " << max << endl;
    //cout << "points " << points << endl;
    for (int x = 0; x < sizeOfBins + 1; x++) {
        // test = test + bin[x];
         cout << x << " " << min+(width*x) <<  " " <<  bin[x] << " " << (bin[x]/width)/points <<endl;
    }
}