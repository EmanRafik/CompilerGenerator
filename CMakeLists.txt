# cmake_minimum_required(VERSION <specify CMake version here>)
project(compilergenerator)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(.idea)
include_directories(bin)
include_directories(include)
include_directories(obj)
include_directories(src)

add_executable(compilergenerator
        .idea/.gitignore
        .idea/compilergenerator.iml
        .idea/misc.xml
        .idea/modules.xml
        .idea/vcs.xml
        .idea/workspace.xml
        bin/Debug/CompilerGenerator.exe
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
        obj/Debug/main.o
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
        CompilerGenerator.cbp
        )
