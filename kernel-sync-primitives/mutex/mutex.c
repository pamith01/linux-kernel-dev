#include "mutex.h"

//Declarations
int kern_thread (void *args);
static int __init kthread_init(void);
static void __exit kthread_exit(void);

int kern_thread(void *args)
{
    int data = *(int*)args;

    while (kthread_should_stop() == 0)
    {
        mutex_lock(&m_lock);
        dev_print("Thread %d acquired the lock\n", data);
        for (int i=0;i<5;i++)
        {
            dev_print("%d\n", global_buffer[i]);
        }
        mutex_unlock(&m_lock);
        msleep(5*1000);
    }
}

static int __init kthread_init(void)
{
    return 0;
}

static void __exit kthread_exit(void)
{

}

module_init(kthread_init);
module_exit(kthread_exit);

MODULE_LICENSE("GPL")
MODULE_AUTHOR("Pamith")
MODULE_DESCRIPTION("Mutex Lock Implementation")