#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/workqueue.h>

static struct workqueue_struct *my_wq;

typedef struct {
    struct work_struct my_work;
    int x;
} my_work_t;

my_work_t *work;

static void my_wq_function(struct work_struct *work)
{
    my_work_t *my_work = (my_work_t *)work;
    printk("my_work.x %d\n", my_work->x);
    kfree((void*)work);
    return;
}

static irqreturn_t irq_handler(int irq, void *dev_id)
{
    static int count = 0;
    static unsigned char scancode;
    scancode = inb(0x60);

    if (0x1E == scancode) {
        count++;
        printk("Keyboard key 'a' pressed %d times\n", count);

        if (my_wq) {
            work = (my_work_t *)kmalloc(sizeof(my_work_t), GFP_KERNEL);
            if (work) {
                INIT_WORK((struct work_struct *)work, my_wq_function);
                work->x = 1;
                int ret = queue_work(my_wq, (struct work_struct *)work);
            }
        }
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
    my_wq = create_workqueue("my_queue");
    printk(KERN_INFO "WORKQUEUE_START");
    return res;
}

static void __exit stop(void)
{
    flush_workqueue(my_wq);
    destroy_workqueue(my_wq);
    free_irq(1, &context);
    printk(KERN_INFO "WORKQUEUE_STOP");
}

MODULE_LICENSE("GPL");

module_init(start);
module_exit(stop);
