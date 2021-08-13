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
 * @file term_tt_posix_cpp.cxx
 * @author Patrick Pedersen
 * @date 2021-08-05
 * 
 * @brief C++ wrapper implementation of term_tt_posix.cxx
 * 
 * The following file is equivalent to term_tt_posix.cxx, except that
 * the C++ wrapper of the tempo tapper library has been used.
 * For a functional understanding of this code, please refer to the
 * documentation of term_tt_posix.cxx.
 * 
 * Dependencies:
 *      - ncurses
 *
 * To compile, execute the following command from the projects root directory:
 * ```
 *      $ g++ -D TT_TARGET_PLATFORM_POSIX -I include/ examples/posix/term_tt_posix.cxx src/tempo_tapper_common.cxx src/tempo_tapper_posix.cxx src/tempo_tapper_cpp.cxx -lncurses -o examples/posix/term_tt
 * ```
 * 
 * The resulting executable will be located in examples/posix/.
 * To execute it from the project root directory, run:
 * ```
 *      $ ./examples/posix/term_tt
 * ```
 * 
 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <curses.h>

#include <tempo_tapper_cpp.h> // C++ wrapper

int main()
{
        tempo_tapper_cpp tt; // Create new tempo tapper class object
        
        if (!tt.is_init()) {
                printf("term_tt: Failed to create a new tempo tapper object!\n");
                return EXIT_FAILURE; // Exit 
        }

        // Initialize ncurses
        initscr();
        timeout(-1);
        curs_set(0);

        char input; // Keyboard input

        do {
                clear();
                printw("Use the enter key to tap a tempo. Press q to quit.\n");
                refresh();

                while (1) {
                        input = getchar();
                        clear();

                        if (input == 'q' || input == 'r')
                                break;
                        else if (input == '\r' || input == '\n')
                                tt.tap(); // Newline received, tap!
                        else
                                printw("Invalid input!\n");
                        
                        // Get tempo, using tt_bpm(), and tempo period using tt_preiod_us(), and print it out!
                        printw("Tempo: %.2f BPM, Period: %.2fms\n", tt.bpm(), float(tt.period_us())/1000);
                        printw("Press r to reset, press q to quit.\n");
                        refresh();
                }

                tt.reset(); // Reset tempo tapper
        } while(input != 'q');

        endwin();
        return 0;
}