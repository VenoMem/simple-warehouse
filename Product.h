#ifndef PRODUCT_H
#define PRODUCT_H

class Product
{
protected:
	const int id;
	const int index_storage;

public:
	explicit Product(const int id, const int index_storage) : id{ id }, index_storage{ index_storage } {}
	virtual ~Product() = 0;

	virtual void printProduct() const = 0;
	virtual void setAmount(const double) = 0;
	virtual void mergeProduct(Product* product) = 0;

	virtual double getAmount() const = 0;
	virtual double getWeight() const = 0;
	virtual double getUnitWeight() const = 0;

	virtual Product* divideProduct(const double, const int, const int) = 0;
};

#endif