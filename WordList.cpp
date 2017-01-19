/* Project3 - Naive Bayes
 * WordList.cpp
 * by Jared Vu
 */
#include "WordList.h"
#include <random>
#include <time.h>
using namespace std;

WordList::WordList() {
	srand(NULL);
}
WordList::WordList(string a, string b)
{
	readIn(a, b);
}

void WordList::readIn(string fReview, string rReview) {
	ifstream freshR;
	string temp;
	Word w;
	freshR.open(fReview);
	if (!freshR.is_open()) {
		cout << "File could not be found!\n";
		system("pause");
		exit(1);
	}
	else {
		while (!freshR.eof()) {
			freshR >> temp;

			for (size_t i = 0; i < temp.size(); i++) {
				if (temp[i] <= 0 || temp[i] >= 255)
					temp[i] = '~';
				temp[i] = tolower(temp[i]);
			}

			w.setWord(temp);
			freshWords.push_back(w);
		}
	}

	ifstream rottenR;
	Word w1;
	rottenR.open(rReview);
	if (!rottenR.is_open()) {
		cout << "Rotten Reviews could not be found!\n";
		system("pause");
		exit(1);
	}
	else {
		while (!rottenR.eof()) {
			rottenR >> temp;

			for (size_t i = 0; i < temp.size(); i++) {
				if (temp[i] <= 0 || temp[i] >= 255)
					temp[i] = '~';
				temp[i] = tolower(temp[i]);
			}

			w1.setWord(temp);
			rottenWords.push_back(w1);
		}
	}
	freshTotal = freshWords.size();
	rottenTotal = rottenWords.size();
}

string WordList::processWord(string toProcess) {
	toProcess.resize(remove_if(toProcess.begin(), toProcess.end(), [](char x) {return (!isalnum(x) && !isspace(x)); }) - toProcess.begin());
	return toProcess;
}

void WordList::processAllWords(){
	for (size_t i = 0; i < freshWords.size(); i++) {
		freshWords[i].setWord(processWord(freshWords[i].getWord()));
	}
	for (size_t i = 0; i < rottenWords.size(); i++) {
		rottenWords[i].setWord(processWord(rottenWords[i].getWord()));
	}
}

void WordList::countAllWords() {

	for(unsigned int i = 0; i < freshWords.size(); i++) {
		if(fHash.find(freshWords[i].getWord()) == fHash.end()) 
			fHash.insert(pair<string,Word>(freshWords[i].getWord(), freshWords[i]));
		else
			fHash[freshWords[i].getWord()].addCount();
	}

	freshWords.clear();

	for (unordered_map<string,Word>::iterator it=fHash.begin(); it!=fHash.end(); ++it) {
		it->second.addCount();
		freshWords.push_back(it->second);
	}


	for (unsigned int i = 0; i < rottenWords.size(); i++) {
		if (rHash.find(rottenWords[i].getWord()) == rHash.end())
			rHash.insert(pair<string, Word>(rottenWords[i].getWord(), rottenWords[i]));
		else
			rHash[rottenWords[i].getWord()].addCount();
	}

	rottenWords.clear();

	for (unordered_map<string, Word>::iterator it = rHash.begin(); it != rHash.end(); ++it) {
		it->second.addCount();
		rottenWords.push_back(it->second);
	}
	calcCondFreq();

}

void WordList::calcCondFreq() {
	for (unordered_map<string, Word>::iterator it = fHash.begin(); it != fHash.end(); ++it) {
		(it->second).setFreshP((long double)(it->second).getCount()/ (long double)freshTotal);
	}
	for (unordered_map<string, Word>::iterator it = rHash.begin(); it != rHash.end(); ++it){
		(it->second).setRottenP((long double)(it->second).getCount() / (long double)rottenTotal);
	}
}

void WordList::print() {
	ofstream data;
	data.open("output.txt");
	data << "Fresh Review Data\n";
	for (unordered_map<string, Word>::iterator it = fHash.begin(); it != fHash.end(); ++it) {
		data << (it->second).getWord() << " " << (it->second).getCount() << " " << (it->second).getFreshP() << endl;
	}
	data << "Rotten Review Data\n";
	for (unordered_map<string, Word>::iterator it = rHash.begin(); it != rHash.end(); ++it) {
		data << (it->second).getWord() << " " << (it->second).getCount() << " " << (it->second).getRottenP() << endl;
	}
	data.close();
}

long double WordList::getFProbability(string x) {
	unordered_map<string, Word>::iterator it = fHash.find(x);
	if (it == fHash.end())
		return -1;
	else
		return (it->second).getFreshP();
}

long double WordList::getRProbability(string x) {
	unordered_map<string, Word>::iterator it = rHash.find(x);
	if (it == rHash.end())
		return -1;
	else
		return (it->second).getRottenP();
}

int WordList::getFSize() {
	return freshTotal;
}

int WordList::getRSize() {
	return rottenTotal;
}