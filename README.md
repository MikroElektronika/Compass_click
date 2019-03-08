![MikroE](http://www.mikroe.com/img/designs/beta/logo_small.png)

---

# Compass Click

- **CIC Prefix**  : COMPASS
- **Author**      : Katarina Perendic
- **Verison**     : 1.0.0
- **Date**        : avg 2018.

---


### Software Support

We provide a library for the Compass Click on our [LibStock](https://libstock.mikroe.com/projects/view/562/compass-click) 
page, as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). The demo can run on all the main 
MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

**Library Description**

The library initializes and defines the I2C bus driver and drivers that offer a choice for writing data in register and reads data from register.
The library includes function for read X/Y/Z Accel and Magnet axis data.
The user also has the function for initializes chip .

Key functions :

- ``` void compass_init() ``` - Functions for init chip
- ``` void compass_readAccelAxis(int16_t *x_axis, int16_t *y_axis, int16_t *z_axis) ``` - Functions for reads accel axis data
- ``` void compass_readMagnetAxis(int16_t *x_axis, int16_t *y_axis, int16_t *z_axis) ``` - Functions for reads magnet axis data

**Examples Description**

The application is composed of three sections :

- System Initialization - Initializes I2C module and sets RST and INT pin as INPUT
- Application Initialization - Initialization driver init and init chip
- Application Task - (code snippet) - Read magnet axis data and accel axis data and logs data on USBUART every 1 sec.


```.c
void applicationTask()
{
   compass_readMagnetAxis(&Magnet_axis[0], &Magnet_axis[1], &Magnet_axis[2]);
   mikrobus_logWrite("Magnet axis -- X:", _LOG_TEXT);
   IntToStr(Magnet_axis[0], demoText);
   mikrobus_logWrite(demoText, _LOG_TEXT);
   mikrobus_logWrite(" Y:", _LOG_TEXT);
   IntToStr(Magnet_axis[1], demoText);
   mikrobus_logWrite(demoText, _LOG_TEXT);
   mikrobus_logWrite(" Z:", _LOG_TEXT);
   IntToStr(Magnet_axis[2], demoText);
   mikrobus_logWrite(demoText, _LOG_TEXT);
   mikrobus_logWrite(" ", _LOG_LINE);
   
   compass_readAccelAxis(&Accel_axis[0], &Accel_axis[1], &Accel_axis[2]);
   mikrobus_logWrite("Accel axis -- X:", _LOG_TEXT);
   IntToStr(Accel_axis[0], demoText);
   mikrobus_logWrite(demoText, _LOG_TEXT);
   mikrobus_logWrite(" Y:", _LOG_TEXT);
   IntToStr(Accel_axis[1], demoText);
   mikrobus_logWrite(demoText, _LOG_TEXT);
   mikrobus_logWrite(" Z:", _LOG_TEXT);
   IntToStr(Accel_axis[2], demoText);
   mikrobus_logWrite(demoText, _LOG_TEXT);
   mikrobus_logWrite(" ", _LOG_LINE);
   
   mikrobus_logWrite(" ", _LOG_LINE);
   Delay_ms( 1000 );
}
```

The full application code, and ready to use projects can be found on our 
[LibStock](https://libstock.mikroe.com/projects/view/562/compass-click) page.

Other mikroE Libraries used in the example:

- I2C

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.

---
---
