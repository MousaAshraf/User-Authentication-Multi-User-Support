#ifndef USER_H
#define USER_H

#define MAX_USERS 10
#define MAX_USERNAME 16
#define MAX_PASSWORD 16

struct user {
    int uid;
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    int is_admin;
    int active;
};

extern struct user users[MAX_USERS];
extern int current_user_uid;
extern int user_count;

// Function declarations
int add_user(char *username, char *password, int is_admin);
int authenticate_user(char *username, char *password);
int delete_user(char *username);
int is_current_user_admin(void);
void init_users(void);
void save_users_to_storage(void);
void load_users_from_storage(void);

#endif
