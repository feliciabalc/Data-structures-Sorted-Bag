#include <iostream>
#include "SortedBag.h"
#include "SortedBagIterator.h"

SortedBag::SortedBag(Relation r) {
    this->capacity = 20;
    this->sizee=0;
    this->elements=new TComp [capacity];
    this->frequenz=new int[capacity];
    this->relation = r;
}
//worst case: Theta(size), best case: Theta(1), average case: O(size)
void SortedBag::resizeUp() {
    TElem *newElements = new TComp[2 * this->capacity];
    int *newFrequenz = new int[2 * this->capacity];

    for (int i = 0; i < this->sizee; i++) {
        newElements[i] = this->elements[i];
        newFrequenz[i] = this->frequenz[i];
    }

    this->capacity = 2 * this->capacity;

    delete[] this->elements;
    delete[] this->frequenz;

    this->elements = newElements;
    this->frequenz = newFrequenz;
}
//worst case: Theta(size), best case: Theta(1), average case: O(size)
void SortedBag::resizeDown() {

    int newCapacity = this->capacity / 2;

    TElem *newElements = new TComp[newCapacity];
    int *newFrequenz = new int[newCapacity];

    for (int i = 0; i < this->sizee; i++) {
        newElements[i] = this->elements[i];
        newFrequenz[i] = this->frequenz[i];
    }

    this->capacity = newCapacity;

    delete[] this->elements;
    delete[] this->frequenz;

    this->elements = newElements;
    this->frequenz = newFrequenz;

}

//worst case: Theta(size), best case: Theta(1), average case: 0(size)
void SortedBag::add(TComp elem) {
    if (isEmpty()) {
        this->elements[0] = elem;
        this->frequenz[0] = 1;
        this->sizee = 1;
        return;
    }

    int position = 0;
    while (position < this->sizee && this->relation(this->elements[position], elem)) {
        if ( this->elements[position] == elem) {
            this->frequenz[position]++; // element already exists
            return;
        }
        position++;
    }

    for (int i =  this->sizee; i > position; i--) {
        this->elements[i] =  this->elements[i - 1];
        this->frequenz[i] =  this->frequenz[i - 1];
    }

    this->elements[position] = elem;
    this->frequenz[position] = 1;
    this->sizee++;

    if ( this->sizee ==  this->capacity) {
        resizeUp();
    }
}
//worst case: Theta(size^2), best case: Theta(1), average case: O(size^2)
bool SortedBag::remove(TComp elem) {
    if (isEmpty()) {
        return false;
    }

    if (!search(elem))
        return false;

    int position=0;
    if (search(elem)){//save position
        for (int i = 0; i < this->sizee; i++) {
            if (this->elements[i] == elem) {
                position= i;
            }}
    }

    if(this->frequenz[position]==1) {
        for (int j = position; j < this->sizee - 1; j++)
            this->elements[j] = this->elements[j + 1];
        for (int j = position; j < this->sizee - 1; j++)
            this->frequenz[j] = this->frequenz[j + 1];
        this->sizee--;// decrement array size
    }else{
        this->frequenz[position]--;
    }

    if (this->sizee <= this->capacity / 4) {
        resizeDown();}

    return true;
}

//worst case: Theta(size), best case: Theta(1), average case: O(size)
bool SortedBag::search(TComp elem) const {
    for (int i = 0; i < this->sizee; i++) {
        if (this->elements[i] == elem) {
            return true; //  found
        }
    }
    return false; // not found
}

//worst case: Theta(size), best case: Theta(1), average case: O(size)
int SortedBag::nrOccurrences(TComp elem) const {
    for(int i=0;i<this->sizee;i++){
        if (this->elements[i]==elem) {
            return this->frequenz[i];
        }
    }
    return 0;
}

//worst case: Theta(size), best case: Theta(1), average case:O(size)
int SortedBag::size() const {
    int nrElements=0;
    for(int i=0;i<this->sizee;i++){
        nrElements+=this->frequenz[i];
    }
    return nrElements;
}

//worst case=Theta(size), best case=Theta(1), average case= O(size)
bool SortedBag::isEmpty() const {
    if (this->size() == 0)
        return true;
	return false;
}


SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}

//worst case=best case=average case=Theta(1)
SortedBag::~SortedBag() {
    delete[] this->elements;
}
