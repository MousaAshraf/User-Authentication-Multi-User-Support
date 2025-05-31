#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "riscv.h"
#include "spinlock.h"
#include "proc.h"
#include "defs.h"
#include "user.h"

struct user users[MAX_USERS];
int current_user_uid = -1;
int user_count = 0;
struct spinlock user_lock;

void init_users(void) {
    initlock(&user_lock, "user");
    
    acquire(&user_lock);
    
    // Initialize with default admin user
    users[0].uid = 0;
    safestrcpy(users[0].username, "admin", MAX_USERNAME);
    safestrcpy(users[0].password, "admin", MAX_PASSWORD);
    users[0].is_admin = 1;
    users[0].active = 1;
    user_count = 1;
    
    release(&user_lock);
}

int add_user(char *username, char *password, int is_admin) {
    acquire(&user_lock);
    
    if (user_count >= MAX_USERS) {
        release(&user_lock);
        return -1; // User limit reached
    }
    
    // Check if username already exists
    for (int i = 0; i < user_count; i++) {
        if (users[i].active && strncmp(users[i].username, username, MAX_USERNAME) == 0) {
            release(&user_lock);
            return -2; // Username already exists
        }
    }
    
    // Find next available UID
    int new_uid = user_count;
    users[new_uid].uid = new_uid;
    safestrcpy(users[new_uid].username, username, MAX_USERNAME);
    safestrcpy(users[new_uid].password, password, MAX_PASSWORD);
    users[new_uid].is_admin = is_admin;
    users[new_uid].active = 1;
    user_count++;
    
    release(&user_lock);
    return new_uid;
}

int authenticate_user(char *username, char *password) {
    acquire(&user_lock);
    
    for (int i = 0; i < user_count; i++) {
        if (users[i].active && 
            strncmp(users[i].username, username, MAX_USERNAME) == 0 &&
            strncmp(users[i].password, password, MAX_PASSWORD) == 0) {
            current_user_uid = users[i].uid;
            release(&user_lock);
            return users[i].uid;
        }
    }
    
    release(&user_lock);
    return -1; // Authentication failed
}

int delete_user(char *username) {
    acquire(&user_lock);
    
    // Don't allow deletion of admin user
    if (strncmp(username, "admin", MAX_USERNAME) == 0) {
        release(&user_lock);
        return -3; // Cannot delete admin
    }
    
    for (int i = 0; i < user_count; i++) {
        if (users[i].active && strncmp(users[i].username, username, MAX_USERNAME) == 0) {
            users[i].active = 0;
            release(&user_lock);
            return 0; // Success
        }
    }
    
    release(&user_lock);
    return -1; // User not found
}

int is_current_user_admin(void) {
    if (current_user_uid == -1) return 0;
    
    acquire(&user_lock);
    for (int i = 0; i < user_count; i++) {
        if (users[i].active && users[i].uid == current_user_uid) {
            int is_admin = users[i].is_admin;
            release(&user_lock);
            return is_admin;
        }
    }
    release(&user_lock);
    return 0;
}

// Placeholder functions for storage (not implemented for simplicity)
void save_users_to_storage(void) {
    // Not implemented - would require complex file system integration
}

void load_users_from_storage(void) {
    // Not implemented - would require complex file system integration
}
