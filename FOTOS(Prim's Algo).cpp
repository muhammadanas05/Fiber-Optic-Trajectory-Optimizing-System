#include <bits/stdc++.h>
#include <conio.h>
#include <windows.h>
#include <iomanip>
#include <functional>

using namespace std;

void gotoxy(int x, int y)  //Function to move Console Position
{
    static HANDLE h = NULL;
    if(!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x, y };
    SetConsoleCursorPosition(h,c);
}

class Log_Sign //Login and Signup
{
	private:
	    string UserName;
	    string Password = "";
	    string User;
	    string Pass ;
	public:
	    Log_Sign() {	}		// DEFAULT CONSTRUCTOR
	
	
	    bool Login() //Login Func
	    {
	
	        int count=0;
			static int  temp=1;
	        system("CLS");
	        gotoxy(15,2);
	        cout << "Enter User Name: ";
	        fflush(stdin);
	        getline(cin, UserName);
			
			gotoxy(15,3);
	        cout<<"Enter User Password: ";
	        fflush(stdin);
	        //CODE FOR HIDING CHARACTERS OF PASSWORD ON CONSOLE
	        char ch;
	        ch = _getch();
	        Password.clear();
	        while(ch != 13) //character 13 is enter
	        {
	            Password.push_back(ch);
	            cout << '*';
	            ch = _getch();
	        }
	        
	        ifstream myfile("userData.txt");
	
	        while(myfile>>User>>Pass)
	        {
	
	            if (User == UserName && Pass == Password)
	            {
	                count=1;
	            }
	        }
	        myfile.close();
	        if (count==1)
	        {
	            cout << "\nLOGIN APPROVED" << endl;
	            system("PAUSE");
	            return true;
	
	        }
	        else
	        {
	            temp +=1;
	            if(temp>3) 		// ONLY 3 TIMES PASSWORD CAN BE ENTERED!
	            {
					temp = 1;
	                return false;
	            }
	            else
	            {
	                cout<<"\nInvalid Input!!\n  Try Again." << endl;
	                system("PAUSE");
					system("CLS");
	            }
	        }
	    }	// end of "LOGIN Func."
	
	    void Signup() //Register Func
	    {
	
	        system("CLS");
	        gotoxy(40,8);
	        cout << "\nEnter User Name: " ;
	        cin>>UserName;
	        cout << "\nEnter User Password: " ;
	        fflush(stdin);
	        char ch;
	        ch = _getch();
	        while(ch != 13) //character 13 is enter
	        {
	            Password.push_back(ch);
	            cout << '*';
	            ch = _getch();
	        }
	
	        ofstream file("userData.txt",ios::app);
	
	        file<<UserName<<" "<<Password<<endl;
	
	        file.close();
			
	        cout<<"\nRegistration Successful"<< endl;
	        system("PAUSE");
	
	    }	// end of "SIGNUP Func."

};

struct listNode //Linked-List Node
{
	int target, weight;
	listNode * next;
	listNode(int t, int w) { target = t, weight = w, next = NULL; }
	~listNode() { next = NULL; }
};

class List //Linked-List
{
	private:
		listNode *head;
	public:
		List() { head = NULL; }
		void insertAtStart(int, int);  //inserts listNode at start of List for quick insertion
		listNode* getHead() { return head; }
		~List();
};

void List::insertAtStart(int x, int w)
{
	listNode * n = new listNode(x, w);
	if (!head)
		head = n;
	else
	{
		listNode * aux = head;
		n->next = aux;
		head = n;
	}
}
List::~List()
{
	while (head)
	{
		listNode * n = head->next;
		delete head;
		head = n;
	}
}

struct heapItem //Heap Node
{
	int value, key;
	heapItem(int v, int k) { value = v, key = k; }
};

struct minHeap //Minimum Heap
{
	int size, capacity, *position; //var 'position' will be used in 3 functions as a helper
								   //to get current index of node in minHeap
	heapItem** heapArray;
	minHeap(int);
	void swapHeapItem(heapItem **, heapItem **);
	void minHeapify(int);
	heapItem* extractMin();
	void decreaseKey(int v, int k); //decreases key value 'k' of vertex
	~minHeap();
};

minHeap::minHeap(int c) //default constructor
{
	capacity = c, size = 0, position = new int[capacity];
	heapArray = new heapItem*[capacity];
	for (int i = 0; i < capacity; i++)
		heapArray[i] = NULL;
}
void minHeap::swapHeapItem(heapItem** x, heapItem** y) // swap heap items
{
	heapItem* aux = *x;
	*x = *y;
	*y = aux;
}
void minHeap::minHeapify(int i) // heapify the data structure
{
	int index = i, l = 2 * i + 1, r = 2 * i + 2; //'l' represents left index
												 //'r' reqresents right index
	if (l < size &&	heapArray[l]->key < heapArray[index]->key)
		index = l;
	if (r < size &&	heapArray[r]->key < heapArray[index]->key)
		index = r;
	if (index != i)
	{
		heapItem * indexItem = heapArray[index], *iItem = heapArray[i];
		//swapping positions
		position[indexItem->value] = i;
		position[iItem->value] = index;
		//
		//swapping nodes
		swapHeapItem(&heapArray[index], &heapArray[i]);
		minHeapify(index);
	}
}
heapItem* minHeap::extractMin() // extracting top node of heap
{
	if (size == 0)
		return NULL;
	heapItem * h1 = heapArray[0]; //storing 'root' node in 'h1'
	//replacing 'h1' with 'h2'
	heapItem * h2 = heapArray[size - 1];
	heapArray[0] = h2;
	//
	//updating position of h2
	position[h1->value] = size - 1;
	position[h2->value] = 0;
	//
	--size;
	minHeapify(0);
	return h1;
}
void minHeap::decreaseKey(int v, int k) 
{
	int index = position[v];
	heapArray[index]->key = k;
	while (index && heapArray[index]->key < heapArray[(index - 1) / 2]->key)
	{
		//swapping current node with its parent node
		position[heapArray[index]->value] = (index - 1) / 2;
		position[heapArray[(index - 1) / 2]->value] = index;
		swapHeapItem(&heapArray[index], &heapArray[(index - 1) / 2]);
		//
		index = (index - 1) / 2; // to move to parent index
	}
}
minHeap::~minHeap()
{
	for (int i = 0; i < capacity; i++)
	{
		if (heapArray[i])
			delete heapArray[i];
	}
	delete[] heapArray;
}

class Graph //Graph Data Structure
{
		int numOfVertices;
		List *adjList;
	public:
		Graph(int n) { numOfVertices = n, adjList = new List[numOfVertices]; }
		void insertEdge(int, int, int); //makes 'link' from both vertices
										//to each other
		int getNumOfVertices() { return numOfVertices; }
		int * make_MST_via_PrimAlgo();
		int getWeightOfEdge(int x, int y); //returns weight of edge xy
		void printMST(int []); //prints all edges of MST along with their weight
		int getMSTWeight(int []); //returns total weight of all edges in MST
		void printGraph(); 	//to print graph
		~Graph() { delete[] adjList; }
};

void Graph::insertEdge(int x, int y, int w)
{
	adjList[y].insertAtStart(x, w);
	adjList[x].insertAtStart(y, w);
}

int* Graph::make_MST_via_PrimAlgo() //Implementation of Prim's Algo to make MST
{
	int* MST = new int[numOfVertices];
	int* k = new int[numOfVertices]; //key values for picking minimum weight edge in cut
	minHeap* h = new minHeap(numOfVertices);
	//initializing minHeap with all vertices
	
	for (int i = 1; i < numOfVertices; i++)
	{
		MST[i] = 0;
		k[i] = INT_MAX;
		h->heapArray[i] = new heapItem(i, k[i]);
		h->position[i] = i;
	}
	//
	k[0] = 0; // making key value of 0th vertex '0' so it's extracted first
	h->heapArray[0] = new heapItem(0, 0);
	h->position[0] = 0;
	h->size = numOfVertices;
	while (h->size != 0)
	{
		heapItem* min = h->extractMin();
		int num = min->value;
		//traversing through all adjacent vertices of 'num' (extracted vertex)
		//and update their key values
		listNode* aux = adjList[num].getHead();
		while (aux)
		{
			int t = aux->target;
			if (h->position[t] < h->size && aux->weight < k[t])
			{
				k[t] = aux->weight;
				MST[t] = num;
				h->decreaseKey(t, k[t]);
			}
			aux = aux->next;
		}
	}
	return MST;
}
int Graph::getWeightOfEdge(int x, int y)
{
	listNode * n = adjList[x].getHead();
	while (n)
	{
		if (n->target == y)
			return n->weight;
		n = n->next;
	}
}

void Graph::printGraph() //Func to print graph
{
	listNode* temp;
	for(int i = 0 ; i < numOfVertices; i++)
	{
		temp = adjList[i].getHead();
		cout<<"\nNode "<<"("<<i<<")";
		
		while(temp != NULL)
		{
			cout<<"---"<<"("<<temp->target<<", "<<temp->weight<<")";
			temp=temp->next;
		}
		cout<<endl;
	}
	
}

void Graph::printMST(int MST[]) //Func to print MST
{
	if (MST)
	{
		cout << "\nEdge           Weight\n";
		for (int i = 1; i < numOfVertices; ++i)
		{
			cout << MST[i] << " - " << i;
			//for symmetric spacing between edge & weight
			int x = 0;
			if (MST[i] > 9)
				x = 1;
			else if (MST[i] > 99)
				x = 2;
			else if (MST[i] > 999)
				x = 3;
			if (i > 9)
				x += 1;
			else if (i > 99)
				x += 2;
			else if (i > 999)
				x += 3;
			for (int j = 0; j < 12 - x; j++)
				cout << " ";
			//
			cout << getWeightOfEdge(MST[i], i) << endl;
		}
		cout << endl;
	}
	else
		cout << "\n<ERROR! NO MST HAS BEEN MADE YET>\n\n";
}
int Graph::getMSTWeight(int MST[])
{
	int n = -1;
	if (MST)
	{
		n = 0;
		for (int i = 1; i < numOfVertices; i++)
			n += getWeightOfEdge(MST[i], i);	
	}
	return n;
}

int printMenu() //Main Menu
{
	int n = 0;
	cout << "                                      -----------------\n"
		<< "                                      | PROJECT FOTOS |\n"
		<< "                                      -----------------\n"
		<< "---------------------------------------------------------------------------------------------\n"
		<< "|                          FIBER OPTIC TRAJECTORY OPTIMIZING SYSTEM                         |\n"
		<< "---------------------------------------------------------------------------------------------\n"
		<< "| 0 = EXIT PROGRAM                                                                          |\n"
		<< "| 1 = MAKE MST VIA PRIM'S ALGORITHM                                                         |\n"
		<< "| 2 = PRINT MST                                                                             |\n"
		<< "| 3 = CALCULATE MST WEIGHT                                                              	|\n"  
		<< "| 4 = PRINT GRAPH																			|\n"
		<< "---------------------------------------------------------------------------------------------\n\n"
		<< "Enter your choice: ";
	cin >> n;
	while (n < 0 || n > 4)
	{
		cout << "\n<ERROR! INVALID INPUT>\nEnter again: ";
		cin >> n;
	}
	return n;
}

void Intro(void) //Introduction
{
	system("CLS");
	string p2="|FIBER OPTIC TRAJECTORY OPTIMIZING SYSTEM|";
	gotoxy(50, 2);

	cout<<"\n-------------------------------------------------------------------------------------------------------------------";
	gotoxy(40,4);
	for(int i=0; i<p2.size(); i++)
	{
	Sleep(20);
	cout<<p2[i];
	}
	cout<<"\n-------------------------------------------------------------------------------------------------------------------";




	string S="Muhammad Anas ";

	gotoxy(42,11);

	for(int i=0; i<S.size(); i++)
	{

	Sleep(50);
	cout<<S[i];
	}

}

int mainMenu(void) //Login/Signup Menu
    {
        int choice2;
        int success;
        gotoxy(60, 15);
        cout<<"\n1. Login\n2.Register\n";
        cout<<"Entire desired option: ";
        cin>>choice2;
        Log_Sign A;
        switch (choice2)
        {
        case 1:
x:
            success =  A.Login();
            break;
        case 2:
            A.Signup();
            goto x;
            break;
        default:
            cout<<"\nInvalid Data Entry!!";
            exit(EXIT_FAILURE);
            break;
        }
		return success;	
}
int main(void) //Main Procedure
{
	system("color f4");
	Intro();
z:
	if(mainMenu())
	{

		ifstream fin;
		fin.open("file.txt", ios::in);
		if (!fin)
		{
			cout << "\n<ERROR! UNABLE TO OPEN FILE '" << "'>\n"
				<< "File is missing from default/given path.\n\n";
			exit(EXIT_FAILURE);
		}
		cout << endl;
		int nOfNodes = 0;
		fin >> nOfNodes;
		Graph *G = new Graph(nOfNodes);
		int x = 0, y = 0, w = 0;
		while (!fin.eof())
		{
			fin >> x >> y >> w;
			cout << "Adding edge '" << x << " - " << y << "' with weight " << w << "...\n";
			G->insertEdge(x, y, w);
		}
		fin.close();
		cout << "\nAll edges has been added to the graph successfully.\n\n";
		system("pause");
		system("cls");
		int * mst = NULL;
		int m = printMenu();
		while (m != 0)
		{
			if (m == 1)
			{
				mst = G->make_MST_via_PrimAlgo();
				cout << "\nMST has been made successfully via Prim's Algorithm.\n\n";
			}
			else if (m == 2)
				G->printMST(mst);
			else if(m == 3)
			{
				if (mst)
					cout << "\nTotal weight of MST: " << G->getMSTWeight(mst) << endl << endl;
					
				else if(G->getMSTWeight(mst) == -1)
					cout << "\n<ERROR! NO MST HAS BEEN MADE YET>\n\n";
			}
			else
			{
				G->printGraph();
			}
			system("pause");
			system("cls");
			m = printMenu();
		}
		delete G;
	}
	else
	{
		system("CLS");
		goto z;
	}
	system("CLS");
    string p1="|DATA STRUCTURE AND ALGORITHMS|";
    string p2="|FIBER OPTIC TRAJECTORY OPTIMIZING SYSTEM|";
    gotoxy(50, 2);
	for(int i=0; i<p1.size();i++){
		Sleep(15);
		cout<<p1[i];
	}
	cout<<"\n-------------------------------------------------------------------------------------------------------------------";
	gotoxy(46,4);
	for(int i=0; i<p2.size(); i++)
	{
		Sleep(20);
		cout<<p2[i];
	}
	cout<<"\n-------------------------------------------------------------------------------------------------------------------";
	
	
    string S="   THANK YOU! ";
    
	gotoxy(42,17);

    for(int i=0; i<S.size(); i++)
    {

        Sleep(50);
        cout<<S[i];
    }

	return 0;
}
