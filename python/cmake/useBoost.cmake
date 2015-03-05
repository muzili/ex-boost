include(findBoost)
target_include_directories(${TARGET} PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(${TARGET} ${Boost_LIBRARIES})