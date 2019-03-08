/*
Example for Compass Click

    Date          : avg 2018.
    Author        : Katarina Perendic

Test configuration CEC :
    
    MCU              : CEC1702
    Dev. Board       : Clicker 2 for CEC1702
    ARM Compiler ver : v6.0.0.0

---

Description :

The application is composed of three sections :

- System Initialization - Initializes I2C module and sets RST and INT pin as INPUT
- Application Initialization - Initialization driver init and init chip
- Application Task - (code snippet) - Read magnet axis data and accel axis data and logs data on USBUART every 1 sec.

*/

#include "Click_Compass_types.h"
#include "Click_Compass_config.h"

int16_t Accel_axis[ 3 ];
int16_t Magnet_axis[ 3 ];
char demoText[ 50 ];

void systemInit()
{
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_INT_PIN, _GPIO_INPUT );
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_RST_PIN, _GPIO_INPUT );
    mikrobus_i2cInit( _MIKROBUS1, &_COMPASS_I2C_CFG[0] );
    mikrobus_logInit( _MIKROBUS2, 9600 );
    mikrobus_logWrite("--- System init ---", _LOG_LINE);
    Delay_ms( 100 );
}

void applicationInit()
{
    compass_i2cDriverInit( (T_COMPASS_P)&_MIKROBUS1_GPIO, (T_COMPASS_P)&_MIKROBUS1_I2C, 0x19, 0x1E );
    compass_init();
}

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

void main()
{
    systemInit();
    applicationInit();

    while (1)
    {
            applicationTask();
    }
}