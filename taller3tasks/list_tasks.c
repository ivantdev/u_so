#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>

int list_task_init(void);
void list_task_exit(void);

struct task_struct *task;

int list_task_init(void) {
    printk(KERN_INFO "Loading Kernel module: List tasks\n");
    for_each_process(task) {
        printk(KERN_INFO "Task: pid=%d ppid=%d command=%s state=%ld\n",
            task->pid, task->real_parent->pid, task->comm, task->__state);
    }
    return 0;
}

void list_task_exit(void) {
    printk(KERN_INFO "Removing Kernel module: List tasks\n");
}

module_init(list_task_init);
module_exit(list_task_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("List tasks - linear");
MODULE_AUTHOR("Ivan Castellanos");