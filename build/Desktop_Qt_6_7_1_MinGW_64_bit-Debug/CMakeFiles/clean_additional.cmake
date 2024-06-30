# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "Account_Management_autogen"
  "CMakeFiles\\Account_Management_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Account_Management_autogen.dir\\ParseCache.txt"
  )
endif()
