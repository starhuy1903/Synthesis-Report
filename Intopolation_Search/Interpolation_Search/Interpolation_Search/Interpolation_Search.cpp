#include <iostream>
using namespace std;
int InterPolationSearch(int arr[], int n, int x)
{
    int left = 0;
    int right = n - 1;
    while (left <= right && x >= arr[left] && x <= arr[right])
    {
        double val1 = (double)(x - arr[left]) / (arr[right] - arr[left]);
        int val2 = (right - left);
        int Search = left + val1 * val2;
        
        if (arr[Search] == x)
            return Search;

        if (arr[Search] < x)
            left = Search + 1;
        else
            right = Search - 1;
        
    }
    return -1;
}

int main()
{
    int *arr ;
    arr = new int[1000];
    int n;
    int x;

    cout << "Input size of array: ";
    cin >> n;

    cout << "Input element that you want to search: ";
    cin >> x;

    cout << "Input array: ";
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    int index = InterPolationSearch(arr, n, x);
    cout << endl;
    if (index != -1)
        cout << "At position " << index;
    else
        cout <<"Can't find ";

    delete[]arr;
}