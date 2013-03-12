#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <math.h>
int direction = 1;
int pinStep = 7;
int pinDirection = 0;

  
  
/**********NOTE*********/

float EIGHTH = 1;
float DOTTED_EIGHTH = 1.5;
float QUARTER = 2;
float DOTTED_QUARTER =3;
float HALF = 4;
float WHOLE = 8;
float ETERNITY =-1;

float A     = 14080;
float AS    = 14917.2;
float B     = 15804.3;
float C     = 16744;
float CS    = 17739.7;
float D     = 18794.5;
float DS    = 19912.1;
float E     = 21096.2;
float F     = 22350.6;
float FS    = 23679.6;
float G     = 25087.7;
float GS    = 26579.5;
float A2    = 28160;
float A2S   = 29834.5;
float B2    = 31608.5;
float C2    = 33488.1;
float C2S   = 35479.4;
float D2    = 37589.1;
float D2S   = 39824.3;
float E2    = 42192.3;
float F2    = 44701.2;
float F2S   = 47359.3;
float G2    = 50175.4;
float G2S   = 53159;
float A3    = 56320;
float AS3   = 59669;
float B3    = 63217;
float C3    = 66976.2;

float REST  = 0;


int cNumSongs = 7;
int position = 0;
