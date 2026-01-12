#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("You");
MODULE_DESCRIPTION("A simple Linux char driver");
MODULE_VERSION("0.1");

#define DEVICE_NAME "hello_dev"

static int major_num;

static int dev_open(struct inode *inodep, struct file *filep)
{
    printk(KERN_INFO "Hello device opened\n");
    return 0;
}

static int dev_release(struct inode *inodep, struct file *filep)
{
    printk(KERN_INFO "Hello device closed\n");
    return 0;
}

static ssize_t dev_read(struct file *filep, char __user *buffer, size_t len, loff_t *offset)
{
    char message[] = "Hello from kernel!\n";
    int message_len = strlen(message);
    int bytes_to_copy;
    
    if (*offset >= message_len)
        return 0;
    
    bytes_to_copy = min((int)len, message_len - (int)*offset);
    
    if (copy_to_user(buffer, message + *offset, bytes_to_copy))
        return -EFAULT;
    
    *offset += bytes_to_copy;
    
    return bytes_to_copy;
}

static struct file_operations fops = {
    .open = dev_open,
    .read = dev_read,
    .release = dev_release,
};

static int __init hello_init(void)
{
    printk(KERN_INFO "Hello driver initializing\n");
    
    major_num = register_chrdev(0, DEVICE_NAME, &fops);
    if (major_num < 0) {
        printk(KERN_ALERT "Failed to register device\n");
        return major_num;
    }
    
    printk(KERN_INFO "Hello driver registered with major number %d\n", major_num);
    return 0;
}

static void __exit hello_exit(void)
{
    unregister_chrdev(major_num, DEVICE_NAME);
    printk(KERN_INFO "Hello driver unregistered\n");
}

module_init(hello_init);
module_exit(hello_exit);
