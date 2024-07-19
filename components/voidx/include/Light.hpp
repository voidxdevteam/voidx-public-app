#pragma once
#include "Node.hpp"
#include "NodeEnum.hpp"

namespace Light {
	void disable();
	void enable();
	void initialize(Node * parent);
	void setStatus(NodeEnum * status);
	void forceColor(std::string value);
	void setDefaultColor(std::string value);
	void tasks();
}
