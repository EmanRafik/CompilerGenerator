cmake_minimum_required(VERSION 3.15)
project(compilergenerator)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(compilergenerator
        include/DFA.h
        include/Files_manager.h
        include/ID.h
        include/Identifier.h
        include/Keyword.h
        include/Lexical_analyzer.h
        include/NFA.h
        include/Number.h
        include/Punctuation_symbol.h
        include/Regular_definition.h
        include/Regular_expression.h
        include/Token.h
        include/Lexical_analyzer_generator.h
        include/State.h
        src/DFA.cpp
        src/Files_manager.cpp
        src/ID.cpp
        src/Identifier.cpp
        src/Keyword.cpp
        src/Lexical_analyzer.cpp
        src/NFA.cpp
        src/Number.cpp
        src/Punctuation_symbol.cpp
        src/Regular_definition.cpp
        src/Regular_expression.cpp
        src/Token.cpp
        src/Lexical_analyzer_generator.cpp
        src/State.cpp
        main.cpp )
