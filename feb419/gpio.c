nclude <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>                 // Required for the GPIO functions
#include <linux/interrupt.h>            // Required for the IRQ code

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Derek Molloy");
MODULE_DESCRIPTION("A Button/LED test driver for the BBB");
MODULE_VERSION("0.1");

static unsigned int gpioLED = 49;       ///< hard coding the LED gpio for this example to P9_23 (GPIO49)
static unsigned int gpioButton = 115;   ///< hard coding the button gpio for this example to P9_27 (GPIO115)
static unsigned int irqNumber;          ///< Used to share the IRQ number within this file
static unsigned int numberPresses = 0;  ///< For information, store the number of button presses
static bool     ledOn = 0;          ///< Is the LED on or off? Used to invert its state (off by default)
tatic irq_handler_t  ebbgpio_irq_handler(unsigned int irq, void *dev_id, struct pt_regs *regs);

/** @brief The LKM initialization function
 *  *  The static keyword restricts the visibility of the function to within this C file. The __init
 *   *  macro means that for a built-in driver (not a LKM) the function is only used at initialization
 *    *  time and that it can be discarded and its memory freed up after that point. In this example this
 *     *  function sets up the GPIOs and the IRQ
 *      *  @return returns 0 if successful
 *       */
static int __init ebbgpio_init(void){
     int result = 0;
        printk(KERN_INFO "GPIO_TEST: Initializing the GPIO_TEST LKM\n");
           // Is the GPIO a valid GPIO number (e.g., the BBB has 4x32 but not all available)
           //    if (!gpio_is_valid(gpioLED)){
           //          printk(KERN_INFO "GPIO_TEST: invalid LED GPIO\n");
           //                return -ENODEV;
           //                   }
           //                      // Going to set up the LED. It is a GPIO in output mode and will be on by default
           //                         ledOn = true;
           //                            gpio_request(gpioLED, "sysfs");          // gpioLED is hardcoded to 49, request it
           //                               gpio_direction_output(gpioLED, ledOn);   // Set the gpio to be in output mode and on
           //                               // gpio_set_value(gpioLED, ledOn);          // Not required as set by line above (here for reference)
           //                                  gpio_export(gpioLED, false);             // Causes gpio49 to appear in /sys/class/gpio
           //                                                       // the bool argument prevents the direction from being changed
           //                                                          gpio_request(gpioButton, "sysfs");       // Set up the gpioButton
           //                                                             gpio_direction_input(gpioButton);        // Set the button GPIO to be an input
           //                                                                gpio_set_debounce(gpioButton, 200);      // Debounce the button with a delay of 200ms
           //                                                                   gpio_export(gpioButton, false);          // Causes gpio115 to appear in /sys/class/gpio
           //
