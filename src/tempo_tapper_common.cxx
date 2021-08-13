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
 * @file tempo_tapper_common.cxx
 * @author Patrick Pedersen
 * @date 2021-08-05
 * 
 * @brief Defines code shared accross all target platform s
 * 
 * The following file defines tempo tapper functions that are shared
 * across all target platforms.
 * 
 * All function descriptions can be found in the tempo_tapper.h file.
 */

#include <stdlib.h>
#include <stddef.h>

#include <tempo_tapper.h>

unsigned long tt_period_us(tempo_tapper *tapper)
{
        if (tapper->taps < 1)
                return 0;

        unsigned long us = time_to_us(&tapper->prd_sum);
        return us/tapper->taps;
}

void tt_tap(tempo_tapper *tapper)
{
        tt_time_t c_time;
        current_time(&c_time);

        if (tapper->taps >= 0) {
                tt_time_t tdiff;
                sub_time(&c_time, &tapper->lst_t, &tdiff);
                add_time(&tapper->prd_sum, &tdiff, &tapper->prd_sum);
        }

        tapper->taps++;
        tapper->lst_t = c_time;
}

tempo_tapper* tt_new()
{
        tempo_tapper *tapper = (tempo_tapper *) malloc(sizeof(tempo_tapper));
        
        if (tapper == NULL)
                return NULL;
        
        tt_reset(tapper);
        return tapper;
}

float tt_bpm(tempo_tapper *tapper)
{
        unsigned long us = tt_period_us(tapper);
        
        if (us == 0)
                return 0;

        
        return (60 * S_TO_US)/(float)tt_period_us(tapper);
}

void tt_reset(tempo_tapper *tapper)
{
        tapper->taps = -1;
        reset_time(&tapper->prd_sum);
}