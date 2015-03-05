include(findPython)
target_include_directories(${TARGET} PUBLIC ${PYTHON_INCLUDE_DIRS})
target_link_libraries(${TARGET} ${PYTHON_LIBRARIES} ${Boost_LIBRARIES})