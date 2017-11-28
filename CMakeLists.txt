cmake_minimum_required(VERSION 3.8)
project(Project)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_STEMMER stemmer/english.c stemmer/api.c stemmer/utilities.c)
set(SOURCE_FILES main.cpp stemmer.cpp)
add_executable(Project ${SOURCE_FILES} ${SOURCE_STEMMER})
#add_executable(Project ${SOURCE_STEMMER} stemmer/driver.c)