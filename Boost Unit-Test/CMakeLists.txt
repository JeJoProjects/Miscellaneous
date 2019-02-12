cmake_minimum_required(VERSION 3.0.0)

project("Unit_Test_Project")


file(GLOB SOURCES
    *.h
    *.hpp
    *.cc
    *.cpp
)

file(GLOB LIBS
# if it is GCC Dynamic     = *.a and *.dll
   *.a    # if GCC Static  = *.a only
   *.dll
# if it is MSVS Dynamic    = *.lib and *.dll
   *.lib  # if MSVS Static = *.lib only
   *.dll
)

# set the variables for both INCLUDE and LIB Files
set(BOOST_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies)
#set(BOOST_LIBS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/Libs_MSVS2017_Static)
set(BOOST_LIBS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/Libs_GCC_Shared)

# tell where the HEADERs are  and the linker where the BINARIES(LIBs) are
include_directories(${BOOST_INCLUDE_DIR})
link_directories(${BOOST_LIBS_DIR})

# make the single executable using the sources in the current cmake dir
add_executable(${PROJECT_NAME} ${SOURCES})

# Link the external LIBs to the executable
target_link_libraries(${PROJECT_NAME} ${LIBS})
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

# set the compiler std to build
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

