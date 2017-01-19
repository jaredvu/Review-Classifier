/* Project3 - Naive Bayes
 * main.cpp
 * by Jared Vu
 */

#include <stdlib.h>
#include "WordList.h"
#include "Word.h"
#include "Test.h"
using namespace std;

//Global Constants ---------------------------------
#define FRESH_PROPORTION .7011494253
#define ROTTEN_PROPORTION .2988505747
#define FRESH_TEST "fresh_reviews.txt"
#define ROTTEN_TEST "rotten_reviews.txt"
#define F_HELDOUT "FreshHeldOut.txt"
#define R_HELDOUT "RottenHeldOut.txt"
//--------------------------------------------------

int main()
{
	int choice;
	string testFile;
	WordList Review(FRESH_TEST, ROTTEN_TEST);
	Review.processAllWords();
	Review.countAllWords();
	Review.print();

	// Ask to test a file
	cout << "Enter an option: \n";
	cout << "<1>Test a file\n";
	cout << "<2>Exit\n";
	cin >> choice;
	if (choice == 1) {
		system("CLS");
		cout << "Enter file name: ";
		cin >> testFile;
		system("CLS");
		Test testReview(testFile, F_HELDOUT, R_HELDOUT, FRESH_PROPORTION, ROTTEN_PROPORTION, Review);
		testReview.classify();
		testReview.print();
	}
	if (choice == 2) {
		exit(1);
	}
	
	system("pause");
    return 0;
}

