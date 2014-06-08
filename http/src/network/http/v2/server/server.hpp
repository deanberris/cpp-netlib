// Copyright 2014 Google, Inc.
// Copyright 2014 Dean Michael Berris <dberris@google.com>
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef NETWORK_HTTP_V2_SERVER_SERVER_HPP_20140126
#define NETWORK_HTTP_V2_SERVER_SERVER_HPP_20140126

namespace network {
namespace http {
namespace v2 {

/** This is the server implementation.
 */
class server {
 public:
  /** These are the options supported by the server at construction time.
   */
  struct options {};

  /// A server is default-constructible.
  server() = default;

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

