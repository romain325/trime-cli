#include "../public/act.h"
#include <time.h>

void addNewActivity(cJSON* json, char* name){
  cJSON* act;
  if(!(act = cJSON_GetObjectItem(json, name))){
    //create a new activity
    act = cJSON_CreateObject();
    //precise an empty act type & empty acts
    cJSON_AddArrayToObject(act, "act_tags");
    cJSON_AddArrayToObject(act, "acts");

    // add to the final object
    cJSON_AddItemToObject(json, name, act);
  } else { 
    endActivity(json, name);
  }

  // create new act object
  cJSON* newAct = cJSON_CreateObject();
  cJSON_AddNumberToObject(newAct, "start", time(NULL));
  
  // add object to our array
  cJSON_AddItemToArray(cJSON_GetObjectItem(act, "acts"), newAct);
}

char endActivity(cJSON* json, char* name){
  cJSON* act;
  if((act = cJSON_GetObjectItem(json, name))){
    cJSON* acts = cJSON_GetObjectItem(act, "acts");
    cJSON* lastAct;
    if((lastAct = cJSON_GetArrayItem(acts, cJSON_GetArraySize(acts)-1))){
      if(!(cJSON_GetObjectItem(lastAct, "end"))){
        cJSON_AddNumberToObject(lastAct, "end", time(NULL));
        return 1;
      }
    }
  }
  return 0;
}
