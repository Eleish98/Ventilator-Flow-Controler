/*
 * I2C_Manage.c
 *
 *  Created on: May 10, 2020
 *      Author: Ahmed_Saad
 */
//#define LCD_EX

//#define READ_EX

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_i2c.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/i2c.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"

#include"I2C_Manage.h"

uint32_t I2C_Bases[4] = {I2C0_BASE, I2C1_BASE, I2C2_BASE, I2C3_BASE};

//initialize I2C module 0
//Slightly modified version of TI's example code
void InitI2C(void)
{
  //  uint32_t    g_ui32SysClock;

  //  g_ui32SysClock = SysCtlClockFreqSet((SYSCTL_OSC_MAIN | SYSCTL_XTAL_25MHZ | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_320), 40000000);

    //enable I2C modules
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C2);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C3);

    //reset module
   // SysCtlPeripheralReset(SYSCTL_PERIPH_I2C0);

    //enable GPIO peripheral that contains I2C 0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    //enable GPIO peripheral that contains I2C 1
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    //enable GPIO peripheral that contains I2C 2
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    //enable GPIO peripheral that contains I2C 3
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);


    // Configure the pin muxing for I2C0 functions on port B2 and B3.
    GPIOPinConfigure(GPIO_PB2_I2C0SCL);
    GPIOPinConfigure(GPIO_PB3_I2C0SDA);

    // Select the I2C function for these pins.
    GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, GPIO_PIN_2);
    GPIOPinTypeI2C(GPIO_PORTB_BASE, GPIO_PIN_3);


    // Configure the pin muxing for I2C1 functions on port A6 and A7.
    GPIOPinConfigure(GPIO_PA6_I2C1SCL);
    GPIOPinConfigure(GPIO_PA7_I2C1SDA);

    // Select the I2C function for these pins.
    GPIOPinTypeI2CSCL(GPIO_PORTA_BASE, GPIO_PIN_6);
    GPIOPinTypeI2C(GPIO_PORTA_BASE, GPIO_PIN_7);


    // Configure the pin muxing for I2C2 functions on port E4 and E5.
    GPIOPinConfigure(GPIO_PE4_I2C2SCL);
    GPIOPinConfigure(GPIO_PE5_I2C2SDA);

    // Select the I2C function for these pins.
    GPIOPinTypeI2CSCL(GPIO_PORTE_BASE, GPIO_PIN_4);
    GPIOPinTypeI2C(GPIO_PORTE_BASE, GPIO_PIN_5);

    // Configure the pin muxing for I2C3 functions on port D0 and D1.
    GPIOPinConfigure(GPIO_PD0_I2C3SCL);
    GPIOPinConfigure(GPIO_PD1_I2C3SDA);

    // Select the I2C function for these pins.
    GPIOPinTypeI2CSCL(GPIO_PORTD_BASE, GPIO_PIN_0);
    GPIOPinTypeI2C(GPIO_PORTD_BASE, GPIO_PIN_1);





    // Enable and initialize the I2C0 master module.  Use the system clock for
    // the I2C0 module.  The last parameter sets the I2C data transfer rate.
    // If false the data rate is set to 100kbps and if true the data rate will
    // be set to 400kbps.
    I2CMasterInitExpClk(I2C0_BASE,SysCtlClockGet(), false);
    I2CMasterInitExpClk(I2C1_BASE,SysCtlClockGet(), false);
    I2CMasterInitExpClk(I2C2_BASE,SysCtlClockGet(), false);
    I2CMasterInitExpClk(I2C3_BASE,SysCtlClockGet(), false);

    //clear I2C FIFOs
    //HWREG(I2C0_BASE + I2C_O_FIFOCTL) = 80008000;
}

/*
void InitI2C1(void)
{

    //enable I2C module 0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C1);

    //enable GPIO peripheral that contains I2C 1
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    // Configure the pin muxing for I2C1 functions on port A6 and A7.
    GPIOPinConfigure(GPIO_PA6_I2C1SCL);
    GPIOPinConfigure(GPIO_PA7_I2C1SDA);

    // Select the I2C function for these pins.
    GPIOPinTypeI2CSCL(GPIO_PORTA_BASE, GPIO_PIN_6);
    GPIOPinTypeI2C(GPIO_PORTA_BASE, GPIO_PIN_7);


    // Enable and initialize the I2C1 master module.  Use the system clock for
    // the I2C0 module.  The last parameter sets the I2C data transfer rate.
    // If false the data rate is set to 100kbps and if true the data rate will
    // be set to 400kbps.
    I2CMasterInitExpClk(I2C1_BASE, SysCtlClockGet(), true);

    //clear I2C FIFOs
    //HWREG(I2C0_BASE + I2C_O_FIFOCTL) = 80008000;
}

void InitI2C2(void)
{

    //enable I2C module 0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C2);

    //enable GPIO peripheral that contains I2C 1
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

    // Configure the pin muxing for I2C1 functions on port A6 and A7.
    GPIOPinConfigure(GPIO_PE4_I2C2SCL);
    GPIOPinConfigure(GPIO_PE5_I2C2SDA);

    // Select the I2C function for these pins.
    GPIOPinTypeI2CSCL(GPIO_PORTE_BASE, GPIO_PIN_4);
    GPIOPinTypeI2C(GPIO_PORTE_BASE, GPIO_PIN_5);


    // Enable and initialize the I2C1 master module.  Use the system clock for
    // the I2C0 module.  The last parameter sets the I2C data transfer rate.
    // If false the data rate is set to 100kbps and if true the data rate will
    // be set to 400kbps.
    I2CMasterInitExpClk(I2C2_BASE, SysCtlClockGet(), true);

    //clear I2C FIFOs
    //HWREG(I2C0_BASE + I2C_O_FIFOCTL) = 80008000;
}

void InitI2C3(void)
{

    //enable I2C module 0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C3);

    //enable GPIO peripheral that contains I2C 1
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);

    // Configure the pin muxing for I2C1 functions on port A6 and A7.
    GPIOPinConfigure(GPIO_PD0_I2C3SCL);
    GPIOPinConfigure(GPIO_PD1_I2C3SDA);

    // Select the I2C function for these pins.
    GPIOPinTypeI2CSCL(GPIO_PORTD_BASE, GPIO_PIN_0);
    GPIOPinTypeI2C(GPIO_PORTD_BASE, GPIO_PIN_1);


    // Enable and initialize the I2C1 master module.  Use the system clock for
    // the I2C0 module.  The last parameter sets the I2C data transfer rate.
    // If false the data rate is set to 100kbps and if true the data rate will
    // be set to 400kbps.
    I2CMasterInitExpClk(I2C3_BASE, SysCtlClockGet(), true);

    //clear I2C FIFOs
    //HWREG(I2C0_BASE + I2C_O_FIFOCTL) = 80008000;
}
*/
//read specified register on slave device
uint32_t I2CReceiveOneByte(uint8_t I2C_ID, uint32_t slave_addr, uint8_t reg)
{

    uint32_t u32ErrorFlags = 0;
    uint32_t Base = I2C_Bases[I2C_ID];
    //specify that we are writing (a register address) to the
    //slave device
    I2CMasterSlaveAddrSet(Base, slave_addr, false);

    //specify register to be read
    I2CMasterDataPut(Base, reg);

    //send control byte and register address byte to slave device
    I2CMasterControl(Base, I2C_MASTER_CMD_BURST_SEND_START);

    //wait for MCU to finish transaction
    while(I2CMasterBusy(Base));

    u32ErrorFlags |= I2CMasterErr(Base);

    //specify that we are going to read from slave device
    I2CMasterSlaveAddrSet(Base, slave_addr, true);

    //send control byte and read from the register we
    //specified
    I2CMasterControl(Base, I2C_MASTER_CMD_SINGLE_RECEIVE);

    //wait for MCU to finish transaction
    while(I2CMasterBusy(Base));

    u32ErrorFlags |= I2CMasterErr(Base);

    //return data pulled from the specified register
    return I2CMasterDataGet(Base);
}


uint32_t I2CReceiveBytes(uint8_t I2C_ID, uint32_t slave_addr,uint8_t u8Command, uint8_t u8BytesNumber,uint8_t * RxBuffer)
{
    uint32_t u32ErrorFlags = 0;
    //initialize index into array
    uint8_t u8RxIndex = 1;
    uint32_t Base = I2C_Bases[I2C_ID];

    //specify that we are writing (a register address) to the
    //slave device
    I2CMasterSlaveAddrSet(Base, slave_addr, false);

    //specify register to be read
    I2CMasterDataPut(Base, u8Command);

    //send control byte and register address byte to slave device
    I2CMasterControl(Base, I2C_MASTER_CMD_BURST_SEND_START);

    //wait for MCU to finish transaction
    while(I2CMasterBusy(Base));

    u32ErrorFlags |= I2CMasterErr(Base);



    //specify that we are going to read from slave device
    I2CMasterSlaveAddrSet(Base, slave_addr, true);
    //if there is only one argument, we only need to use the
    //single send I2C function
    if(u8BytesNumber == 1)
    {
        //send control byte and read from the register we
        //specified
        I2CMasterControl(Base, I2C_MASTER_CMD_SINGLE_RECEIVE);

        //wait for MCU to finish transaction
        while(I2CMasterBusy(Base));

        // Save this bit Rx buffer
        RxBuffer[0] = I2CMasterDataGet(Base);

        u32ErrorFlags |= I2CMasterErr(Base);

    }
    else
    {

        //Initiate send of data from the MCU
          I2CMasterControl(Base, I2C_MASTER_CMD_BURST_RECEIVE_START);

          // Wait until MCU is done transferring.
          while(I2CMasterBusy(Base));

          // Save this bit Rx buffer
          RxBuffer[0] = I2CMasterDataGet(Base);

          u32ErrorFlags |= I2CMasterErr(Base);



          //send num_of_args-2 pieces of data, using the
          //BURST_SEND_CONT command of the I2C module
          while(u8RxIndex < (u8BytesNumber-1))
          {

              //send next data that was just placed into FIFO
              I2CMasterControl(Base, I2C_MASTER_CMD_BURST_RECEIVE_CONT);

              // Wait until MCU is done transferring.
              while(I2CMasterBusy(Base));

              // Save this bit Rx buffer
              RxBuffer[u8RxIndex] = I2CMasterDataGet(Base);

              u32ErrorFlags |= I2CMasterErr(Base);

              u8RxIndex++;

          }

          //send next data that was just placed into FIFO
          I2CMasterControl(Base, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);

          // Wait until MCU is done transferring.
          while(I2CMasterBusy(Base));

          // Save this bit Rx buffer
          RxBuffer[u8RxIndex] = I2CMasterDataGet(Base);

          u32ErrorFlags |= I2CMasterErr(Base);
    }

    return u32ErrorFlags;
}


#ifdef FEATURE_IMPLEMENTATION
//sends an I2C command to the specified slave
void I2CSend(uint8_t slave_addr, uint8_t num_of_args, ...)
{
    // Tell the master module what address it will place on the bus when
    // communicating with the slave.
    I2CMasterSlaveAddrSet(I2C0_BASE, slave_addr, false);

    //stores list of variable number of arguments
    va_list vargs;

    //specifies the va_list to "open" and the last fixed argument
    //so vargs knows where to start looking
    va_start(vargs, num_of_args);

    //put data to be sent into FIFO
    I2CMasterDataPut(I2C0_BASE, va_arg(vargs, uint32_t));

    //if there is only one argument, we only need to use the
    //single send I2C function
    if(num_of_args == 1)
    {
        //Initiate send of data from the MCU
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_SEND);

        // Wait until MCU is done transferring.
        while(I2CMasterBusy(I2C0_BASE));

        //"close" variable argument list
        va_end(vargs);
    }

    //otherwise, we start transmission of multiple bytes on the
    //I2C bus
    else
    {
        //Initiate send of data from the MCU
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);

        // Wait until MCU is done transferring.
        while(I2CMasterBusy(I2C0_BASE));

        //send num_of_args-2 pieces of data, using the
        //BURST_SEND_CONT command of the I2C module
        for(uint8_t i = 1; i < (num_of_args - 1); i++)
        {
            //put next piece of data into I2C FIFO
            I2CMasterDataPut(I2C0_BASE, va_arg(vargs, uint32_t));
            //send next data that was just placed into FIFO
            I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);

            // Wait until MCU is done transferring.
            while(I2CMasterBusy(I2C0_BASE));
        }

        //put last piece of data into I2C FIFO
        I2CMasterDataPut(I2C0_BASE, va_arg(vargs, uint32_t));
        //send next data that was just placed into FIFO
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
        // Wait until MCU is done transferring.
        while(I2CMasterBusy(I2C0_BASE));

        //"close" variable args list
        va_end(vargs);
    }
}
#endif
//sends an array of data via I2C to the specified slave
uint32_t I2CSendString(uint8_t I2C_ID, uint8_t slave_addr, uint8_t array[])
{
    uint32_t Base = I2C_Bases[I2C_ID];
    uint32_t u32ErrorFlags = 0;
    // Tell the master module what address it will place on the bus when
    // communicating with the slave.
    I2CMasterSlaveAddrSet(Base, slave_addr, false);

    //put data to be sent into FIFO
    I2CMasterDataPut(Base, array[0]);

    //if there is only one argument, we only need to use the
    //single send I2C function
    if(array[1] == 0xFF)
    {
        //Initiate send of data from the MCU
        I2CMasterControl(Base, I2C_MASTER_CMD_SINGLE_SEND);

        // Wait until MCU is done transferring.
        while(I2CMasterBusy(Base));

        u32ErrorFlags |= I2CMasterErr(Base);
    }

    //otherwise, we start transmission of multiple bytes on the
    //I2C bus
    else
    {
        //Initiate send of data from the MCU
        I2CMasterControl(Base, I2C_MASTER_CMD_BURST_SEND_START);

        // Wait until MCU is done transferring.
        while(I2CMasterBusy(Base));

        u32ErrorFlags |= I2CMasterErr(Base);

        //initialize index into array
        uint8_t i = 1;

        //send num_of_args-2 pieces of data, using the
        //BURST_SEND_CONT command of the I2C module
        while(array[i + 1] != 0XFF)
        {
            //put next piece of data into I2C FIFO
            I2CMasterDataPut(Base, array[i++]);

            //send next data that was just placed into FIFO
            I2CMasterControl(Base, I2C_MASTER_CMD_BURST_SEND_CONT);

            // Wait until MCU is done transferring.
            while(I2CMasterBusy(Base));

            u32ErrorFlags |= I2CMasterErr(Base);

        }

        //put last piece of data into I2C FIFO
        I2CMasterDataPut(Base, array[i]);

        //send next data that was just placed into FIFO
        I2CMasterControl(Base, I2C_MASTER_CMD_BURST_SEND_FINISH);

        // Wait until MCU is done transferring.
        while(I2CMasterBusy(Base));

        u32ErrorFlags |= I2CMasterErr(Base);

    }

    return u32ErrorFlags;
}


uint32_t I2CReadBytes(uint8_t I2C_ID, uint32_t slave_addr,uint8_t * u8Command, uint8_t u8BytesNumber,uint8_t * RxBuffer)
{
    uint32_t Base = I2C_Bases[I2C_ID];
    uint32_t u32ErrorFlags = 0;
    //initialize index into array
    uint8_t u8RxIndex = 1;


    //specify that we are writing (a register address) to the
    //slave device
    I2CMasterSlaveAddrSet(Base, slave_addr, false);

    //specify register to be read
    I2CMasterDataPut(Base, u8Command[1]);


    //Initiate send of data from the MCU
    I2CMasterControl(Base, I2C_MASTER_CMD_BURST_SEND_START);

    // Wait until MCU is done transferring.
    while(I2CMasterBusy(Base));

    u32ErrorFlags |= I2CMasterErr(Base);


    //put last piece of data into I2C FIFO
    I2CMasterDataPut(Base, u8Command[0]);
#if 1
    //send next data that was just placed into FIFO
    I2CMasterControl(Base, I2C_MASTER_CMD_BURST_SEND_CONT);
#else

    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);
    //send next data that was just placed into FIFO
    //I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
#endif
    // Wait until MCU is done transferring.
    while(I2CMasterBusy(Base));

    u32ErrorFlags |= I2CMasterErr(Base);





    //specify that we are going to read from slave device
    I2CMasterSlaveAddrSet(Base, slave_addr, true);
    //if there is only one argument, we only need to use the
    //single send I2C function
    if(u8BytesNumber == 1)
    {
        //send control byte and read from the register we
        //specified
        I2CMasterControl(Base, I2C_MASTER_CMD_SINGLE_RECEIVE);

        //wait for MCU to finish transaction
        while(I2CMasterBusy(Base));

        // Save this bit Rx buffer
        RxBuffer[0] = I2CMasterDataGet(Base);

        u32ErrorFlags |= I2CMasterErr(Base);

    }
    else
    {

        //Initiate send of data from the MCU
          I2CMasterControl(Base, I2C_MASTER_CMD_BURST_RECEIVE_START);

          // Wait until MCU is done transferring.
          while(I2CMasterBusy(Base));

          // Save this bit Rx buffer
          RxBuffer[0] = I2CMasterDataGet(Base);

          u32ErrorFlags |= I2CMasterErr(Base);



          //send num_of_args-2 pieces of data, using the
          //BURST_SEND_CONT command of the I2C module
          while(u8RxIndex < (u8BytesNumber-1))
          {

              //send next data that was just placed into FIFO
              I2CMasterControl(Base, I2C_MASTER_CMD_BURST_RECEIVE_CONT);

              // Wait until MCU is done transferring.
              while(I2CMasterBusy(Base));

              // Save this bit Rx buffer
              RxBuffer[u8RxIndex] = I2CMasterDataGet(Base);

              u32ErrorFlags |= I2CMasterErr(Base);

              u8RxIndex++;

          }

          //send next data that was just placed into FIFO
          I2CMasterControl(Base, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);

          // Wait until MCU is done transferring.
          while(I2CMasterBusy(Base));

          // Save this bit Rx buffer
          RxBuffer[u8RxIndex] = I2CMasterDataGet(Base);

          u32ErrorFlags |= I2CMasterErr(Base);
    }

    return u32ErrorFlags;
}

/*
//initialize I2C module 1
//Slightly modified version of TI's example code
uint32_t I2C1SendString(uint8_t I2C_ID, uint8_t slave_addr, uint8_t array[])
{

    uint32_t u32ErrorFlags = 0;
    // Tell the master module what address it will place on the bus when
    // communicating with the slave.
    I2CMasterSlaveAddrSet(I2C1_BASE, slave_addr, false);

    //put data to be sent into FIFO
    I2CMasterDataPut(I2C1_BASE, array[0]);

    //if there is only one argument, we only need to use the
    //single send I2C function
    if(array[1] == 0xFF)
    {
        //Initiate send of data from the MCU
        I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_SINGLE_SEND);

        // Wait until MCU is done transferring.
        while(I2CMasterBusy(I2C1_BASE));

        u32ErrorFlags |= I2CMasterErr(I2C1_BASE);
    }

    //otherwise, we start transmission of multiple bytes on the
    //I2C bus
    else
    {
        //Initiate send of data from the MCU
        I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_START);

        // Wait until MCU is done transferring.
        while(I2CMasterBusy(I2C1_BASE));

        u32ErrorFlags |= I2CMasterErr(I2C1_BASE);

        //initialize index into array
        uint8_t i = 1;

        //send num_of_args-2 pieces of data, using the
        //BURST_SEND_CONT command of the I2C module
        while(array[i + 1] != 0XFF)
        {
            //put next piece of data into I2C FIFO
            I2CMasterDataPut(I2C1_BASE, array[i++]);

            //send next data that was just placed into FIFO
            I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);

            // Wait until MCU is done transferring.
            while(I2CMasterBusy(I2C1_BASE));

            u32ErrorFlags |= I2CMasterErr(I2C1_BASE);

        }

        //put last piece of data into I2C FIFO
        I2CMasterDataPut(I2C1_BASE, array[i]);

        //send next data that was just placed into FIFO
        I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);

        // Wait until MCU is done transferring.
        while(I2CMasterBusy(I2C1_BASE));

        u32ErrorFlags |= I2CMasterErr(I2C1_BASE);

    }

    return u32ErrorFlags;
}

uint32_t I2C1ReadBytes(uint32_t slave_addr,uint8_t  u8Command, uint8_t u8BytesNumber,uint8_t * RxBuffer)
{
    uint32_t u32ErrorFlags = 0;
    //initialize index into array
    uint8_t u8RxIndex = 1;


    //specify that we are writing (a register address) to the
    //slave device
    I2CMasterSlaveAddrSet(I2C1_BASE, slave_addr, false);

    //specify register to be read
    I2CMasterDataPut(I2C1_BASE, u8Command);


    //Initiate send of data from the MCU
    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_START);

    // Wait until MCU is done transferring.
    while(I2CMasterBusy(I2C1_BASE));

    u32ErrorFlags |= I2CMasterErr(I2C1_BASE);





    //specify that we are going to read from slave device
    I2CMasterSlaveAddrSet(I2C1_BASE, slave_addr, true);
    //if there is only one argument, we only need to use the
    //single send I2C function
    if(u8BytesNumber == 1)
    {
        //send control byte and read from the register we
        //specified
        I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE);

        //wait for MCU to finish transaction
        while(I2CMasterBusy(I2C1_BASE));

        // Save this bit Rx buffer
        RxBuffer[0] = I2CMasterDataGet(I2C1_BASE);

        u32ErrorFlags |= I2CMasterErr(I2C1_BASE);

    }
    else
    {

        //Initiate send of data from the MCU
          I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_RECEIVE_START);

          // Wait until MCU is done transferring.
          while(I2CMasterBusy(I2C1_BASE));

          // Save this bit Rx buffer
          RxBuffer[0] = I2CMasterDataGet(I2C1_BASE);

          u32ErrorFlags |= I2CMasterErr(I2C1_BASE);



          //send num_of_args-2 pieces of data, using the
          //BURST_SEND_CONT command of the I2C module
          while(u8RxIndex < (u8BytesNumber-1))
          {

              //send next data that was just placed into FIFO
              I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_RECEIVE_CONT);

              // Wait until MCU is done transferring.
              while(I2CMasterBusy(I2C1_BASE));

              // Save this bit Rx buffer
              RxBuffer[u8RxIndex] = I2CMasterDataGet(I2C1_BASE);

              u32ErrorFlags |= I2CMasterErr(I2C1_BASE);

              u8RxIndex++;

          }

          //send next data that was just placed into FIFO
          I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);

          // Wait until MCU is done transferring.
          while(I2CMasterBusy(I2C1_BASE));

          // Save this bit Rx buffer
          RxBuffer[u8RxIndex] = I2CMasterDataGet(I2C1_BASE);

          u32ErrorFlags |= I2CMasterErr(I2C1_BASE);
    }

    return u32ErrorFlags;
}

//initialize I2C module 1
//Slightly modified version of TI's example code
uint32_t I2C2SendString(uint8_t slave_addr, uint8_t array[])
{

    uint32_t u32ErrorFlags = 0;
    // Tell the master module what address it will place on the bus when
    // communicating with the slave.
    I2CMasterSlaveAddrSet(I2C2_BASE, slave_addr, false);

    //put data to be sent into FIFO
    I2CMasterDataPut(I2C2_BASE, array[0]);

    //if there is only one argument, we only need to use the
    //single send I2C function
    if(array[1] == 0xFF)
    {
        //Initiate send of data from the MCU
        I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_SINGLE_SEND);

        // Wait until MCU is done transferring.
        while(I2CMasterBusy(I2C2_BASE));

        u32ErrorFlags |= I2CMasterErr(I2C2_BASE);
    }

    //otherwise, we start transmission of multiple bytes on the
    //I2C bus
    else
    {
        //Initiate send of data from the MCU
        I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_BURST_SEND_START);

        // Wait until MCU is done transferring.
        while(I2CMasterBusy(I2C2_BASE));

        u32ErrorFlags |= I2CMasterErr(I2C2_BASE);

        //initialize index into array
        uint8_t i = 1;

        //send num_of_args-2 pieces of data, using the
        //BURST_SEND_CONT command of the I2C module
        while(array[i + 1] != 0XFF)
        {
            //put next piece of data into I2C FIFO
            I2CMasterDataPut(I2C2_BASE, array[i++]);

            //send next data that was just placed into FIFO
            I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);

            // Wait until MCU is done transferring.
            while(I2CMasterBusy(I2C2_BASE));

            u32ErrorFlags |= I2CMasterErr(I2C2_BASE);

        }

        //put last piece of data into I2C FIFO
        I2CMasterDataPut(I2C2_BASE, array[i]);

        //send next data that was just placed into FIFO
        I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);

        // Wait until MCU is done transferring.
        while(I2CMasterBusy(I2C2_BASE));

        u32ErrorFlags |= I2CMasterErr(I2C2_BASE);

    }

    return u32ErrorFlags;
}

uint32_t I2C2ReadBytes(uint32_t slave_addr,uint8_t  u8Command, uint8_t u8BytesNumber,uint8_t * RxBuffer)
{
    uint32_t u32ErrorFlags = 0;
    //initialize index into array
    uint8_t u8RxIndex = 1;


    //specify that we are writing (a register address) to the
    //slave device
    I2CMasterSlaveAddrSet(I2C2_BASE, slave_addr, false);

    //specify register to be read
    I2CMasterDataPut(I2C2_BASE, u8Command);


    //Initiate send of data from the MCU
    I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_BURST_SEND_START);

    // Wait until MCU is done transferring.
    while(I2CMasterBusy(I2C2_BASE));

    u32ErrorFlags |= I2CMasterErr(I2C2_BASE);





    //specify that we are going to read from slave device
    I2CMasterSlaveAddrSet(I2C2_BASE, slave_addr, true);
    //if there is only one argument, we only need to use the
    //single send I2C function
    if(u8BytesNumber == 1)
    {
        //send control byte and read from the register we
        //specified
        I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE);

        //wait for MCU to finish transaction
        while(I2CMasterBusy(I2C2_BASE));

        // Save this bit Rx buffer
        RxBuffer[0] = I2CMasterDataGet(I2C2_BASE);

        u32ErrorFlags |= I2CMasterErr(I2C2_BASE);

    }
    else
    {

        //Initiate send of data from the MCU
          I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_BURST_RECEIVE_START);

          // Wait until MCU is done transferring.
          while(I2CMasterBusy(I2C2_BASE));

          // Save this bit Rx buffer
          RxBuffer[0] = I2CMasterDataGet(I2C2_BASE);

          u32ErrorFlags |= I2CMasterErr(I2C2_BASE);



          //send num_of_args-2 pieces of data, using the
          //BURST_SEND_CONT command of the I2C module
          while(u8RxIndex < (u8BytesNumber-1))
          {

              //send next data that was just placed into FIFO
              I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_BURST_RECEIVE_CONT);

              // Wait until MCU is done transferring.
              while(I2CMasterBusy(I2C2_BASE));

              // Save this bit Rx buffer
              RxBuffer[u8RxIndex] = I2CMasterDataGet(I2C2_BASE);

              u32ErrorFlags |= I2CMasterErr(I2C2_BASE);

              u8RxIndex++;

          }

          //send next data that was just placed into FIFO
          I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);

          // Wait until MCU is done transferring.
          while(I2CMasterBusy(I2C2_BASE));

          // Save this bit Rx buffer
          RxBuffer[u8RxIndex] = I2CMasterDataGet(I2C2_BASE);

          u32ErrorFlags |= I2CMasterErr(I2C2_BASE);
    }

    return u32ErrorFlags;
}

//initialize I2C module 1
//Slightly modified version of TI's example code
uint32_t I2C3SendString(uint8_t slave_addr, uint8_t array[])
{

    uint32_t u32ErrorFlags = 0;
    // Tell the master module what address it will place on the bus when
    // communicating with the slave.
    I2CMasterSlaveAddrSet(I2C3_BASE, slave_addr, false);

    //put data to be sent into FIFO
    I2CMasterDataPut(I2C3_BASE, array[0]);

    //if there is only one argument, we only need to use the
    //single send I2C function
    if(array[1] == 0xFF)
    {
        //Initiate send of data from the MCU
        I2CMasterControl(I2C3_BASE, I2C_MASTER_CMD_SINGLE_SEND);

        // Wait until MCU is done transferring.
        while(I2CMasterBusy(I2C3_BASE));

        u32ErrorFlags |= I2CMasterErr(I2C3_BASE);
    }

    //otherwise, we start transmission of multiple bytes on the
    //I2C bus
    else
    {
        //Initiate send of data from the MCU
        I2CMasterControl(I2C3_BASE, I2C_MASTER_CMD_BURST_SEND_START);

        // Wait until MCU is done transferring.
        while(I2CMasterBusy(I2C3_BASE));

        u32ErrorFlags |= I2CMasterErr(I2C3_BASE);

        //initialize index into array
        uint8_t i = 1;

        //send num_of_args-2 pieces of data, using the
        //BURST_SEND_CONT command of the I2C module
        while(array[i + 1] != 0XFF)
        {
            //put next piece of data into I2C FIFO
            I2CMasterDataPut(I2C3_BASE, array[i++]);

            //send next data that was just placed into FIFO
            I2CMasterControl(I2C3_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);

            // Wait until MCU is done transferring.
            while(I2CMasterBusy(I2C3_BASE));

            u32ErrorFlags |= I2CMasterErr(I2C3_BASE);

        }

        //put last piece of data into I2C FIFO
        I2CMasterDataPut(I2C3_BASE, array[i]);

        //send next data that was just placed into FIFO
        I2CMasterControl(I2C3_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);

        // Wait until MCU is done transferring.
        while(I2CMasterBusy(I2C3_BASE));

        u32ErrorFlags |= I2CMasterErr(I2C3_BASE);

    }

    return u32ErrorFlags;
}

uint32_t I2C3ReadBytes(uint32_t slave_addr,uint8_t  u8Command, uint8_t u8BytesNumber,uint8_t * RxBuffer)
{
    uint32_t u32ErrorFlags = 0;
    //initialize index into array
    uint8_t u8RxIndex = 1;


    //specify that we are writing (a register address) to the
    //slave device
    I2CMasterSlaveAddrSet(I2C3_BASE, slave_addr, false);

    //specify register to be read
    I2CMasterDataPut(I2C3_BASE, u8Command);


    //Initiate send of data from the MCU
    I2CMasterControl(I2C3_BASE, I2C_MASTER_CMD_BURST_SEND_START);

    // Wait until MCU is done transferring.
    while(I2CMasterBusy(I2C3_BASE));

    u32ErrorFlags |= I2CMasterErr(I2C3_BASE);





    //specify that we are going to read from slave device
    I2CMasterSlaveAddrSet(I2C3_BASE, slave_addr, true);
    //if there is only one argument, we only need to use the
    //single send I2C function
    if(u8BytesNumber == 1)
    {
        //send control byte and read from the register we
        //specified
        I2CMasterControl(I2C3_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE);

        //wait for MCU to finish transaction
        while(I2CMasterBusy(I2C3_BASE));

        // Save this bit Rx buffer
        RxBuffer[0] = I2CMasterDataGet(I2C3_BASE);

        u32ErrorFlags |= I2CMasterErr(I2C3_BASE);

    }
    else
    {

        //Initiate send of data from the MCU
          I2CMasterControl(I2C3_BASE, I2C_MASTER_CMD_BURST_RECEIVE_START);

          // Wait until MCU is done transferring.
          while(I2CMasterBusy(I2C3_BASE));

          // Save this bit Rx buffer
          RxBuffer[0] = I2CMasterDataGet(I2C3_BASE);

          u32ErrorFlags |= I2CMasterErr(I2C3_BASE);



          //send num_of_args-2 pieces of data, using the
          //BURST_SEND_CONT command of the I2C module
          while(u8RxIndex < (u8BytesNumber-1))
          {

              //send next data that was just placed into FIFO
              I2CMasterControl(I2C3_BASE, I2C_MASTER_CMD_BURST_RECEIVE_CONT);

              // Wait until MCU is done transferring.
              while(I2CMasterBusy(I2C3_BASE));

              // Save this bit Rx buffer
              RxBuffer[u8RxIndex] = I2CMasterDataGet(I2C3_BASE);

              u32ErrorFlags |= I2CMasterErr(I2C3_BASE);

              u8RxIndex++;

          }

          //send next data that was just placed into FIFO
          I2CMasterControl(I2C3_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);

          // Wait until MCU is done transferring.
          while(I2CMasterBusy(I2C3_BASE));

          // Save this bit Rx buffer
          RxBuffer[u8RxIndex] = I2CMasterDataGet(I2C3_BASE);

          u32ErrorFlags |= I2CMasterErr(I2C3_BASE);
    }

    return u32ErrorFlags;
}
*/

#ifdef LCD_EX
#define LCD_SLAVE_ADDR 0x28
#define LCD_CMD 0xFE //used to send commands to the LCD

//clear LCD
void ClearScreen()
{
    I2CSend(LCD_SLAVE_ADDR, 2, LCD_CMD, 0x58);
}

//set brightness of LCD
void SetBrightness(uint8_t brightness)
{
    I2CSend(LCD_SLAVE_ADDR, 3, LCD_CMD, 0x99, brightness);
}

//set contrast of LCD
void SetContrast(uint8_t contrast)
{
    I2CSend(LCD_SLAVE_ADDR, 3, LCD_CMD, 0x50, contrast);
}

//write single char to LCD
void WriteChar(uint8_t character)
{
    I2CSend(LCD_SLAVE_ADDR, 1, character);
}

//write string to LCD
void WriteString(char string[255])
{
    I2CSendString(LCD_SLAVE_ADDR, string);
}

//draw a line with start point (x1, y1) and endpoint (x2, y2)
void DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
    I2CSend(LCD_SLAVE_ADDR, 6, LCD_CMD, 0x6C, x1, y1, x2, y2);
}

//set coordinates (in exact pixels) of the cursor
void SetCursorCoord(uint8_t x, uint8_t y)
{
    I2CSend(LCD_SLAVE_ADDR, 4, LCD_CMD, 0x79, x, y);
}

//set position of the text cursor
void SetCursorPos(uint8_t col, uint8_t row)
{
    I2CSend(LCD_SLAVE_ADDR, 4, LCD_CMD, 0x47, col, row);
}

void main(void)
{
    // Set the clocking to run directly from the external crystal/oscillator.
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_PLL | SYSCTL_OSC_INT | SYSCTL_XTAL_16MHZ);

    //initialize I2C module 0
    InitI2C0();

    //initialize display
    SetBrightness(0);
    SetContrast(150);
    ClearScreen();

    SetCursorPos(0, 1);
    WriteString("Hello,");
    SetCursorPos(0, 2);
    WriteString("World!");

    while(1){};
}
#endif

#ifdef READ_EX
#define ACCEL_SLAVE_ADDR 0x1D
#define XOUT8 0x06
#define YOUT8 0x07
#define ZOUT8 0x08

uint8_t ReadAccel(uint8_t reg)
{
    uint8_t accelData =  I2CReceive(ACCEL_SLAVE_ADDR, reg);

    return accelData;
}

void main(void)
{
    // Set the clocking to run directly from the external crystal/oscillator.
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_PLL | SYSCTL_OSC_INT | SYSCTL_XTAL_16MHZ);

    //initialize I2C module 0
    InitI2C0();

    uint8_t Ax, Ay, Az;

    Ax = ReadAccel(XOUT8);
    Ay = ReadAccel(YOUT8);
    Az = ReadAccel(ZOUT8);

    while(1){};
}
#endif
