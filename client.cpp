// client.cpp -- by Andrew Stevenson -- Assignment 4 -- CS163 Summer 2019
// Display a simple test menu facilitating the test of the event_table ADT

#include <fstream>
#include <iostream>
#include "table.h"

using namespace std;

// read the indicated input file to the event_table object
void read_file(ifstream & fin, event_table& targ_table);

// print the testing menu
void print_menu( void );

// read an event_record from input stream into table object
void read_keyboard(istream & fin, event_table& targ_table); 

int main( void )
{
	ifstream fin;
	event_table * my_table = new event_table;
	event_record my_record;
	char input;
	char input_str[256];

	print_menu();

   do
   {
		cout << endl;
      cout << "Enter Command: ";
      cin.get(input);
      cin.ignore(256,'\n');
      if(!cin)
         cin.clear();
      switch(input)
      {
			case '1': // Load data from Events.txt
				fin.open("Events.txt");
				read_file(fin, *my_table);
				fin.close();
				break;

			case '2': // Load data from Events_rand.txt
				fin.open("Events_rand.txt");
				read_file(fin, *my_table);
				fin.close();
				break;
			
			case '3': // Add an event from keyboard
				cout << "Enter Name, Desc, Date, Time, and Price separated by carriage returns." << endl;
				read_keyboard(cin, *my_table);
				break;

			case '4': // Retrieve a single record
				cout << "Enter name: ";
				cin.getline(input_str, 256);
				if( my_table->retrieve(input_str, my_record) )
				{
					cout << "Retrieve Sucessful!" << endl;
					cout << my_record.name << my_record.desc << my_record.date;
					cout << my_record.time << my_record.price << endl << endl;
					init_event_record(my_record);
				}
				else
					cout << "Retrieve Failed!" << endl;
				break;

			case '5': // Remove a single record
				cout << "Enter name: ";
				cin.getline(input_str, 256);
				if( my_table->remove(input_str) )
					cout << "Delete Sucessful!" << endl;
				else
					cout << "Delete Failed!" << endl;
				break;
		
			case '6': // Print a single record
				cout << "Enter name: ";
				cin.getline(input_str, 256);
				if( my_table->display_single(input_str))
					cout << "Display Sucessful!" << endl;
				else
					cout << "Display Failed!" << endl;
				break;

			case '7': // Print all records
				if( my_table->display_all() )
					cout << "Display Sucessful!" << endl;
				else
					cout << "Display Failed!" << endl;
				break;

			case '8': // Print tree height
				cout << endl << "Tree height: " << my_table->height() << endl;
				break;

			case 'M': // Print this menu
				print_menu();
				break;
		
			default:

				break;
		}
	} while(input != 'Q');

	delete my_table;
	return 0;
}



void print_menu( void )
{
	cout << endl;
	cout << "1 - Load data from Events.txt" << endl;
	cout << "2 - Load data from Events_rand.txt" << endl;
	cout << "3 - Add an event from keyboard" << endl;
	cout << "4 - Retrieve a single record" << endl;
	cout << "5 - Remove a single record" << endl;
	cout << "6 - Print a single record" << endl;
	cout << "7 - Print all records" << endl;
	cout << "8 - Print tree height" << endl;
	cout << "M - Print this menu" << endl;
	cout << "Q - Exit program" << endl;
}

void read_keyboard(istream & fin, event_table& targ_table)
{
	char in_name[150]; // just static allocate adequate memory for testing
	char in_desc[300]; // to avoid fiddling with dynamic 
	char in_date[20];  // allocating on the client side
	char in_time[20];
	char in_price[15];
	event_record in_event;
	in_event.name = in_name;
	in_event.desc = in_desc;
	in_event.date = in_date;
	in_event.time = in_time;
	in_event.price = in_price;

	fin.getline(in_event.name, 150);
	fin.getline(in_event.desc, 300);
	fin.getline(in_event.date, 20);
	fin.getline(in_event.time, 20);
	fin.getline(in_event.price, 15);

	cout << endl;
	if( targ_table.add(in_event) )
		cout << "Add Successful!";
	else
		cout << "Add failed!";
	cout << endl;

	return;
}

void read_file(ifstream & fin, event_table& targ_table)
{
	char in_name[150]; // just static allocate adequate memory for testing
	char in_desc[300]; // to avoid fiddling with dynamic 
	char in_date[20];  // allocating on the client side
	char in_time[20];
	char in_price[15];
	event_record in_event;
	in_event.name = in_name;
	in_event.desc = in_desc;
	in_event.date = in_date;
	in_event.time = in_time;
	in_event.price = in_price;

	int counter = 0;
	int incrementor = 1;
	int printable = 1;
	cout << endl << "# of Records Imported, BST Height" << endl;

	while(fin)
	{
		++counter;
		fin.getline(in_event.name, 150, '|');
		fin.getline(in_event.desc, 300, '|');
		fin.getline(in_event.date, 20, '|');
		fin.getline(in_event.time, 20, '|');
		fin.getline(in_event.price, 15);
		targ_table.add(in_event);
		if(counter==(printable))
		{
			cout << counter << "," << targ_table.height() << endl;
			printable += (incrementor <<= 1);
		}
	}

	return;
}
