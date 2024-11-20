# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\PlateRecognizeSystem_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\PlateRecognizeSystem_autogen.dir\\ParseCache.txt"
  "PlateRecognizeSystem_autogen"
  )
endif()
