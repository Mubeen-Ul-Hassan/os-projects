# Follow the steps
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
    
