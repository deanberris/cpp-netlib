// Copyright 2014 Google, Inc.
// Copyright 2014 Dean Michael Berris <dberris@google.com>
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <igloo/igloo_alt.h>

#include "network/http/v2/server/server.hpp"

using namespace igloo;
namespace http = network::http::v2;

Describe(http_server) {
  It(constructs_with_default_options) {
    http::server server;
    static_cast<void>(server);
  }
};

int main(int argc, char* argv[]) {
  return TestRunner::RunAllTests(argc, const_cast<const char**>(argv));
}
