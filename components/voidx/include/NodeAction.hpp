#pragma once
#include "Node.hpp"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define NODE_ACTION_TYPE_SIMPLE 		"smp"
#define NODE_ACTION_TYPE_CONFIRM 		"smp_cfm"

#define NODE_ACTION_STATUS_IDLE			"idle"
#define NODE_ACTION_STATUS_RUN			"run"

#define ACTION_TIME_MS					50

class NodeAction : public Node {
private:
    inline static std::queue<NodeAction *> action_queue;
	inline static bool actionInitialized = false;
	static void initializeAction();
	static void action_task(void * ptr);

	std::string value;
	const char* actionType;

	void * node_action_data;
	void (*node_action) (void * data);

protected:
	void exec();

public:
	NodeAction(Node* parent, const char* name, const char* displayName, const char * actionType, void (*node_action) (void *), void * node_action_data = NULL);

	const char* getType();
	virtual std::string getValue();
	bool setValue(std::string value);

	void edit(bool dir);
    void * getStorageData(int * length);
	std::string toString();
	bool fromString(std::string value);
	std::string getValueJSON();
	std::string getDescription();

	const char* getActionType();
};
