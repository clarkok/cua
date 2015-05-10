ADD_SUBDIRECTORY (parse)
ADD_SUBDIRECTORY (runtime)

SET (cua_SRCS main.cpp)
ADD_EXECUTABLE (cua ${cua_SRCS})
