// table.cpp -- by Andrew Stevenson -- Assignment 4 -- CS163 Summer 2019
// table module implements a table ADT for storage & retrieval of event
// records, suitable for searching and display to users

#include "table.h"
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

// default constructor
event_table::event_table()
{
	root = NULL;
	return;
}



// Destructor
event_table::~event_table()
{
	init(root);
	return;
}


// recursively delete the nodes in tree, setting class member
// "root" to null
bool event_table::init(node<event_record> *& root)
{
	bool retval;

	if(root==NULL)
		return false;

	//postorder node deletion
	retval = init(root->left) || init(root->right);

	init_event_record(root->data);
	delete root;
	return retval;
}



// Client code must call this to unalloc after call
// to retrieve()
void init_event_record(event_record & to_init)
{
	dealloc_str(to_init.name);
	dealloc_str(to_init.desc);
	dealloc_str(to_init.date);
	dealloc_str(to_init.time);
	dealloc_str(to_init.price);
	return;
}


// simple utility function that deallocates memory if pointer is not null
void dealloc_str(char * ch)
{
	if(ch) delete [] ch;
	ch=NULL;
	return;
}



// simple utility function that allocates memory for new string and
// makes necessary library calls to copy contents of string array
void alloc_str(char *& to, char * from)
{
   if(from==NULL) // don't need to copy null string
   {
      to = NULL;
      return;
   }
   to = new char[strlen(from) + 1]; // add room for string terminator
   strcpy(to, from);
   return;
}



// add an event reocrd to the table ADT
// wrapper function
bool event_table::add(const event_record& to_add)
{
	if(to_add.name == NULL || to_add.name[0] == '\0')
		return false;

	return add(to_add, root);
}



// add an event reocrd to the table ADT
// recursive function for add()
bool event_table::add(const event_record& to_add, node<event_record> *& root)
{
	if(root==NULL) // base case
	{
		root = new node<event_record>;
		copy_event_record(root->data, to_add);
		root->right = NULL;
		root->left = NULL;
		return true;
	}
	if( strcmp( to_add.name, root->data.name ) >= 0)
		return add(to_add, root->right);
	else
		return add(to_add, root->left);
}


 // copy a record from one record object to another
void copy_event_record(event_record& to, const event_record& from)
{
	if(&to == &from) // avoid self-copy
		return;

	alloc_str(to.name, from.name);
	alloc_str(to.desc, from.desc);
	alloc_str(to.date, from.date);
	alloc_str(to.time, from.time);
	alloc_str(to.price, from.price);
	return;
}



// retrieve a single record from the table adt
// wrapper function
bool event_table::retrieve(char * key, event_record& to_get) const
{
	if(key  == NULL || key[0] == '\0')
		return false;
	
	return retrieve(key, to_get, root);
}



// retrieve FIRST matching record
// recursive function
bool event_table::retrieve(char * key, event_record& to_get, node<event_record> * root) const
{
	if(root == NULL)
		return false;

	int comparison = strcmp(key, root->data.name);

	if( comparison == 0 )
	{
		copy_event_record(to_get, root->data);
		return true;
	}
	if( comparison > 0 )
		return retrieve(key, to_get, root->right);
	else
		return retrieve(key, to_get, root->left);
}



// remove a matching record from the table adt
// wrapper function
bool event_table::remove(char* key)
{
	if(key == NULL || key[0] == '\0') 
		return false;

	return remove(key, root);
}



// recursive function
// find node for deletion and dispatch delete_node() call
bool event_table::remove(char* key, node<event_record>*& root)
{
	if(root == NULL)
		return false;

	int comparison = strcmp(key, root->data.name);

	if( comparison == 0 )
	{
		delete_node(root);
		return true;
	}
	if( comparison > 0 )
		return remove(key, root->right);
	else
		return remove(key, root->left);
}



// deletes parameter 
// adjusts neighboring nodes, including finding IOS
// NOTE: deletion logic separated from remove() in order to
// 	improve readability.
void event_table::delete_node(node<event_record>*& root)
{
	node<event_record>* to_delete = root;	// holder to allow pointer adjustment before deletion

	// Leaf
	if( root->left == NULL && root->right == NULL)
	{
		root = NULL;
		init_event_record(to_delete->data);
		delete to_delete;
		return;
	}

	// internal node with two children
	if( root->right != NULL && root->left != NULL)
	{
		// find in order sucessor (IOS)
		node<event_record>* IOS = root->right;
		node<event_record>* IOS_parent = root;
		while(IOS->left != NULL)
		{
			IOS_parent = IOS;
			IOS = IOS->left;
		}

		// check if root->right was the IOS
		if(IOS_parent == to_delete)
		{
			IOS->left = root->left;
			root = IOS;
		}
		else
		{
			// IOS's right child may need to be adopted
			IOS_parent->left = IOS->right;
		
			// replace root with IOS
			IOS->left = root->left;
			IOS->right = root->right;
			root = IOS;
		}

		init_event_record(to_delete->data);
		delete to_delete;
		return;
	}

	// Internal node w/ left child
	if( root->left != NULL ) 
	{
		root = root->left;
		init_event_record(to_delete->data);
		delete to_delete;
		return;
	}
	else // Internal node w/ right child
	{
		root = root->right;
		init_event_record(to_delete->data);
		delete to_delete;
		return;
	}

}



// display a single matching record to the output stream
// Wrapper function
bool event_table::display_single(char* key) const
{
	if(key  == NULL || key[0] == '\0')
		return false;
	
	return display_single(key, root);
}



// Display a single record from tree
// Recursive function
bool event_table::display_single(char* key, node<event_record> * root) const
{
	if(root == NULL)
		return false;
	
	int comparison = strcmp(key, root->data.name);

	if( comparison == 0 )
	{
		display_node(root);
		return true;
	}
	if( comparison > 0 )
		return display_single(key, root->right);
	else
		return display_single(key, root->left);
}



// Dispatch the calls to cout to display a given node's data
void event_table::display_node(node<event_record>* head) const
{
	cout << endl;
	cout << "Event Name: " << head->data.name << endl;
	cout << "Description: " << head->data.desc << endl;
	cout << "Date: " << head->data.date << endl;
	cout << "Time: " << head->data.time << endl;
	cout << "Price: " << head->data.price << endl;
	cout << endl;
	return;
}



// display every single record to the output stream
// using inorder traversal
// wrapper function
bool event_table::display_all( void ) const
{
	if(root==NULL)
		return false;

	return display_all(root);
}



// recursive function, using inorder traversal
bool event_table::display_all( node<event_record>* root ) const
{
	if(root == NULL)
		return true;

	display_all(root->left);

	display_node(root);

	display_all(root->right);

	return true;
}



// Returns the current height of the tree
// Wrapper function
int event_table::height( void ) const
{
	return height(root);
}



// Returns the current height of the tree
// Recursive function
int event_table::height( node<event_record>* root) const
{
	if(root == NULL)
		return 0;
	return 1+max(height(root->left), height(root->right));
}
