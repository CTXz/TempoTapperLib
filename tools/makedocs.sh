#!/bin/bash

#
# Copyright (C) 2021  Patrick Pedersen

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
# 
# Author: Patrick Pedersen <ctx.xda@gmail.com>
# Brief description: Script to generate a customized doxygen web documentation
# Detailed description:
#       The following script has been made out of the necessity to support
#       struct definitions for multiple platforms in docs generated by doxygen.
#       It is done by first generating multiple doxygen references for platform
#       specific files, then generating a full doxygen web documentation,
#       and lastly, filling the references with the content obtained from the
#       platform specific doxygen refrences.
#
#       PS: I am aware that this is a very ugly hack, and can easily break on
#           doxygen updates, however I have not found a way to solve this issue
#           with the custimization options provided by doxygen.
#
#       PS PS: My sed and regex skills have become very rusty and I do not have
#              the time nor the motivation to relearn all of this crap properly
#              again. Sorry.

DOCS_URL="https://ctxz.github.io/TempoTapperLib/"

### MAIN ###

# cd into project root
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
PROJECT_ROOT="$DIR/.."
cd "$PROJECT_ROOT"

rm -rf "doxygen/"
rm -rf docs/
doxygen
mv doxygen/html docs/ 
rm -r doxygen

echo "makedocs: Done"