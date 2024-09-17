/*
 * File:   tonn0030_lab6_bufferLib_v001.c
 * Author: ntonn
 *
 * Created on February 12, 2024, 12:48 AM
 */
#include "xc.h"
#include "tonn0030_lab6_bufferLib_v001.h"
#define ARRAY_SIZE 1024

int buffer[ARRAY_SIZE];
unsigned int currentPos = 0;
unsigned int numElems = 0;
unsigned int bufferSize;
double avg = 0;

/**
 * putVal adds a new value to the buffer, then updates the moving average.
 * @param newValue the value to be added to the front of the buffer.
 */
void putVal(int newValue)
{
    buffer[currentPos] = newValue;
    currentPos++;
    if(numElems < bufferSize)
    {
        numElems++;
        avg = avg * ((double)(numElems-1)/numElems);
        avg += (double)(newValue)/numElems;
    }
    else
    {
        avg += (double)(newValue)/bufferSize;
        unsigned int tempIndex = currentPos - 1 - bufferSize;
        if(tempIndex <0)
        {
            tempIndex += ARRAY_SIZE;
        }
        avg -= (double)(buffer[tempIndex])/bufferSize;
    }
    if(currentPos >= ARRAY_SIZE)
    {
        currentPos = 0;
    }
}

/**
 * The getAvg function just returns the continuously updating average rounded
 * to the nearest integer.
 * @return An integer corresponding to the average of the last BUFFER_SIZE elements.
 */
int getAvg(void)
{
    return (int)(avg + 0.5);
}

/**
 * Initializes the buffer to all 0s, also decides on the size of the moving-average
 * buffer.
 * @param buffer_size the amount of data points to be averaged.
 */
void initBuffer(unsigned int buffer_size)
{
    bufferSize = buffer_size;
    for(int i = 0; i < ARRAY_SIZE; i++)
    {
        buffer[i] = 0;
    }
}