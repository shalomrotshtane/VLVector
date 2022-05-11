#ifndef VLVECTOR_HPP
#define VLVECTOR_HPP

#include <stdexcept>

#include <cstring>

/**
 * this class represent VLVectror, the VLVectror is a smart vector that using the stack memory and
 * the heap memory, depends what is faster for him.
 * @tparam T - Type of the elements.
 * @tparam C - Static capacity, under that the vector will use the stack memory only.
 */
template<typename T, size_t C = 16>
class VLVector {

private:

	size_t STATIC_CAPACITY;

	int vectorSize;

	int vectorCapacity;

	bool usingHeap = false;

	T stackVector[C];

	T *heapVector;

	/**
	 * this function calculate the new capacity by the following formula.
	 * cap(currentSize) = C if  currentSize + 1 <= C, (3 * (currentSize + 1)) / 2 else.
	 * @param currentSize - the size of the current vector
	 * @return int - the new capacity.
	 */
	int _newCapCalc(int currentSize) {
		return ((3 * (currentSize + 1)) / 2);
	}

	/**
	 * this function get pointer to array and copy that array to a new array in the heap and delete
	 * the old array
	 * @param array - the array that we copy the data from.
	 * @return T * - pointer to the new array in the heap.
	 */
	T *_newHeapVector(T *array) {

		T *temp;
		T *vector = usingHeap ? heapVector : stackVector;
		temp = new T[vectorCapacity];

		for (int i = 0; i < vectorSize; ++i) {
			temp[i] = vector[i];
		}

		if (usingHeap) {
			delete[] array;
		}

		usingHeap = true;
		return temp;
	}

	/**
	 * this function copy the heap array to the stack array and delete the heap array.
	 * calling to this function only if (vectorSize <= STATIC_CAPACITY)
	 */
	void _copyHeapToStack() {
		for (int i = 0; i < (int) STATIC_CAPACITY; ++i) {
			stackVector[i] = heapVector[i];
		}

		delete[] heapVector;
		heapVector = nullptr;
		usingHeap = false;
	}


public:

	//represent iterator of the VLVector.
	typedef T *iterator;

	//represent const iterator of the VLVector.
	typedef const T *constIterator;


//----------------------------- constructors -------------------------------//


	/**
	 * default constructor that initialize empty vector
	 */
	VLVector() : STATIC_CAPACITY(C), vectorCapacity(C), vectorSize(0), heapVector(nullptr) {}


	/**
	 * copy constructor.
	 */
	VLVector(const VLVector &other) : STATIC_CAPACITY(C), vectorCapacity(other.capacity()),
									  vectorSize(other.size()), heapVector(nullptr) {

		if (vectorSize > (int) STATIC_CAPACITY) {
			heapVector = new T(vectorCapacity);
			usingHeap = true;

			for (int i = 0; i < vectorCapacity; ++i) {
				heapVector[i] = other[i];
			}

		} else {

			for (int i = 0; i < vectorCapacity; ++i) {
				stackVector[i] = other[i];
			}
		}
	}

	/**
	 * constructor that get's iterator(interval) of T value and keeping the value in the vector.
	 * @tparam InputIterator - the iterator
	 * @param first - the first value
	 * @param last - the last value
	 */
	template<class InputIterator>
	VLVector(InputIterator first, InputIterator last): STATIC_CAPACITY(C), vectorCapacity(C),
													   vectorSize(0), heapVector(nullptr) {

		InputIterator k = first;
		while (k != last) {
			this->pushBack(*k);
			k++;
		}
	}

	/**
	 * destructor, delete the memory in case the class used the heap.
	 */
	~VLVector() {
		if (!usingHeap) {
			delete[](heapVector);
			heapVector = NULL;
		}
	}


//--------------------   methods   -------------------//


	/**
	 * this method return the number of items that we have in the stackVector.
	 * @return vectorSize - the number of items that we have in the stackVector.
	 */
	size_t size() const {
		return vectorSize;
	}

	/**
	 * this method return the capacity size of the stackVector.
	 * @return vectorCapacity - the capacity size of the stackVector.
	 */
	size_t capacity() const {
		return vectorCapacity;
	}

	/**
	 * this method return if the stackVector empty or not.
	 * @return true - if the stackVector is empty, false - otherwise.
	 */
	bool isEmpty() const {
		return vectorSize == 0;
	}

	/**
	 * this method get index i and return the item in the i place at the stackVector,
	 * if the index is not legal the method will throw exception.
	 * @param i - the index.
	 * @return T - the item in the i place at the stackVector.
	 */
	T &at(const int i) {
		if (0 <= i && i < vectorSize) {
			return (*this)[i];
		} else {
			throw std::out_of_range("ERROR: index out of range.");
		}
	}

	/**
 	 * this method get index i and return the item in the i place at the stackVector,
	 * if the index is not legal the method will throw exception.
	 * @param i - the index.
	 * @return T - the item in the i place at the stackVector.
	 */
	T at(const int i) const {
		if (0 <= i && i < vectorSize) {
			return (*this)[i];
		} else {
			throw std::out_of_range("ERROR: index out of range.");
		}
	}

	/**
	 * this method get's object and add it in the Vector after the last object in the Vector.
	 * @param object - the object to add.
	 */
	void pushBack(const T object) {

		if (vectorSize + 1 <= (int) STATIC_CAPACITY) {
			stackVector[vectorSize] = object;
		} else if (vectorSize + 1 <= vectorCapacity) {
			heapVector[vectorSize] = object;
		} else {

			vectorCapacity = _newCapCalc(vectorSize);
			heapVector = usingHeap ? _newHeapVector(heapVector) : _newHeapVector(stackVector);
			heapVector[vectorSize] = object;
		}
		vectorSize++;
	}

	/**
	 * this method insert object to the place before the iterator that we get.
	 * @tparam Iterator - the object iterator that we getting.
	 * @param position - iterator that point to the place in the vector that we want to add the object
	 * before im
	 * @param object - the object that we add to the vector.
	 * @return iterator - iterator that point to the new place of the object.
	 */
	iterator insert(iterator position, T object) {

		if (begin() == end()) {
			PushBack(*position);
			position++;
			return position;
		}

		VLVector<T, C> tempVec;
		int i = 0;

		iterator k = begin();

		while (k != position) {
			tempVec.PushBack((*this)[i]);
			i++;
			k++;
		}

		iterator toReturn = k;

		tempVec.PushBack(object);
		i++;

		while (k != end()) {
			tempVec.PushBack((*this)[i]);
			i++;
			k++;
		}

		*this = tempVec;
		return toReturn;
	}

	/**
	 * this method insert interval of object's to the place before the iterator that we get.
	 * @tparam Iterator - the object iterator that we getting.
	 * @param first - iterator that point to the first position in  the interval.
	 * @param last - iterator that point to the last position in  the interval.
	 * @param position - iterator that point to the position position.
	 * @return iterator - iterator that point to the new place of the object.
	 */
	template<class InputIterator>
	iterator insert(iterator position, const InputIterator first, const InputIterator last) {
		if (first == last) {
			PushBack(*position);
			position++;
			return position;
		}

		VLVector<T, C> tempVec;
		int i = 0;

		iterator k = begin();

		while (k != position) {
			tempVec.PushBack((*this)[i]);
			i++;
			k++;
		}

		iterator toReturn = k;
		InputIterator j = first;

		while (j != last) {
			tempVec.PushBack(*j);
			i++;
			j++;
		}

		while (k != end()) {
			tempVec.PushBack((*this)[i]);
			i++;
			k++;
		}

		*this = tempVec;
		return toReturn;
	}

	/**
	 * this function get iterator and delete the object that the iterator point.
	 * @param position - iterator that point on the object.
	 * @return iterator - iterator that point to the object from the right to object that we
	 * delete.
	 */
	iterator erase(iterator position) {

		VLVector<T, C> tempVec;
		int i = 0;

		iterator k = begin();

		while (k != position){
			tempVec.PushBack((*this)[i]);
			i++;
			k++;
		}

		i++;
		k++;

		iterator toReturn = k;

		while (k != end()){
			tempVec.PushBack((*this)[i]);
			i++;
			k++;
		}

		*this = tempVec;
		return toReturn;
	}

	/**
	 * this function get interval iterator's and delete the object that the iterator point.
	 * @param first - iterator to the first place in the interval.
	 * @param last - iterator to the last place in the interval.
	 * @return iterator - iterator that point to the object from the right to object's that we
	 * delete.
	 */
	iterator erase(iterator first, iterator last) {
		VLVector<T, C> tempVec;
		int i = 0;

		iterator k = begin();

		while (k != first) {
			tempVec.PushBack((*this)[i]);
			i++;
			k++;
		}

		iterator j = first;

		while (j != last) {
			j++;
			i++;
			k++;
		}

		iterator toReturn = k;

		while (k != end()) {
			tempVec.PushBack((*this)[i]);
			i++;
			k++;
		}

		*this = tempVec;
		return toReturn;
	}

	/**
	 * this method delete the all vector.
	 */
	void clear() {

		vectorSize = 0;
		if (usingHeap) {
			delete[](heapVector);
			heapVector = nullptr;
		}
	}

	/**
	 * this method delete the object T in the last place in the stackVector(vectorSize place)
	 */
	void popBack() {
		vectorSize--;

		if (vectorSize == (int) STATIC_CAPACITY) {
			_copyHeapToStack();
		}
	}

	/**
	 * this method return pointer to the data structure that old the vector data.
	 * @return T * - pointer to the data structure that old the vector data.
	 */
	T *data() {
		return usingHeap ? heapVector : stackVector;
	}

	/**
	 * this method return pointer to the data structure that old the vector data.
	 * @return T * - pointer to the data structure that old the vector data.
	 */
	T data() const {
		return usingHeap ? *heapVector : *stackVector;
	}

	/**
	 * this method return the iterator in the begin place
	 * @return - iterator of the begin place
	 */
	iterator begin() {
		return usingHeap ? iterator(&heapVector[0]) : iterator(&stackVector[0]);
	}

	/**
	 * this method return the const iterator in the begin place
	 * @return - const_iterator of the begin place
	 */
	constIterator begin() const {
		return usingHeap ? iterator(&heapVector[0]) : iterator(&stackVector[0]);
	}

	/**
 	 * this method return the const iterator in the begin place
	 * @return - const_iterator of the begin place
	 */
	constIterator cbegin() const {
		return usingHeap ? iterator(&heapVector[0]) : iterator(&stackVector[0]);
	}

	/**
	 * this method return the iterator of the end place + 1
	 * @return - iterator of end place + 1
	 */
	iterator end() {
		return begin() + vectorSize;
	}

	/**
	 * this method return the iterator of the end place + 1
	 * @return - const iterator of end place + 1
	 */
	constIterator end() const {
		return begin() + vectorSize;
	}

	/**
	 * this method return the iterator of the end place + 1
	 * @return - const iterator of end place + 1
	 */
	constIterator cend() const {
		return cbegin() + vectorSize;
	}


//------------------------ operators -----------------------//


	/**
	 * operator that compere between 2 vectors.
	 * @param other - the stackVector that we compare to.
	 * @return true if there equal, false otherwise.
	 */
	VLVector &operator=(const VLVector &rhs) noexcept {
		if (this == &rhs) {
			return *this;
		}

		(*this).STATIC_CAPACITY = rhs.STATIC_CAPACITY;
		(*this).vectorCapacity = rhs.capacity();
		(*this).vectorSize = rhs.vectorSize;
		(*this).heapVector = nullptr;

		if (vectorSize + 1 <= (int) STATIC_CAPACITY) {
			for (int i = 0; i < vectorCapacity; ++i) {
				stackVector[i] = rhs[i];
			}
		} else {
			heapVector = new T(vectorCapacity);
			for (int i = 0; i < vectorCapacity; ++i) {
				heapVector[i] = rhs[i];
			}
		}

		return *this;
	}

	/**
 	 * operator that get's index return the object in the i place at the stackVector.
 	 * @param i - the index.
 	 * @return the object in the i place at the stackVector.
 	 */
	T &operator[](const int i) noexcept(false) {
		return usingHeap ? heapVector[i] : stackVector[i];
	}

	/**
	 * operator that get's index return the object in the i place at the stackVector.
	 * @param i - the index.
	 * @return the object in the i place at the stackVector.
	 */
	T operator[](const int i) const noexcept(false) {
		return usingHeap ? heapVector[i] : stackVector[i];
	}

	/**
	 * operator that compere between 2 vectors.
	 * @param other - the stackVector that we compare to.
	 * @return true if there equal, false otherwise.
	 */
	bool operator==(const VLVector &rhs) const noexcept{
		if (vectorSize != rhs.vectorSize) {
			return false;
		}

		for (int i = 0; i < vectorSize; ++i) {
			if ((*this)[i] != rhs[i]) {
				return false;
			}
		}

		return true;
	}

	/**
	 * operator that compere between 2 vectors.
	 * @param other - the stackVector that we compare to.
	 * @return true if there are not equal, false otherwise.
 	 */
	bool operator!=(const VLVector &rhs) const noexcept{
		return !(*this == rhs);
	}
};

#endif //VLVECTOR_HPP
