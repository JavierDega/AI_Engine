#pragma once
#include <vector>


typedef struct GraphEdgeStr {
	public:
	GraphEdgeStr(int from, int to) {
		m_from = from;
		m_to = to;
	}
	//@Variables
	int m_from;//Connected nodes
	int m_to;
	//@@float m_cost;//Not used
}GraphEdge;

typedef struct GraphNodeStr {
public:
	GraphNodeStr() {
	
	}

	GraphNodeStr(int index) {
		m_index = index;
	}
	
	//@Variables
	int m_index;
	std::vector<GraphEdge> m_edges;//adjacency list

}GraphNode;


class NavGraph
{
public:
	NavGraph();
	~NavGraph();

	//@NOT WORKING CORRECTLY.
	/*std::vector<int> CalculateAStar(DirectX::SimpleMath::Vector2 currentPos, DirectX::SimpleMath::Vector2 targetPos) {
		//@A*
		List<int> m_path = new List<int>();
		for (int y = 0; y < 64; y++)
		{
			for (int x = 0; x < 64; x++)
			{
				m_path.Add(-1);//= null value
			}
		}

		List<int> m_costs = new List<int>();
		for (int y = 0; y < 64; y++)
		{
			for (int x = 0; x < 64; x++)
			{
				m_costs.Add(int.MaxValue);
			}
		}


		List<GraphEdge> m_alreadyTraversed = new List<GraphEdge>();

		MinPriorityQueue m_mpq = new MinPriorityQueue();
		m_mpq.m_edges = new List<GraphEdge>();
		m_mpq.m_costs = new List<int>();

		m_costs[sourceNode] = 0;
		//@Calculate only once
		int targetX = targetNode % 64;
		int targetY = targetNode / 64;

		int sourceX = sourceNode % 64;
		int sourceY = sourceNode / 64;

		//Add all adjacent nodes to the source, to the min priority queue

		for (int i = 0; i < m_nodes[sourceNode].m_edges.Count; i++)
		{
			GraphEdge edge = m_nodes[sourceNode].m_edges[i];
			//Input manhattan heuristic cost
			int nodeX = edge.m_to % 64;
			int nodeY = edge.m_to / 64;

			int heuristicCost = Math.Abs(nodeX - targetX) + Math.Abs(nodeY - targetY);
			m_mpq.Add(edge, 1 + heuristicCost);//All costs are initially one (Grid based solution)
		}
		bool TargetNodeFound = false;
		while (m_mpq.m_edges.Count > 0) {
			//Pop element from MPQueue and put into traversedEdges list
			GraphEdge curEdge = m_mpq.Pop();
			m_alreadyTraversed.Add(curEdge);

			//Check if the cost of the node this edge leads to is greater than the cost of the previous node plus the cost of the edge
			if (m_costs[curEdge.m_to] > m_costs[curEdge.m_from] + 1) {
				m_path[curEdge.m_to] = curEdge.m_from;
				m_costs[curEdge.m_to] = m_costs[curEdge.m_from] + 1;
				if (targetNode == curEdge.m_to)
				{
					TargetNodeFound = true;//Not ideal to terminate loop YET
					break;
				}
				else {
					//Add all adjacent edges to the queue using a for loop
					GraphNode curNode = m_nodes[curEdge.m_to];
					for (int i = 0; i < curNode.m_edges.Count; i++) {
						//If the edge is on the already traversed queue or the min-priority queue then do not add
						if (m_alreadyTraversed.Contains(curNode.m_edges[i]))
						{
							continue;
						}
						if (m_mpq.m_edges.Contains(curNode.m_edges[i]))
						{
							continue;
						}
						//Otherwise add to the queue and set its priority as the current node's cost plus the cost of this adjacent edge
						//In our case all edges cost 1.
						//Input manhattan heuristic cost
						int nodeX = curNode.m_edges[i].m_to % 64;
						int nodeY = curNode.m_edges[i].m_to / 64;

						int heuristicCost = Math.Abs(nodeX - targetX) + Math.Abs(nodeY - targetY);
						m_mpq.Add(curNode.m_edges[i], m_costs[curNode.m_index] + 1 + heuristicCost);
					}
				}
			}

		}
		if (TargetNodeFound) return m_path;
		else return null;
	}*/

	//@Variables
	GraphNode m_nodes[20][20];//64 pixels wide on the screen, 54 pixels tall.
};
