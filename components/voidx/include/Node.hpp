#pragma once
#include "Storage.hpp"
#include "debug.hpp"
#include <string>
#include <queue>
#include <list>

extern std::hash<std::string> string_hasher;

#define NODE_TYPE_FLOAT				"float"
#define NODE_TYPE_ENUM				"enum"
#define NODE_TYPE_ITEM				"item"
#define NODE_TYPE_LIST				"list"
#define NODE_TYPE_PAR_LIST			"plist"
#define NODE_TYPE_CONTROL			"ctrl"

#define NODE_DIR_INC				true
#define NODE_DIR_DEC				false

class Node: public Storable {

protected:
	const char* name;
	const char* displayName;
	Node* parent;
	std::list<Node *> children;
	int64_t editTime;
	bool visible;

public:
	Node(Node* parent, const char* name, const char * displayName);

	const char* getName();
	const char* getDisplayName();
	void setDisplayName(const char * displayName);
	std::string getPath();
	Node* pathToNode(std::string path);
	int childrenCount();
	int childrenCount(bool visible);
	int leafCount();
	Node* getParent();
	Node* childrenAt(int index);
	Node * childrenAt(int index, bool visible);
	std::list<Node *> getChildren();
	bool isLeaf();
	bool isVisible();
	void setVisible(bool visible);

	bool parseJSON(std::string data);

	std::string getJSON(bool description);
	std::string getJSON(bool description, bool recursive);
	std::string getJSON_after(bool description, bool recursive, Node * after);
	std::string getJSON_after(bool description, bool recursive, Node * after, bool older, int64_t time, bool include_leaf);

	//timing
	void notifyUpdate();
	int64_t getTime();
	bool older(int64_t time, bool recursive, Node * after);

	//abstract functions
	void createId();
	virtual void edit(bool dir) = 0;
	virtual bool fromString(std::string value) = 0;
	virtual std::string toString() = 0;
	virtual const char* getType() = 0;
	virtual std::string getValueJSON() = 0;
	virtual std::string getDescriptionJSON() = 0;
	virtual ~Node() {}
};

