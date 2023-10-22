#pragma once

#define STORE_STATUS_OFF      0
#define STORE_STATUS_OK       1
#define STORE_STATUS_CHANGED  2

#define STORAGE_DELAY         50
#define STORAGE_TIME_MS       10

class Storable {
protected:
    char id[16];
    int status;
public:
    Storable();
    char * getStorageId();
    int getStorageStatus();
    void loadStorage();
    void storeStorage();
    virtual void onLoad(){};
    virtual void createId() = 0;
    virtual void * getStorageData(int * length) = 0;
    virtual ~Storable() {}
};

namespace Storage
{
   void addItem(Storable * item);    
   void storageTasks(void * par);
   void tasks();
}
