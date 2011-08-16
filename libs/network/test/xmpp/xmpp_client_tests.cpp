//            Copyright (c) Glyn Matthews 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#define BOOST_TEST_MODULE XMPP client tests
#include <boost/test/unit_test.hpp>
#include <boost/network/protocol/xmpp/client.hpp>


namespace xmpp = boost::network::xmpp;
struct test_handler;
typedef xmpp::client<test_handler> client;


struct test_handler {

    void operator () (const client::message_type &message) {

    }

    void operator () (const client::presence_type &presence) {

    }

    void operator () (const client::iq_type &iq) {

    }

    void operator () (const client::error_type &error) {

    }

};


BOOST_AUTO_TEST_CASE(test_client_connection) {
    test_handler handler;
    client instance(handler);
    //instance.connect("glyn@lola", "xxx");
    //instance.run();
}
