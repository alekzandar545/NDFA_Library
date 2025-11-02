
//LIFE CYCLE--------------------------------
template <typename DataType>
Stack<DataType>::Stack(size_t capacity)
    : data(new DataType[capacity])
    , tos(0)
    , capacity(capacity)
{}

template <typename DataType>
Stack<DataType>::Stack(const Stack& rhs)
    : data(new DataType[rhs.capacity])
    , tos(0)
    , capacity(rhs.capacity)
{
    while (tos < rhs.tos)
    push(rhs.data[tos]);
}

template <typename DataType>
Stack<DataType>::Stack(Stack&& rhs) noexcept
    : data(rhs.data)
    , tos(rhs.tos)
    , capacity(rhs.capacity)
{
    rhs.data = nullptr;
    rhs.tos = 0;
    rhs.capacity = 0;
}

template <typename DataType>
Stack<DataType>& Stack<DataType>::operator=(const Stack& rhs) {
    if (this != &rhs) {
        while (rhs.tos > capacity) {
            resize(rhs.tos);
        }
        tos = 0;
        while (tos < rhs.tos) {
            data[tos] = rhs.data[tos];
            ++tos;
        }
    }
    return *this;
}

template <typename DataType>
Stack<DataType>& Stack<DataType>::operator=(Stack&& rhs) noexcept
{
    if (this != &rhs) {
        delete[] data;
        data = rhs.data;
        tos = rhs.tos;
        capacity = rhs.capacity;
        
        rhs.data = nullptr;
        rhs.tos = 0;
        rhs.capacity = 0;
    }
    return *this;
}

template <typename DataType>
Stack<DataType>::~Stack() {
    delete[] data;
}

template <typename DataType>
void Stack<DataType>::push(const DataType& elem) {
    if (full()) {
        resize(capacity == 0 ? 1 : capacity * 2);
    }
    data[tos++] = elem;
}


template <typename DataType>
DataType Stack<DataType>::pop()
{
    if (!empty()) return data[--tos];
    throw std::underflow_error("Empty stack");
}

template <typename DataType>
const DataType& Stack<DataType>::top() const
{
    if (!empty()) return data[tos - 1];
    throw std::underflow_error("Empty stack");
}

template <typename DataType>
bool Stack<DataType>::empty() const
{
    return tos == 0;
}

template <typename DataType>
bool Stack<DataType>::full() const
{
    return tos == capacity;
}

template <typename DataType>
size_t Stack<DataType>::size() const
{
    return tos;
}

template <typename DataType>
void Stack<DataType>::resize(size_t new_capacity) {
    if (new_capacity < tos) {
        throw std::invalid_argument("New capacity cannot be less than current size");
    }
    
    DataType* new_data = new DataType[new_capacity];
    for (size_t i = 0; i < tos; ++i) {
        new_data[i] = std::move(data[i]);
    }
    
    delete[] data;
    data = new_data;
    capacity = new_capacity;
}
