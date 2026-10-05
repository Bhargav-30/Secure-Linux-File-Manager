#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/mutex.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "slf_audit"
#define CLASS_NAME "slf"
#define BUFFER_SIZE 256

static dev_t device_number;
static struct cdev slf_cdev;
static struct class *slf_class;
static struct device *slf_device;

static char audit_buffer[BUFFER_SIZE];
static size_t audit_length;

static DEFINE_MUTEX(audit_mutex);

static int slf_open(struct inode *inode, struct file *file)
{
    pr_info("slf_audit: device opened\n");
    return 0;
}

static int slf_release(struct inode *inode, struct file *file)
{
    pr_info("slf_audit: device closed\n");
    return 0;
}

static ssize_t slf_write(
    struct file *file,
    const char __user *buffer,
    size_t count,
    loff_t *offset)
{
    size_t length;

    if (count == 0)
        return 0;

    length = min(count, (size_t)(BUFFER_SIZE - 1));

    if (mutex_lock_interruptible(&audit_mutex))
        return -ERESTARTSYS;

    memset(audit_buffer, 0, BUFFER_SIZE);

    if (copy_from_user(audit_buffer, buffer, length)) {
        mutex_unlock(&audit_mutex);
        return -EFAULT;
    }

    audit_buffer[length] = '\0';
    audit_length = length;

    pr_info("slf_audit: %s", audit_buffer);

    mutex_unlock(&audit_mutex);

    return length;
}

static ssize_t slf_read(
    struct file *file,
    char __user *buffer,
    size_t count,
    loff_t *offset)
{
    if (*offset >= audit_length)
        return 0;

    if (mutex_lock_interruptible(&audit_mutex))
        return -ERESTARTSYS;

    if (count > audit_length - *offset)
        count = audit_length - *offset;

    if (copy_to_user(
            buffer,
            audit_buffer + *offset,
            count)) {

        mutex_unlock(&audit_mutex);
        return -EFAULT;
    }

    *offset += count;

    mutex_unlock(&audit_mutex);

    return count;
}

static const struct file_operations slf_fops = {
    .owner = THIS_MODULE,
    .open = slf_open,
    .release = slf_release,
    .read = slf_read,
    .write = slf_write,
};

static int __init slf_init(void)
{
    int result;

    result = alloc_chrdev_region(
        &device_number,
        0,
        1,
        DEVICE_NAME
    );

    if (result < 0) {
        pr_err("slf_audit: failed to allocate device number\n");
        return result;
    }

    cdev_init(&slf_cdev, &slf_fops);
    slf_cdev.owner = THIS_MODULE;

    result = cdev_add(
        &slf_cdev,
        device_number,
        1
    );

    if (result < 0) {
        pr_err("slf_audit: failed to add cdev\n");
        unregister_chrdev_region(device_number, 1);
        return result;
    }

    slf_class = class_create(CLASS_NAME);

    if (IS_ERR(slf_class)) {
        pr_err("slf_audit: failed to create class\n");
        cdev_del(&slf_cdev);
        unregister_chrdev_region(device_number, 1);
        return PTR_ERR(slf_class);
    }

    slf_device = device_create(
        slf_class,
        NULL,
        device_number,
        NULL,
        DEVICE_NAME
    );

    if (IS_ERR(slf_device)) {
        pr_err("slf_audit: failed to create device\n");
        class_destroy(slf_class);
        cdev_del(&slf_cdev);
        unregister_chrdev_region(device_number, 1);
        return PTR_ERR(slf_device);
    }

    mutex_init(&audit_mutex);
    audit_length = 0;

    pr_info("slf_audit: driver loaded successfully\n");
    pr_info("slf_audit: device created as /dev/%s\n", DEVICE_NAME);

    return 0;
}

static void __exit slf_exit(void)
{
    device_destroy(slf_class, device_number);
    class_destroy(slf_class);
    cdev_del(&slf_cdev);
    unregister_chrdev_region(device_number, 1);

    pr_info("slf_audit: driver unloaded\n");
}

module_init(slf_init);
module_exit(slf_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Bhargav Raj");
MODULE_DESCRIPTION(
    "Secure Linux File Manager Audit Character Device Driver"
);
MODULE_VERSION("1.0");
