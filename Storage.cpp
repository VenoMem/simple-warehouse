#include "Storage.h"
#include <iostream>

bool isNumber(std::string* liczba);

Storage::Storage(const double capacity)
{
	index = 0;
	this->trolly = new SiteTrolly{ capacity };
	storage_contents.clear();
}

Storage::~Storage()
{
	delete trolly;
	
	for (auto element : storage_contents)
		delete element;

	std::cout << "Storage has been emptied and destroyed.\n" << std::endl;
}

void Storage::printContents() const
{
	for (auto element : storage_contents)
		element->printProduct();
}

void Storage::addProductToStorage(Product* product)
{
	storage_contents.push_back(product);
}

void Storage::addProductToTrolley(Product* product)
{
	storage_contents.push_back(product);
}

void Storage::addAmount()
{
	int index;
	double amount;

	for(;;)
	{
		this->printContents();
		std::cout << "Choose the product(by index_storage): ";

		try { index = readInt(); }
		catch (Tnumber_error& capsule)
		{
			std::cout << capsule.msg;
			continue;
		}

		try { if (isIndex(index, this->index)) break; }
		catch (Tindex_error& capsule) { std::cout << capsule.msg; }
	}

	for(;;)
	{
		storage_contents[index]->printProduct();
		std::cout << "How much units would you like to add: ";

		try
		{
			amount = readDouble();
			break;
		}
		catch (Tnumber_error& capsule) { std::cout << capsule.msg; }	
	}
	
	storage_contents[index]->setAmount(storage_contents[index]->getAmount() + amount);
	std::cout << "Amount of product has been updated.\n";
	storage_contents[index]->printProduct();
}

void Storage::removeAmount()
{
	int index;
	double amount;

	for (;;)
	{                                                   
		this->printContents();                           
		std::cout << "Choose the product(by index_storage): ";   

		try { index = readInt(); }
		catch (Tnumber_error& capsule)
		{
			std::cout << capsule.msg;
			continue;
		}

		try { if (isIndex(index, this->index)) break; }
		catch (Tindex_error& capsule) { std::cout << capsule.msg; }
	}

	for (;;)
	{
		storage_contents[index]->printProduct();
		std::cout << "How much units would you like to remove: ";

		try { amount = readDouble(); }
		catch (Tnumber_error &capsule)
		{
			std::cout << capsule.msg;
			continue;
		}

		double nowa_ilosc = storage_contents[index]->getAmount() - amount;

		if (nowa_ilosc < 0)    
		{                       
			std::cout << "Wrong amount! Please choose again.\n";
			continue;
		}
		storage_contents[index]->setAmount(nowa_ilosc);
		break;
	}

	std::cout << "Amount of product has been updated.\n";
	storage_contents[index]->printProduct();
}

void Storage::loadTrolleyFromStorage(Product* product)
{
	trolly->site_trolley_contents.push_back(product);
}

void Storage::unloadTrolleyToStorage()
{
	for (auto element : trolly->site_trolley_contents)
		storage_contents.push_back(element);
	
	trolly->clearContents();
	trolly->actual_capacity = trolly->max_lifting_capacity;
	std::cout << "Trolley has been emptied.\n";
}

bool Storage::isEmpty()
{
	return storage_contents.empty();
}

std::string readString()
{
	std::string line;
	std::getline(std::cin >> std::ws, line);
	return line;
}

int readInt()                           
{                                       
	std::string wybor = readString();
	if (!isNumber(&wybor)) { Tnumber_error capsule; capsule.msg = "It's not an integer!\n";  throw capsule; }
	return atoi(wybor.c_str());
}

bool isNumber(std::string* liczba)
{                                  
	for (char znak : *liczba)
		if (!isdigit(znak)) return false;

	return true;
}

double readDouble()
{
	bool sign = false;
	double result = 0;
	double after_comma = 0.1;
	
	std::string line = readString();
	for(unsigned int i = 0; i < line.size(); i++)
	{
		if(i == 0)
		{
			if (!isdigit(line[i])) { Tnumber_error capsule; capsule.msg = "It's not a numebr!\n"; throw capsule; }
			result = static_cast<double>(line[i]) - static_cast<double>('0');
		}
		else
		{
			if (!sign)
			{
				if (line[i] == '.' || line[i] == ',') sign = true;
				else {
					if (!isdigit(line[i])) { Tnumber_error capsule; capsule.msg = "It's not a numebr!\n"; throw capsule; }
					result = result * 10 + line[i] - '0';
				}
			}
			else
			{
				if (!isdigit(line[i])) { Tnumber_error capsule; capsule.msg = "It's not a numebr!\n"; throw capsule; }
				result = result + (static_cast<double>(line[i]) - static_cast<double>('0')) * after_comma;
				after_comma *= 0.1;
			}
		}
	}
	return  result;
}

bool isIndex(int index, int r_index)
{
	if (index < 0 || index >= r_index)
	{
		Tindex_error capsule;
		capsule.msg = "Wrong index!\n";
		throw capsule;
	}

	return true;
}

