#include <iostream>
#include <windows.h>
using namespace std;
int n, maxElem, minElem, aver;
int* arr;
DWORD WINAPI min_max(){
	minElem = 0;
	maxElem = 0;
	for (int i = 1; i < n; i++) {
		if (arr[minElem] > arr[i]) {
			minElem = i;
		}
		Sleep(7);
		if (arr[maxElem] < arr[i]) {
			maxElem = i;
		}
		Sleep(7);
	}
	cout << "min = " << arr[minElem] << endl;
	cout << "max = " << arr[maxElem] << endl;
	return 0;
}
DWORD WINAPI average(){
	int sum = 0;
	for (int i = 0; i < n; i++) {
		sum += arr[i];
		Sleep(12);
	}
	aver = sum / n;
	cout << "average = " << aver << endl;
	return 0;
}
int main(){
	cout << "Enter size of array: ";
	cin >> n;
	arr = new int[n];
	cout << "Enter elements of array: " << endl;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	HANDLE hmin_max;
	HANDLE haverage;
	DWORD IDmin_max;
	DWORD IDaverage;
	hmin_max = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)min_max, NULL, 0, &IDmin_max);
	if (hmin_max == NULL) {
		return GetLastError();
	}
	haverage = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)average, NULL, 0, &IDaverage);
	if (haverage == NULL) {
		return GetLastError();
	}
	WaitForSingleObject(hmin_max, INFINITE);
	WaitForSingleObject(haverage, INFINITE);
	CloseHandle(hmin_max);
	CloseHandle(haverage);
	arr[minElem] = aver;
	arr[maxElem] = aver;
	for (int i = 0; i < n; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
	system("pause");
	return 0;
}
