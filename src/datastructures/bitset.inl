#include <stdexcept>

const short BITSET_LENGTH = 128;

inline BitSet::BitSet(){m_capacity = BITSET_LENGTH; m_size = BITSET_LENGTH; m_data.resize(BITSET_LENGTH);}

inline BitSet::BitSet(size_t size):m_data((size+7) >> 3, 0){
    m_capacity = m_data.size() << 3;
    this->m_size = size;
};

inline void BitSet::setBit(bool b,size_t pos){
    size_t bIndex = pos >> 3;
    uint8_t bPos = pos & 7;
    uint8_t mask = 1 << bPos;
    m_data[bIndex] = (m_data[bIndex] & (~mask)) | (b << bPos);
}

inline bool BitSet::getBit(size_t pos) const
{
    return m_data[pos>>3] & (1<<(pos&7));
}

inline void BitSet::push_back(bool val){
    if(m_size >= (m_data.size() << 3)){
        m_data.append(0);
    }
    setBit(val,m_size++);
        
};

inline BitSet::Proxy BitSet::operator[](size_t index){
    if(index >= m_size)
        throw std::invalid_argument("Index out of range");
    return BitSet::Proxy(m_data.getData()+(index>>3),index & 7);
}

inline bool BitSet::operator[](size_t index)const{
    return getBit(index);
}
   

inline void BitSet::pop_back(){
    m_size--;
    if(m_size < ((m_data.size() - 1) << 3)){
        m_data.pop_back();
    }
}

inline size_t BitSet::size()const{
    return m_size;
}
inline void BitSet::flip(size_t pos){
    if(pos>=m_size){
        throw std::invalid_argument("Index out of range");
    }
    size_t bIndex = pos>>3;
    uint8_t bPos = pos & 7;
    m_data[bIndex] = m_data[bIndex] ^ (1<<bPos);
}

// begin() returns first set bit
inline BitSet::Iterator BitSet::begin() {
    return Iterator(*this, 0);
}

// end() returns m_size
inline BitSet::Iterator BitSet::end() {
    return Iterator(*this, m_size);
}



inline bool BitSet::all() const {
    if (m_size == 0) return false;
    
    const size_t full_bytes = m_size / 8;
    for (size_t i = 0; i < full_bytes; ++i) {
        if (m_data[i] != 0xFF) {
            return false;
        }
    }
    
    if (m_size % 8 != 0) {
        uint8_t mask = (1 << (m_size % 8)) - 1;
        if ((m_data.back() & mask) != mask) {
            return false;
        }
    }
    
    return true;
}

inline bool BitSet::any() const {
    for (auto byte : m_data) {
        if (byte != 0) {
            return true;
        }
    }
    return false;
}

inline bool BitSet::none() const {
    return !any();
}
inline const Vector<uint8_t>& BitSet::getData() const{
    return m_data;
}
inline bool operator==(const BitSet& a, const BitSet& b) {
    return a.size() == b.size() && a.getData() == b.getData();
}

inline void BitSet::resize(size_t new_size, bool value) {
    size_t old_size = m_size;
    m_size = new_size;
    m_capacity = new_size; 

    //required number of bytes
    size_t old_num_bytes = (old_size + 7) / 8;
    size_t new_num_bytes = (new_size + 7) / 8;

    m_data.resize(new_num_bytes);

    if (new_size > old_size) {
        //new bits to given value
        for (size_t i = old_size; i < new_size; ++i) {
            setBit(value, i);
        }
    } 
}