add_library(robocrawl robocrawl.cpp robocrawl.hpp)
set_property(TARGET robocrawl PROPERTY CXX_STANDARD 20)
target_include_directories(robocrawl PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
  $<INSTALL_INTERFACE:include>
)
install(TARGETS robocrawl)