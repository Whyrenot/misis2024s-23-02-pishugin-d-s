add_executable(test_complex test_complex.cpp)
target_link_libraries(test_complex complex)

add_executable(test_rational test_rational.cpp)
target_link_libraries(test_rational rational)

add_executable(test_dynarr test_dynarr.cpp)
target_link_libraries(test_dynarr dynarr)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT test_dynarr)



add_executable(stack_arr_test stack_arr_test.cpp "stack_arr_test.cpp")
target_link_libraries(stack_arr_test StackArr)



add_executable(test_stack_lst test_stack_lst.cpp "test_stack_lst.cpp")
target_link_libraries(test_stack_lst stacklst)


