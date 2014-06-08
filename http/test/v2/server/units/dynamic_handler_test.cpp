// Copyright 2014 (c) Dean Michael Berris <dberris@google.com>
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <gtest/gtest.h>
#include <functional>
#include "network/http/v2/server/handler_base.hpp"

namespace http = network::http::v2;

class CustomRequestHandler : public http::request_handler_base {
 public:
  void register_handler(boost::string_ref path, handler some_handler) override {
    // Do nothing here.
  };
  ~CustomRequestHandler();
};

TEST(RequestHandlerTest, ConstructorTest) {
  auto handler = std::make_shared<CustomRequestHandler>();
}
