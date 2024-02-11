add_executable(stack_arr_test stack_arr_test.cpp "stack_arr_test.cpp")

target_link_libraries(stack_arr_test stack)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT test_stack)