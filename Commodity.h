#ifndef COMMODITY_H
#define COMMODITY_H

#include "Product.h"
#include <string>

class Commodity : public Product
{
private:
	const std::string name;
	int amount;
	const double weight;
	
public:
	explicit Commodity(const int id, const int index_storage, const std::string &name, const int amount, const double weight) : Product(id, index_storage), name{ name }, amount{ amount }, weight{ weight } {}
	~Commodity() override;

	void printProduct() const override;
	void setAmount(const double amount) override;
	void mergeProduct(Product* product) override;

	double getAmount() const override;
	double getWeight() const override;
	double getUnitWeight() const override;
	
	Product* divideProduct(const double amount, const int id, const int id_storage) override;
};

#endif