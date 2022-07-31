#include <iostream>
#include "vl_vector.h"
#include <vector>
#include <cassert>
#include <chrono>

using std::vector;

void test1() {

	VLVector<int, 16> vlVector;

	for(int i = 0; i < 16; i++){
		vlVector.pushBack(i);
	}

	for(int i = 0; i < 16; i++){
		assert(i == vlVector[i]);;
	}

	assert(vlVector.size() == 16);
	assert(vlVector.capacity() == 16);

	for(int i = 16; i < 1600; i++){
		vlVector.pushBack(i);
	}

	for(int i = 0; i < 1600; i++){
		assert(i == vlVector[i]);;
	}

	for(int i = 0; i < 1600; i++){
		assert(i == vlVector.at(i));
	}

	assert(vlVector.size() == 1600);

	for(int i = 0; i < 600; i++){
		vlVector.popBack();
	}

	assert(vlVector.size() == 1000);

	vlVector.clear();
	assert(vlVector.size() == 0);

	assert(vlVector.isEmpty());

	std::cout << "PASSED FIRST TEST" << std::endl;
}


void test2() {
	int arr[230];

	for (int i = 0; i < 230; ++i) {
		arr[i] = i + 50;
	}

	vector<int> vector;
	VLVector<int, 16> vlVector;
	for (int i : arr) {
		vector.push_back(i);
	}

	vlVector.insert(vlVector.begin(), vector.begin(), vector.end());

	for (int i = 0; i < 230; ++i) {
		assert(vlVector[i] == vector[i]);
	}

	assert(vlVector.size() == 230);

	vlVector.erase(vlVector.begin(), vlVector.end() - 200);

	assert(vlVector.size() == 200);

	for (int i = 0; i < 200; ++i) {
		assert(vlVector[i] == i + 80);
	}

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
	assert(int_vec2.isEmpty());
	assert(int_vec2 != int_vec1);

	VLVector<int, 16> int_vec3;
	int_vec3 = int_vec1;
	assert(int_vec1 == int_vec3);

	std::cout << "PASSED THIRD TEST" << std::endl;
}


void test4() {
  vector<int> vector;
  for (int i = 0; i < 5; ++i) {
    vector.push_back(i + 20);
  }

  VLVector<int, 16> int_vec;
  int_vec.insert(int_vec.begin(), vector.begin(), vector.end());

  int k = 0;
  for (int i:int_vec) {
    assert(i == vector[k]);
    k += 1;
  }

  assert(int_vec.size() == 5);
  assert(int_vec.capacity() == 16);

  int_vec.insert(int_vec.end(), vector.begin(), vector.end());
  vector.insert(vector.end(), vector.begin(), vector.end());
  k = 0;
  for (int i:int_vec) {
    assert(i == vector[k]);
    k += 1;
  }

  assert(int_vec.size() == 10);
  assert(int_vec.capacity() == 16);

  int_vec.insert(int_vec.end(), vector.begin(), vector.end());
  vector.insert(vector.end(), vector.begin(), vector.end());
  k = 0;
  for (int i:int_vec) {
    assert(i == vector[k]);
    k += 1;
  }

  assert(int_vec.size() == 20);
  assert(int_vec.capacity() == 25);

  int_vec.insert(int_vec.begin() + 3, 5);
  int_vec.insert(int_vec.begin() + 3, vector.begin(), vector.begin() + 2);
  vector =
      {20, 21, 22, 20, 21, 5, 23, 24, 20, 21, 22, 23, 24, 20, 21, 22, 23, 24,
       20, 21, 22, 23, 24};
  k = 0;
  for (int i:int_vec) {
    assert(i == vector[k]);
    k += 1;
  }

  int_vec.erase(int_vec.begin());
  vector =
      {21, 22, 20, 21, 5, 23, 24, 20, 21, 22, 23, 24, 20, 21, 22, 23, 24,
       20, 21, 22, 23, 24};
  k = 0;
  for (int i:int_vec) {
    assert(i == vector[k]);
    k += 1;
  }

  int_vec.erase(int_vec.begin()+4, int_vec.begin()+6);
  vector.erase(vector.begin()+4, vector.begin()+6);
  k = 0;
  for (int i:int_vec) {
    assert(i == vector[k]);
    k += 1;
  }

  std::cout << "PASSED FOURTH TEST" << std::endl;
}

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

void test6(){

	vector<float> vector;
	VLVector<float, 120000> vlvector;

	std::cout << "Starting testing vector: " << std::endl;
	auto start = std::chrono::system_clock::now();
	for (int i = 0; i < 120000; ++i) {
		vector.push_back(i);
	}
	vector.erase(vector.begin(), vector.end());
	auto end = std::chrono::system_clock::now();

	std::chrono::duration<double> elapsed_seconds = end-start;
	std::cout << "the test took: " << elapsed_seconds.count() << " seconds" << std::endl;

	std::cout << "Starting testing vlvector: " << std::endl;
	start = std::chrono::system_clock::now();
	for (int i = 0; i < 120000; ++i) {
		vlvector.pushBack(i);
	}
	vlvector.erase(vlvector.begin(), vlvector.end());
	end = std::chrono::system_clock::now();

	elapsed_seconds = end-start;
	std::cout << "the test took: " << elapsed_seconds.count() << " seconds" << std::endl;

}


int main() {
	test1();
	test2();
	test3();
	test4();
	test5();
	test6();
	std::cout << "PASSED ALL TESTS!!!" << std::endl;

}
