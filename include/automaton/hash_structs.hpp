#pragma once

#include "transition.hpp"
#include <iostream>
#include <unordered_set>

using State = unsigned;

struct TransitionHash {
    size_t operator()(const Transition& t) const {
        //hash everyting
        size_t h1 = std::hash<State>()(t.from); 
        size_t h2 = std::hash<State>()(t.to);   
        size_t h3 = std::hash<char>()(t.tag); 

        return h1 ^ (h2 << 1) ^ (h3 << 2);
    }
};

struct set_hash {
    template <typename T>
    size_t operator()(const std::unordered_set<T>& set) const {
        size_t seed = 0;
        for (const auto& elem : set)
            seed ^= std::hash<T>{}(elem) + (seed << 6) + (seed >> 2); //random hash
        return seed;
    }
};
struct vector_hash {
    template <typename T>
    size_t operator()(const Vector<T>& vec) const {
        size_t h = 0;
        for (auto& elem : vec) {
            h ^= std::hash<T>{}(elem) + 0x9e3779b9 + (h << 6) + (h >> 2);
        }
        return h;
    }
};
struct bitset_hash {
    size_t operator()(const BitSet& bs) const noexcept {
        size_t hash = 0x1f347449;
        for (uint8_t byte : bs.getData()) { 
            hash ^= static_cast<size_t>(byte);
            hash *= 0x9e3779b9;
        }
        return hash;
    }
};
struct pair_hash {
    template <typename T1, typename T2>
    size_t operator ()(const std::pair<T1, T2>& p) const {
        size_t h1 = std::hash<T1>{}(p.first);
        size_t h2 = std::hash<T2>{}(p.second);
        return h1 ^ (h2 << 1);  //random hash again
    }
};