#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXLEN 1000000
char input[MAXLEN];

int main() {
	scanf("%s", input);

	//CODE HERE! 
	int len = strlen(input);
	int result = 0;
	for(int i = 1; i < len; i++){
		if(input[i-1] == '(' && input[i] == '('){
			for(int j = i; j < len; j++){
				if(input[j-1] == ')' && input[j] == ')'){
					result++;
				}
			}		
		}
	}
	printf("%d", result);
}
