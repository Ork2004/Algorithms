#pragma once
#include <vector>

using namespace std;

class Heaps
{
	vector<int> arr;

	int left_child(int i) {
		return 2*i + 1;
	}

	int right_child(int i) {
		return 2*i + 2;
	}


};

