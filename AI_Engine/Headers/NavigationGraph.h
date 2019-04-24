#pragma once
#include <vector>

typedef struct GraphEdgeStr {
	public:
	GraphEdgeStr(int from, int to) {
		m_from = from;
		m_to = to;
	}

	bool operator==(const GraphEdgeStr  &g) const {
		return (m_from == g.m_from) && (m_to == g.m_to);
	};
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

typedef struct MinPriorityQueueStr {
public:
	GraphEdge Add(GraphEdge edge, int cost) {
		m_edges.push_back(edge);
		m_costs.push_back(cost);
		return edge;
	}

	GraphEdge Pop() {
		//Pop the one with lowest priority
		int lowestPriority = INT_MAX;
		int index = -1;
		for (int i = 0; i < m_edges.size(); i++) {
			//Size should be the same as the cost list.
			if (m_costs[i] < lowestPriority)
			{
				lowestPriority = m_costs[i];
				index = i;
			}
		}
		GraphEdge returnedEdge = m_edges[index];
		m_edges.erase(m_edges.begin() + index);
		m_costs.erase(m_costs.begin() + index);
		return returnedEdge;
	}

	std::vector<GraphEdge> m_edges;
	std::vector<int> m_costs;
}MinPriorityQueue;

class NavGraph
{
public:
	NavGraph();
	~NavGraph();

	//@NOT WORKING CORRECTLY.
	std::vector<DirectX::SimpleMath::Vector2> CalculateAStar(DirectX::SimpleMath::Vector2 currentPos, DirectX::SimpleMath::Vector2 targetPos);

	//@Variables
	GraphNode m_nodes[20][20];//60 pixels wide on the screen, 54 pixels tall.
};
