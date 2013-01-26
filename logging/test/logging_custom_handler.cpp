// Copyright (c) 2012 A. Joel Lamotte <mjklaim@gmail.com>
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <string>
#include <sstream>

#include <gtest/gtest.h>

#include <network/logging/logging.hpp>

using namespace network::logging;

TEST(logging_custom_handler, custom_log_handler_output) {
  
  std::stringstream log_output;
  auto custom_log_handler = [&]( const log_record& log )
  {
    log_output << "[CPPNETLIB]<" << log.filename() << ":" << log.line() << "> "
               << log.message();
  };

  const auto line_num = 42;
  const auto file_name = "somewhere.cpp";
  const auto message = "At line " + std::to_string(line_num) + " we check the code.";

  set_log_record_handler( custom_log_handler );
  log( log_record( file_name, line_num ) << "At line " << line_num << " we check the code." );

  const auto result_output = log_output.str();

  ASSERT_TRUE( !result_output.empty() );
  ASSERT_TRUE( result_output == "[CPPNETLIB]<somewhere.cpp:42> " + message );
}
