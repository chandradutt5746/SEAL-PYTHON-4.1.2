cmake_minimum_required(VERSION 3.15)
project(SEAL_Python_Bindings VERSION 4.1.2 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Configure SEAL
set(SEAL_USE_INTEL_HEXL ON CACHE BOOL "Enable Intel HEXL acceleration")
add_subdirectory(third_party/SEAL)

# Find pybind11
find_package(pybind11 REQUIRED CONFIG)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core
    ${CMAKE_CURRENT_BINARY_DIR}
    ${PYBIND11_INCLUDE_DIR}
    ${Python_INCLUDE_DIRS}
    ${SEAL_INCLUDE_DIRS}
    
)

set(HEADERS
    # src/core/bind_advanced.h
    src/core/bind_batchencoder.h
    src/core/bind_ciphertext.h
    src/core/bind_ckksencoder.h
    src/core/bind_context.h
    src/core/bind_coeffmodulus.h
    src/core/bind_decryptor.h
    # src/core/bind_encoder.h
    src/core/bind_encryption.h
    src/core/bind_encryptor.h
    src/core/bind_evaluator.h
    src/core/bind_keys.h
    src/core/bind_modulus.h
    src/core/bind_plainmodulus.h
    src/core/bind_plaintext.h
    src/core/bind_random.h
    src/core/bind_security.h
    src/core/bind_serialization.h
    src/core/bind_util.h
)

set(BINDING_SOURCES
    src/core/module.cpp
    # src/core/bind_advanced.cpp
    src/core/bind_batchencoder.cpp
    src/core/bind_ciphertext.cpp
    src/core/bind_ckksencoder.cpp
    src/core/bind_context.cpp
    src/core/bind_coeffmodulus.cpp
    src/core/bind_decryptor.cpp
    # src/core/bind_encoder.cpp
    src/core/bind_util.cpp
    src/core/bind_encryption.cpp
    src/core/bind_encryptor.cpp
    src/core/bind_evaluator.cpp
    src/core/bind_keys.cpp
    src/core/bind_modulus.cpp
    src/core/bind_plainmodulus.cpp
    src/core/bind_plaintext.cpp
    src/core/bind_random.cpp
    src/core/bind_security.cpp
    src/core/bind_serialization.cpp
)

# Define Python module - CHANGE TARGET NAME
pybind11_add_module(seal_python src/core/module.cpp ${BINDING_SOURCES}
)

# Link against SEAL
target_link_libraries(seal_python PRIVATE SEAL::seal)  # Updated target name

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core  # Add source directory to includes
)

# Include directories
target_include_directories(seal_python PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core  
    ${SEAL_SOURCE_DIR}/native/src
    ${SEAL_BINARY_DIR}/native/src
    ${pybind11_INCLUDE_DIRS}
)

# Set output directory and RENAME OUTPUT
set_target_properties(seal_python PROPERTIES  # Updated target name
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/python
    OUTPUT_NAME "seal"  # Force output to be named seal.so
    PREFIX ""
    SUFFIX ".so"
)

# Security hardening
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(seal_python PRIVATE  # Updated target name
        -O3
        -march=native
        -Werror
        -Wall
        -Wextra
        -Wconversion
        -Wsign-conversion
        -fstack-protector-strong
    )
endif()
