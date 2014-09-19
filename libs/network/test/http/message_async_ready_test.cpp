
// Copyright 2010 Dean Michael Berris <dberris@google.com>
// Copyright 2014 Google, Inc.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/version.hpp>

// We only define BOOST_NETWORK_ENABLE_WHEN_READY if Boost is > version 1.55.0.
#if (BOOST_VERSION >= 105500)
#define BOOST_NETWORK_ENABLE_WHEN_READY

// We currently need this for when_ready(...)
#define BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
#endif

#define BOOST_TEST_MODULE HTTP Async Response Test

#include <boost/test/unit_test.hpp>
#include <boost/network/include/http/client.hpp>
#include <boost/network/utils/thread_pool.hpp>
#include "client_types.hpp"

namespace http = boost::network::http;
namespace util = boost::network::utils;

BOOST_AUTO_TEST_CASE_TEMPLATE(unready_state_response_test, client,
                              async_only_client_types) {
  typename client::response r;
  BOOST_CHECK(!ready(r));
}

#ifdef BOOST_NETWORK_ENABLE_WHEN_READY
// We only build these test cases when the BOOST_NETWORK_ENABLE_WHEN_READY macro
// is set. This is dependent on a Boost version that's at least 1.55.0.
struct ready_callback {
  template <class Tag>
  void operator()(http::async_message<Tag> const &response,
                  boost::system::error_code const &ec) const {
    BOOST_CHECK(ready(response));
    BOOST_CHECK(!ec);
  }
};

BOOST_AUTO_TEST_CASE_TEMPLATE(when_ready_valid_response_test, client,
                              async_only_client_types) {
  client http_client;
  typename client::request request("http://www.google.com");
  typename client::response response;
  util::thread_pool threads(1);
  BOOST_REQUIRE_NO_THROW(response = http_client.get(request));
  when_ready(response, ready_callback(), threads);
  await(response);  // block!
}

BOOST_AUTO_TEST_CASE_TEMPLATE(when_ready_valid_response_nothreadpool_test,
                              client, async_only_client_types) {
  client http_client;
  typename client::request request("http://www.google.com");
  typename client::response response = http_client.get(request);
  when_ready(response, ready_callback());
  await(response);  // block!
}
#endif
