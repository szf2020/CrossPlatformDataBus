/* 
   main.pp: Generic main() for caling Arduino-style setup(), loop()

   This file is part of CrossPlatformDataBus.

   CrossPlatformDataBus is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   CrossPlatformDataBus is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   You should have received a copy of the GNU General Public License
   along with CrossPlatformDataBus.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <unistd.h>
#include <stdint.h>

void delay(uint32_t msec)
{
    usleep(msec*1000);
}

extern void setup(), loop();

int main(int argc, char ** argv)
{
    setup();

    while (true) {
        loop();
    }
}