#include "../public/router.h"
#include "../public/tracker.h"
#include "../public/utils.h"

#include <stdio.h>
#include <string.h>

void router(int argc, char** argv){
  // Get hash for the needed commands
  //printf("%lu\n", hash("track"));
  //printf("%lu\n", hash("stop"));
  //printf("%lu\n", hash("tag"));
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
        if(strcmp(argv[2], "add") == 0){
          addTag(argv[3], argv[4]);
          break;
        }else if(strcmp(argv[2], "rm") == 0){
          removeTag(argv[3], argv[4]);
          break;
        }
      }
      help();
      break;
    default:
      help();
      break;
  }
}
