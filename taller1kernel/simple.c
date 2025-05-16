#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/hash.h>
#include <linux/gcd.h>

#define ul unsigned long
/* is called when the module is loaded. */
int simple_init(void)
{
    printk(KERN_INFO "Loading Kernel Module\n");
    printk(KERN_INFO "%lu\n", GOLDEN_RATIO_PRIME);
    return 0;
}

/* is called when the module is removed. */
void simple_exit(void)
{
    ul a = 3300;
    ul b = 24;

    printk(KERN_INFO "GCD(%lu, %lu) = %lu\n", a, b, gcd(a, b));
    printk(KERN_INFO "Removing Kernel Module\n");
}

/* macros for registering the module entry and exit points. */
module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");
