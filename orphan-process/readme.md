# Orphan Process
A process becomes an orphan if is parent exits while the child is still running. Unlike zombies, orphans are still running not dead.                     
## Explanation
- fork() creates a child.
- Parent sleeps 1 second, then exits.
- Child sleeps 5 seconds, so it outlives the parent.
- During the child’s sleep, the parent exits → child becomes an orphan.
- After orphaned, getppid() in the child will show 1 (PID of init/systemd).

## How to identify them
Compile and run program
`gcc orphan.c -o orphan.out && ./orphan.out`
After this run this command and watch
`ps -o pid,ppid,cmd`
You will see the child's PPID change to 1 once the parent exits.