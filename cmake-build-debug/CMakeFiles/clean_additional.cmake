# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/videoPlayer_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/videoPlayer_autogen.dir/ParseCache.txt"
  "videoPlayer_autogen"
  )
endif()
