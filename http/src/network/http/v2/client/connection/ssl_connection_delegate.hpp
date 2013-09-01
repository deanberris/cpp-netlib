// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef __NETWORK_HTTP_V2_CLIENT_CONNECTION_SSL_CONNECTION_DELEGATE_INC__
#define __NETWORK_HTTP_V2_CLIENT_CONNECTION_SSL_CONNECTION_DELEGATE_INC__

#include "network/http/v2/client/connection/connection_delegate.hpp"
#include "network/http/v2/client/client_options.hpp"
#include <memory>
#include <vector>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/asio/placeholders.hpp>

namespace network {
  namespace http {
    namespace v2 {
      class ssl_connection_delegate
	: public connection_delegate, std::enable_shared_from_this<ssl_connection_delegate> {

	ssl_connection_delegate(const ssl_connection_delegate &) = delete;
	ssl_connection_delegate &operator = (const ssl_connection_delegate &) = delete;

      public:

	ssl_connection_delegate(boost::asio::io_service &io_service, const client_options &options)
	  : io_service_(io_service)
	  , options_(options) {

	}

	virtual ~ssl_connection_delegate() noexcept {

	}

	virtual void connect(boost::asio::ip::tcp::endpoint &endpoint,
			     const std::string &host,
			     std::function<void (const boost::system::error_code &)> handler) {
	  context_.reset(
			 new boost::asio::ssl::context(boost::asio::ssl::context::sslv23));
	  std::vector<std::string> const& certificate_paths =
	    options_.openssl_certificate_paths();
	  std::vector<std::string> const& verifier_paths =
	    options_.openssl_verify_paths();
	  bool use_default_verification = certificate_paths.empty() &&
	    verifier_paths.empty();
	  if (!use_default_verification) {
	    for (auto path : certificate_paths) {
	      context_->load_verify_file(path);
	    }
	    for (auto path : verifier_paths) {
	      context_->add_verify_path(path);
	    }
	    context_->set_verify_mode(boost::asio::ssl::context::verify_peer);
	    context_->set_verify_callback(boost::asio::ssl::rfc2818_verification(host));
	  } else {
	    context_->set_default_verify_paths();
	    context_->set_verify_mode(boost::asio::ssl::context::verify_none);
	  }
	  socket_.reset(new boost::asio::ssl::stream<
			  boost::asio::ip::tcp::socket>(io_service_, *context_));

	  using namespace std::placeholders;
	  socket_->lowest_layer()
	    .async_connect(endpoint,
			   std::bind(&ssl_connection_delegate::handle_connected,
				     ssl_connection_delegate::shared_from_this(),
				     _1,
				     handler));
	}

	virtual void write(boost::asio::streambuf &command_streambuf,
			   std::function<void (const boost::system::error_code &, size_t)> handler) {
	  boost::asio::async_write(*socket_, command_streambuf, handler);
	}

	virtual void read_some(const boost::asio::mutable_buffers_1 &read_buffer,
			       std::function<void (const boost::system::error_code &, size_t)> handler) {
	  socket_->async_read_some(read_buffer, handler);
	}

      private:

	boost::asio::io_service &io_service_;
	client_options options_;
	std::unique_ptr<boost::asio::ssl::context> context_;
	std::unique_ptr<
	  boost::asio::ssl::stream<boost::asio::ip::tcp::socket>> socket_;

	void handle_connected(boost::system::error_code const& ec,
			      std::function<void(const boost::system::error_code &)> handler);

      };
    } // namespace v2
  } // namespace http
} // namespace network

#endif // __NETWORK_HTTP_V2_CLIENT_CONNECTION_SSL_CONNECTION_DELEGATE_INC__
