#include "Functions.h"
#include <fstream>
#include <iostream>


using namespace std;

enum { add_storage = 1, add_product_to_storage, add_amount_to_storage, load_on_trolley_from_storage, add_product_to_trolley,
		unload_trolley_to_storage, unload_trolley, remove_storage, remove_amount_from_storage, show_contents, exit_program };

vector<Storage*> econimic_zone;

int main(int argc, char* argv[])
{
	//Do obslugi pliku, wypelniamy bufor poleceniami
	std::fstream in;
	if (argc > 1)
	{
		in.open(argv[1]);
		std::cin.rdbuf(in.rdbuf());
	}

	int choice;
	for(;;){
		cout << "/////////////////////////////////////\n" <<
				"                  MENU				  \n" <<
				"      1 Add storage				  \n" <<
				"      2 Add product to storage		  \n" <<
				"      3 Add amount to storage		  \n" <<
				"      4 Load on trolley from storage \n" <<
				"      5 Add product to trolley		  \n" <<
				"      6 Unload trolley to storage	  \n" <<
				"      7 Unload trolley				  \n" <<
				"      8 Remove storage				  \n" <<
				"      9 Remove amount from storage	  \n" <<
				"      10 Show contents				  \n" <<
				"      11 Exit program				  \n" <<
				"//////////////////////////////////////\n";
		cout << "Choose an action: ";

		try{ choice = readInt(); }
		catch (Tnumber_error &capsule)
		{
			cout << "Wrong choice!\n";
			continue;
		}
		
		switch (choice)
		{
		case add_storage:					addStorage(econimic_zone);
											break;
			
		case add_product_to_storage:		if (econimic_zone.empty()) { cout << "There is not any storage yet.\n"; break; }
											addProductToStorage(econimic_zone);
											break;

		case add_amount_to_storage:			if (econimic_zone.empty()) { cout << "There is not any storage yet.\n"; break; }
											addAmountToStorage(econimic_zone);
											break;

		case load_on_trolley_from_storage:	if (econimic_zone.empty()) { cout << "There is not any storage yet.\n"; break; }
											loadTrolleyFromStorage(econimic_zone);
											break;
			
		case add_product_to_trolley:		if (econimic_zone.empty()) { cout << "There is not any storage yet.\n"; break; }
											addProductToTrolley(econimic_zone);
											break;

		case unload_trolley_to_storage:		if (econimic_zone.empty()) { cout << "There is not any storage yet.\n"; break; }
											unloadTrolleyToStorage(econimic_zone);
											break;

		case unload_trolley:				if (econimic_zone.empty()) { cout << "There is not any storage yet.\n"; break; }
											unloadTrolley(econimic_zone);
											break;
			
		case remove_storage:				if (econimic_zone.empty()) { cout << "There is not any storage yet.\n"; break; }
											removeStorage(econimic_zone);
											break;

		case remove_amount_from_storage:	if (econimic_zone.empty()) { cout << "There is not any storage yet.\n"; break; }
											removeAmountFromStorage(econimic_zone);
											break;
			
		case show_contents:					if (econimic_zone.empty()) { cout << "There is not any storage yet.\n"; break; }
											showContents(econimic_zone);
											break;

		case exit_program:					exitProgram(econimic_zone);
											return 0;
		default:			cout << "There is not such an option in MENU! Please choose again.\n";
		}	
	}
}
