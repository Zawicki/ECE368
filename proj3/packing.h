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

typedef struct _coord
{
	double x;
	double y;
}Coord;

Node * Load_File(char * Filename, int * num_b, int * num_n); //store nodes in array
Coord * Pack(Node * arr, int size, int num_b, double * x_tot, double * y_tot);
void Find_Coords(Coord * crd, Node * arr, int ind, double * x_tot, double * y_tot);
void Preorder(Node * arr, int ind);
void Inorder(Node * arr, int ind);
void Postorder(Node * size, int ind);
void Save_File(char * Filename, Node * arr, Coord * crd, int num_b);
#endif
