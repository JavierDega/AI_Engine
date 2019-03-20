#include "pch.h"
#include "..\Headers\NavigationGraph.h"



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
