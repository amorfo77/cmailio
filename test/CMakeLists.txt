
function(add_cmailio_tests SOURCE_FILE)
    get_filename_component(file_name ${SOURCE_FILE} NAME_WE)
    add_executable(${file_name} ${SOURCE_FILE})
    target_link_libraries(${file_name} PUBLIC ${Boost_LIBRARIES} cmailio ${CMAKE_THREAD_LIBS_INIT})
    install(TARGETS ${file_name} DESTINATION "${SHARE_INSTALL_DIR}/${PROJECT_NAME}/test")
endfunction(add_cmailio_tests)

file(GLOB test_files ${CMAKE_CURRENT_SOURCE_DIR}/test*.cpp)
foreach(file_name ${test_files})
    add_cmailio_tests(${file_name})
endforeach(file_name ${test_files})
