/* edge is the connecting structure of the knowledge graph
 * it contains the following components
 * 	1. weight	
 * 		this is the front / back weight of the connection
 * 		data type is long long int
 * 		ideally it should be arbitararily large number
 *
 * 	2. truth_bit	
 * 		this tells wether the inserted connection is true or not
 * 		truth_bit = 0 -> connection is false
 * 		truth_bit = 1 -> connection is true
 *
 * 	3. verb_descriptor
 * 		this contains the string that describes more about the connection
 * 		if no such string exists, then it will contain empty string
 *
 * 	4. noun_ptr
 * 		points to the node in the noun_tree of knowledge graph
 * 		
 * 	5. end_time
 * 		gives the temporal context of the connection
 * 		i.e. tells upto what time the connection will remain true
 *
 * edges are inserted in the query_maxheap of verbs, and are also pointed to by search heaps
 */
typedef struct edge{ 
	long long int weight;
        long long int truth_bit;
        char* verb_descriptor;
	struct noun_tree_node* noun_ptr;
        //time
        time_t end_time;
}edge;


/* node of the data base descriptor verb tree
 * it is an AVL tree of strings
 * the AVL property states that 
 * 	for any root node n, 
 * 	height(left subtree of n) - height(right subtree of n) is either -1, 0, or 1
 * 	this value is called the balance factor and is stored in each node
 *
 * 	if the bf has any other value than -1, 0 or 1, then rotations are done
 * 	these rotations balance out the imbalance in the AVL tree
 * 	this ensures that
 * 		if the AVL tree has x nodes, then
 * 		height(tree) = lg(x)
 * node contains :
 * 	1. db_desc_verb_name
 * 		string which stores the name of the verb
 * 		memory is malloced for the string in this tree
 * 		nouns using this verb will point to this this malloced memory
 *
 * 	2. left
 * 		points to the left child of node
 *
 * 	3. right
 * 		points to the right child of node
 *
 * 	4. bf
 * 		balance factor of the node
 *
 */
typedef struct db_desc_verb_tree_node {
	char * db_desc_verb_name;
	struct db_desc_verb_tree_node * left;
	struct db_desc_verb_tree_node * right;
	long long int bf;
} db_desc_verb_tree_node;


// db_desc_verb_tree is a pointer to db_desc_verb_node 
typedef struct db_desc_verb_tree_node *db_desc_verb_tree;

// returns malloced node, which contains string "data"
db_desc_verb_tree_node * db_desc_verb_tree_createnode(char * data);

// initialises the tree by returning NULL
db_desc_verb_tree db_desc_verb_tree_init(void);

/* calculates the height of the tree, returns it
 * definition of height
 * 	root is NULL
 * 		height is returned as 0
 * 	tree contains one node
 *			root->
 * 				"db_desc_verb_1"
 * 		height is 1
 *	tree contains nodes like this
 *			root->
 *				"db_desc_verb_1"
 *			"db_desc_verb_2"	NULL
 *		height is 2
 *	and so on
 * this is a recursive function 
 */
long long int db_desc_verb_tree_height(db_desc_verb_tree_node * root);

// updates the balance factor of the nodes in tree pionted to by root
void db_desc_verb_tree_cal_balance(db_desc_verb_tree_node * root);

// LL rotation performed on node pointed to by p
db_desc_verb_tree_node * db_desc_verb_tree_LL(db_desc_verb_tree_node * root,db_desc_verb_tree_node * p);

// RR rotation performed on node pointed to by p
db_desc_verb_tree_node * db_desc_verb_tree_RR(db_desc_verb_tree_node * root,db_desc_verb_tree_node * p);

// LR rotation performed on node pointed to by p
db_desc_verb_tree_node * db_desc_verb_tree_LR(db_desc_verb_tree_node * root,db_desc_verb_tree_node * p);

// RL rotation performed on node pointed to by p
db_desc_verb_tree_node * db_desc_verb_tree_RL(db_desc_verb_tree_node * root,db_desc_verb_tree_node * p);

/* inserts into the tree pointed to by root
 * string "data" is inserted into the tree
 * this function also takes a pointer "recent" which will point to the recently inserted node
 * address of recent is passed, which is changed by the function
 *
 * root of tree is returned, caller shoudl store it properly
 */
db_desc_verb_tree db_desc_verb_tree_insert(db_desc_verb_tree root, db_desc_verb_tree_node * p, db_desc_verb_tree_node **recent, char * data);

/* LNR inorder traversal of tree
 * this will print
 * 	1. db_desc_verb_tree_node -> db_dec_verb_name
 * 	2. db_desc_verb_tree_node -> bf
 */
void db_desc_verb_tree_inorder(db_desc_verb_tree_node * root);


/* NLR inorder traversal of tree
 * this will print
 * 	1. db_desc_verb_tree_node -> db_dec_verb_name
 * 	2. db_desc_verb_tree_node -> bf
 */
void db_desc_verb_tree_preorder(db_desc_verb_tree_node * root);


/* LRN inorder traversal of tree
 * this will print
 * 	1. db_desc_verb_tree_node -> db_dec_verb_name
 * 	2. db_desc_verb_tree_node -> bf
 */
void db_desc_verb_tree_postorder(db_desc_verb_tree_node * root);

// returns the preorder successor of the node pointed to by root
db_desc_verb_tree_node * db_desc_verb_tree_in_pre(db_desc_verb_tree_node * root);

/* searches for the string "input_dec_verb" in the tree pointed to by root
 * returns pointer to the node if the string exists
 * else returns NULL
 *
 * comparison of strings is case insensitive, see function string_cmp
 */
db_desc_verb_tree_node* db_desc_verb_tree_search(db_desc_verb_tree_node* root  , char* input_desc_verb);


// data base verb tree
typedef struct db_verb_tree_node {
	char * db_verb_name;
	struct db_verb_tree_node * left;
	struct db_verb_tree_node * right;
	long long int bf;
} db_verb_tree_node;

typedef struct db_verb_tree_node *db_verb_tree;

db_verb_tree_node * db_verb_tree_init(void);

db_verb_tree_node * db_verb_tree_createnode(char * data);

long long int db_verb_tree_height(db_verb_tree_node * root);

void db_verb_tree_cal_balance(db_verb_tree_node * root);

db_verb_tree_node * db_verb_tree_LL(db_verb_tree_node * root,db_verb_tree_node * p);

db_verb_tree_node * db_verb_tree_RR(db_verb_tree_node * root,db_verb_tree_node * p);

db_verb_tree_node * db_verb_tree_LR(db_verb_tree_node * root,db_verb_tree_node * p);

db_verb_tree_node * db_verb_tree_RL(db_verb_tree_node * root,db_verb_tree_node * p);

db_verb_tree db_verb_tree_insert(db_verb_tree_node *root, db_verb_tree_node * p, db_verb_tree_node **recent, char * data);

void db_verb_tree_inorder(db_verb_tree_node * root);

db_verb_tree_node * db_verb_tree_in_pre(db_verb_tree_node * root);

db_verb_tree_node* db_verb_tree_search(db_verb_tree_node* root  , char* db_verb_name);

/* this is a node in the tree of nouns which is the backbone of the knowledge graph
 * the node contains the following components
 * 	1. noun_name
 * 		string which contains the name of the noun
 * 	2. noun_id
 * 		integer value which contains the ID of the noun
 * 	3. noun_def
 * 		string which contains the definition of the noun
 * 	4. next
 * 		pointer to the root of "next" verb_tree of noun node
 * 	5. prev
 * 		pointer to the root of "prev" verb_tree of noun node
 * 	6. src_heap
 * 		pointer to the search_maxheap of the noun node
 * 		it is accessed whenever maximum priority edges are needed
 * 	7. sub_heap
 * 		pointer to the subclass_heap of noun node
 * 		it is accessed whenever maximum priority subclasses are needed
 * 	8. left
 * 		points to the left child noun node
 * 	9. right
 * 		points to the right child noun node
 * 	10. bf
 * 		balance factor of the noun node
 */
typedef struct noun_tree_node {
	char * noun_name;
	long long int noun_id;
	char * noun_def;
	struct verb_tree_node * next;
	struct verb_tree_node * prev;
	struct search_maxheap* src_heap;
	struct subclass_maxheap * sub_heap;
	struct noun_tree_node * left;
	struct noun_tree_node * right;
	long long int bf;
} noun_tree_node;

typedef struct noun_tree_node * noun_tree;

noun_tree_node * noun_tree_init(void);

noun_tree_node * noun_tree_createnode(char * noun_name , char * noun_def , long long int noun_id);

long long int noun_tree_height(noun_tree_node * root);

void noun_tree_cal_balance(noun_tree_node * root);

noun_tree_node * noun_tree_LL(noun_tree_node * root,noun_tree_node * p);

noun_tree_node * noun_tree_RR(noun_tree_node * root,noun_tree_node * p);

noun_tree_node * noun_tree_LR(noun_tree_node * root,noun_tree_node * p);

noun_tree_node * noun_tree_RL(noun_tree_node * root,noun_tree_node * p);

noun_tree noun_tree_insert(noun_tree root,noun_tree_node * p, noun_tree_node ** recent, char * noun_name , char * noun_def , long long int noun_id);

void noun_tree_inorder(noun_tree_node * root);
	
noun_tree_node* noun_tree_search(noun_tree_node* root  , char* noun_name , long long int id);

/* this is a node in the tree of verbs, i.e. verb_tree
 * each noun_tree_node has its own prev and next verb trees
 *
 * the node contains the following components
 * 	1. verb_name
 * 		string which contains the name of the verb
 * 	2. qheap
 * 		pointer to the query_maxheap of the node
 * 	3. left
 * 		points to the left child of node
 * 	4. right
 * 		points to the right child of node
 * 	5. bf
 * 		balance factor of the node
 */

typedef struct verb_tree_node {
	char * verb_name;
	struct query_maxheap* qheap;
	struct verb_tree_node * left;
	struct verb_tree_node * right;
	long long int bf;
} verb_tree_node;

typedef struct verb_tree_node * verb_tree;

verb_tree_node * verb_tree_createnode(char * data);

verb_tree_node * verb_tree_init(void);

long long int verb_tree_height(verb_tree_node * root);

void verb_tree_cal_balance(verb_tree_node * root);

verb_tree_node * verb_tree_LL(verb_tree_node * root,verb_tree_node * p);

verb_tree_node * verb_tree_RR(verb_tree_node * root,verb_tree_node * p);

verb_tree_node * verb_tree_LR(verb_tree_node * root,verb_tree_node * p);

verb_tree_node * verb_tree_RL(verb_tree_node * root,verb_tree_node * p);

verb_tree verb_tree_insert(verb_tree root ,verb_tree_node * p, verb_tree_node **recent, char * data);

verb_tree_node * verb_tree_search(verb_tree_node *root, char *verb_name);

void verb_tree_inorder(verb_tree_node * root);

/* query_maxheap_node is the connecting structure of the knowledge graph
 * it is the same as edge
 * it contains the following components
 * 	1. weight	
 * 		this is the front / back weight of the connection
 * 		data type is long long int
 * 		ideally it should be arbitararily large number
 *
 * 	2. truth_bit	
 * 		this tells wether the inserted connection is true or not
 * 		truth_bit = 0 -> connection is false
 * 		truth_bit = 1 -> connection is true
 *
 * 	3. verb_descriptor
 * 		this contains the string that describes more about the connection
 * 		if no such string exists, then it will contain empty string
 *
 * 	4. noun_ptr
 * 		points to the node in the noun_tree of knowledge graph
 * 		
 * 	5. end_time
 * 		gives the temporal context of the connection
 * 		i.e. tells upto what time the connection will remain true
 *
 * edges are inserted in the query_maxheap of verbs, and are also pointed to by search heaps
 */
typedef struct query_maxheap_node {
	struct noun_tree_node* noun_ptr;
	long long int weight;
	 long long int truth_bit;
	char * verb_descriptor;
	time_t end_time;

} query_maxheap_node;

typedef struct query_maxheap{
	query_maxheap_node* arr;
	long long int len;
}query_maxheap;

query_maxheap* query_maxheap_init(void);

void query_maxheap_swap(query_maxheap_node* a, query_maxheap_node* b);

void query_maxheap_insert(query_maxheap* qh, struct edge e);

void query_maxheap_print(query_maxheap* qh);

struct query_maxheap_node * query_maxheap_delete(query_maxheap* qh);

query_maxheap_node *query_maxheap_search(query_maxheap *qh, struct edge e);

long long int query_maxheap_add_weights(query_maxheap* qh);

query_maxheap * query_maxheap_copy(query_maxheap* qh);

// search maximum heap
typedef struct search_maxheap_node{
	char* verb;
	long long int weight;
	edge *e;
}search_maxheap_node;

typedef struct search_maxheap{
	search_maxheap_node* arr;
	long long int len;
}search_maxheap;

search_maxheap* search_maxheap_init(void);

void search_maxheap_swap(search_maxheap_node* a, search_maxheap_node* b);

search_maxheap_node * search_maxheap_search(search_maxheap *hp, char *verb, edge *e);

void search_maxheap_insert(search_maxheap* hp, edge *e, char *verb, long long int weight);

void search_maxheap_print(search_maxheap* hp);

search_maxheap_node * search_maxheap_delete(search_maxheap* hp);

search_maxheap * search_maxheap_copy(search_maxheap* hp);

long long int search_maxheap_add_weights(search_maxheap* hp);

search_maxheap * search_maxheap_copy(search_maxheap* hp);

// subclass maximum heap
typedef struct subclass_maxheap_node{
	struct noun_tree_node* noun_ptr;
	long long int weight;
}subclass_maxheap_node;

typedef struct subclass_maxheap{
	subclass_maxheap_node* arr;
	long long int len;
}subclass_maxheap;

subclass_maxheap* subclass_maxheap_init(void);

void subclass_maxheap_swap(subclass_maxheap_node* a, subclass_maxheap_node* b);

void subclass_maxheap_insert(subclass_maxheap* hp, struct noun_tree_node *noun_ptr, long long int weight);

void subclass_maxheap_print(subclass_maxheap* hp);

struct subclass_maxheap_node * subclass_maxheap_delete(subclass_maxheap* hp);

subclass_maxheap_node * subclass_maxheap_search(subclass_maxheap *hp, struct noun_tree_node *noun_ptr);

long long int subclass_maxheap_add_weights(subclass_maxheap* hp);

subclass_maxheap * subclass_maxheap_copy(subclass_maxheap* hp);


/* finally we come accross the ADT for the knowledge grpah itself
 * knowledge graph consists of 3 AVL tree pointers
 * these three pointers are all that is needed to access the tremendous information stored
 *
 * it contains the following components
 * 	1. main_noun_tree
 * 		pointer to the AVL tree of nouns
 * 	2. main_verb_tree
 * 		pointer to the AVL verb tree of verbs
 * 	3. main_desc_verb_tree
 * 		pointer to the AVL tree of verb descriptors
 *
 */
typedef struct knowledge_graph{
	noun_tree main_noun_tree;
	db_verb_tree main_verb_tree;
	db_desc_verb_tree main_desc_verb_tree;
}knowledge_graph;

#define default_id -5

/* this is the data structure which corresponds to one entry in the knowlegde graph
 * it contains all the necessary information for connecting nouns in the kg
 * one line of the data file which is given as input to the code has all this info
 *
 * it contains the following components
 * 	1. front_weight
 * 		front weight of the connection
 * 		how much important is this connection with respect to noun1
 *
 * 	2. inference
 * 		if the relation already exsists transitively
 * 		still do you want to insert the relation?
 * 		inference = 0 -> insert
 * 		inference = 1 -> do not insert
 *
 * 	3. truth_bit
 * 		truth value of the connection being made
 * 		truth_bit = 0 -> connection is false
 * 		truth_bit = 1 -> connection is true
 *
 * 	4. noun1
 * 		string which contains noun1
 *
 * 	5. noun1_id
 * 		id of noun1
 *
 * 	6. verb
 * 		string which contains the name of the verb
 *
 * 	7. verb_descriptor
 * 		string which contains the words describing the connection
 *
 * 	8. noun2
 * 		string which contains noun2
 *
 * 	9. noun2_id
 * 		id of noun2
 *
 * 	10. back_weight
 * 		back weight of the connection
 * 		how much important is this connection with respect to noun3 
 * 		NOTE:
 * 			noun3 = concatenation(noun1, '_', noun2)
 * 	11. definition
 * 		string which is generally a large sentence that defines noun3
 *
 * 	12. time
 * 		this gives temporal context
 * 		indicates till when the connection will be true
 */
typedef struct line_data{
	long long int front_weight;
	long long int inference;
	long long int truth_bit;
	char* noun1;
	long long int noun1_id;
	char* verb;
	char* verb_descriptor;
	char* noun2;
	long long int noun2_id;
	long long int back_weight;
	char* definition;
	time_t time;
} line_data;

line_data* line_fetch_data_csv(char ** arr);

knowledge_graph * knowledge_graph_init(void);

void knowledge_graph_insert(knowledge_graph* kg_ptr ,line_data data);

/* this is a queue data structure's node
 * it is used excessively in levelwise traversal of knowledge graph
 * it is used in weighted traversal, and the queue contains connections
 *
 * it contains the following components
 * 	1. noun_ptr
 * 		pointer to a noun_tree_node, with which the connection is made
 *
 * 	2. verb_ptr
 * 		pointer to the verb string of the connection
 *
 * 	3. e
 * 		pointer to the edge which contains other importantt info
 *
 * 	4. alloc_lines
 * 		lines allocated to the noun pointed to by noun_ptr
 * 	
 * 	5. next
 * 		since the queue is implemented by a singly linked NULL terminated list
 * 		the node structure of queue has na "next" pointer
 */
typedef struct traversal_queue_node {
        struct noun_tree_node *noun_ptr;
        char * verb_ptr;
        struct edge *e;
        long long int alloc_lines;
        struct traversal_queue_node *next;
} traversal_queue_node;

/* traversal queue data structure
 * queue is implemented by a singly linked NULL terminated list
 * queue structure contains the following components
 * 	1. front
 * 		pointer to the front node of the queue
 * 		on dequeuing, this data will be returned
 * 	2. rear
 * 		pointer to the rear of the queue
 * 		on enqueuing, data will be inserted here
 * 	3. length
 * 		number of nodes in the queue
 */
typedef struct traversal_queue {
        struct traversal_queue_node * front;
        struct traversal_queue_node * rear;
        long long int length;
} traversal_queue;

/* initialise the traversal queue by mallocing memory, returns pointer to queue
 * front and rear are set to NULL
 *length is set to zero
 */
traversal_queue *traversal_queue_init(void);

// enqueue into the queue traversal_queue_node "data"
void traversal_queue_enqueue (traversal_queue *q, traversal_queue_node * data);

// dequeue from the queue, return a traversal_queue_node pointer
traversal_queue_node *traversal_queue_dequeue(traversal_queue *q) ;

/* check if queue is empty or not
 * returns 0 : queue is not empty
 * returns 1 : queue is empty
 */
long long int traversal_queue_isempty(traversal_queue *q) ;

/* peek into the queue
 * returns pointer to the traversal_queue_node at the front, if such node exists
 */
traversal_queue_node *traversal_queue_peek(traversal_queue *q) ;

/* prints the entire queue by traversing it
 * following will get printed
 * 	noun_name
 * 	verb_name
 * 	verb
 * 	
 */
void traversal_queue_print (traversal_queue *q);

edge *copy_query_maxheap_node_into_edge(query_maxheap_node * qptr);
                                                                       
long long int print_info_lines(noun_tree_node* noun_ptr , long long int total_lines );

void print_line_data(line_data data);

long long int edge_compare(struct edge *e1, struct edge *e2);

void print_str_without_context(char *str, char context_char);

long long int string_cmp_percentage(char * a , char * b);

long long int string_cmp(char * a , char * b);

char **string_tokenise(char *str, char delimiter);

void query_recognizer(knowledge_graph *kg, char *str);

long long int getaline(char str[], long long int lim);

long long int query_verb_noun(knowledge_graph* kg, char * input_noun, long long int input_noun_id, char * input_verb, long long int total_lines, int choice_flag);

long long int query_verb_verb_desc_noun(knowledge_graph* kg, char * input_noun, long long int input_noun_id, char * input_verb, char* input_verb_desc,long long int total_lines, long long int choice_flag);

long long int noun_verb_verb_desc_query(knowledge_graph* kg, char * input_noun, long long int input_noun_id, char * input_verb, char* input_verb_desc,long long int total_lines, long long int choice_flag);

long long int noun_verb_query(knowledge_graph* kg, char * input_noun, long long int input_noun_id, char * input_verb, long long int total_lines, int choice_flag);

void print_sentence(char * noun, char * verb, edge * e);
