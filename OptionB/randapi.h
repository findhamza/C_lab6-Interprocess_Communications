/*	in file randapi.h
	Defines a wrapper for family of random number generators
	utilizing the GNU/Linux random number library for float
	and integer data types.  The float type is used to
	support generation of the exponential distribution
	using a famous IBM approximation.

	Function prototype definitions (function signatures) follow.
*/

#ifndef __RAND_API_H
#define __RAND_API_H

/* generate seed from clock */
extern void seedRandGenerator(  );

/*  0.0 <= random float < 1.0  */
extern float getRandFloat(  );

/*  0 thru (max - 1)  */
extern int getRandInteger( int max );

/*  exponential interarrival time, multiply by mean */
extern float getRandExponential( );

#endif /* __RAND_API_H */
