#pragma once

#ifndef _STATIC_STACK_HEADER_INCLUDED_
#define _STATIC_STACK_HEADER_INCLUDED_

#include <cstddef>
#include <stdexcept>

template <typename DataType>
class Stack
{
public:
    Stack(size_t _size = 16);
    Stack(const Stack& rhs);
    Stack(Stack&& rhs) noexcept;
    Stack& operator=(const Stack& rhs);
    Stack& operator=(Stack&& rhs) noexcept;
    ~Stack();

    void push(const DataType& elem);
    DataType pop();
    size_t size() const;
    const DataType& top() const;
    bool empty() const;
    bool full() const;
    void resize(size_t new_capacity);

private:
    DataType* data;
    size_t tos;
    size_t capacity;
};

#include "../../src/datastructures/stack.inl"

#endif