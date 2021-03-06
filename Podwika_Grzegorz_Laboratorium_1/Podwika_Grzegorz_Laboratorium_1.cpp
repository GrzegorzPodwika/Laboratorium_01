// Grzegorz Podwika - wtorek 11:00

#include "pch.h"
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int loadCorrectNumberOfDataSets();
int loadCorrectNumberOfRowsOrColumns();
int **createTable(int rows, int columns);
void deleteTable(int **t, int rows);
void insertDataToTable(int **tab, int rows, int columns);
int searchHighestSum(int **tab, int rows, int columns);
void showMaxSums(int *TabOfSum, int length);
void computeMaxSumsAndShowResults();

//**************************************************************************************************************************************************************************************************************************************************
int main()
{
	computeMaxSumsAndShowResults();
	getchar();
	cin.ignore();
	return 0;
}
//**************************************************************************************************************************************************************************************************************************************************

//funkcja sprawdzajaca czy liczba zestawow danych jest poprawna
int loadCorrectNumberOfDataSets()
{
	int sets{};
	bool flag = false;

	while (!flag)
	{
		cin >> sets;
		if (sets > 0)
			flag = true;
	}

	return sets;
}

//funkcja sprawdzajaca czy liczba wierszy lub kolumn jest z poprawnego zakresu
int loadCorrectNumberOfRowsOrColumns()
{
	int number{};
	bool flag = false;

	while (!flag)
	{
		cin >> number;
		if (number >= 1 && number <= 100)
			flag = true;
		else
			cout << "Bledne dane, podaj liczbe calkowita z zakresu 1 do 100!: ";
	}

	return number;
}

//funkcja tworzaca dynamiczna tablice dwuwymiarowa
int **createTable(int rows, int columns)
{
	int **T = nullptr;
	try
	{
		T = new int*[rows];
	}
	catch (bad_alloc)
	{
		cout << "Nie udalo sie utworzyc tablicy!";
		exit(0);
	}

	for (int i = 0; i < rows; i++) {
		try
		{
			T[i] = new int[columns];
		}
		catch (bad_alloc)
		{
			cout << "Nie udalo sie wypelnic tablicy!";
		}
	}
	return T;
}

//funkcja zwalniajaca pamiec po dynamicznej tablicy dwuwymiarowej
void deleteTable(int ** t, int rows)
{
	for (int i = 0; i < rows; i++) {
		delete[]t[i];
	}
	delete[] t;
}

//funkcja wypelniajaca tablice 2D wartosciami podanymi przez uzytkownika
void insertDataToTable(int ** tab, int rows, int columns)
{
	int number;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			cin >> number;
			if (number > pow(-2, 15) && number < pow(2, 15))
				tab[i][j] = number;
			else 
			{
				cout << "Liczba musi byc z zakresu -2^15 do 2^15!";
				tab[i][j] = 0;
			}
		}
	}
}

//funkcja szukajaca najwiekszej sumy w podtablicy wyslanej przez uzytkownika tablicy
int searchHighestSum(int ** tab, int rows, int columns)
{
	int maxSum{};
	int tmpSum{};

	int upperEdge{};
	int leftEdge{};

	int positionOfX{};
	int positionOfY{};

	for (upperEdge = 0; upperEdge < rows; upperEdge++)
	{
		for (leftEdge = 0; leftEdge < columns; leftEdge++)
		{
			for (positionOfY = 0; positionOfY < rows - upperEdge; positionOfY++)
			{
				for (positionOfX = 0; positionOfX < columns - leftEdge; positionOfX++)
				{
					tmpSum = 0;
					
					for (int i = 0 + upperEdge; i < rows - positionOfY; i++)
					{
						for (int j = 0 + leftEdge; j < columns - positionOfX; j++)
						{
							tmpSum += tab[i][j];
						}
					}
					
					if (tmpSum > maxSum)
						maxSum = tmpSum;
				}
			}
		}
	}

	if (maxSum < 0)
		maxSum = 0;

	return maxSum;
}

//funkcja pomocnicza pokazujaca maksymalne sumy na ekran
void showMaxSums(int * TabOfSum, int length)
{
	for (int i = 0; i < length; i++)
	{
		cout << TabOfSum[i] << endl;
	}

	delete[] TabOfSum;
}

//glowna funkcja zarzadzajaca obliczaniem i pokazywaniem na ekran wszystkich wartosci
void computeMaxSumsAndShowResults()
{
	int numberOfDataSets = loadCorrectNumberOfDataSets();
	int *sumArray = new int[numberOfDataSets];

	for (int i = 0; i < numberOfDataSets; i++)
	{
		int rows = loadCorrectNumberOfRowsOrColumns();
		int columns = loadCorrectNumberOfRowsOrColumns();
		int **tabNumbers = createTable(rows, columns);

		insertDataToTable(tabNumbers, rows, columns);
		sumArray[i] = searchHighestSum(tabNumbers, rows, columns);
		deleteTable(tabNumbers, rows);
	}

	showMaxSums(sumArray, numberOfDataSets);
}

