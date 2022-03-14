#include "SiteTrolley.h"
#include <iostream>

SiteTrolly::~SiteTrolly()
{
	for (auto element : site_trolley_contents)
		delete element;
	
	std::cout << "Site trolley has been emptied and destroyed.\n";
}

double SiteTrolly::getCapacity() const
{
	return actual_capacity;
}

void SiteTrolly::setCapacity(const double capacity)
{
	actual_capacity = capacity;
}

void SiteTrolly::showContents() const
{
	for (auto element : site_trolley_contents)
		element->printProduct();
}

bool SiteTrolly::isEmpty()
{
	return site_trolley_contents.empty();
}

void SiteTrolly::clearContents()
{
	site_trolley_contents.clear();
}


