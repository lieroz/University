#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");

extern char *export_char;
extern int export_int;
extern char *even_or_odd(int num);
extern int factorial(int num);
extern int return_zero(void);

static int __init md2_init(void)
{
    printk(KERN_INFO "Module 2 is loaded.\n");

    printk(KERN_INFO "MD2: Export char* from MD1 - %s.\n", export_char);
    printk(KERN_INFO "MD2: Export int from MD1 - %d.\n", export_int);

    printk(KERN_INFO "MD2: Function 'even_or_odd(2)' from MD1 return %s.\n", even_or_odd(2));
    printk(KERN_INFO "MD2: Function 'even_or_odd(3)' from MD1 return %s.\n", even_or_odd(3));

    printk(KERN_INFO "MD2: Function 'factorial(0)' from MD1 return %d.\n", factorial(0));
    printk(KERN_INFO "MD2: Function 'factorial(5)' from MD1 return %d.\n", factorial(5));

    printk(KERN_INFO "MD2: Function 'return_zero' from MD1 return %d.\n", return_zero());

    return 0;
}

static void __exit md2_cleanup(void)
{
    printk(KERN_INFO "Module 2 is unloaded.\n");
}

module_init(md2_init);
module_exit(md2_cleanup);
