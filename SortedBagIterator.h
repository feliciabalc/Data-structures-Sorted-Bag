#pragma once
#include "SortedBag.h"

class SortedBag;

class SortedBagIterator
{
	friend class SortedBag;

public:
	const SortedBag& bag;
	SortedBagIterator(const SortedBag& b);

    int current_element;
    int current_frecv;

public:
	TComp getCurrent();
	bool valid();
	void next();
	void first();
};

