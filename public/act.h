#ifndef ACTS_H
#define ACTS_H

#include "../public/cJSON.h"

// start a new activity
void addNewActivity(cJSON* json, char* name);
// end an activity if any is running
char endActivity(cJSON* json, char* name);

#endif
