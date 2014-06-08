// Copyright 2014 (c) Dean Michael Berris <dberris@google.com>
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef NETWORK_HTTP_V2_SERVER_HANDLER_BASE_HPP_
#define NETWORK_HTTP_V2_SERVER_HANDLER_BASE_HPP_

#include <functional>
#include <memory>
#include <string>

#include "boost/utility/string_ref.hpp"

#include "network/http/v2/server/session.hpp"
#include "network/http/v2/server/connection.hpp"

namespace network {
namespace http {
namespace v2 {

class request_handler_base {
 public:
  /// Request handler function type.
  typedef std::function<void(session, std::shared_ptr<connection>)> handler;

  virtual void register_handler(boost::string_ref path, handler some_handler) = 0;

  virtual ~request_handler_base() = 0;
};

}  // namespace v2
}  // namespace http
}  // namespace network

#endif /* end of include guard: NETWORK_HTTP_V2_SERVER_HANDLER_BASE_HPP_ */

