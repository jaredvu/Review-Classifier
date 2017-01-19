/* Project3 - Naive Bayes
 * Word.cpp
 * by Jared Vu
 */
#include "Word.h"


Word::Word()
{
	word = "";
	count = 0;
	freshProb = 0.00;
	rottenProb = 0.00;
}


void Word::setWord(string x) {
	word = x;
}

string Word::getWord() {
	return word;
}

void Word::addCount() {
	count++;
}

int Word::getCount() {
	return count;
}

void Word::setFreshP(long double a) {
	freshProb = a;
}
void Word::setRottenP(long double a) {
	rottenProb = a;
}
long double Word::getFreshP() {
	return freshProb;
}
long double Word::getRottenP() {
	return rottenProb;
}