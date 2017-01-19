/* Project3 - Naive Bayes
 * Test.cpp
 * by Jared Vu
 */
#include "Test.h"


Test::Test(string x, string x1, string x2, long double y, long double z, WordList a)
{
	likes = log10(y);
	dislikes = log10(z);
	readHeldOut(x1, x2);
	readFile(x);
	trainingData = a;
	
}

void Test::readFile(string fileName) {
	ifstream testFile(fileName);
	string temp;
	if (!testFile.is_open()) {
		cout << "Test file could not be found!\n";
		system("pause");
		exit(1);
	}
	else {
		while (!testFile.eof()) {
			testFile >> temp;
			for (size_t i = 0; i < temp.size(); i++) {
				if (temp[i] <= 0 || temp[i] >= 255)
					temp[i] = '~';
				temp[i] = tolower(temp[i]);
			}
			testWords.push_back(temp);
		}
	}
	processFile();
}

void Test::readHeldOut(string f, string r) {
	ifstream fheld(f);
	string temp;
	if (!fheld.is_open()) {
		cout << "Held out file could not be found!\n";
		system("pause");
		exit(1);
	}
	else {
		while (!fheld.eof()) {
			fheld >> temp;
			for (size_t i = 0; i < temp.size(); i++) {
				if (temp[i] <= 0 || temp[i] >= 255)
					temp[i] = '~';
				temp[i] = tolower(temp[i]);
			}
			heldOutF.push_back(temp);
		}
		fheld.close();
	}

	ifstream rheld(r);

	if (!rheld.is_open()) {
		cout << "Held out file could not be found!\n";
		system("pause");
		exit(1);
	}
	else {
		while (!rheld.eof()) {
			rheld >> temp;
			for (size_t i = 0; i < temp.size(); i++) {
				if (temp[i] <= 0 || temp[i] >= 255)
					temp[i] = '~';
				temp[i] = tolower(temp[i]);
			}
			heldOutR.push_back(temp);
		}
		rheld.close();
	}

}

string Test::processString(string toProcess) {
	toProcess.resize(remove_if(toProcess.begin(), toProcess.end(), [](char x) {return (!isalnum(x) && !isspace(x)); }) - toProcess.begin());
	return toProcess;
}

void Test::processFile() {
	for (size_t i = 0; i < testWords.size(); i++) {
		testWords[i] = processString(testWords[i]);
	}
	for (size_t i = 0; i < heldOutF.size(); i++) {
		heldOutF[i] = processString(heldOutF[i]);
	}
	for (size_t i = 0; i < heldOutR.size(); i++) {
		heldOutR[i] = processString(heldOutR[i]);
	}
}

void Test::classify() {
	long double F;
	long double R;
	int uniqueF = 0;
	int uniqueR = 0;
	long double FUNK = 0;
	long double RUNK = 0;
	for (size_t i = 0; i < heldOutF.size(); i++) {
		if (trainingData.getFProbability(heldOutF[i]) == -1)
			uniqueF++;
	}
	FUNK = (long double)uniqueF / (long double)(heldOutF.size() + trainingData.getFSize());
	for (size_t i = 0; i < heldOutR.size(); i++) {
		if (trainingData.getFProbability(heldOutR[i]) == -1)
			uniqueR++;
	}
	RUNK = (long double)uniqueR / (long double)(heldOutF.size() + trainingData.getRSize());
	for (size_t i = 0; i < testWords.size(); i++) {
		F = trainingData.getFProbability(testWords[i]);
		R = trainingData.getRProbability(testWords[i]);

		if ( F != -1) {
			likes += log10(F);
		}
		else {
			//likes = likes * trainingData.getFUNK();
			likes = likes + log10(FUNK);
		}
		if (R != -1) {
			dislikes += log10(R);
		}
		else {
			//dislikes = dislikes* trainingData.getRUNK();
			dislikes = dislikes + log10(RUNK);
		}
	}
}

void Test::print() {
	if (likes > dislikes) {
		cout << "This review has been classified as Fresh.\n";
	}
	else {
		cout << "This review has been classified as Rotten.\n";	
	}
	//cout << testWords.size() << endl;
	cout << "Scores of ....\n" << "Fresh: " << likes << endl << "Rotten: " << dislikes << endl;
}