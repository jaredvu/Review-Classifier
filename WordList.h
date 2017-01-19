/* Project3 - Naive Bayes
 * WordList.h
 * by Jared Vu
 */
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <stdlib.h>
#include <unordered_map>
#include "Word.h"


#ifndef WORDLIST_H
#define WORDLIST_H
class WordList
{
private:
	vector<Word> freshWords;
	vector<Word> rottenWords;
	unordered_map<string, Word> fHash;
	unordered_map<string, Word> rHash;
	int freshTotal;
	int rottenTotal;
	string freshReview;
	string rottenReview;
public:
	WordList();
	WordList(string, string);
	void readIn(string, string);
	string processWord(string);
	void processAllWords();
	void countAllWords();
	void calcCondFreq();	//calculates conditional frequencies
	void print();			//Dumps word counts and conditional frequencies out to the screen
	long double getFProbability(string);
	long double getRProbability(string);
	int getFSize();
	int getRSize();

};
#endif
