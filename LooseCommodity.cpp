#include "LooseCommodity.h"
#include <iostream>

LooseCommodity::~LooseCommodity()
{
	std::cout << name << " has been deleted.\n";
}

void LooseCommodity::printProduct() const
{
	std::cout << "Product: -id: " << id << " -index_storage: " << index_storage << " -name: " << name << " -amount: " << amount << " -weight per unit: " << weight << std::endl;
}

void LooseCommodity::setAmount(const double amount)
{
	this->amount = amount;
}

double LooseCommodity::getAmount() const
{
	return amount;
}

double LooseCommodity::getUnitWeight() const
{
	return weight;
}

double LooseCommodity::getWeight() const
{
	return weight * amount;
}

Product* LooseCommodity::divideProduct(const double amount, const int id, const int index_storage)
{
	this->amount = this->amount - amount;
	Product* temp_pointer = new LooseCommodity(id, index_storage, name, amount, weight);
	return temp_pointer;
}

void LooseCommodity::mergeProduct(Product* product)
{
	this->amount = this->amount + dynamic_cast<LooseCommodity*>(product)->amount;
	delete product;
}
