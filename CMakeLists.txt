cmake_minimum_required(VERSION 3.28)

project(
  KStore
  VERSION 0.1.1
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

option(KSTORE_BUILD_TESTS "Build tests" ${PROJECT_IS_TOP_LEVEL})

add_subdirectory(src/qt)
add_library(meta_model STATIC src/share_store.cpp)
add_library(meta_model::meta_model ALIAS meta_model)

target_compile_features(meta_model PRIVATE cxx_std_20)
target_include_directories(meta_model PUBLIC include)
target_link_libraries(meta_model PRIVATE kstore_qt)

if(KSTORE_BUILD_TESTS)
  include(CTest)
  enable_testing()
  add_subdirectory(test)
endif()
