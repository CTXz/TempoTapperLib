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
 * @file tempo_tapper_posix.cxx
 * @author Patrick Pedersen
 * @date 2021-08-05
 * 
 * @brief Defines platform specific functions for POSIX compliant platforms
 * 
 * The following file defines platform specific functions for devices that comply, or mostly-comply
 * to the POSIX standards (ex. Linux, MacOS, etc.).
 * 
 * All function descriptions can be found in the tempo_tapper.h file.
 */

#ifdef TT_TARGET_PLATFORM_POSIX

#include <stdlib.h>
#include <stddef.h>
#include <sys/time.h>

#include <tempo_tapper.h>

void current_time(tt_time_t *time)
{
        gettimeofday(time, NULL);
}

void add_time(tt_time_t *a, tt_time_t *b, tt_time_t *res)
{
        timeradd(a, b, res);
}

void sub_time(tt_time_t *a, tt_time_t *b, tt_time_t *res)
{
        timersub(a, b, res);
}

unsigned long time_to_us(tt_time_t *time)
{
        return (time->tv_sec * S_TO_US + time->tv_usec);
}

void reset_time(tt_time_t *time)
{
        time->tv_sec = 0;
        time->tv_usec = 0;
}

#endif