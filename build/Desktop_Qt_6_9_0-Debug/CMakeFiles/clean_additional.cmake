# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/VS_MockProject_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/VS_MockProject_autogen.dir/ParseCache.txt"
  "VS_MockProject_autogen"
  )
endif()
