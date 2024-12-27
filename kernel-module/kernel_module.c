#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

#include <linux/cdev.h>
#include <linux/fs.h>

#include <linux/sched.h>
#include <linux/seq_file.h>

#define MAX_BUFFER_SIZE 16384  

static struct cdev tasks_cdev;

static char kernel_data[MAX_BUFFER_SIZE];

int buffer_len = 0;


static ssize_t tasks_dev_read(struct file *file, char __user *buf, size_t len, loff_t *offset)
{
    ssize_t bytes_read = 0;
    size_t remaining_data;
    
    remaining_data = buffer_len - *offset;

    if (remaining_data <= 0) {
        pr_info("Kernel UI: No more data to read, end of file.\n");
        return 0;
    }

    len = min(len, remaining_data);

    pr_info("Kernel UI: Sending %ld bytes to user-space.\n", len);

    if (copy_to_user(buf, kernel_data + *offset, len)) {
        pr_err("Kernel UI: Failed to send data to user-space.\n");
        return -EFAULT;
    }

    *offset += len;
    bytes_read = len;

    pr_info("Kernel UI: Sent %ld bytes to user-space.\n", bytes_read);
    return bytes_read;
}

static int tasks_dev_release(struct inode *inode, struct file *file) {
    printk(KERN_INFO "Kernel UI: Device closed.\n");
    return 0;
}

static int tasks_dev_open(struct inode *inodep, struct file *filep) {
    printk(KERN_INFO "Device opened\n");
    pr_info("Kernel UI: Starting to collect task data...\n");
    buffer_len=0;
    rcu_read_lock();

    struct task_struct *task;
    for_each_process(task) {
        pr_info("Kernel UI: Collecting info for task PID %d, Name: %s\n", task->pid, task->comm);

        buffer_len += snprintf(kernel_data + buffer_len, MAX_BUFFER_SIZE - buffer_len,
                               "Name: %s\n", task->comm);
        buffer_len += snprintf(kernel_data + buffer_len, MAX_BUFFER_SIZE - buffer_len,
                               "Tgid: %d\n", task->tgid);
        buffer_len += snprintf(kernel_data + buffer_len, MAX_BUFFER_SIZE - buffer_len,
                               "Pid: %d\n", task->pid);

        if (task->real_parent) {
            buffer_len += snprintf(kernel_data + buffer_len, MAX_BUFFER_SIZE - buffer_len,
                                   "PPid: %d\n", task->real_parent->pid);
        } else {
            buffer_len += snprintf(kernel_data + buffer_len, MAX_BUFFER_SIZE - buffer_len,
                                   "PPid: NULL (real_parent is NULL)\n");
        }

        if (task->cred) {
            buffer_len += snprintf(kernel_data + buffer_len, MAX_BUFFER_SIZE - buffer_len,
                                   "Uid: %d %d %d %d\n",
                                   task->cred->uid.val, task->cred->euid.val,
                                   task->cred->suid.val, task->cred->fsuid.val);
            buffer_len += snprintf(kernel_data + buffer_len, MAX_BUFFER_SIZE - buffer_len,
                                   "Gid: %d %d %d %d\n",
                                   task->cred->gid.val, task->cred->egid.val,
                                   task->cred->sgid.val, task->cred->fsgid.val);
        } else {
            buffer_len += snprintf(kernel_data + buffer_len, MAX_BUFFER_SIZE - buffer_len,
                                   "Uid/Gid: NULL (cred is NULL)\n");
        }

        if (task->mm) {
            buffer_len += snprintf(kernel_data + buffer_len, MAX_BUFFER_SIZE - buffer_len,
                                   "VmSize: %lu kB\n", task->mm->total_vm * PAGE_SIZE / 1024);
        } else {
            buffer_len += snprintf(kernel_data + buffer_len, MAX_BUFFER_SIZE - buffer_len,
                                   "VmSize: NULL (mm_struct is NULL)\n");
        }

        if (task->signal) {
            buffer_len += snprintf(kernel_data + buffer_len, MAX_BUFFER_SIZE - buffer_len,
                                   "Threads: %d\n", task->signal->nr_threads);
        } else {
            buffer_len += snprintf(kernel_data + buffer_len, MAX_BUFFER_SIZE - buffer_len,
                                   "Threads: NULL (signal is NULL)\n");
        }

        buffer_len += snprintf(kernel_data + buffer_len, MAX_BUFFER_SIZE - buffer_len,
                               "Voluntary context switches: %lu\n", task->nvcsw);
        buffer_len += snprintf(kernel_data + buffer_len, MAX_BUFFER_SIZE - buffer_len,
                                       "Nonvoluntary context switches: %lu\n", task->nivcsw);
        
        
        buffer_len += snprintf(kernel_data + buffer_len, MAX_BUFFER_SIZE - buffer_len,
                               "User time (utime): %llu \n", task->utime);
        buffer_len += snprintf(kernel_data + buffer_len, MAX_BUFFER_SIZE - buffer_len,
                               "System time (stime): %llu \n", task->stime);
 
        if (buffer_len >= MAX_BUFFER_SIZE) {
            pr_warn("Kernel UI: Buffer full, stopping data collection.\n");
            break;
        }
    }

    rcu_read_unlock();

    return 0;
}


static struct file_operations tasks_fops = {
    .read = tasks_dev_read,
    .release = tasks_dev_release,
    .open = tasks_dev_open,
};

static int __init kerenl_module_init(void){

    pr_info("kerenl_module_init -> initialized\n");
    
    int major_number = register_chrdev(0, "kernel_tasks",&tasks_fops);

    if(major_number < 0){
        pr_info("error while creating character dev\n");
    }

    cdev_init(&tasks_cdev, &tasks_fops);
    tasks_cdev.owner = THIS_MODULE;

    if(cdev_add(&tasks_cdev, major_number, 1)< 0){
        unregister_chrdev(major_number, "kernel_tasks");
        pr_info("error while creating character dev\n");
        return -1;
    }


    pr_info("%i\n", major_number);


    return 0;
}

static void __exit kerenl_module_exit(void){
    pr_info("Module removed.\n");
} 

module_init(kerenl_module_init);
module_exit(kerenl_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Abdelrahman Khalifa");
MODULE_DESCRIPTION("gather important kernel internals data such as CPU usage, memory statistics, and task management details.");

