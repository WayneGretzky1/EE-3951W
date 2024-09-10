#include "bye00035_circularBuffer_v001.h"

#define BUFSIZE 128
#define NUMSAMPLES 128

int adc_buffer[BUFSIZE];
int buffer_index = 0;

/* Set all buffer entries to 0 */
void initBuffer()
{
    for (int i=0; i < BUFSIZE; i++) {
        adc_buffer[i] = 0;
    }
}



void putVal(int ADCvalue)
{
    adc_buffer[buffer_index++] = ADCvalue;
    if (buffer_index >= BUFSIZE) {
        buffer_index = 0;
    }
}


unsigned int getAvg() 
{
    unsigned long int sum = 0;
    for (int i=0; i < NUMSAMPLES - 1; i++) {
        sum += adc_buffer[i];
    }
    
    return sum/NUMSAMPLES;

}