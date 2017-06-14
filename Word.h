// Norman Lew
// CS 300
// Spring 2017

// Assignment 4, Question 2

// This is the Word class.  It includes a word counting data structure using a hash table.  Each word input into the data structure
// will be assigned a hash value and placed into the array of words.  Collisions are handled by chaining.

#include "LinkedList.h"
#include <string>
#include <string.h>
using namespace std;

#ifndef WORD_H_
#define WORD_H_


class Word
{
private:
	// Words will be stored in an array of string Linked Lists
	LinkedList<string> wordArray [26];
	int numberOfCollisions;

	// Internal hash function
	int hashFunction(const string& c)
	{
		int i;
		int x = 0;

		for (i = 0; i < c.length(); i++)
		{
			x = x + (int)c[i];
		}

		return x % 26;
	}


public:
	Word();

	// Add a string into the array
	void add(const string&);

	// Check to see if the array contains the string
	bool contains(const string&);

	// Return the total number of collisions
	int getNumberOfCollisions();

	// Prints the entire array
	void print();

	// Returns the number of occurrences in the array for the givern string
	int get(const string&);
};

Word::Word()
{
	numberOfCollisions = 0;
}

// Add a string into the word array.  
void Word::add(const string& c)
{
	int a = hashFunction(c);
	string b = c;

	if (!wordArray[a].is_empty())
	{
		numberOfCollisions++;
	}

	wordArray[a].insert_first(b);
}


// Check to see if the array contains the string
bool Word::contains(const string& c)
{
	int x = hashFunction(c);
	string a = c;

	return wordArray[x].contains(a);
}

int Word::getNumberOfCollisions()
{
	return numberOfCollisions;
}

void Word::print()
{
	int i;
	for (i = 0; i < 26; i++)
	{
		cout << "Bucket " << i << ": " << endl;
		printLinkedList(wordArray[i]);
	}
}

int Word::get(const string& c)
{
	string a = c;
	int x = hashFunction(c);
	return wordArray[x].numOfOccurrences(a);
}

#endif