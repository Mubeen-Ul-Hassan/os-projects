# Orphan Process
A process becomes an orphan if is parent exits while the child is still running. Unlike zombies, orphans are still running not dead.                     
## Explanation
- fork() creates a child.
- Parent sleeps 1 second, then exits.
- Child sleeps 5 seconds, so it outlives the parent.
- During the child’s sleep, the parent exits → child becomes an orphan.
- After orphaned, getppid() in the child will show 1 (PID of init/systemd).

## How to identify them
Compile and run program:
`gcc orphan.c -o orphan.out && ./orphan.out`
While the child process is still running, check its PID and PPID:
`ps -o pid,ppid,cmd -p <child_pid>`
Initially, its PPID is the PID of its parent process. After the parent exits, the child becomes **orphan**. The PPID will change to the PID of the adopting process (usually `systemmd` or your shell), which may or may not be 1. Orphan processes are often adopted by a subreaper.
