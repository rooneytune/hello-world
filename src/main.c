#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/device.h>
#include <zephyr/logging/log.h>
#include <zephyr/display/cfb.h>
#include "button.h"
#include <zephyr/drivers/sensor.h>

/* Definition used in Part 1
static const struct device *gpio_ct_dev =
   DEVICE_DT_GET(DT_NODELABEL(gpio0)) ;
  static const int BUILTIN_LED_PIN = 2;
*/
LOG_MODULE_REGISTER(main);
// Declaration using Device tree struct
static const struct gpio_dt_spec led =
    GPIO_DT_SPEC_GET(DT_NODELABEL(blinking_led), gpios);

//static const struct device *display = DEVICE_DT_GET(DT_NODELABEL(ssd1306));

static char *helper_button_evt_str(enum button_evt evt)
{
  switch (evt)
  {
  case BUTTON_EVT_PRESSED:
    return "Pressed";
  case BUTTON_EVT_RELEASED:
    return "Released";
  default:
    return "Unknown";
  }
}

 static void button_event_handler(enum button_evt evt)
{
  printk("Button event: %s\n", helper_button_evt_str(evt));
  switch (evt)
  {
  case BUTTON_EVT_PRESSED:
    gpio_pin_toggle_dt(&led);
    break;

  default:
    break;
  }
}



void setupLeds()
{
  //  if (!device_is_ready(gpio_ct_dev))
  printk("Initialising LEDs !\n");
  if (!device_is_ready(led.port))
  {
    return;
  }
  int ret;
  /*ret = gpio_pin_configure(gpio_ct_dev, BUILTIN_LED_PIN, GPIO_OUTPUT_ACTIVE);
   */
  ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
  if (ret != 0)
  {
    return;
  }
}
void setupButtons()
{
  int err = -1;

  printk("Initialising button !\n");

  err = button_init(button_event_handler);
  if (err)
  {
    printk("Button Init failed: %d\n", err);
    return;
  }

  printk("Init succeeded. Waiting for event...\n");
}

// bool setupDisplay(){
//   if (display==NULL){
//     LOG_ERR("Display device pointer is null");
//     return false;
//   }

//   if (!device_is_ready(display)){
//     LOG_ERR("Display device not ready");
//     return false;
//   }

//   int ret;
//   ret = cfb_framebuffer_init(display);
//   if (ret!=0){
//     LOG_ERR("Could not initialise the display");
//     return false;
//   }


//   return true;
// }

int main(void)
{

  /*-------------------
  -Setup
  ---------------------*/
  int ret;
  setupLeds();
  setupButtons();

  // if (setupDisplay()==true){
  //   ret = cfb_print(display,"Hello Rooney",0,0);
  //   if (ret!=0){
  //     LOG_ERR("could not print to display");
  //     return;
  //   }
  //   ret = cfb_framebuffer_finalize(display);
  //   if (ret!=0){
  //     LOG_ERR("could not finalise");
  //     return;
  //   }
  // }
  
 gpio_pin_set_dt(&led,0);
/*
  while (true)
  {
    // ret = gpio_pin_set_raw(gpio_ct_dev, BUILTIN_LED_PIN, 1);
    ret = gpio_pin_toggle_dt(&led);
    if (ret != 0)
    {
      return;
    }
    k_msleep(1000);

    //     ret = gpio_pin_set_raw(gpio_ct_dev, BUILTIN_LED_PIN, 0);
    // if (ret != 0)
    // {
    //   return;
    // }
    // k_msleep(1000);
  }
  */
}
