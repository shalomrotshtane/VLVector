#include <iostream>
#include "vl_vector.h"

template<size_t StaticCapacity = 16>
class VLString {

	VLVector<char, StaticCapacity> str;

public:

	typedef char *iterator;

	typedef const char *const_iterator;

	VLString() : str()
	{
		str.At(str.Capacity()) = '\0';
	}

	VLString(const VLString &other) : str(other.str)
	{}

	explicit VLString(const char *str) : str()
	{
		while (*str != '\0')
		{
			this->str.push_back(*str);
			str++;
		}
	}

	// ========================== methods ==========================//

	size_t Size() const noexcept {
		return str.Size();
	}

	size_t Capacity() const noexcept {
		return str.Capacity();
	}

	bool Empty() const noexcept {
		return str.Empty();
	}

	char At(int i) const noexcept(false) {
		return str.At(i);
	}

	char &At(int i) noexcept(false) {
		return str.At(i);
	}

	void PushBack(const char &element) noexcept {
		str.PushBack(element);
	}

	iterator &insert(iterator position, const char &element) noexcept {
		return str.Insert(position, element);
	}

	template<class InputIterator>
	iterator &insert(iterator position, InputIterator first, InputIterator last) noexcept
	{
		return str.Insert(position, first, last);
	}

	iterator &Erase(iterator position) noexcept
	{
		return str.Erase(position);
	}

	iterator &Erase(iterator first, iterator last) noexcept
	{
		return str.Erase(first, last);
	}

	void Clear() noexcept
	{
		str.Clear();
	}

	char *Data() const noexcept
	{
		return str.Data();
	}

	char *Data() noexcept
	{
		return str.Data();
	}

	iterator begin()
	{
		return str.begin();
	}

	const_iterator begin() const
	{
		return str.begin();
	}

	const_iterator cbegin() const
	{
		return str.cbegin();
	}

	iterator end()
	{
		return str.end();
	}

	const_iterator end() const
	{
		return str.end();
	}

	const_iterator cend() const
	{
		return str.cend();
	}

	//====================== operators =======================//

	VLString &operator=(const VLString &rhs) noexcept
	{
		if (this == &rhs)
		{
			return *this;
		}
		else
		{
			str = rhs.str;
		}
		return *this;
	}

	char operator[](int i) const noexcept
	{
		return str[i];
	}

	char &operator[](int i) noexcept
	{
		return str[i];
	}

	bool operator==(const VLString &rhs) const noexcept
	{
		return (str == rhs.str);
	}

	bool operator!=(const VLString &rhs) const noexcept
	{
		return (!((*this) == rhs));
	}

	VLString &operator+=(const char *&rhs) noexcept
	{
		(*this).PushBack(*rhs);
		return *this;
	}

	VLString &operator+=(const char &rhs) noexcept
	{
		(*this).PushBack(rhs);
		return *this;
	}
	
	VLString &operator+(const char *&rhs) noexcept
	{
		(*this).PushBack(*rhs);
		return *this;
	}

	VLString &operator+(const char &rhs) noexcept
	{
		(*this).PushBack(rhs);
		return *this;
	}


	explicit operator const char *() noexcept
	{
		return &(*this)[0];
	}

};