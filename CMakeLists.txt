cmake_minimum_required(VERSION 3.15)
project(compilergenerator)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
include_directories(include/Phase1_LexicalAnalyzer)
include_directories(include/Phase2_Parser)

add_executable(compilergenerator
        include/Phase1_LexicalAnalyzer/DFA.h
        include/Phase1_LexicalAnalyzer/Lexical_analyzer.h
        include/Phase1_LexicalAnalyzer/Lexical_analyzer_generator.h
        include/Phase1_LexicalAnalyzer/NFA.h
        include/Phase1_LexicalAnalyzer/NFA_constructor.h
        include/Phase1_LexicalAnalyzer/Regular_definition.h
        include/Phase1_LexicalAnalyzer/Regular_expression.h
        include/Phase1_LexicalAnalyzer/Token.h
        include/Phase2_Parser/Parser.h
        include/Phase2_Parser/Parser_generator.h
        include/Phase2_Parser/Parser_table.h
        include/Phase2_Parser/Production.h
        include/Phase2_Parser/Symbol.h
        src/LexicalAnalyzer/DFA.cpp
        src/LexicalAnalyzer/Lexical_analyzer.cpp
        src/LexicalAnalyzer/Lexical_analyzer_generator.cpp
        src/LexicalAnalyzer/NFA.cpp
        src/LexicalAnalyzer/NFA_constructor.cpp
        src/LexicalAnalyzer/Regular_definition.cpp
        src/LexicalAnalyzer/Regular_expression.cpp
        src/LexicalAnalyzer/Token.cpp
        src/Parser/Parser.cpp
        src/Parser/Parser_generator.cpp
        src/Parser/Parser_table.cpp
        src/Parser/Production.cpp
        src/Parser/Symbol.cpp
        main.cpp)
