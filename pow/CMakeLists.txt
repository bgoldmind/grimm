if (POLICY CMP0074)
  cmake_policy(SET CMP0074 NEW)
endif()

set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR};${CMAKE_MODULE_PATH}")

include_directories(impl)

set(POW_SRC
    equihash.cpp
    ${PROJECT_SOURCE_DIR}/3rdparty/crypto/equihash_impl.cpp
    ${PROJECT_SOURCE_DIR}/3rdparty/arith_uint256.cpp
    ${PROJECT_SOURCE_DIR}/3rdparty/uint256.cpp
    ${PROJECT_SOURCE_DIR}/3rdparty/utilstrencodings.cpp
)

if(UNIX)
    set_source_files_properties(impl/crypto/equihash_impl.cpp PROPERTIES COMPILE_FLAGS -O2)
endif()


    add_library(pow STATIC ${POW_SRC})


target_compile_definitions(pow PRIVATE ENABLE_MINING)

add_dependencies(pow crypto randomx)
target_link_libraries(pow crypto randomx)
if(Boost_FOUND)
    target_link_libraries(pow boost)
endif()

target_include_directories(pow PRIVATE ${PROJECT_SOURCE_DIR}/3rdparty/crypto)

add_library(external_pow STATIC
    external_pow_stub.cpp
    stratum.cpp
    stratum_server.cpp
)

add_dependencies(external_pow core p2p pow randomx)
target_link_libraries(external_pow p2p pow core randomx)

if (NOT ANDROID)
    add_executable(miner_client miner_client.cpp ../core/block_crypt.cpp) # ???????????????????????????
    if (Boost_FOUND)
        find_package(Boost COMPONENTS program_options)
        add_dependencies(miner_client external_pow  Boost::program_options randomx)
        target_link_libraries(miner_client external_pow Boost::program_options randomx)
    else()
        add_dependencies(miner_client external_pow boost_program_options randomx)
        target_link_libraries(miner_client external_pow boost_program_options randomx)
    endif()

    add_subdirectory(unittests)
endif()
