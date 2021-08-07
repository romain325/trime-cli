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
  endActivity(json, name);
  saveTrackedData(json);
}
