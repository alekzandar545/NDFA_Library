#pragma once
#ifndef QUEUE_HEADER
#define QUEUE_HEADER

#include <stdexcept>
#include <iostream>

template <typename DataType>
class Queue {
private:
    DataType* data = nullptr;
    size_t size = 0;
    size_t capacity = 0;
    size_t whereToPut = 0;
    size_t whereToGet = 0;

    void free();
    void copyPrimitiveData(const Queue& other) noexcept;
    void copyFrom(const Queue& other);
    void moveFrom(Queue&& other) noexcept;
    void clear();
    DataType back() const;
    void resize(size_t newCapacity);
    void ensureCapacity();

public:
    Queue(size_t initialCapacity = 5);
    ~Queue();
    Queue(const Queue& other);
    Queue(Queue&& other) noexcept;
    Queue& operator=(const Queue& other);
    Queue& operator=(Queue&& other) noexcept;

    void push(const DataType& element);
    DataType pop();
    const DataType& front() const;
    bool empty() const;
    size_t getSize() const;
    size_t getCapacity() const;
};

#include "../../src/datastructures/queue.inl" 

#endif 