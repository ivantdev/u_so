#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/hash.h>
#include <linux/gcd.h>
#include <linux/jiffies.h>

#define ul unsigned long

ul start_jiffies;

/* is called when the module is loaded. */
int simple_init(void) {
    start_jiffies = get_jiffies_64();

    printk(KERN_INFO "Loading Kernel Module\n");
    printk(KERN_INFO "Golden ration prime: %lu\n", GOLDEN_RATIO_PRIME);
    printk(KERN_INFO "HZ: %lu\n", HZ);

    return 0;
}

/* is called when the module is removed. */
void simple_exit(void) {
    ul a = 3300;
    ul b = 24;
    printk(KERN_INFO "GCD(%lu, %lu) = %lu\n", a, b, gcd(a, b));

    ul seconds = (get_jiffies_64() - start_jiffies) / HZ;
    printk(KERN_INFO "Loaded time (seconds): %lu\n", seconds);
    
    printk(KERN_INFO "Removing Kernel Module\n");
}

/* macros for registering the module entry and exit points. */
module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("Ivan Castellanos");
