#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "p2.h"

using namespace std;

int main(int argc, char *argv[])
{
    // We will calculate the 10, 50, and 90th percentile in several different ways to compare accuracy
    // p2_10, p2_50 and p2_90 will each be used to calculate a single percentile
	p2_t p2_10(0.1), p2_50(0.5), p2_90(0.9);
    // multi will be used to simultaneously calculate the 10, 50 and 90 percentiles
	p2_t multi;
    // equal will track all deciles (0%, 10%, 20% ... 90%, 100%)
    // densequal will track all multiples of 5% (0%, 5%, 10% ... 95%, 100%)
	p2_t equal, denseequal;
	FILE *fi;
	double d;
	char buf[30];

	multi.add_quantile(0.1);
	multi.add_quantile(0.5);
	multi.add_quantile(0.9);
	equal.add_equal_spacing(10);
	denseequal.add_equal_spacing(20);

	if( argc != 2 ) {
		cout << "No file specified" << endl;
		exit(1);
	}

	fi = fopen(argv[1], "r");

	if( fi == NULL ) {
		printf( "Failed to open %s\n", argv[1] );
		exit(1);
	}

    // Read data from a file, one value per line. Add it into each of the p2_t trackers
	while(!feof(fi) ) {
		fgets(buf, 30, fi);
		d = strtod(buf, NULL);

		p2_10.add( d );
		p2_50.add( d );
		p2_90.add( d );
		multi.add( d );
		equal.add( d );
		denseequal.add( d );
	}
	fclose(fi);

    // Print out the results from each of the trackers at the 10, 50 and 90 percentiles
	printf("%g %g %g\n", p2_10.result( ), p2_50.result( ), p2_90.result( ) );
	printf("%g %g %g\n", multi.result( 0.1 ), multi.result( 0.5 ), multi.result( 0.9 ) );
	printf("%g %g %g\n", equal.result( 0.1 ), equal.result( 0.5 ), equal.result( 0.9 ) );
	printf("%g %g %g\n", denseequal.result( 0.1 ), denseequal.result( 0.5 ), denseequal.result( 0.9 ) );
}
