#include <iostream>
#include <math.h>

template<class T, size_t StaticCapacity = 16>
class VLVector {

private:

	T _stackArray[StaticCapacity];
	T *_heapArray;
	const size_t _sCap;
	size_t _size{};
	size_t _capacity{};
	bool _onStack{};

	size_t _capC(size_t size, size_t k) const noexcept {
		size_t temp = ((3 * (size + k)) / 2);
		return size + k <= _sCap ? _sCap : floor(temp);
	}

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

	VLVector() : _onStack(true), _size(0), _capacity(StaticCapacity), _sCap(StaticCapacity)
	{}

	VLVector(const VLVector &other) : _sCap(other._sCap), _capacity(other._capacity),
									  _size(other._size), _onStack(other._onStack)
	{
		if (_onStack)
		{
			_copyArrays(_stackArray, other._stackArray);
		}
		else
		{
			_heapArray = new T[_capacity];
			_copyArrays(_heapArray, other._heapArray);
		}

	}

	template<class InputIterator>
	VLVector(InputIterator first, InputIterator last) :_onStack(true), _size(0),
													   _capacity(StaticCapacity),
													   _sCap(StaticCapacity)
	{
		InputIterator begin = first;

		while (begin != last)
		{
			this->PushBack(*begin);
			++begin;
		}
	}

	~VLVector()
	{
		if (!_onStack)
		{
			delete[] _heapArray;
		}
	}

	size_t Size() const noexcept
	{
		return _size;
	}

	size_t Capacity() const noexcept
	{
		return _capacity;
	}

	bool Empty() const noexcept
	{ return (_size == 0); }

	T At(int i) const noexcept(false)
	{
		if (_size <= i)
		{
			throw std::out_of_range("ERROR: index out of range.");
		}
		else
		{
			return (*this)[i];
		}
	}

	T &At(int i) noexcept(false)
	{
		if (_size <= i)
		{
			throw std::out_of_range("ERROR: index out of range.");
		}
		else
		{
			return (*this)[i];
		}
	}

	void PushBack(const T &element) noexcept
	{
		if (_size < _capacity)
		{
			if (_size < _sCap)
			{
				_stackArray[_size] = element;
				_size++;
			}
			else
			{
				_heapArray[_size] = element;
				_size++;
			}
		}
		else
		{
			if (_onStack)
			{
				_capacity = _capC(_size, 1);
				_heapArray = new T[_capacity];
				_copyArrays(_heapArray, _stackArray);
				PushBack(element);
			}

			else
			{
				_capacity = _capC(_size, 1);
				T *temp = new T[_capacity];
				_copyArrays(temp, _heapArray);
				delete[] _heapArray;
				_heapArray = temp;
				PushBack(element);
			}

			_onStack = false;
		}
	}

	iterator &Insert(iterator position, const T &element) noexcept
	{
		if (begin() == end())
		{
			PushBack(*position);
			position++;
			return position;
		}

		VLVector<T, StaticCapacity> tempVec;
		int i = 0;

		iterator k = begin();

		while (k != position)
		{
			tempVec.PushBack((*this)[i]);
			i++;
			k++;
		}

		iterator toReturn = k;

		tempVec.PushBack(element);
		i++;

		while (k != end())
		{
			tempVec.PushBack((*this)[i]);
			i++;
			k++;
		}

		*this = tempVec;
		return toReturn;
	}

	template<class InputIterator>
	iterator &Insert(iterator position, InputIterator first, InputIterator last) noexcept
	{
		if (first == last)
		{
			PushBack(*position);
			position++;
			return position;
		}

		VLVector<T, StaticCapacity> tempVec;
		int i = 0;

		iterator k = begin();

		while (k != position)
		{
			tempVec.PushBack((*this)[i]);
			i++;
			k++;
		}

		iterator toReturn = k;
		InputIterator j = first;

		while (j != last)
		{
			tempVec.PushBack(*j);
			i++;
			j++;
		}

		while (k != end())
		{
			tempVec.PushBack((*this)[i]);
			i++;
			k++;
		}

		*this = tempVec;

		return toReturn;
	}

	iterator &Erase(iterator position) noexcept
	{
		VLVector<T, StaticCapacity> tempVec;
		int i = 0;

		iterator k = begin();

		while (k != position)
		{
			tempVec.PushBack((*this)[i]);
			i++;
			k++;
		}

		i++;
		k++;

		iterator toReturn = k;

		while (k != end())
		{
			tempVec.PushBack((*this)[i]);
			i++;
			k++;
		}

		*this = tempVec;

		return toReturn;
	}

	iterator &Erase(iterator first, iterator last) noexcept
	{
		VLVector<T, StaticCapacity> tempVec;
		int i = 0;

		iterator k = begin();

		while (k != first)
		{
			tempVec.PushBack((*this)[i]);
			i++;
			k++;
		}

		iterator j = first;

		while (j != last)
		{
			j++;
			i++;
			k++;
		}

		iterator toReturn = k;

		while (k != end())
		{
			tempVec.PushBack((*this)[i]);
			i++;
			k++;
		}

		*this = tempVec;

		return toReturn;
	}

	void PopBack() noexcept
	{
		_size--;

		if ((_size <= _sCap) && (!_onStack))
		{
			_onStack = true;
			_copyArrays(_heapArray, _stackArray);
			delete[] _heapArray;
			_capacity = _sCap;
		}
	}

	void Clear() noexcept
	{
		_size = 0;
		if (!_onStack)
		{
			_onStack = true;
			delete[] _heapArray;
			_capacity = _sCap;
		}
	}

	T *Data() const noexcept
	{
		return {_onStack ? _stackArray : _heapArray};
	}

	T *Data() noexcept
	{
		return {_onStack ? _stackArray : _heapArray};
	}

	iterator begin()
	{
		return {_onStack ? iterator(&_stackArray[0]) : iterator(&_heapArray[0])};
	}

	reverse_iterator rbegin()
	{
		return {_onStack ? Reverse_iterator(&_stackArray[_size - 1]) : Reverse_iterator(
				&_heapArray[_size - 1])};
	}

	const_iterator begin() const
	{
		return {_onStack ? iterator(&_stackArray[0]) : iterator(&_heapArray[0])};
	}

	const_iterator cbegin() const
	{
		return {_onStack ? iterator(&_stackArray[0]) : iterator(&_heapArray[0])};
	}

	iterator end()
	{
		return begin() + _size;
	}

	reverse_iterator rend()
	{
		return {_onStack ? Reverse_iterator(&(--_stackArray[0])) : Reverse_iterator(&
																							(--_heapArray[0]))};
	}

	const_iterator end() const
	{
		return begin() + _size;
	}

	const_iterator cend() const
	{
		return cbegin() + _size;
	}

	//====================== operators =======================//

	VLVector &operator=(const VLVector &rhs) noexcept
	{
		if (this == &rhs)
		{
			return *this;
		}
		else
		{
			_size = rhs._size;
			_capacity = rhs._capacity;

			if (_onStack)
			{
				if (rhs._onStack)
				{
					_copyArrays(_stackArray, rhs._stackArray);
				}
				else
				{
					_heapArray = new T[rhs._capacity];
					_copyArrays(_heapArray, rhs._heapArray);
					_onStack = false;
				}
			}
			else
			{
				delete[] _heapArray;

				if (rhs._onStack)
				{
					_copyArrays(_stackArray, rhs._stackArray);
					_onStack = true;
				}
				else
				{
					_heapArray = new T[rhs._capacity];
					_copyArrays(_heapArray, rhs._heapArray);
				}
			}
			return *this;
		}
	}

	T operator[](int i) const noexcept
	{
		return {_onStack ? _stackArray[i] : _heapArray[i]};
	}

	T &operator[](int i) noexcept
	{
		return {_onStack ? _stackArray[i] : _heapArray[i]};
	}

	bool operator==(const VLVector &rhs) const noexcept
	{
		if ((*this).Size() != rhs.Size())
		{
			return false;
		}

		for (int i = 0; i < (*this).Size(); ++i)
		{
			if ((*this)[i] != rhs[i])
			{
				return false;
			}
		}
		return true;
	}

	bool operator!=(const VLVector &rhs) const noexcept
	{
		return (!((*this) == rhs));
	}
};