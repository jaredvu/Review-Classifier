/* Project3 - Naive Bayes
 * Word.h
 * by Jared Vu
 */
#include <string>
#include <iostream>
#include <vector>
#include <stdlib.h>
using namespace std;

#ifndef WORD_H
#define WORD_H
class Word
{
private:
	string word;
	int count;
	long double freshProb;
	long double rottenProb;

public:
	Word();
	void setWord(string);	//Sets word
	string getWord();		//Get word
	void addCount();		//Adds one to the count
	int getCount();			//Get wordCount
	void setFreshP(long double); //set the fresh probability
	void setRottenP(long double); //set the rotten probability
	long double getFreshP(); //get the fresh probability
	long double getRottenP(); //get the rotten probability
};

#endif