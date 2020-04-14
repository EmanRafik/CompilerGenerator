cmake_minimum_required(VERSION 3.15)
project(compilergenerator)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(compilergenerator
        include/LexicalAnalyzer/DFA.h
        include/LexicalAnalyzer/Lexical_analyzer.h
        include/LexicalAnalyzer/Lexical_analyzer_generator.h
        include/LexicalAnalyzer/NFA.h
        include/LexicalAnalyzer/NFA_constructor.h
        include/LexicalAnalyzer/Regular_definition.h
        include/LexicalAnalyzer/Regular_expression.h
        include/LexicalAnalyzer/Token.h
        src/LexicalAnalyzer/DFA.cpp
        src/LexicalAnalyzer/Lexical_analyzer.cpp
        src/LexicalAnalyzer/Lexical_analyzer_generator.cpp
        src/LexicalAnalyzer/NFA.cpp
        src/LexicalAnalyzer/NFA_constructor.cpp
        src/LexicalAnalyzer/Regular_definition.cpp
        src/LexicalAnalyzer/Regular_expression.cpp
        src/LexicalAnalyzer/Token.cpp
        main.cpp)
