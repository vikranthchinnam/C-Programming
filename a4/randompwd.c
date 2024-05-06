#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>


char getDigit(){
	int digit = rand() % 10;
	char result = digit + 48;
	return result;
}

char getSpecial(){
	char special[] = {'!', '@', '#', '$', '%', '^', '&', '*', '+', ':', ';'};
	int random = rand() % 11;

	return special[random];

}

char getLower(){
	int random = (rand() % 26) + 97;
	char result = random;
	return result;
}

char getUpper(){
	int random = (rand() % 26) + 65;
	char result = random;
	return result;
}
int main(int argc, char* argv[]){
	int minLen = atoi(argv[1]);
	int maxLen = atoi(argv[2]);
	int minLower = atoi(argv[3]);
	int minUpper = atoi(argv[4]);
	int minDigits = atoi(argv[5]);
	int minSpecial = atoi(argv[6]);

	char password[100];
		
	srand(time(NULL) + getpid());
	maxLen = minLen + (rand() % (maxLen - minLen + 1));
	for(int i = 0; i < maxLen; i++){
		
		int weightedTotal = minLower + minUpper + minDigits + minSpecial;
		if(weightedTotal == 0){
				int temp = rand() % 4;
				switch(temp){
					case 0:
						password[i] = getLower();
						break;
					case 1: 
						password[i] = getUpper();
						break;
					case 2: 
						password[i] = getDigit();
						break;
					case 3: 
						password[i] = getSpecial();
						break;
				}
				continue;
		}
		int random = rand() % weightedTotal;
		if( random < minLower){
			password[i] = getLower();
			minLower--;
		}
		else if(random < minLower + minUpper){
			password[i] = getUpper();
			minUpper--;
		}
		else if(random < minLower + minUpper + minDigits){
			password[i] = getDigit();
			minDigits--;
		}
		else{
			password[i] = getSpecial();
			minSpecial--;
		}
		minLen--;
	}
	printf("%s\n", password);
}
