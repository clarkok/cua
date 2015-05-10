SET(runtime_SRCS table.cpp runtime.cpp value.cpp hash.cpp scope.cpp)

ADD_LIBRARY(runtime STATIC ${runtime_SRCS})