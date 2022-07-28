#include <iostream>
#include <math.h>

/**
 * this class represent VLVectror that is a smart vector that using in the stack memory and in the
 * heap memory depends what is faster for im.
 * @tparam T - generic value that represent the object that we store in the vector.
 * @tparam C - the static capacity that represent the max size of element the the vector use in the
 * stack memory.
 */
template<class T, size_t StaticCapacity = 16>
class VLVector {

private:

	T _stackArray[StaticCapacity];
	T *_heapArray;
	const size_t _sCapacity;
	size_t _size{};
	size_t _capacity{};
	bool _usingStack{};

	/**
	 * this function calculate the new capacity by thr formula that we got.
	 * @param currentSize - the size of the current vector
	 * @return int - capacity by thr formula that we got.
	 */
	size_t _capC(size_t size, size_t k) const noexcept {
		size_t temp = ((3 * (size + k)) / 2);
		return size + k <= _sCapacity ? _sCapacity : floor(temp);
	}

	/**
	 * this function copy from the heap array to the stack array and delete the heap array.
	 * calling to this function only if (vectorSize <= STATIC_CAPACITY)
	 */
	void _copyArrays(T *first, const T *second) {
		for (int i = 0; i < _size; ++i) {
			first[i] = second[i];
		}
	}

	class Reverse_iterator {

	private:
		T *pointer_;

	public:

		Reverse_iterator() : pointer_() {}

		explicit Reverse_iterator(T *pointer) : pointer_(pointer) {}

		Reverse_iterator(const Reverse_iterator *other) : pointer_(other->pointer_)
		{}

		T &operator*()
		{
			return *pointer_;
		}

		Reverse_iterator &operator++()
		{
			--pointer_;
			return *this;
		}

		Reverse_iterator operator++(int)
		{
			Reverse_iterator temp = *this;
			--pointer_;
			return temp;
		}

		Reverse_iterator &operator--()
		{
			return ++pointer_;
		}

		Reverse_iterator operator--(int)
		{
			Reverse_iterator temp = *this;
			++pointer_;
			return temp;
		}

		bool operator==(const Reverse_iterator &other) const
		{
			return pointer_ == other.pointer_;
		}

		bool operator!=(const Reverse_iterator &other) const
		{
			return !(*this == other);
		}


	};

public:

	typedef Reverse_iterator reverse_iterator;

	typedef T *iterator;

	typedef const T *const_iterator;

	/**
	 * default constructor that initialize empty vector
	 */
	VLVector() : _usingStack(true), _size(0), _capacity(StaticCapacity), _sCapacity(StaticCapacity) {}

	VLVector(const VLVector &other) : _usingStack(other._usingStack), _size(other._size), _capacity(other._capacity), _sCapacity(other._sCapacity)  {

		if (_usingStack) {
			_copyArrays(_stackArray, other._stackArray);
		} else {
			_heapArray = new T[_capacity];
			_copyArrays(_heapArray, other._heapArray);
		}
	}

	template<class InputIterator>
	VLVector(InputIterator first, InputIterator last) :_usingStack(true), _size(0), _capacity(StaticCapacity), _sCapacity(StaticCapacity) {

		InputIterator begin = first;

		while (begin != last) {
			this->pushBack(*begin);
			++begin;
		}
	}

	~VLVector() {
		if (!_usingStack) {
			delete[] _heapArray;
			_heapArray = nullptr;
		}
	}

	size_t size() const noexcept {
		return _size;
	}

	size_t capacity() const noexcept {
		return _capacity;
	}

	bool isEmpty() const noexcept{
		return _size == 0;
	}

	T at(int i) const {
		if (i < 0 || _size <= i) {
			throw std::out_of_range("ERROR: index out of range.");
		} else {
			return (*this)[i];
		}
	}

	T &at(int i) noexcept(false) {
		if (i < 0 || _size <= i) {
			throw std::out_of_range("ERROR: index out of range.");
		} else {
			return (*this)[i];
		}
	}

	void pushBack(const T &element) noexcept {
		if (_size < _capacity) {

			if (_size < _sCapacity) {
				_stackArray[_size] = element;

			} else {

				_heapArray[_size] = element;
			}
			_size++;

		} else {

			if (_usingStack) {

				_capacity = _capC(_size, 1);
				_heapArray = new T[_capacity];
				_copyArrays(_heapArray, _stackArray);
				pushBack(element);

			} else {

				_capacity = _capC(_size, 1);
				T *temp = new T[_capacity];
				_copyArrays(temp, _heapArray);
				delete[] _heapArray;
				_heapArray = temp;
				pushBack(element);
			}

			_usingStack = false;
		}
	}

	iterator &insert(iterator position, const T &element) noexcept {
		if (begin() == end()) {
			pushBack(*position);
			position++;
			return position;
		}

		VLVector<T, StaticCapacity> tempVec;
		int i = 0;

		iterator k = begin();

		while (k != position) {
			tempVec.pushBack((*this)[i]);
			i++;
			k++;
		}

		iterator toReturn = k;

		tempVec.pushBack(element);
		i++;

		while (k != end()) {
			tempVec.pushBack((*this)[i]);
			i++;
			k++;
		}

		*this = tempVec;
		return toReturn;
	}

	template<class InputIterator>
	iterator &insert(iterator position, InputIterator first, InputIterator last) noexcept {
		if (first == last) {
			pushBack(*position);
			position++;
			return position;
		}

		VLVector<T, StaticCapacity> tempVec;
		int i = 0;

		iterator k = begin();

		while (k != position) {
			tempVec.pushBack((*this)[i]);
			i++;
			k++;
		}

		iterator toReturn = k;
		InputIterator j = first;

		while (j != last) {
			tempVec.pushBack(*j);
			i++;
			j++;
		}

		while (k != end()) {
			tempVec.pushBack((*this)[i]);
			i++;
			k++;
		}

		*this = tempVec;

		return toReturn;
	}

	iterator &erase(iterator position) noexcept {
		VLVector<T, StaticCapacity> tempVec;
		int i = 0;

		iterator k = begin();

		while (k != position) {
			tempVec.pushBack((*this)[i]);
			i++;
			k++;
		}

		i++;
		k++;

		iterator toReturn = k;

		while (k != end()) {
			tempVec.pushBack((*this)[i]);
			i++;
			k++;
		}

		*this = tempVec;

		return toReturn;
	}

	iterator &erase(iterator first, iterator last) noexcept {
		VLVector<T, StaticCapacity> tempVec;
		int i = 0;

		iterator k = begin();

		while (k != first) {
			tempVec.pushBack((*this)[i]);
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
			tempVec.pushBack((*this)[i]);
			i++;
			k++;
		}

		*this = tempVec;

		return toReturn;
	}

	void popBack() noexcept {
		_size--;

		if ((_size <= _sCapacity) && (!_usingStack)) {
			_usingStack = true;
			_copyArrays(_heapArray, _stackArray);
			delete[] _heapArray;
			_capacity = _sCapacity;
		}
	}

	void clear() noexcept {
		_size = 0;

		if (!_usingStack) {
			_usingStack = true;
			delete[] _heapArray;
			_capacity = _sCapacity;
		}
	}

	T *Data() const noexcept {
		return {_usingStack ? _stackArray : _heapArray};
	}

	T *Data() noexcept {
		return {_usingStack ? _stackArray : _heapArray};
	}

	iterator begin() {
		return {_usingStack ? iterator(&_stackArray[0]) : iterator(&_heapArray[0])};
	}

	reverse_iterator rbegin() {
		return {_usingStack ? Reverse_iterator(&_stackArray[_size - 1]) : Reverse_iterator(
				&_heapArray[_size - 1])};
	}

	const_iterator begin() const {
		return {_usingStack ? iterator(&_stackArray[0]) : iterator(&_heapArray[0])};
	}

	const_iterator cbegin() const {
		return {_usingStack ? iterator(&_stackArray[0]) : iterator(&_heapArray[0])};
	}

	iterator end() {
		return begin() + _size;
	}

	reverse_iterator rend() {
		return {_usingStack ? Reverse_iterator(&(--_stackArray[0])) : Reverse_iterator(&
																							(--_heapArray[0]))};
	}

	const_iterator end() const {
		return begin() + _size;
	}

	const_iterator cend() const {
		return cbegin() + _size;
	}

	//====================== operators =======================//

	VLVector &operator=(const VLVector &rhs) noexcept {
		if (this == &rhs) {
			return *this;
		} else {
			_size = rhs._size;
			_capacity = rhs._capacity;

			if (_usingStack) {

				if (rhs._usingStack) {
					_copyArrays(_stackArray, rhs._stackArray);

				} else {

					_heapArray = new T[rhs._capacity];
					_copyArrays(_heapArray, rhs._heapArray);
					_usingStack = false;

				}

			} else {

				delete[] _heapArray;

				if (rhs._usingStack) {

					_copyArrays(_stackArray, rhs._stackArray);
					_usingStack = true;

				} else {

					_heapArray = new T[rhs._capacity];
					_copyArrays(_heapArray, rhs._heapArray);
				}
			}
			return *this;
		}
	}

	T operator[](int i) const noexcept {
		return {_usingStack ? _stackArray[i] : _heapArray[i]};
	}

	T &operator[](int i) noexcept {
		return {_usingStack ? _stackArray[i] : _heapArray[i]};
	}

	bool operator==(const VLVector &rhs) const noexcept {
		if ((*this).size() != rhs.size()) {
			return false;
		}

		for (int i = 0; i < (*this).size(); ++i) {
			if ((*this)[i] != rhs[i]) {
				return false;
			}
		}
		return true;
	}

	bool operator!=(const VLVector &rhs) const noexcept {
		return (!((*this) == rhs));
	}
};