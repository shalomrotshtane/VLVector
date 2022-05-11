#include <iostream>
#include "VLVector.hpp"
#include <vector>
#include <cassert>
#include <algorithm>

using std::vector;

void test1() {
	int arr[5] = {12, 21, 31, 45, 77};

	VLVector<int, 16> int_vec;
	for (int i : arr) {
		int_vec.pushBack(i);
	}

	assert(int_vec.size() == 5);
	assert(int_vec.capacity() == 16);

	auto a = std::find(int_vec.begin(), int_vec.end(), 21);
	assert(*a == 21);
	auto b = std::find(int_vec.begin(), int_vec.end(), 76);
	assert(b == int_vec.end());

	int k = 0;
	for (int i:int_vec) {
		assert(i == arr[k]);
		k += 1;
	}



	VLVector<int> rev_vec(int_vec.begin(), int_vec.end());


	k -= 1;
	for (int i:rev_vec) {
		assert(i == arr[k]);
		k--;
	}
	std::cout << "PASSED FIRST TEST" << std::endl;
}

void test2() {
	int arr[17];

	for (int i = 0; i < 17; ++i) {
		arr[i] = i + 20;
	}

	VLVector<int, 16> int_vec;
	for (int i : arr) {
		int_vec.pushBack(i);
	}

	assert(int_vec.size() == 17);
	assert(int_vec.capacity() == 25);





//  auto a = std::find(int_vec.rbegin(), int_vec.rend(), 21);
//  assert(*a == 21);

	int k = 0;
	for (int i:int_vec) {
		assert(i == arr[k]);
		k += 1;
	}

	VLVector<int> rev_vec(int_vec.begin(), int_vec.end());
	k -= 1;
	for (int i:rev_vec) {
		assert(i == arr[k]);
		k--;
	}

	int_vec.popBack();
	assert(int_vec.size() == 16);
	assert(int_vec.capacity() == 16);

	std::cout << "PASSED SECOND TEST" << std::endl;
}

void test3() {
	int arr[17];

	for (int i = 0; i < 17; ++i) {
		arr[i] = i + 20;
	}

	VLVector<int, 16> int_vec1;
	VLVector<int> int_vec2;
	for (int i = 0; i < 17; ++i) {
		int_vec1.pushBack(arr[i]);
		int_vec2.pushBack(arr[i]);
	}

	assert(int_vec1 == int_vec2);

	for (size_t i = 0; i < int_vec1.size(); ++i) {
		assert(arr[i] == int_vec1[i]);
		assert(arr[i] == int_vec2[i]);
		assert(arr[i] == int_vec1.at(i));
		assert(arr[i] == int_vec2.at(i));
	}

	int_vec2.clear();
	assert(int_vec2.size() == 0);
	assert(int_vec2.capacity() == 16);
	assert(int_vec2.isEmpty() == true);
	assert(int_vec2 != int_vec1);

	VLVector<int, 16> int_vec3;
	int_vec3 = int_vec1;
	assert(int_vec1 == int_vec3);

	std::cout << "PASSED THIRD TEST" << std::endl;
}

//void test4() {
//  vector<int> vector;
//  for (int i = 0; i < 5; ++i) {
//    vector.pushBack(i + 20);
//  }
//
//  VLVector<int, 16> int_vec;
//  int_vec.Insert(int_vec.begin(), vector.begin(), vector.end());
//  int k = 0;
//  for (int i:int_vec) {
//    assert(i == vector[k]);
//    k += 1;
//  }
//
//  assert(int_vec.Size() == 5);
//  assert(int_vec.Capacity() == 16);
//
//  int_vec.Insert(int_vec.end(), vector.begin(), vector.end());
//  vector.insert(vector.end(), vector.begin(), vector.end());
//  k = 0;
//  for (int i:int_vec) {
//    assert(i == vector[k]);
//    k += 1;
//  }
//
//  assert(int_vec.Size() == 10);
//  assert(int_vec.Capacity() == 16);
//
//  int_vec.Insert(int_vec.end(), vector.begin(), vector.end());
//  vector.insert(vector.end(), vector.begin(), vector.end());
//  k = 0;
//  for (int i:int_vec) {
//    assert(i == vector[k]);
//    k += 1;
//  }
//
//  std::cout << int_vec.Capacity() << std::endl;
//  assert(int_vec.Size() == 20);
////  assert(int_vec.Capacity() == 30);
//
//  int_vec.Insert(int_vec.begin() + 3, 5);
//  int_vec.Insert(int_vec.begin() + 3, vector.begin(), vector.begin() + 2);
//  vector =
//      {20, 21, 22, 20, 21, 5, 23, 24, 20, 21, 22, 23, 24, 20, 21, 22, 23, 24,
//       20, 21, 22, 23, 24};
//  k = 0;
//  for (int i:int_vec) {
//    assert(i == vector[k]);
//    k += 1;
//  }
//
//  int_vec.Erase(int_vec.begin());
//  vector =
//      {21, 22, 20, 21, 5, 23, 24, 20, 21, 22, 23, 24, 20, 21, 22, 23, 24,
//       20, 21, 22, 23, 24};
//  k = 0;
//  for (int i:int_vec) {
//    assert(i == vector[k]);
//    k += 1;
//  }
//
//  int_vec.Erase(int_vec.begin()+4, int_vec.begin()+6);
//  vector.erase(vector.begin()+4, vector.begin()+6);
//  k = 0;
//  for (int i:int_vec) {
//    assert(i == vector[k]);
//    k += 1;
//  }
//
//  std::cout << "PASSED FOURTH TEST" << std::endl;
//}

void test5() {
	vector<float> vector = {21, 22, 23};
	VLVector<float, 4> float_vec1(vector.begin(), vector.end());
	VLVector<float, 4> float_vec2 = float_vec1;
	assert(float_vec1 == float_vec2);
	assert(float_vec1.size() == 3);
	assert(float_vec1.capacity() == 4);
	int k = 0;
	for (float i:float_vec1) {
		assert(i == vector[k]);
		assert(i == float_vec2[k]);
		k += 1;
	}
	std::cout << "PASSED FIFTH TEST" << std::endl;
}

int main() {
	test1();
	test2();
	test3();
//  test4();
	test5();
	std::cout << "PASSED ALL TESTS!!!" << std::endl;
	return 0;
}
