find_package(Qt6 REQUIRED COMPONENTS Test Widgets)

file(GLOB_RECURSE TEST_FILES CONFIGURE_DEPENDS "tst_*.cpp")

foreach(test_source ${TEST_FILES})
    get_filename_component(test_name ${test_source} NAME_WE)

    qt_add_executable(${test_name}
        ${test_source}
        ../src/account-model.cpp
    )

    target_include_directories(${test_name} PRIVATE ../src)
    target_link_libraries(${test_name} PRIVATE Qt6::Widgets Qt6::Test)

    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()