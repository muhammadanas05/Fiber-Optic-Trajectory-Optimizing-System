//C++ Code to generate random dataset

#include <bits/stdc++.h>
#include <fstream>
#define nodes 100
#define weight 10000

using namespace std;

int main()
{
	fstream myfile, myfile2;
	
	myfile.open("file.txt", ios::in);
	myfile2.open("file2.txt", ios::out);
	
	int vertices, x, y, z;
	myfile >> vertices;
	myfile2 << vertices;
	
	while(!(myfile.eof()))
	{
		myfile2 << "\n";
		
		myfile >> x >> y >> z;
		myfile2 << x << " " << y << " ";
		do
		{
			z = rand() % weight;
		}while(z < 1000);
		myfile2 << z;
	}
	
	return 0;
}
