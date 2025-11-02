#pragma once

#ifndef _DYN_ARRAY_INCLUDED__
#define _DYN_ARRAY_INCLUDED__

#include <stdexcept>
#include <cassert>
#include <cstddef>
#include <algorithm>
#include "allocator.hpp"

template <class DataType, class Allocator = DefaultAllocator<DataType>>
class Vector
{
public:
        ////
        // Class life-cycle members

        // Ctor that sets the initial capacity
        Vector(int initialCapacity = 16);

        Vector(int initialCapacity, const DataType& filler);

        // copy ctor
        Vector(const Vector& other);

        // assignment operator
        Vector& operator= (const Vector& other);

        // A constructor, that creates an array as a copy.
        // The source array can have different type of elements!
        // In that case implicit cast operator between two types is expected.
        template <class OtherType, class __>
        Vector(const Vector<OtherType, __>& other);

        // Assignment operator.
        // The source array can have different type of elements!
        // In that case implicit cast operator between two types is expected.
        template <class OtherType, class __>
        Vector<DataType, Allocator>& operator= (const Vector<OtherType, __>& other);

        // dtor
        ~Vector();

        ////
        // Move semantics
        // Move ctor
        Vector(Vector&& other);

        // Move assignment
        Vector& operator= (Vector&& other);

        ////
        // Addition, removal and search of elements

        // Appends an array to the current.
        // The source array can have different type of elements!
        // In that case implicit cast operator between two types is expected.
        template <class OtherType, class __>
        Vector<DataType, Allocator>& operator+= (const Vector<OtherType, __>& other);
        
        // Appends an element at the end of the array.
        Vector<DataType, Allocator>& operator+= (const DataType& data);
        
        void append(const DataType& elem);
        
        void pop_back();
        
        DataType back() const;
        // Removes an element at given position
        void remove(size_t index);

        // Checks if an element exists in the array.
        // Requires comparison operator for the data type.
        bool contains(const DataType& data) const;

        // Returns a copy of the element at a given position.
        DataType get(size_t index) const;

        //getter for data
        DataType* getData() const;

        // Removes all elements in the array.
        void clear();

        ////
        // Information methods
        // the number of elements in the array
        size_t size() const;


        // the actual allocated size of the array
        size_t getCapacity() const;
        
        // checks if there are elements in the array
        bool empty() const;

        ////
        // Access operators and iterators

        // An indexing operators
        const DataType& operator[](size_t index) const;
        DataType& operator[](size_t index);

        // Here will be inserted the actual implementation
        // of a random-access iterator class
#include "../../src/datastructures/vector_iterator.inl"

        // Creates an iterator at the beginning of the array
        DArrayIterator begin() { return DArrayIterator(data); }
        DArrayIterator begin() const { return DArrayIterator(data); }
        // Creates an iterator at the end of the array
        DArrayIterator end() { return DArrayIterator(data + _size); }
        DArrayIterator end() const { return DArrayIterator(data + _size); }

protected:
        DataType* data;
        size_t _size, capacity;
        Allocator allocator;

public:
        // ensures there are enough space for given number of elements
        void reserve(size_t size);

        // changes the actual allocated space to the given number of elements
        void resize(size_t newCapacity);

        // changes the actual allocated space and fills the given number of elements
        void resize(size_t newCapacity, const DataType& filler);
};
// Equality operators
template <class DataType, class Allocator>
bool operator==(const Vector<DataType, Allocator>& lhs,
                const Vector<DataType, Allocator>& rhs);

template <class DataType, class Allocator>
bool operator!=(const Vector<DataType, Allocator>& lhs,
                const Vector<DataType, Allocator>& rhs);

#include "../../src/datastructures/vector.inl"

#endif //_DYN_ARRAY_INCLUDED__
