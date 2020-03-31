cmake_minimum_required(VERSION 3.15)
project(compilergenerator)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(compilergenerator
        include/DFA.h
        include/Lexical_analyzer.h
        include/Lexical_analyzer_generator.h
        include/NFA.h
        include/NFA_constructor.h
        include/Regular_definition.h
        include/Regular_expression.h
        include/Token.h
        src/DFA.cpp
        src/Lexical_analyzer.cpp
        src/Lexical_analyzer_generator.cpp
        src/NFA.cpp
        src/NFA_constructor.cpp
        src/Regular_definition.cpp
        src/Regular_expression.cpp
        src/Token.cpp
        main.cpp)
