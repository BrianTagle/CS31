#include <iostream>
#include <string>
#include <cctype>
#include<cassert>
using namespace std; 

bool isLegalAlpha(string song, int index) { //Checks if the letter character of a note is one of the 7 legal letters for a note
	if (song[index] == 'A' || song[index] == 'B' || song[index] == 'C' || song[index] == 'D' || song[index] == 'E' || song[index] == 'F' || song[index] == 'G')
		return true;
	else
		return false;
}

bool isLegalDigit(string song, int index) { //Checks if the digit character of a note is one of the 4 legal octaves 
	if (song[index] == '2' || song[index] == '3' || song[index] == '4' || song[index] == '5')
		return true;
	else
		return false;
}


bool hasCorrectSyntax(string song) {
	int i = 0;
	if (song.size() == 0) // an empty string is correct syntax so it returns false
		return true;
	else if (song[song.size() - 1] != '/') // the last character of the song string must be "/" do denote a beat, otherwise the string has incorrect syntax
		return false;
	while (i != song.size()) {
		

		if (isalpha(song[i]) && isLegalAlpha(song, i )) {// checks to make sure the first character is a note is an legal alpha character
			i++;
			if (i != song.size() && (song[i]== 'b' || song[i] == '#') ){ //if there is a following character there are two possibilites; one is that it is an accidental sign
				i++;
				if (i != song.size() && isdigit(song[i]) ) { // if there still a part of the note reaming it must be a digit
					i++;

				}

			}
			else if (i != song.size() && isdigit(song[i]) ) { // if the following character is not an accidental sign but is a digit
				i++;

			}

		}
		else if (song[i] == '/') { // if the character is '/' the function moves onto the next character in the string since / is always syntactically correct
			i++;
		}
		else { // if the character given is not / or is not a note in the form (note letter, accidental sign, octave number)
			return false;
		}
	}
	return true;
}


bool isPlayableSong(string song) {
	int i = 0;
	if (song.size() == 0) // a empty song is playable (technically there is nothing to play but it is still correct)
		return true;
	else if (song[song.size() - 1] != '/') // all beats must end with a slash
		return false;

	
	while (i != song.size()) {

		if ((i + 2) < song.size() && song.substr(i, 3) == "Cb2") { //This and the the three following statements are exceptions for four different notes 
			return false;										// these notes would otherwise fail the normal checks for legal notes yet these notes
																// are still legal based on instructions given.
		}
		else if ((i + 2) < song.size() && song.substr(i, 3) == "Cb6") {
			(i += 3);

		}
		else if ((i + 2) < song.size() && song.substr(i, 3) == "B#1") {
			(i += 3);

		}
		else if ((i + 1) < song.size() && song.substr(i, 2) == "C6") {
			(i += 2);

		}

		else if (isalpha(song[i]) && isLegalAlpha(song, i)) { // same general conditions as hasCorrectSyntax checks for the first character be a legal alpha character
			i++;
			if (i != song.size() && (song[i] == 'b' || song[i] == '#')) { // then the code checks if the next part is an accidental sign or a digit
				i++;
				if (i != song.size() && isdigit(song[i]) && isLegalDigit(song, i)) { // if the the third char is a digit (MUST BE LEGAL DIGIT)
					i++;

				}

			}
			else if (i != song.size() && isdigit(song[i]) && isLegalDigit(song, i)) { //if the second char is a digit (MUST BE LEGAL DIGIT)
				i++;

			}

		}
		else if (song[i] == '/') { //beat signs are always playable no matter what comes before or after them
			i++;
		}
		else {
			return false;
		}
	}
	return true;
}

string extractNote(string song, int& index) { //extracts the note (3 characters) at the specificed index then changes the index number to the beginning of the next note
	
	if (index != song.size() && isalpha(song[index])) {
		index++;
		if (index != song.size() && isdigit(song[index])) {
			index++;
			return song.substr((index - 2), 1) + " " + song.substr((index-1), 1); //gives the note letter then a space then the digit; EX: "A 3"

		}
		else if (index != song.size() && (song[index] == 'b' || song[index] == '#')) {
			index++;
			if (index != song.size() && isdigit(song[index])) {
				index++;
				return song.substr((index - 3), 3); //gives a note with all three characters filled ; EX: "B#5"
			}
			else {
				return song.substr((index - 2), 2) + " "; //gives a note with note letter and accidental sign; EX: "Db "
			}
		}
		else {
			return song.substr((index - 1), 1) + "  "; //gives just the note letter ; EX: "C  "
		}
	}
	else {
		return "";// this return path should never be used, if it is used, the programmer inputed something that was not a note
	}				// THIS FUNCTION DOES NOT CHECK CONDITIONS PROGRAMMER MUST CHECK THEMSELVES BEFORE USING THIS FUNCTION
}

	

char encodeNote(int octave, char noteLetter, char accidentalSign) //given function from specs
{
	// This check is here solely to report a common CS 31 student error.
	if (octave > 9)
	{
		cerr << "********** encodeNote was called with first argument = "
			<< octave << endl;
	}

	// Convert Cb, C, C#/Db, D, D#/Eb, ..., B, B#
	//      to -1, 0,   1,   2,   3, ...,  11, 12

	int note;
	switch (noteLetter)
	{
	case 'C':  note = 0; break;
	case 'D':  note = 2; break;
	case 'E':  note = 4; break;
	case 'F':  note = 5; break;
	case 'G':  note = 7; break;
	case 'A':  note = 9; break;
	case 'B':  note = 11; break;
	default:   return ' ';
	}
	switch (accidentalSign)
	{
	case '#':  note++; break;
	case 'b':  note--; break;
	case ' ':  break;
	default:   return ' ';
	}

	// Convert ..., A#1, B1, C2, C#2, D2, ... to
	//         ..., -2,  -1, 0,   1,  2, ...

	int sequenceNumber = 12 * (octave - 2) + note;

	string keymap = "Z1X2CV3B4N5M,6.7/A8S9D0FG!H@JK#L$Q%WE^R&TY*U(I)OP";
	if (sequenceNumber < 0 || sequenceNumber >= keymap.size())
		return ' ';
	return keymap[sequenceNumber];
}

int encodeSong(string song, string& instructions, int& badBeat) {
	int octaveNumber = 4;
	char noteLetter = ' ';
	char accidentalSign = ' ';
	char currentNote = ' ';
	string extractedNote = "";
	if (hasCorrectSyntax(song) && isPlayableSong(song)) { //if the song is formatted correcrtly and is playable on the online keyboard
		// return 0;
		int chord = 0;
		int i = 0;
		instructions = "";
		if (song.size() == 0) {
			instructions = ""; //a song with 0 size returns instructions with 0 size;
			return 0;

		}
		while (i != song.size()) {
			octaveNumber = 4;
			if ((song[i] == '/' && i != 0 && song[i-1]== '/') || ( song[i] =='/' && i==0 ) ){ //if / is the first character or there are two /'s back to back
				instructions += " ";														// which means that there is an empty beat
				i++;
				chord = 0; //chord tracks the number of notes in a beat, 
			}
			else if (song[i] == '/') { 
				
				if (chord > 1) {
					size_t wheretoinsert = instructions.size()- chord; //if chord is greater than 1 it puts brackets around the the previous beat when it reachs the beat marker
					instructions.insert(wheretoinsert, "[", 1);
					instructions += "]";
				}
				i++;
				chord = 0;
			}
			else { // extracts the current note from the string and enter in the three parameters to encode note, adds the encoded note to instructions 
				extractedNote = extractNote(song, i); //extractNote increments i
				noteLetter = extractedNote[0];
				accidentalSign = extractedNote[1];
				if (extractedNote[2] == ' ') {
					octaveNumber = 4;
				}
				else {
					octaveNumber = extractedNote[2] - '0';
				}
				chord++;
				currentNote = encodeNote(octaveNumber, noteLetter, accidentalSign);
				instructions += currentNote;
			}

		}

		return 0;
	}
	
	else if (hasCorrectSyntax(song) && !isPlayableSong(song)) { //If the song is formatted correctly but is not playable on the online keyboard
		int i = 0;
		badBeat = 1; //tracks what beat the program is looking at so when the while loops breaks, badbeat will equal the beat which caused the progam
		while (i != song.size()) {   //to break because the beat had an unplayable note.
			if (song[i] == '/') {
				i++;
				badBeat++;
			}
			else {
				extractedNote = extractNote(song, i);
				noteLetter = extractedNote[0];
				accidentalSign = extractedNote[1];
				if (extractedNote[2] == ' ') {
					octaveNumber = 4;
				}
				else {
					octaveNumber = extractedNote[2] - '0';
				}
				if (encodeNote(octaveNumber, noteLetter, accidentalSign) == ' ') { //if the extracted note is " " the note was incorrect somehow so it breaks the function
					break;
				}
			}

			
		}
		return 2;
	}
	else {
		return 1; //if the song is not a song string ie. the song returns false for hasCorrectSyntax 
	}
	return  1;
}

int main(){
	
	
}
