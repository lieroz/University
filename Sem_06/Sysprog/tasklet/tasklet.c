#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/interrupt.h>

char my_tasklet_data[] = "my_tasklet_function was called";

void my_tasklet_function(unsigned long data)
{
    printk("%s\n", (char *)data);
}

DECLARE_TASKLET(my_tasklet, my_tasklet_function, (unsigned long) &my_tasklet_data);

static irqreturn_t irq_handler(int irq, void *dev_id)
{
    static int count = 0;
    static unsigned char scancode;
    scancode = inb(0x60);

    if (0x1E == scancode) {
        count++;
        printk("Keyboard key 'a' pressed %d times\n", count);
        tasklet_schedule(&my_tasklet);
    }

    return IRQ_HANDLED;
}

typedef struct {
    int irq;
    char *name;
} context_t;

static context_t context = {
    .irq = 1,
    .name = "context_example"
};

static int __init start(void)
{
    int res = request_irq(context.irq, irq_handler, IRQF_SHARED, context.name, &context);
    printk(KERN_INFO "TASKLET_START");
    return res;
}

static void __exit stop(void)
{
    tasklet_kill(&my_tasklet);
    free_irq(1, &context);
    printk(KERN_INFO "TASKLET_STOP");
}

MODULE_LICENSE("GPL");

module_init(start);
module_exit(stop);
