#==============================================================================
# Copyright (c) 2016-2017 Allan CORNET (Nelson)
#==============================================================================
# LICENCE_BLOCK_BEGIN
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
# LICENCE_BLOCK_END
#==============================================================================
include_directories(${EIGEN_INCLUDE_DIR})
#==============================================================================	
LIST(APPEND moduleslist
characters_encoding
i18n
elementary_mathematics
error_manager
types
api_nelson
stream_manager
elementary_functions
interpreter
double
single
sparse
constructors_functions
console
logical
time
trigonometric_functions
string
integer
random
files_folders_functions
os_functions
core
functions_manager
function_handle
memory_manager
overload
data_structures
history_manager
terminal
gui
help_browser
dynamic_link
help_tools
localization
assert_functions
tests_manager
modules_manager
engine
main
)
#==============================================================================	
FOREACH(mod ${moduleslist})
  INCLUDE_DIRECTORIES("../build/modules/${mod}/includes")
  INCLUDE_DIRECTORIES("${mod}/src/c")
  INCLUDE_DIRECTORIES("${mod}/src/cpp")
  add_subdirectory(${mod})
ENDFOREACH(mod)
#==============================================================================	
install(FILES ${CMAKE_SOURCE_DIR}/modules/modules.nls DESTINATION ${ROOT_OUTPUT}/modules) 
#==============================================================================	
