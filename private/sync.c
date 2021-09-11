#include "../public/utils.h"
#include "../public/tracker.h"
#include "../public/cJSON.h"
#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <string.h>

void send_patch_req(char* act_name, char* patched){
  CURL* req;
  CURLcode res;
  struct curl_slist *header = NULL;

  if((req = curl_easy_init() )){
    char url[256] = "";
    snprintf(url, sizeof(url), "%s%s", "https://firestore.googleapis.com/v1/projects/trime-tracker/databases/(default)/documents/trime/", act_name);

    curl_easy_setopt(req, CURLOPT_URL, url);
    // verbose, debug only
    // curl_easy_setopt(req, CURLOPT_VERBOSE, 1L);
    curl_easy_setopt(req, CURLOPT_CUSTOMREQUEST, "PATCH");
    curl_easy_setopt(req, CURLOPT_POSTFIELDS, patched);

    header = curl_slist_append(header, "Content-Type: application/json");
    curl_easy_setopt(req, CURLOPT_HTTPHEADER, header);

    res = curl_easy_perform(req);
    if(res != CURLE_OK){
      fprintf(stderr, "Error while requesting distant server\n%s\n", curl_easy_strerror(res));
    }

    curl_slist_free_all(header);
    curl_easy_cleanup(req);
  }
}

struct curl_string { char* ptr; size_t len; };

void init_curl_string(struct curl_string *s){
  s->len = 0;
  s->ptr = malloc(s->len+1);
  if (s->ptr == NULL) {
    fprintf(stderr, "malloc() failed\n");
    exit(EXIT_FAILURE);
  }
  s->ptr[0] = '\0';
}

const size_t write_func(void* ptr, const size_t size, const size_t nmemb, struct curl_string *s){
  const size_t new_len = s->len + size*nmemb;
  s->ptr = realloc(s->ptr, new_len+1);
  if (s->ptr == NULL) {
    fprintf(stderr, "realloc() failed\n");
    exit(EXIT_FAILURE);
  }
  memcpy(s->ptr+s->len, ptr, size*nmemb);
  s->ptr[new_len] = '\0';
  s->len = new_len;

  return size*nmemb;
}

cJSON* getPreviousAct(char* act_name){
  CURL* req;
  CURLcode res;
  struct curl_slist *header = NULL;

  if((req = curl_easy_init() )){
    char url[256] = "";
    snprintf(url, sizeof(url), "%s%s", "https://firestore.googleapis.com/v1/projects/trime-tracker/databases/(default)/documents/trime/", act_name);

    curl_easy_setopt(req, CURLOPT_URL, url);
    curl_easy_setopt(req, CURLOPT_WRITEFUNCTION, write_func);

    struct curl_string s;
    init_curl_string(&s);
    curl_easy_setopt(req, CURLOPT_WRITEDATA, &s);
    // verbose, debug only
    //curl_easy_setopt(req, CURLOPT_VERBOSE, 1L);

    res = curl_easy_perform(req);
    if(res != CURLE_OK){
      fprintf(stderr, "Error while requesting distant server\n%s\n", curl_easy_strerror(res));
      return NULL;
    }

    cJSON* result = cJSON_Parse(s.ptr);
    
    free(s.ptr);
    curl_slist_free_all(header);
    curl_easy_cleanup(req);

    return result;
  }
  return NULL;
}

void updateActivities(cJSON* prev_arr, const cJSON* to_add){
  cJSON* elem = NULL;
  cJSON_ArrayForEach(elem, to_add){
    cJSON* firestore_obj = cJSON_CreateObject();
    cJSON* fields = cJSON_AddObjectToObject(cJSON_AddObjectToObject(firestore_obj, "mapValue"), "fields");
    cJSON_AddNumberToObject(cJSON_AddObjectToObject(fields, "start"), "integerValue", cJSON_GetNumberValue(cJSON_GetObjectItem(elem, "start")));
    cJSON_AddNumberToObject(cJSON_AddObjectToObject(fields, "end"), "integerValue", cJSON_GetNumberValue(cJSON_GetObjectItem(elem, "end")));
    cJSON_AddItemToArray(prev_arr, firestore_obj);
  }
}

void sync_act(void){
  const cJSON* json = getTrackedData();
  const cJSON* elem = NULL;
  cJSON* prev = NULL;
  cJSON_ArrayForEach(elem, json) {
    prev = getPreviousAct(elem->string);
    if(prev == NULL) continue;

    //printf("%s\n%s\n", cJSON_Print(elem), cJSON_Print(prev));
    //printf("%s\n%s\n", cJSON_Print(cJSON_GetObjectItem(cJSON_GetObjectItem(cJSON_GetObjectItem(cJSON_GetObjectItem(prev, "fields"), "acts"), "arrayValue"), "values")), cJSON_Print(cJSON_GetObjectItem(elem, "acts")));
    updateActivities(cJSON_GetObjectItem(cJSON_GetObjectItem(cJSON_GetObjectItem(cJSON_GetObjectItem(prev, "fields"), "acts"), "arrayValue"), "values"), cJSON_GetObjectItem(elem, "acts"));
    send_patch_req(elem->string, cJSON_PrintUnformatted(prev));
    cJSON_Delete(prev);
  }

  cJSON_Delete(json);

  char* filename = getFilePath();
  remove(filename);
  free(filename);
}

void sync_tag(void){
  const cJSON* json = getTrackedData();
  const cJSON* elem = NULL;
  cJSON* prev = NULL;
  cJSON_ArrayForEach(elem, json) {
    prev = getPreviousAct(elem->string);
    if(prev == NULL) continue;

    char* tags_local = cJSON_GetObjectItem(elem, "act_tags")->valuestring;
    trim(tags_local);
    if(strcmp(tags_local, "") == 0) continue;
    
    cJSON* tags = cJSON_GetObjectItem(cJSON_GetObjectItem(cJSON_GetObjectItem(prev, "fields"), "act_tags"), "stringValue");
    if(tags) {
      tags->valuestring = tags_local;
    }
    send_patch_req(elem->string, cJSON_PrintUnformatted(prev));
    cJSON_Delete(prev);
  }

  cJSON_Delete(json);
}

void sync_all(void){
  sync_tag();
  sync_act();
}