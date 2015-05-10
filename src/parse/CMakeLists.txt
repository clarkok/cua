ADD_CUSTOM_COMMAND(
    COMMAND flex
        -o ${CUA_BINARY_DIR}/src/parse/lex.yy.cpp
        ${CUA_SOURCE_DIR}/src/parse/lex.l
    OUTPUT ${CUA_BINARY_DIR}/src/parse/lex.yy.cpp
    DEPENDS ${CUA_SOURCE_DIR}/src/parse/lex.l
            ${CUA_BINARY_DIR}/src/parse/parser.yy.hpp
)

ADD_CUSTOM_COMMAND(
    COMMAND /usr/local/Cellar/bison/3.0.4/bin/bison -d
        -o ${CUA_BINARY_DIR}/src/parse/parser.yy.cpp
        ${CUA_SOURCE_DIR}/src/parse/parser.y
    OUTPUT ${CUA_BINARY_DIR}/src/parse/parser.yy.cpp
           ${CUA_BINARY_DIR}/src/parse/parser.yy.hpp
    DEPENDS ${CUA_SOURCE_DIR}/src/parse/parser.y
)

SET_SOURCE_FILES_PROPERTIES(
    ${CUA_BINARY_DIR}/src/parse/lex.yy.cpp PROPERTIES GENERATED TRUE)
SET_SOURCE_FILES_PROPERTIES(
    ${CUA_BINARY_DIR}/src/parse/parser.yy.cpp PROPERTIES GENERATED TRUE)
    
INCLUDE_DIRECTORIES(
    ${CUA_SOURCE_DIR}/src/parse/
    ${CUA_BINARY_DIR}/src/parse/
)

ADD_LIBRARY (parser STATIC 
    ${CUA_BINARY_DIR}/src/parse/lex.yy.cpp
    ${CUA_BINARY_DIR}/src/parse/parser.yy.cpp
)