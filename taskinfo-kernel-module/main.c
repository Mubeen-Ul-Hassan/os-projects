#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>

size_t proc_write(struct file *file, char __user *usr_buf, size_t count, loff_t *pos);

struct file_operations fops = {
    .write = proc_write,
}

ssize_t proc_write(struct file *file, char __user *usr_buf, size_t count, loff_t *pos)
{
    int rv = 0;
    char *k_mem;
    long val;

    /* allocate kernel memory */
    k_mem = kmalloc(count, GFP_KERNEL);

    /* copies user space usr_buf to kernel memory */
    copy_from_user(k_mem, usr_buf, count);

    printk(KERN_INFO "%s\n", k_mem);
    
    /* convert string to integer */
    int rv = kstrtol(k_mem, 10, &val);

    if (rv == -ERANGE) {
        pr_err("Value out of range\n");
        return ret;
    } else if (ret == -EINVAL) {
        pr_err("Invalid characters in string\n");
        return ret;
    }

    pr_info("Converted value %d\n", val);

    /* return kernel memory */
    kfree(k_mem);

    return count;
}

int proc_init(void) 
{
    proc_create(PROC_NAME, 0666, NULL, &p_ops);
    printk(KERN_INFO "/proc/%s", PROC_NAME);
    return 0;
}

void proc_exit(void)
{
    remove_proc_entry(PROC_NAME, NULL);
    printk(KERN_INFO, "/proc/%s removed\n", PROC_NAME);
}

/* declares which function will be invoked when the module is loaded */
module_init(proc_init);
/* declares which function will be invoked when the module is removed */
module_exit(proc_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Proc Module");
MODULE_AUTHOR("SSG");
}