/* 
   I2CDevI2C.cpp: Linux i2cdev implementation of cross-platform I2C routines

   This file is part of CrossPlatformI2C.

   CrossPlatformI2C is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   CrossPlatformI2C is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   You should have received a copy of the GNU General Public License
   along with CrossPlatformI2C.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "CrossPlatformI2C.h"

#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

static const uint8_t I2C_BUS_NUMBER = 1;

void I2C::delay(uint32_t msec)
{
    usleep(msec*1000);
}

uint8_t I2C::setup(uint8_t address)
{
    // Attempt to open /dev/i2c-<NUMBER>
    char fname[32];
    sprintf(fname,"/dev/i2c-%d", I2C_BUS_NUMBER);
    int fd = open(fname, O_RDWR);
    if (fd < 0) {
        fprintf(stderr, "Unable to open %s\n", fname);
        exit(1);
    }

    // Attempt to make this device an I2C slave
    if (ioctl(fd, I2C_SLAVE, address) < 0) {
        fprintf(stderr, "ioctl failed on %s\n", fname);
        exit(1);
    }

    return fd;
}

void I2C::writeRegister(uint8_t address, uint8_t subAddress, uint8_t data)
{
    i2c_smbus_write_byte_data(address, subAddress, data);
}

void I2C::readRegisters(uint8_t address, uint8_t subAddress, uint8_t count, uint8_t * dest)
{
    i2c_smbus_write_byte(address, subAddress);

    for (uint8_t k=0; k<count; ++k) {
        dest[k] = i2c_smbus_read_byte(address);
    }
}