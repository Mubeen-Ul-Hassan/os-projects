#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/jiffies.h>

#define BUFFER_SIZE 128
#define PROC_NAME "jiffies"

static ssize_t proc_read(struct file *file, char __user *usr_buf, size_t count, loff_t *pos);

static struct proc_ops p_ops = {
	.proc_read = proc_read,
};

/* This function is called when the /proc/jiffies file is read */
static ssize_t proc_read(struct file *file, char __user *usr_buf, size_t count, loff_t *pos)
{
	int rv = 0;
	char buffer[BUFFER_SIZE];
	static int completed = 0;

	if (completed) {
		completed = 0;
		return 0;
	}

	completed = 1;
	rv = sprintf(buffer, "Current jiffies: %lu\n", jiffies);

	/* copies kernel space buffer to user space usr_buf */
	if (copy_to_user(usr_buf, buffer, rv)) {
		return -EFAULT;
	}

	return rv;
}

int proc_init(void)
{
	proc_create(PROC_NAME, 0666, NULL, &p_ops);
	printk(KERN_INFO "/proc/%s created\n", PROC_NAME);
	return 0;
}

void proc_exit(void)
{
	remove_proc_entry(PROC_NAME, NULL);
	printk(KERN_INFO "/proc/%s removed\n", PROC_NAME);
}

module_init(proc_init);
module_exit(proc_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Proc Module");
MODULE_AUTHOR("SGG");
