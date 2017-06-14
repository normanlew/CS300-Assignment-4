// Norman Lew
// CS 300
// Spring 2017

// Assignment 4, Question 2

// This program will read an input file composed of strings.  Each string is passed to a hash function, and then the string is stored in an
// array of strings.  The placement of the string into the array is determined by the value returned by the hash function.  Collisions are handled by
// chaining.

#include "Word.h"
#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	Word x;
	string theWord;
	char menuSelection;
	string s;

	// Open the file.  Read in each string and put it into the array of strings.
	ifstream myfile;
	myfile.open("test.txt");
	if (myfile.is_open()) {
		while (!myfile.eof())
		{
			myfile >> theWord;
			x.add(theWord);
		}
	}
	myfile.close();

	// Report the total number of collisions.
	cout << "Number of collisions: " << x.getNumberOfCollisions() << endl << endl;
	
	do {
		cout << "(S)earch | (L)ist | (Q)uit: ";
		cin >> menuSelection;

		// Prompt user word to search for
		if (menuSelection == 'S' || menuSelection == 's')
		{
			cout << "Enter word to search for : ";
			cin.ignore();
			getline(cin, s);
			cout << s << " occurs " << x.get(s) << " times " << endl << endl;
		}

		// Print the entire string array
		if (menuSelection == 'L' || menuSelection == 'l')
		{
			x.print();
		}


	} while (menuSelection != 'Q' && menuSelection != 'q');

	cin.get();
	cin.get();
	return 0;
}
