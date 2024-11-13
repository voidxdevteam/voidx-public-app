#pragma once
#include "Node.hpp"
#include "Storage.hpp"

#define NODE_LIST_ELEMENT_CHUNK_SIZE			128
#define NODE_LIST_ELEMENT_HEADER_SIZE  			(NODE_LIST_ELEMENT_CHUNK_SIZE)
#define NODE_LIST_ELEMENT_HEADER_NAME_SIZE		32
#define NODE_LIST_ELEMENT_HEADER_CHECKSUM_SIZE	(NODE_LIST_ELEMENT_HEADER_SIZE - NODE_LIST_ELEMENT_HEADER_NAME_SIZE)

class NodeListElement : public Storable {
private:	
	std::string elmId;
	char * data;
	int dataSize;

public:
	NodeListElement();
	void setElmId(std::string elmId);
	std::string getName();
	char * getData();
	void setData(std::string name, void * data);
	void setDataSize(int size);
	void load();
	bool isEmpty();
	void clear();
	void setName(std::string name);

	void createId();
	void * getStorageData(int * length);
};

#define NODE_LIST_BUFFER_STATUS_IDLE -1

class NodeList : public Node {
private:
	const char* itemType;
	int elementSize;
	int elementCount;
	NodeListElement * elements;
	char * buffer;
	int bufferStatus;
	int bufferIndex;

public:
	NodeList(Node* parent, const char* name, const char* displayName, const char * itemType, int elementSize, int elementCount);

	const char* getType();

	bool parseWriteJSON(std::string data);
	std::string parseReadJSON(std::string data);
	std::string writeStatusJSON();

	char * dataAt(int index);
	int indexOf(std::string value);
	int firstEmpty();
	bool emptyAt(int index);
	std::string nameAt(int index);
	std::string firstValid();
	std::string before(std::string value);
	std::string next(std::string value);
	int getElementCount();
	int getElementSize();
	void clear();
	void deleteAt(int index);

	void edit(bool dir);
    void * getStorageData(int * length);

	void setElementAt(int index, std::string name, void * data);
	void setNameAt(int index, std::string name);
	std::string toString();
	bool fromString(std::string value);
	std::string getValueJSON();
	std::string getDescription();

	const char* getItemType();
};
