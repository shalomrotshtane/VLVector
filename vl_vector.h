#include <iostream>
#include <math.h>

/**
 * @brief A standard container which offers fixed time access to
 * individual elements in any order.
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


public:

	typedef T *iterator;

	typedef const T *const_iterator;

	/**
	 *  @brief  Creates a vector with default constructed elements.
	 */
	VLVector() : _usingStack(true), _size(0), _capacity(StaticCapacity), _sCapacity(StaticCapacity) {}

	/**
	 *  @brief  Vector copy constructor.
	 *  @param  other  A vector of identical element.
	 */
	VLVector(const VLVector& other) : _usingStack(other._usingStack), _size(other._size), _capacity(other._capacity), _sCapacity(other._sCapacity)  {

		if (_usingStack) {
			_copyArrays(_stackArray, other._stackArray);
		} else {
			_heapArray = new T[_capacity];
			_copyArrays(_heapArray, other._heapArray);
		}
	}

	/**
	 *  @brief  Builds a vector from a range.
	 *  @param  first  An input iterator.
	 *  @param  last  An input iterator.
	 *
	 *  Create a vector consisting of copies of the elements from
	 *  [first,last).
	 */
	template<class InputIterator>
	VLVector(InputIterator first, InputIterator last) :_usingStack(true), _size(0), _capacity(StaticCapacity), _sCapacity(StaticCapacity) {

		InputIterator begin = first;

		while (begin != last) {
			this->pushBack(*begin);
			++begin;
		}
	}

	/**
	 *  The dtor only erases the elements, and note that if the
	 *  elements themselves are pointers, the pointed-to memory is
	 *  not touched in any way.  Managing the pointer is the user's
	 *  responsibility.
	 */
	~VLVector() {
		if (!_usingStack) {
			delete[] _heapArray;
			_heapArray = nullptr;
		}
	}

	/**  Returns the number of elements in the vector.  */
	size_t size() const noexcept {
		return _size;
	}

	/**
	 *  Returns the total number of elements that the vector can
	 *  hold before needing to allocate more memory.
	 */
	size_t capacity() const noexcept {
		return _capacity;
	}

	/**
	 *  Returns true if the vector is empty.  (Thus size() == 0.)
	 */
	bool isEmpty() const noexcept{
		return _size == 0;
	}

	/**
	 *  @brief  Provides access to the data contained in the vector.
	 *  @param i The index of the element for which data should be
	 *  accessed.
	 *  @return  Read/write reference to data.
	 *  @throw  std::out_of_range  If i is an invalid index.
	 *
	 *  This function provides for safer data access.  The parameter
	 *  is first checked that it is in the range of the vector.  The
	 *  function throws out_of_range if the check fails.
	 */
	T& at(int i) {
		if (i < 0 || _size <= i) {
			throw std::out_of_range("ERROR: index out of range.");
		} else {
			return (*this)[i];
		}
	}

	/**
	 *  @brief  Provides access to the data contained in the vector.
	 *  @param i The index of the element for which data should be
	 *  accessed.
	 *  @return  Read-only (constant) reference to data.
	 *  @throw  std::out_of_range  If i is an invalid index.
	 *
	 *  This function provides for safer data access.  The parameter
	 *  is first checked that it is in the range of the vector.  The
	 *  function throws out_of_range if the check fails.
	 */
	T at(int i) const {
		if (i < 0 || _size <= i) {
			throw std::out_of_range("ERROR: index out of range.");
		} else {
			return (*this)[i];
		}
	}

	/**
	 *  @brief  Add data to the end of the vector.
	 *  @param  element  Data to be added.
	 *
	 *  This is a typical stack operation.  The function creates an
	 *  element at the end of the vector and assigns the given data
	 *  to it.
	 */
	void pushBack(const T& element) noexcept {
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

	/**
	 *  @brief  Inserts given value into vector before specified iterator.
	 *  @param  position  A const_iterator into the vector.
	 *  @param  element  Data to be inserted.
	 *  @return  An iterator that points to the inserted data.
	 *
	 *  This function will insert a copy of the given value before
	 *  the specified location.
	 */
	iterator& insert(iterator position, const T& element) noexcept {
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

		while (k != end()) {
			tempVec.pushBack((*this)[i]);
			i++;
			k++;
		}

		*this = tempVec;
		return toReturn;
	}

	/**
	 *  @brief  Inserts a range into the vector.
	 *  @param  position  A const_iterator into the vector.
	 *  @param  first  An input iterator.
	 *  @param  last   An input iterator.
	 *  @return  An iterator that points to the inserted data.
	 *
	 *  This function will insert copies of the data in the range
	 *  [first, last) into the vector before the location specified
	 *  by position.
	 */
	template<class InputIterator>
	iterator& insert(iterator position, InputIterator first, InputIterator last) noexcept {
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

	/**
	 *  @brief  Remove element at given position.
	 *  @param  position  Iterator pointing to element to be erased.
	 *  @return  An iterator pointing to the next element (or end()).
	 *
	 *  This function will erase the element at the given position and thus
	 *  shorten the vector by one.
	 */
	iterator& erase(iterator position) noexcept {
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

	/**
	 *  @brief  Remove a range of elements.
	 *  @param  first  Iterator pointing to the first element to be erased.
	 *  @param  last  Iterator pointing to one past the last element to be
	 *                  erased.
	 *  @return  An iterator pointing to the element pointed to by @a last
	 *           prior to erasing (or end()).
	 *
	 *  This function will erase the elements in the range
	 *  [first,last) and shorten the vector accordingly.
	 */
	iterator& erase(iterator first, iterator last) noexcept {
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

	/**
	 *  @brief  Removes last element.
	 *
	 *  This is a typical stack operation. It shrinks the vector by one.
	 */
	void popBack() noexcept {
		_size--;

		if ((_size <= _sCapacity) && (!_usingStack)) {
			_usingStack = true;
			_copyArrays(_heapArray, _stackArray);
			delete[] _heapArray;
			_capacity = _sCapacity;
		}
	}

	/**
	 *  Erases all the elements.  Note that this function only erases the
	 *  elements, and that if the elements themselves are pointers, the
	 *  pointed-to memory is not touched in any way.  Managing the pointer is
	 *  the user's responsibility.
	 */
	void clear() noexcept {
		_size = 0;

		if (!_usingStack) {
			_usingStack = true;
			delete[] _heapArray;
			_capacity = _sCapacity;
		}
	}

	/**
	 *   Returns a pointer such that [data(), data() + size()) is a valid
	 *   range..
	 */
	T *Data() noexcept {
		return {_usingStack ? _stackArray : _heapArray};
	}

	/**
	 *   Returns a pointer such that [data(), data() + size()) is a valid
	 *   range..
	 */
	T *Data() const noexcept {
		return {_usingStack ? _stackArray : _heapArray};
	}

	/**
	 *  Returns a read/write iterator that points to the first
	 *  element in the vector.
	 */
	iterator begin() {
		return {_usingStack ? iterator(&_stackArray[0]) : iterator(&_heapArray[0])};
	}

	/**
	 *  Returns a read-only (constant) iterator that points to the
	 *  first element in the vector.
	 */
	const_iterator begin() const {
		return {_usingStack ? iterator(&_stackArray[0]) : iterator(&_heapArray[0])};
	}

	/**
	 *  Returns a read-only (constant) iterator that points to the
	 *  first element in the vector.
	 */
	const_iterator cbegin() const {
		return {_usingStack ? iterator(&_stackArray[0]) : iterator(&_heapArray[0])};
	}

	/**
	 *  Returns a read/write iterator that points one past the last
	 *  element in the vector.
	 */
	iterator end() {
		return begin() + _size;
	}

	/**
	 *  Returns a read-only (constant) iterator that points one past
	 *  the last element in the vector.
	 */
	const_iterator end() const {
		return begin() + _size;
	}

	/**
	 *  Returns a read-only (constant) iterator that points one past
	 *  the last element in the vector.
	 */
	const_iterator cend() const {
		return cbegin() + _size;
	}


	//====================== operators =======================//


	/**
	 *  @brief  Vector assignment operator.
	 *  @param  rhs  A vector of identical element and allocator types.
	 *
	 *  All the elements of @a rhs are copied, but any unused capacity in
	 *  @a rhs will not be copied.
	 *
	 *  Whether the allocator is copied depends on the allocator traits.
	 */
	VLVector& operator=(const VLVector& rhs) noexcept {
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

	/**
	 *  @brief  Subscript access to the data contained in the vector.
	 *  @param i The index of the element for which data should be
	 *  accessed.
	 *  @return  Read/write reference to data.
	 *
	 *  This operator allows for easy, array-style, data access.
	 *  Note that data access with this operator is unchecked and
	 *  out_of_range lookups are not defined. (For checked lookups
	 *  see at().)
	 */
	T& operator[](int i) noexcept {
		return {_usingStack ? _stackArray[i] : _heapArray[i]};
	}

	/**
	 *  @brief  Subscript access to the data contained in the vector.
	 *  @param i The index of the element for which data should be
	 *  accessed.
	 *  @return  Read-only (constant) reference to data.
	 *
	 *  This operator allows for easy, array-style, data access.
	 *  Note that data access with this operator is unchecked and
	 *  out_of_range lookups are not defined. (For checked lookups
	 *  see at().)
	 */
	T operator[](int i) const noexcept {
		return {_usingStack ? _stackArray[i] : _heapArray[i]};
	}

	/**
	 *  @brief  Vector equality comparison.
	 *  @param  rhs  A vector of the same type.
	 *  @return  True iff the size and elements of the vectors are equal.
	 *
	 *  This is an equivalence relation.  It is linear in the size of the
	 *  vectors.  Vectors are considered equivalent if their sizes are equal,
	 *  and if corresponding elements compare equal.
	*/
	bool operator==(const VLVector& rhs) const noexcept {
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

	/// Based on operator==
	bool operator!=(const VLVector& rhs) const noexcept {
		return (!((*this) == rhs));
	}
};