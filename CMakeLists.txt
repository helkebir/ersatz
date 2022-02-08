cmake_minimum_required(VERSION 3.16)
project(Ersatz)

set(CMAKE_CXX_STANDARD 11)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    MESSAGE("Building in debug mode.")
    option(WITH_EXAMPLES "Compile examples" ON)
    option(WITH_TESTS "Compile tests" ON)
else()
    option(WITH_EXAMPLES "Compile examples" OFF)
    option(WITH_TESTS "Compile tests" OFF)
endif()

include_directories(ersatz ersatz/dep)

add_library(ersatz STATIC ersatz/Codegen.cpp ersatz/Codegen.hpp ersatz/FunctionBuilder.cpp ersatz/FunctionBuilder.hpp ersatz/ClangFormatter.cpp ersatz/ClangFormatter.hpp ersatz/CodegenLang.hpp ersatz/CodegenLangTraits.cpp ersatz/CodegenLangTraits.hpp ersatz/VariableBuilder.cpp ersatz/VariableBuilder.hpp ersatz/PreambleBuilder.cpp ersatz/PreambleBuilder.hpp)

if(WITH_TESTS)
    add_executable(ersatz_test main.cpp ersatz/dep/catchOnce.hpp test/Codegen_test.cpp)
    target_link_libraries(ersatz_test ersatz)
endif()

if(WITH_EXAMPLES)
    add_custom_target(build-time-make-directory ALL
            COMMAND ${CMAKE_COMMAND} -E make_directory example)

    add_executable(codegen_demo example/Codegen_demo.cpp)
    set_target_properties(codegen_demo PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/example")
    target_link_libraries(codegen_demo ersatz)

    add_executable(codegen_formatting example/Codegen_formatting.cpp)
    set_target_properties(codegen_formatting PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/example")
    target_link_libraries(codegen_formatting ersatz)

    add_executable(codegen_python example/Codegen_Python.cpp)
    set_target_properties(codegen_python PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/example")
    target_link_libraries(codegen_python ersatz)
endif()