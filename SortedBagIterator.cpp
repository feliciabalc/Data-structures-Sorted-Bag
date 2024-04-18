#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>
#include <stdexcept>
#include <iostream>
using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
    this->current_element = 0;
    this->current_frecv=1;
}

//worst case=best case=average case=Theta(1)
TComp SortedBagIterator::getCurrent() {
    if (!this->valid())
        throw exception();

    return this->bag.elements[current_element];
}

//worst case=best case=average case=Theta(1)
bool SortedBagIterator::valid() {
    if (this->bag.isEmpty())
        return false;
    if (this->current_element >= this->bag.sizee)
        return false;

    return true;
}

//worst case=best case=average case=Theta(1)
void SortedBagIterator::next() {
    if (!this->valid())
        throw exception();

    if (this->bag.nrOccurrences(this->getCurrent()) > this->current_frecv) { //checks if fully iterated
        this->current_frecv++;
        return;
    }

    if (this->current_element < this->bag.size()) { //next elem
        this->current_element++;
        this->current_frecv = 1;// reset index
    }
}

//worst case=best case=average case=Theta(1)
void SortedBagIterator::first() {
    this->current_element = 0;
    this->current_frecv=1;
}

