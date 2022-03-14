#include "LiquidCommodity.h"
#include <iostream>

LiquidCommodity::~LiquidCommodity()
{
	std::cout << name << " has been deleted.\n";
}

void LiquidCommodity::printProduct() const
{
	std::cout << "Product: -id: " << id << " -index_storage: " << index_storage << " -name: " << name << " -amount: " << amount << " -weight per unit: " << weight << std::endl;
}

void LiquidCommodity::setAmount(const double amount)
{
	this->amount = amount;
}

double LiquidCommodity::getAmount() const
{
	return amount;
}

double LiquidCommodity::getUnitWeight() const
{
	return weight;
}

double LiquidCommodity::getWeight() const
{
	return weight * amount;
}

Product* LiquidCommodity::divideProduct(const double amount, const int id, const int index_storage)
{
	this->amount = this->amount - amount;
	Product* temp_pointer = new LiquidCommodity(id, index_storage, name, amount, weight);
	return temp_pointer;
}

void LiquidCommodity::mergeProduct(Product* product)
{
	this->amount = this->amount + dynamic_cast<LiquidCommodity*>(product)->amount;
	delete product;
}
