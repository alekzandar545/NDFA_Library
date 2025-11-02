#include <iostream>

template <class DataType, class Allocator>
inline Vector<DataType, Allocator>::Vector(int initialCapacity)
    : data(nullptr)
    , _size(0)
    , capacity(initialCapacity)
{
    if (initialCapacity <= 0) 
        throw std::invalid_argument("Illegal initial size");

    data = allocator.allocArr(capacity);
}

template <class DataType, class Allocator>
inline Vector<DataType, Allocator>::Vector(int initialCapacity, const DataType& filler)
    : data(nullptr)
    , _size(initialCapacity)
    , capacity(initialCapacity)
{
    if (initialCapacity <= 0) 
        throw std::invalid_argument("Illegal initial size");
    
    data = allocator.allocArr(capacity);

    for (size_t i = 0; i < capacity; i++)
        data[i] = filler;
    
}


template <class DataType, class Allocator>
inline Vector<DataType, Allocator>::~Vector()
{
    clear();
#ifdef _DEBUG
    allocator.printStatistics();
#endif
}


template <class DataType, class Allocator>
inline Vector<DataType, Allocator>::Vector(const Vector& other)
    : data(nullptr)
    , _size(other.size())
    , capacity(other.getCapacity())
{
    capacity = capacity ? capacity : 1;
    data = allocator.allocArr(capacity);

    try {
        for (size_t i = 0; i < _size; ++i)
            data[i] = other[i];
    }
    catch (...) {
        allocator.freeArr(data);
        throw;
    }
}

template <class DataType, class Allocator>
inline Vector<DataType, Allocator>::Vector(Vector&& other)
    : data(nullptr)
    , _size(other._size)
    , capacity(other.capacity)
{
    std::swap(data, other.data);
    allocator.swap(other.allocator);
}

template <class DataType, class Allocator>
inline Vector<DataType, Allocator>& Vector<DataType, Allocator>::operator= (const Vector<DataType, Allocator>& other)
{
    if (this != &other) {
        if (capacity < other.size()) {
            clear();
            reserve(other.getCapacity());
        }
        for (_size = 0; _size < other._size; ++_size) 
            data[_size] = other[_size];
    }
    return *this;
}

template <class DataType, class Allocator>
inline Vector<DataType, Allocator>& Vector<DataType, Allocator>::operator=(Vector<DataType, Allocator>&& other)
{
    if (this != &other) {
        std::swap(data, other.data);
        std::swap(_size, other._size);
        std::swap(capacity, other.capacity);
        allocator.swap(other.allocator);
    }
    return *this;
}

template <class DataType, class Allocator>
template <class OtherType, class __>
inline Vector<DataType, Allocator>::Vector(const Vector<OtherType, __>& other)
    : data(nullptr)
    , _size(other.size())
    , capacity(other.getCapacity())
{
    capacity = capacity ? capacity : 1;
    data = allocator.allocArr(capacity);
    try {
        for (size_t i = 0; i < _size; ++i) {
            data[i] = other[i];
        }
    }
    catch (...) {
        allocator.freeArr(data);
        throw;
    }
}

template <class DataType, class Allocator>
template <class OtherType, class __>
inline Vector<DataType, Allocator>& Vector<DataType, Allocator>::operator= (const Vector<OtherType, __>& other)
{
    _size = other.size();
    if (capacity < other.size()) {
        clear();
        reserve(other.size());
    }

    for (_size = 0; _size < other.size(); ++_size) {
        data[_size] = other[_size];
    }

    return *this;
}

//vectors may be of different types
template <class DataType, class Allocator>
template <class OtherType, class __>
inline Vector<DataType, Allocator>& Vector<DataType, Allocator>::operator+= (const Vector<OtherType, __>& other)
{
    reserve(_size + other.size());
    for (size_t i = 0; i < other.size(); ++i) {
        data[_size + i] = other[i];
    }
    _size += other.size();
    return *this;
}

template <class DataType, class Allocator>
inline Vector<DataType, Allocator>& Vector<DataType, Allocator>::operator+= (const DataType& elem)
{
    append(elem);
    return *this;
}

template <class DataType, class Allocator>
inline void Vector<DataType, Allocator>::append(const DataType& elem)
{
    reserve(_size + 1);
    data[_size] = elem;
    ++_size;
}


template <class DataType, class Allocator>
inline size_t Vector<DataType, Allocator>::size() const
{
    return _size;
}


template <class DataType, class Allocator>
inline size_t Vector<DataType, Allocator>::getCapacity() const
{
    return capacity;
}

template <class DataType, class Allocator>
inline bool Vector<DataType, Allocator>::empty() const
{
    return _size == 0;
}

template <class DataType, class Allocator>
inline void Vector<DataType, Allocator>::clear()
{
    allocator.freeArr(data);
    data = nullptr;
    capacity = _size = 0;
}


template <class DataType, class Allocator>
inline DataType Vector<DataType, Allocator>::get(size_t index) const
{
    if (index < _size) 
        return data[index];

    //default value of datatype
    return DataType();
}


template <class DataType, class Allocator>
inline void Vector<DataType, Allocator>::remove(size_t index)
{
    if (index >= _size) {
        throw std::invalid_argument("Illegal index");
    }

    for (size_t i = index; i < _size - 1; ++i) {
        data[i] = data[i + 1];
    }
    --_size;
}


template <class DataType, class Allocator>
inline bool Vector<DataType, Allocator>::contains(const DataType& elem) const
{
    for (size_t i = 0; i < _size; ++i) {
        if (elem == data[i]) {
            return true;
        }
    }
    return false;
}


// Note, that there are two same operators.
//It is possible to implement one using the other, but it is a bit ugly to use casts
//As the code is simple enough, in that case it OK to have duplication.
template <class DataType, class Allocator>
inline const DataType& Vector<DataType, Allocator>::operator[](size_t index) const
{
    if (index < _size) return data[index];
    throw std::invalid_argument("Illegal index");
}


template <class DataType, class Allocator>
inline DataType& Vector<DataType, Allocator>::operator[](size_t index)
{
    if (index < _size) return data[index];
    throw std::invalid_argument("Illegal index");
}


//reserve adds to the capacity
template <class DataType, class Allocator>
inline void Vector<DataType, Allocator>::reserve(size_t size) {

    if (size > capacity) {
        DataType* newData = allocator.allocArr(size);

        try {
            //copy
            for (size_t i = 0; i < _size; ++i) {
                newData[i] = data[i];
            }
        }
        catch (...) {
            allocator.freeArr(newData);
            throw;
        }

        //free old mem
        allocator.freeArr(data);
        data = newData;
        capacity = size;
    }
}

//resize affects capacity and size
template <class DataType, class Allocator>
inline void Vector<DataType, Allocator>::resize(size_t newSize) {
    if (newSize > capacity)
        reserve(newSize);

    for (size_t i = _size; i < newSize; ++i) 
        data[i] = DataType(); //construct remainder of elements with default values

    _size = newSize;
}

//here whe choose what to fill the blank spaces with
template <class DataType, class Allocator>
inline void Vector<DataType, Allocator>::resize(size_t newSize, const DataType& filler) {
    if (newSize > capacity) 
        reserve(newSize);

    for (size_t i = _size; i < newSize; ++i)
        data[i] = filler;

    _size = newSize;
}

template <class DataType, class Allocator>
inline Vector<DataType, Allocator> operator+ (const Vector<DataType, Allocator>& array, const DataType& data)
{
    return Vector<DataType, Allocator>(array) += data;
}


template <class DataType, class OtherType, class Allocator1, class Allocator2>
inline Vector<DataType, Allocator1> operator+ (const Vector<DataType, Allocator1>& array, const Vector<OtherType, Allocator2>& other)
{
    return Vector<DataType, Allocator1>(array) += other;
}

template <class DataType, class Allocator>
inline void Vector<DataType, Allocator>::pop_back() {
    if (_size == 0) {
        throw std::out_of_range("Vector::pop_back - vector is empty");
    }
    
    // Destroy the last element
    if constexpr (!std::is_trivially_destructible_v<DataType>) {
        data[_size - 1].~DataType();
    }
    
    _size--;
}

template <class DataType, class Allocator>
inline DataType Vector<DataType, Allocator>::back() const{
    return data[_size-1];
}


template <class DataType, class Allocator>
inline DataType* Vector<DataType, Allocator>::getData() const {return data;}

template <class DataType, class Allocator>
bool operator==(const Vector<DataType, Allocator>& lhs,
                const Vector<DataType, Allocator>& rhs) {
    if (lhs.size() != rhs.size())
        return false;
    for (size_t i = 0; i < lhs.size(); ++i) {
        if (!(lhs[i] == rhs[i]))
            return false;
    }
    return true;
}

template <class DataType, class Allocator>
bool operator!=(const Vector<DataType, Allocator>& lhs,
                const Vector<DataType, Allocator>& rhs) {
    return !(lhs == rhs);
}