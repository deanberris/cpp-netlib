#ifndef BOOST_NETWORK_PROTOCOL_HTTP_MESSAGE_WRAPPERS_WHEN_READY_HPP_20140902
#define BOOST_NETWORK_PROTOCOL_HTTP_MESSAGE_WRAPPERS_WHEN_READY_HPP_20140902

// Copyright 2014 Dean Michael Berris <dberris@google.com>
// Copyright 2014 Google, Inc.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/make_shared.hpp>
#include <boost/network/detail/wrapper_base.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/system/error_code.hpp>
#include <boost/network/traits/string.hpp>
#include <boost/thread/future.hpp>

namespace boost {
namespace network {
namespace http {

// Forward decl for async_message.
template <class Tag> struct async_message;

namespace impl {

template <class Tag, class Callback>
struct when_ready_wrapper :
  boost::enable_shared_from_this<when_ready_wrapper<Tag, Callback> >,
  detail::wrapper_base_const<Tag, async_message<Tag> > {

  typedef detail::wrapper_base_const<Tag, async_message<Tag> > wrapper_base;
  typedef typename string<Tag>::type string_type;

  when_ready_wrapper(async_message<Tag> const& message, Callback callback)
      : wrapper_base(message),
	message_(message),
	callback_(callback) {}

  async_message<Tag> message_;
  Callback callback_;

  template <class ThreadPool>
  void operator()(ThreadPool& threadpool) {
    wrapper_base::_message.body_.then(boost::bind(
	  &when_ready_wrapper<Tag, Callback>::body_ready<ThreadPool, string_type>,
	  when_ready_wrapper<Tag, Callback>::shared_from_this(),
	  boost::ref(threadpool), _1));
  }

  // This version of the operation causes the implementation to not defer
  // the execution of the callback to a different threadpool. This means
  // that the callback will be executed in the HTTP handling threads.
  void operator()() {
    wrapper_base::_message.body_.then(boost::bind(
	  &when_ready_wrapper<Tag, Callback>::body_ready<string_type>,
	  when_ready_wrapper<Tag, Callback>::shared_from_this(), _1));
  }

  // This deals with the version that supports/uses thread-pools.
  template <class ThreadPool, class String>
  void body_ready(ThreadPool& threadpool, boost::shared_future<String> const &f) {
    try {
      f.wait();
      threadpool.post(boost::bind(&when_ready_wrapper<Tag, Callback>::run_callback,
	    when_ready_wrapper<Tag, Callback>::shared_from_this(),
	    boost::system::error_code()));
    } catch (boost::system::error_code& ec) {
      threadpool.post(boost::bind(&when_ready_wrapper<Tag, Callback>::run_callback,
	  when_ready_wrapper<Tag, Callback>::shared_from_this(), ec));
    }
  }

  // This executes the callback immediately in the same thread (usually an
  // HTTP handling thread.
  template <class String>
  void body_ready(boost::shared_future<String> const &future) {
    try {
      future.wait();
      callback_(message_, boost::system::error_code());
    } catch (boost::system::error_code& ec) {
      callback_(message_, ec);
    }
  }

  void run_callback(boost::system::error_code const &ec) {
    callback_(message_, ec);
  }
};

}  // namespace impl

// Takes the following parameters:
//   - the response message
//   - a callback to execute
//   - the threadpool to execute the callback in
//
// This function returns immediately and execution of the provided callback may
// happen at a later time.
//
// This version of the implementation allows for explicitly scheduling the work
// of the callback in a different threadpool. We assume that a ThreadPool
// supports a post member function. We also require that the threadpool lasts
// longer than the function.
//
template <class Tag, class Callback, class ThreadPool>
inline void when_ready(async_message<Tag> const &message, Callback callback,
		       ThreadPool& threadpool) {
  boost::shared_ptr<impl::when_ready_wrapper<Tag, Callback> > deferred_to =
      boost::make_shared<impl::when_ready_wrapper<Tag, Callback> >(
	  message, callback);
  return (*deferred_to)(threadpool);
}

// Takes the following parameters:
//   - the response message
//   - a callback to execute
//
// This function returns immediately and execution of the provided callback may
// happen at a later time.
//
// This version of the function doesn't take an explicit threadpool, so the
// callback provided is executed in the same threads handling the HTTP
// request/response processing.
//
template <class Tag, class Callback>
inline void when_ready(async_message<Tag> const &message, Callback callback) {
  boost::shared_ptr<impl::when_ready_wrapper<Tag, Callback> > deferred_to =
      boost::make_shared<impl::when_ready_wrapper<Tag, Callback> >(
	  message, callback);
  return (*deferred_to)();
}

}  // namespace http
}  // namespace network
}  // namespace boost

#endif  // BOOST_NETWORK_PROTOCOL_HTTP_MESSAGE_WRAPPERS_WHEN_READY_HPP_20140902

