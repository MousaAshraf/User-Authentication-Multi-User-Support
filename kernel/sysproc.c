#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "user.h"

uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return wait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  if(n < 0)
    n = 0;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

uint64
sys_login(void)
{
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    
    if (argstr(0, username, MAX_USERNAME) < 0 ||
        argstr(1, password, MAX_PASSWORD) < 0)
        return -1;
    
    return authenticate_user(username, password);
}

uint64
sys_adduser(void)
{
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    int is_admin;
    
    if (!is_current_user_admin())
        return -4;
    
    if (argstr(0, username, MAX_USERNAME) < 0)
        return -1;
    if (argstr(1, password, MAX_PASSWORD) < 0)
        return -1;
    
    argint(2, &is_admin);
    
    return add_user(username, password, is_admin);
}

uint64
sys_deluser(void)
{
    char username[MAX_USERNAME];
    
    if (!is_current_user_admin())
        return -4;
    
    if (argstr(0, username, MAX_USERNAME) < 0)
        return -1;
    
    return delete_user(username);
}

uint64
sys_isadmin(void)
{
    return is_current_user_admin();
}
