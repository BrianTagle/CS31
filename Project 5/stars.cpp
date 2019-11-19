#define _CRT_SECURE_NO_DEPRECATE
#include "utilities.h"
#include <iostream>
#include <cstring>
#include<string>
using namespace std;


const char WORDFILENAME[] = "C:/CS31/tester.txt";
const int MAXWORDS = 9000;

bool isLowerCase(char word[], int wordlength) {
	for (int i = 0; i < wordlength; i++) { //check to make sure the cstring contains only lower case letters.
		if (!islower(word[i])) {
			return false; //if a letter is upper case
		}
	}
	return true; //if all letters are lower case
}
bool isWordinList(const char words[][MAXWORDLEN + 1], int nWords, char probeWord[]) { // checks if probeWord is in the word list
	for (int i = 0; i < nWords; i++) { //cycles through every word in the word list
		if (strcmp(words[i], probeWord) == 0) {
			return true; // The probeWord is in the word list
		}
	}
	return false; //the probeWord is not in the word list
}
void findSandP(const char correctWord[], const char probeWord[], int& stars, int& planets) {
	stars = 0; //equal to 0, can't assume anything about original values of stars and planets
	planets = 0;

	char changeableCorrectWord[MAXWORDLEN + 1];
	strcpy(changeableCorrectWord, correctWord); // create an editable copy of the correct word to be used when finding planets
	int correctLength = strlen(correctWord);
	int probeLength = strlen(probeWord);
	for (int i = 0; i < correctLength; i++) {
		if (correctWord[i] == probeWord[i]) { // if the letter at the same spot of correct and probe word are the same, it is a star
			stars++;
		}
	}
	for (int i = 0; i < probeLength; i++) {
		for (int j = 0; j < correctLength; j++) {
			if (probeWord[i] == changeableCorrectWord[j]) { //if a letter in the probeWord is found in the correct word, it is a planet
				planets++;
				changeableCorrectWord[j] = '.'; //if there is a match, the matched letter in the correctWord is changed so that it is ineligible for further matches
				break; //breaks so that if there is a match, the program doesn't look farther down the correctWord and make more matches for only one letter of the probe
			}
		}
	}
	planets -= stars; // since a planet is also a star, except a star simply has more criterion.
	
}


int runOneRound(const char words[][MAXWORDLEN + 1], int nWords, int wordnum) {
	
	//
	char correctWord[MAXWORDLEN + 1];
	char probeWord[200] = "NOT A VALID WORD"; //random intial value so that the while loop starts correctly
	strcpy(correctWord, words[wordnum]);
	int score = 0;
	while (strcmp(correctWord, probeWord) != 0) { // while the user has not guessed correctly, let them guess again
		int stars;
		int planets;

		

		cout << "Probe word: ";
		cin.getline(probeWord, 200);


		int probeWordLEN = strlen(probeWord);
		if (strlen(probeWord) > 6 || strlen(probeWord) < 4 || !isLowerCase(probeWord, probeWordLEN)) {//if the probeword is too short, too long, or character that are not lower case
			cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
		}
		else if (!isWordinList(words, nWords, probeWord)) { //the word isn't in the list
			cout << "I don't know that word." << endl;
		}
		else {
			findSandP(correctWord, probeWord, stars, planets); // find stars and planets
			score++;							//score only increases on valid guesses
			if (stars == strlen(correctWord) && strlen(correctWord) == strlen(probeWord)) {
				break; //stops when the correct word is found
			}
			cout << "Stars: " << stars << ", Planets: " << planets << endl;
			
		}
	}
	return score;
}



int main()
{

	cout.setf(ios::fixed);
	cout.precision(2);
	int numRounds = 0; //intial values for various score keeping variables
	double averageScore = 0;
	int minScore = 0;
	int maxScore = 0;

	char wordList[MAXWORDS][MAXWORDLEN + 1];
	// the 2D array wordList is filled with words from the wordlist
	int n = getWords(wordList, MAXWORDS, WORDFILENAME);


	if (n < 1) {
		cout << "No words were loaded, so I can't play the game."; //no words in text file
	}
	else {
		cout << "How many rounds do you want to play? ";
		cin >> numRounds;
		cin.ignore(10000, '\n'); //allows the program to read in a cstring next, otherwise there are errors
		if (numRounds < 0) {
			cout << "The number of rounds must be positive."; //no rounds so exit
			exit(0);
		}
		cout << endl;

		for (int i = 1; i <= numRounds; i++) {
			cout << "Round " << (i) << endl; 
			int randNum = randInt(0, n - 1); //select a random number
			char WORD[MAXWORDLEN + 1];
			strcpy(WORD, wordList[randNum]); //WORD is the word at the random index of wordList
			cout << "The secret word is " << strlen(WORD) << " letters long." << endl;
			int score = runOneRound(wordList, n, randNum);
			if (score == 1) {
				cout << "You got it in " << score << " try." << endl; // 1 try
			}
			else {
				cout << "You got it in " << score << " tries." << endl; // >1 try
			}

			if (score > maxScore) {// change maxScore to the new high score
				maxScore = score;
			}
			if (minScore == 0) {//change minScore to be equal to the score after the first round
				minScore = maxScore;
			}
			if (score < minScore) {//change minScore in the new min score
				minScore = score;
			}
			if (averageScore == 0) { //average Score is equal to the score on the first round
				averageScore = score;
			}
			else {
				averageScore = ((averageScore * (i - 1)) + score) / i; //find average score by taking the old average, multiplying it to change it back into a sum of previous score, add a new score, then divide by the round number
			}
			cout << "Average: " << averageScore << ", minimum: " << minScore << ", maximum: " << maxScore << endl;
			cout << endl;
		}
	}
}
