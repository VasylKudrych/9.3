#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>
#include <fstream>


using namespace std;

struct Note
{
	string prizv;
	string name;
	string telephone;
	int date[3];
};

void Create(Note* n, const int N);
void Print(Note* n, const int N);
void PrintW(Note* n, const int N, int k);
void Sort(Note* n, const int N);
int Search(Note* n, const int N, const int month);

int main()
{
	// забезпечення відображення кирилиці:
	SetConsoleCP(1251); // встановлення сторінки win-cp1251 в потік вводу
	SetConsoleOutputCP(1251); // встановлення сторінки win-cp1251 в потік виводу
	int N;
	string prizv;
	string telephone;
	int month;
	int position;
	cout << "Введіть кількість людей: "; cin >> N;
	Note* n = new Note[N];
	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "Виберіть дію:" << endl << endl;
		cout << " [1] - введення даних з клавіатури" << endl;
		cout << " [2] - вивід даних на екран" << endl;
		cout << " [3] - впорядкування масиву структур за прізвищами" << endl;
		cout << " [4] - пошук людей за їх місяцем народження" << endl;
		cout << " [0] - вихід та завершення роботи програми" << endl << endl;
		cout << "Введіть значення: "; cin >> menuItem;
		cout << endl << endl << endl;
		switch (menuItem)
		{
		case 1:
			Create(n, N);
			break;
		case 2:
			Print(n, N);
			break;
		case 3:
			Sort(n, N);
			break;
		case 4:
			cout << "Введіть ключі пошуку:" << endl;
			cout << " Month: ";
			cin >> month;
			cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
			cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок
			cout << endl;
			if ((position = Search(n, N, month)) != -1) {
				cout << "Знайдено людину з заданим знаком в позиції " << position + 1 << endl;
				cout << "Її дані " << endl;
				cout << "Прізвище та ім'я: " + n[position].prizv + " " + n[position].name << endl;
			}
			else
				cout << "Шукану людину не знайдено" << endl;
			break;
		case 0:
			break;
		default:
			cout << "Ви ввели помилкове значення! "
				"Слід ввести число - номер вибраного пункту меню" << endl;
		}
	} while (menuItem != 0);
	return 0;
}

void Create(Note* n, const int N)
{
	for (int i = 0; i < N; i++)
	{
		cout << "Людина No " << i + 1 << ":" << endl;
		cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
		cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок
		cout << " прізвище: "; getline(cin, n[i].prizv);
		cout << " ім'я: "; getline(cin, n[i].name);
		cout << " День народження: "; cin >> n[i].date[0];
		cout << " Місяць народження: "; cin >> n[i].date[1];
		cout << " Рік народження: "; cin >> n[i].date[2];
		cout << endl;
	}
}
void Print(Note* n, const int N)
{
	cout << "============================================================================="
		<< endl;
	cout << "| No | День Народження | Місяць народження | Рік народження | Прізвище | Ім'я | Телефон | "
		<< endl;
	cout << "------------------------------------------------------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(4) << right << i + 1 << " ";
		cout << "| " << setw(17) << left << n[i].date[0]
			<< "| " << setw(17) << left << n[i].date[1]
			<< "| " << setw(17) << left << n[i].date[2]
			<< "| " << setw(6) << left << n[i].prizv
			<< "| " << setw(10) << right << n[i].name
			<< "| " << setw(14) << left << n[i].telephone
			<< "|" << endl;
	}
	cout << "========================================================================================================================"
		<< endl;
	cout << endl;
}

void PrintW(Note* n, const int N, int k)
{
	cout << "========================================================================================================================"
		<< endl;
	cout << "| No | День Народження | Місяць народження | Рік народження | Прізвище | Ім'я | Телефон | "
		<< endl;
	cout << "------------------------------------------------------------------------------------------------------------------------"
		<< endl;

	cout << "| " << setw(4) << right << k + 1 << " ";
	cout << "| " << setw(17) << left << n[k].date[0]
		<< "| " << setw(17) << left << n[k].date[1]
		<< "| " << setw(17) << left << n[k].date[2]
		<< "| " << setw(6) << left << n[k].prizv
		<< "| " << setw(10) << right << n[k].name
		<< "| " << setw(14) << left << n[k].telephone
		<< "|" << endl;

	cout << "========================================================================================================================"
		<< endl;
	cout << endl;
}

void Sort(Note* n, const int N) {
	Note tmp;
	for (int i = 0; i < N; i++)
	{
		for (int i0 = 0; i0 < N - 1; i0++) // метод "бульбашки"
			for (int i1 = 0; i1 < N - i0 - 1; i1++)
				if ((n[i1].prizv > n[i1 + 1].prizv))
				{
					tmp = n[i1];
					n[i1] = n[i1 + 1];
					n[i1 + 1] = tmp;
				}
	}
}
int Search(Note* n, const int N, const int month)
{
	int L = 0, R = N - 1, m;
	do {
		m = (L + R) / 2;
		if (n[m].date[1] == month)
		{
			return m;
		}
		if (n[m].date[1] < month)
		{
			L = m + 1;
		}
		else
		{
			R = m - 1;
		}
	} while (L <= R);
	return -1;
}
