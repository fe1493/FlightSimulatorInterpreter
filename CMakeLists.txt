cmake_minimum_required(VERSION 3.15)
project(PleaseWork)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(PleaseWork main.cpp Command.h Command.cpp OpenServerCommand.cpp OpenServerCommand.h
        DefineVarCommand.cpp DefineVarCommand.h Var.cpp Var.h ConnectCommand.cpp ConnectCommand.h InputSymbolTable.cpp InputSymbolTable.h OutputSymbolTable.cpp OutputSymbolTable.h Parser.cpp Parser.h)