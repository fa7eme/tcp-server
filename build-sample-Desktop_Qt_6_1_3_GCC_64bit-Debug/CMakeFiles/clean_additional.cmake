# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/sample_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/sample_autogen.dir/ParseCache.txt"
  "sample_autogen"
  )
endif()
