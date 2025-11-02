#pragma once
#include <cstddef> // for size_t

class String {
public:
    // Default constructor
    String() : data(nullptr), length(0), capacity(0) {}

    // Constructor from C-string
    String(const char* str) {
        length = stringLength(str);
        capacity = length + 1;
        data = new char[capacity];
        stringCopy(data, str, length);
        data[length] = '\0';
    }

    // Constructor from char
    String(const char ch) {
        length = 1;
        capacity = length + 1;
        data = new char[capacity];
        data[0] = ch;
        data[length] = '\0';
    }

    // Copy constructor
    String(const String& other) : length(other.length), capacity(other.capacity) {
        data = new char[capacity];
        stringCopy(data, other.data, length);
        data[length] = '\0';
    }

    // Move constructor
    String(String&& other) noexcept : data(other.data), length(other.length), capacity(other.capacity) {
        other.data = nullptr;
        other.length = 0;
        other.capacity = 0;
    }

    // Destructor
    ~String() {
        delete[] data;
    }

    // Copy assignment operator
    String& operator=(const String& other) {
        if (this != &other) {
            delete[] data;
            length = other.length;
            capacity = other.capacity;
            data = new char[capacity];
            stringCopy(data, other.data, length);
            data[length] = '\0';
        }
        return *this;
    }

    // Move assignment operator
    String& operator=(String&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            length = other.length;
            capacity = other.capacity;

            other.data = nullptr;
            other.length = 0;
            other.capacity = 0;
        }
        return *this;
    }

    // Access operator
    char& operator[](size_t index) { return data[index]; }
    const char& operator[](size_t index) const { return data[index]; }

    // Concatenation operators
    String& operator+=(const String& other) {
        if (length + other.length + 1 > capacity) {
            resizeBuffer(length + other.length + 1);
        }
        stringCopy(data + length, other.data, other.length);
        length += other.length;
        data[length] = '\0';
        return *this;
    }

    String operator+(const String& other) const {
        String result(*this);
        result += other;
        return result;
    }
    //handles cases when there is a c_str on the left
    friend String operator+(const char* lhs, const String& rhs) {
        return String(lhs) + rhs;
    }
    //handles the case where lhs is a char
    friend String operator+(char lhs, const String& rhs) {
        return String(lhs) + rhs;
    }

    String& operator+=(char other) {
        if (length + 1 + 1 > capacity) {
            resizeBuffer(length + 1 + 1);
        }
        data[length] = other;
        length++;
        data[length] = '\0';
        return *this;
    }

    String operator+(char other) const {
        String result(*this);
        result += other;
        return result;
    }

    // Comparison operators
    bool operator==(const String& other) const {
        if (length != other.length) return false;
        for (size_t i = 0; i < length; ++i) {
            if (data[i] != other.data[i]) return false;
        }
        return true;
    }

    bool operator!=(const String& other) const {
        return !(*this == other);
    }

    //operator<<
    friend std::ostream& operator<<(std::ostream& os, const String& str) {
        if (str.data) {
            os.write(str.data, str.length);
        }
        return os;
    }

    // Methods
    size_t size() const { return length; }
    size_t getCapacity() const { return capacity; }
    bool empty() const { return length == 0; }
    void clear() {
        length = 0;
        if (data) {
            data[0] = '\0';
        }
    }

    void pushBack(char c) {
        if (length + 1 >= capacity) {
            resizeBuffer(capacity == 0 ? 1 : capacity * 2);
        }
        data[length++] = c;
        data[length] = '\0';
    }

    void popBack() {
        if (length > 0) {
            data[--length] = '\0';
        }
    }

    // Iterators
    class Iterator {
        char* ptr;
    public:
        Iterator(char* p) : ptr(p) {}
        char& operator*() { return *ptr; }
        Iterator& operator++() { ++ptr; return *this; }
        bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
    };

    Iterator begin() const { return Iterator(data); }
    Iterator end() const { return Iterator(data + length); }

    // For debugging/testing
    const char* c_str() const { return data; }

private:
    char* data;
    size_t length;
    size_t capacity;

    static size_t stringLength(const char* str) {
        size_t len = 0;
        while (str[len] != '\0') ++len;
        return len;
    }

    static void stringCopy(char* dest, const char* src, size_t len) {
        for (size_t i = 0; i < len; ++i) {
            dest[i] = src[i];
        }
    }

    void resizeBuffer(size_t newCapacity) {
        char* newData = new char[newCapacity];
        if (data) {
            stringCopy(newData, data, length);
            delete[] data;
        }
        data = newData;
        capacity = newCapacity;
    }
};
