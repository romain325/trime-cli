#include "../public/router.h"
#include "../public/tracker.h"
#include "../public/utils.h"
#include "../public/sync.h"

#include <stdio.h>
#include <string.h>

void router(int argc, char** argv){
  // Get hash for the needed commands
  //printf("%lu\n", hash("track"));
  //printf("%lu\n", hash("stop"));
  //printf("%lu\n", hash("tag"));
  //printf("%lu\n", hash("add"));
  //printf("%lu\n", hash("rm"));
  //printf("%lu\n", hash("act"));
  //printf("%lu\n", hash("both"));

  //printf("%lu\n", hash(argv[1]));
  //printf("%d\n", argc);

  switch (hash(argv[1])) {
    case TRACK_ACT:
      track(argv[2]);
      break;
    case STOP_ACT:
      stop_tracking(argv[2]);
      break;
    case TAG_ACT:
      if(argc >= 4){
        switch(hash(argv[2])){
          case ADD_ACT:
            addTag(argv[3], argv[4]);
            break;
          case RM_ACT:
            removeTag(argv[3], argv[4]);
            break;
          default: help();
        }
      }else { help(); }
      break;
    case SYNC_ACT:
      if(argc >= 2){
        switch(hash(argv[2])){
          case ACT_ACT:
            sync_act();
            break;
          case TAG_ACT:
            sync_tag();
            break;
          case BOTH_ACT:
            sync_all();
            break;
          default:
            help();
        }
      }else{ help(); }
      break;
    default:
      help();
      break;
  }
}
