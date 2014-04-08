#ifndef reroot_h
#define reroot_h

typedef struct _node
{
	struct _node * par;
	struct _node * lc;
	struct _node * rc;
	char cut;
	double width;
	double height;
}Node;

typedef struct _stack
{
	struct _stack * next;
	Node * n;
}Stack;

typedef struct _coord
{
	double x;
	double y;
}Coord;

Node * Load_File(char * Filename); //store nodes in array
Stack * Stack_push(Stack * s, Node * t);
Stack * Stack_pop(Stack * s);
void Preorder(Node * head);
void Inorder(Node * head);
void Postorder(Node * head);
//void Save_File(char * Filename, Node * arr, Coord * crd, int num_b);
#endif
