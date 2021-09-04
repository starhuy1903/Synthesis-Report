#include <iostream>

using namespace std;

/* This function takes last element as pivot, places
the pivot element at its correct position in sorted
array, and places all smaller (smaller than pivot)
to left of pivot and all greater elements to right
of pivot */
int partition(int arr[], int low, int high) {
	int pivot = arr[high];
	int i = low - 1;

	for (int j = low; j <= high - 1; j++) {
		// If current element is smaller than the pivot
		if (arr[j] < pivot) {
			i++;
			swap(arr[i], arr[j]);
		}
	}
	swap(arr[i + 1], arr[high]);
	return i + 1;
}

void quickSort(int arr[], int low, int high) {
	if (low < high) {
		/* pi is partitioning index, arr[p] is now
		at right place */
		int pi = partition(arr, low, high);

		/* Separately sort elements before
		partition and after partition */
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}

int max(int a, int b) {
	return (a > b) ? a : b;
}

int maxArea(int h, int w, int horizontalCuts[], int nH, int verticalCuts[], int nV) {
	// Start by sorting the inputs
	quickSort(horizontalCuts, 0, nH - 1);
	quickSort(verticalCuts, 0, nV - 1);

	// Consider the edges first
	long maxHeight = max(horizontalCuts[0], h - horizontalCuts[nH - 1]);
	for (int i = 1; i < nH; i++) {
		// horizontalCuts[i] - horizontalCuts[i - 1] represents the distance 
		// between two adjacent edges, and thus a possible height
		maxHeight = max(maxHeight, horizontalCuts[i] - horizontalCuts[i - 1]);
	}

	// Consider the edges first
	long maxWidth = max(verticalCuts[0], w - verticalCuts[nV - 1]);
	for (int i = 1; i < nV; i++) {
		// verticalCuts[i] - verticalCuts[i - 1] represents the distance between
		// two adjacent edges, and thus a possible width
		maxWidth = max(maxWidth, verticalCuts[i] - verticalCuts[i - 1]);
	}

	return (int)((maxWidth * maxHeight) % (1000000007));
}

int main() {
	int horizontalCuts[] = { 3, 1 };
	int nH = sizeof(horizontalCuts) / sizeof(horizontalCuts[0]);

	int verticalCuts[] = { 1 };
	int nV = sizeof(verticalCuts) / sizeof(verticalCuts[0]);

	int area = maxArea(5, 4, horizontalCuts, nH, verticalCuts, nV);

	cout << "Max area = " << area << endl;
}