#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    char choice[10];
    char username[16];
    char password[16];
    int result;
    
    if (!isadmin()) {
        printf("Access denied! Administrator privileges required.\n");
        exit(1);
    }
    
    printf("=== User Management System ===\n");
    printf("1. Add User\n");
    printf("2. Delete User\n");
    printf("3. Add Admin User\n");
    printf("4. Exit\n");
    printf("Enter choice (1-4): ");
    
    gets(choice, sizeof(choice));
    
    switch (choice[0]) {
        case '1':
            printf("Enter username: ");
            gets(username, sizeof(username));
            for (int i = 0; username[i]; i++) {
                if (username[i] == '\n') { username[i] = '\0'; break; }
            }
            
            printf("Enter password: ");
            gets(password, sizeof(password));
            for (int i = 0; password[i]; i++) {
                if (password[i] == '\n') { password[i] = '\0'; break; }
            }
            
            result = adduser(username, password, 0);
            if (result >= 0) {
                printf("User added successfully!\n");
            } else {
                printf("Failed to add user.\n");
            }
            break;
            
        case '2':
            printf("Enter username to delete: ");
            gets(username, sizeof(username));
            for (int i = 0; username[i]; i++) {
                if (username[i] == '\n') { username[i] = '\0'; break; }
            }
            
            result = deluser(username);
            if (result == 0) {
                printf("User deleted successfully!\n");
            } else {
                printf("Failed to delete user.\n");
            }
            break;
            
        case '3':
            printf("Enter admin username: ");
            gets(username, sizeof(username));
            for (int i = 0; username[i]; i++) {
                if (username[i] == '\n') { username[i] = '\0'; break; }
            }
            
            printf("Enter admin password: ");
            gets(password, sizeof(password));
            for (int i = 0; password[i]; i++) {
                if (password[i] == '\n') { password[i] = '\0'; break; }
            }
            
            result = adduser(username, password, 1);
            if (result >= 0) {
                printf("Admin user added successfully!\n");
            } else {
                printf("Failed to add admin user.\n");
            }
            break;
            
        case '4':
            printf("Goodbye!\n");
            break;
            
        default:
            printf("Invalid choice!\n");
            break;
    }
    
    exit(0);
}
