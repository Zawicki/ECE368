#ifndef sorting_h
#define sorting_h

typedef struct _node
{
	int par;
	int lc;
	int rc;
	char cut;
	double width;
	double height;
}Node;

Node * Load_File(char * Filename, int * num_b, int * num_n); //store nodes in array
void Pack(Node * arr, int size);
void Preorder(Node * arr, int ind);
void Inorder(Node * arr, int ind);
void Postorder(Node * size, int ind);
void Delete_Nodes(Node * arr, int size);
void Save_File(char * Filename, Node * arr, int num_b, int size);
#endif
