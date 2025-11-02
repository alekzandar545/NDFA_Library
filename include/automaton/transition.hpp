#pragma once

using State = unsigned;

struct Transition
{
    State from, to;
    char tag;

    //Transition() : from(0), to(0){}

    bool operator==(const Transition& other) const {
        return from == other.from && to == other.to && tag == other.tag;
    }
};