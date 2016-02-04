/*
 * File:   adc.c
 * Author: Harry
 *
 * This file holds functions to setup the adc peripheral for reading both the 
 * line tracking reflective sensors, and the battery voltage. 
 * 
 * Created on 31 January 2016, 21:24
 */

#include "adc.h"

/*
 * Initialises the ADC module for reading the 4 line-tracking reflective sensors.
 * The four ADC channels are sampled sequentially and the results stored in the 
 * ADC buffer ADC1BUF0 through ADC1BUF3.
 * 
 * The AD conversion interrupt must be enabled in the IEC0 register for this to 
 * function correctly. This will happen in the "interrupts" source files.
 * 
 * The sample/conversion process is started by the function ().
 */
void adc_linetrackinginit()
{
    // AD input scan select register
    AD1CSSL = 0x0F00;             // Include AN8,9,10,11 in scan
    
    // AD input select register
    AD1CHS = 0x0000;

    // AD control register 1
    AD1CON1bits.ADON = 0;         // Module is off. (Must set on to begin)
    AD1CON1bits.FORM = 0b00;      // Output in integer format.
    AD1CON1bits.SSRC = 0b111;     // Internal counter triggers conversion.
    AD1CON1bits.ASAM = 0;         // Set SAMP bit to start sampling. (Not used in operation)
    AD1CON1bits.SAMP = 0;         // 
    AD1CON1bits.DONE = 0;         // Conversion not done. (not yet started obv)
    
    // AD control register 2
    AD1CON2bits.VCFG = 0b000;     // AVDD and AVSS as voltage references.
    // May change this setting to vref+/- once resistor values are tuned.
    // AD1CON2bits.VCFG = 0b011;     // VREF+ and VREF- as voltage references.
    AD1CON2bits.CSCNA = 1;        // Scan inputs
    AD1CON2bits.BUFS = 0;         // Buffer fill status bit (invalid as BUFM = 0)
    AD1CON2bits.SMPI = 0b0011;    // Interrupts after every 4 samples
    AD1CON2bits.BUFM = 0;         // Buffer configured as one 16 word structure
    AD1CON2bits.ALTS = 0;         // Always use MUX A
    
    // AD Control Register 3
    AD1CON3bits.ADRC = 0;          // Use system clock
    AD1CON3bits.SAMC = 0b1100;     // Sample time = 12Tad
    AD1CON3bits.ADCS = 0b00000000; // Tad = Tcy
}

/*
 * Samples sequentially the 4 adc channels used to measure the reflective sensors for line 
 * tracking. Writes the result to a temporary unsigned int buffer register. 
 * The temporary buffer register passed as an argument should be of size 4.
 * The buffer should be int type (16 bits) as the ADC is 10 bit.
 */
void linetracking_sample(unsigned int *tempBuffer[3])
{
    int * ADC4Ptr = &ADC1BUF0;       // Initialise a pointer to the first adc buffer word;
    
    AD1CON1bits.ADON = 1;           // turn ADC on
    IFS0bits.AD1IF = 0;             // Clear AD interrupt flag
    AD1CON1bits.ASAM = 1;           // Auto-start sampling and conversion.
    while (!IFS0bits.AD1IF){};
    for (int count = 0; count < 4; count++)
    {
       tempBuffer(count) = *ADC4Ptr++;
    }
    AD1CON1bits.ADON = 0;           // turn ADC off
}

/*
 * Initialises the ADC module to sample the V_BATT_SENSE_ADC pin and read the 
 * battery voltage. The module will take a single sample and store it in the 
 * ADC1BUF0 register. 
 */
void adc_vbattinit()
{
    // AD input scan select register
    AD1CSSL = 0x0000;             // No channels in scan
    
    // AD input select register
    AD1CHS = 0x0000;

    // AD control register 1
    AD1CON1bits.ADON = 0;         // Module is off. (Must set on to begin)
    AD1CON1bits.FORM = 0b00;      // Output in integer format.
    AD1CON1bits.SSRC = 0b111;     // Internal counter triggers conversion.
    AD1CON1bits.ASAM = 0;         // Set SAMP bit to start sampling. (Not used in operation)
    AD1CON1bits.SAMP = 0;         // 
    AD1CON1bits.DONE = 0;         // Conversion not done. (not yet started obv)
    
    // AD control register 2
    AD1CON2bits.VCFG = 0b000;     // AVDD and AVSS as voltage references.
    // May change this setting to vref+/- once resistor values are tuned.
    // AD1CON2bits.VCFG = 0b011;     // VREF+ and VREF- as voltage references.
    AD1CON2bits.CSCNA = 0;        // Don't scan inputs
    AD1CON2bits.BUFS = 0;         // Buffer fill status bit (invalid as BUFM = 0)
    AD1CON2bits.SMPI = 0b0000;    // Interrupts after every 1 samples
    AD1CON2bits.BUFM = 0;         // Buffer configured as one 16 word structure
    AD1CON2bits.ALTS = 0;         // Always use MUX A
    
    // AD Control Register 3
    AD1CON3bits.ADRC = 0;          // Use system clock
    AD1CON3bits.SAMC = 0b1100;     // Sample time = 12Tad
    AD1CON3bits.ADCS = 0b00000000; // Tad = Tcy
}

/*
 * Samples the V_BATT_SENSE_ADC channel (AN15) and writes the value to the 
 * dereferenced pointer that is passed in.
 */
void vbatt_sample(int * sample_ptr)
{
    AD1CON1bits.ADON = 1;           // turn ADC on
    IFS0bits.AD1IF = 0;             // Clear AD interrupt flag
    AD1CON1bits.ASAM = 1;           // Auto-start sampling and conversion.
    while (!IFS0bits.AD1IF){};
    *sample_ptr = ADC1BUF0;         // Write the ADC1BUF0 value to the location 
                                    // pointed to by sample_ptr
    AD1CON1bits.ADON = 0;           // turn ADC off
}
