// table.h -- by Andrew Stevenson -- Assignment 4 -- CS163 Summer 2019
// table module implements a table ADT for storage & retrieval of event
// records, suitable for searching and display to users

#ifndef TABLE__H__
#define TABLE__H__


struct event_record;

/* PURPOSE: Deallocate an event_record populated with dynamically
		allocated strings.
	INPUT: to_init: an event_record to deallocate */
// WARNING WARNING call this method to free memory allocated by
// copy_event_record AND the retrieve() method.
void init_event_record(event_record & to_init);

/* PURPOSE: copy the data of an event_record
	INPUT: to: empty event_record object in which data will be copied
			from: data_record object from which data will be copied.*/
void copy_event_record(event_record& to, const event_record& from);


/* PURPOSE: free up dynamically allocated data from a string
		** CALLED BY init_event_record();
	INPUT: ch: pointer to dynamically allocated string. */
void dealloc_str(char * ch);

/* PURPOSE: allocate memory and copy data in to new string
		** CALLED by copy_event_record and ADT class methods
	INPUT: to: pointer to which memory will be allocated
		from: string that is to be copied. */
void alloc_str(char *& to, char * from);

/* PURPOSE: node structure supporting hash table data structure.
		Used internally by ADT. */
template <class Type>
struct node
{
	Type data; 				//data stored
	node<Type>* right;	//right child in tree
	node<Type>* left;		//left child in tree
};


/* PURPOSE: record class suitable for handling of event record data.
		Required for leveraging the event_table ADT.*/
struct event_record
{
	char * name;	// name of event
	char * desc;	// description of event
	char * date;	// date of event -- can be range of dates
	char * time;	// time of event -- can be range of times
	char * price;	// price of event -- can be price range
};


/* PURPOSE: storage and retrieval of large number of event_record
		data records. This class implements a table ADT. */
class event_table
{
public:
	// default constructor
	event_table();

	// destructor
	~event_table();		

	/* PURPOSE: add a new record to the table.
		INPUT: to_add: event reocrd that will be copied into table 
		OUTPUT: return value: true if record was sucessfully added,
			false otherwise. */
	bool add(const event_record& to_add);

	/* PURPOSE: retrieve a record from the table.
		INPUT: key: string to search for match.
			to_get: empty record into which data of matching record
				will  be copied.
		OUTPUT: true if record was sucessfully located and copied; false
			otherwise.
		WARNING: memory in copied record will be dynamically allocated! 
			Deallocate with init_event_record()! */
	bool retrieve(char * key, event_record& to_get) const;

	/* PURPOSE: remove a record from the table.
		INPUT: key: string to match with deletion candidates
		OUTPUT: true if record matched and deleted; false otherwise.
		NOTE: this function deletes *all* matching records. */
	bool remove(char* key);

	/* PURPOSE: display a single record to the output stream
		INPUT: key: string to match with display records.
		OUTPUT: true if record located and displayed; false otherwise. */
	bool display_single(char* key) const;

	/* PURPOSE: display all records stored in table, in order stored. 
		OUTPUT: true if at least one record displayed; false otherwise. */
	bool display_all( void ) const;

	/* PURPOSE: return the height of the tree (in nodes, not edges)
		OUTPUT: number of nodes (not edges) in tree at maximum height. 
		NOTE: this function does not belong in final ADT, as it exposes
			details of underlying data structure to client. */
	int height( void ) const; 

private:

	/* PURPOSE: execute the deletion logic separately from the recusive
			logic in remove()
		INPUT: root: node to be deleted. */
	void delete_node(node<event_record>*& root);

	/* PURPOSE: recursively delete all the nodes in the tree, setting root to NULL
		INPUT: root: next node to be deleted.
		OUTPUT: true if at least one node was deleted; false otherwise. */
	bool init(node<event_record> *& root);

	/* Recursive functions matching the wrappers in the public section */
	bool display_all( node<event_record>* root ) const;
	bool remove(char* key, node<event_record>*& root);
	bool display_single(char* key, node<event_record> * root) const;
	bool add(const event_record& to_add, node<event_record> *& root);
	bool retrieve(char * key, event_record& to_get, node<event_record> * root) const;
	int height( node<event_record>* root) const;

	/* PURPOSE: display a single node to output stream
		INPUT: node whose data shall be displayed on screen. */
	void display_node(node<event_record>* head) const;

	// data
	node<event_record> * root; 			// BST root node
};

#endif //TABLE__H__
