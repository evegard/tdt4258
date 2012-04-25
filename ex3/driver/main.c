/*****************************************************************************
 *
 * Øving 3 uCSysDes, driverkoden
 *
 *****************************************************************************/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/ioport.h>
#include <asm/io.h>
#include <asm/uaccess.h>

#include "ap7000.h"
#include "led.h"
#include "button.h"

/* prototyper */

static int __init driver_init(void);
static void __exit driver_exit(void);
static int driver_open (struct inode *inode, struct file *filp);
static int driver_release (struct inode *inode, struct file *filp);
static ssize_t driver_read (struct file *filp, char __user *buff,
                                         size_t count, loff_t *offp);
static ssize_t driver_write (struct file *filp, const char __user *buff,
                                            size_t count, loff_t *offp);

/* fops-struct */

static struct file_operations driver_fops =
{
    .owner = THIS_MODULE,
    .read = driver_read,
    .write = driver_write,
    .open = driver_open,
    .release = driver_release
};

static struct cdev driver_cdev = {};

/* The driver's allocated device number. */
dev_t devicenum = 0;

/*****************************************************************************/
/* init-funksjon (kalles når modul lastes) */

static int __init driver_init (void)
{
    /* allokere device-nummer */
    alloc_chrdev_region(&devicenum, 0, 1, "stkboard");

    /* be om tilgang til I/O-porter */
    request_region(AVR32_PIOB_ADDRESS, 172, "stkboard");
    
    /* initialisere PIO-maskinvaren (som i øving 2) */
    led_init();
    led_update();
    btn_init();
 
    /* registrere device i systemet (må gjøres når alt annet er initialisert) */
    cdev_init(&driver_cdev, &driver_fops);
    driver_cdev.owner = THIS_MODULE;
    cdev_add(&driver_cdev, devicenum, 1);

    printk(KERN_INFO "STK board kernel module loaded");
    return 0;
}

/*****************************************************************************/
/* exit-funksjon (kalles når modul fjernes fra systemet) */

static void __exit driver_exit (void)
{
    cdev_del(&driver_cdev);
    release_region(AVR32_PIOB_ADDRESS, 172);
    unregister_chrdev_region(devicenum, 1);
    printk(KERN_INFO "STK board kernel module unloading");
}

/*****************************************************************************/
/* fops-funksjoner */

static int driver_open (struct inode *inode, struct file *filp)
{
    return 0;
}

/*---------------------------------------------------------------------------*/

static int driver_release (struct inode *inode, struct file *filp)
{
    return 0;
}

/*---------------------------------------------------------------------------*/

static ssize_t driver_read (struct file *filp, char __user *buff,
                            size_t count, loff_t *offp)
{
    char output;
    if (count == 0)
        return 0;
    output = btn_read();
    copy_to_user(buff, &output, 1);
    *offp += 1;
    return 1;
}

/*---------------------------------------------------------------------------*/

static ssize_t driver_write (struct file *filp, const char __user *buff,
                             size_t count, loff_t *offp)
{
    char input;
    if (count == 0)
        return 0;
    copy_from_user(&input, buff, 1);
    led_set_all(input);
    led_update();
    *offp += 1;
    return 1;
}

/*****************************************************************************/
/* modul-beskrivelsesmakroer */

module_init (driver_init);    /* angir hva som er init-funksjon */
module_exit (driver_exit);    /* angir hva som er exit-funksjon */

MODULE_LICENSE ("GPL");         /* programlisens for modulen */
MODULE_DESCRIPTION ("");        /* tekstlig beskrivelse */
MODULE_VERSION ("");                /* versjonsnummer */
MODULE_AUTHOR ("");                 /* forfatter(e) */

