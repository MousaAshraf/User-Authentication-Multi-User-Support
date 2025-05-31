#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    char username[16];
    char password[16];
    int uid;
    
    printf("=== XV6 Login System ===\n");
    printf("Username: ");
    gets(username, sizeof(username));
    
    for (int i = 0; username[i]; i++) {
        if (username[i] == '\n') {
            username[i] = '\0';
            break;
        }
    }
    
    printf("Password: ");
    gets(password, sizeof(password));
    
    for (int i = 0; password[i]; i++) {
        if (password[i] == '\n') {
            password[i] = '\0';
            break;
        }
    }
    
    uid = login(username, password);
    
    if (uid >= 0) {
        printf("Login successful! Welcome, %s\n", username);
        
        if (isadmin()) {
            printf("Administrator access granted.\n");
            printf("Type 'usermgmt' to manage users.\n");
        } else {
            printf("Regular user access.\n");
        }
        
        char *sh_argv[] = { "sh", 0 };
        exec("sh", sh_argv);
    } else {
        printf("Login failed!\n");
        exit(1);
    }
    
    exit(0);
}
