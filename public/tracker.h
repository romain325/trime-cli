#ifndef TRACKER_H
#define TRACKER_H

#include "../public/cJSON.h"

cJSON* getTrackedData();
void saveTrackedData(cJSON* data);

void track(char* name);
void stop_tracking(char* name);

void removeTag(char* act_name, char* tag_name);
void addTag(char* act_name, char* tag_name);


#endif
