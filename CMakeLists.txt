cmake_minimum_required(VERSION 3.10)
project(DSAKnowledgeGraph)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executable
add_executable(dsa_knowledge_graph dsa_knowledge_graph.cpp)

# Set compiler flags for better debugging and warnings
if(MSVC)
    target_compile_options(dsa_knowledge_graph PRIVATE /W4)
else()
    target_compile_options(dsa_knowledge_graph PRIVATE -Wall -Wextra -pedantic)
endif()

# Optional: Set output directory
set_target_properties(dsa_knowledge_graph PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
