// Sort algorithms.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std; // because I am lazy

void printArray(int* myArray, const int arrayLength) {
	cout << "Printing the array:" << endl;
	for (int i = 0; i < arrayLength; ++i)
		cout << myArray[i] << " ";
	cout << endl;
}


void zeroArray(int* myArray, const int arrayLength) {
	cout << "The array is going to be set to zero" << endl;
	for (int i = 0; i < arrayLength; ++i)
		myArray[i] = 0;
	printArray(myArray, arrayLength);
}

void insertionSort(int* myArray, const int arrayLength) {
	cout << "Insertion sort is starting" << endl;
	int i;
	for (int j = 1; j < arrayLength; ++j) {
		int key = myArray[j];
		for (i = j - 1; i > -1 && myArray[i] > key; --i)
			myArray[i + 1] = myArray[i];
		myArray[i + 1] = key;
	}
}

void bubbleSort(int* myArray, const int arrayLength) {
	cout << "Bubble sort is starting" << endl;
	for (int i = arrayLength - 1; i > 0; --i)
		for (int j = 0; j < i; ++j)
			if (myArray[j] > myArray[j + 1]) {
				myArray[j] += myArray[j + 1];
				myArray[j + 1] = myArray[j] - myArray[j + 1];
				myArray[j] -= myArray[j + 1];
			}
}

void selectionSort(int* myArray, const int arrayLength) {
	cout << "Selection sort is starting" << endl;
	
	for (int i = 0; i < arrayLength - 1; ++i) {
		int iSmall = i;
		for (int j = i + 1; j < arrayLength; ++j) 
			if (myArray[iSmall] > myArray[j])
				iSmall = j;
		if (i != iSmall)
			swap(myArray[iSmall], myArray[i]);
	}
}

void mergeSort(int* myArray, const int start, const int end) {
	cout << "Merge sort is starting" << endl;
	if (end - start < 2 or myArray == nullptr) return;
	if (end - start == 2) {
		if (myArray[start] > myArray[end - 1])
			swap(myArray[start], myArray[end - 1]);
	}

	mergeSort(myArray, start, start + (end - start) / 2);
	mergeSort(myArray, start + (end - start) / 2, end);

	int* newArray = new int[end - start];
	int newLength = 0;
	int s1 = start;
	int e1 = start + (end - start) / 2;
	int s2 = e1;
	while (newLength < end - start) {
		if (s1 >= e1 || s2 < end && myArray[s2] < myArray[s1]) 
			newArray[newLength++] = myArray[s2++];
		else 
			newArray[newLength++] = myArray[s1++];
	}
	for (int i = start; i < end; ++i)
		myArray[i] = newArray[i - start];
}

void quickSort(int* myArray, const int arrayLength) {
	cout << "Quick sort is starting" << endl;
	if (arrayLength < 2 or myArray == nullptr) return;

	if (arrayLength == 2) {
		if (myArray[0] > myArray[1])
			swap(myArray[0], myArray[1]);
	}
	int right = arrayLength - 1;
	int left = 0;
	int temp; 
	srand(time(NULL));
	int point = myArray[rand() % arrayLength];
	while (left <= right) {
		while (myArray[left] < point) ++left;
		while (myArray[right] > point) --right;

		if (left < right) {
			temp = myArray[left];
			myArray[left++] = myArray[right];
			myArray[right--] = temp;
		}
	}
	
	if (right > 0) quickSort(myArray, right + 1);
	if (arrayLength > left) quickSort(myArray + left, arrayLength - left);
}


void countingSort(int* myArray, const int len, const int min, const int max) {
	cout << "Counting sort is starting" << endl;
	if (min > max or myArray == nullptr) return;

	int *cnt = new int[max - min + 1];

	for (int i = min; i <= max; ++i)
		cnt[i - min] = 0;

	for (int i = 0; i < len; ++i)
		++cnt[myArray[i] - min];

	for (int i = min; i <= max; ++i)
		for (int j = cnt[i - min]; j--;)
			*myArray++ = i;
	delete[] cnt;
}



int main()
{
	int key = 1;
	clock_t timer;
	while (key) {
		int myArray[6] = { 5, 6, 2, 1, 9, 5 };
		int arrayLength = 6;
		printArray(myArray, arrayLength);
		cout << "What insertion mode do you want to use? Choose between:" << endl;
		cout << "insertion" << endl << "bubble" << endl << "selection" << endl 
			 << "quick" << endl << "counting" << endl << "merge" << endl;
		char* insMode = new char[10];
		cin >> insMode;
		if (!strcmp(insMode, "insertion") || !strcmp(insMode, "INSERTION") || !strcmp(insMode, "ins")) {
			timer = clock();
			insertionSort(myArray, arrayLength);
		}
			
		else if (!strcmp(insMode, "bubble") || !strcmp(insMode, "BUBBLE") || !strcmp(insMode, "bub")) {
			timer = clock();
			bubbleSort(myArray, arrayLength);
		}

		else if (!strcmp(insMode, "selection") || !strcmp(insMode, "SELECTION") || !strcmp(insMode, "sel")) {
			timer = clock();
			selectionSort(myArray, arrayLength);
		}
			
		else if (!strcmp(insMode, "quick") || !strcmp(insMode, "QUICK") || !strcmp(insMode, "qui")) {
			cout << "Quick sort is starting" << endl;
			timer = clock();
			quickSort(myArray, arrayLength);
		}
			
		else if (!strcmp(insMode, "counting") || !strcmp(insMode, "COUNTING") || !strcmp(insMode, "count")) {
			timer = clock();
			countingSort(myArray, arrayLength, 0, 10);
		}

		else if (!strcmp(insMode, "merge") || !strcmp(insMode, "MERGE") || !strcmp(insMode, "mer")) {
			timer = clock();
			mergeSort(myArray, 0, arrayLength);
		}
			
		else if (!strcmp(insMode, "zero") || !strcmp(insMode, "ZERO")) {
			timer = clock();
			zeroArray(myArray, arrayLength);
		}
			
		timer = clock() - timer;
		printArray(myArray, arrayLength);
		cout << "Time spent: " << (float)timer / CLOCKS_PER_SEC << endl;
		cout << "Another try? (1/0)" << endl;
		key = 0;
		cin >> key;
	}
    return 0;
}

