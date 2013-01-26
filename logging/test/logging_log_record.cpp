// Copyright (c) 2012 A. Joel Lamotte <mjklaim@gmail.com>
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <string>

#include <gtest/gtest.h>

#include <network/logging/logging.hpp>
#define NETWORK_ENABLE_LOGGING
#include <network/detail/debug.hpp>

using namespace network::logging;

TEST(logging_log_record, default_constructor) {
  log_record record;
  ASSERT_TRUE( record.message() == "" );
  ASSERT_TRUE( record.filename() == log_record::UNKNOWN_FILE_NAME );
  ASSERT_TRUE( record.line() == 0 );
}

TEST(logging_log_record, cstring_constructor) {
  const auto message = "This is a test.";
  log_record record( message );
  ASSERT_TRUE( record.message() == message );
  ASSERT_TRUE( record.filename() == log_record::UNKNOWN_FILE_NAME );
  ASSERT_TRUE( record.line() == 0 );
}

TEST(logging_log_record, string_constructor) {
  const std::string message("This is a test.");
  log_record record( message );
  ASSERT_TRUE( record.message() == message );
  ASSERT_TRUE( record.filename() == log_record::UNKNOWN_FILE_NAME );
  ASSERT_TRUE( record.line() == 0 );
}

TEST(logging_log_record, int_constructor) {
  const auto num = 42;
  log_record record( num );
  ASSERT_TRUE( record.message() == std::to_string( num ) );
  ASSERT_TRUE( record.filename() == log_record::UNKNOWN_FILE_NAME );
  ASSERT_TRUE( record.line() == 0 );
}

TEST(logging_log_record, info_constructor) {
  const auto line_num = 42;
  const auto file_name = "somewhere.cpp";
  log_record record( file_name, line_num );
  ASSERT_TRUE( record.message() == "" );
  ASSERT_TRUE( record.filename() == file_name );
  ASSERT_TRUE( record.line() == line_num );
}

TEST(logging_log_record, text_stream) {
  const auto line_num = 42;
  const auto file_name = "somewhere.cpp";
  const auto message = "At line " + std::to_string(line_num) + " we check the code.";
  log_record record( file_name, line_num );

  record << "At line " << line_num << " we check the code.";

  ASSERT_TRUE( record.message() == message );
  ASSERT_TRUE( record.filename() == file_name );
  ASSERT_TRUE( record.line() == line_num );
}

TEST(logging_log_record, raw_log) {
  log( "This is a raw log." );
}

TEST(logging_log_record, macro_log) {
  NETWORK_MESSAGE( "This is a log through the macro." );
  NETWORK_MESSAGE( "This is a log through the macro, with a stream! Num=" << 42  << " - OK!" );
}