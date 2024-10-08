/*
 * File:   tonn0030_lab6_bufferLib_v001.c
 * Author: ntonn
 *
 * Created on February 12, 2024, 12:48 AM
 */
#include "xc.h"
#include "tonn0030_lab6_bufferLib_v001.h"
#include "string.h"
#define ARRAY_SIZE 1024

int buffer[ARRAY_SIZE];
unsigned int currentPos = 0;
unsigned int numElems = 0;
unsigned int bufferSize;
char looped = 0;

/**
 * putVal adds a new value to the buffer, then updates the moving average.
 * @param newValue the value to be added to the front of the buffer.
 */
void putVal(int newValue)
{
    buffer[currentPos] = newValue;
    currentPos++;
    if(currentPos == ARRAY_SIZE)
    {
        currentPos = 0;
        looped = 1;
    }
    if(currentPos >= bufferSize){
        looped = 0;
    }
}

/**
 * The getAvg function just returns the continuously updating average rounded
 * to the nearest integer.
 * @return An integer corresponding to the average of the last BUFFER_SIZE elements.
 */
int getAvg(void)
{
    int sum = 0;
    if(looped == 1)
    {
        for(int i = 0; i < currentPos; i++)
        {
            sum += buffer[i];
        }
        for(int i = ARRAY_SIZE - bufferSize + currentPos - 1; i < ARRAY_SIZE; i++)
        {
            sum += buffer[i];
        }
    }
    else if(looped == 0 && currentPos < bufferSize)
    {
        for(int i = 0; i < currentPos; i++)
        {
            sum += buffer[i];
        }
    }
    else
    {
        for(int i = currentPos - bufferSize; i < currentPos; i++)
        {
            sum += buffer[i];
        }
    }
    
    return sum/bufferSize;
}

/**
 * Initializes the buffer to all 0s, also decides on the size of the moving-average
 * buffer.
 * @param buffer_size the amount of data points to be averaged.
 */
void initBuffer()
{
    bufferSize = 6;
    for(int i = 0; i < ARRAY_SIZE; i++)
    {
        buffer[i] = 0;
    }
}