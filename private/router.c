#include "public/router.h"
#include "public/tracker.h"
#include "public/utils.h"

#include <stdio.h>

void router(int argc, char** argv){
  // Get hash for the needed commands
  //printf("%lu\n", hash("track"));
  //printf("%lu\n", hash("stop"));

  switch (hash(argv[1])) {
    case TRACK_ACT:
      track(argv[2]);
      break;
    case STOP_ACT:
      stop_tracking(argv[2]);
      break;
    default:
      help();
      break;
  }
}
