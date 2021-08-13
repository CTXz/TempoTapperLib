/*
 * Copyright (C) 2021  Patrick Pedersen

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 * 
 */

/**
 * @file tempo_tapper_arduino.cxx
 * @author Patrick Pedersen
 * @date 2021-08-05
 * 
 * @brief Defines platform specific functions for Arduino compatible platforms
 * 
 * The following file defines platform specific functions for devices that support
 * the Arduino programming framework.
 * 
 * All function descriptions can be found in the tempo_tapper.h file.
 */

#ifdef TT_TARGET_PLATFORM_ARDUINO

#include <stdlib.h>
#include <stddef.h>

#include <Arduino.h>

#include <tempo_tapper.h>

void current_time(tt_time_t *time)
{
        *time = micros();
}

void add_time(tt_time_t *a, tt_time_t *b, tt_time_t *res)
{
        *res = *a + *b;
}

void sub_time(tt_time_t *a, tt_time_t *b, tt_time_t *res)
{
        *res = *a - *b;
}

unsigned long time_to_us(tt_time_t *time)
{
        return *time;
}

void reset_time(tt_time_t *time)
{
        *time = 0;
}

#endif