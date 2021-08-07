#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../public/ansi_constants.h"

unsigned long hash(char* str){
  unsigned long hash = 5381;
  int c;
  while((c = *str++))
    hash = ((hash << 5) + hash) + c;
  return hash;
}

char* getFilePath(){
  char* home = getenv("HOME");
  char* path = malloc(strlen(home) + 24);
  strcat(path, home);
  strcat(path, "/.config/trime_act.json");
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

    exit(EXIT_SUCCESS);
}
