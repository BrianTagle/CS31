#include <iostream>
#include <string>
#include <cassert>
using namespace std;




bool indexOutOfBounds(int n, int pos) {// false means that the index n and position pos are valid
	if (n < 0 || pos < 0)							// true means that either index n is less than zero or position is greater than index or less than zero
		return true;
	else if (n == 0) {
		if (pos == 0)
			return false;
		else
			return true;
	}
	else if (pos >= n)
		return true;
	else 
		return false;
}




int appendToAll(string a[], int n, string value) { //looks through the array and adds value to the end of each string in the array
	if (indexOutOfBounds(n, 0)) { //This checks to make sure n is in range, since there is no positon for this function 0 is an input 
								// that will cause the indexOutOfBound function to only inspect n.  This code is repeated several times.
		return -1;
	}
	for (int i = 0; i < n; i++) {
		a[i] += value;
	}
	return n;
}




int lookup(const string a[], int n, string target) { //looks for the target in the array.  returns -1 if the target is not in the array.  
	if (indexOutOfBounds(n, 0)) {					// returns i (the position of target in the array) if the target is in the array
		return -1;
	}
	for (int i = 0; i < n; i++) {
		if (a[i] == target) {
			return i;
		}
	}
	return -1;
}




int positionOfMax(const string a[], int n) {  // compares characters in the string with whatever string is believes the max at the time
	if (n != 0) {							// returns the position of the max position if it can inspect elements else returns -1
		if (indexOutOfBounds(n, 0)) {
			return -1;
		}
		int maxPos = 0;
		string maxString = a[0];
		for (int i = 0; i < n; i++) {
			if (maxString < a[i]) {
				maxPos = i;
				maxString = a[i];

			}
		}
		return maxPos;
	}
	return -1;
}




int rotateLeft(string a[], int n, int pos) { //take the string at pos move it to the end of the array and everything else shifts to the left
	if (n != 0) {							// filling the empty spaces left by the moving string at pos
		if (indexOutOfBounds(n, pos)) {
			return -1;
		}
		string temp = a[pos];
		for (int i = pos; i < n - 1; i++) { // (i < n-1) we dont want to go to n because we are looking at i+1 in this loop so if we went to i we would go out of bounds
			a[i] = a[i + 1];
		}
		a[n - 1] = temp;
		return pos;
	}
	return -1;
}




int countRuns(const string a[], int n) {
	if (n != 0) {

		if (indexOutOfBounds(n, 0)) {
			return -1;
		}

		int runs = 1; // runs starts at 1 because my code works by comparing to upcoming strings so the final run wouldnt count itself because it can't compare itself to upcoming characters
		for (int i = 0; i < n - 1; i++) { // comparing to i+1 so we must end the loop early by making the condition i < n-1
			if (a[i] == a[i + 1]) {
				;
			}
			else {
				runs++;

			}
		}
		return runs;
	}
	else
		return 0; // if there are no elements to inspect
}




int flip(string a[], int n) { //flips the string around the n/2 index
	if (indexOutOfBounds(n, 0)) {
		return -1;
	}
	for (int i = 0; i < (n / 2); i++) { //looks at a[i] and a[n-1-i] and swaps the elements of the two
		string temp = a[i];				// for even arrays, every loop is a swap
		a[i] = a[n - 1 - i];			// for odd arrays the last loop swaps the middle element with itself, making no change
		a[n - 1 - i] = temp;
	}
	return n;
}




int differ(const string a1[], int n1, const string a2[], int n2) {
	if (indexOutOfBounds(n1, 0)) {
		return -1;						//checks the legality of both n1 and n2
	}
	if (indexOutOfBounds(n2, 0)) {
		return -1;
	}
	int n = 0;
	if (n1 >= n2)					// sets the value of n to be the smaller of n1 and n2.  We do this because we are going to compare the strings n times and if n was larger than one of the arrays we would go out of bounds
		n = n2;
	else // n1 < n2
		n = n1;
	for (int i = 0; i < n; i++) {
		if (a1[i] != a2[i]) {
			return i;				// returns the first place in the arrays where the two arrays differ
		}
	}
	return n; //returns n if they never differ
}




int subsequence(const string a1[], int n1, const string a2[], int n2) { //attempts to find the array a2 in a1
	if (indexOutOfBounds(n1, 0)) {
		return -1;
	}
	if (indexOutOfBounds(n2, 0)) {
		return -1;
	}
	if (n1 == 0 && n2 == 0)
		return 0;
	else if (n1 == 0) // this solves a problem with my code where it looks the second array even if it has 0 elements
		return -1;
	else if (n2 == 0) 
		return 0;
	int numCorrect = 0;
	for (int i = 0; i <= (n1 - n2); i++) { // i <= n1 - n2  because when i gets to a point where a2 could no longer fit into a1 there is no point in continuing to check
		numCorrect = 0;
		if (a1[i] == a2[0]) { //if we find a1[i] equals the first string in a2 we then look through the array to see if the following character in a1 match a2 to make a subsequence
			
			for (int j = 0; j < n2; j++) {
				if (a1[i+j] == a2[j]) {
					numCorrect++;
				}
			}
			if (numCorrect == n2) {
				return i; //when a subsequence is found return where it starts in a1
			}
		}
		
	}
	return -1; // no subsequence is found
}




int lookupAny(const string a1[], int n1, const string a2[], int n2) {
	if (indexOutOfBounds(n1, 0)) {
		return -1;
	}
	if (indexOutOfBounds(n2, 0)) {
		return -1;
	}
	for (int i = 0; i < n1; i++) { //takes a1[i]
		for (int j = 0; j < n2; j++) { //comapres it to all values of a2[]
			if (a1[i] == a2[j])
				return i; //if it finds that a1[i] is in a2[] then it returns pos(i) of that string in a1
		}
	}
	return -1; // if there are no strings that are the same in both arrays
}




int split(string a[], int n, string splitter) {
	if (indexOutOfBounds(n, 0)) {
		return -1;
	}
	int originalN = n;
	int finalSplit = n;
	for (int i = 0; i < n; i++) { //looks through the array
		if (a[i] > splitter) { //if a[i] is > splitter
			rotateLeft(a, n, i); //move a[i] to the end of the array and move everything down one
			i--; //since we move everything down one we must i-- because when we rotateLeft a[i] changes so we must check it again
			n--; // we don't need to check all the way to the end if we rotate because we know what we rotated is correctly at the end, also prevents an infinite loop by infinitley checking and rotating elements that are > splitter
		}

	}
	for (int i = 0; i < originalN; i++) { //after we have rearragned we check to see where the first value that is > splitter
		if (a[i] >= splitter) {
			finalSplit--;
		}
	}
	return finalSplit; //return the first elemment that is > splitter
}




void printarray(string arg[], int length) {
	for (int n = 0; n<length; ++n)
		cout << arg[n] << "  ";
	cout << '\n';
}




int main(){
	// tests for appendToAll
	string people1[5] = { "clark", "peter", "diana", "tony", "selina" };
	assert(appendToAll(people1, 5, "!!!") == 5 && people1[0] == "clark!!!" && people1[4] == "selina!!!");
	string people2[5] = { "clark", "peter", "diana", "tony", "selina" };
	assert(appendToAll(people2, 3, "!!!") == 3 && people2[0] == "clark!!!" && people2[4] == "selina" && people2[3] == "tony");
	string people3[5] = { "clark", "peter", "diana", "tony", "selina" };
	assert(appendToAll(people3, 0, "!!!") == 0 && people3[0] == "clark" && people3[4] == "selina" && people3[3] == "tony");
	assert(appendToAll(people3, -20, "!!!") == -1 && people3[0] == "clark" && people3[4] == "selina" && people3[3] == "tony");
	string test1[5] = { "a", "b", "c", "d", "e" };
	assert(appendToAll(test1, 4, "y") == 4 && test1[0] == "ay" && test1[3] == "dy" && test1[4] == "e");

	//tests for lookup
	string people4[5] = { "clark", "peter", "diana", "tony", "selina" };
	assert(lookup(people4, 5, "tony") == 3);
	assert(lookup(people4, 3, "tony") == -1);
	assert(lookup(people4, 3, "diana") == 2);
	assert(lookup(people4, -3, "diana") == -1);
	assert(lookup(people4, 5, "bob") == -1);
	assert(lookup(people4, 0, "bob") == -1);
	string test2[5] = { "a", "b", "c", "d", "e" };
	assert(lookup(test2, 2, "c") == -1);

	//tests for positionOfMax
	string hero[6] = { "clark", "peter", "reed", "tony", "diana", "bruce" };
	assert(positionOfMax(hero, 6) == 3);
	assert(positionOfMax(hero, 1) == 0);
	assert(positionOfMax(hero, 3) == 2);
	assert(positionOfMax(hero, 0) == -1);
	assert(positionOfMax(hero, -1) == -1);
	string test3[5] = { "a", "b", "c", "d", "e" };
	assert(positionOfMax(test3, 5) == 4);

	//tests for rotateLeft
	string super[5] = { "logan", "clark", "peter", "sue", "reed" };
	assert(rotateLeft(super, 5, 1) == 1 && super[1] == "peter" && super[4] == "clark" && super[2] == "sue");
	assert(rotateLeft(super, 0, 1) == -1);
	assert(rotateLeft(super, 0, 0) == -1);
	assert(rotateLeft(super, -10, 2) == -1);
	assert(rotateLeft(super, 5, -3) == -1);
	assert(rotateLeft(super, 3, 0) == 0 && super[3] == "reed" && super[0] == "peter" && super[1] == "sue" && super[2] == "logan");
	string test4[5] = { "a", "b", "c", "d", "e" };
	assert(rotateLeft(test4, 4, 1) == 1 && test4[0] == "a" && test4[1] == "c" && test4[3] == "b" && test4[4] == "e");

	//tests for CountRuns
	string d[9] = { "tony", "bruce", "steve", "steve", "diana", "diana", "diana", "steve", "steve" };
	assert(countRuns(d, 9)== 5);
	assert(countRuns(d, 8) == 5);
	assert(countRuns(d, 7) == 4);
	assert(countRuns(d, 2) == 2);
	assert(countRuns(d, 0) == 0);
	assert(countRuns(d, -20) == -1);
	string test5[5] = { "c", "b", "c", "c", "c" };
	assert(countRuns(test5, 5) == 3);

	//tests for flip
	string folks[6] = { "bruce", "steve", "", "tony", "sue", "clark" };
	assert(flip(folks, 6) == 6 && folks[0] == "clark" && folks[1] == "sue" && folks[4] == "steve" && folks[5] == "bruce");
	string folks1[6] = { "bruce", "steve", "", "tony", "sue", "clark" };
	assert(flip(folks1, 4) == 4 && folks1[0] == "tony" && folks1[1] == "" && folks1[4] == "sue" && folks1[5] == "clark");
	assert(flip(folks1, -5) == -1 && folks1[0] == "tony" && folks1[1] == "" && folks1[4] == "sue" && folks1[5] == "clark");
	assert(flip(folks1, 0) == 0 && folks1[0] == "tony" && folks1[1] == "" && folks1[4] == "sue" && folks1[5] == "clark");
	string test6[5] = { "a", "b", "c", "d", "e" };
	assert(flip(test6, 3) == 3);

	//tests for differ
	string folks2[6] = { "bruce", "steve", "", "tony", "sue", "clark" };
	string group[5] = { "bruce", "steve", "clark", "", "tony" };
	assert(differ(folks2, 6, group, 5)== 2);
	assert(differ(folks2, 2, group, 1)== 1);
	assert(differ(folks2, -3, group, 1) == -1);
	assert(differ(folks2, 4, group, -7) == -1);
	assert(differ(folks2, -3, group, -50) == -1);
	assert(differ(folks2, 6, group, 1) == 1);
	assert(differ(folks2, 1, group, 5) == 1);
	assert(differ(folks2, 3, group, 3) == 2);
	assert(differ(folks2, 0, group, 0) == 0);
	assert(differ(folks2, 5, group, 0) == 0);
	assert(differ(folks2, 0, group, 5) == 0);
	string test7[5] = { "a", "b", "c", "d", "e" };
	assert(differ(test7, 5, group, 5) == 0);

	//tests for subsequence
	string names[10] = { "logan", "reed", "sue", "selina", "bruce", "peter" };
	string names1[10] = { "reed", "sue", "selina" };
	string names2[10] = { "logan", "selina" };
	assert(subsequence(names, 6, names1, 3) == 1);
	assert(subsequence(names, 5, names2, 2) == -1);
	assert(subsequence(names, 0, names1, 0) == 0);
	assert(subsequence(names, -5, names1, -20) == -1);
	assert(subsequence(names2, 2, names2, 2) == 0);
	assert(subsequence(names2, 1, names2, 2) == -1);
	assert(subsequence(names2, 2, names2, 1) == 0);
	assert(subsequence(names, 2, names2, 0) == 0); //WHAT THE FUCK DOES THIS MEAN
	assert(subsequence(names, 0, names2, 2) == -1);
	string test8[5] = { "a", "b", "c", "d", "e" };
	string test9[2] = { "d", "e" };
	assert(subsequence(test8, 4, test9, 2) == -1);

	//tests for lookupAny
	string names3[10] = { "logan", "reed", "sue", "selina", "bruce", "peter" };
	string set1[10] = { "clark", "bruce", "selina", "reed" };
	string set2[10] = { "tony", "diana" };
	assert(lookupAny(names3, 6, set1, 4)==1); 
	assert(lookupAny(names3, 1, set1, 4) == -1);
	assert(lookupAny(names3, 5, set1, 2) == 4);
	assert(lookupAny(names3, 6, set2, 2)==-1);  
	assert(lookupAny(names3, -4, set1, 0) == -1);
	assert(lookupAny(names3, 0, set1, -4) == -1);
	assert(lookupAny(names3, -4, set1, -26) == -1);
	assert(lookupAny(names3, 0, set1, 4) == -1);
	assert(lookupAny(names3, 6, set1, 0) == -1);
	assert(lookupAny(names3, 0, set1, 0) == -1);
	string test10[5] = { "a", "c", "d", "e" };
	string test11[2] = {"c", "d", };
	assert(lookupAny(test10, 4, test11, 2)== 1);

	//tests for split
	string hero1[6] = { "clark", "peter", "reed", "tony", "diana", "bruce" };
	string hero2[4] = { "reed", "sue", "peter", "steve" };
	string hero3[6] = { "clark", "diana", "bruce", "peter", "reed", "tony" };
	assert(split(hero1, 0, "logan") == 0);
	assert(split(hero1, -3, "logan") == -1);
	assert(split(hero1, 6, "logan") == 3);
	assert(split(hero3, 6, "logan") == 3);
	assert(split(hero2, 2, "steve") == 1);
	string hero4[4] = { "reed", "sue", "peter", "steve" };
	assert(split(hero4, 4, "steve")==2); // should == 2
	assert(split(hero1, 1, "logan") == 1);
	assert(split(hero1, 2, "logan") == 2);
	string hero5[6] = { "clark", "peter", "reed", "tony", "diana", "bruce" };
	assert(split(hero5, 5, "logan") == 2);
	string test12[5] = { "a", "b", "c", "d", "e" };
	string test13[5] = { "a", "b", "c", "d", "e" };
	assert(split(test12, 5, "c") == 2);
	assert(split(test13, 5, "d") == 3);
	
	
	


	cerr << "All tests succeeded" << endl;

}