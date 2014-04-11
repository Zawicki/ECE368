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
	double x;
	double y;
}Node;

typedef struct _stack
{
	struct _stack * next;
	Node * n;
}Stack;

Node * Load_File(char * Filename); //store nodes in array
Stack * Stack_push(Stack * s, Node * t);
Stack * Stack_pop(Stack * s);
void Find_Area(Node * h);
//void Find_YCoords(Node * h, double * y_prev);
//void Find_XCoords(Node * h, double * x_new);
void Find_Coords(Node * h, double * x_new, double * y_prev);
void Preorder(Node * head);
void Inorder(Node * head);
void Postorder(Node * head, double * x, double * y);
void Save_File(FILE * f, Node * h);
#endif
