#include "adc.h"

unsigned int adcIRLeftDark;
unsigned int adcIRRightDark;
unsigned int adcIRFrontDark;

unsigned int adcIRLeft;
unsigned int adcIRRight;
unsigned int adcIRFront;

unsigned int adcUser;

//unsigned int adcSideCenterDistance;
//unsigned int adcFrontCenterDistance;

void ADC_Init(void)
{
	IR_Emitter_Off();
	
	SAR10_EnableInt(); // Enable SAR10 interrupt
	SAR10_Start();     // Power on SAR10 block
}

void ADC_Update(void)
{
	if (IR_Emitter_Powered)
	{
		// ------------ Read reflected light levels ------------
		
		SAR10_SetADCChannel(ADC_CHAN_IR_FRONT);
		SAR10_Trigger();                     // Trigger new sample
		while(SAR10_fIsDataAvailable()==0);  // Wait while data is not ready
		adcIRFront = SAR10_iGetData();       // Read result
		adcIRFront -= adcIRFrontDark;        // Correct reading for ambient lighting
		
		SAR10_SetADCChannel(ADC_CHAN_IR_LEFT);
		SAR10_Trigger();                     // Trigger new sample
		while(SAR10_fIsDataAvailable()==0);  // Wait while data is not ready
		adcIRLeft = SAR10_iGetData();        // Read result
		adcIRLeft -= adcIRLeftDark;          // Correct reading for ambient lighting
		
		SAR10_SetADCChannel(ADC_CHAN_IR_RIGHT);
		SAR10_Trigger();                     // Trigger new sample
		while(SAR10_fIsDataAvailable()==0);  // Wait while data is not ready
		adcIRRight = SAR10_iGetData();       // Read result
		adcIRRight -= adcIRRightDark;        // Correct reading for ambient lighting
		
		IR_Emitter_Off();
	}
	else
	{	
		//------------ Read ambient light levels ------------
		
		SAR10_SetADCChannel(ADC_CHAN_USER);
		SAR10_Trigger();                      // Trigger new sample
		while(SAR10_fIsDataAvailable()==0);   //Wait while data is not ready
		adcUser = SAR10_iGetData();           // Read result
	
		SAR10_SetADCChannel(ADC_CHAN_IR_FRONT);
		SAR10_Trigger();                      // Trigger new sample
		while(SAR10_fIsDataAvailable()==0);   //Wait while data is not ready
		adcIRFrontDark = SAR10_iGetData();    // Read result
		adcIRFrontDark += ADC_OFFSET_IR_FRONT;// Apply offset
		
		SAR10_SetADCChannel(ADC_CHAN_IR_LEFT);
		SAR10_Trigger();                      // Trigger new sample
		while(SAR10_fIsDataAvailable()==0);   //Wait while data is not ready
		adcIRLeftDark = SAR10_iGetData();     // Read result
		adcIRLeftDark += ADC_OFFSET_IR_LEFT;  // Apply offset
		
		SAR10_SetADCChannel(ADC_CHAN_IR_RIGHT);
		SAR10_Trigger();                      // Trigger new sample
		while(SAR10_fIsDataAvailable()==0);   //Wait while data is not ready
		adcIRRightDark = SAR10_iGetData();    // Read result
		adcIRRightDark += ADC_OFFSET_IR_RIGHT;// Apply offset
		
		IR_Emitter_On();
	}
}