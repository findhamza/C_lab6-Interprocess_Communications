/*
	Random Functions API Wrapper in file randapi.c

	extern float getRandFloat(  );   returns random floating point 0 <= rand < 1.0.
	extern getRandInteger(  max );    returns random integer between 0 and (max - 1)
	extern float getRandExponential(  ); returns random exponential 
	      inter-arrival time, multiply by the mean to obtain the actual interval.

	Must seed first using extern void seedGenerator( void );
	in file seedRandGererator.c.
	Prototypes in randapi.h

	All “C” compilers provide a random number generator providing random integers
	In the range 0 =< rand( ) < RAND_MAX where RAND_MAX is compiler/hardware
	 dependent.  The quality of the deviates is a topic of constant debate.  “rand( )”
	is uniformly distributed.  This functionality is provided in stdlib.h.  srand(  ) may be
	used to seed the generator.  If the seed is not changed/set, rand(  ) will always
	produce the same series (sequence)of random numbers - a pseudo random
	 number generator.
*/

/* generate random floating point */
#include <stdlib.h>

float getRandFloat( )    //  0 <= random deviate < 1
{					// “RAND_MAX” is largest integer
		float randDeviate;

		randDeviate = ((float)rand( ) / (float)RAND_MAX);
		return randDeviate;

		//return ((float)rand( ) / (float)RAND_MAX);
}

/* generate random integer from 0 thru (max - 1).  */

int getRandInteger( int max )
{
	int randDeviate;
	randDeviate = (int)((float)max * rand( ) / 
			(RAND_MAX+1.0));  //force float division
	return randDeviate;
}
/* Assume max = 5, Rand_Max =100.  If Rn = 17 => 17*5/101 = 0.84 = 0; if Rn = 25 => 25*5/101 = 1.237 = 1; if Rn = 100 => 100*5/101 = 4.95 = 4 */

/* getExponential( );  returns exponential interarrival time.  Multiply by mean. */

float getRandExponential( )  //Interpolate between points on
{						//graph: lower bound + slope 
    float x, deviate;        //of line * distance on x axis.
						//Note more approximation
    x = getRandFloat( );		//points in exponential tail.

    if (x == 0.0)
      deviate = 0.0;
    else if (x <= 0.1)
      		deviate = ((x - 0.0) * 1.04 + 0.0);
    else if (x <= 0.2)
      		deviate = ((x - 0.1) * 1.18 + 0.104);
    else if (x <= 0.3)
      		deviate = ((x - 0.2) * 1.33 + 0.222);
    else if (x <= 0.4)
      		deviate = ((x - 0.3) * 1.54 + 0.355);
    else if (x <= 0.5)
      		deviate = ((x - 0.4) * 1.81 + 0.509);
    else if (x <= 0.6)
      		deviate = ((x - 0.5) * 2.25 + 0.690);
    else if (x <= 0.7)
      		deviate = ((x - 0.6) * 2.85 + 0.915);
    else if (x <= 0.75)
      		deviate =  ((x - 0.70) * 3.60 + 1.2);
    else if (x <= 0.8)
      		deviate =  ((x - 0.75) * 4.40 + 1.38);
    else if (x <= 0.84)
      		deviate =  ((x - 0.8) * 5.75 + 1.60);
    else if (x <= 0.88)
      		deviate =  ((x - 0.84) * 7.25 + 1.83);
    else if (x <= 0.9)
      		deviate =  ((x - 0.88) * 9.00 + 2.12);
    else if (x <= 0.92)
      		deviate =  ((x - 0.90) * 11.0 + 2.30);
    else if (x <= 0.94)
      		deviate =  ((x - 0.92) * 14.5 + 2.52);
    else if (x<= 0.95)
      		deviate =  ((x - 0.94) * 18.0 + 2.81);
    else if (x <= 0.96)
      	    deviate =  ((x - 0.95) * 21.0 + 2.99);
    else if (x <= 0.97)
      		deviate =  ((x - 0.96) * 30.0 + 3.20);
    else if (x <= 0.98)
      		deviate =  ((x - 0.97) * 40.0 + 3.50);
    else if (x <= 0.99)
      		deviate =  ((x - 0.98) * 70.0 + 3.90);
    else if (x <= 0.995)
      		deviate =  ((x - 0.99) * 140.0 + 4.60);
    else if (x <= 0.998)
      		deviate =  ((x - 0.995) * 300.0 + 5.30);
    else if (x <= 0.999)
    	  	deviate =  ((x - 0.998) * 800.0 + 6.20);
    else
      		deviate =  ((x - 0.9997) * 1000.0 + 8.0);

    return (float)deviate;
}
