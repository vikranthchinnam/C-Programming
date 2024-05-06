#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXLEN 1000000
char input[MAXLEN];

int main() {
	scanf("%s", input);

	//CODE HERE!
	int len = strlen(input);
	int hindLegs = 0;
	int result = 0;
	for(int i = 1; i < len; i++){
		if(input[i-1] == '(' && input[i] == '('){
			hindLegs++;
		}
		else if(input[i-1] == ')' && input[i] == ')'){
			result = result + hindLegs; 
		}
	}
	printf("%d", result);
}
