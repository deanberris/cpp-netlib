// Copyright 2009, 2010, 2011 Dean Michael Berris, Jeroen Habraken, Glyn Matthews.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt of copy at
// http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_MODULE URL Test
#include <boost/config/warning_disable.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/network/uri.hpp>
#include <boost/network/uri/uri.hpp>
#include <boost/network/uri/uri_io.hpp>
#include <boost/range/algorithm/equal.hpp>
#include <map>


using namespace boost::network;


BOOST_AUTO_TEST_CASE(basic_uri_range_test) {
    uri::uri instance("http://www.example.com/");
    BOOST_REQUIRE(uri::valid(instance));
    BOOST_CHECK(boost::equal(instance.scheme_range(), boost::as_literal("http")));
    BOOST_CHECK(boost::empty(instance.user_info_range()));
    BOOST_CHECK(boost::equal(instance.host_range(), boost::as_literal("www.example.com")));
    BOOST_CHECK(boost::empty(instance.port_range()));
    BOOST_CHECK(boost::equal(instance.path_range(), boost::as_literal("/")));
    BOOST_CHECK(boost::empty(instance.query_range()));
    BOOST_CHECK(boost::empty(instance.fragment_range()));
}

BOOST_AUTO_TEST_CASE(full_uri_range_test) {
    uri::uri instance("http://user:password@www.example.com:80/path?query#fragment");
    BOOST_REQUIRE(uri::valid(instance));
    BOOST_CHECK(boost::equal(instance.scheme_range(), boost::as_literal("http")));
    BOOST_CHECK(boost::equal(instance.user_info_range(), boost::as_literal("user:password")));
    BOOST_CHECK(boost::equal(instance.host_range(), boost::as_literal("www.example.com")));
    BOOST_CHECK(boost::equal(instance.port_range(), boost::as_literal("80")));
    BOOST_CHECK(boost::equal(instance.path_range(), boost::as_literal("/path")));
    BOOST_CHECK(boost::equal(instance.query_range(), boost::as_literal("query")));
    BOOST_CHECK(boost::equal(instance.fragment_range(), boost::as_literal("fragment")));
}

BOOST_AUTO_TEST_CASE(basic_uri_test) {
    uri::uri instance("http://www.example.com/");
    BOOST_REQUIRE(uri::valid(instance));
    BOOST_CHECK_EQUAL(uri::scheme(instance), "http");
    BOOST_CHECK_EQUAL(uri::host(instance), "www.example.com");
    BOOST_CHECK_EQUAL(uri::path(instance), "/");
}

BOOST_AUTO_TEST_CASE(full_uri_test) {
    uri::uri instance("http://user:password@www.example.com:80/path?query#fragment");
    BOOST_REQUIRE(uri::valid(instance));
    BOOST_CHECK_EQUAL(uri::scheme(instance), "http");
    BOOST_CHECK_EQUAL(uri::user_info(instance), "user:password");
    BOOST_CHECK_EQUAL(uri::host(instance), "www.example.com");
    BOOST_CHECK(uri::port_us(instance));
    BOOST_CHECK_EQUAL(uri::port_us(instance).get(), 80);
    BOOST_CHECK_EQUAL(uri::port(instance), "80");
    BOOST_CHECK_EQUAL(uri::path(instance), "/path");
    BOOST_CHECK_EQUAL(uri::query(instance), "query");
    BOOST_CHECK_EQUAL(uri::fragment(instance), "fragment");
}

BOOST_AUTO_TEST_CASE(mailto_test) {
    uri::uri instance("mailto:john.doe@example.com");
    BOOST_REQUIRE(uri::valid(instance));
    BOOST_CHECK_EQUAL(uri::scheme(instance), "mailto");
    BOOST_CHECK_EQUAL(uri::path(instance), "john.doe@example.com");
}

BOOST_AUTO_TEST_CASE(file_test) {
    uri::uri instance("file:///bin/bash");
    BOOST_REQUIRE(uri::valid(instance));
    BOOST_CHECK_EQUAL(uri::scheme(instance), "file");
    BOOST_CHECK_EQUAL(uri::path(instance), "/bin/bash");
}

BOOST_AUTO_TEST_CASE(xmpp_test) {
    uri::uri instance("xmpp:example-node@example.com?message;subject=Hello%20World");
    BOOST_REQUIRE(uri::valid(instance));
    BOOST_CHECK_EQUAL(uri::scheme(instance), "xmpp");
    BOOST_CHECK_EQUAL(uri::path(instance), "example-node@example.com");
    BOOST_CHECK_EQUAL(uri::query(instance), "message;subject=Hello%20World");
}

BOOST_AUTO_TEST_CASE(ipv4_address_test) {
    uri::uri instance("http://129.79.245.252/");
    BOOST_REQUIRE(uri::valid(instance));
    BOOST_CHECK_EQUAL(uri::scheme(instance), "http");
    BOOST_CHECK_EQUAL(uri::host(instance), "129.79.245.252");
    BOOST_CHECK_EQUAL(uri::path(instance), "/");
}

BOOST_AUTO_TEST_CASE(ipv6_address_test_1) {
    uri::uri instance("http://[1080:0:0:0:8:800:200C:417A]/");
    BOOST_REQUIRE(uri::valid(instance));
    BOOST_CHECK_EQUAL(uri::scheme(instance), "http");
    BOOST_CHECK_EQUAL(uri::host(instance), "[1080:0:0:0:8:800:200C:417A]");
    BOOST_CHECK_EQUAL(uri::path(instance), "/");
}

BOOST_AUTO_TEST_CASE(ipv6_address_test_2) {
    uri::uri instance("http://[2001:db8:85a3:8d3:1319:8a2e:370:7348]/");
    BOOST_REQUIRE(uri::valid(instance));
    BOOST_CHECK_EQUAL(uri::scheme(instance), "http");
    BOOST_CHECK_EQUAL(uri::host(instance), "[2001:db8:85a3:8d3:1319:8a2e:370:7348]");
    BOOST_CHECK_EQUAL(uri::path(instance), "/");
}

BOOST_AUTO_TEST_CASE(ftp_test) {
    uri::uri instance("ftp://john.doe@ftp.example.com/");
    BOOST_REQUIRE(uri::valid(instance));
    BOOST_CHECK_EQUAL(uri::scheme(instance), "ftp");
    BOOST_CHECK_EQUAL(uri::user_info(instance), "john.doe");
    BOOST_CHECK_EQUAL(uri::host(instance), "ftp.example.com");
    BOOST_CHECK_EQUAL(uri::path(instance), "/");
}

BOOST_AUTO_TEST_CASE(news_test) {
    uri::uri instance("news:comp.infosystems.www.servers.unix");
    BOOST_REQUIRE(uri::valid(instance));
    BOOST_CHECK_EQUAL(uri::scheme(instance), "news");
    BOOST_CHECK_EQUAL(uri::path(instance), "comp.infosystems.www.servers.unix");
}

BOOST_AUTO_TEST_CASE(tel_test) {
    uri::uri instance("tel:+1-816-555-1212");
    BOOST_REQUIRE(uri::valid(instance));
    BOOST_CHECK_EQUAL(uri::scheme(instance), "tel");
    BOOST_CHECK_EQUAL(uri::path(instance), "+1-816-555-1212");
}

BOOST_AUTO_TEST_CASE(encoded_uri_test) {
    uri::uri instance("http://www.example.com/Path%20With%20%28Some%29%20Encoded%20Characters%21");
    BOOST_REQUIRE(uri::valid(instance));
    BOOST_CHECK_EQUAL(uri::scheme(instance), "http");
    BOOST_CHECK_EQUAL(uri::host(instance), "www.example.com");
    BOOST_CHECK_EQUAL(uri::path(instance), "/Path%20With%20%28Some%29%20Encoded%20Characters%21");
    BOOST_CHECK_EQUAL(uri::decoded_path(instance), "/Path With (Some) Encoded Characters!");
}

BOOST_AUTO_TEST_CASE(copy_constructor_test) {
    uri::uri instance("http://www.example.com/");
    uri::uri copy = instance;
    BOOST_CHECK(instance == copy);
}

BOOST_AUTO_TEST_CASE(assignment_test) {
    uri::uri instance("http://www.example.com/");
    uri::uri copy;
    copy = instance;
    BOOST_CHECK_EQUAL(instance.string(), copy.string());
    BOOST_CHECK_EQUAL(instance, copy);
}

BOOST_AUTO_TEST_CASE(username_test) {
    uri::uri instance("ftp://john.doe:password@ftp.example.com/");
    BOOST_REQUIRE(uri::valid(instance));
    BOOST_CHECK_EQUAL(uri::username(instance), "john.doe");
    BOOST_CHECK_EQUAL(uri::password(instance), "password");
}

BOOST_AUTO_TEST_CASE(authority_test) {
    uri::uri instance("http://user:password@www.example.com:80/path?query#fragment");
    BOOST_REQUIRE(uri::valid(instance));
    BOOST_CHECK_EQUAL(uri::authority(instance), "user:password@www.example.com:80");
}

BOOST_AUTO_TEST_CASE(http_query_map_test) {
    uri::uri instance("http://user:password@www.example.com:80/path?query=something#fragment");
    BOOST_REQUIRE(uri::valid(instance));

    std::map<std::string, std::string> queries;
    uri::query_map(instance, queries);
    BOOST_REQUIRE_EQUAL(queries.size(), std::size_t(1));
    BOOST_CHECK_EQUAL(queries.begin()->first, "query");
    BOOST_CHECK_EQUAL(queries.begin()->second, "something");
}

BOOST_AUTO_TEST_CASE(xmpp_query_map_test) {
    uri::uri instance("xmpp:example-node@example.com?message;subject=Hello%20World");
    BOOST_REQUIRE(uri::valid(instance));

    std::map<std::string, std::string> queries;
    uri::query_map(instance, queries);
    BOOST_REQUIRE_EQUAL(queries.size(), std::size_t(2));
    BOOST_CHECK_EQUAL(queries.begin()->first, "message");
    BOOST_CHECK_EQUAL(queries.begin()->second, "");
    BOOST_CHECK_EQUAL((++queries.begin())->first, "subject");
    BOOST_CHECK_EQUAL((++queries.begin())->second, "Hello%20World");
}

BOOST_AUTO_TEST_CASE(range_test)
{
    const std::string url("http://www.example.com/");
    uri::uri instance(url);
    BOOST_REQUIRE(uri::valid(instance));
    BOOST_CHECK(boost::equal(instance, url));
}

BOOST_AUTO_TEST_CASE(issue_67_test)
{
    const std::string site_name("http://www.google.com");
    uri::uri bar0;
    uri::uri bar1 = site_name;
    bar0 = site_name;
    BOOST_CHECK(uri::is_valid(bar0));
    BOOST_CHECK(uri::is_valid(bar1));
}
