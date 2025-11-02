
template <class DataType>
inline DataType PriorityQueue<DataType>::dequeue()
{
    for (int i = 0; i < size; i++)
    {
        if(!data[i].isEmpty())
            return data[i].dequeue();
    }
    throw std::underflow_error("Empty queue");
}

template <class DataType>
inline const DataType& PriorityQueue<DataType>::first() const
{
    for (int i = 0; i < size; i++)
    {
        if(!data[i].isEmpty())
            return data[i].first();
    }
    throw std::underflow_error("Empty queue");
}

template <class DataType>
inline void PriorityQueue<DataType>::enqueue(const DataType& elem, const unsigned priority)
{
    if(priority >= size)
        throw std::overflow_error("wrong position");
    data[priority].enqueue(elem);
}

template <class DataType>
inline void PriorityQueue<DataType>::enqueue(const DataType& elem)
{
    data[0].enqueue(elem);
}

template <class DataType>
inline bool PriorityQueue<DataType>::isEmpty() const
{
    for (size_t i = 0; i < size; i++)
        if (!data[i].isEmpty())
            return false;
    return true;
}

template <class DataType>
inline bool PriorityQueue<DataType>::isFull() const
{
    for (size_t i = 0; i < size; i++)
        if(!data[i].isFull())
            return false;
    return true;
}

