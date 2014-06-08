// Copyright 2014 Google, Inc.
// Copyright 2014 Dean Michael Berris <dberris@google.com>
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "network/http/v2/server/dynamic_dispatcher.hpp"

namespace network {
namespace http {
namespace v2 {

void dynamic_dispatcher::register_handler(boost::string_ref path,
    request_handler_base::handler a_handler) {
  handlers_.emplace(
      std::piecewise_construct,
      std::forward_as_tuple(path.to_string()),
      std::forward_as_tuple(std::move(a_handler)));
}

dynamic_dispatcher::~dynamic_dispatcher() {}

}  // namespace v2
}  // namespace http
}  // namespace network
