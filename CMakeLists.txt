cmake_minimum_required(VERSION 3.2)

# Set project version
project(ip_filter VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

# Set automoc om
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Find packages
find_package(Qt5  REQUIRED COMPONENTS  Widgets Test)

# Configure version file
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/include/version.h.in 
	${CMAKE_CURRENT_SOURCE_DIR}/include/version.h)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include
                    ${CMAKE_CURRENT_SOURCE_DIR}/include/tests)

# Set target names
set(main_target "ipfilter_main")
set(test_target "test_ipfilter")

# Add executables
add_executable(${main_target} ${CMAKE_CURRENT_SOURCE_DIR}/src/ip_filter.cpp)
add_executable(${test_target} ${CMAKE_CURRENT_SOURCE_DIR}/src/tests/main_test.cpp)

# Add libraries
add_library(version ${CMAKE_CURRENT_SOURCE_DIR}/src/version.cpp)

# Set target properties
set_target_properties(${main_target} version ${test_target} PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

# Include directories for libraries
target_include_directories(version
    PRIVATE "${CMAKE_BINARY_DIR}"
)

# Link libraries with main target
target_link_libraries(${main_target} PRIVATE
     version
)

#target_include_directories(${test_target} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/tests"
#                                             "${CMAKE_CURRENT_SOURCE_DIR}/include"
#                                              )

# Link libraries with test target
target_link_libraries(${test_target}
    version Qt5::Widgets Qt5::Test
)

# Print include directories for main target
get_target_property(${main_target}_dirs ${main_target} INCLUDE_DIRECTORIES)
message(STATUS "Include directories for ${main_target}:")
foreach(dir ${${main_target}_dirs})
  message(STATUS "'${dir}'")
endforeach()

# Print include directories for test target
get_target_property(${test_target}_dirs ${test_target} INCLUDE_DIRECTORIES)
message(STATUS "Include directories for ${test_target}:")
foreach(dir ${${test_target}_dirs})
  message(STATUS "'${dir}'")
endforeach()

# Compile options
if (MSVC)
    target_compile_options(${main_target} PRIVATE
	    /W4
    )
    target_compile_options(version PRIVATE
            /W4
    )
    target_compile_options(${test_target} PRIVATE
            /W4
    )
else ()
    target_compile_options(${main_target} PRIVATE
            -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(version PRIVATE
            -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(${test_target} PRIVATE
            -Wall -Wextra -pedantic -Werror
    )
endif()

# Install main target
install(TARGETS ${main_target} RUNTIME DESTINATION bin)

# CPack
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT testov@protei.ru)
include(CPack)

# Testing
enable_testing()
add_test(${test_target} ${test_target})
