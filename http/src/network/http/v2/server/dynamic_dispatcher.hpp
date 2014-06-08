// Copyright 2014 Google, Inc.
// Copyright 2014 Dean Michael Berris <dberris@google.com>
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef NETWORK_HTTP_V2_SERVER_DYNAMIC_DISPATCHER_HPP_
#define NETWORK_HTTP_V2_SERVER_DYNAMIC_DISPATCHER_HPP_

#include <unordered_map>

#include "boost/utility/string_ref.hpp"

#include "network/http/v2/server/handler_base.hpp"

namespace network {
namespace http {
namespace v2 {

class dynamic_dispatcher : public request_handler_base {
 public:
  void register_handler(
      boost::string_ref path,
      request_handler_base::handler some_handler) override;
  virtual ~dynamic_dispatcher();

 private:
  std::unordered_map<std::string, request_handler_base::handler> handlers_;
};

}  // namespace v2
}  // namespace http
}  // namespace network

#endif /* end of include guard: NETWORK_HTTP_V2_SERVER_DYNAMIC_DISPATCHER_HPP_ */

