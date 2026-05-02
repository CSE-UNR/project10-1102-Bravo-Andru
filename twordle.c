// Andru Bravo
// Project 10

#include <stdio.h>
#define BOARDLENGTH 9
#define GUESSCAP 6
#define STEPLENGTH 6
#define FILENAME "answer.txt"
int fileWordConverter(char answer[]);
void clearBoard(int guessCap, int board, char totalGuesses[][board], char step[], int steplength);
void showBoard(int guessCap, int board, char totalGuesses[][board]);
int checkGuessOverflow(char step[]);
int checkGuess(int guessCap, char step[], char answer[]);
void guessToTotal(int board, char totalGuesses[][board], char step[], int rowCont);
int winning(int rowCont, char answer[], int currentGuess);
int main(){
	char totalGuesses[GUESSCAP][BOARDLENGTH];
	char step[STEPLENGTH];
	char answer[STEPLENGTH];
	int rowCont = 0;
	_Bool Overflow = 0;
	int i;
	_Bool win = 0;
	int currentGuess;
	FILE* fileptr;
	fileptr = fopen(FILENAME, "r");
	if(fileptr == NULL){
		printf("Could not open file\n");
		return 0;
	}
	fscanf(fileptr, "%s", answer);
	fclose(fileptr);
	i = fileWordConverter(answer);
	if(i != 5){
		printf("The correct answer either does not properly abide by the proper character constraints, or contains non-letter characters. Please change the correct answer in the appropriate file.\n");
		return 0;
	}
	printf("A capital letter means it's correct and in the right spot\nA \"?\" means the letter is present but in the wrong spot\nAn unaffected letter means it's not present in the word\nGood luck!\n");
	clearBoard(GUESSCAP, BOARDLENGTH, totalGuesses, step, STEPLENGTH);
	showBoard(GUESSCAP, BOARDLENGTH, totalGuesses);
	for(currentGuess=0; currentGuess< GUESSCAP; currentGuess++){
		printf("GUESS %d\nWhat is your guess?\n", currentGuess+1);
		do{
			scanf("%s", step);
			Overflow = checkGuessOverflow(step);
			if(Overflow == 0){
				break;
			}
			else{
				printf("Invalid guess. Guess must be 5 characters long\n");
			}
		}while(Overflow != 0);
		win = checkGuess(GUESSCAP, step, answer);
		guessToTotal(BOARDLENGTH, totalGuesses, step, rowCont);
		rowCont++;
		showBoard(GUESSCAP, BOARDLENGTH, totalGuesses);
		if(win){
			winning(rowCont, answer, currentGuess);
			return 0;
		}
	}
	printf("\nLooks like you couldn't get it!\nThe answer is %s!\n", answer);
	return 0;
}
int fileWordConverter(char answer[]){
	int i;
	for(i = 0; answer[i] != '\0'; i++){
		if(answer[i] >= 'A' && answer[i] <= 'Z'){
			answer[i] = answer[i] + 32;
		}
		else if(answer[i] < 'A' || answer[i] > 'z'){
			i = 50;
			break;
		}
		else if(answer[i] > 'Z' && answer[i] < 'a'){
			i = 50;
			break;
		}
	}
	return i;
}
void clearBoard(int guessCap, int board, char totalGuesses[][board], char step[], int steplength){
	for(int i=0; i<GUESSCAP; i++){
		for(int j=0; j<BOARDLENGTH; j++){
			if((j%2) == 0){
				totalGuesses[i][j] = ' ';
			}
			else if(j%2 != 0){
				totalGuesses[i][j] = '|';
			}
		}
	}
	for(int k=0; step[k] != '\0'; k++){
		step[k] = ' ';
	}
}

void showBoard(int guessCap, int board, char totalGuesses[][board]){
	for(int i=0; i<GUESSCAP; i++){
		for(int j=0; j<BOARDLENGTH; j++){
			printf(" %c", totalGuesses[i][j]);
		}
		printf("\n-------------------\n");
	}
}
int checkGuessOverflow(char step[]){
	int counter=0;
	int i=0;
		for(i = 0; step[i] != '\0'; i++){
			if(step[i] >= 'A' && step[i] <= 'Z'){
				step[i] = step[i] + 32;
			}
			counter++;
		}
	if(counter != 5){
		return 1;
	}
	return 0;
	
}
int checkGuess(int guessCap, char step[], char answer[]){
	int i = 0;
	int counter = 0;
	for(int j = 0; j < GUESSCAP; j++){
		for(i=0; step[i] != '\0'; i++){
			if(step[i] == answer[j] && i != j){
				step[i] = '?';
			}
			else if(step[i] == answer[j] && i == j){
				step[i] = step[i] - 32;
				counter++;
			}
		}
	}
	for(int j = 0; j < GUESSCAP; j++){
		for(i=0; step[i] != '\0'; i++){
			if(step[i] != '?' && step[i] >= 'a' && step[i] <= 'z'){
				step[i] = '#';
			}
		}
	}
	if(counter == 5){
		return 1;
	}
	return 0;
}
void guessToTotal(int board, char totalGuesses[][board], char step[], int rowCont){
	int k = 0;
	for(int j=0; j<BOARDLENGTH; j++){
		if((j%2) == 0){
			totalGuesses[rowCont][j] = step[k];
			k++;
		}
	}
}
int winning(int rowCont, char answer[], int currentGuess){
	if(rowCont == 1){
		printf("\nWoah! A perfect game! Did you cheat? Or did you just get lucky?\n\nThe word is %s!\nYou got it in a single guess!\n", answer);
	}
	else if(rowCont == 6){
		printf("\nPhew, just got it!\n\nThe word is %s!\nYou got it on your last guess!\n", answer);
	}
		else if(rowCont > 1 || rowCont <= 5){
		printf("\nGood Job!\n\nThe word is %s!\nYou got it in %d guesses!\n", answer, currentGuess+1);
	}
	return 1;
}

