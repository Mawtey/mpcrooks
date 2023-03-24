
#include <iostream>
#include <vector>
#include <omp.h>
#include <cmath>
#include <thread>

using namespace std;
vector <int> vec_for_clasic;
vector <int> even;
vector <int> odd;
vector <int> result;
bool sorted = true;


void bubble_sort(vector <int>& vec) {
	int size = vec.size();
	for (int i = 0; i < size - 1; i++)
		for (int j = 0; j < size - i - 1; j++)
			if (vec[j] > vec[j + 1])
				swap(vec[j], vec[j + 1]);
}

void mergeVectors() {
	result.clear();
	int k = 0;
	int i = 0;
	int j = 0;
	result.resize(even.size() + odd.size());
	while (i < even.size() && j < odd.size())
	{
		if (even[i] <= odd[j]) {
			result[k++] = even[i++];
		}
		else {
			result[k++] = odd[j++];
		}
	}
	while (i < even.size()) {
		result[k++] = even[i++];
	}
	while (j < odd.size()) {
		result[k++] = odd[j++];
	}
}

void parallelSort() {
	thread th1(bubble_sort, ref(even));
	thread th2(bubble_sort, ref(odd));
	th1.join();
	th2.join();
	thread th3(mergeVectors);
	th3.join();
}

bool unit_test_sort(vector <int> v) {
	for (int i = 0; i < v.size() - 1; i++)
		if (v[i] > v[i + 1])
			return false;
	return true;
}

void generetor(int size) {
	even.clear();
	odd.clear();
	vec_for_clasic.clear();
	for (int i = 0; i < size; i++) {
		int el = rand() % 1000 + 1;
		if (i % 2 == 0) even.push_back(el);
		else odd.push_back(el);
		vec_for_clasic.push_back(el);
	}
}

void printTime() {
	double stime, ftime;
	stime = clock();
	bubble_sort(vec_for_clasic);
	ftime = clock();
	cout << "Time common sort : " << (ftime - stime) / CLOCKS_PER_SEC << endl;
	cout << "Test sort: " << unit_test_sort(vec_for_clasic) << endl;
	cout.precision(8);

	stime = clock();
	parallelSort();
	ftime = clock();
	cout << "Time paralel sort : " << (ftime - stime) / CLOCKS_PER_SEC << endl;
	cout << "Test sort: " << unit_test_sort(result) << endl;
	cout.precision(8);
	cout << endl;
	cout << endl;
}

void test(int n) {
	cout << "---------" << n << "---------" << endl;
	generetor(n);
	printTime();
}

int main() {
	test(10);
	test(100);
	test(1000);
	test(10000);
	test(20000);
	test(30000);
	test(40000);
	test(50000);
	test(60000);
	test(70000);
	test(80000);
	test(90000);
	test(100000);
}
