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
 * @file tempo_tapper.h
 * @author Patrick Pedersen
 * @date 2021-08-05
 * 
 * @brief Provides all necessary structs and functions to implement a tempo tapper
 * 
 * The following file Provides all necessary strucs and functions to implement a tempo tapper, i.e.
 * the tempo tapper struct and prototypes for all functions that interact with a tempo tapper struct
 * instance.
 * 
 * The tempo tapper libraries is supported by multiple target platforms.
 * Define one of the following preprocessors to select your target platform:
 * 
 * - TT_TARGET_PLATFORM_POSIX - Posix compliant platforms (Ex. Linux, MacOS, etc.)
 * - TT_TARGET_PLATFORM_ARDUINO - Platforms that support the Arduino programming framework
 * 
 */

#pragma once

#include <stdint.h>

#define S_TO_US 1000000

#if defined(TT_TARGET_PLATFORM_POSIX)

#include <sys/time.h>
typedef struct timeval tt_time_t;

#elif defined(TT_TARGET_PLATFORM_ARDUINO)

#include <Arduino.h>
typedef unsigned long tt_time_t;

#else

#error No target platform specified!

#endif

typedef float BPM_t; // Data type to store BPM values

/**
 * @brief Tempo tapper struct
 * 
 * The following struct represents a virtual tempo tapper,
 * and stores the necessary information to set, alter and
 * receive a tempo value.
 * 
 * To create and interface with a tempo tapper struct, use the following
 * functions:
 * 
 * - tt_new() - Creates a new tempo tapper struct
 * - tt_period_us() - Returns the period of a tempo in microseconds
 * - tt_tap() - "Taps" the tempo tapper
 * - tt_reset() - Resets the tempo tapper
 * - tt_bpm() - Returns the tempo in BPM
 * 
 * To store time values, the platform varying tt_time_t typedef is used, as each
 * platform offers its own preferred data type or struct to store time values
 * (Ex. timeval on posix). This means that time arithmetic is implemented differently
 * on every platform (see current_time(), add_time(), sub_time(), time_to_us(), reset_time()).
 * For the library user, this is irrelevant as platform specific code is handled
 * by the library internally. The only noticable external difference may be a variation
 * in speed and precision. 
 */

typedef struct tempo_tapper
{
        tt_time_t prd_sum;      ///< Holds the sum of all measured/"tapped" periods.
        tt_time_t lst_t;        ///< Hold the clock time of the last tap.
        int taps;               ///< Number of taps. The inital val is -1, meaning the 1st tap does not count.
} tempo_tapper;

// Platform Specific

/**
 * @brief Receives the current clock time 
 * 
 * The following function sets the parsed time var
 * to the current clock time. The clock time may be
 * the time that has passed since the start of the program,
 * (ex. micros() on arduino platforms), but may also be the
 * current time of the day (ex. gettimeofday() on posix).
 * 
 * @note The implementation of this function is platform specific.
 */
void current_time(tt_time_t *time);

/**
 * @brief Adds two time values
 * 
 * The following function adds two time values, a, and b and
 * stores the result in res.
 * 
 * @note The implementation of this function is platform specific.
 */
void add_time(tt_time_t *a, tt_time_t *b, tt_time_t *res);

/**
 * @brief Subtracts two time values
 * 
 * The following function subtracts the time value of b from a
 * and stores the result in res.
 * 
 * @note The implementation of this function is platform specific.
 */
void sub_time(tt_time_t *a, tt_time_t *b, tt_time_t *res);

/**
 * @brief Resets a time var to 0
 * 
 * The following function resets a time var to 0
 * 
 * @note The implementation of this function is platform specific.
 */
void reset_time(tt_time_t *time);

/**
 * @brief Returns a time value in microseconds
 * 
 * The following function converts and returns a time value in microseconds.
 * 
 * @return Time in microseconds
 * @note The implementation of this function is platform specific.
 */
unsigned long time_to_us(tt_time_t *time);

// Common

/**
 * @brief Creates a new tempo tapper instance
 * 
 * The following function creates and initializes a tempo tapper struct instance.
 * 
 * @return A initialized tempo_tapper struct instance or NULL on failure
 * 
 */
tempo_tapper* tt_new();

/**
 * @brief Returns the period of a tempo in microseconds
 * 
 * The following function returns the time in microseconds
 * for a period of the current tempo set by the tempo tapper
 * struct.
 * 
 * @return Period time in microseconds
 * 
 */
unsigned long tt_period_us(tempo_tapper *tapper);

/**
 * @brief "Taps" the tempo tapper
 * 
 * The following function is used to "tap" a tempo tapper
 * struct instance. Calling this function on a tempo tapper
 * struct will increase the value of taps, add the time that
 * has passed since the last tap to prd_sum and update
 * lst_t to the current clock time.
 * 
 */
void tt_tap(tempo_tapper *tapper);

/**
 * @brief Resets the tempo tapper
 * 
 * The following function resets the tempo tapper to its
 * iniital values.
 * 
 */
void tt_reset(tempo_tapper *tapper);

/**
 * @brief Returns the tempo in BPM
 * 
 * The following function returns the tempo of the tempo tapper
 * in BPM. The decimal precision is platform dependant. 
 *
 * @return Tempo in BPM 
 */
BPM_t tt_bpm(tempo_tapper *tapper);
