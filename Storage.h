#ifndef STORAGE_H
#define STORAGE_H

#include "Product.h"
#include "SiteTrolley.h"
#include <vector>
#include <string>

int readInt();
double readDouble();
std::string readString();
bool isIndex(int index, int r_index);
struct Tnumber_error { std::string msg; };
struct Tindex_error { std::string msg; };

class Storage
{
private:
	std::vector<Product*> storage_contents;
	SiteTrolly* trolly;
	int index;

public:
	Storage(const double capacity);
	~Storage();

	void printContents() const;
	void addProductToStorage(Product* product);
	void addProductToTrolley(Product* product);
	void addAmount();
	void removeAmount();
	void unloadTrolleyToStorage();
	void loadTrolleyFromStorage(Product* product);
	
	bool isEmpty();

	friend void addProductToStorage(std::vector<Storage*>& vector_ref);
	friend void showContents(std::vector<Storage*>& vector_ref);
	friend void unloadTrolley(std::vector<Storage*>& vector_ref);
	friend void unloadTrolleyToStorage(std::vector<Storage*>& vector_ref);
	friend void addProductToTrolley(std::vector<Storage*>& vector_ref);
	friend void loadTrolleyFromStorage(std::vector<Storage*>& vector_ref);
};

#endif