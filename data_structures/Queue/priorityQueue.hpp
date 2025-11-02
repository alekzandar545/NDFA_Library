#pragma once

#include "queue.hpp"
#include "../DynamicArray/DynArray.hpp"
#include "staticQueue.hpp"
#include <stdexcept>

namespace fmi::sdp {

template <class DataType>
class PriorityQueue : public Queue<DataType>
{
public:
    PriorityQueue(size_t size = 16, size_t length = 128) : size(size), length(length+1)
    {
        for (size_t i = 0; i < size; i++)
        {
            StaticQueue<DataType> q(length);
            data.append(q);
        }
    }
    PriorityQueue(const PriorityQueue<DataType>& rhs) = default;
    PriorityQueue<DataType>& operator=(const PriorityQueue<DataType>& rhs) = default;
    ~PriorityQueue() = default;

    void enqueue(const DataType& data, const unsigned priority);
    void enqueue(const DataType& data) override; //lowest priority enqueue
    DataType dequeue() override;
    const DataType& first() const override;
    bool isEmpty() const override;
    bool isFull() const override;

    size_t count() const
    {
        size_t count = 0;
        for (size_t i = 0; i < size; i++)
            count += data[i].count();
        return count;
        
    }
private:
    DynArray<StaticQueue<DataType>> data;
    const size_t size;
    const size_t length;
};

#include "priorityQueue.inl"

}   // namespace sdp::fmi

