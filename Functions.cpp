#include "Functions.h"
#include "LiquidCommodity.h"
#include "LooseCommodity.h"
#include "Commodity.h"
#include <iostream>

//Funkcje pomocnicze
int chosenStorage(const std::vector<Storage*>& vector_ref);
double giveWeight();
double giveAmount();
int giveType();

template<typename T>
T getNumber()
{
	T number;
	for (;;) {
		std::cout << "Give the number: ";

		try
		{
			number = static_cast<T>(readDouble());
			break;
		}
		catch (Tnumber_error& capsule) { std::cout << capsule.msg; }
	}

	return number;
}

//Stale do obslugi programu
static int id = 0; //indeks obiektu w ogole wszytskich magazynow

enum { by_the_piece = 1, loose, liquid };
enum {divide = 1, choose_different};

////////////////////////////////////////////////////////////////////////////
void showContents(std::vector<Storage*>& vector_ref)
{
	int i = 0;
	bool condition = true;
	for (auto element : vector_ref)
	{
		if (!element->isEmpty() || !element->trolly->isEmpty())
		{
			std::cout << "Contents of " << i << " storage: " << std::endl;
			element->printContents();
			std::cout << "Contents of storage's trolley: " << std::endl;
			element->trolly->showContents();
			i++;
			condition = false;
		}
	}
	if (condition)
		std::cout << "There is not any product in storages yet.\n";
}

void removeStorage(std::vector<Storage*>& vector_ref)
{
	int choice = chosenStorage(vector_ref);
	delete vector_ref[choice];
	vector_ref.erase(vector_ref.begin() + choice);
}

void addStorage(std::vector<Storage*>& vector_ref)
{
	double capacity;
	for (;;) {
		std::cout << "Give the trolley capacity: ";

		try
		{
			capacity = readDouble();
			break;
		}
		catch (Tnumber_error &capsule){	std::cout << capsule.msg; }
	}
	vector_ref.push_back(new Storage(capacity));
}

void exitProgram(std::vector<Storage*>& vector_ref)
{
	for (auto element : vector_ref)
		delete element;
}

void unloadTrolley(std::vector<Storage*>& vector_ref)
{
	int choice = chosenStorage(vector_ref);
	
	if (vector_ref[choice]->trolly->isEmpty())
	{
		std::cout << "Trolley is empty." << std::endl;
		return;
	}

	std::cout << "Trolley has been emptied." << std::endl;
	vector_ref[choice]->trolly->clearContents();
}

void unloadTrolleyToStorage(std::vector<Storage*>& vector_ref)
{
	int choice = chosenStorage(vector_ref);

	if(vector_ref[choice]->trolly->isEmpty())
	{
		std::cout << "Trolley is empty." << std::endl;
		return;
	}

	vector_ref[choice]->unloadTrolleyToStorage();
}

void removeAmountFromStorage(std::vector<Storage*>& vector_ref)
{
	int choice = chosenStorage(vector_ref);

	if (vector_ref[choice]->isEmpty())
	{
		std::cout << "Storage is empty." << std::endl;
		return;
	}
	
	vector_ref[choice]->removeAmount();
}

void addAmountToStorage(std::vector<Storage*>& vector_ref)
{
	int choice = chosenStorage(vector_ref);

	if (vector_ref[choice]->isEmpty())
	{
		std::cout << "Storage is empty." << std::endl;
		return;
	}

	vector_ref[choice]->addAmount();
}

void addProductToStorage(std::vector<Storage*>& vector_ref)
{
	int choice = chosenStorage(vector_ref);
	
	bool condition = true;
	while (condition) {
		std::cout << "///////////////////////////////////\n" <<
					 "	  1 By the piece	\n" <<
					 "	  2 Loose			\n" <<
					 "	  3 Liquid			\n" <<
					 "///////////////////////////////////" << std::endl;
		std::cout << "Choose the type of product(by number)\n";
		int next_choice = getNumber<int>();
		std::cout << "Give the name of the product: ";
		std::string name = readString();
		std::cout << "Give weight per unit\n";
		double weight = getNumber<double>();

		switch (next_choice)
		{
		case by_the_piece:	vector_ref[choice]->addProductToStorage(new Commodity(id, vector_ref[choice]->index, name, 0, weight));
							vector_ref[choice]->index++;
							id++;
							condition = false; break;

		case loose:			vector_ref[choice]->addProductToStorage(new LooseCommodity(id, vector_ref[choice]->index, name, 0, weight));
							vector_ref[choice]->index++;
							id++;
							condition = false; break;

		case liquid:		vector_ref[choice]->addProductToStorage(new LiquidCommodity(id, vector_ref[choice]->index, name, 0, weight));
							vector_ref[choice]->index++;
							id++;
							condition = false; break;

		default: std::cout << "There is not such a type of product! Please choose again.\n";
		}
	}
}

void addProductToTrolley(std::vector<Storage*>& vector_ref)
{
	int choice = chosenStorage(vector_ref);
	int next_choice;
	
	bool condition = true;
	while (condition) {
		std::cout << "///////////////////////////////////\n" <<
					 "	  1 By the piece	\n" <<
					 "	  2 Loose			\n" <<
					 "	  3 Liquid			\n" <<
					 "///////////////////////////////////" << std::endl;
		std::cout << "Trolley capacity left: " << vector_ref[choice]->trolly->getCapacity() << std::endl;

		std::cout << "Choose the type of product(by number)\n";
		next_choice = getNumber<int>();
		std::cout << "Give the name of the product: ";
		std::string name = readString();
		std::cout << "Give amount of product\n";
		double amount = getNumber<double>();
		std::cout << "Give weight per unit\n";
		double weight = getNumber<double>();

		if (amount * weight > vector_ref[choice]->trolly->getCapacity())
		{
			std::cout << "Trolley capacity: " << vector_ref[choice]->trolly->getCapacity();
			std::cout << "\nProduct weight: " << amount * weight;
			std::cout << "\nSite trolley has not enough capacity to support this product. Please choose again.\n";
			continue;
		}

		switch (next_choice)
		{
		case by_the_piece:	vector_ref[choice]->trolly->site_trolley_contents.push_back(new Commodity(id, vector_ref[choice]->index, name, static_cast<int>(amount), weight));
							vector_ref[choice]->trolly->setCapacity(vector_ref[choice]->trolly->getCapacity() - amount * weight);
							std::cout << "Trolley capacty left: " << vector_ref[choice]->trolly->getCapacity() << std::endl;
							vector_ref[choice]->index++;
							id++;
							break;

		case loose:			vector_ref[choice]->trolly->site_trolley_contents.push_back(new LooseCommodity(id, vector_ref[choice]->index, name, amount, weight));
							vector_ref[choice]->trolly->setCapacity(vector_ref[choice]->trolly->getCapacity() - amount * weight);
							std::cout << "Trolley capacty left: " << vector_ref[choice]->trolly->getCapacity() << std::endl;
							vector_ref[choice]->index++;
							id++;
							break;

		case liquid:		vector_ref[choice]->trolly->site_trolley_contents.push_back(new LiquidCommodity(id, vector_ref[choice]->index, name, amount, weight));
							vector_ref[choice]->trolly->setCapacity(vector_ref[choice]->trolly->getCapacity() - amount * weight);
							std::cout << "Trolley capacty left: " << vector_ref[choice]->trolly->getCapacity() << std::endl;
							vector_ref[choice]->index++;
							id++;
							break;

		default: std::cout << "There is not such a type of product! Please choose again.\n";
		}

		int more_choice;
		for (;;) {
			std::cout << "Do you want to add more products to trolley(1 for yes, 0 for no)? ";

			try { more_choice = readInt(); }
			catch (Tnumber_error &capsule)
			{
				std::cout << capsule.msg;
				continue;
			}
			if (more_choice == 0) { condition = false; break; }
			if (more_choice == 1) { break; }
			std::cout << "No such an option!" << std::endl;
		}
	}
}

void loadTrolleyFromStorage(std::vector<Storage*>& vector_ref)
{	
	int choice = chosenStorage(vector_ref);

	if(vector_ref[choice]->isEmpty())
	{
		std::cout << "Storage is empty.\n";
		return;
	}

	bool condition = true;
	while (condition)
	{
		vector_ref[choice]->printContents();
		std::cout << "Trolley capacity: " << vector_ref[choice]->trolly->getCapacity() << std::endl;
		std::cout << "Choose the product(by index_storage): ";
		int index;

		for (;;) {

			try{ index = getNumber<int>(); }
			catch (Tnumber_error& capsule)
			{
				std::cout << capsule.msg;
				continue;
			}

			try { if (isIndex(index, vector_ref[choice]->index)) break; }
			catch (Tindex_error& capsule) { std::cout << capsule.msg; }
		}

		std::cout << "Give amount of product\n";
		double amount = getNumber<double>();
		if(amount > vector_ref[choice]->storage_contents[index]->getAmount())
		{
			std::cout << "Not enough product in the storage.\n";
			continue;
		}

		if(vector_ref[choice]->storage_contents[index]->getUnitWeight() * amount > vector_ref[choice]->trolly->getCapacity())
		{
			std::cout << "It is impossible to load trolley, product weights too much\n";
			continue;
		}

		Product* temp_pointer = vector_ref[choice]->storage_contents[index]->divideProduct(amount, id, vector_ref[choice]->index);
		vector_ref[choice]->loadTrolleyFromStorage(temp_pointer);
		vector_ref[choice]->trolly->setCapacity(vector_ref[choice]->trolly->getCapacity() - temp_pointer->getWeight());
		id++;
		vector_ref[choice]->index++;
		
		if (vector_ref[choice]->trolly->getCapacity() == 0) return;

		int next_choice;
		for (;;) {
			std::cout << "Do want to load trolley(1 for yes, 0 for no)?";

			try { next_choice = readInt(); }
			catch (Tnumber_error &capsule)
			{
				std::cout << capsule.msg;
				continue;
			}

			if (next_choice == 0) { condition = false; break; }
			if (next_choice == 1) { break; }
			std::cout << "No such an option!" << std::endl;
		}
	}
}

////////////////////////////////////////////////////////////////////////////
int chosenStorage(const std::vector<Storage*>& vector_ref)
{
	int choice;

	for (;;) {
		for (unsigned int j = 0; j < vector_ref.size(); j++)
			std::cout << "Storage\t" << j << std::endl;

		std::cout << "Choose storage: \n";

		try { choice = readInt(); }
		catch (Tnumber_error &capsule)
		{
			std::cout << "Wrong infomration.\n";
			continue;
		}
		
		if (choice <= -1 || choice >= static_cast<int>(vector_ref.size())) { std::cout << "Wrong infomration.\n"; continue; }
		break;
	}

	return choice;
}

//szablon tych funkcji
double giveWeight()
{
	double weight;

	for (;;) {
		std::cout << "Give the weight of the product for one unit: ";

		try
		{
			weight = readDouble();
			break;
		}
		catch (Tnumber_error &capsule){	std::cout << capsule.msg; }
	}

	return weight;
}

double giveAmount()
{
	double amount;
	for (;;) {
		std::cout << "Give the amount of the product: ";

		try
		{
			amount = readDouble();
			break;
		}
		catch (Tnumber_error& capsule) { std::cout << capsule.msg; }
	}

	return amount;
}

int giveType()
{
	int choice;
	for (;;) {
		std::cout << "What type of product would you like to add(number): \n";

		try
		{
			choice = readInt();
			break;
		}
		catch (Tnumber_error& capsule) { std::cout << capsule.msg; }
	}
	return choice;
}
