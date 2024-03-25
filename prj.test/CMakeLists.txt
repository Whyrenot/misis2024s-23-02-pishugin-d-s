add_executable(test_complex test_complex.cpp)
target_link_libraries(test_complex complex)

add_executable(test_rational test_rational.cpp)
target_link_libraries(test_rational rational)

add_executable(test_dynarr test_dynarr.cpp)
target_link_libraries(test_dynarr dynarr)


add_executable(stack_arr_test stack_arr_test.cpp "stack_arr_test.cpp")
target_link_libraries(stack_arr_test StackArr)



add_executable(test_stack_lst test_stack_lst.cpp "test_stack_lst.cpp")
target_link_libraries(test_stack_lst stacklst)


add_executable(test_queue_lst test_queue_lst.cpp "test_queue_lst.cpp")
target_link_libraries(test_queue_lst queuelst)

add_executable(test_queue_arr test_queue_arr.cpp "test_queue_arr.cpp")
target_link_libraries(test_queue_arr queuearr)

add_executable(test_bitset test_bitset.cpp "test_bitset.cpp")
target_link_libraries(test_bitset bitset)

