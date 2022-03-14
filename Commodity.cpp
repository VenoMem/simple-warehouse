#include "Commodity.h"
#include <iostream>

Commodity::~Commodity()
{
	std::cout << name << " has been deleted.\n";
}

void Commodity::printProduct() const
{
	std::cout << "Product: -id: " << id << " -index_storage: " << index_storage << " -name: " << name << " -amount: " << amount << " -weight per unit: " << weight << std::endl;
}

void Commodity::setAmount(const double amount)
{
	this->amount = static_cast<int>(amount);
}

double Commodity::getAmount() const
{
	return amount;
}

double Commodity::getUnitWeight() const
{
	return weight;
}

double Commodity::getWeight() const
{
	return weight * amount;
}

Product* Commodity::divideProduct(const double amount, const int id, const int index_storage)
{
	this->amount = this->amount - static_cast<int>(amount);
	Product* temp_pointer = new Commodity(id, index_storage, name, static_cast<int>(amount), weight);
	return temp_pointer;
}

void Commodity::mergeProduct(Product* product)
{
	this->amount = this->amount + dynamic_cast<Commodity*>(product)->amount;
	delete product;
}
