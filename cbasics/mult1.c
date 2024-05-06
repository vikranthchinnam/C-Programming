#include <stdio.h>

int main(){
	int number;
	printf("Enter the number: ");
	scanf("%d", &number);
	for(int i = 1; i <= 10; i++){
		printf("%3d * %3d = %3d\n", i, number, i*number);
	} 
}
