class DArrayIterator
{
    friend class Vector;
public:
    const DataType& operator*() const
    {
        return *pointer;
    }
    DataType& operator*()
    {
        return *pointer;
    }

    const DataType* operator->() const
    {
        return pointer;
    }
    DataType* operator->()
    {
        return pointer;
    }

    DArrayIterator& operator++()
    {
        ++pointer;
        return *this;
    }
    DArrayIterator operator++(int)
    {
        DArrayIterator res(*this);
        ++(*this);
        return res;
    }
    DArrayIterator& operator--()
    {
        --pointer;
        return *this;
    }
    DArrayIterator operator--(int)
    {
        DArrayIterator res(*this);
        --(*this);
        return res;
    }
    DArrayIterator& operator+=(int offset)
    {
        pointer += offset;
        return *this;
    }
    DArrayIterator operator+(int offset) const
    {
        DArrayIterator res(*this);
        res += offset;
        return res;
    }

    const DataType& operator[](int offset) const
    {
        return *(pointer + offset);
    }
    DataType& operator[](int offset)
    {
        return *(pointer + offset);
    }

    bool operator==(const DArrayIterator& other) const
    {
        return pointer == other.pointer;
    }
    bool operator!=(const DArrayIterator& other) const
    {
        return !(other == *this);
    }
    bool operator<(const DArrayIterator& other) const
    {
        return pointer < other.pointer;
    }
    bool operator>(const DArrayIterator& other) const
    {
        return other < *this;
    }
    bool operator>=(const DArrayIterator& other) const
    {
        return !(*this < other);
    }
    bool operator<=(const DArrayIterator& other) const
    {
        return !(*this > other);
    }
private:
    //private constructor, we dont want people creating iterators
    DArrayIterator(DataType* pointer) : pointer(pointer){}

    DataType* pointer;
};

