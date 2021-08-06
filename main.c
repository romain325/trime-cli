#include "public/utils.h"
#include "public/router.h"

int main(int argc, char** argv) {
    if(argc <= 2) help();
    router(argc, argv); 
    return 0;
}
