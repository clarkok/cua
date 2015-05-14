ADD_SUBDIRECTORY (parse)
ADD_SUBDIRECTORY (runtime)

SET (other_SRCS vm.cpp visitor.cpp naive-compiler.cpp compiler.cpp)
SET (cua_SRCS main.cpp ${other_SRCS})

ADD_LIBRARY(for_test STATIC ${other_SRCS})
ADD_EXECUTABLE (cua ${cua_SRCS})

TARGET_LINK_LIBRARIES(
    cua
    parser
    runtime
)
