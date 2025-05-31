#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    printf("Logging out... Goodbye!\n");
    
    // Start login program again
    exec("login", argv);
    
    // If exec fails, exit
    printf("Logout failed - exec error\n");
    exit(1);
}
