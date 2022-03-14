#ifndef SITETROLLEY_H
#define SITETROLLEY_H

#include "Product.h"
#include <vector>

class Storage;

class SiteTrolly
{
private:
	std::vector<Product*> site_trolley_contents;
	const double max_lifting_capacity;
	double actual_capacity;

public:
	SiteTrolly(const double capacity) : max_lifting_capacity(capacity)
	{
		actual_capacity = capacity;
		site_trolley_contents.clear();
	}
	~SiteTrolly();

	double getCapacity() const;

	bool isEmpty();
	
	void setCapacity(const double capacity);
	void showContents() const;
	void clearContents();

	friend class Storage;
	friend void addProductToTrolley(std::vector<Storage*>& vector_ref);
	friend void loadTrolleyFromStorage(std::vector<Storage*>& vector_ref);
};

#endif