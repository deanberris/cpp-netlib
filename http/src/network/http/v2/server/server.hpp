// Copyright 2014 Google, Inc.
// Copyright 2014 Dean Michael Berris <dberris@google.com>
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef NETWORK_HTTP_V2_SERVER_SERVER_HPP_20140126
#define NETWORK_HTTP_V2_SERVER_SERVER_HPP_20140126

#include <cstdint>
#include <utility>

#include "network/http/v2/server/handler_base.hpp"
#include "network/http/v2/server/dynamic_dispatcher.hpp"

namespace network {
namespace http {
namespace v2 {

/** This is the server implementation.
 */
class server {
 public:
  /** These are the options supported by the server at construction time.
   */
  class options {
   public:
    /** Set the port (rvalue references implementation).
     *
     * Example:
     *   options{}.port(80);
     *
     */
    options&& port(uint32_t port) && {
      port_ = port;
      return std::move(*this);
    }

    /** Set the port (lvalue references implementation).
     *
     * Example:
     *	  options options;
     *	  options.port(80);
     *
     */
    options& port(uint32_t port) & {
      port_ = port;
      return *this;
    }

    /** Set the request handler (rvalue references implementation).
     *
     * Example:
     *   options{}.handler(std::make_shared<my_request_handler>());
     *
     */
    options&& handler(std::shared_ptr<request_handler_base> a_handler) && {
      handler_ = std::move(a_handler);
      return std::move(*this);
    }

    /** Set the request handler (lvalue references implementation).
     *
     * Example:
     *	 options options;
     *	 options.handler(std::make_shared<my_request_handler>());
     *
     */
    options& handler(std::shared_ptr<request_handler_base> a_handler) & {
      handler_ = std::move(a_handler);
      return *this;
    }

   private:
    uint32_t port_{0};
    std::shared_ptr<request_handler_base> handler_{std::make_shared<dynamic_dispatcher>()};
  };

  /// A server is default-constructible.
  server() = default;

  /// A server is move-constructible.
  server(server&&) = default;

  /// A server is *not* copy-constructible.
  server(const server&) = delete;

  /// A server can take an rvalue reference to a set of options.
  server(options&& provided_options) : options_(provided_options) {}

  ~server();
 private:
  options options_;
};

}  // namespace v2
}  // namespace http
}  // namespace network

#endif /* end of include guard: NETWORK_HTTP_V2_SERVER_SERVER_HPP_20140126 */

