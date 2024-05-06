#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int main(){
	char string1[100];
	char string2[100];

	fgets(string1, 100, stdin);
	fgets(string2, 100, stdin);
	for(int i = 0; string1[i]; i++){
		if(string1[i] == ' '){
			for(int j = i; string1[j]; j++){
				string1[j] = string1[j+1];
			}
			i--;
		}
		string1[i] = tolower(string1[i]);

	}


	for(int i = 0; string2[i]; i++){
		if(string2[i] == ' '){
			for(int j = i; string2[j]; j++){
				string2[j] = string2[j+1];

			}
			i--;	
		}
		string2[i] = tolower(string2[i]);

	}

	int result = strcmp(string1, string2);

	if(result == 0){
		printf("Both strings are same!");
	}
	else{
		printf("Both strings are different!");
	}

	return 0;
}
