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
 * @file tempo_tapper_cpp.h
 * @author Patrick Pedersen
 * @date 2021-08-05
 * 
 * @brief C++ wrapper for the tempo tapper library
 * 
 * The following file provides a C++ class wrapper around the
 * tempo tapper library.
 * 
 * For a functional understanding, please refer to definitions of
 * the C interface in tempo_tapper.h, as the methods of the wrapper
 * class correspond to the definitions of the C interface. 
 */

#pragma once

#include "tempo_tapper.h"

/**
 * @brief C++ wrapper for the tempo tapper library
 * 
 * The following class wraps around the C interface
 * of the tempo tapper library.
 * 
 */
class tempo_tapper_cpp {
private:
        tempo_tapper *_tt;

public:
        tempo_tapper_cpp();        ///< Wraps around tt_new()
        ~tempo_tapper_cpp();

        unsigned long period_us(); ///< Wraps around tt_period_us()
        void tap();                ///< Wraps around tt_tap()
        void reset();              ///< Wraps around tt_reset()
        float bpm();               ///< Wraps around tt_bpm()
};