// Copyright 2009, 2010, 2011 Dean Michael Berris, Jeroen Habraken, Glyn Matthews.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __BOOST_NETWORK_URI_INC__
# define __BOOST_NETWORK_URI_INC__


# include <boost/network/traits/string.hpp>
# include <boost/network/constants.hpp>
# include <boost/network/uri/detail/uri_parts.hpp>
# include <boost/fusion/sequence/intrinsic/at_c.hpp>
# include <boost/algorithm/string.hpp>
# include <boost/range/iterator_range.hpp>
# include <boost/operators.hpp>
# include <boost/utility/swap.hpp>
# include <boost/lexical_cast.hpp>
# include <boost/optional.hpp>
# include <algorithm>


namespace boost {
namespace network {
namespace uri {
namespace detail {
bool parse(std::string::const_iterator first,
           std::string::const_iterator last,
           uri_parts<std::string> &parts);
} // namespace detail


class uri
    : public boost::equality_comparable<uri> {

public:

    typedef std::string string_type;
    typedef string_type::iterator iterator;
    typedef boost::iterator_range<iterator> range_type;
    typedef string_type::const_iterator const_iterator;
    typedef boost::iterator_range<const_iterator> const_range_type;

    uri()
        : is_valid_(false) {

    }

    template <
        class FwdIter
        >
    uri(const FwdIter &first, const FwdIter &last)
        : uri_(first, last), is_valid_(false) {
        parse();
    }

    uri(const string_type &uri)
        : uri_(uri), is_valid_(false) {
        parse();
    }

    uri(const uri &other)
        : uri_(other.uri_),
          uri_parts_(other.uri_parts_),
          is_valid_(other.is_valid_) {

    }

    uri &operator = (const uri &other) {
        uri(other).swap(*this);
        return *this;
    }

    uri &operator = (const string_type &uri) {
        uri_ = uri;
        parse();
        return *this;
    }

    ~uri() {

    }

    void swap(uri &other) {
        boost::swap(uri_, other.uri_);
        parse();
    }

    iterator begin() {
        return uri_.begin();
    }

    const_iterator begin() const {
        return uri_.begin();
    }

    iterator end() {
        return uri_.end();
    }

    const_iterator end() const {
        return uri_.end();
    }

    const_range_type scheme_range() const {
        using boost::fusion::at_c;
        return const_range_type(at_c<0>(at_c<0>(uri_parts_)),
                                at_c<1>(at_c<0>(uri_parts_)));
    }

    const_range_type user_info_range() const {
        using boost::fusion::at_c;
        return const_range_type(at_c<0>(at_c<0>(at_c<1>(uri_parts_))),
                                at_c<1>(at_c<0>(at_c<1>(uri_parts_))));
    }

    const_range_type host_range() const {
        using boost::fusion::at_c;
        return const_range_type(at_c<0>(at_c<1>(at_c<1>(uri_parts_))),
                                at_c<1>(at_c<1>(at_c<1>(uri_parts_))));
    }

    const_range_type port_range() const {
        using boost::fusion::at_c;
        return const_range_type(at_c<0>(at_c<2>(at_c<1>(uri_parts_))),
                                at_c<1>(at_c<2>(at_c<1>(uri_parts_))));
    }

    const_range_type path_range() const {
        using boost::fusion::at_c;
        return const_range_type(at_c<0>(at_c<3>(at_c<1>(uri_parts_))),
                                at_c<1>(at_c<3>(at_c<1>(uri_parts_))));
    }

    const_range_type query_range() const {
        using boost::fusion::at_c;
        return const_range_type(at_c<0>(at_c<2>(uri_parts_)),
                                at_c<1>(at_c<2>(uri_parts_)));
    }

    const_range_type fragment_range() const {
        using boost::fusion::at_c;
        return const_range_type(at_c<0>(at_c<3>(uri_parts_)),
                                at_c<1>(at_c<3>(uri_parts_)));
    }

    string_type scheme() const {
        const_range_type range = scheme_range();
        return string_type(boost::begin(range), boost::end(range));
    }

    string_type user_info() const {
        const_range_type range = user_info_range();
        return string_type(boost::begin(range), boost::end(range));
    }

    string_type host() const {
        const_range_type range = host_range();
        return string_type(boost::begin(range), boost::end(range));
    }

    string_type port() const {
        const_range_type range = port_range();
        return string_type(boost::begin(range), boost::end(range));
    }

    string_type path() const {
        const_range_type range = path_range();
        return string_type(boost::begin(range), boost::end(range));
    }

    string_type query() const {
        const_range_type range = query_range();
        return string_type(boost::begin(range), boost::end(range));
    }

    string_type fragment() const {
        const_range_type range = fragment_range();
        return string_type(boost::begin(range), boost::end(range));
    }

    string_type string() const {
        return uri_;
    }

    bool is_valid() const {
        return is_valid_;
    }

    void append(const string_type &data) {
        uri_.append(data);
        parse();
    }

    template <
        class FwdIter
        >
    void append(const FwdIter &first, const FwdIter &last) {
        uri_.append(first, last);
        parse();
    }

private:

    void parse();

    string_type uri_;
    detail::uri_parts<std::string> uri_parts_;
    bool is_valid_;

};

inline
void uri::parse() {
    const_iterator first(boost::begin(uri_)), last(boost::end(uri_));
    is_valid_ = detail::parse(first, last, uri_parts_);
}

inline
std::string scheme(const uri &uri_) {
    return uri_.scheme();
}

inline
std::string user_info(const uri &uri_) {
    return uri_.user_info();
}

inline
std::string host(const uri &uri_) {
    return uri_.host();
}

inline
std::string port(const uri &uri_) {
    return uri_.port();
}

inline
boost::optional<unsigned short> port_us(const uri &uri_) {
    std::string port = uri_.port();
    return (port.empty())?
        boost::optional<unsigned short>() :
        boost::optional<unsigned short>(boost::lexical_cast<unsigned short>(port));
}

inline
std::string path(const uri &uri_) {
    return uri_.path();
}

inline
std::string query(const uri &uri_) {
    return uri_.query();
}

inline
std::string fragment(const uri &uri_) {
    return uri_.fragment();
}

inline
std::string authority(const uri &uri_) {
    uri::const_range_type user_info(uri_.user_info_range());
    uri::const_range_type port(uri_.port_range());
    return std::string(user_info.begin(), port.end());
}

inline
std::string netloc(const uri &uri_) {
    return authority(uri_);
}

inline
bool valid(const uri &uri_) {
    return uri_.is_valid();
}

inline
bool is_valid(const uri &uri_) {
    return valid(uri_);
}

inline
bool is_hierarchical(const uri &uri_) {
    //uri::const_range_type scheme = uri_.scheme_range();
    //uri::const_range_type user_info = uri_.user_info_range();
    //return is_valid(uri_) &&
    //    boost::equal(std::make_pair(boost::end(scheme),
    //                                boost::begin(user_info)),
    //                 boost::as_literal("://"));
    return false;
}

bool is_opaque(const uri &uri_) {
    return false;
}

inline
bool operator == (const uri &lhs, const uri &rhs) {
    return std::equal(lhs.begin(), lhs.end(), rhs.begin());
}
} // namespace uri
} // namespace network

inline
network::uri::uri::iterator begin(network::uri::uri &uri_) {
    return uri_.begin();
}

inline
network::uri::uri::iterator end(network::uri::uri &uri_) {
    return uri_.end();
}

inline
network::uri::uri::const_iterator begin(const network::uri::uri &uri_) {
    return uri_.begin();
}

inline
network::uri::uri::const_iterator end(const network::uri::uri &uri_) {
    return uri_.end();
}

inline
void swap(network::uri::uri &lhs, network::uri::uri &rhs) {
    lhs.swap(rhs);
}
} // namespace boost


# include <boost/network/uri/accessors.hpp>
# include <boost/network/uri/directives.hpp>


#endif // __BOOST_NETWORK_URI_INC__
