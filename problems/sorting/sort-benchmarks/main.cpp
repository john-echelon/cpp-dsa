#include<iostream>
#include<fstream>
#include<string>
#include<limits> //numeric_limits
#include <cstring>  //strlen
#include <cctype> //tolower
#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "Sort.h"
using namespace std;
void generateNumbers(int arr[], int n, int maxValue);
int writeToFile(int arr[], int n, int maxValue);
int readFromFile(int* &arr, int & n, int & maxValue);
void promptNumber(int & num, string msg);
void displayNumbers(int arr[], int n);
void copyArray(int *&destArr, int * sourceArr, int n);
void print(int arr[], int n, void(Sort<int>::*foo)(int *, int), ostream &os);
void runBenchmark(int arr[], int n, int maxValue);
int main ()
{
	//prompt vars
	const int inputSize = 30;
	char cmdInput[inputSize];
	int err = 0;

	//gen vars
	int maxValue = 100;
	int sampleSize = 10;//536870911
	int * arr = 0;

	//benchmark vars
	time_t now, then;
	double seconds;
	double timeElapsedGenerateNumbers = 0, timeElapsedWritingToFile = 0, timeElapsedReadingFromFile = 0;

	while (cin.good()) {
		cout << "Enter G to generate numbers(set sample size)\nEnter D to display numbers\nEnter S to save sample size\nEnter L to load a sample size\nEnter B to begin benchmark or press enter to quit:";
		cin.getline(cmdInput, inputSize);
		if (strlen(cmdInput) == 0) {
			cin.setstate(std::ios::failbit);
			break;
		}
		switch (toupper(cmdInput[0])) {
			case 'G':
				promptNumber(sampleSize, "Please enter numbers to generate (sample size): ");
				promptNumber(maxValue, "Please enter max value for a generated number: ");
				delete[] arr;
				arr = new int[sampleSize];
				time(&now); //get current time
				generateNumbers(arr, sampleSize, maxValue);
				time(&then);
				timeElapsedGenerateNumbers = difftime(then, now);
				cout << endl << "Time elapsed generating numbers (seconds): " << timeElapsedGenerateNumbers << endl;
				break;
			case 'D':
				displayNumbers(arr, sampleSize);
				break;
			case 'S':
				time(&now); //get current time
				err = writeToFile(arr, sampleSize, maxValue);
		
				if (err != 0) {
					cout << "Error writing to file." << endl;;
				}
				else {
					time(&then);
					timeElapsedWritingToFile = difftime(then, now);
					cout << endl << "Time elapsed writing to file (seconds): " << timeElapsedWritingToFile << endl;
				}
				break;
			case 'L':
					time(&now); //get current time
					err = readFromFile(arr, sampleSize, maxValue);
					if (err != 0) {
						cout << "error reading from file" << endl;;
					}
					else {
						time(&then);
						timeElapsedReadingFromFile = difftime(then, now);
						cout << endl << "Time elapsed reading from file (seconds): " << timeElapsedReadingFromFile << endl;
					}
					break;
			case 'B':
				if(arr ==0)
					cout << "Benchmark aborted. No sample size available to sort" << endl;
				else
					runBenchmark(arr, sampleSize, maxValue);
				break;
			default:
				break;
		}

	}
	delete[] arr;
	if (cin.fail()) {
		return 0;
	}

	return 0;
}

void generateNumbers(int arr[], int n, int maxValue) {
	/* initialize random seed: */
	srand(time(NULL));
	cout << endl << "Sample Size: " << n << endl;
	cout << endl << "Max value for a generated number: " << maxValue << endl;
	for (int i = 0; i < n; i++) {
		arr[i] = rand() % maxValue + 1;
	}
	cout << endl;
}

int writeToFile(int arr[], int n, int maxValue) {
	ofstream numFile("gen_numbers.txt");
	if (arr == 0 || !numFile.is_open())
	{
		return -1;
	}
	numFile << n << endl;//first line is the sample size
	numFile << maxValue << endl;//2nd line is the max gen value

	for (int i = 0; i < n; i++) {
		numFile << arr[i] << endl;
	}
	numFile.close();
	return 0;
}

int readFromFile(int * &arr, int & n, int & maxValue) {
	string line;
	ifstream numFile("gen_numbers.txt");
	if (!numFile.is_open())
	{
		return -1;
	}
	//get sample size
	getline(numFile, line);
	n = stoi(line);
	//get max value
	getline(numFile, line);
	maxValue = stoi(line);

	delete[] arr;
	arr = new int[n];
	for (int i = 0; i < n && getline(numFile, line); i++) {
	
		arr[i] = stoi(line);
	}
	return 0;
}

int * copyArray(int * sourceArr, int n) {
	int * destArr = new int[n];
	for (int i = 0; i < n; i++) {
		destArr[i] = sourceArr[i];
	}
	return destArr;
}
void runBenchmark(int arr[], int n, int maxValue) {
	//file vars
	ofstream outputFile("sortbenchmarks.txt");
	if (!outputFile.is_open())
	{
		cout << "failed to create benchmark file";
	}

	int * temp;

	Sort<int> s;
	void (Sort<int>::*foo)(int *, int);

	outputFile << "Sample Size: " << n << " max value: " << maxValue << endl;

	//TODO: use switch statement
	//foo = &Sort<int>::InsertionSort;
	//outputFile << "############ Running benchmark on insertion sort ############" << endl;
	//cout << "############ Running benchmark on insertion sort ############" << endl;
	//print(arr, n, foo, outputFile);

	//foo = &Sort<int>::SelectionSort;
	//outputFile << "############ Running benchmark on selection sort ############" << endl;
	//cout << "############ Running benchmark on selection sort ############" << endl;
	//print(arr, n, foo, outputFile);

	//foo = &Sort<int>::BubbleSort;
	//outputFile << "############ Running benchmark on bubble sort ############" << endl;
	//cout << "############ Running benchmark on bubble sort ############" << endl;
	//print(arr, n, foo, outputFile);

	// temp = copyArray(arr, n);
	// foo = &Sort<int>::QuickSort;
	// outputFile << "############ Running benchmark on quick sort ############" << endl;
	// cout << "############ Running benchmark on quick sort ############" << endl;
	// print(arr, n, foo, outputFile);
	// delete[] temp;
	temp = copyArray(arr, n);
	foo = &Sort<int>::MergeSort;
	outputFile << "############ Running benchmark on mergesort ############" << endl;
	cout << "############ Running benchmark on merge sort ############" << endl;
	print(arr, n, foo, outputFile);
	if(n<=10)
		displayNumbers(arr, n);
	delete[] temp;
	outputFile.close();
}
void print(int arr[], int n, void(Sort<int>::*foo)(int *, int), ostream &os) {
	time_t now, then;
	double seconds;
	int err = 0;
	Sort<int> obj;

	time(&now); //get current time
	(obj.*foo)(arr, n);
	time(&then);
	seconds = difftime(then, now);
	os << "Time elapsed sorting (seconds): " << seconds << endl;
	cout << "Time elapsed sorting(seconds) : " << seconds << endl;
}

void promptNumber(int & num, string msg) {
	cout << msg;
	while (!(cin >> num)) {
		cout << "Please enter a valid number: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void displayNumbers(int arr[], int n) {
	if (arr == 0)
	{
		cout << "No generated numbers to display" << endl;
		return;
	}
	for (int i = 0; i < n; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}