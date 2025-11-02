template <typename DataType>
void Queue<DataType>::free() {
    delete[] data;
    data = nullptr;
    size = capacity = whereToPut = whereToGet = 0;
}

template <typename DataType>
void Queue<DataType>::copyPrimitiveData(const Queue& other) noexcept {
    size = other.size;
    capacity = other.capacity;
    whereToPut = other.whereToPut;
    whereToGet = other.whereToGet;
}

template <typename DataType>
void Queue<DataType>::copyFrom(const Queue& other) {
    data = new DataType[other.capacity];
    for (size_t i = 0; i < other.size; i++) {
        data[i] = other.data[(other.whereToGet + i) % other.capacity];
    }
    copyPrimitiveData(other);
}

template <typename DataType>
void Queue<DataType>::moveFrom(Queue&& other) noexcept {
    data = other.data;
    copyPrimitiveData(other);

    other.data = nullptr;
    other.capacity = 0;
    other.size = 0;
    other.whereToGet = 0;
    other.whereToPut = 0;
}

template <typename DataType>
void Queue<DataType>::clear() {
    delete[] data;
    data = nullptr;
    size = capacity = whereToPut = whereToGet = 0;
}

template <typename DataType>
DataType Queue<DataType>::back() const {
    if (empty())
        throw std::underflow_error("Queue is empty.");
    return data[(whereToPut == 0 ? capacity : whereToPut) - 1];
}

template <typename DataType>
void Queue<DataType>::resize(size_t newCapacity) {
    if (newCapacity <= size)
        throw std::logic_error("New capacity must be greater than current size.");

    DataType* temp = new DataType[newCapacity];
    for (size_t i = 0; i < size; i++)
        temp[i] = std::move(data[(whereToGet + i) % capacity]);

    delete[] data;
    data = temp;
    capacity = newCapacity;
    whereToGet = 0;
    whereToPut = size;
}

template <typename DataType>
void Queue<DataType>::ensureCapacity() {
    if (size == capacity) {
        resize(capacity == 0 ? 1 : capacity * 2);
    }
}

template <typename DataType>
Queue<DataType>::Queue(size_t initialCapacity)
    : data(new DataType[initialCapacity]), size(0), capacity(initialCapacity), whereToPut(0), whereToGet(0) {}

template <typename DataType>
Queue<DataType>::~Queue() {
    free();
}

template <typename DataType>
Queue<DataType>::Queue(const Queue& other) {
    copyFrom(other);
}

template <typename DataType>
Queue<DataType>::Queue(Queue&& other) noexcept {
    moveFrom(std::move(other));
}

template <typename DataType>
Queue<DataType>& Queue<DataType>::operator=(const Queue& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

template <typename DataType>
Queue<DataType>& Queue<DataType>::operator=(Queue&& other) noexcept {
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

template <typename DataType>
void Queue<DataType>::push(const DataType& element) {
    ensureCapacity();
    data[whereToPut] = element;
    whereToPut = (whereToPut + 1) % capacity;
    size++;
}

template <typename DataType>
DataType Queue<DataType>::pop() {
    if (empty()) {
        throw std::underflow_error("Queue is empty.");
    }
    DataType res = data[whereToGet];
    whereToGet = (whereToGet + 1) % capacity;
    size--;
    return res;
}

template <typename DataType>
const DataType& Queue<DataType>::front() const {
    if (empty()) {
        throw std::underflow_error("Queue is empty.");
    }
    return data[whereToGet];
}

template <typename DataType>
bool Queue<DataType>::empty() const {
    return size == 0;
}

template <typename DataType>
size_t Queue<DataType>::getSize() const {
    return size;
}

template <typename DataType>
size_t Queue<DataType>::getCapacity() const {
    return capacity;
}
