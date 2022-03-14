#ifndef LIQUIDCOMMODITY_H
#define LIQUIDCOMMODITY_H

#include "Product.h"
#include <string>

class LiquidCommodity : public Product
{
private:
	const std::string name;
	double amount;
	const double weight;

public:
	explicit LiquidCommodity(const int id, const int index_storage, const std::string &name, const double amount, const double weight) : Product(id, index_storage), name{ name }, amount{ amount }, weight{ weight } {}
	~LiquidCommodity() override;

	void printProduct() const override;
	void setAmount(const double amount) override;
	void mergeProduct(Product* product) override;

	double getAmount() const override;
	double getWeight() const override;
	double getUnitWeight() const override;
	
	Product* divideProduct(const double amount, const int id, const int index_storage) override;
};


#endif