# tests/CMakeLists.txt

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/model)

# Add the test executable
add_executable(dashboard_model_test dashboard_model_test.cpp
                                    
)

# Link Google Test and your project's code
target_link_libraries(dashboard_model_test gtest gtest_main)

# Add the test to CTest
add_test(NAME DashboardModelTests COMMAND dashboard_model_test)

