#pragma once
#include "Node.hpp"
#include "NodeEnum.hpp"

namespace Light {
	void initialize(Node * parent);
	void setStatus(NodeEnum * status);
	void tasks();
}
