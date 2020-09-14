#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int global_var = 0;

int main(int argc, char const *argv[])
{
	vfork();
	int local_var = 0;

	global_var++;
	local_var++;

	printf("%i ", global_var);
	printf("%i ", local_var);

	printf("\n");

	return 0;
}