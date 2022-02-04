#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{	
	//execlp("/Users/BigZozyo/Documents/Informatique/42_projets/fdf/fdf", 
	//	"/Users/BigZozyo/Documents/Informatique/42_projets/fdf/fdf", 
	//	"/Users/BigZozyo/Documents/Informatique/42_projets/fdf/fdf/test_maps/mars.fdf", 
	//	NULL); 
	
	execlp("fdf", 
		"fdf", 
		"/Users/BigZozyo/Documents/Informatique/42_projets/fdf/fdf/test_maps/mars.fdf", 
		NULL); 
	
	printf("Program finished executing\n");





	return (0);
}
