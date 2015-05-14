SET (test_SRCS test-parse.cpp test-table.cpp test-scope.cpp
               test-casting.cpp test-naive-compiler.cpp
               test-enum-class.cpp test-naive-vm.cpp)

ADD_EXECUTABLE (unit_test ${test_SRCS})
TARGET_LINK_LIBRARIES (unit_test gtest gtest_main)
ADD_TEST (
    unit_test unit_test
    COMMAND ${CUA_BINARY_DIR}/test/unit_test
    )

TARGET_LINK_LIBRARIES(
    unit_test 
    parser
    runtime
    for_test
)