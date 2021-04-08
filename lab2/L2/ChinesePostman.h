#include "utils/Dijkstra.h"
#include "utils/Matching.h"
#include "utils/Graph.h"

bool Connected(const Graph& G)
{
	vector<bool> visited(G.GetNumVertices(), false);
	list<int> L;

	int n = 0;
	L.push_back(0);
	while (not L.empty())
	{
		int u = L.back();
		L.pop_back();
		if (visited[u]) continue;

		visited[u] = true;
		n++;

		for (list<int>::const_iterator it = G.AdjList(u).begin(); it != G.AdjList(u).end(); it++)
		{
			int v = *it;
			L.push_back(v);
		}
	}

	return G.GetNumVertices() == n;
}

pair< list<int>, double > ChinesePostman(const Graph& G, const vector<double>& cost)
{
	vector< list<int> > A(G.GetNumVertices(), list<int>());
	for (int u = 0; u < G.GetNumVertices(); u++)
		A[u] = G.AdjList(u);

	vector<int> odd;
	for (int u = 0; u < G.GetNumVertices(); u++)
		if (A[u].size() % 2)
			odd.push_back(u);

	if (!odd.empty())
	{
		Graph O(odd.size());
		for (int u = 0; u < (int)odd.size(); u++)
			for (int v = u + 1; v < (int)odd.size(); v++)
				O.AddEdge(u, v);

		vector<double> costO(O.GetNumEdges());

		vector< vector<int> > shortestPath(O.GetNumVertices());
		for (int u = 0; u < (int)odd.size(); u++)
		{
			pair< vector<int>, vector<double> > sp = Dijkstra(G, odd[u], cost);

			shortestPath[u] = sp.first;

			for (int v = 0; v < (int)odd.size(); v++)
				if (v != u)
					costO[O.GetEdgeIndex(u, v)] = sp.second[odd[v]];
		}

		Matching M(O);
		pair< list<int>, double > p = M.SolveMinimumCostPerfectMatching(costO);
		list<int> matching = p.first;

		for (list<int>::iterator it = matching.begin(); it != matching.end(); it++)
		{
			pair<int, int> p = O.GetEdge(*it);
			int u = p.first, v = odd[p.second];

			int w = shortestPath[u][v];
			while (w != -1)
			{
				A[w].push_back(v);
				A[v].push_back(w);
				v = w;
				w = shortestPath[u][v];
			}
		}
	}

	list<int> cycle;
	vector<int> traversed(G.GetNumEdges(), 0);
	for (int u = 0; u < G.GetNumVertices(); u++)
	{
		for (list<int>::iterator it = A[u].begin(); it != A[u].end(); it++)
		{
			int v = *it;

			if (v < u) continue;

			traversed[G.GetEdgeIndex(u, v)]++;
		}
	}

	cycle.push_back(0);
	list<int>::iterator itp = cycle.begin();
	double obj = 0;
	while (itp != cycle.end())
	{
		int u = *itp;
		list<int>::iterator jtp = itp;
		jtp++;

		while (!A[u].empty())
		{
			while (not A[u].empty() and traversed[G.GetEdgeIndex(u, A[u].back())] == 0)
				A[u].pop_back();

			if (not A[u].empty())
			{
				int v = A[u].back();
				A[u].pop_back();
				cycle.insert(jtp, v);
				traversed[G.GetEdgeIndex(u, v)]--;
				obj += cost[G.GetEdgeIndex(u, v)];
				u = v;
			}
		}

		itp++;
	}

	return pair< list<int>, double >(cycle, obj);
}
