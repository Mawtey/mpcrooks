#include <iostream>
#include <vector>
#include <omp.h>
#include <cmath>
#include <thread>

using namespace std;
vector <int> vec, veccopy;
bool sorted = true;

void evensEl() {
	int n = vec.size();
	//for (int i = 0; i < 10; i++)
	//	cout << "ID = " << this_thread::get_id() << "  Сhet " << i << " " << endl;
	for (int i = 0; i < n; i++) {
		if (i % 2 == 0)
		for (int j = 0; j < n; j += 2)
			if (j < n - 1)
				if (vec[j] > vec[j + 1]) {
					swap(vec[j], vec[j + 1]);
					sorted = true;
				}
	}
}

void oddEl() {
	int n = vec.size();
	//for (int i = 0; i < 10; i++)
	//	cout << "ID = " << this_thread::get_id() << "  Chet " << i << " " << endl;
	for (int i = 1; i < n; i++) {
		if (i % 2 != 0)
			for (int j = 1; j < n; j += 2)
				if (j < n - 1)
					if (vec[j] > vec[j + 1]) {
						swap(vec[j], vec[j + 1]);
						sorted = true;
					}
	}
}

void parallelSort() {
	thread th1(evensEl);
	thread th2(oddEl);
	th1.join();
	th2.join();
}

bool unit_test_sort(vector <int> v) {
	for (int i = 0; i < v.size() - 1; i++)
		if (v[i] > v[i + 1])
			return false;
	return true;
}

vector <int> generetor(int size) {
	vector <int> v;
	for (int i = 0; i < size; i++) v.push_back(rand() % 1000 + 1);
    return v;
}

void classicSort() {
	int n = veccopy.size();
	for (int i = 0; i <= n - 2; i += 2) {
		if (veccopy[i] > veccopy[i + 1]) {
			swap(veccopy[i], veccopy[i + 1]);
			sorted = true;
		}
	}
	for (int i = 1; i <= n - 2; i += 2) {
		if (veccopy[i] > veccopy[i + 1]) {
			swap(veccopy[i], veccopy[i + 1]);
			sorted = true;
		}
	}
}

void printTime() {
	//обычная сортировка
	double stime, ftime;
	stime = clock();
	sorted = true;
	while (sorted) {
		sorted = false;
		classicSort();
	}
	ftime = clock();
	cout << "Time common sort : " << (ftime - stime) / CLOCKS_PER_SEC << endl;
	cout << "Test sort: " << unit_test_sort(veccopy) << endl;
	cout.precision(8);

	//соритровка с потоками
	sorted = true;
	stime = clock();
	while (sorted) {
		sorted = false;
		parallelSort();
	}
	ftime = clock();
	cout << "Time paralel sort : " << (ftime - stime) / CLOCKS_PER_SEC << endl;
	cout << "Test sort: " << unit_test_sort(vec) << endl;
	cout.precision(8);
	cout << endl;
	cout << endl;
}

//Тест для 10 случайных эл-ов
void test10(){
	cout << "---------10-------------" << endl;
	veccopy = vec = generetor(10);
	printTime();
}

//Тест для 100 случайных эл-ов
void test100() {
	cout << "---------100-------------" << endl;
	veccopy = vec = generetor(100);
	printTime();
}

//Тест для 1000 случайных эл-ов
void test1000() {
	cout << "---------1000-------------" << endl;
	veccopy = vec = generetor(1000);
	printTime();
}

//Тест для 10000 случайных эл-ов
void test10000() {
	cout << "---------10000-------------" << endl;
	veccopy = vec = generetor(10000);
	printTime();
}

//Тест для 100000 случайных эл-ов
void test100000() {
	cout << "---------100000-------------" << endl;
	veccopy = vec = generetor(100000);
	printTime();
}

void test1000000() {
	cout << "---------1000000-------------" << endl;
	veccopy = vec = generetor(1000000);
	printTime();
}

int main() {
	test10();
	test100();
	test1000();
	test10000();
	test100000();
	test1000000();
}