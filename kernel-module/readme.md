# Assignments

This assignment will involve designing two kernel modules: <br>
1. Design a kernel module that creates a /proc file named */proc/jiffies*
that reports the current value of jiffies when the /proc/jiffies file
is read, such as with the command
<br> `cat /proc/jiffies` <br>
Be sure to remove /proc/jiffies when the module is removed. <br>

2. Design a kernel module that creates a proc file named /proc/seconds
that reports the number of elapsed seconds since the kernel module was
loaded. This will involve using the value of jiffies as well as the HZ
rate. When a user enters the command
<br> `cat /proc/seconds` <br>
your kernel module will report the number of seconds that have
elapsed since the kernel module was first loaded. Be sure to remove
/proc/seconds when the module is removed.

# Follow the steps
Follow these step to load kernel module in the kernel. <br>
**Load kernel module in a virtual machine otherwise this can crash your machine.**
## 1. Load the Module

    sudo insmod simple.ko
    
## 2. Verify it is Loaded

    lsmod | grep simple
    
## 3. Read the Kernel Output

    sudo dmesg | tail -n 5
    
## 4. Remove the Module

    sudo rmmod simple
    
## 5. Verify it is Removed

    lsmod | grep simple
    
    // or you can also verify through kernel log buffer 
    
    sudo dmesg | grep simple
    
