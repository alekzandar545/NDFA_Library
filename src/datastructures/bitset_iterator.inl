inline BitSet::Iterator::Iterator(BitSet& bitset, size_t pos) : owner(bitset), index(pos) {
    if (index < owner.size() && !owner[index])
        moveToNext();
}

// Move to next set bit
inline void BitSet::Iterator::moveToNext() {
    while (index < owner.size() && !owner[index]) ++index;
}

// Move to previous set bit
inline void BitSet::Iterator::moveToPrev() {
    while (index > 0 && !owner[index]) --index;
}

inline BitSet::Iterator& BitSet::Iterator::operator++() {
    ++index;
    moveToNext();
    return *this;
}

inline BitSet::Iterator BitSet::Iterator::operator++(int) {
    Iterator temp = *this;
    ++(*this);
    return temp;
}

inline BitSet::Iterator& BitSet::Iterator::operator--() {
    if (index == owner.size()) --index; // end() case
    moveToPrev();
    return *this;
}

inline BitSet::Iterator BitSet::Iterator::operator--(int) {
    Iterator temp = *this;
    --(*this);
    return temp;
}

inline BitSet::Iterator& BitSet::Iterator::operator+=(difference_type n) {
    if (n >= 0) for (difference_type i = 0; i < n; ++i) ++(*this);
    else for (difference_type i = 0; i < -n; ++i) --(*this);
    return *this;
}

inline BitSet::Iterator BitSet::Iterator::operator+(difference_type n) const {
    Iterator temp = *this;
    temp += n;
    return temp;
}

inline BitSet::Iterator& BitSet::Iterator::operator-=(difference_type n) {
    *this += -n;
    return *this;
}

inline BitSet::Iterator BitSet::Iterator::operator-(difference_type n) const {
    Iterator temp = *this;
    temp -= n;
    return temp;
}

inline BitSet::Iterator::difference_type BitSet::Iterator::operator-(const Iterator& other) const {
    return static_cast<difference_type>(index) - static_cast<difference_type>(other.index);
}

inline bool BitSet::Iterator::operator==(const Iterator& other) const {
    return &owner == &other.owner && index == other.index;
}

inline bool BitSet::Iterator::operator!=(const Iterator& other) const {
    return !(*this == other);
}

inline bool BitSet::Iterator::operator<(const Iterator& other) const {
    return &owner == &other.owner && index < other.index;
}

inline bool BitSet::Iterator::operator>(const Iterator& other) const {
    return &owner == &other.owner && index > other.index;
}

inline bool BitSet::Iterator::operator<=(const Iterator& other) const {
    return !(*this > other);
}

inline bool BitSet::Iterator::operator>=(const Iterator& other) const {
    return !(*this < other);
}

