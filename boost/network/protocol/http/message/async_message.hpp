#ifndef BOOST_NETWORK_PROTOCOL_HTTP_MESSAGE_ASYNC_MESSAGE_HPP_20100622
#define BOOST_NETWORK_PROTOCOL_HTTP_MESSAGE_ASYNC_MESSAGE_HPP_20100622

// Copyright 2010 (c) Dean Michael Berris
// Copyright 2010 (c) Sinefunc, Inc.
// Copyright 2011 Dean Michael Berris (dberris@google.com).
// Copyright 2011 Google, Inc.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/thread/future.hpp>
#include <boost/cstdint.hpp>
#include <boost/optional.hpp>
#include <boost/network/traits/string.hpp>
#include <boost/network/traits/headers_container.hpp>

// FIXME move this out to a trait
#include <set>
#include <boost/foreach.hpp>
#include <boost/network/detail/wrapper_base.hpp>

namespace boost {
namespace network {
namespace http {

namespace impl {

template <class Tag>
struct ready_wrapper;

} /* impl */

template <class Tag>
struct async_message {

  typedef typename string<Tag>::type string_type;
  typedef typename headers_container<Tag>::type headers_container_type;
  typedef typename headers_container_type::value_type header_type;

  async_message()
      : status_message_(),
        version_(),
        source_(),
        destination_(),
        status_(),
        headers_(),
        body_() {}

  async_message(async_message const& other)
      : status_message_(other.status_message_),
        version_(other.version_),
        source_(other.source_),
        destination_(other.destination_),
        status_(other.status_),
        headers_(other.headers_),
        body_(other.body_) {}

  string_type status_message() const { return status_message_.get(); }

  void status_message(boost::shared_future<string_type> const& future) {
    status_message_ = future;
  }

  string_type version() const { return version_.get(); }

  void version(boost::shared_future<string_type> const& future) const {
    version_ = future;
  }

  boost::uint16_t status() const { return status_.get(); }

  void status(boost::shared_future<uint16_t> const& future) {
    status_ = future;
  }

  string_type source() const { return source_.get(); }

  void source(boost::shared_future<string_type> const& future) {
    source_ = future;
  }

  string_type destination() const { return destination_.get(); }

  void destination(boost::shared_future<string_type> const& future) {
    destination_ = future;
  }

  headers_container_type const& headers() const {
    if (retrieved_headers_) return *retrieved_headers_;
    headers_container_type raw_headers = headers_.get();
    raw_headers.insert(added_headers.begin(), added_headers.end());
    BOOST_FOREACH(string_type const & key, removed_headers) {
      raw_headers.erase(key);
    }
    retrieved_headers_ = raw_headers;
    return *retrieved_headers_;
  }

  void headers(boost::shared_future<headers_container_type> const& future) {
    headers_ = future;
  }

  void add_header(typename headers_container_type::value_type const& pair_) {
    added_headers.insert(added_headers.end(), pair_);
  }

  void remove_header(typename headers_container_type::key_type const& key_) {
    removed_headers.insert(key_);
  }

  string_type body() const { return body_.get(); }

  void body(boost::shared_future<string_type> const& future) { body_ = future; }

  void swap(async_message& other) {
    using std::swap;
    swap(status_message_, other.status_message_);
    swap(version_, other.version_);
    swap(source_, other.source_);
    swap(destination_, other.destination_);
    swap(status_, other.status_);
    swap(headers_, other.headers_);
    swap(body_, other.body_);
  }

  async_message& operator=(async_message other) {
    other.swap(*this);
    return *this;
  }

 private:
  mutable boost::shared_future<string_type> status_message_;
  mutable boost::shared_future<string_type> version_;
  mutable boost::shared_future<string_type> source_;
  mutable boost::shared_future<string_type> destination_;
  mutable boost::shared_future<boost::uint16_t> status_;
  mutable boost::shared_future<headers_container_type> headers_;
  mutable boost::shared_future<string_type> body_;
  headers_container_type added_headers;
  std::set<string_type> removed_headers;
  mutable boost::optional<headers_container_type> retrieved_headers_;

  friend struct boost::network::http::impl::ready_wrapper<Tag>;

#ifdef BOOST_NETWORK_ENABLE_WHEN_READY
  template <class, class>
  friend struct boost::network::http::impl::when_ready_wrapper;

  template <class T>
  friend void await(async_message<T>&);
#endif
};

template <class Tag>
inline void swap(async_message<Tag>& lhs, async_message<Tag>& rhs) {
  lhs.swap(rhs);
}

}  // namespace http

}  // namespace network

}  // namespace boost

#endif  // BOOST_NETWORK_PROTOCOL_HTTP_MESSAGE_ASYNC_MESSAGE_HPP_20100622
