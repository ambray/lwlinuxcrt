#include "lwclib.h"

static char* tmp = "Hello from main.\n";

int main()
{
	int i;
	write(1, tmp, strlen(tmp));
	return 0;
}