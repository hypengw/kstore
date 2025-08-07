find_package(Qt6 REQUIRED COMPONENTS Core)

add_library(
  kstore_qt STATIC moc.cpp meta_role.cpp meta_utils.cpp gadget_model.cpp
                   meta_list_model.cpp qtable_proxy_model.cpp)
add_library(kstore::qt ALIAS kstore_qt)

target_compile_features(kstore_qt PRIVATE cxx_std_20)
set_target_properties(kstore_qt PROPERTIES AUTOMOC ON)
target_include_directories(kstore_qt PUBLIC "../../include")
target_link_libraries(kstore_qt PUBLIC Qt6::Core)
