/*	Angela Chen 
	CIS350-Program1

	Description: The program allows users to input a series of 
	graphs to generate the order of the minimum maximum distance 
	of the set of vertices of that graph.
*/

#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>

using namespace std;
class Graph
{
	public:
		Graph (int size)		// creates an empty graph with size vertices
		{	graph.resize(size);	}
		void fillGraph();		// fills in the graph from cin
		void printGraph();		// prints the graph (for debugging only)
		int maxCover( vector<char> order); // returns the maxCover for the order
		int cover( char vertex,vector<char> order);		// returns the cover size for vertex
		void minMaxCover();			//generates the permutations and prints the minimum max cover order of graph
	private:
		vector <vector <char> > graph;
};
//================================MAIN FUNCTION==============================//
int main()
{
	int numOfGraphs;
	int vertices;

	cin>>numOfGraphs;		//number of graphs
	for(int i=0; i<numOfGraphs; i++)
	{
		cin>>vertices;		//number of vertices
		Graph input(vertices);
		input.fillGraph();
//		input.printGraph();
		input.minMaxCover();
		cout<<endl;
	} 

	return 0;
}
//============================================================================//

//================================Class Graph member functions=================//
/*	Description: Takes the user's input and fills it in 
*				the 2D vectors appropriately
*	Pre: Appropriate graph inputs
*	Post: Filled graph
*/
void Graph::fillGraph()
{
	int degreeOfVertex;
	char letter;
	char adjletter;
	char num;

	for(int i=0; i<graph.size();i++)
	{
		cin>>letter;
		graph[i].push_back(letter);
		cin>>degreeOfVertex;		//number of connections
		num='0'+degreeOfVertex;
		graph[i].push_back(num);

		for (int j=0; j<degreeOfVertex; j++)
		{
			cin>>adjletter;			//adjacent letter
			graph[i].push_back(adjletter);
		}
	}
}
/*	Description: Prints out the contents of graph
*	Pre: Filled graph
*	Post: Graph output
*/
void Graph::printGraph()
{
	for (int i=0; i<graph.size(); i++)
	{
		cout<<endl;
		for(int j=0; j<graph[i].size(); j++)
			cout<<graph[i][j]<<" ";
	}
	cout<<endl;
}
/*	Description: Generates permutation, calls other functions to 
*				calculate, and prints out the min max order
*	Pre: Filled graph
*	Post: Min max order and distance
*/
void Graph::minMaxCover()
{
	vector<char> minMaxOrder;
	vector<char> order;
	int minMax;
	int cover;
	int counter;

	for(int i=0; i<graph.size();i++)
	{
		order.push_back(graph[i][0]);
	}
	sort(order.begin(),order.end());
	minMax=order.size();
	minMaxOrder.resize(order.size());		
	
	do			
	{
		cover=maxCover(order);
		if (cover<minMax)
		{
			minMax=cover;
			minMaxOrder=order;
		}
	}while(next_permutation(order.begin(),order.end()));

	for (int i=0; i<minMaxOrder.size(); i++)		//print order
	{
		cout<<minMaxOrder[i]<<" ";
	}
	cout<<minMax;
}
/*	Description: Calculates the maximum distance of that particular vertex
*	Pre: Vertex and permutation
*	Post: Max cover for the vertex
*/
int Graph::cover(char vertex,vector<char> order)
{
	int coverSize;
	int vertexPos;		//vertex Position
	int adjVertPos;		//adjacent vertex position
	int vertexRow;
	int maxCovSize=0;	//maximum cover for this particular vertex
	char adjVertex;
	for (int k=0; k<order.size();k++)
	{
			if(order[k]==vertex)
			{
				vertexPos=k;
				break;
			}
	}

	for (int row=0;row<graph.size(); row++)
		if (graph[row][0]==vertex)
		{
			vertexRow=row;
		}
	for (int col=2; col<graph[vertexRow].size(); col++)
	{
		adjVertex=graph[vertexRow][col];
		for (int i=0; i<order.size();i++)
		{
			if(order[i]==adjVertex)
			{
				adjVertPos=i;
				break;
			}
		}
		coverSize=abs(adjVertPos-vertexPos);
		if(coverSize>maxCovSize)
			maxCovSize=coverSize;
	}

	return maxCovSize;		
}
/*	Description: Calculates max cover for this particular permutation
*	Pre: A permutation
*	Post: Maximum cover for permutation
*/
int Graph::maxCover( vector<char> order)
{
	int max=0;		//initialize the maximum cover
	int current;	//current cover
	for (int i=0;i<order.size();i++)
	{
		current =cover(order[i],order);
		if (current>max)
			max=current;
	}																	
	return max;
}