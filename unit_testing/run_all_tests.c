#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <unistd.h>
#include "header.h"
#include "CuTest.h"

int main()
{
    run_all_tests();
}

void run_all_tests()
{
    CuString *output = CuStringNew();
    CuString *suite = CuSuiteNew();

    // tilføjer test suiter
    CuSuiteAddSuite(suite, (CuSuite *) print_comment_get_suite());

    CuSuiteRun(suite);
	CuSuiteSummary(suite, output);
	CuSuiteDetails(suite, output);
	printf("%s\n", output->buffer);
}