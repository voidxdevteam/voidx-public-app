#pragma once
#include "Node.hpp"
#include "NodeEnum.hpp"

namespace Light {
	void disable();
	void enable();
	void initialize(Node * parent);
	void setStatus(NodeEnum * status);
	void tasks();
}
