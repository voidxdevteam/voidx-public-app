#pragma once
#include "ComInterface.hpp"

#include "esp_err.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "mdns.h"
#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include <lwip/netdb.h>
#include "../NodeItem.hpp"

#define WIFI_BUFFER_MAX_SIZE (1024*16)
#define WIFI_MAX_SERVER		 5

class Wifi: public ComInterface {
private:
	wifi_config_t config;
	Node * devName;
	NodeItem * nodeSSID;
	NodeItem * nodePWD;
	int port;
	int listen_sock;
	int server_sock[WIFI_MAX_SERVER];
	int ip_protocol;
	int addr_family;
	mdns_txt_item_t desc_txt[2];
	char service_instance[50];
	struct timeval timeout;
    struct sockaddr_in6 dest_addr;
	struct sockaddr_storage source_addr;
	socklen_t socklen;
	int socket_state;
	char * buffer;
	bool connected;
public:
	Wifi(Node * root, Node * devName, int port);
	void initialize();
	void friend udp_socket_thread(void * param);
	void tasks();
	virtual ~Wifi(){};
};
