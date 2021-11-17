#include <vector>
#include <time.h>
#include <fstream>
#include <iostream>
using namespace std;
float parallel(std::vector<std::vector<float>> a);
float posledovatelna(std::vector<std::vector<float>> a);
void create(int size, std::vector<std::vector<float>>  time_records, string str)

{

	// указатель файла

	fstream fout;



	// открывает существующий CSV-файл или создает новый файл.

	fout.open(str, ios::out);
	// Чтение ввода
	for (int i = time_records.size()-1; i >= 0; i--) {
		fout << size << ", ";
		for (int j = 0; j < time_records[i].size(); j++)
		{
			fout << time_records[i].back() << ", ";

				
			time_records[i].pop_back();
		}
		fout << "\n";
		time_records.pop_back();
		size += 1000;
	}

}
int main()
{
	int n;
	std::vector<std::vector<float>> a = {};
	std::vector<std::vector<float>> posledovatelna_time = {};
	std::vector<std::vector<float>> parallel_time = {};
	srand((unsigned)time(NULL)); //устанавливаем начальную точку генерации
									//случайных чисел в зависимости от времени,
								//необходимо, чтобы числа каждый раз были разные
	scanf_s("%i", &n);
	for (int start=10000; start <= n; )
	{
		posledovatelna_time.push_back({float(start)});
		parallel_time.push_back({float(start)});
		for (int k = 0; k < 100; k++)
		{
			for (int i = 0;i < start;i++)
			{
				a.push_back({});
				for (int j = 0;j < n;j++)
				{
					a[i].push_back(0);
					if (i == j) a[i][j] = 0;
					else if (j < i)
					{
						a[i][j] = rand() % 100; //Берём остаток от деления случайно
						a[j][i] = a[i][j];  // сгенерированного числа на 100 (от 0 до 99)
					}
				}
			}
			posledovatelna_time[posledovatelna_time.size()-1].push_back(posledovatelna(a));
			parallel_time[parallel_time.size()-1].push_back(parallel(a));
			a.clear();
		}
		start += 1000;
	}
	create(10000, posledovatelna_time, "posledovatelna.csv");
	create(10000, parallel_time, "parallel.csv");
	return 0;
}