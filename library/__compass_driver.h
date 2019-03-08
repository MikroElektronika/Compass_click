/*
    __compass_driver.h

-----------------------------------------------------------------------------

  This file is part of mikroSDK.
  
  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

/**
@file   __compass_driver.h
@brief    Compass Driver
@mainpage Compass Click
@{

@image html libstock_fb_view.jpg

@}

@defgroup   COMPASS
@brief      Compass Click Driver
@{

| Global Library Prefix | **COMPASS** |
|:---------------------:|:-----------------:|
| Version               | **1.0.0**    |
| Date                  | **avg 2018.**      |
| Developer             | **Katarina Perendic**     |

*/
/* -------------------------------------------------------------------------- */

#include "stdint.h"

#ifndef _COMPASS_H_
#define _COMPASS_H_

/** 
 * @macro T_COMPASS_P
 * @brief Driver Abstract type 
 */
#define T_COMPASS_P    const uint8_t*

/** @defgroup COMPASS_COMPILE Compilation Config */              /** @{ */

//  #define   __COMPASS_DRV_SPI__                            /**<     @macro __COMPASS_DRV_SPI__  @brief SPI driver selector */
   #define   __COMPASS_DRV_I2C__                            /**<     @macro __COMPASS_DRV_I2C__  @brief I2C driver selector */                                          
// #define   __COMPASS_DRV_UART__                           /**<     @macro __COMPASS_DRV_UART__ @brief UART driver selector */ 

                                                                       /** @} */
/** @defgroup COMPASS_VAR Variables */                           /** @{ */

extern const uint8_t _COMPASS_CTRL_REG1;
extern const uint8_t _COMPASS_CTRL_REG2;
extern const uint8_t _COMPASS_CTRL_REG3;
extern const uint8_t _COMPASS_CTRL_REG4;
extern const uint8_t _COMPASS_CTRL_REG5;
extern const uint8_t _COMPASS_CTRL_REG6;
extern const uint8_t _COMPASS_FIFO_CTRL_REG;
extern const uint8_t _COMPASS_STATUS_REG;
extern const uint8_t _COMPASS_INT1_CFG;
extern const uint8_t _COMPASS_INT2_CFG;

extern const uint8_t _COMPASS_CRA_REG;
extern const uint8_t _COMPASS_CRB_REG;
extern const uint8_t _COMPASS_MR_REG ;
extern const uint8_t _COMPASS_SR_REG ;

extern const uint8_t _COMPASS_IRA_REG;
extern const uint8_t _COMPASS_IRB_REG;
extern const uint8_t _COMPASS_IRC_REG;

extern const uint8_t _COMPASS_OUT_ACCEL_X_LOW ;
extern const uint8_t _COMPASS_OUT_ACCEL_X_HIGH;
extern const uint8_t _COMPASS_OUT_ACCEL_Y_LOW ;
extern const uint8_t _COMPASS_OUT_ACCEL_Y_HIGH;
extern const uint8_t _COMPASS_OUT_ACCEL_Z_LOW ;
extern const uint8_t _COMPASS_OUT_ACCEL_Z_HIGH;
 
extern const uint8_t _COMPASS_OUT_MAGNET_X_HIGH;
extern const uint8_t _COMPASS_OUT_MAGNET_X_LOW ;
extern const uint8_t _COMPASS_OUT_MAGNET_Z_HIGH;
extern const uint8_t _COMPASS_OUT_MAGNET_Z_LOW ;
extern const uint8_t _COMPASS_OUT_MAGNET_Y_HIGH;
extern const uint8_t _COMPASS_OUT_MAGNET_Y_LOW ;

extern const uint8_t _COMPASS_TEMP_OUT_HIGH;
extern const uint8_t _COMPASS_TEMP_OUT_LOW ;


                                                                       /** @} */
#ifdef __cplusplus
extern "C"{
#endif

/** @defgroup COMPASS_INIT Driver Initialization */              /** @{ */

#ifdef   __COMPASS_DRV_SPI__
void compass_spiDriverInit(T_COMPASS_P gpioObj, T_COMPASS_P spiObj);
#endif
#ifdef   __COMPASS_DRV_I2C__
void compass_i2cDriverInit(T_COMPASS_P gpioObj, T_COMPASS_P i2cObj, uint8_t accel_slave, uint8_t magnet_slave);
#endif
#ifdef   __COMPASS_DRV_UART__
void compass_uartDriverInit(T_COMPASS_P gpioObj, T_COMPASS_P uartObj);
#endif

// GPIO Only Drivers - remove in other cases
void compass_gpioDriverInit(T_COMPASS_P gpioObj);
                                                                       /** @} */
/** @defgroup COMPASS_FUNC Driver Functions */                   /** @{ */

/**
 * @brief Functions for sets active slave address
 */
void compass_setSlaveAddress(uint8_t slave);

/**
 * @brief Functions for write one byte in register
 *
 * @param[in] reg    Register in which the data will be written
 * @param[in] _data  Data which be written in the register
 */
void compass_writeByte(uint8_t reg, uint8_t _data);

/**
 * @brief Functions for read byte from register
 *
 * @param[in] reg    Register which will be read
 * @retval one byte data which is read from the register
 */
uint8_t compass_readByte(uint8_t reg);

/**
 * @brief Functions for init chip
 */
void compass_init();

/**
 * @brief Functions for reads accel axis data
 *
 * @param[in] x_axis    Accel X axis
 * @param[in] y_axis    Accel Y axis
 * @param[in] z_axis    Accel Z axis
 *
 */
void compass_readAccelAxis(int16_t *x_axis, int16_t *y_axis, int16_t *z_axis);

/**
 * @brief Functions for reads magnet axis data
 *
 * @param[in] x_axis    Magnet X axis
 * @param[in] y_axis    Magnet Y axis
 * @param[in] z_axis    Magnet Z axis
 *
 */
void compass_readMagnetAxis(int16_t *x_axis, int16_t *y_axis, int16_t *z_axis);






                                                                       /** @} */
#ifdef __cplusplus
} // extern "C"
#endif
#endif

/**
    @example Click_Compass_STM.c
    @example Click_Compass_TIVA.c
    @example Click_Compass_CEC.c
    @example Click_Compass_KINETIS.c
    @example Click_Compass_MSP.c
    @example Click_Compass_PIC.c
    @example Click_Compass_PIC32.c
    @example Click_Compass_DSPIC.c
    @example Click_Compass_AVR.c
    @example Click_Compass_FT90x.c
    @example Click_Compass_STM.mbas
    @example Click_Compass_TIVA.mbas
    @example Click_Compass_CEC.mbas
    @example Click_Compass_KINETIS.mbas
    @example Click_Compass_MSP.mbas
    @example Click_Compass_PIC.mbas
    @example Click_Compass_PIC32.mbas
    @example Click_Compass_DSPIC.mbas
    @example Click_Compass_AVR.mbas
    @example Click_Compass_FT90x.mbas
    @example Click_Compass_STM.mpas
    @example Click_Compass_TIVA.mpas
    @example Click_Compass_CEC.mpas
    @example Click_Compass_KINETIS.mpas
    @example Click_Compass_MSP.mpas
    @example Click_Compass_PIC.mpas
    @example Click_Compass_PIC32.mpas
    @example Click_Compass_DSPIC.mpas
    @example Click_Compass_AVR.mpas
    @example Click_Compass_FT90x.mpas
*/                                                                     /** @} */
/* -------------------------------------------------------------------------- */
/*
  __compass_driver.h

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