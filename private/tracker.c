#include "../public/tracker.h"
#include "../public/act.h"
#include "../public/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

cJSON* getTrackedData(){
  FILE* f;

  char* filename = getFilePath();
  if((f = fopen(filename, "r"))){
    
    //define file size
    fseek(f,0,SEEK_END);
    long fsize = ftell(f);
    fseek(f,0,SEEK_SET);

    // get whole as string
    char* str = malloc(fsize+1);
    fread(str, 1,fsize,f);
    fclose(f);
    
    // set end of char *  as classic end
    str[fsize] = '\0';

    free(filename);
    return cJSON_Parse(str);
  }else {
    free(filename);
    return cJSON_Parse("{}");
  }
  
}

void saveTrackedData(cJSON* data){
  FILE* f;
  char* filename = getFilePath();
  if((f = fopen(filename, "w"))){
    fputs(cJSON_Print(data), f);
    fclose(f);
  }else{
    printf("error while opening file");
  }
  free(filename);
}

void track(char* name){
  printf("Now tracking %s", name);
  cJSON* json = getTrackedData();
  addNewActivity(json, name);
  saveTrackedData(json);
}

void stop_tracking(char* name){
  printf("Not tracking anymore %s", name);
  cJSON* json = getTrackedData();
  if(endActivity(json, name)){
    saveTrackedData(json);
  }
}

void addTag(char* act_name, char* tag_name) {
  printf("Adding tag %s to %s", tag_name, act_name);
  cJSON* json = getTrackedData();

  cJSON* elem = cJSON_GetObjectItem(json, act_name);
  if(elem){
    cJSON* arr = cJSON_GetObjectItem(elem, "act_tags");
    if(!arr){
      cJSON_AddArrayToObject(elem, "act_tags");
    }
    cJSON_AddItemToArray(arr, cJSON_CreateString(tag_name));
    saveTrackedData(json);
  }
}

void removeTag(char* act_name, char* tag_name){
  printf("Removing tag %s from %s", tag_name, act_name);
  cJSON* json = getTrackedData();

  cJSON* elem = cJSON_GetObjectItem(json, act_name);
  if(elem){
    cJSON* arr = cJSON_GetObjectItem(elem, "act_tags");
    if(arr){
      const cJSON* elem = NULL;
      int cnt = 0;
      cJSON_ArrayForEach(elem, arr){
        if(strcmp(tag_name, elem->valuestring) == 0){
          cJSON_DeleteItemFromArray(arr, cnt);
        }
        cnt++;
      }
    }
  }

  saveTrackedData(json);
}
