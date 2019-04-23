#pragma once
template <class T>
class Sort
{
private:

	void Swap(T &x, T &y) {
		T temp = x;
		x = y;
		y = temp;
	}

	void QuickSort(T arr[], int first, int last) {
		int lower = first + 1, upper = last;
		Swap(arr[first], arr[(first + last) / 2]);
		T bound = arr[first];
		while (lower <= upper) {
			while (arr[lower] < bound)
				lower++;
			while (bound < arr[upper])
				upper--;
			if (lower < upper)
				Swap(arr[lower++], arr[upper--]);
			else
				lower++;
		}
		Swap(arr[upper], arr[first]);
		if (first < upper-1)
			QuickSort(arr, first, upper-1);
		if (upper+1 < last)
			QuickSort(arr, upper + 1, last);
	}
public:
	Sort() {}
	~Sort() {}
	void InsertionSort(T arr[],int n)
	{
		for (int i = 1; i < n; i++) {
			T temp = arr[i];
			int j ;
			for (j = i; j > 0 && temp < arr[j - 1]; --j)
			{
				arr[j] = arr[j - 1];
			}
			if (j != i)
				arr[j] = temp;
		}
	}

	void Insertion2(T arr[], int n) {
		for (int i = 1; i < n; i++) {
			int j = i;
			T temp = arr[j];
			while (j > 0 && temp < arr[j - 1]) {
				arr[j] = arr[j - 1];
				--j;
			}
			if (j != i)
				arr[j] = temp;
		}
	}
	
	void SelectionSort(T arr[], int n){
		for(int i = 0, j, least; i< n-1; ++i){
			for(j = n-1, least = i; j > i; --j){
				if(arr[j]< arr[least])
					least = j;
			}
			swap(arr[least], arr[i]);
		}
	}

	void BubbleSort(T arr[], int n) {
		for (int i = 0; i < n-1; ++i) {
			for (int j = n - 1; j > i; --j) {
				if (arr[j] < arr[j - 1])
					swap(arr[j], arr[j - 1]);
			}
		}
	}

	void QuickSort(T arr[], int n) {
		if (n < 2) return;
		int max = 0;
		for (int i = 1; i < n; i++) {
			if (arr[max] < arr[i]) {
				max = i;
			}
		}
		Swap(arr[max], arr[n - 1]);
		QuickSort(arr, 0, n - 2);
	}
	
    void MergeSort(T arr[], int n){
    	MergeSort(arr, 0, n);
    }

	void Merge(T arr[], int first, int last)
	{
		T * temp = new T[last - first];
		int mid = (first + last) / 2;
		int i1 = 0, i2 = first, i3 = mid;
		while (i2 < mid && i3 < last) { //while both left and right subarrays of arr contain elements
			if (arr[i2] < arr[i3])
				temp[i1++] = arr[i2++];
			else
				temp[i1++] = arr[i3++];
		}
		//load into temp the remaining elements
		while (i2 < mid) {
			temp[i1++] = arr[i2++];
		}
		while (i3 < last) {
			temp[i1++] = arr[i3++];
		}
		i1 = 0;
		//load to arr the content of temp
		for (int i = first; i < last; i++) {
			arr[i] = temp[i1++];
		}
		delete[] temp;
	}
	//first : first element, last: last element +1
	void MergeSort(T arr[], int first, int last) {
		if (last - first < 2) 
			return;
		int mid = (first + last) / 2;
		MergeSort(arr, first, mid);
		MergeSort(arr, mid, last);
		Merge(arr, first, last);
	}
};

