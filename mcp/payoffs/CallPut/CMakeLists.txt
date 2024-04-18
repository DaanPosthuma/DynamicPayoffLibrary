add_library (CallPut SHARED CallPutInterface.cpp CallPutPayoff.cpp)
target_link_options(CallPut PRIVATE 
        /DEF:${CMAKE_CURRENT_SOURCE_DIR}/../DynamicPayoffInterface.def
)
target_link_libraries(CallPut PRIVATE common)
