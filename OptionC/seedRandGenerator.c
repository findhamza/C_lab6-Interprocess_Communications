/*
	Initialize Random API using system clock.
	This is convenient but not cryptographically sound.
*/

#include <stdlib.h>
#include <time.h>

void seedRandGenerator( )
{
	time_t seed;  //The seed repeats every 60 seconds.

	seed = time( NULL );    // srand( time( NULL ) );
	srand( seed );
	return;
}
