# Copyright 2014 Google, Inc.
# Copyright 2014 Dean Michael Berris <dberris@google.com>
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)

set (CPP-NETLIB_SERVER_TESTS construction_test)

foreach (test ${CPP-NETLIB_SERVER_TESTS})
  if (${CMAKE_CXX_COMPILER_ID} MATCHES GNU OR
      ${CMAKE_CXX_COMPILER_ID} MATCHES Clang)
    set_source_files_properties(${test}.cpp
      PROPERTIES COMPILE_FLAGS "-Wall")
  endif()

  add_executable(cpp-netlib-http-v2-server-${test} ${test}.cpp)
  target_link_libraries(cpp-netlib-http-v2-server-${test}
    network-http-v2-server
    ${Boost_LIBRARIES} ${ICU_LIBRARIES} ${ICU_I18N_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT})
  set_target_properties(cpp-netlib-http-v2-server-${test}
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CPP-NETLIB_BINARY_DIR}/tests)
  add_test(cpp-netlib-http-v2-server-${test}
    ${CPP-NETLIB_BINARY_DIR}/tests/cpp-netlib-http-v2-server-${test})
endforeach(test)
