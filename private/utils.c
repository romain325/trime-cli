#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../public/ansi_constants.h"

unsigned long hash(char* str){
  unsigned long hash = 5381;
  int c;
  while((c = *str++))
    hash = ((hash << 5) + hash) + c;
  return hash;
}

char* getFilePath(){
  char* path = (char*) malloc(2048 * sizeof(char));
  sprintf(path, "%s/.config/trime_act.json", getenv("HOME"));
  return path;
}

void help(void){
    printf(BMAG "Help\n" RESET);
    printf(MAG "trime " RESET);
    printf("is a time tracking tool designed to help you track your activities\n");
    printf("The CLI allow you too track time from your command line quickly and then send the archived data to a remote db if wanted\n");
    printf(UMAG "Commands\n" RESET);
    printf(BWHT "track <name>:\n" RESET);
    printf("Track a specified action\n");
    printf(BWHT "stop <name>:\n" RESET);
    printf("Stop the tracking of a specified action\n");
    printf(BWHT "tag <action> <act_name> <tag_name>: \n" RESET);
    printf("Add/Remove a tag to a given activity if it exists\n");
    printf(MAG "Actions: add, rm" RESET);
    exit(EXIT_SUCCESS);
}

void trim(char * s) {
    char * p = s;
    int l = strlen(p);

    while(isspace(p[l - 1])) p[--l] = 0;
    while(* p && isspace(* p)) ++p, --l;

    memmove(s, p, l + 1);
}

char *strremove(char *str, const char *sub) {
    char *p, *q, *r;
    if (*sub && (q = r = strstr(str, sub)) != NULL) {
        size_t len = strlen(sub);
        while ((r = strstr(p = r + len, sub)) != NULL) {
            while (p < r)
                *q++ = *p++;
        }
        while ((*q++ = *p++) != '\0')
            continue;
    }
    return str;
}