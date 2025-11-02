#pragma once

#ifndef BITSET_HEADER
#define BITSET_HEADER

#include <cstdint>
#include <stdexcept>
#include "vector.hpp"

class BitSet{
private:
    size_t  m_capacity, m_size;
    Vector<uint8_t> m_data;

    void setBit(bool,size_t);
    bool getBit(size_t) const;

public:
    class Proxy{
        Proxy(uint8_t* el, uint8_t pos);
        uint8_t* m_el;
        uint8_t m_pos;
        
        public: 
        operator bool()const;
        bool operator=(bool val);

        friend class BitSet;
    };
    class Iterator{
        using iterator_category = std::random_access_iterator_tag;
        using value_type = bool;
        using difference_type = std::ptrdiff_t;
        using pointer = void;
        using reference = Proxy; 
        size_t index;
        BitSet& owner;
        Iterator(BitSet& bitset, size_t pos);
        friend class BitSet;
        // helper: move to the next set bit
        void moveToNext();
        void moveToPrev();
        public:

        //ITERATOR RETURNS INDECIES OF ACTIVE BITS
        unsigned operator*() const { return index; }
        Iterator& operator++();
        Iterator operator++(int);
        Iterator& operator--();
        Iterator operator--(int);
        Iterator& operator+=(difference_type n);
        Iterator operator+(difference_type n) const;
        Iterator& operator-=(difference_type n);
        Iterator operator-(difference_type n) const;
        difference_type operator-(const Iterator& other) const;
        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;
        bool operator<(const Iterator& other) const;
        bool operator>(const Iterator& other) const;
        bool operator<=(const Iterator& other) const;
        bool operator>=(const Iterator& other) const;
        reference operator[](difference_type n) const;
    };

    BitSet();
    BitSet(size_t size);
    Proxy operator[](size_t index);
    bool operator[](size_t index)const;
    void push_back(bool);
    void pop_back();
    size_t size()const;
    void flip();
    void flip(size_t pos);
    bool all()const;
    bool any()const;
    bool none()const;
    const Vector<uint8_t>& getData() const;
    void resize(size_t new_size, bool value);

    friend class Iterator;
    friend class Proxy;

    Iterator begin();
    Iterator end();
};
#include "../../src/datastructures/bitset_iterator.inl" 
#include "../../src/datastructures/bitset_proxy.inl" 
#include "../../src/datastructures/bitset.inl" 

#endif