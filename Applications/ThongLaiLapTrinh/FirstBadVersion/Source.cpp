#include <iostream>
using namespace std;


// The API isBadVersion is defined for you.
// bool isBadVersion(int version);

int n = 5, bad = 4;
bool isBadVersion(int version) {
    return version >= bad ? true : false;
}

int firstBadVersion(int n) {
    int left = 1, right = n;
    int mid;
    while (left <= right)
    {
        mid = left + (right - left) / 2;
        if (isBadVersion(mid))
            right = mid - 1;
        else
            left = mid + 1;
    }

    return left;
}

int main()
{
    cout << firstBadVersion(n);

    return 0;
}