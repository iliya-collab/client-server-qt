cmake_minimum_required(VERSION 3.19)
project(server_client)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


#find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets )
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Network)

get_target_property(Qt6Core_includes Qt6::Core INTERFACE_INCLUDE_DIRECTORIES)
get_target_property(Qt6Widgets_includes Qt6::Widgets INTERFACE_INCLUDE_DIRECTORIES)
get_target_property(Qt6Network_includes Qt6::Network INTERFACE_INCLUDE_DIRECTORIES)

qt_standard_project_setup()

set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
set(HEADER_DIR "${CMAKE_SOURCE_DIR}/inc")

file(GLOB_RECURSE MY_SOURCES 
    "${SOURCE_DIR}/*.cpp"
    "${SOURCE_DIR}/*.c"
)

file(GLOB_RECURSE MY_HEADERS 
    "${HEADER_DIR}/*.h"
    "${HEADER_DIR}/*.hpp"
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${TYPE_PROG})

qt_add_executable(${PROJECT_NAME}
    WIN32 MACOSX_BUNDLE
    ${MY_SOURCES}
    ${MY_HEADERS}
)

target_include_directories(${PROJECT_NAME} PRIVATE 
    ${HEADER_DIR}
    ${Qt6Core_includes}
    ${Qt6Widgets_includes}
    ${Qt6Network_includes}
)

target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE
    ${Qt6Core_includes}
    ${Qt6Widgets_includes}
    ${Qt6Network_includes}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Network
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

include(GNUInstallDirs)

#[[if(DEFINED TYPE_PROG)
    unset(TYPE_PROG CACHE)
endif()]]

#[[install(TARGETS ${PROJECT_NAME}
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET ${PROJECT_NAME}
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})]]