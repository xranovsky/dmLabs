#include "utils/Graph.h"
#include "ChinesePostman.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

pair< Graph, vector<double> > ReadWeightedGraph(string filename)
{
	ifstream file;
	int size;

	file.open(filename);

	file >> size;

	Graph G(size);
	vector<double> cost(1000);

	int weight;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			file >> weight;
			if (weight != 0)
			{
				G.AddEdge(i, j);
				cost[G.GetEdgeIndex(i, j)] = weight;
			}
		}
	}

	file.close();
	return make_pair(G, cost);
}

int main(int argc, char* argv[])
{

	Graph G;
	vector<double> cost;

	pair< Graph, vector<double> > p = ReadWeightedGraph("input.txt");
	G = p.first;
	cost = p.second;

	pair< list<int>, double > sol = ChinesePostman(G, cost);

	cout << "Solution cost: " << sol.second << endl;

	list<int> s = sol.first;

	cout << "Solution:" << endl;
	for (list<int>::iterator it = s.begin(); it != s.end(); it++)
		cout << *it << " ";
	cout << endl;

	return 0;
}


