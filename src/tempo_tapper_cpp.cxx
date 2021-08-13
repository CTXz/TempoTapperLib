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
 * @file tempo_tapper_cpp.cxx
 * @author Patrick Pedersen
 * @date 2021-08-05
 * 
 * @brief Defines methods for the C++ tempo tapper wrapper
 * 
 * The following file defines the wrapper methods of the C++
 * tempo tapper wrapper class.
 */

#include <stdlib.h>
#include <tempo_tapper_cpp.h>

tempo_tapper_cpp::tempo_tapper_cpp()
{
        _tt = tt_new();
}

tempo_tapper_cpp::~tempo_tapper_cpp()
{
        free(_tt);
}

unsigned long tempo_tapper_cpp::period_us()
{
        return tt_period_us(_tt);
}

void tempo_tapper_cpp::tap()
{
        tt_tap(_tt);
}

void tempo_tapper_cpp::reset()
{
        tt_reset(_tt);
}

float tempo_tapper_cpp::bpm()
{
        return tt_bpm(_tt);
}