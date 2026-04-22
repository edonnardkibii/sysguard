add_executable(sysguard_tests
    test_monitor_engine.cpp
    ../src/monitor_engine.cpp
)

target_include_directories(sysguard_tests
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

add_test(
    NAME sysguard_tests
    COMMAND sysguard_tests
)