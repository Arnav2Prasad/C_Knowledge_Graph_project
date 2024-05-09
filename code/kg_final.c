#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#include<time.h>
#include "kg_final.h"

// this variable tells the total amount of lines printed
long long int count_printed = 0;

/* concat joins the two strings a and b, by the "joining" character
 * parameters : strings a and b
 * 		joining character
 * for example, 
 * 	a -> "knowledge"
 * 	joining = '_'
 * 	b -> "graph"
 *
 * concat will return "knowledge_graph"
 *
 * memory is malloced for the string, should be freed by caller
 */
char * concat(char *a, char joining, char *b) 
{
	long long int lena;	// length of string a
	long long int lenb;	// length of string b
	char *c;		// third string
	long long int i;	// traverses the strings 
	long long int j;	// traverses the strings

	lena = strlen(a);
	lenb = strlen(b);

	// malloc enough memory for c
	// lena for a, lenb for b, 1 for nul byte, 1 for joining character
	c = (char *) malloc((sizeof(char) * (lena + lenb)) + 2);
	
	// copy string a into c
	for(i = 0; i < lena; i++) 
	{
		c[i] = a[i];
	}

	// copy the joining character
	j = i + 1;
	c[i] = joining;

	// copy string b into c
	for(i = 0; i < lenb; i++) 
	{
		c[j + i] = b[i];
	}

	// stringify c by appending the nul byte to it
	c[j + i] = '\0';
	return c;
}

/* returns the maximum of the two integers a and b
 * if a >  b, a is returned
 * if a <= b, b is returned
 */
long long int max(long long int a, long long int b)
{
	if (a > b)
	{
		return a;
	}
	return b;
}

/*
    *------------------------------------------------------------------------------------  
    *   AVL TREE
    *
    *
    *   WHAT IS BST?
    *   BST stands for Binary Search Tree
    *   in it left child <= root <= right child
    *               40
    *             /    \
    *           20      50
    *          /  \    /   \
    *        10   30  45    60
    * 
    *   it is useful for efficient searching --> o(height) 
    * 
    * DRAWBACKS OF BST
    * 	For same elements, but different order , we get BST of different height
    * 	On given array(series of order of input elements) we get different BST
    * 	We get BST of difference height
    * 	Total possibilities of BST :   2n
    *    	                         C
    *                                     n-1
    * 
    * Example:
    *  for order of elements : 30,10,20      AND   20,10,30
    *       30                                      20
    *      /                                      /    \
    *     10                                    10      30
    *       \
    *        20 
    *   height = 3                                height=2
    * 
    * So for skewed tree : insertion and searching complexity may be : o(n)
    *   o(logn) <= insert and serach <= o(n)   --> it depends on order of input of elements 
    * 
    * HOW TO IMPROVE?
    *   We can construct a height balanced BST 
    *   so that insert, search complexity would be o(log n)
    * 
    *  It uses the concept of balance factor 
    *   Balance Factor  =   height of   -    height of
    *                      left subtree    right subtree
    *   if | bf | > 1 : tree is imbalanced
    *   if | bf | <= 1 : tree is balanced
    * 
    * In order to get tree as balanced : we introduce the concept of "ROTATIONS!"
    *  Rotation includes : LL,RR,LR,RL rotation
    * Rotation is performed on 3 nodes only!
    * 
    * INSERTION : 
    * While inserting elements in the AVL tree , as soon as a node becomes imbalance,
    * perform rotation , Dont wait for other keys to get inserted and then perform rotation.
    * 
    * If multiple nodes are imbalanced , start performing rotation with the "lower" one
    * No 2 nodes can have the same value.
    *  
    * Time Complexity : o(log n)
    * 
    * 
    * SEARCHING:
    * To search key 'K' in the AVL tree:
    *  if  root > k:
    *              go to left subtree 
    *  if root < k:
    *               go to right subtree
    *  if root == k:
    *               node found !
    * 
    * Time Complexity : o(log n)
    * 
    * 
    * DELETION:
    * To delete key 'k' in the AVL tree:
    * 
    * Find the node to be deleted :
    *  CASE 1 : if the node has no child  --> delete it
    *  CASE 2 : if the node has only 1 children --> replace the node with 
    *           the children and delete the node
    * CASE 3 : if the node has 2 children --> you have 2 options
    *           one is to replace the node with the largest value node
    *               of its left subtree and then delete the node.
    *           other option is to replace the node with the smallest value node
    *               of its right subtree and then delete the node.
    * 
    * Time Complexity : o(log n)
    * 
    * After deletion of the node , check if the tree has becomed imbalanced or not
    * If imbalanced : perform suitable rotations(LL,RR,LR,RL)
    * 
    * -----------------------------------------------------------------------------------------------------
*/


db_desc_verb_tree_node * db_desc_verb_tree_init(void) 
{
	return NULL;
}

db_desc_verb_tree_node * db_desc_verb_tree_createnode(char * data)
{
	db_desc_verb_tree_node * nn = (db_desc_verb_tree_node  *)malloc(sizeof(db_desc_verb_tree_node ));
	if (nn)
	{
		nn->db_desc_verb_name = (char *) malloc(strlen(data) + 1);
		strcpy(nn->db_desc_verb_name, data);
		nn->right = NULL;
		nn->left = NULL;
		nn->bf = 0;
	}
	return nn;

}

long long int db_desc_verb_tree_height(db_desc_verb_tree_node * root) 
{
	if (root == NULL)
	{
		return 0;
	}
	return max(db_desc_verb_tree_height(root->left),db_desc_verb_tree_height(root->right)) + 1;
}

void db_desc_verb_tree_cal_balance(db_desc_verb_tree_node * root)
{
	long long int lh = db_desc_verb_tree_height(root->left);
	long long int rh = db_desc_verb_tree_height(root->right);

	root->bf = lh-rh;
	return;
}

db_desc_verb_tree_node * db_desc_verb_tree_LL(db_desc_verb_tree_node * root,db_desc_verb_tree_node * p)
{
	db_desc_verb_tree_node * pl = p->left;
	db_desc_verb_tree_node * plr = pl->right;

	pl->right=p;
	p->left = plr;

	db_desc_verb_tree_cal_balance(p);
	db_desc_verb_tree_cal_balance(pl);
	
	if (root==p)
	{
		root=pl;
	}
	return pl;

}

db_desc_verb_tree_node * db_desc_verb_tree_RR(db_desc_verb_tree_node * root,db_desc_verb_tree_node * p)
{
	db_desc_verb_tree_node * pr = p->right;
	db_desc_verb_tree_node * prl = pr->left;

	pr->left = p;
	p->right = prl;

	db_desc_verb_tree_cal_balance(p);
	db_desc_verb_tree_cal_balance(pr);

	if (root==p)
	{
		root = pr;
	}
	return pr;

}

db_desc_verb_tree_node * db_desc_verb_tree_LR(db_desc_verb_tree_node * root,db_desc_verb_tree_node * p)
{
	db_desc_verb_tree_node * pl=p->left;
	db_desc_verb_tree_node * plr = pl->right;

	pl->right = plr->left;
	p->left = plr->right;

	plr->left = pl;
	plr->right = p;

	db_desc_verb_tree_cal_balance(p);
	db_desc_verb_tree_cal_balance(pl);
	db_desc_verb_tree_cal_balance(plr);

	if (root==p)
	{
		root=plr;
	}
	return plr;

}

db_desc_verb_tree_node  * db_desc_verb_tree_RL(db_desc_verb_tree_node * root,db_desc_verb_tree_node * p)
{
	db_desc_verb_tree_node * pr=p->right;
	db_desc_verb_tree_node * prl = pr->left;

	p->right = prl->left;
	pr->left = prl->right;

	prl->right = pr;
	prl->left = p;

	db_desc_verb_tree_cal_balance(p);
	db_desc_verb_tree_cal_balance(pr);
	db_desc_verb_tree_cal_balance(prl);

	if (root==p)
	{
		root=prl;
	}
	return prl;
}

/* returns the absolute value of x
 * if x <  0, then -x is returned
 * if x >= 0, then  x is returned
 */
long long int mod(long long int x) 
{
	if(x < 0) 
	{
		return -x;
	}
	return x;
}


/*
 * compares two strings a and b case insensitively
 * comparison of non - alphabets is done based on their ascii value
 * parameters : (char * a , char * b)
 * returns :	 
 * 	 0 : equal
 * 	 1 : string a is greater than b
 * 	-1 : string b is greater than a
 * if a is a proper of b, then here b > a
 * if b is a proper of a, then here a > b
 *
 * i.e. a -> "maxheap insert"
 * 	b -> "maxheap insert node"
 * 	then, b > a 
 */
long long int string_cmp(char * a , char * b)
{
	long long int i;	// traverses both arrays
	char ac;		// instance of character of array a
	char bc;		// instance of character of array b

	i = 0;
	// till any of the strings is over
	while (a[i] && b[i])
	{
		// copy the current characters of a and b
		ac = a[i]; 
		bc = b[i];
		// make them case insensitive by converting to lowercase
		if (ac >= 'A' && ac <='Z')
		{
			ac = ac + 'a' - 'A';
		}
		if (bc  >= 'A' && bc<='Z')
		{
			bc = bc + 'a' - 'A';
		}

		// now compare them
		if (ac > bc)
		{
			return 1;
		}
		else if (ac < bc)
		{
			return -1;
		}
		i++;
	}
	// if both strings finished and we reached here, then strings are equal
	if (a[i] == b[i])
	{
		return 0;
	}
	// if a is larger in length then return 1
	else if (a[i])
	{
		return 1;
	}
	else 
	{
		return -1;
	}
}

// compares the strings but returns the percentage of mismatched characters
long long int string_cmp_percentage(char * a , char * b)
{
	long long int i;		// traverses both arrays
	char ac;			// instance of character of array a
	char bc;			// instance of character of array b
	long long int chars_matched;	// counts the matching characters
				
	chars_matched = 0;

	i = 0;
	while (a[i] && b[i])
	{
		ac = a[i]; 
		bc = b[i];
		if (ac >= 'A' && ac <='Z')
		{
			ac = ac + 'a' - 'A';
		}
		if (bc  >= 'A' && bc<='Z')
		{
			bc = bc + 'a' - 'A';
		}
		if(ac == bc) 
		{
			chars_matched++;
		}
		i++;
	}
	while(a[i]) 
	{
		i++;
	}
	while(b[i]) 
	{
		i++;
	}
	return (long long int) (((float) chars_matched / (float) i) * 100);

}

db_desc_verb_tree db_desc_verb_tree_insert(db_desc_verb_tree root,db_desc_verb_tree_node * p, db_desc_verb_tree_node **recent, char * data)
{
	if (p==NULL)
	{
		db_desc_verb_tree_node * nn = db_desc_verb_tree_createnode(data);
		*recent = nn;
		return nn;
	}
	long long int result;
	result = string_cmp(p->db_desc_verb_name, data);
	if (result == 1)
	{
		p->left = db_desc_verb_tree_insert(root, p->left, recent, data);
		
	}
	else if (result == -1)
	{
		p->right = db_desc_verb_tree_insert(root, p->right, recent, data);
	}
	else 
	{
		return p;
	}
	
	db_desc_verb_tree_cal_balance(p);
	
	if (p->bf == 2)
	{
		if (p->left->bf == -1)
		{
			return db_desc_verb_tree_LR(root,p);
		}
		else
		{
			return db_desc_verb_tree_LL(root,p);
		}
	}
	else if (p->bf == -2)
	{
		if (p->right->bf == 1)
		{
			return db_desc_verb_tree_RL(root,p);
		}
		else
		{
			return db_desc_verb_tree_RR(root,p);
		}
	}
	return p;
}

void db_desc_verb_tree_inorder(db_desc_verb_tree_node * root)
{
	if (root==NULL)
	{
		return;
	}
	db_desc_verb_tree_inorder(root->left);
	printf("%s ",root->db_desc_verb_name);
	printf("bf = %lld \n", root->bf);
	db_desc_verb_tree_inorder(root->right);
	return;

}

void db_desc_verb_tree_preorder(db_desc_verb_tree_node * root) {
	if (root==NULL)
	{
		return;
	}
	printf("%s ",root->db_desc_verb_name);
	printf("bf = %lld \n", root->bf);
	db_desc_verb_tree_inorder(root->left);
	db_desc_verb_tree_inorder(root->right);
	return;
}

void db_desc_verb_tree_postorder(db_desc_verb_tree_node * root) {
	if (root==NULL)
	{
		return;
	}
	db_desc_verb_tree_inorder(root->left);
	db_desc_verb_tree_inorder(root->right);
	printf("%s ",root->db_desc_verb_name);
	printf("bf = %lld \n", root->bf);
	return;
}
	
db_desc_verb_tree_node* db_desc_verb_tree_search(db_desc_verb_tree_node* root  , char* db_desc_verb_name)
{
       if (root==NULL)
       {
         return NULL;
       }
       long long int result = string_cmp(root->db_desc_verb_name,db_desc_verb_name);
       if (result == 1)
       {
               return db_desc_verb_tree_search(root->left,db_desc_verb_name);
       }
       else if (result==-1)
       {
               return db_desc_verb_tree_search(root->right, db_desc_verb_name);
       }
       else
       {
                return root;
       }
}

db_verb_tree_node * db_verb_tree_init(void) 
{
	return NULL;
}

db_verb_tree_node * db_verb_tree_createnode(char * data)
{
	db_verb_tree_node * nn = (db_verb_tree_node  *)malloc(sizeof(db_verb_tree_node ));
	if (nn)
	{
		nn->db_verb_name = (char *) malloc(strlen(data) + 1);
		strcpy(nn->db_verb_name, data);
		nn->right = NULL;
		nn->left = NULL;
		nn->bf = 0;
	}
	return nn;

}

long long int db_verb_tree_height(db_verb_tree_node * root) 
{
	if (root == NULL)
	{
		return 0;
	}
	return max(db_verb_tree_height(root->left),db_verb_tree_height(root->right)) + 1;
}

void db_verb_tree_cal_balance(db_verb_tree_node * root)
{
	long long int lh = db_verb_tree_height(root->left);
	long long int rh = db_verb_tree_height(root->right);

	root->bf = lh-rh;
	return;
}

db_verb_tree_node * db_verb_tree_LL(db_verb_tree_node * root,db_verb_tree_node * p)
{
	db_verb_tree_node * pl = p->left;
	db_verb_tree_node * plr = pl->right;

	pl->right = p;
	p->left = plr;

	db_verb_tree_cal_balance(p);
	db_verb_tree_cal_balance(pl);
	
	if (root == p)
	{
		root = pl;
	}
	return pl;

}

db_verb_tree_node * db_verb_tree_RR(db_verb_tree_node * root,db_verb_tree_node * p)
{
	db_verb_tree_node * pr = p->right;
	db_verb_tree_node * prl = pr->left;

	pr->left = p;
	p->right = prl;

	db_verb_tree_cal_balance(p);
	db_verb_tree_cal_balance(pr);

	if (root == p)
	{
		root = pr;
	}
	return pr;

}

db_verb_tree_node * db_verb_tree_LR(db_verb_tree_node * root,db_verb_tree_node * p)
{
	db_verb_tree_node * pl = p->left;
	db_verb_tree_node * plr = pl->right;

	pl->right = plr->left;
	p->left = plr->right;

	plr->left = pl;
	plr->right = p;

	db_verb_tree_cal_balance(p);
	db_verb_tree_cal_balance(pl);
	db_verb_tree_cal_balance(plr);

	if (root == p)
	{
		root = plr;
	}
	return plr;

}

db_verb_tree_node  * db_verb_tree_RL(db_verb_tree_node * root,db_verb_tree_node * p)
{
	db_verb_tree_node * pr = p->right;
	db_verb_tree_node * prl = pr->left;

	p->right = prl->left;
	pr->left = prl->right;

	prl->right = pr;
	prl->left = p;

	db_verb_tree_cal_balance(p);
	db_verb_tree_cal_balance(pr);
	db_verb_tree_cal_balance(prl);

	if (root == p)
	{
		root = prl;
	}
	return prl;
}

db_verb_tree db_verb_tree_insert(db_verb_tree root ,db_verb_tree_node * p, db_verb_tree_node **recent, char * data)
{
        if (p==NULL)
        {
                db_verb_tree_node * nn = db_verb_tree_createnode(data);
                *recent = nn;
		return nn;
        }

        long long int result;	// stores result to avoid repeated computations

        result = string_cmp(p->db_verb_name, data);
        if (result == 1)
        {
		p->left = db_verb_tree_insert(root, p->left, recent, data);
        }
        else if (result == -1)
        {

		p->right = db_verb_tree_insert(root, p->right, recent, data);
        }

        db_verb_tree_cal_balance(p);
                

        if (p->bf == 2)
        {
                if (p->left->bf == -1)
                { 
                        return db_verb_tree_LR(root,p);
                }
                else
                {
                        return db_verb_tree_LL(root,p);
                }
        }
        else if (p->bf == -2)
        {
                if (p->right->bf == 1)
                {
                        return db_verb_tree_RL(root,p);
                }
                else
                {
                        return db_verb_tree_RR(root,p);
                }
        }

        return p;


}

void db_verb_tree_inorder(db_verb_tree_node * root)
{
	if (root==NULL)
	{
		return;
	}
	db_verb_tree_inorder(root->left);
	printf("%s ", root->db_verb_name);
	printf("bf = %lld \n", root->bf);
	db_verb_tree_inorder(root->right);
	return;

}

	

db_verb_tree_node * db_verb_tree_search(db_verb_tree_node * root  , char * db_verb_name)
{
       if (root == NULL)
       {
         return NULL;
       }
       long long int result = string_cmp(root->db_verb_name,db_verb_name);
       if (result == 1)
       {
               return db_verb_tree_search(root->left,db_verb_name);
       }
       else if (result == -1)
       {
               return db_verb_tree_search(root->right, db_verb_name);
       }
       else
       {
                return root;
       }
}

/* insert into the knowledge graph all line_data acquired
 * all necessary connections are made by this code
 * makes changes in the 3 main trees of knowledge graph
 *
 * 1. initial phase
 * 	we have nouns noun1, noun2 
 * 	construct noun3 as noun1_noun2
 * 	check if all the nouns, db_verb, db_desc_verb exist
 * 	if they do not exist, then insert them into the kg
 *
 * 2. connection phase
 * 	in this phase, connections will be made using edges
 * 	functoin will make a front connection from n1 -> n3
 * 	function will make a back  connection from n3 -> n1
 *
 * 	then, edge will be searched for in n1
 * 	if not there, 
 * 	edge will inserted into search_maxheap of n1
 * 	if it exists, its weight will get incremented
 *
 * 	similar will be done for 
 * 		subclass_heap of n1
 * 		query_maxheap of n1
 * 		query_maxheap of n3
 * 	in the end, if definition exists, n3 will get memory for it
 */
void knowledge_graph_insert(knowledge_graph* kg_ptr ,line_data data)
{
	// 1. initial phase
	noun_tree_node * n1;		// points to noun_tree_node of n1
	noun_tree_node * n2;		// points to noun_tree_node of n2
	noun_tree_node * n3;		// points to noun_tree_node of n3
				
	n1 = NULL;
	n2 = NULL;
	n3 = NULL;
	
	char * noun3;
	// construct noun3 as noun1_noun2
	noun3 = concat(data.noun1 ,'_',data.noun2);

	// initialise pointers to recently inserted nodes in all trees
	noun_tree_node * noun_recent = NULL;
	verb_tree_node * verb_recent = NULL;
	db_verb_tree_node * db_verb_recent = NULL;
	db_desc_verb_tree_node * db_desc_verb_recent = NULL;	
	
	// search for all 3 nouns in noun tree of knowledge graph
	n1 = noun_tree_search(kg_ptr -> main_noun_tree, data.noun1,data.noun1_id);
	n2 = noun_tree_search(kg_ptr -> main_noun_tree, data.noun2,data.noun2_id);
	n3 = noun_tree_search(kg_ptr -> main_noun_tree,noun3 ,default_id);
	
	// search for db_verb and db_desc_verb in their respective trees
	db_verb_tree_node * db_verb = db_verb_tree_search(kg_ptr->main_verb_tree, data.verb);
	db_desc_verb_tree_node * db_desc_verb = db_desc_verb_tree_search(kg_ptr->main_desc_verb_tree, data.verb_descriptor);
	
	/* for each tree search, if the node was not present
	 * 	1. insert the node into the tree
	 * 	2. store the "recent" pointer which points to recently inserted node
	 * 	3. for each newly inserted node, initialse all its internal data structures
	 * 	   for nouns, call init for the search_heap, subclass_heap and verb trees
	 */


	// if noun1 is not present in the tree, insert it
	if (!n1)
	{
		kg_ptr -> main_noun_tree = noun_tree_insert(kg_ptr->main_noun_tree , kg_ptr->main_noun_tree , &(noun_recent), data.noun1 ,NULL , data.noun1_id);
		// make n1 point to the recently inserted node for making connections
		n1 = noun_recent;
		
		// initialise verb_trees of n1
		n1->next = verb_tree_init();
		n1->prev = verb_tree_init();

		// initialise search heap of n1
		n1->src_heap = search_maxheap_init();
		
		// initialise subclass heap of n1
		n1->sub_heap = subclass_maxheap_init();

	}

	// if noun2 is not present in the tree, insert it
	if (!n2)
	{
                kg_ptr -> main_noun_tree = noun_tree_insert(kg_ptr->main_noun_tree , kg_ptr->main_noun_tree , &(noun_recent), data.noun2 ,NULL , data.noun2_id);
		// make n2 point to the recently inserted node for making connections
		n2 = noun_recent;
		
		// initialise verb_trees of n2
		n2->next = verb_tree_init();
		n2->prev = verb_tree_init();

		// initialise search heap of n2
		n2->src_heap = search_maxheap_init();
		
		// initialise subclass heap of n2
		n2->sub_heap = subclass_maxheap_init();


        }

	// if noun3 is not present in the tree, insert it
	if (!n3)
	{
                kg_ptr -> main_noun_tree = noun_tree_insert(kg_ptr->main_noun_tree , kg_ptr->main_noun_tree, &(noun_recent) ,noun3 ,data.definition , default_id);
		// make n3 point to the recently inserted node for making connections
		n3 = noun_recent;

		// initialise verb_trees of n3
		n3->next = verb_tree_init();
		n3->prev = verb_tree_init();

		// initialise search heap of n3
		n3->src_heap = search_maxheap_init();
		
		// initialise subclass heap of n3
		n3->sub_heap = subclass_maxheap_init();
        }
	
	// if db_verb is not there, insert it
	if (!db_verb)
	{
		kg_ptr->main_verb_tree = db_verb_tree_insert(kg_ptr->main_verb_tree , kg_ptr->main_verb_tree, &(db_verb_recent), data.verb);
		// make db_verb point to the recently inserted node for making connections
		db_verb = db_verb_recent;
        }

	// if db_desc_verb is not there, insert it
	if (!db_desc_verb)
	{
		kg_ptr->main_desc_verb_tree = db_desc_verb_tree_insert(kg_ptr->main_desc_verb_tree, kg_ptr->main_desc_verb_tree, &(db_desc_verb_recent),  data.verb_descriptor);
		// make db_desc_verb point to the recently inserted node for making connections
		db_desc_verb = db_desc_verb_recent;
	}
	
	// 2. connection phase
	
	edge e;		// edge to be inserted
	edge * eptr;	// inserted into search_maxheap of n1

	// now we will search for n1_verb in the verb tree of n1
	verb_tree_node * n1_verb = verb_tree_search(n1->next, data.verb);

	// if it is not there, insert it and initialise its query heap
	if (!n1_verb)
	{
		n1->next = verb_tree_insert(n1->next , n1->next , &(verb_recent), db_verb->db_verb_name);
		// make n1_verb point to recently inserted node
		n1_verb = verb_recent;

		// initialise query heap of n1_verb
		n1_verb->qheap = query_maxheap_init();
	}

	// copy the edge data from line_data data	
	e.weight = data.front_weight;
	e.truth_bit = data.truth_bit;
	//e.time = data.time;
	// verb_descriptor is not newly malloced
	// instead, the string malloced in db_desc_verb is used
	e.verb_descriptor = db_desc_verb -> db_desc_verb_name;
	e.noun_ptr = n3;
	
	// serch the particular edge to be inserted in query_maxheap of n1_verb
	query_maxheap_node * n1_edge = query_maxheap_search(n1_verb->qheap,e);

	// if edge exists, then copy it into edge pointer eptr
	if(n1_edge)
	{	
		eptr = copy_query_maxheap_node_into_edge(n1_edge);
	}
	
	// if the edge exists, then update its weight in search_maxheap
	// for that, it needs to be searched over there 
	search_maxheap_node * n1_searchnode = search_maxheap_search(n1->src_heap , data.verb , &e);
	if (n1_edge && n1_searchnode) 
	{
		// increment weights in query_maxheap and search_maxheap
		n1_edge->weight += data.front_weight;
		n1_searchnode->weight += data.front_weight;

	}
	// if it does not exist, then insert it
	else
	{
		//changes to be made for edge e in input insert()
		query_maxheap_insert(n1_verb->qheap,e);
		n1_edge = query_maxheap_search(n1_verb->qheap, e);
		eptr = copy_query_maxheap_node_into_edge(n1_edge);
		search_maxheap_insert(n1->src_heap , eptr , db_verb->db_verb_name ,  data.front_weight);
	}
	
	// now search for n3 in subclass_maxheap of n2	
	subclass_maxheap_node * n3_subnode = subclass_maxheap_search(n2->sub_heap , n3);
	
	// if it exists, then increment its weight
	if (n3_subnode)
	{
		n3_subnode->weight += data.front_weight;
	}
	// if it does not exist, then insert it
	else
	{
		subclass_maxheap_insert(n2->sub_heap , n3 , data.front_weight);
	}
	
	// now make a back connection from n3 to n1
	
	// search for the verb in prev verb_tree of n3
	verb_tree_node * n3_verb = verb_tree_search(n3->prev,data.verb);

	// if it does not exist, insert it and initialise its query_maxheap
	if (!n3_verb)
	{
		n3->prev = verb_tree_insert(n3->prev , n3->prev , &(verb_recent), db_verb->db_verb_name);
		// make n3_verb point to recently inserted node
		n3_verb = verb_recent;	
		// initialise query_maxheap of n3_verb
		n3_verb->qheap = query_maxheap_init();
	}
	
	e.weight = data.back_weight;
	e.truth_bit = data.truth_bit;
	//e.time = data.time;
	e.verb_descriptor = db_desc_verb->db_desc_verb_name;
	e.noun_ptr = n1;
	
	// search for edge in query_maxheap of n3_verb
	query_maxheap_node * n3_edge = query_maxheap_search(n3_verb->qheap,e);

	// if edge exists, update the weight
	if (n3_edge)
	{
		// increment weights in query_maxheap
		n3_edge -> weight += data.back_weight;
	}
	// if edge does not exist, then insert it
	else
	{
		query_maxheap_insert(n3_verb->qheap,e);
	}
	// for the definition of n3, we malloc memory for storing the string
	
	n3->noun_def = (char *) malloc(strlen(data.definition) + 1);
	strcpy(n3->noun_def, data.definition);
	return;
}

noun_tree_node * noun_tree_init(void) 
{
	return NULL;
}

noun_tree_node * noun_tree_createnode(char * noun_name , char * noun_def , long long int noun_id)
{
	noun_tree_node * nn = (noun_tree_node  *)malloc(sizeof(noun_tree_node ));
	if (nn)
	{
		nn->noun_name = (char *) malloc(strlen(noun_name) + 1);
		strcpy(nn->noun_name, noun_name);

		if (noun_def)
		{
			nn-> noun_def = (char *)malloc(strlen(noun_def)+1);
			strcpy(nn->noun_def,noun_def);
		}

		nn->noun_id = noun_id;

		nn->prev = NULL;
		nn->next=NULL;
		nn->src_heap = NULL;
		nn->sub_heap = NULL;
		nn->right = NULL;
		nn->left = NULL;
		nn->bf = 0;
	}
	return nn;

}

long long int noun_tree_height(noun_tree_node * root) 
{
	if (root == NULL)
	{
		return 0;
	}
	return max(noun_tree_height(root->left),noun_tree_height(root->right)) + 1;
}

void noun_tree_cal_balance(noun_tree_node * root)
{
	long long int lh = noun_tree_height(root->left);
	long long int rh = noun_tree_height(root->right);

	root->bf = lh-rh;
	return;
}

noun_tree_node * noun_tree_LL(noun_tree_node * root,noun_tree_node * p)
{
	noun_tree_node * pl = p->left;
	noun_tree_node * plr = pl->right;

	//p->left-pl->right;
	pl->right = p;
	p->left = plr;

	noun_tree_cal_balance(p);
	noun_tree_cal_balance(pl);
	
	if (root == p)
	{
		root = pl;
	}
	return pl;

}

noun_tree_node * noun_tree_RR(noun_tree_node * root,noun_tree_node * p)
{
	noun_tree_node * pr = p->right;
	noun_tree_node * prl = pr->left;

	pr->left = p;
	p->right = prl;

	noun_tree_cal_balance(p);
	noun_tree_cal_balance(pr);

	if (root == p)
	{
		root = pr;
	}
	return pr;

}

noun_tree_node * noun_tree_LR(noun_tree_node * root,noun_tree_node * p)
{
	noun_tree_node * pl = p->left;
	noun_tree_node * plr = pl->right;

	pl->right = plr->left;
	p->left = plr->right;

	plr->left = pl;
	plr->right = p;

	noun_tree_cal_balance(p);
	noun_tree_cal_balance(pl);
	noun_tree_cal_balance(plr);

	if (root == p)
	{
		root = plr;
	}
	return plr;

}

noun_tree_node  * noun_tree_RL(noun_tree_node * root,noun_tree_node * p)
{
	noun_tree_node * pr=p->right;
	noun_tree_node * prl = pr->left;

	p->right = prl->left;
	pr->left = prl->right;

	prl->right = pr;
	prl->left = p;

	noun_tree_cal_balance(p);
	noun_tree_cal_balance(pr);
	noun_tree_cal_balance(prl);

	if (root == p)
	{
		root = prl;
	}
	return prl;
}

noun_tree noun_tree_insert(noun_tree root, noun_tree_node * p, noun_tree_node **recent, char * noun_name , char * noun_def , long long int noun_id)
{
	if (p == NULL)
	{
		noun_tree_node * nn = noun_tree_createnode(noun_name , noun_def , noun_id);
		*recent = nn;
		return nn;
	}
	long long int result;
	result = string_cmp(p->noun_name, noun_name);
	if (result == 1)
	{
		p->left = noun_tree_insert(root,p->left, recent, noun_name,noun_def,noun_id);
	}
	else if (result == -1)
	{
		p->right = noun_tree_insert(root,p->right, recent, noun_name,noun_def,noun_id);
	}
	else if (result == 0)
	{
		if (p->noun_id > noun_id)
		{
			p->left = noun_tree_insert(root,p->left, recent, noun_name,noun_def,noun_id);
		}
		else if (p->noun_id < noun_id)
		{
			p->right = noun_tree_insert(root,p->right, recent, noun_name,noun_def,noun_id);
		}
		
	}
	
	noun_tree_cal_balance(p);
	
	if (p->bf == 2)
	{
		if (p->left->bf == -1)
		{
			 return noun_tree_LR(root,p);
		}
		else
		{
			return noun_tree_LL(root,p);
		}
	}
	else if (p->bf == -2)
	{
		if (p->right->bf == 1)
		{
			return noun_tree_RL(root,p);
		}
		else
		{
			return noun_tree_RR(root,p);
		}
	}
	return p;
}

noun_tree_node* noun_tree_search(noun_tree_node* root  , char* noun_name , long long int id)
{
       if (root==NULL)
       {
	 return NULL;
       }

       long long int result = string_cmp(root->noun_name,noun_name);
       if (result == 1)
       {
	       return noun_tree_search(root->left,noun_name,id);
       }
       else if (result==-1)
       {
	       return noun_tree_search(root->right,noun_name,id);
       }
       else
       {
		if (root->noun_id > id)
		{
                        return noun_tree_search(root->left,noun_name,id);
                }
                else if (root->noun_id < id)
		{
                        return noun_tree_search(root->right,noun_name,id);
                }
		return root;
       }
}

long long int noun_tree_count(noun_tree_node * root) {
	if(root == NULL) {
		return 0;
	}
	return 1 + noun_tree_count(root->left) + noun_tree_count(root->right);
}

void noun_tree_inorder(noun_tree_node * root)
{
	if (root==NULL)
	{
		return;
	}
	noun_tree_inorder(root->left);
	printf("%s\n",root->noun_name);
	// printf("%s\n" ,root->noun_def);
	printf("%lld\n",root->noun_id);
	printf("bf = %lld \n", root->bf);
	printf("-----\n\n");
	noun_tree_inorder(root->right);
	return;
}

#define MATCHING_PERCENTAGE 60
/* performs the preorder traversal of the noun_tree and returns matching nouns
 * matching is decided by string_cmp_percentage
 * strings that match above MATCHING_PERCENTAGE are called "matching"
 *
 * the function updates an array of noun_tree_node pointers, and its length
 * both these are parameters whose address is given to the function
 *
 * this array of pointers will contain pointers to all matching strings
 */
void noun_tree_preorder_string_match(noun_tree_node * root , char * input_noun , long long int input_noun_id , long long int * noun_arr_len , noun_tree_node *** noun_arr)
{
	if (root == NULL)
	{
		return;
	}

	// check if the id of the noun matches, and the string is "matching"
	if (input_noun_id == root->noun_id && string_cmp_percentage(root->noun_name , input_noun) >= MATCHING_PERCENTAGE)
	{
		// if it does, then add the pointer to this node into the array
		*noun_arr = (noun_tree_node **)realloc(*noun_arr ,sizeof(noun_tree_node * ) * ( (*noun_arr_len)+1));
        	(*noun_arr)[*(noun_arr_len)] = root;

		// update its length
		*noun_arr_len += 1;	
	}
	noun_tree_preorder_string_match(root->left , input_noun , input_noun_id , noun_arr_len , noun_arr);
	noun_tree_preorder_string_match(root->right , input_noun , input_noun_id , noun_arr_len , noun_arr);
	return;
}

/* performs the preorder traversal of the noun_tree
 * returns array of 
 * matching nouns that contain input_verb in their next verb_tree
 *
 * AND
 *
 * matching noun's subclasses that contain input_verb in their next verb_tree
 *
 * matching is decided by string_cmp_percentage
 * strings that match above MATCHING_PERCENTAGE are called "matching"
 *
 * the function updates an array of noun_tree_node pointers, and its length
 * both these are parameters whose address is given to the function
 *
 * this array of pointers will contain pointers to all matching strings
 */
void noun_tree_preorder_string_match_next_verb(noun_tree_node * root , char * input_noun , long long int input_noun_id , long long int * noun_arr_len , noun_tree_node *** noun_arr, char *input_verb)
{
	if (root==NULL)
	{
		return;
	}
	
	// check if the id of the noun matches, and the string is "matching"
	if (input_noun_id == root->noun_id && string_cmp_percentage(root->noun_name , input_noun) >= MATCHING_PERCENTAGE)
	{
		// now check if the next verb_tree contains the required verb
	 	if(verb_tree_search(root->next, input_verb)) 
		{
			*noun_arr = (noun_tree_node **)realloc(*noun_arr ,sizeof(noun_tree_node * ) * ( (*noun_arr_len)+1));
        		(*noun_arr)[*(noun_arr_len)] = root;
			*noun_arr_len += 1;	
		}
		// now check for the subclasses of the matching noun
		for(long long int i = 0; i < root->sub_heap->len; i++) 
		{
			if(verb_tree_search(((root->sub_heap->arr[i]).noun_ptr)->next, input_verb)) 
			{
					*noun_arr = (noun_tree_node **)realloc(*noun_arr ,sizeof(noun_tree_node * ) * ( (*noun_arr_len)+1));
        				(*noun_arr)[*(noun_arr_len)] = root;
					*noun_arr_len += 1;	
				}
		}
	}
	noun_tree_preorder_string_match_next_verb(root->left , input_noun , input_noun_id , noun_arr_len , noun_arr, input_verb);
	noun_tree_preorder_string_match_next_verb(root->right , input_noun , input_noun_id , noun_arr_len , noun_arr, input_verb);
	return;

}

/* performs the preorder traversal of the noun_tree
 * returns array of 
 * matching nouns that contain input_verb in their prev verb_tree
 *
 * AND
 *
 * matching noun's subclasses that contain input_verb in their prev verb_tree
 *
 * matching is decided by string_cmp_percentage
 * strings that match above MATCHING_PERCENTAGE are called "matching"
 *
 * the function updates an array of noun_tree_node pointers, and its length
 * both these are parameters whose address is given to the function
 *
 * this array of pointers will contain pointers to all matching strings
 */
void noun_tree_preorder_string_match_prev_verb(noun_tree_node * root , char * input_noun , long long int input_noun_id , long long int * noun_arr_len , noun_tree_node *** noun_arr, char *input_verb)
{
	if (root==NULL)
	{
		return;
	}
	// check if the id of the noun matches, and the string is "matching"
	if (input_noun_id == root->noun_id && string_cmp_percentage(root->noun_name , input_noun) >= 60)
	{
		// now check if the next verb_tree contains the required verb
	 	if(verb_tree_search(root->prev , input_verb)) 
		{
			*noun_arr = (noun_tree_node **)realloc(*noun_arr ,sizeof(noun_tree_node * ) * ( (*noun_arr_len)+1));
        		(*noun_arr)[*(noun_arr_len)] = root;
			*noun_arr_len += 1;	
		}
		// now check for the subclasses of the matching noun
		for(long long int i = 0; i < root->sub_heap->len; i++) 
		{
			if(verb_tree_search(((root->sub_heap->arr[i]).noun_ptr)->prev, input_verb)) 
			{
					*noun_arr = (noun_tree_node **)realloc(*noun_arr ,sizeof(noun_tree_node * ) * ( (*noun_arr_len)+1));
        				(*noun_arr)[*(noun_arr_len)] = root;
					*noun_arr_len += 1;	
				}
		}
	}
	noun_tree_preorder_string_match_next_verb(root->left , input_noun , input_noun_id , noun_arr_len , noun_arr, input_verb);
	noun_tree_preorder_string_match_next_verb(root->right , input_noun , input_noun_id , noun_arr_len , noun_arr, input_verb);
	return;

}

/* performs the preorder traversal of the noun_tree
 * returns array of 
 * matching nouns that contain
 * 	i)  input_verb in their next verb_tree
 * 	ii) input_verb's qheap contains input_verb_desc
 *
 * AND
 *
 * matching noun's subclasses that contain
 * 	i)  input_verb in their next verb_tree
 * 	ii) input_verb's qheap contains input_verb_desc
 *
 * matching is decided by string_cmp_percentage
 * strings that match above MATCHING_PERCENTAGE are called "matching"
 *
 * the function updates an array of noun_tree_node pointers, and its length
 * both these are parameters whose address is given to the function
 *
 * this array of pointers will contain pointers to all matching strings
 */
void noun_tree_preorder_string_match_next_verb_verb_desc(noun_tree_node * root , char * input_noun , long long int input_noun_id , long long int * noun_arr_len , noun_tree_node *** noun_arr, char *input_verb, char * input_verb_desc)
{
	if (root==NULL)
	{
		return;
	}
	verb_tree_node * verb;
	long long int i;
	// check if the id of the noun matches, and the string is "matching"
	if (input_noun_id == root->noun_id && string_cmp_percentage(root->noun_name , input_noun) >= MATCHING_PERCENTAGE) 
	{
		verb = verb_tree_search(root->next, input_verb);
		// now check if the input_verb exists
	 	if(verb) {
			// if it does, then check its qheap for input_verb_desc
			for(i = 0; i < verb->qheap->len; i++) {
				if(string_cmp(verb->qheap->arr[i].verb_descriptor, input_verb_desc) == 0) {
					*noun_arr = (noun_tree_node **)realloc(*noun_arr ,sizeof(noun_tree_node * ) * ( (*noun_arr_len)+1));
        				(*noun_arr)[*(noun_arr_len)] = root;
					*noun_arr_len += 1;	
				}
			}
		}
		// now check its sub_heap by following the same procedure
		for(i = 0; i < root->sub_heap->len; i++) {
			verb = verb_tree_search((root->sub_heap->arr[i].noun_ptr)->next, input_verb);
			if(verb) {
				for(i = 0; i < verb->qheap->len; i++) {
					if(string_cmp(verb->qheap->arr[i].verb_descriptor, input_verb_desc) == 0) {
						*noun_arr = (noun_tree_node **)realloc(*noun_arr ,sizeof(noun_tree_node * ) * ( (*noun_arr_len)+1));
        					(*noun_arr)[*(noun_arr_len)] = root;
						*noun_arr_len += 1;	
					}
				}
			}
		}
	}
	noun_tree_preorder_string_match_next_verb_verb_desc(root->left , input_noun , input_noun_id , noun_arr_len , noun_arr, input_verb, input_verb_desc);
	noun_tree_preorder_string_match_next_verb_verb_desc(root->right , input_noun , input_noun_id , noun_arr_len , noun_arr, input_verb, input_verb_desc);
	return;
}

/* performs the preorder traversal of the noun_tree
 * returns array of 
 * matching nouns that contain
 * 	i)  input_verb in their prev verb_tree
 * 	ii) input_verb's qheap contains input_verb_desc
 *
 * AND
 *
 * matching noun's subclasses that contain
 * 	i)  input_verb in their prev verb_tree
 * 	ii) input_verb's qheap contains input_verb_desc
 *
 * matching is decided by string_cmp_percentage
 * strings that match above MATCHING_PERCENTAGE are called "matching"
 *
 * the function updates an array of noun_tree_node pointers, and its length
 * both these are parameters whose address is given to the function
 *
 * this array of pointers will contain pointers to all matching strings
 */
void noun_tree_preorder_string_match_prev_verb_verb_desc(noun_tree_node * root , char * input_noun , long long int input_noun_id , long long int * noun_arr_len , noun_tree_node *** noun_arr, char *input_verb, char * input_verb_desc)
{
	if (root==NULL)
	{
		return;
	}
	verb_tree_node * verb;	// verb_tree_node which contains input_verb
	long long int i;	// traverses the sub_heap, query_heap
	
	// check if the id of the noun matches, and the string is "matching"
	if (input_noun_id == root->noun_id && string_cmp_percentage(root->noun_name , input_noun) >= MATCHING_PERCENTAGE) 
	{
		verb = verb_tree_search(root->prev, input_verb);
		// now check if the input_verb exists
	 	if(verb) 
		{
			// if it does, then check its qheap for input_verb_desc
			for(i = 0; i < verb->qheap->len; i++) 
			{
				if(string_cmp(verb->qheap->arr[i].verb_descriptor, input_verb_desc) == 0) 
				{
					*noun_arr = (noun_tree_node **)realloc(*noun_arr ,sizeof(noun_tree_node * ) * ( (*noun_arr_len)+1));
        				(*noun_arr)[*(noun_arr_len)] = root;
					*noun_arr_len += 1;	
				}
			}
		}
		// now check its sub_heap by following the same procedure
		for(i = 0; i < root->sub_heap->len; i++) 
		{
			verb = verb_tree_search((root->sub_heap->arr[i].noun_ptr)->prev, input_verb);
			if(verb) 
			{
				for(i = 0; i < verb->qheap->len; i++) 
				{
					if(string_cmp(verb->qheap->arr[i].verb_descriptor, input_verb_desc) == 0) 
					{
						*noun_arr = (noun_tree_node **)realloc(*noun_arr ,sizeof(noun_tree_node * ) * ( (*noun_arr_len)+1));
        					(*noun_arr)[*(noun_arr_len)] = root;
						*noun_arr_len += 1;	
					}
				}
			}
		}
	}
	noun_tree_preorder_string_match_prev_verb_verb_desc(root->left , input_noun , input_noun_id , noun_arr_len , noun_arr, input_verb, input_verb_desc);
	noun_tree_preorder_string_match_prev_verb_verb_desc(root->right , input_noun , input_noun_id , noun_arr_len , noun_arr, input_verb, input_verb_desc);
	return;
}

/*
    *------------------------------------------------------------------------------------  
    *                 HEAP
    *
    * ARRAY REPRESENTATION OF BINARY TREE
    *   if node is at index 'i' :
    *           its left child : 2i + 1
    *           its right child : 2i + 2
    *           parent : (i-1)/2
    * 
    * 
    * HEAP is a Complete Binary Tree!
    * A Complete binary tree of height 'h' is a full binary tree
    * upto height 'h-1' and then elements starts filling from left to right
    * 
    *               OR
    * We can define it in the array , there should not be any empty gaps (gaps 
    * in between elements) 
    * 
    * Height of a Complete Binary Tree is : ln n
    * 
    *           &
    *          / \
    *         &   &
    *        /  \
    *       &    & 
    * 
    * This is a Complete Binary Tree
    * 
    * 
    *           &
    *          /  \
    *         &    &
    *             /  \
    *            &    &
    * 
    * This is not a Complete Binary Tree
    * 
    * 
    * Heap is further classified to 1. Minimum heap
    *                               2. Maximum heap
    * 
    * Duplicates are allowed in heap!
    * height = O(ln n)
    * 
    * 
    * 
    * INSERTION IN HEAP
    * Insert the newly added element at the end of the array , and
    * start comparing it with its parent [ (i-1)/2 ] , if needed
    * swap it
    * The size of the array is incresed by size 1.
    * Time Complexity : O(n ln n)
    * 
    * DELETION IN HEAP
    * We can delete only the 1st element in the heap.
    * For max heap : 1st element refers to the highest priority element!
    * We have to swap this element with the last element
    * of the array and so start performing swapping with
    * its parent if needed.
    * The size of the array is decreased by size 1.
    * Time Complexity : O(n ln n)
    * 
    * 
    * 
    * HEAPSORT
    * For sorting the array we follow the "while" procedure
    * of the deleting the 1st element , swapping it with the last element 
    * and decreasing the length of the array visibility by 1 
    * the swapped element at position 1st will be compared with its child and 
    * so necessary swapping will take place.
    * We will loop this till the array length , So that we get the decreasing array of elements.
    * 
    * Time Complexity : O( n ln n)
    * 
    * 
    * NOTE : direction of adjustment is UPWARDS in both insertion and deletion case
    * 
    * 
    * We used MAXHEAP in 1. subclass_maxheap
    *                    2.  query_maxheap
    *                    3.  search_maxheap
    * 
    * We used maxheap to get the priority of the dataset we will be storing
    * So that user will get the most weighted information(valueable information)
    * of what he is looking for:)
    * -----------------------------------------------------------------------------------------------------
*/    
query_maxheap_node * query_maxheap_search(query_maxheap *hp, edge e) 
{
	long long int i;
	for(i = 0; i < hp->len; i++) 
	{
		if(hp->arr[i].noun_ptr == e.noun_ptr && hp->arr[i].truth_bit == e.truth_bit && string_cmp(e.verb_descriptor, hp->arr[i].verb_descriptor) == 0) 
		{
			return &(hp->arr[i]);
		}
	}
	return NULL;
}

query_maxheap* query_maxheap_init(void)
{
	query_maxheap* nn = (query_maxheap *)malloc(sizeof(query_maxheap));
	if (nn)
	{
		nn->len=0;
		nn->arr = NULL;
	}
	return nn;
}

void query_maxheap_swap(query_maxheap_node* a , query_maxheap_node* b)
{
       query_maxheap_node temp = *a;
       *a = *b;
       *b = temp;
       return;
}

void query_maxheap_insert(query_maxheap* hp,edge e )
{
	hp->arr = (query_maxheap_node *)realloc(hp->arr , sizeof(query_maxheap_node)*(hp->len+1));
	long long int i = hp->len;
	hp->arr[i].weight = e.weight;
	hp->arr[i].noun_ptr = e.noun_ptr;
	hp->arr[i].truth_bit=e.truth_bit;
	hp->arr[i].verb_descriptor=e.verb_descriptor;
	hp->arr[i].end_time=e.end_time;
	while (i>0 && hp->arr[i].weight > hp->arr[(i-1)/2].weight)
	{
		query_maxheap_swap(&hp->arr[i],&hp->arr[(i-1)/2]);
		i = (i-1)/2;
	}
	hp->len++;
}

void query_maxheap_print(query_maxheap* h)
{
	for (long long int i=0;i<h->len;i++)
	{
		printf("%lld ", h->arr[i].weight);
		printf("%lld ", h->arr[i].truth_bit);
		printf("%s ", (h->arr[i].noun_ptr)->noun_name);
		printf("%s ", h->arr[i].verb_descriptor);
		//time to be printed...
		printf("\n");
	}
	return;
}

query_maxheap_node * query_maxheap_delete(query_maxheap* hp)
{
	if (hp->len==0)
	{
		return NULL;
	}
	query_maxheap_node *temp = NULL;
	long long int i = hp->len-1;	
	long long int j = 0;

	query_maxheap_swap(&hp->arr[0],&hp->arr[i]);
	while ( (2*j) + 1 < i)
	{
		long long int largest = (2*j) + 1;	
		if (((2*j) + 2 < i) && hp->arr[largest].weight < hp->arr[ (2*j) + 2].weight)
		{
			largest = (2*j)+2;
		}
		if (hp->arr[j].weight < hp->arr[largest].weight)
		{
			query_maxheap_swap(&hp->arr[j],&hp->arr[largest]);
		}
		j=largest;
	}
	hp->len--;
	temp = &(hp->arr[hp->len]);
	return temp;
}

long long int edge_compare(edge *e1, edge *e2) {
	if(e1->truth_bit == e2->truth_bit && (string_cmp(e1->verb_descriptor, e2->verb_descriptor) == 0) && e1->noun_ptr == e2->noun_ptr) {
		return 1;
	}
	return 0;

}

search_maxheap_node * search_maxheap_search(search_maxheap *hp, char *verb, edge *e) 
{
        long long int i;

        for(i = 0; i < hp->len; i++) 
	{
                if((string_cmp(hp->arr[i].verb, verb) == 0) && (edge_compare(hp->arr[i].e, e)) == 1)
		{
                        return &(hp->arr[i]);
                }
        }
        return NULL;
}

search_maxheap* search_maxheap_init(void)
{
	search_maxheap* nn = (search_maxheap *)malloc(sizeof(search_maxheap));
	if (nn)
	{
		nn->len=0;
		nn->arr = NULL;
	}
	return nn;
}

void search_maxheap_swap(search_maxheap_node* a, search_maxheap_node* b)
{
	search_maxheap_node temp=*a;
	*a=*b;
	*b=temp;
	return;
}


void search_maxheap_insert(search_maxheap* hp, edge *e ,char * verb, long long int weight)
{
	hp->arr = (search_maxheap_node *)realloc(hp->arr , sizeof(search_maxheap_node)*(hp->len + 1));
	long long int i = hp->len;
	hp->arr[i].weight = weight;
	hp->arr[i].e = e;
	hp->arr[i].verb = verb;
	while (i > 0 && hp->arr[i].weight > hp->arr[(i - 1) / 2].weight)
	{
		search_maxheap_swap(&hp->arr[i],&hp->arr[(i - 1) / 2]);
		i = (i - 1) / 2;
	}
	hp->len++;
}

void search_maxheap_print(search_maxheap* h)
{
	for (long long int i=0;i<h->len;i++)
	{
		printf("%lld ", h->arr[i].weight);
		printf("%s ", (h->arr[i].verb));
		printf("\n");
	}
	return;
}

search_maxheap_node * search_maxheap_delete(search_maxheap* hp)
{
	if (hp->len==0)
	{
		return NULL;
	}
	search_maxheap_node *temp = NULL;
	long long int i = hp->len-1;	
	long long int j = 0;

	search_maxheap_swap(&hp->arr[0],&hp->arr[i]);
	while ( (2*j) + 1 < i)
	{
		long long int largest = (2*j) + 1;	
		if (((2*j) + 2 < i) && hp->arr[largest].weight < hp->arr[ (2*j) + 2].weight)
		{
			largest = (2*j)+2;
		}
		if (hp->arr[j].weight < hp->arr[largest].weight)
		{
			search_maxheap_swap(&hp->arr[j],&hp->arr[largest]);
		}
		j=largest;
	}
	hp->len--;
	temp = &(hp->arr[hp->len]);
	return temp;
}

subclass_maxheap_node * subclass_maxheap_search(subclass_maxheap *hp, noun_tree_node *noun_ptr) 
{
	long long int i;
	for(i = 0; i < hp->len; i++) 
	{
		if(hp->arr[i].noun_ptr == noun_ptr) 
		{
			return &(hp->arr[i]);
		}
	}
	return NULL;
}

subclass_maxheap* subclass_maxheap_init(void)
{
	subclass_maxheap* nn = (subclass_maxheap *)malloc(sizeof(subclass_maxheap));
	if (nn)
	{
		nn->len = 0;
		nn->arr = NULL;
	}
	return nn;
}

void subclass_maxheap_swap(subclass_maxheap_node* a, subclass_maxheap_node* b)
{
	subclass_maxheap_node temp=*a;
	*a=*b;
	*b=temp;
	return;
}

void subclass_maxheap_insert(subclass_maxheap* hp, noun_tree_node *noun_ptr, long long int weight)
{
	hp->arr = (subclass_maxheap_node *)realloc(hp->arr , sizeof(subclass_maxheap_node)*(hp->len+1));
	long long int i = hp->len;
	hp->arr[i].weight = weight;
	hp->arr[i].noun_ptr = noun_ptr;
	while (i>0 && hp->arr[i].weight > hp->arr[(i - 1) / 2].weight)
	{
		subclass_maxheap_swap(&hp->arr[i],&hp->arr[(i - 1) / 2]);
		i = (i - 1) / 2;
	}
	hp->len++;
}

void subclass_maxheap_print(subclass_maxheap* h)
{
	for (long long int i=0;i<h->len;i++)
	{
		printf("%lld ", h->arr[i].weight);
		printf("%s ", (h->arr[i].noun_ptr)->noun_name);
		printf("\n");
	}
	return;
}

subclass_maxheap_node * subclass_maxheap_delete(subclass_maxheap* hp)
{
	if (hp->len==0)
	{
		return NULL;
	}
	subclass_maxheap_node *temp = NULL;
	long long int i = hp->len-1;	
	long long int j = 0;

	subclass_maxheap_swap(&hp->arr[0],&hp->arr[i]);
	while ( (2 * j) + 1 < i)
	{
		long long int largest = (2 * j) + 1;	
		if (((2 * j) + 2 < i) && hp->arr[largest].weight < hp->arr[ (2*j) + 2].weight)
		{
			largest = (2 * j)+2;
		}
		if (hp->arr[j].weight < hp->arr[largest].weight)
		{
			subclass_maxheap_swap(&hp->arr[j],&hp->arr[largest]);
		}
		j = largest;
	}
	hp->len--;
	temp = &(hp->arr[hp->len]);
	return temp;
}


verb_tree_node * verb_tree_init(void) 
{
	return NULL;
}

verb_tree_node * verb_tree_createnode(char * data)
{
	verb_tree_node * nn = (verb_tree_node  *)malloc(sizeof(verb_tree_node ));
	if (nn)
	{
		nn->qheap = NULL;
		nn->verb_name = (char *) malloc(strlen(data) + 1);
		strcpy(nn->verb_name, data);
		nn->right = NULL;
		nn->left = NULL;
		nn->bf = 0;
	}
	return nn;

}

long long int verb_tree_height(verb_tree_node * root) 
{
	if (root == NULL)
	{
		return 0;
	}
	return max(verb_tree_height(root->left),verb_tree_height(root->right)) + 1;
}

void verb_tree_cal_balance(verb_tree_node * root)
{
	long long int lh = verb_tree_height(root->left);
	long long int rh = verb_tree_height(root->right);

	root->bf = lh-rh;
	return;
}

verb_tree_node * verb_tree_LL(verb_tree_node * root,verb_tree_node * p)
{
	verb_tree_node * pl = p->left;
	verb_tree_node * plr = pl->right;

	pl->right=p;
	p->left = plr;

	verb_tree_cal_balance(p);
	verb_tree_cal_balance(pl);
	
	if (root == p)
	{
		root = pl;
	}
	return pl;

}

verb_tree_node * verb_tree_RR(verb_tree_node * root,verb_tree_node * p)
{
	verb_tree_node * pr = p->right;
	verb_tree_node * prl = pr->left;

	pr->left = p;
	p->right = prl;

	verb_tree_cal_balance(p);
	verb_tree_cal_balance(pr);

	if (root == p)
	{
		root = pr;
	}
	return pr;

}

verb_tree_node * verb_tree_LR(verb_tree_node * root,verb_tree_node * p)
{
	verb_tree_node * pl = p->left;
	verb_tree_node * plr = pl->right;

	pl->right = plr->left;
	p->left = plr->right;

	plr->left = pl;
	plr->right = p;

	verb_tree_cal_balance(p);
	verb_tree_cal_balance(pl);
	verb_tree_cal_balance(plr);

	if (root == p)
	{
		root = plr;
	}
	return plr;

}

verb_tree_node  * verb_tree_RL(verb_tree_node * root,verb_tree_node * p)
{
	verb_tree_node * pr=p->right;
	verb_tree_node * prl = pr->left;

	p->right = prl->left;
	pr->left = prl->right;

	prl->right = pr;
	prl->left = p;

	verb_tree_cal_balance(p);
	verb_tree_cal_balance(pr);
	verb_tree_cal_balance(prl);

	if (root == p)
	{
		root = prl;
	}
	return prl;
}

void verb_tree_inorder(verb_tree_node * root)
{
	if (root==NULL)
	{
		return;
	}
	verb_tree_inorder(root->left);
	printf("%s ",root->verb_name);
	printf("bf = %lld \n", root->bf);
	verb_tree_inorder(root->right);
	return;

}

verb_tree verb_tree_insert(verb_tree root ,verb_tree_node * p, verb_tree_node **recent, char * data)
{
        if (p == NULL)
        {
                verb_tree_node * nn = verb_tree_createnode(data);
		*recent = nn;
		return nn;
        }
        long long int result;
        result = string_cmp(p->verb_name, data);
        if (result == 1)
        {
		p->left = verb_tree_insert(root, p->left, recent, data);
        }
        else if (result == -1)
        {

		p->right = verb_tree_insert(root, p->right, recent, data);
        }

        verb_tree_cal_balance(p);

        if (p->bf == 2)
        {
                if (p->left->bf == -1)
                { 
                        return verb_tree_LR(root,p);
                }
                else
                {
                        return verb_tree_LL(root,p);
                }
        }
        else if (p->bf == -2)
        {
                if (p->right->bf == 1)
                {
                        return verb_tree_RL(root,p);
                }
                else
                {
                        return verb_tree_RR(root,p);
                }
        }
        return p;

}
	
verb_tree_node* verb_tree_search(verb_tree_node* root  , char* verb_name)
{
       if (root==NULL)
       {
         return NULL;
       }
       long long int result = string_cmp(root->verb_name,verb_name);
       if (result == 1)
       {
               return verb_tree_search(root->left,verb_name);
       }
       else if (result==-1)
       {
               return verb_tree_search(root->right, verb_name);
       }
       else
       {
                return root;
       }
}

/* traversal queue is a queue used while printing information lines.
 * node of the traversal queue consisits of a pointer to a noun node, 
 * a string named verb_ptr,a pointer to an edge, count of alloc_lines,
 * and a pointer to the next queue node.
 * 
 * traversal queue initialize function:
 * 1. parameters: none.
 * 2. returns a pointer to a traversal queue.
 */
traversal_queue *traversal_queue_init(void) 
{
	// malloc a pointer to a traversal queue with the sizeof traversal_queue
	traversal_queue *q = (traversal_queue *) malloc (sizeof(traversal_queue));
	/* to prevent any segmentation fault, check if not null.
	 * if not null,point the front and rear pointers to NULL,
	 * so that they are not dangling.
	 * initialize length of queue to 0.
	 */
	if(q) 
	{
		q->front = NULL;
		q->rear = NULL;
		q->length = 0;
	}
	// return the pointer q.
	return q;
}

/* traversal queue enqueue function: 
 * enqueues a traversal queue node to the traversal queue.
 *
 * 1.Parameters: 1) Pointer to the traversal queue,
 * 		 2)Node to be enqueued.
 *
 * 2. Returns : Nothing (All changes are made inside the function)
 */
void traversal_queue_enqueue (traversal_queue *q, traversal_queue_node * data)
{

	// if queue is empty then change front as well
	if(q->front == NULL) 
	{
		// make front pointer point to the new node(data)
		q->front = data;
		//make rear pointer point to the new node (data)
		q->rear = data;
		// increment the length of the queue
		q->length += 1;
		// next pointer of the new node (data) should point to NULL.
		data->next = NULL;
		return;
	}
	// if queue is not empty, the last node's next pointer 
	// should point to the new node(data) 
	q->rear->next = data;
	// next pointer of the new node (data) should point to NULL
	data->next = NULL;
	// rear pointer of the queue should point to the enqueued node
	q->rear = q->rear->next;
	// increment the length of queue
	q->length += 1;
}


/* traversal queue dequeue function:
 * dequeues a traversal queue node form the traversal queue and returns pointer
 * to that node.
 * 1.Parameters: 1)Pointer to the traversal queue.
 * 2.Returns a pointer to the dequeued node.
 */
traversal_queue_node *traversal_queue_dequeue(traversal_queue *q) 
{
	// if queue is empty
	if(q->front == NULL) 
	{
		// return NULL as queue is empty.
		return NULL;
	}
	// create a traversal queue node pointer 'temp'
	traversal_queue_node *temp;
	// temp should point to the node to be dequeued.
	temp = q->front;
	// front pointer of the queue should point to the next node(if present)
	q->front = q->front->next;
	// if queue had only one node, then change rear
	if(q->front == NULL) 
	{
		// rear pointer of the queue should point to NULL
		// as the queue is now empty.
		q->rear = NULL;
	}
	// decrement the length of the queue.
	q->length -= 1;
	// return the pointer to the dequeued node.
	return temp;
}


/* function to check if the traversal queue is empty:
 *
 * 1. Parameters: 1)pointer to the traversal queue.
 *
 * 2. Returns a long long integer whose value is:
 * 		1, if the queue is empty,
 * 		0, if the queue is not empty.
 */
long long int traversal_queue_isempty(traversal_queue *q) 
{
	// return 1 if the queue is empty, else return 0.
	return q->length == 0;
}


/* traversal queue peek function:
 * 1. Parameters: 1)pointer to the traversal queue.
 * 2. Returns a pointer to a node which is identical to 1st node of the queue.
 */
traversal_queue_node *traversal_queue_peek(traversal_queue *q) 
{
        // if queue is empty, return NULL.
        if(q->front == NULL) 
		{
                return NULL;
        }
	// create a traversal queue node pointer, which is to be returned,
	// and malloc it with the size of a traversal queue node.
        traversal_queue_node *temp = (traversal_queue_node *) malloc(sizeof(traversal_queue_node));
	// noun_ptr of the node pointed by temp pointer should point to the 
	// noun_node which is pointed by the first node of the queue.
        temp->noun_ptr = q->front->noun_ptr;
	// verb_ptr of the node pointed by temp pointer should point to the 
	// string pointed by the verb_ptr of first node of the queue.
        temp->verb_ptr = q->front->verb_ptr;
	// edge pointer of the node pointed by temp pointer should point to 
	// the edge pointed by the edge pointer of the queue's first node.
        temp->e = q->front->e;
	// alloc_lines of the node pointed by the temp pointershould be equal 
	// to the alloc_lines of the first node of the queue.
        temp->alloc_lines = q->front->alloc_lines;
	// return the temp pointer
        return temp;
}



/*traversal queue print function:
 * 1.Parameters: 1)pointer to the traversal queue.
 * 2. Returns : Nothing (Contents of the traversal queue are printed). 
 */
void traversal_queue_print (traversal_queue *q) 
{
	// return if the queue is empty.
	if(traversal_queue_isempty(q)) 
	{
		return;
	}
		// create a traversal queue node pointer temp which will
		// traverse through the queue. 
        traversal_queue_node *temp;
		// tempshould point to the first node of the queue initially.
        temp = q->front;
	// the while loop will iterate until the temp pointer is not NULL
	// ,i.e, till the end of the queue.
    while(temp) 
	{
		/* if edge pointer of the node pointed by temp is NULL,
		 * print the noun name of the noun_node pointed to by the 
		 * noun_ptr of temp, verb, and the alloc lines of node pointed by temp
		 */
		if(!temp->e) 
		{
                	printf("%s %s %lld\n", temp->noun_ptr->noun_name, temp->verb_ptr, temp->alloc_lines);
		}
		/* else, print the noun name of the noun_node pointed to by the
		 * noun_ptr of temp, verb, verb descriptor for the edge pointed by e, 
		 * weight for the edge pointed by e and alloc lines of the node 
		 * pointed to by temp. 
		 */
		else {

                	printf("%s %s %s %lld %lld\n", temp->noun_ptr->noun_name, temp->verb_ptr, temp->e->verb_descriptor, temp->e->weight, temp->alloc_lines);
		}
		// temp should now point to the next node in the queue
                temp = temp->next;
        }

        return;
}

// adds the weights of all nodes in search_maxheap and returns the sum
long long int search_maxheap_add_weights(search_maxheap* hp)
{
	// if heap is empty, then return zero
        if (hp == NULL || hp->len == 0)
	{
                return 0;
        }

        long long int i;
        long long int sum = 0;

        for (i = 0; i < hp->len; i++)
	{
               sum += hp->arr[i].weight;
        }
        return sum;
}

/* copies search_maxheap hp into a new search_maxheap
 * memory is malloced for this new search_maxheap, should be freed by caller
 */
search_maxheap * search_maxheap_copy(search_maxheap* hp)
{
        if (hp == NULL || hp->len == 0)
	{
                return NULL;
        }
        search_maxheap * sh = search_maxheap_init();
        long long int i;
        for (i = 0;i < hp->len; i++)
	{
                search_maxheap_insert(sh , hp->arr[i].e , hp->arr[i].verb , hp->arr[i].weight);
        }
        return sh;
}

long long int alternate = 0;
/* approximates the floating value num to an integer
 *
 * if decimal point < 0.5, then returns floor
 * if decimal point > 0.5, then returns ceiling
 *
 * 1.5, 2.5 etc will be alternately converted to floor / ceiling
 */
long long int approx(float num)
{
        long long int a = num;
        num = num - a;
        if (num < 0.5)
	{

                return a;
        }
	if(num == 0.5) {
		if(alternate % 2== 1) {
			alternate++;
			return a + 1;
		}
		alternate++;
		return a;
	}
        return a+1;
}

/* calculates the number of lines to be allocated to a particular noun
 * the lines are allocated in prpoortion to the connection's weight
 * with respect to the total weight of all the other connections
 *
 * child count of the noun is subtracted since those lines are reserved
 */
long long int calc_line(float weight1 , float sum_weights ,float total_lines , float child_count)
{
        return approx((weight1/sum_weights) * (total_lines - child_count));
}

/* calculates the number of lines to be allocated to a particular noun
 * the lines are allocated in prpoortion to the connection's weight
 * with respect to the total weight of all the other connections
 *
 * child count of the noun is not subtracted since subclasses are considered
 */
long long int calc_line_subclass(float weight1 , float sum_weights ,float total_lines)
{
        return approx((weight1/sum_weights) * (total_lines));
}

/* allocates lines for each node in the search_maxheap
 * enqueues each node into a traversal_queue
 * returns the queue to the caller
 *
 * memory is malloced for the traversal_queue, should be fred by caller
 */
traversal_queue* allocate_lines_search_maxheap(noun_tree_node* noun_tree_node_ptr , search_maxheap* hp , long long int total_lines)
{

        long long int sum_weights;	// addition of weights of search_maxheap
        traversal_queue * tq;		// traversal_queue pointer to be returned
	traversal_queue_node *tq_node;	// traversal_queue node
        search_maxheap * sh;		// stores a copy of the search_maxheap
	search_maxheap_node * src_node;	// search_maxheap_node
        long long int i;		// traverses the search_maxheap

        tq = traversal_queue_init();
	sum_weights = search_maxheap_add_weights(hp);
        sh = search_maxheap_copy(hp);
	
	// for each node in the maxheap, allocate lines and enqueue into tq
        for (i = 0; i < hp->len; i++)
	{
                tq_node = (traversal_queue_node * )malloc(sizeof(traversal_queue_node));
                src_node = search_maxheap_delete(sh);
                tq_node->alloc_lines = calc_line(src_node->weight , sum_weights , total_lines ,sh->len);
                tq_node ->verb_ptr = src_node->verb;
                tq_node->noun_ptr = noun_tree_node_ptr;
                tq_node->e = src_node->e;
                traversal_queue_enqueue(tq,tq_node);
        }
        return tq;
}

long long int subclass_maxheap_add_weights(subclass_maxheap* hp)
{
        if (hp==NULL || hp->len==0)
	{
                return 0;
        }
        long long int i;
        long long int sum=0;
        for ( i=0 ; i<hp->len ; i++)
	{
               sum += hp->arr[i].weight;
        }
        return sum;
}

subclass_maxheap * subclass_maxheap_copy(subclass_maxheap* hp)
{
        if (hp==NULL || hp->len == 0)
	{
                return NULL;
        }
        subclass_maxheap * sb = subclass_maxheap_init();
        long long int i;
        for (i=0;i<hp->len;i++)
	{
                subclass_maxheap_insert(sb , hp->arr[i].noun_ptr , hp->arr[i].weight);
        }
        return sb;
}




traversal_queue* allocate_lines_subclass_maxheap(subclass_maxheap* hp , long long int total_lines)
{

        long long int sum_weights;	// addition of weights of subclass_maxheap
        traversal_queue * tq;		// traversal_queue pointer to be returned
	traversal_queue_node *tq_node;	// traversal_queue node
        subclass_maxheap * sb;		// stores a copy of the subclass_maxheap
	subclass_maxheap_node * sb_node;// subclass_heap node
        long long int i;		// traverses the search_maxheap

        
	sum_weights = subclass_maxheap_add_weights(hp);
        tq = traversal_queue_init();
        sb = subclass_maxheap_copy(hp);

        for (i = 0; i < hp->len; i++)
	{
                tq_node = (traversal_queue_node * )malloc(sizeof(traversal_queue_node));
                sb_node = subclass_maxheap_delete(sb);
                tq_node->alloc_lines= calc_line_subclass(sb_node->weight , sum_weights , total_lines);
                tq_node ->verb_ptr = NULL;
                tq_node->noun_ptr = sb_node -> noun_ptr;
                tq_node->e = NULL;
                traversal_queue_enqueue(tq,tq_node);
        }

        return tq;
}

// prints the edge, i.e. the connection
void edge_print(struct edge e)
{
        if (e.truth_bit == 0)
	{
                printf("not ");
        }
	if(e.verb_descriptor) 
	{
		if(e.verb_descriptor[0] != '\0') 
		{
        		printf("%s ",e.verb_descriptor);
		}
	}
	print_str_without_context((e.noun_ptr)->noun_name, '_');
        return;
}

long long int search_maxheap_isempty(search_maxheap* src)
{
        return src->len==0;
}


long long int display_info_lines(knowledge_graph * kg, char * input_noun, long long int input_noun_id,long long int total_lines)
{
        noun_tree_node * noun_ptr= noun_tree_search(kg->main_noun_tree, input_noun, input_noun_id);
	if(!noun_ptr) 
	{
		
		// if noun doesn't exist, then search for similar nodes
		long long int noun_arr_len=0;

		noun_tree_node** noun_arr = NULL;
		noun_tree_preorder_string_match(kg->main_noun_tree , input_noun , input_noun_id , &noun_arr_len ,&noun_arr);

		if(noun_arr_len > 0) 
		{
			printf("Did you mean : \n");
			for (long long int i=0;i<noun_arr_len;i++)
			{
				printf("%lld : %s\n",i + 1,noun_arr[i]->noun_name);
			}
		
			long long int choice;
			scanf("%lld",&choice);
			
			long long int divide_lines = (float)total_lines / (float)noun_arr_len;
			long long int remaining_lines = 0;
			long long int k=0;
			long long int count_lines = 0;
			if (choice < 1 && choice > noun_arr_len)
			{
				for (int j=0;j<noun_arr_len ; j++)
				{
					k = print_info_lines(noun_arr[j], divide_lines + remaining_lines - k);
					count_lines += k;
				}
	
			}
			else
			{
				k = print_info_lines(noun_arr[choice - 1], total_lines);
			}
			return count_lines;
			}
			
			else 
			{
				return 0;
			}
	}
	long long int lines_printed = 0;
        lines_printed = print_info_lines(noun_ptr,total_lines);
        return lines_printed;
}

long long int print_info_lines(noun_tree_node* noun_ptr , long long int total_lines )
{
        if (total_lines <= 0)
	{
                return 0;
        }
        if (noun_ptr->src_heap && noun_ptr->src_heap->len >= total_lines)
	{
		long long int i;
                search_maxheap* sh = search_maxheap_copy(noun_ptr -> src_heap);
                for (i = 0; i < total_lines; i++)
		{
			printf("\n\n");
                        search_maxheap_node* nn = search_maxheap_delete(sh);

			// print noun name
                        printf("%s ",noun_ptr -> noun_name);

                        //print verb name
                        printf("%s ",nn->verb);

                        //print edge
                        edge_print(*(nn->e));
			count_printed++;
                }
		
                return total_lines;
        }

        traversal_queue* tq;
	tq = traversal_queue_init();
        long long int count_lines_printed = 0;
        long long int j = 0;
        long long int k = 0;
	if(noun_ptr->src_heap && noun_ptr->src_heap->len > 0) 
	{
        	tq = allocate_lines_search_maxheap(noun_ptr , noun_ptr-> src_heap , total_lines);
	}
	traversal_queue_node *temp = tq->front;
	while(temp != NULL) 
	{
		printf("\n\n");
                //print noun1 name
                printf("%s ",temp->noun_ptr -> noun_name);

                //print verb name
                printf("%s ",temp->verb_ptr);

                //print edge
                if(temp->e) 
		{
                        edge_print(*(temp->e));
                }
		temp = temp->next;
		count_printed++;
	}

	total_lines -= noun_ptr->src_heap->len;
        while (!traversal_queue_isempty(tq) && total_lines > 0)
	{
                temp = traversal_queue_dequeue(tq);
                temp->alloc_lines += j - k;
                count_lines_printed++;
                j = temp->alloc_lines;
                k = print_info_lines(temp->e->noun_ptr , j);
                total_lines -= k;

        }
	long long int k1 = 0;
        if (noun_ptr -> sub_heap && noun_ptr -> sub_heap->len >0 && total_lines > 0)
	{
                tq = allocate_lines_subclass_maxheap(noun_ptr-> sub_heap , total_lines);
                while (!traversal_queue_isempty(tq) && total_lines > 0 )
		{
                        traversal_queue_node* temp = traversal_queue_dequeue(tq);
                        temp->alloc_lines +=  j - k - k1;
			k = 0;
                        j = temp->alloc_lines;
                        k1 = print_info_lines(temp->noun_ptr , temp->alloc_lines);
                        count_lines_printed += k1;
                }

        }
        return count_lines_printed;
}


edge *copy_query_maxheap_node_into_edge(query_maxheap_node * qptr) 
{
	if(qptr == NULL) 
	{
		return NULL;
	}
        edge *e = (edge *) malloc(sizeof(edge));
        if(e) 
	{
                e->weight = qptr->weight;
                e->truth_bit = qptr->truth_bit;
                e->verb_descriptor = qptr->verb_descriptor;
                e->noun_ptr = qptr->noun_ptr;
                e->end_time = qptr->end_time;
        }
        return e;
}

long long int readline(FILE* fp, char line[], long long int size)
{
        long long int i=0;
        long long int ch;
        while (i<size-1 && (ch=fgetc(fp)) != '\n' && ch != -1)
	{
                line[i++]=ch;
        }
	if(i > 0 && line[i - 1] == 13) 
	{
        	line[i - 1]='\0';
		return i - 1;
	}
        line[i]='\0';
        return i;
}

knowledge_graph * knowledge_graph_init(void) 
{
        knowledge_graph *kg;
        kg = (knowledge_graph *) malloc(sizeof(knowledge_graph));
        if(kg) 
	{
                kg->main_noun_tree = NULL;
                kg->main_verb_tree = NULL;
                kg->main_desc_verb_tree = NULL;
        }
        return kg;
}

#define FIELDS 	12

/* tokenises the line stored in string "str" based on delimeter "delimiter"
 * returns an array of strings arr, containing "FIELDS" number of strings
 * for example, 
 * 	str 	  = "ab,c,d,,e"
 * 	delimiter = ','
 * then arr is
 * 	arr[0]->"ab"
 * 	arr[1]->"c"
 * 	arr[2]->"d"
 * 	arr[3]->""
 * 	arr[4]->"e"
 *
 * as seen above, if ",," (delimiter followed by delimiter) is encountered
 * then empty string will be placed in arr[i]
 *
 * no changes are made to str
 * memory for arr is malloced, and should be freed by user once used
 */
char **string_tokenise(char *str, char delimiter) 
{
	char **arr;		// array of strings to be returned
	char tmp[1024];		// stores tmp data

	long long int arr_index = 0;	// traverses arr
	long long int str_index = 0;	// traverses atr
	long long int tmp_index = 0;	// traverses tmp

	// malloc memory for array of strings
	arr = (char **) malloc (sizeof(char *) * FIELDS);
	
	/* while the string str doesn't end, 
	 * 	1. copy all characters till the next delimiter into tmp
	 * 	2. stringify tmp by inserting nul byte '\0' in the end
	 * 	3. copy that into arr[arr_index]
	 */

	while(str[str_index] != '\0') 
	{
		tmp_index = 0;
		// copy characters till the delimiter is encountered or str ends
		while(str[str_index] != '\0' && str[str_index] != delimiter) 
		{
			tmp[tmp_index] = str[str_index];
			tmp_index++;
			str_index++;
		}
		// increment str_index only if str has ended
		if(str[str_index] != '\0') 
		{
			str_index++;
		}

		// stringify tmp
		tmp[tmp_index] = '\0';


		// copy tmp into arr[arr_index]
		arr[arr_index] = (char *) malloc((sizeof(char) * tmp_index) + 1);
		strcpy(arr[arr_index], tmp);
		arr_index++;
	}
	return arr;
}

/* here below the various fields of the CSV file are defined
 * each field has its own index in the array of strings returned by string_tokeniser
 */


#define	FRONT_WEIGHT_INDEX	0
#define	INFERENCE_INDEX		1
#define	TRUTH_BIT_INDEX		2
#define	NOUN_1_INDEX		3
#define	NOUN_1_ID_INDEX		4
#define	VERB_INDEX		5
#define	VERB_DESCRIPTOR_INDEX	6
#define	NOUN_2_INDEX		7
#define	NOUN_2_ID_INDEX		8
#define	BACK_WEIGHT_INDEX	9
#define DEFINITION_INDEX	10
#define END_TIME_INDEX		11

/* converts a string array returned by string_tokeniser into line_data 
 * returns pointer to the data created
 * memory malloced must be freed by caller
 */
line_data* line_fetch_data_csv(char ** arr)
{
	
        line_data* temp_line= (line_data *) malloc (sizeof(line_data));

	// front weight
        temp_line->front_weight=atoi(arr[FRONT_WEIGHT_INDEX]);

	// inference
        temp_line->inference=atoi(arr[INFERENCE_INDEX]);

	// truth bit
        temp_line->truth_bit=atoi(arr[TRUTH_BIT_INDEX]);

	// noun1
        temp_line->noun1=(char *) malloc(strlen(arr[NOUN_1_INDEX])+1);
        strcpy(temp_line->noun1, arr[NOUN_1_INDEX]);

	// noun1_id
        temp_line->noun1_id=atoi(arr[NOUN_1_ID_INDEX]);

	// verb
        temp_line->verb= (char *) malloc (strlen(arr[VERB_INDEX])+1);
        strcpy(temp_line->verb, arr[VERB_INDEX]);

	// verb_descriptor
        temp_line->verb_descriptor= (char *) malloc (strlen(arr[VERB_DESCRIPTOR_INDEX])+1);
        strcpy(temp_line->verb_descriptor, arr[VERB_DESCRIPTOR_INDEX]);

	// noun2
        temp_line->noun2= (char *) malloc (strlen(arr[NOUN_2_INDEX])+1);
        strcpy(temp_line->noun2, arr[NOUN_2_INDEX]);
	
	// noun2_id
        temp_line->noun2_id=atoi(arr[NOUN_2_ID_INDEX]);

	// back weight
        temp_line->back_weight=atoi(arr[BACK_WEIGHT_INDEX]);
	
	// definition
        temp_line->definition= (char *) malloc (strlen(arr[DEFINITION_INDEX])+1);
        strcpy(temp_line->definition, arr[DEFINITION_INDEX]);
        
	//time to be inserted here
        //temp_line->end_time= (char *) malloc (strlen(arr[END_TIME_INDEX] + 1);
	//strcpy(temp_line->end_time, arr[END_TIME_INDEX]);

        return temp_line;
}



/* populate the knowledge graph from data stored in csv file
 * name of csv file is "filename"
 * 
 * one by one, line is read from file and inserted into knowledge graph
 * maximum line size is MAX_LINE_SIZE
 */

#define MAX_LINE_SIZE 2048

knowledge_graph * populate_csv(char * filename)
{
        FILE *fp = fopen(filename, "r");

	// fopen fails, return NULL
        if (fp == NULL)
	{
                perror("fopen failed");
                return NULL;
        }
	char **arr;			// array of strings returned by tokeniser
	char line[MAX_LINE_SIZE];	// line read from csv file
	long long int count;			// number of characters read from line
	line_data *l_data;		// data in srtcutred format
	
	// intialise knowledge_graph
        knowledge_graph * kg_ptr = knowledge_graph_init();
        while (1) 
	{
		// read a line from the file
                count = readline(fp,line, MAX_LINE_SIZE); 
		// printf("count = %lld\n", count);

		// if line is empty, then break
                if (count == 0)
		{
                        break;
               	}

		// tokenise the line on delimiter ','
		arr = string_tokenise(line, ',');

		// convert the array of strings into line_data format
                l_data=line_fetch_data_csv(arr);

		/*
		// print for testing
		if(l_data) 
		{
			print_line_data(*l_data);
		}
		*/
		// insert into knowledge graph
                knowledge_graph_insert(kg_ptr, *l_data);
        }
        return kg_ptr;
}

void print_str_without_context(char *str, char context_char) {
	int str_index = 0;
	int tmp_index = 0;
	char tmp[2048];
	while(str[str_index] != '\0') {
		while(str[str_index] != '\0' && str[str_index] != context_char) {
			tmp[tmp_index] = str[str_index];	
			tmp_index++;
			str_index++;
		}
		tmp[tmp_index] = '\0';
		if(str[str_index] == context_char) {
			str_index++;
			tmp_index = 0;
		}
		else {
			printf("%s", tmp);
		}
	}
	return;
}


// prints all data contained in line_data one below the other
void print_line_data(line_data data) 
{
	printf("front_weight = %lld\n", data.front_weight);
	printf("inference    = %lld\n", data.inference);
	printf("truth_bit    = %lld\n", data.truth_bit);
	printf("noun1 	     = %s\n", data.noun1);
	printf("noun1_id     = %lld\n", data.noun1_id);
	printf("verb         = %s\n", data.verb);
	printf("verb_desc    = %s\n", data.verb_descriptor);
	printf("noun2        = %s\n", data.noun2);
	printf("noun2_id     = %lld\n", data.noun2_id);
	printf("back_weight  = %lld\n", data.back_weight);
	printf("definition   = %s\n", data.definition);
	// printf("time = %s\n", data.time);
	return;
}

long long int query_maxheap_add_weights(query_maxheap* qh)
{
        if (qh == NULL || qh->len == 0)
	{
                return 0;
        }
        long long int i;
        long long int sum = 0;
        for (i = 0 ; i < qh->len ; i++)
	{
               sum += qh->arr[i].weight;
        }
        return sum;
}

query_maxheap * query_maxheap_copy(query_maxheap* hp)
{
        if (hp == NULL || hp->len == 0)
	{
                return NULL;
        }
        query_maxheap * qh = query_maxheap_init();
        long long int i;
	edge * e;
        for (i = 0;i < hp->len; i++)
	{
		e = copy_query_maxheap_node_into_edge(&hp->arr[i]);
		if (e != NULL)
		{
			query_maxheap_insert(qh , *e);
        	}
	}
        return qh;
}

void print_sentence(char * noun, char * verb, edge * e)
{
	printf("%s %s ", noun, verb);
	edge_print(*e);
	return;
}

long long int noun_verb_query(knowledge_graph* kg, char * input_noun, long long int input_noun_id, char * input_verb, long long int total_lines, int choice_flag)
{
	if (total_lines <= 0)
	{
		return 0;
	}
	noun_tree_node * noun;
	verb_tree_node * verb;
	noun = noun_tree_search(kg->main_noun_tree, input_noun, input_noun_id);
	if (!noun)
	{
		// if noun doesnt exists search for similar nodes
		long long int noun_arr_len=0;

		noun_tree_node** noun_arr = NULL;
		noun_tree_preorder_string_match_next_verb(kg->main_noun_tree , input_noun , input_noun_id , &noun_arr_len ,&noun_arr, input_verb);

		if(noun_arr_len > 0) 
		{
			printf("Did you mean : \n");
			for (long long int i=0;i<noun_arr_len;i++)
			{
				printf("%lld : %s\n",i + 1,noun_arr[i]->noun_name);
			}
			
			long long int choice;
			scanf("%lld",&choice);
		
			long long int divide_lines = (float)total_lines / (float)noun_arr_len;
			long long int remaining_lines = 0;
			long long int k=0;
			long long int count_lines = 0;
			if (choice < 1 && choice > noun_arr_len)
			{
				for (int j=0;j<noun_arr_len ; j++)
				{
					k = noun_verb_query(kg, noun_arr[j]->noun_name,noun_arr[j]->noun_id ,input_verb, divide_lines + remaining_lines - k, choice_flag);
					count_lines += k;
				}
	
			}
			else
			{
				count_lines = noun_verb_query(kg, noun_arr[choice-1]->noun_name,noun_arr[choice-1]->noun_id ,input_verb, total_lines, choice_flag);
			}
			return count_lines;
		}
		else 
		{
			return 0;
		}

		
	}
	
	verb = verb_tree_search(noun->next,input_verb);

	long long int verb_exists = 1;
        if (!verb)
	{
		verb_exists = 0;
 	}
	long long int j = 0;
	long long int k = 0;
	long long int i;
	long long int sum_weight ;
	traversal_queue * tq;
	traversal_queue_node* temp;
	query_maxheap * qh;
	long long int count_lines_printed = 0;
	if(verb_exists) {
		if (verb->qheap && verb->qheap->len > 0 && verb->qheap->len >= total_lines)
		{
			long long int i;
			edge * eptr;
			query_maxheap * qh = query_maxheap_copy(verb->qheap);
			for (i = 0; i < total_lines; i++)
			{
				query_maxheap_node * nn = query_maxheap_delete(qh);
				eptr = copy_query_maxheap_node_into_edge(nn);
				print_sentence(input_noun, input_verb, eptr);
				printf("\n\n");
			}
			return total_lines;
		}
		tq = traversal_queue_init();
		qh = query_maxheap_copy(verb->qheap);
		for (i=0;i<verb->qheap->len;i++)
		{
			query_maxheap_node * qnode;
			qnode = query_maxheap_delete(qh);
			if(qnode->truth_bit == 0) 
			{
				print_str_without_context(input_noun, '_');
				printf(" %s not %s ", input_verb, qnode->verb_descriptor);
				print_str_without_context(qnode->noun_ptr->noun_name, '_');
				printf("\n\n");
			}
			else 
			{
				print_str_without_context(input_noun, '_');
				printf(" %s %s ", input_verb, qnode->verb_descriptor);
				print_str_without_context(qnode->noun_ptr->noun_name, '_');
				printf("\n\n");
			}
			sum_weight = query_maxheap_add_weights(verb->qheap);
	       		temp = (traversal_queue_node * ) malloc (sizeof(traversal_queue_node));
			temp->alloc_lines = calc_line(qnode->weight, sum_weight, total_lines, verb->qheap->len);
			temp->verb_ptr = NULL;
			temp->e = copy_query_maxheap_node_into_edge(qnode);
			temp->noun_ptr=qnode->noun_ptr;
			count_lines_printed += 1;
			traversal_queue_enqueue(tq,temp);
		}
		total_lines -= verb->qheap->len;
		while (!traversal_queue_isempty(tq) && total_lines>0)
		{
			temp = traversal_queue_dequeue(tq);
			temp->alloc_lines += j-k;
			total_lines -= 1;
			count_lines_printed++;
			j = temp->alloc_lines;
			if(temp->e != NULL) 
			{
				k = print_info_lines(temp->e->noun_ptr, j);
			}
			total_lines -= k;
		}
	}
	subclass_maxheap *sh;
	j = 0;
	long long int p = 0;
	long long int ctr = 1;
	long long int choice;
	subclass_maxheap_node * sh_node;
	subclass_maxheap_node * choice_subheap_node;
	if(total_lines > 0 && noun->sub_heap && noun->sub_heap->len > 0) {
		sh = subclass_maxheap_copy(noun->sub_heap);
		if(choice_flag == 1) 
		{
			choice_flag = !choice_flag;
			subclass_maxheap *choice_subheap;
			choice_subheap = subclass_maxheap_init();
			while(sh->len > 0) 
			{
				sh_node = subclass_maxheap_delete(sh);
				if(verb_tree_search(sh_node->noun_ptr->next, input_verb)) 
				{
					subclass_maxheap_insert(choice_subheap, sh_node->noun_ptr, sh_node->weight);
					ctr++;
				}
			}
			if(choice_subheap->len > 1) 
			{
				subclass_maxheap * tmp_choice_subheap;
				tmp_choice_subheap = subclass_maxheap_copy(choice_subheap);
				printf("What are you interested in ??\n");
				ctr = 1;
				while(choice_subheap->len > 0) 
				{
					choice_subheap_node = subclass_maxheap_delete(choice_subheap);
					printf("%lld . %s\n", ctr, choice_subheap_node->noun_ptr->noun_name); 
					ctr++;
				}
				printf("\n");
				printf("Enter your choice : ");
				scanf("%lld", &choice);
				if(choice >= 1 && choice < ctr) 
				{	
					for(i = 1; i <= choice; i++) 
					{
						choice_subheap_node = subclass_maxheap_delete(tmp_choice_subheap);
					}
					sh = subclass_maxheap_init();
					subclass_maxheap_insert(sh, choice_subheap_node->noun_ptr, choice_subheap_node->weight);
	
				}
				else 
				{
					sh = subclass_maxheap_copy(noun->sub_heap);
				}
			}
			else if(choice_subheap->len == 1) 
			{
				sh_node = subclass_maxheap_delete(choice_subheap);
				subclass_maxheap_insert(sh, sh_node->noun_ptr, sh_node->weight);
			}
		}

		tq = allocate_lines_subclass_maxheap(sh, total_lines);
		while(!traversal_queue_isempty(tq)) 
		{
			temp = traversal_queue_dequeue(tq);
			temp->alloc_lines += j - p;
			j = temp->alloc_lines;
			p = noun_verb_query(kg, temp->noun_ptr->noun_name, temp->noun_ptr->noun_id, input_verb, temp->alloc_lines, choice_flag);
			count_lines_printed += p;
		}
		
	}
	return count_lines_printed;
}

long long int noun_verb_verb_desc_query(knowledge_graph* kg, char * input_noun, long long int input_noun_id, char * input_verb, char* input_verb_desc,long long int total_lines, long long int choice_flag)
{
	if (total_lines <= 0)
	{
		return 0;
	}
	noun_tree_node * noun;
	verb_tree_node * verb;
	noun = noun_tree_search(kg->main_noun_tree, input_noun, input_noun_id);
	if (!noun)
	{
		// if noun doesnt exists search for similar nodes
		long long int noun_arr_len=0;

		noun_tree_node** noun_arr = NULL;
		noun_tree_preorder_string_match_next_verb_verb_desc(kg->main_noun_tree , input_noun , input_noun_id , &noun_arr_len ,&noun_arr, input_verb, input_verb_desc);
		// printf("length : %lld\n",noun_arr_len);

		if(noun_arr_len > 0) 
		{
			printf("Did you mean : \n");
			for (long long int i=0;i<noun_arr_len;i++)
			{
				printf("%lld : %s\n",i + 1,noun_arr[i]->noun_name);
			}
			
			long long int choice;
			scanf("%lld",&choice);
			
			long long int divide_lines = (float)total_lines / (float)noun_arr_len;
			long long int remaining_lines = 0;
			long long int k=0;
			long long int count_lines = 0;
			if (choice < 1 && choice > noun_arr_len)
			{
				for (int j=0;j<noun_arr_len ; j++)
				{
					k = noun_verb_verb_desc_query(kg, noun_arr[j]->noun_name,noun_arr[j]->noun_id ,input_verb, input_verb_desc, divide_lines + remaining_lines - k, choice_flag);
					count_lines += k;
				}
	
			}
			else
			{
				count_lines = noun_verb_verb_desc_query(kg, noun_arr[choice-1]->noun_name,noun_arr[choice-1]->noun_id ,input_verb, input_verb_desc, total_lines, choice_flag);
			}
		}
		else {
			return 0;
		}

		
	}
	
	verb = verb_tree_search(noun->next,input_verb);
	long long int verb_not_there = 0;
        if (!verb)
	{
       		// printf("noun found, but relation doesn't exist for given verb");
		verb_not_there = 1;
 	}

	long long int i=0;
	long long int j = 0;
	long long int k = 0;
	traversal_queue * tq;
	traversal_queue_node* temp;
	long long int count_lines_printed = 0;

	edge* eptr;
	query_maxheap * qh = query_maxheap_init();
	if(verb_not_there == 0) 
	{
		for (i=0;i<verb->qheap->len ; i++)
		{
			if (string_cmp(verb->qheap->arr[i].verb_descriptor , input_verb_desc) == 0)
			{
				eptr = copy_query_maxheap_node_into_edge(&(verb->qheap->arr[i]));
				query_maxheap_insert(qh,*eptr);
			}
		}
	
		query_maxheap * qh_copy = query_maxheap_copy(qh);
		if (qh && qh->len > 0 && qh->len >= total_lines)
		{
			for (i = 0; i < total_lines; i++)
			{
				query_maxheap_node * nn = query_maxheap_delete(qh_copy);
				eptr = copy_query_maxheap_node_into_edge(nn);
				
				print_str_without_context(input_noun, '_');
				printf(" %s ", input_verb);
				if(eptr->truth_bit == 0) 
				{
					printf("not ");
				}
				printf("%s ", input_verb_desc);
				print_str_without_context(eptr->noun_ptr->noun_name, '_');
				printf("\n\n");
			}
			return total_lines;
		}
		long long int sum_weight = query_maxheap_add_weights(verb->qheap);
		tq = traversal_queue_init();
		for (i=0;i<qh->len;i++)
		{
			query_maxheap_node * qnode;
			qnode = query_maxheap_delete(qh);
				
			print_str_without_context(input_noun, '_');
			printf(" %s ", input_verb);
			if(eptr->truth_bit == 0) {
				printf("not ");
			}
			printf("%s ", input_verb_desc);
			print_str_without_context(eptr->noun_ptr->noun_name, '_');
			printf("\n\n");
		
			temp = (traversal_queue_node * ) malloc (sizeof(traversal_queue_node));
			temp->alloc_lines = calc_line(qnode->weight, sum_weight, total_lines, verb->qheap->len);
			temp->verb_ptr = NULL;
			temp->e = copy_query_maxheap_node_into_edge(qnode);
			temp->noun_ptr=qnode->noun_ptr;
			count_lines_printed += 1;
			traversal_queue_enqueue(tq,temp);
		}
		total_lines -= verb->qheap->len;
		while (!traversal_queue_isempty(tq) && total_lines>0)
		{
			temp = traversal_queue_dequeue(tq);
			temp->alloc_lines += j-k;
			total_lines -= 1;
			count_lines_printed++;
			j = temp->alloc_lines;
			if(temp->e != NULL) 
			{
				k = print_info_lines(temp->e->noun_ptr, j);
			}
			total_lines -= k;
		}
	}
	subclass_maxheap *sh;
	long long int p = 0;
	long long int ctr = 1;
	long long int choice;
	subclass_maxheap_node * sh_node;
	subclass_maxheap_node * choice_subheap_node;
	if(total_lines > 0 && noun->sub_heap && noun->sub_heap->len > 0) 
	{
		sh = subclass_maxheap_copy(noun->sub_heap);
		if(choice_flag == 1) 
		{
			choice_flag = !choice_flag;
			subclass_maxheap *choice_subheap;
			choice_subheap = subclass_maxheap_init();
			while(sh->len > 0) 
			{
				sh_node = subclass_maxheap_delete(sh);
				verb = verb_tree_search(sh_node->noun_ptr->next, input_verb);
				if(verb) 
				{
					for(i = 0; i < verb->qheap->len; i++) 
					{
						if(string_cmp(verb->qheap->arr[i].verb_descriptor, input_verb_desc) == 0) 
						{
							subclass_maxheap_insert(choice_subheap, sh_node->noun_ptr, sh_node->weight);
							ctr++;
						}
					}
				}
			}
			if(choice_subheap->len > 1) 
			{
				subclass_maxheap * tmp_choice_subheap;
				tmp_choice_subheap = subclass_maxheap_copy(choice_subheap);
				printf("What are you interested in ??\n");
				ctr = 1;
				while(choice_subheap->len > 0) 
				{
					choice_subheap_node = subclass_maxheap_delete(choice_subheap);
					printf("%lld . %s\n", ctr, choice_subheap_node->noun_ptr->noun_name); 
					ctr++;
				}
				printf("\n");
				printf("Enter your choice : ");
				scanf("%lld", &choice);
				if(choice >= 1 && choice < ctr) 
				{	
					for(i = 1; i <= choice; i++) 
					{
						choice_subheap_node = subclass_maxheap_delete(tmp_choice_subheap);
					}
					sh = subclass_maxheap_init();
					subclass_maxheap_insert(sh, choice_subheap_node->noun_ptr, choice_subheap_node->weight);
	
				}
				else 
				{
					sh = subclass_maxheap_copy(noun->sub_heap);
				}
			}
			
			else if(choice_subheap->len == 1) 
			{
				sh_node = subclass_maxheap_delete(choice_subheap);
				subclass_maxheap_insert(sh, sh_node->noun_ptr, sh_node->weight);
			}
		}

		tq = allocate_lines_subclass_maxheap(sh, total_lines);
		while(!traversal_queue_isempty(tq)) 
		{
			temp = traversal_queue_dequeue(tq);
			temp->alloc_lines += j - p;
			j = temp->alloc_lines;
			p = noun_verb_verb_desc_query(kg, temp->noun_ptr->noun_name, temp->noun_ptr->noun_id, input_verb, input_verb_desc, temp->alloc_lines, choice_flag);
			count_lines_printed += p;
		}
	}

	return count_lines_printed;
}

long long int query_verb_verb_desc_noun(knowledge_graph* kg, char * input_noun, long long int input_noun_id, char * input_verb, char* input_verb_desc,long long int total_lines, long long int choice_flag)
{
	if (total_lines <= 0)
	{
		return 0;
	}
	noun_tree_node * noun;
	verb_tree_node * verb;
	noun = noun_tree_search(kg->main_noun_tree, input_noun, input_noun_id);
	if (!noun)
	{
		//create function for percentage
		// printf("noun does't exist, can't find data\n");

		// if noun doesnt exists search for similar nodes
		long long int noun_arr_len=0;

		noun_tree_node** noun_arr = NULL;
		noun_tree_preorder_string_match_prev_verb_verb_desc(kg->main_noun_tree , input_noun , input_noun_id , &noun_arr_len ,&noun_arr, input_verb, input_verb_desc);
		// printf("length : %lld\n",noun_arr_len);

		if(noun_arr_len > 0) 
		{
		printf("Did you mean : \n");
		for (long long int i=0;i<noun_arr_len;i++)
		{
				
			printf("%lld : %s\n",i + 1,noun_arr[i]->noun_name);
		}
		
		long long int choice;
		scanf("%lld",&choice);
		
		long long int divide_lines = (float)total_lines / (float)noun_arr_len;
		long long int remaining_lines = 0;
		long long int k=0;
		long long int count_lines = 0;
		if (choice < 1 && choice > noun_arr_len)
		{
			for (int j=0;j<noun_arr_len ; j++)
			{
				k = query_verb_verb_desc_noun(kg, noun_arr[j]->noun_name,noun_arr[j]->noun_id ,input_verb, input_verb_desc, divide_lines + remaining_lines - k, choice_flag);
				count_lines += k;
			}

		}
		else
		{
			count_lines = query_verb_verb_desc_noun(kg, noun_arr[choice-1]->noun_name,noun_arr[choice-1]->noun_id ,input_verb, input_verb_desc, total_lines, choice_flag);
		}
		}
		else 
		{
			return 0;
		}

		
	}
	
	verb = verb_tree_search(noun->prev,input_verb);
	long long int verb_not_there = 0;
        if (!verb)
	{
		verb_not_there = 1;
 	}

	long long int i=0;
	long long int j = 0;
	long long int k = 0;
	traversal_queue * tq;
	traversal_queue_node* temp;
	long long int count_lines_printed = 0;

	edge* eptr;
	query_maxheap * qh = query_maxheap_init();
	if(verb_not_there == 0) 
	{
		for (i=0;i<verb->qheap->len ; i++)
		{
			if (string_cmp(verb->qheap->arr[i].verb_descriptor , input_verb_desc) == 0)
			{
				eptr = copy_query_maxheap_node_into_edge(&(verb->qheap->arr[i]));
				query_maxheap_insert(qh,*eptr);
			}
		}
	
		query_maxheap * qh_copy = query_maxheap_copy(qh);
		if (qh && qh->len > 0 && qh->len >= total_lines)
		{
			for (i = 0; i < total_lines; i++)
			{
				query_maxheap_node * nn = query_maxheap_delete(qh_copy);
				eptr = copy_query_maxheap_node_into_edge(nn);
				
				print_str_without_context(input_noun, '_');
				printf(" %s ", input_verb);
				if(eptr->truth_bit == 0) 
				{
					printf("not ");
				}
				printf("%s ", input_verb_desc);
				print_str_without_context(eptr->noun_ptr->noun_name, '_');
				printf("\n\n");
			}
			return total_lines;
		}
		long long int sum_weight = query_maxheap_add_weights(verb->qheap);
		tq = traversal_queue_init();
		for (i=0;i<qh->len;i++)
		{
				query_maxheap_node * qnode;
			qnode = query_maxheap_delete(qh);
				
			print_str_without_context(input_noun, '_');
			printf("%s ", input_verb);
			if(eptr->truth_bit == 0) 
			{
				printf("not ");
			}
			printf("%s ", input_verb_desc);
			print_str_without_context(eptr->noun_ptr->noun_name, '_');
			printf("\n\n");
		
			temp = (traversal_queue_node * ) malloc (sizeof(traversal_queue_node));
			temp->alloc_lines = calc_line(qnode->weight, sum_weight, total_lines, verb->qheap->len);
			temp->verb_ptr = NULL;
			temp->e = copy_query_maxheap_node_into_edge(qnode);
			temp->noun_ptr=qnode->noun_ptr;
			count_lines_printed += 1;
			traversal_queue_enqueue(tq,temp);
		}
		total_lines -= verb->qheap->len;
		while (!traversal_queue_isempty(tq) && total_lines>0)
		{
			temp = traversal_queue_dequeue(tq);
			temp->alloc_lines += j-k;
			total_lines -= 1;
			count_lines_printed++;
			j = temp->alloc_lines;
			if(temp->e != NULL) 
			{
				k = print_info_lines(temp->e->noun_ptr, j);
			}
			total_lines -= k;
		}
	}
	subclass_maxheap *sh;
	long long int p = 0;
	long long int ctr = 1;
	long long int choice;
	subclass_maxheap_node * sh_node;
	subclass_maxheap_node * choice_subheap_node;
	if(total_lines > 0 && noun->sub_heap && noun->sub_heap->len > 0) 
	{
		sh = subclass_maxheap_copy(noun->sub_heap);
		if(choice_flag == 1) 
		{
			choice_flag = !choice_flag;
			subclass_maxheap *choice_subheap;
			choice_subheap = subclass_maxheap_init();
			while(sh->len > 0) 
			{
				sh_node = subclass_maxheap_delete(sh);
				verb = verb_tree_search(sh_node->noun_ptr->prev, input_verb);
				if(verb) 
				{
					for(i = 0; i < verb->qheap->len; i++) 
					{
						if(string_cmp(verb->qheap->arr[i].verb_descriptor, input_verb_desc) == 0) 
						{
							subclass_maxheap_insert(choice_subheap, sh_node->noun_ptr, sh_node->weight);
							ctr++;
						}
					}
				}
			}
			if(choice_subheap->len > 1) 
			{
				subclass_maxheap * tmp_choice_subheap;
				tmp_choice_subheap = subclass_maxheap_copy(choice_subheap);
				printf("What are you interested in ??\n");
				ctr = 1;
				while(choice_subheap->len > 0) 
				{
					choice_subheap_node = subclass_maxheap_delete(choice_subheap);
					printf("%lld . %s\n", ctr, choice_subheap_node->noun_ptr->noun_name); 
					ctr++;
				}
				printf("\n");
				printf("Enter your choice : ");
				scanf("%lld", &choice);
				if(choice >= 1 && choice < ctr) 
				{	
					for(i = 1; i <= choice; i++) 
					{
						choice_subheap_node = subclass_maxheap_delete(tmp_choice_subheap);
					}
					sh = subclass_maxheap_init();
					subclass_maxheap_insert(sh, choice_subheap_node->noun_ptr, choice_subheap_node->weight);
	
				}
				else 
				{
					sh = subclass_maxheap_copy(noun->sub_heap);
				}
			}
			else if(choice_subheap->len == 1) 
			{
				sh_node = subclass_maxheap_delete(choice_subheap);
				subclass_maxheap_insert(sh, sh_node->noun_ptr, sh_node->weight);
			}
		}

		tq = allocate_lines_subclass_maxheap(sh, total_lines);
		while(!traversal_queue_isempty(tq)) 
		{
			temp = traversal_queue_dequeue(tq);
			temp->alloc_lines += j - p;
			j = temp->alloc_lines;
			p = query_verb_verb_desc_noun(kg, temp->noun_ptr->noun_name, temp->noun_ptr->noun_id, input_verb, input_verb_desc, temp->alloc_lines, choice_flag);
			count_lines_printed += p;
		}
	}

	return count_lines_printed;
}

long long int query_verb_noun(knowledge_graph* kg, char * input_noun, long long int input_noun_id, char * input_verb, long long int total_lines, int choice_flag)
{
	if (total_lines <= 0)
	{
		return 0;
	}
	noun_tree_node * noun;
	verb_tree_node * verb;
	noun = noun_tree_search(kg->main_noun_tree, input_noun, input_noun_id);
	if (!noun)
	{
		// if noun doesnt exists search for similar nodes
		long long int noun_arr_len=0;

		noun_tree_node** noun_arr = NULL;
		noun_tree_preorder_string_match_prev_verb(kg->main_noun_tree , input_noun , input_noun_id , &noun_arr_len ,&noun_arr, input_verb);

		if(noun_arr_len > 0) 
		{
			printf("Did you mean : \n");
			for (long long int i=0;i<noun_arr_len;i++)
			{
					
				printf("%lld : %s\n",i + 1,noun_arr[i]->noun_name);
			}
			
			long long int choice;
			scanf("%lld",&choice);
		
			long long int divide_lines = (float)total_lines / (float)noun_arr_len;
			long long int remaining_lines = 0;
			long long int k=0;
			long long int count_lines = 0;
			if (choice < 1 && choice > noun_arr_len)
		
			{
				for (int j=0;j<noun_arr_len ; j++)
				{
					k = query_verb_noun(kg, noun_arr[j]->noun_name,noun_arr[j]->noun_id ,input_verb, divide_lines + remaining_lines - k, choice_flag);
					count_lines += k;
				}
	
			}
			else
			{
				count_lines = query_verb_noun(kg, noun_arr[choice-1]->noun_name,noun_arr[choice-1]->noun_id ,input_verb, total_lines, choice_flag);
			}
		}
		else 
		{
			return 0;
		}
	}
	
	verb = verb_tree_search(noun->prev,input_verb);

	long long int verb_exists = 1;
        if (!verb)
	{
		verb_exists = 0;
 	}
	long long int j = 0;
	long long int k = 0;
	long long int i;
	long long int sum_weight ;
	traversal_queue * tq;
	traversal_queue_node* temp;
	query_maxheap * qh;
	long long int count_lines_printed = 0;
	if(verb_exists) 
	{
		if (verb->qheap && verb->qheap->len > 0 && verb->qheap->len >= total_lines)
		{
			long long int i;
			edge * eptr;
			query_maxheap * qh = query_maxheap_copy(verb->qheap);
			for (i = 0; i < total_lines; i++)
			{
				query_maxheap_node * nn = query_maxheap_delete(qh);
				eptr = copy_query_maxheap_node_into_edge(nn);
				print_sentence(input_noun, input_verb, eptr);
				printf("\n\n");
			}
			return total_lines;
		}
		tq = traversal_queue_init();
		qh = query_maxheap_copy(verb->qheap);
		for (i=0;i<verb->qheap->len;i++)
		{
			query_maxheap_node * qnode;
			qnode = query_maxheap_delete(qh);
			if(qnode->truth_bit == 0) 
			{
				print_str_without_context(input_noun, '_');
				printf(" %s not %s " , input_verb, qnode->verb_descriptor);
				print_str_without_context(qnode->noun_ptr->noun_name, '_');
				printf("\n\n");
			}
			else 
			{
				print_str_without_context(input_noun, '_');
				printf(" %s %s ", input_verb, qnode->verb_descriptor);
				print_str_without_context(qnode->noun_ptr->noun_name, '_');
				printf("\n\n");
			}
			sum_weight = query_maxheap_add_weights(verb->qheap);
	       		temp = (traversal_queue_node * ) malloc (sizeof(traversal_queue_node));
			temp->alloc_lines = calc_line(qnode->weight, sum_weight, total_lines, verb->qheap->len);
			temp->verb_ptr = NULL;
			temp->e = copy_query_maxheap_node_into_edge(qnode);
			temp->noun_ptr=qnode->noun_ptr;
			count_lines_printed += 1;
			traversal_queue_enqueue(tq,temp);
		}
		total_lines -= verb->qheap->len;
		while (!traversal_queue_isempty(tq) && total_lines > 0)
		{
			temp = traversal_queue_dequeue(tq);
			temp->alloc_lines += j-k;
			total_lines -= 1;
			count_lines_printed++;
			j = temp->alloc_lines;
			if(temp->e != NULL) 
			{
				k = print_info_lines(temp->e->noun_ptr, j);
			}
			total_lines -= k;
		}
	}
 	// long long int noun_verb_query(knowledge_graph* kg, char * input_noun, long long int input_noun_id, char * input_verb, long long int total_lines)
	subclass_maxheap *sh;
	j = 0;
	long long int p = 0;
	long long int ctr = 1;
	long long int choice;
	subclass_maxheap_node * sh_node;
	subclass_maxheap_node * choice_subheap_node;
	if(total_lines > 0 && noun->sub_heap && noun->sub_heap->len > 0) 
	{
		sh = subclass_maxheap_copy(noun->sub_heap);
		if(choice_flag == 1) 
		{
			choice_flag = !choice_flag;
			subclass_maxheap *choice_subheap;
			choice_subheap = subclass_maxheap_init();
			while(sh->len > 0) 
			{
				sh_node = subclass_maxheap_delete(sh);
				if(verb_tree_search(sh_node->noun_ptr->prev, input_verb)) 
				{
					subclass_maxheap_insert(choice_subheap, sh_node->noun_ptr, sh_node->weight);
					ctr++;
				}
			}
			if(choice_subheap->len > 1) 
			{
				subclass_maxheap * tmp_choice_subheap;
				tmp_choice_subheap = subclass_maxheap_copy(choice_subheap);
				printf("What are you interested in ??\n");
				ctr = 1;
				while(choice_subheap->len > 0) 
				{
					choice_subheap_node = subclass_maxheap_delete(choice_subheap);
					printf("%lld . %s\n", ctr, choice_subheap_node->noun_ptr->noun_name); 
					ctr++;
				}
				printf("\n");
				printf("Enter your choice : ");
				scanf("%lld", &choice);
				if(choice >= 1 && choice < ctr) 
				{	
					for(i = 1; i <= choice; i++) 
					{
						choice_subheap_node = subclass_maxheap_delete(tmp_choice_subheap);
					}
					sh = subclass_maxheap_init();
					subclass_maxheap_insert(sh, choice_subheap_node->noun_ptr, choice_subheap_node->weight);
	
				}
				else 
				{
					sh = subclass_maxheap_copy(noun->sub_heap);
				}
			}
		}

		tq = allocate_lines_subclass_maxheap(sh, total_lines);
		while(!traversal_queue_isempty(tq)) 
		{
			temp = traversal_queue_dequeue(tq);
			temp->alloc_lines += j - p;
			j = temp->alloc_lines;
			p = query_verb_noun(kg, temp->noun_ptr->noun_name, temp->noun_ptr->noun_id, input_verb, temp->alloc_lines, choice_flag);
			count_lines_printed += p;
		}
	}
	return count_lines_printed;
}


/* gets a line of atmost lim size from standard input
 * stores the line into buffer str, which is a character array
 * stringifies str in the end by appending nul byte to it
 */
long long int getaline(char str[], long long int lim) 
{
	long long int i = 0;	
	char ch;

	while(i < lim && (ch = getchar()) != '\n') 
	{
		str[i] = ch;
		i++;
	}
	str[i] = '\0';
	return i;
}

void query_recognizer(knowledge_graph *kg, char *str) 
{
	int str_index = 0;
	char word[1024];
	char noun[1024];
	char verb[1024];
	char temp[1024];
	int word_index = 0;
	int noun_index = 0;
	int temp_index = 0;
	int flag = 0;
	int question_flag = 0;
	word[word_index] = '\0';
	noun[noun_index] = '\0';
	temp[temp_index] = '\0';

	while(str[str_index] != '\0') 
	{


		while(str[str_index] != '\0' && str[str_index] != ' ') 
		{
			word[word_index] = str[str_index];
			str_index += 1;
			word_index += 1;
		}
		word[word_index] = '\0';
		if(str[str_index] == ' ') 
		{
			str_index += 1;
		}
		if(str[str_index] == '\0' && question_flag == 0 && flag == 0) 
		{
			//printf("concatenating %s with %s\n", noun, word);
			strcat(noun, word);
			/*
			printf("calling display_info_lines\n");
			printf("word = '%s'\n", word);
			printf("noun = '%s'\n", noun);
			printf("verb = '%s'\n", verb);
			*/
			display_info_lines(kg, noun, -5, INT_MAX);
			printf("\n");
			return;
		}

		if(strcmp(word, "?") == 0) 
		{
			question_flag = 1;
		}
		else 
		{
			// check if the word is a verb
			if(db_verb_tree_search(kg->main_verb_tree, word)) 
			{
				strcpy(verb, word);
				flag = 1;
				noun_index = 0;
				while(noun[noun_index] != '\0') 
				{
					noun_index += 1;
				}
				if(noun_index > 0) 
				{
					noun[noun_index - 1] = '\0';
				}
				if(flag != 0) 
				{
					strcpy(temp, word);
					word[word_index] = '\0';
					word_index = 0;
					// check for verb_desc noun or only noun	
					while(str[str_index] != '\0') 
					{
						while(str[str_index] != '\0' && str[str_index] != ' ') 
						{
							word[word_index] = str[str_index];
							str_index += 1;
							word_index += 1;
						}
						if(str[str_index] == ' ') 
						{
							str_index += 1;
						}
						word[word_index] = '\0';
						if(str[str_index] == '\0') 
						{
							// this means that the entire input string is complete
							// and there is no verb_desc
							// either noun verb ?
							// or	  ? verb noun	  
							if(strcmp(word, "?") == 0) 
							{
								/*
								printf("calling noun_verb_query(noun, verb)\n");
								printf("word = '%s'\n", word);
								printf("noun = '%s'\n", noun);
								printf("verb = '%s'\n", verb);
								*/
								noun_verb_query(kg, noun, -5, verb, INT_MAX, 1);
								return;
							}
							else 
							{
								/*
								printf("calling query_verb_noun(word, verb)\n");
								printf("word = '%s'\n", word);
								printf("noun = '%s'\n", noun);
								printf("verb = '%s'\n", verb);
								*/
								query_verb_noun(kg, word, -5, verb, INT_MAX, 1);
								return;
							}
						}
						// printf("searching for '%s' in verb_desc_tree\n", word);
						if(db_desc_verb_tree_search(kg->main_desc_verb_tree, word)) 
						{
							if(question_flag != 0) 
							{
								noun_index = 0;
								while(str[str_index] != '\0') 
								{
									noun[noun_index] = str[str_index];
									noun_index += 1;
									str_index += 1;
								}
								noun[noun_index] = '\0';
								/*
								printf("calling query_verb_verb_desc_noun\n");
								printf("word = '%s'\n", word);
								printf("noun = '%s'\n", noun);
								printf("verb = '%s'\n", verb);
								*/
								query_verb_verb_desc_noun(kg, noun, -5, verb, word, INT_MAX, 1);
								return;
							}
							else 
							{
								/*
								printf("calling noun_verb_verb_desc_query\n");
								printf("word = '%s'\n", word);
								printf("noun = '%s'\n", noun);
								printf("verb = '%s'\n", verb);
								*/
								noun_verb_verb_desc_query(kg, noun, -5, verb, word, INT_MAX, 1); 
								return;
							}
								
						}

						word[word_index] = ' ';
						word_index += 1;
					
					}
				}
			}
			else if (strcmp(word, "") != 0) 
			{
				if(question_flag == 1) 
				{
					return;
				}
				strcat(noun, word);
				strcat(noun, " ");
			}
		}
		word_index = 0;
		word[word_index] = '\0';
	}
	return;
}

int main(int argc, char * argv[])
{
        knowledge_graph * kg = NULL;
	kg = knowledge_graph_init();
        kg = populate_csv(argv[1]);
	if(kg == NULL) 
	{
		printf("knowlegde graph not created properly\n");
		return 1;
	}

	/*
	printf("\nmain_noun_trees of knowledge graph\n\n");
	printf("noun_tree\n");
	noun_tree_inorder(kg->main_noun_tree);
	printf("db_verb_tree\n");
	db_verb_tree_inorder(kg->main_verb_tree);
	printf("db_desc_verb_tree\n");
	db_desc_verb_tree_inorder(kg->main_desc_verb_tree);
	printf("\n\n");
	*/

	// now query the graph
        char str[1024];
	// scanf("%s", str);	
	while(1) 
	{
		printf("\n");
		printf("How may I help you ??\n\n");
		getaline(str, 1024);
		if(string_cmp(str, "end") == 0) 
		{
			break;
		}
		query_recognizer(kg, str);
		printf("\n");
	}
	return 0;
}
