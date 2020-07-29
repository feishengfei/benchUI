function(TestCase NAME)
    if(EXISTS "${PROJECT_SOURCE_DIR}/samples/${TYPE}/${NAME}.cpp")
   	    add_executable(${NAME} ${TYPE}/${NAME}.cpp)
	    set(ALL_LIBRARIES ${FRAMEWORK_NAME} ${OPENGL_LIBRARIES} ${PLATFORM_LIBRARIES})
	    target_link_libraries(${NAME} ${ALL_LIBRARIES})

	    install(TARGETS ${NAME} 
	        DESTINATION ${CMAKE_INSTALL_PREFIX}/${TYPE}/${NAME})
    else()
        message(FATAL_ERROR "${PROJECT_SOURCE_DIR}/samples/${TYPE}/${NAME}.cpp not exists")
    endif()
endfunction(TestCase)

foreach(FNAME ${CASE_NAME})
    TestCase(${FNAME})
endforeach(FNAME)
