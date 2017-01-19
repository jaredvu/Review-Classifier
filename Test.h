/* Project3 - Naive Bayes
 * Test.h
 * by Jared Vu
 */
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <stdlib.h>
#include "WordList.h"

using namespace std;

#ifndef TEST_H
#define TEST_H
class Test
{
private:
	vector<string> testWords;
	vector<string> heldOutF;
	vector<string> heldOutR;
	long double likes;
	long double dislikes;
	WordList trainingData;
public:
	Test(string, string, string, long double, long double, WordList);
	void readFile(string); //Read test file
	void readHeldOut(string, string); //read held out files
	string processString(string); //Process string
	void processFile(); //Process all files
	void classify(); //Classifies test review by adding logs of the probability of each word.
	void print(); //Print results to the screen
};
#endif

