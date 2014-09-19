#ifndef BOOST_NETWORK_PROTOCOL_HTTP_MESSAGE_WRAPPERS_AWAIT_HPP_20140910
#define BOOST_NETWORK_PROTOCOL_HTTP_MESSAGE_WRAPPERS_AWAIT_HPP_20140910

// Copyright 2014 Dean Michael Berris <dberris@google.com>
// Copyright 2014 Google, Inc.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/thread/future.hpp>

namespace boost {
namespace network {
namespace http {

// Forward decl for async_message.
template <class Tag>
struct async_message;

// await is a function that will:
//   - block on the completion of a response object
//   - throw exceptions in case waiting for the completion of a response object
//     throws appropriate exceptions.
//
template <class Tag>
void await(async_message<Tag>& response) {
  // Here, we rely on the ability to use boost::wait_for_all(...), an extension
  // to the future interface.
//  boost::wait_for_all(response.status_message_, response.version_,
//      response.source_, response.destination_, response.status_,
//      response.headers_, response.body_);
  try { response.status_.wait(); } catch (std::exception& e) {
    std::cerr << __LINE__ << ": caught " << e.what();
    throw;
  }
  try { response.status_message_.wait(); } catch (std::exception& e) {
    std::cerr << __LINE__ << ": caught " << e.what();
    throw;
  }
  try { response.version_.wait(); } catch (std::exception& e) {
    std::cerr << __LINE__ << ": caught " << e.what();
    throw;
  }
  try { response.headers_.wait(); } catch (std::exception& e) {
    std::cerr << __LINE__ << ": caught " << e.what();
    throw;
  }
  try { response.source_.wait(); } catch (std::exception& e) {
    std::cerr << __LINE__ << ": caught " << e.what();
    throw;
  }
  try { response.destination_.wait(); } catch (std::exception& e) {
    std::cerr << __LINE__ << ": caught " << e.what();
    throw;
  }
  try { response.body_.wait(); } catch (std::exception& e) {
    std::cerr << __LINE__ << ": caught " << e.what();
    throw;
  }
}

}  // namespace http
}  // namespace network
}  // namespace boost

#endif /* end of include guard: BOOST_NETWORK_PROTOCOL_HTTP_MESSAGE_WRAPPERS_AWAIT_HPP_20140910 */

