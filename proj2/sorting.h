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
Node * assemble_List(List * list, int Size);
Node * insert_Node(Node * head, Node * n);
void Destroy_List(Node * head);
//int Print_Seq(char * Filename, long Size);
//#endif
