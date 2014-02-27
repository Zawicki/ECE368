//#ifndef sorting_h
//#define sorting_h

typedef struct _node
{
	long value;
	struct _node * next;
}Node;

typedef struct _list
{
	Node * node;
	struct _list * next;
}List;

Node * Create_Node(long val);
Node * Load_File(char * Filename);
int Save_File(char * Filename, Node * head);
int * Gen_K_Seq(int * arr_Size, long Size); //Generates the k sequence
Node * Shell_Sort(Node * head);
void Destroy_List(Node * head);
Node * Find_elem(Node * head, int i);
//int Print_Seq(char * Filename, long Size);
//#endif
