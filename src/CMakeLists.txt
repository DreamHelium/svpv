add_executable(svpv_isoc main.cpp reader.cpp reader.h)

target_link_libraries(svpv_isoc "${dhutil_LIBRARIES}" "${GIO_LIBRARIES}"
"${XML_LIBRARIES}")

message("${XML_INCLUDE_DIRS}")

target_include_directories(svpv_isoc PUBLIC "${dhutil_INCLUDE_DIRS}" "${GIO_INCLUDE_DIRS}"
"${XML_INCLUDE_DIRS}")

target_link_directories(svpv_isoc PUBLIC "${dhutil_LIBRARY_DIRS}")
