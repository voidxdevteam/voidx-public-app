#pragma once
#include "Node.hpp"
#include <string>

class NodeFloat : public Node{
private:
	float value;
	float defaultValue;
	float min;
	float max;
	const char* unit;
	float shape; //0.49 - 0.51 = linear 0+-0.49 log, 0.51-1-anti-log
	bool inverted;
	int decimals;

public:
	NodeFloat(Node* parent, const char* name, const char* displayName, float min, float max, float defaultValue, const char * unit, float shape, bool inverted, int decimals);
	NodeFloat(Node* parent, const char* name, const char* displayName, float min, float max, float defaultValue, const char * unit, float shape, bool inverted);

	const char* getType();
	float getValue();
	bool setValue(float val);
	float toSlider();
	void reset();

	void edit(bool dir);
    void * getStorageData(int * length);
	bool fromString(std::string value);
	std::string toString();
	std::string getValueJSON();
	std::string getDescriptionJSON();
};

