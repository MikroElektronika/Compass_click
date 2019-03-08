/*
    __compass_driver.c

-----------------------------------------------------------------------------

  This file is part of mikroSDK.

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

#include "__compass_driver.h"
#include "__compass_hal.c"

/* ------------------------------------------------------------------- MACROS */

const uint8_t _COMPASS_CTRL_REG1 = 0x20;
const uint8_t _COMPASS_CTRL_REG2 = 0x21;
const uint8_t _COMPASS_CTRL_REG3 = 0x22;
const uint8_t _COMPASS_CTRL_REG4 = 0x23;
const uint8_t _COMPASS_CTRL_REG5 = 0x24;
const uint8_t _COMPASS_CTRL_REG6 = 0x25;
const uint8_t _COMPASS_FIFO_CTRL_REG = 0x2E;
const uint8_t _COMPASS_STATUS_REG = 0x27;
const uint8_t _COMPASS_INT1_CFG = 0x30;
const uint8_t _COMPASS_INT2_CFG = 0x34;

const uint8_t _COMPASS_CRA_REG = 0x00;
const uint8_t _COMPASS_CRB_REG = 0x01;
const uint8_t _COMPASS_MR_REG  = 0x02;
const uint8_t _COMPASS_SR_REG  = 0x09;

const uint8_t _COMPASS_IRA_REG = 0x0A;
const uint8_t _COMPASS_IRB_REG = 0x0B;
const uint8_t _COMPASS_IRC_REG = 0x0C;

const uint8_t _COMPASS_OUT_ACCEL_X_LOW  = 0x28;
const uint8_t _COMPASS_OUT_ACCEL_X_HIGH = 0x29;
const uint8_t _COMPASS_OUT_ACCEL_Y_LOW  = 0x2A;
const uint8_t _COMPASS_OUT_ACCEL_Y_HIGH = 0x2B;
const uint8_t _COMPASS_OUT_ACCEL_Z_LOW  = 0x2C;
const uint8_t _COMPASS_OUT_ACCEL_Z_HIGH = 0x2D;

const uint8_t _COMPASS_OUT_MAGNET_X_HIGH = 0x03;
const uint8_t _COMPASS_OUT_MAGNET_X_LOW  = 0x04;
const uint8_t _COMPASS_OUT_MAGNET_Z_HIGH = 0x05;
const uint8_t _COMPASS_OUT_MAGNET_Z_LOW  = 0x06;
const uint8_t _COMPASS_OUT_MAGNET_Y_HIGH = 0x07;
const uint8_t _COMPASS_OUT_MAGNET_Y_LOW  = 0x08;

const uint8_t _COMPASS_TEMP_OUT_HIGH = 0x31;
const uint8_t _COMPASS_TEMP_OUT_LOW  = 0x32;

/* ---------------------------------------------------------------- VARIABLES */

#ifdef   __COMPASS_DRV_I2C__
static uint8_t accel_slaveAddress;
static uint8_t magnet_slaveAddress;
static uint8_t _slaveAddress;
#endif

/* -------------------------------------------- PRIVATE FUNCTION DECLARATIONS */



/* --------------------------------------------- PRIVATE FUNCTION DEFINITIONS */



/* --------------------------------------------------------- PUBLIC FUNCTIONS */

#ifdef   __COMPASS_DRV_SPI__

void compass_spiDriverInit(T_COMPASS_P gpioObj, T_COMPASS_P spiObj)
{
    hal_spiMap( (T_HAL_P)spiObj );
    hal_gpioMap( (T_HAL_P)gpioObj );
}

#endif
#ifdef   __COMPASS_DRV_I2C__

void compass_i2cDriverInit(T_COMPASS_P gpioObj, T_COMPASS_P i2cObj, uint8_t accel_slave, uint8_t magnet_slave)
{
    accel_slaveAddress = accel_slave;
    magnet_slaveAddress = magnet_slave;
    hal_i2cMap( (T_HAL_P)i2cObj );
    hal_gpioMap( (T_HAL_P)gpioObj );
}

#endif
#ifdef   __COMPASS_DRV_UART__

void compass_uartDriverInit(T_COMPASS_P gpioObj, T_COMPASS_P uartObj)
{
    hal_uartMap( (T_HAL_P)uartObj );
    hal_gpioMap( (T_HAL_P)gpioObj );
}

#endif
/* ----------------------------------------------------------- IMPLEMENTATION */

void compass_setSlaveAddress(uint8_t slave)
{
    _slaveAddress = slave;
}

void compass_writeByte(uint8_t reg, uint8_t _data)
{
    uint8_t writeReg[ 2 ];
    
    writeReg[ 0 ] = reg;
    writeReg[ 1 ] = _data;
    
    hal_i2cStart();
    hal_i2cWrite(_slaveAddress, writeReg, 2, END_MODE_STOP);
}

uint8_t compass_readByte(uint8_t reg)
{
    uint8_t writeReg[ 1 ];
    uint8_t readReg[ 1 ];

    writeReg[ 0 ] = reg;

    hal_i2cStart();
    hal_i2cWrite(_slaveAddress, writeReg, 1, END_MODE_RESTART);
    hal_i2cRead(_slaveAddress, readReg, 1, END_MODE_STOP);
    
    return readReg[ 0 ];
}
/******************************************************************************/
void compass_init()
{
    compass_setSlaveAddress(accel_slaveAddress);
    compass_writeByte(_COMPASS_CTRL_REG1, 0x27);
    compass_writeByte(_COMPASS_CTRL_REG4, 0x40);
    compass_writeByte(_COMPASS_CTRL_REG5, 0x40);
    compass_writeByte(_COMPASS_FIFO_CTRL_REG, 0x80);
    compass_setSlaveAddress(magnet_slaveAddress);
    compass_writeByte(_COMPASS_CRA_REG, 0x9C);
    compass_writeByte(_COMPASS_CRB_REG, 0x20);
    compass_writeByte(_COMPASS_MR_REG,  0x00);
    compass_writeByte(_COMPASS_IRA_REG, 0x48);
    compass_writeByte(_COMPASS_IRB_REG, 0x34);
    compass_writeByte(_COMPASS_IRC_REG, 0x33);
}

void compass_readAccelAxis(int16_t *x_axis, int16_t *y_axis, int16_t *z_axis)
{
    uint8_t _axis[ 6 ];

    compass_setSlaveAddress(accel_slaveAddress);
    
    _axis[ 0 ] = compass_readByte(_COMPASS_OUT_ACCEL_X_HIGH);
    _axis[ 1 ] = compass_readByte(_COMPASS_OUT_ACCEL_X_LOW);
    _axis[ 2 ] = compass_readByte(_COMPASS_OUT_ACCEL_Y_HIGH);
    _axis[ 3 ] = compass_readByte(_COMPASS_OUT_ACCEL_Y_LOW);
    _axis[ 4 ] = compass_readByte(_COMPASS_OUT_ACCEL_Z_HIGH);
    _axis[ 5 ] = compass_readByte(_COMPASS_OUT_ACCEL_Z_LOW);

    x_axis[ 0 ] = _axis[ 0 ];
    x_axis[ 0 ] <<= 8;
    x_axis[ 0 ] |= _axis[ 1 ];
    
    y_axis[ 0 ] = _axis[ 2 ];
    y_axis[ 0 ] <<= 8;
    y_axis[ 0 ] |= _axis[ 3 ];
    
    z_axis[ 0 ] = _axis[ 4 ];
    z_axis[ 0 ] <<= 8;
    z_axis[ 0 ] |= _axis[ 5 ];
}

void compass_readMagnetAxis(int16_t *x_axis, int16_t *y_axis, int16_t *z_axis)
{
    uint8_t _axis[ 6 ];

    compass_setSlaveAddress(magnet_slaveAddress);

    _axis[ 0 ] = compass_readByte(_COMPASS_OUT_MAGNET_X_HIGH);
    _axis[ 1 ] = compass_readByte(_COMPASS_OUT_MAGNET_X_LOW);
    _axis[ 2 ] = compass_readByte(_COMPASS_OUT_MAGNET_Y_HIGH);
    _axis[ 3 ] = compass_readByte(_COMPASS_OUT_MAGNET_Y_LOW);
    _axis[ 4 ] = compass_readByte(_COMPASS_OUT_MAGNET_Z_HIGH);
    _axis[ 5 ] = compass_readByte(_COMPASS_OUT_MAGNET_Z_LOW);

    x_axis[ 0 ] = _axis[ 0 ];
    x_axis[ 0 ] <<= 8;
    x_axis[ 0 ] |= _axis[ 1 ];

    y_axis[ 0 ] = _axis[ 2 ];
    y_axis[ 0 ] <<= 8;
    y_axis[ 0 ] |= _axis[ 3 ];

    z_axis[ 0 ] = _axis[ 4 ];
    z_axis[ 0 ] <<= 8;
    z_axis[ 0 ] |= _axis[ 5 ];
}

/* -------------------------------------------------------------------------- */
/*
  __compass_driver.c

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

3. All advertising materials mentioning features or use of this software
   must display the following acknowledgement:
   This product includes software developed by the MikroElektonika.

4. Neither the name of the MikroElektonika nor the
   names of its contributors may be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY MIKROELEKTRONIKA ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL MIKROELEKTRONIKA BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------------------- */