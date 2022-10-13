cmake_minimum_required(VERSION 3.23)

### C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DU_STATIC_IMPLEMENTATION")

project("icu4c-playground")

add_library(sicuio STATIC IMPORTED)

set_property(
  TARGET sicuio APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE
)

set_target_properties(sicuio PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${ICU_ROOT}/lib/libsicuio.a"
)
  
set_target_properties(sicuio PROPERTIES
  MAP_IMPORTED_CONFIG_MINSIZEREL Release
  MAP_IMPORTED_CONFIG_RELWITHDEBINFO Release
)

target_include_directories(sicuio INTERFACE "${ICU_ROOT}/include")



add_library(sicuuc STATIC IMPORTED)

set_property(
  TARGET sicuuc APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE
)

set_target_properties(sicuuc PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${ICU_ROOT}/lib/libsicuuc.a"
)
  
set_target_properties(sicuuc PROPERTIES
  MAP_IMPORTED_CONFIG_MINSIZEREL Release
  MAP_IMPORTED_CONFIG_RELWITHDEBINFO Release
)

target_include_directories(sicuuc INTERFACE "${ICU_ROOT}/include")






# add_library(sicudt STATIC IMPORTED)

# set_property(
#   TARGET sicudt APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE
# )

# set_target_properties(sicudt PROPERTIES
#   IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
#   IMPORTED_LOCATION_RELEASE "${ICU_ROOT}/lib/libsicudt.a"
# )
  

# set_target_properties(sicudt PROPERTIES
#   MAP_IMPORTED_CONFIG_MINSIZEREL Release
#   MAP_IMPORTED_CONFIG_RELWITHDEBINFO Release
# )

# target_include_directories(sicudt INTERFACE "${ICU_ROOT}/include")


add_library(icudt STATIC IMPORTED)

set_property(
  TARGET icudt APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE
)

set_target_properties(icudt PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${ICU_ROOT}/bin/libicudt.a"
)
  

set_target_properties(icudt PROPERTIES
  MAP_IMPORTED_CONFIG_MINSIZEREL Release
  MAP_IMPORTED_CONFIG_RELWITHDEBINFO Release
)

target_include_directories(icudt INTERFACE "${ICU_ROOT}/include")





add_library(sicuin STATIC IMPORTED)

set_property(
  TARGET sicuin APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE
)

set_target_properties(sicuin PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${ICU_ROOT}/lib/libsicuin.a"
)
  
set_target_properties(sicuin PROPERTIES
  MAP_IMPORTED_CONFIG_MINSIZEREL Release
  MAP_IMPORTED_CONFIG_RELWITHDEBINFO Release
)

target_include_directories(sicuin INTERFACE "${ICU_ROOT}/include")

SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")

add_executable(${PROJECT_NAME}
    "src/main.cpp"
)

target_link_libraries(${PROJECT_NAME} sicuio sicuin sicuuc icudt)
