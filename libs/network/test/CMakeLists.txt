#            Copyright (c) Dean Michael Berris 2010.
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)

include_directories(${CPP-NETLIB_SOURCE_DIR})
find_package( Boost 1.41.0 COMPONENTS unit_test_framework system regex date_time thread filesystem )
find_package( OpenSSL )
find_package( Threads )
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
find_package( EXPAT )
find_package( LibXml2 )

add_subdirectory(http)

if (Boost_FOUND)
    set(
        TESTS
        message_test
        message_transform_test
        url_test
        utils_thread_pool
        )
    foreach (test ${TESTS})
        set_source_files_properties(${test}.cpp
            PROPERTIES COMPILE_FLAGS "-Wall")
        add_executable(cpp-netlib-${test} ${test}.cpp)
	add_dependencies(cpp-netlib-${test} cppnetlib-uri-parsers)

        # add_dependencies(cpp-netlib-${test} cppnetlib-uri-parsers)
        # target_link_libraries(cpp-netlib-${test} ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} cppnetlib-uri-parsers)
        target_link_libraries(cpp-netlib-${test} ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} cppnetlib-uri-parsers)
        if (OPENSSL_FOUND)
            target_link_libraries(cpp-netlib-${test} ${OPENSSL_LIBRARIES})
        endif()
        set_target_properties(cpp-netlib-${test}
            PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CPP-NETLIB_BINARY_DIR}/tests)
        add_test(cpp-netlib-${test} ${CPP-NETLIB_BINARY_DIR}/tests/cpp-netlib-${test})
    endforeach (test)

    add_executable(cpp-netlib-xml_element_tests xml_wrappers/xml_element_tests.cpp)
    target_link_libraries(cpp-netlib-xml_element_tests ${Boost_LIBRARIES})
    add_test(cpp-netlib-xml_element_tests ../../../build/tests/cpp-netlib-xml_element_tests)

    set_target_properties(cpp-netlib-xml_element_tests
                          PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../../../build/tests)

    add_executable(cpp-netlib-xmpp_message_tests xmpp/xmpp_message_tests.cpp)
    add_executable(cpp-netlib-xmpp_presence_tests xmpp/xmpp_presence_tests.cpp)
    add_executable(cpp-netlib-xmpp_iq_tests xmpp/xmpp_iq_tests.cpp)
    add_executable(cpp-netlib-xmpp_namespace_tests xmpp/xmpp_namespace_tests.cpp)
    target_link_libraries(cpp-netlib-xmpp_message_tests ${Boost_LIBRARIES})
    target_link_libraries(cpp-netlib-xmpp_presence_tests ${Boost_LIBRARIES})
    target_link_libraries(cpp-netlib-xmpp_iq_tests ${Boost_LIBRARIES})
    target_link_libraries(cpp-netlib-xmpp_namespace_tests ${Boost_LIBRARIES})
    set_target_properties(cpp-netlib-xmpp_message_tests
                          cpp-netlib-xmpp_presence_tests
                          cpp-netlib-xmpp_iq_tests
                          cpp-netlib-xmpp_namespace_tests
                          PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../../../build/tests)
    add_test(cpp-netlib-xmpp_message_tests ../../../build/tests/cpp-netlib-xmpp_message_tests)
    add_test(cpp-netlib-xmpp_presence_tests ../../../build/tests/cpp-netlib-xmpp_presence_tests)
    add_test(cpp-netlib-xmpp_iq_tests ../../../build/tests/cpp-netlib-xmpp_iq_tests)
    add_test(cpp-netlib-xmpp_namespace_tests ../../../build/tests/cpp-netlib-xmpp_namespace_tests)

    if (EXPAT_FOUND)
      include_directories( ${EXPAT_INCLUDE_DIRS} )
      add_executable(cpp-netlib-expat_element_parser_tests xml_wrappers/expat_element_parser_tests.cpp)
      target_link_libraries(cpp-netlib-expat_element_parser_tests ${Boost_LIBRARIES} ${EXPAT_LIBRARIES})
      add_test(cpp-netlib-expat_element_parser_tests ../../../build/tests/cpp-netlib-expat_element_parser_tests)

      add_executable(cpp-netlib-xmpp_client_tests xmpp/xmpp_client_tests.cpp)
      target_link_libraries(cpp-netlib-xmpp_client_tests ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${EXPAT_LIBRARIES})
      add_test(cpp-netlib-xmpp_client_tests ../../../build/tests/cpp-netlib-xmpp_client_tests)

      set_target_properties(cpp-netlib-expat_element_parser_tests
                            cpp-netlib-xmpp_client_tests
                            PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../../../build/tests)
    endif()

    if (LIBXML2_FOUND)
      include_directories( ${LIBXML2_INCLUDE_DIR} )
      add_executable(cpp-netlib-libxml2_element_parser_tests xml_wrappers/libxml2_element_parser_tests.cpp)
      target_link_libraries(cpp-netlib-libxml2_element_parser_tests ${Boost_LIBRARIES} ${LIBXML2_LIBRARIES})
      add_test(cpp-netlib-libxml2_element_parser_tests ../../../build/tests/cpp-netlib-libxml2_element_parser_tests)
      set_target_properties(cpp-netlib-libxml2_element_parser_tests
                            PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../../../build/tests)
    endif()

endif()
