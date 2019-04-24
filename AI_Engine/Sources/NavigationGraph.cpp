#include "pch.h"
#include "..\Headers\NavigationGraph.h"

#include <algorithm>

#define BOUNDXMIN 360
#define BOUNDXMAX 1560
#define XWIDTH 1200
//Y 54 TALL
//X 60 WIDE

using namespace std;
using namespace DirectX;
using namespace SimpleMath;

NavGraph::NavGraph()
{
	for (unsigned int i = 0; i < 20; i++) {
		for (unsigned int j = 0; j < 20; j++) {
			m_nodes[j][i] = GraphNode(i * 20 + j);
		}
	}
}

NavGraph::~NavGraph()
{
}

std::vector<DirectX::SimpleMath::Vector2> NavGraph::CalculateAStar(DirectX::SimpleMath::Vector2 currentPos, DirectX::SimpleMath::Vector2 targetPos)
{
	//@A*
	vector<int> m_path;
	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 20; x++)
		{
			m_path.push_back(-1);//= null value
		}
	}

	vector<int> m_costs;
	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 20; x++)
		{
			m_costs.push_back(INT_MAX);
		}
	}

	vector<GraphEdge> m_alreadyTraversed;

	MinPriorityQueue m_mpq = MinPriorityQueue();

	//@Turn currentPos Vector2 into a sourceNode index.
	int sourceNodeX = round((currentPos.x - 360) / 60.f);
	int sourceNodeY = round(currentPos.y / 54.f);
	int sourceNode = sourceNodeY * 20 + sourceNodeX;

	int targetNodeX = round((targetPos.x - 360) / 60.f);
	int targetNodeY = round(targetPos.y / 54.f);
	int targetNode = targetNodeY * 20 + targetNodeX;

	m_costs[sourceNodeY*20 + sourceNodeX] = 0;
	//@Calculate only once
	//Add all adjacent nodes to the source, to the min priority queue

	for (int i = 0; i < m_nodes[sourceNodeX][sourceNodeY].m_edges.size(); i++)
	{
		GraphEdge edge = m_nodes[sourceNodeX][sourceNodeY].m_edges[i];
		//Input manhattan heuristic cost
		int nodeX = edge.m_to % 20;
		int nodeY = edge.m_to / 20;

		int heuristicCost = abs(nodeX - targetNodeX) + abs(nodeY - targetNodeY);
		m_mpq.Add(edge, 1 + heuristicCost);//All costs are initially one (Grid based solution)
	}
	bool TargetNodeFound = false;
	while (m_mpq.m_edges.size() > 0) {
		//Pop element from MPQueue and put into traversedEdges list
		GraphEdge curEdge = m_mpq.Pop();
		m_alreadyTraversed.push_back(curEdge);

		//Check if the cost of the node this edge leads to is greater than the cost of the previous node plus the cost of the edge
		if (m_costs[curEdge.m_to] > m_costs[curEdge.m_from] + 1) {
			m_path[curEdge.m_to] = curEdge.m_from;//@Each path bit marks where it's from
			m_costs[curEdge.m_to] = m_costs[curEdge.m_from] + 1;
			if (targetNode == curEdge.m_to)
			{
				TargetNodeFound = true;//Not ideal to terminate loop YET
				break;
			}
			else {
				//Add all adjacent edges to the queue using a for loop
				GraphNode curNode = m_nodes[curEdge.m_to % 20] [curEdge.m_to / 20];
				for (int i = 0; i < curNode.m_edges.size(); i++) {
					//If the edge is on the already traversed queue or the min-priority queue then do not add
					if (find(m_alreadyTraversed.begin(), m_alreadyTraversed.end(), curNode.m_edges[i]) != m_alreadyTraversed.end()){
						continue;
					}

					if (find(m_mpq.m_edges.begin(), m_mpq.m_edges.end(), curNode.m_edges[i]) != m_mpq.m_edges.end()) {
						continue;
					}

					//Otherwise add to the queue and set its priority as the current node's cost plus the cost of this adjacent edge
					//In our case all edges cost 1.
					//Input manhattan heuristic cost
					int nodeX = curNode.m_edges[i].m_to % 20;
					int nodeY = curNode.m_edges[i].m_to / 20;

					int heuristicCost = abs(nodeX - targetNodeX) + abs(nodeY - targetNodeY);
					m_mpq.Add(curNode.m_edges[i], m_costs[curNode.m_index] + 1 + heuristicCost);
				}
			}
		}

	}

	//@Format path (TargetNodeFound should always be true.
	vector<Vector2> m_positions;
	m_positions.insert(m_positions.begin(), targetPos);
	//@Now track down from end node, up to starting node, painting the followed upon path
	int endNodeFrom = m_path[targetNode];
	if (endNodeFrom < 0) return m_positions;
	int newNodeFrom = m_path[endNodeFrom];
	if (newNodeFrom < 0) return m_positions;
	while (m_path[newNodeFrom] != sourceNode)
	{
		newNodeFrom = m_path[newNodeFrom];
		if (newNodeFrom == -1)break;
		float x = 360 + (newNodeFrom % 20) * 60;
		float y = (newNodeFrom / 20) * 54;
		Vector2 nextPosition = Vector2(x,y);
		m_positions.insert(m_positions.begin(), nextPosition);
	}
	return m_positions;
}
