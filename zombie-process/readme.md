# Zombie Process
A process that has completed it's execution but still has an entry in the system's process table.
## Working
- When child process finished it execution, it sends a signal `SIGCHILD` to it's parent process and dies.
- Operating System keeps a record which include `process ID` and `exit status` in the process table. So parent can check from their.
- Once the parent call `wait()` sys call to read this status, the zombie is reaped and completely remove from table.
- If parent is poorly programmed and never calls `wait()`, the child remains in table for indefinitely as zombie.

## How to Identify them
Use the `ps` command in terminal and look for status `Z` status or word `<defunct>`
<br>

```
ps aux | grep -E 'Z|<defuct>'
```
