#pragma once

#include "Tools.h"
#include "NodeCPT.h"

class NodeACPT : public NodeCPT
{
public:
	NodeACPT();
	NodeACPT(NodeCPT node);
	~NodeACPT();
	string toString() override;
	bool nextLine();
};