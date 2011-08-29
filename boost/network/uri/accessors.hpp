//            Copyright (c) Glyn Matthews 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __BOOST_NETWORK_URI_URI_ACCESSORS_INC__
# define __BOOST_NETWORK_URI_URI_ACCESSORS_INC__


# include <boost/network/uri/uri.hpp>
# include <boost/network/uri/encode.hpp>
# include <boost/network/uri/decode.hpp>
# include <boost/spirit/include/qi.hpp>


namespace boost {
namespace network {
namespace uri {
namespace details {
template <
    typename Uri,
    typename Map
    >
struct key_value_sequence
    : spirit::qi::grammar<typename Uri::const_iterator_type, Map()>
{
    typedef typename Uri::const_iterator_type const_iterator_type;

    key_value_sequence()
        : key_value_sequence::base_type(query)
    {
        query =  pair >> *((spirit::qi::lit(';') | '&') >> pair);
        pair  =  key >> -('=' >> value);
        key   =  spirit::qi::char_("a-zA-Z_") >> *spirit::qi::char_("a-zA-Z_0-9/%");
        value = +spirit::qi::char_("a-zA-Z_0-9/%");
    }

    spirit::qi::rule<const_iterator_type, Map()> query;
    spirit::qi::rule<const_iterator_type, std::pair<typename Uri::string_type, typename Uri::string_type>()> pair;
    spirit::qi::rule<const_iterator_type, typename Uri::string_type()> key, value;
};
} // namespace details

template <
    class Tag,
    class Map
    >
inline
Map &query_map(const basic_uri<Tag> &uri, Map &map) {
    typename basic_uri<Tag>::const_range_type range = uri.query_range();
    details::key_value_sequence<basic_uri<Tag>, Map> parser;
    spirit::qi::parse(boost::begin(range), boost::end(range), parser, map);
    return map;
}

template <
    class Tag
    >
typename basic_uri<Tag>::string_type username(const basic_uri<Tag> &uri) {
    typename basic_uri<Tag>::const_range_type user_info_range = uri.user_info_range();
    typename basic_uri<Tag>::const_iterator_type it(boost::begin(user_info_range)), end(boost::end(user_info_range));
    for (; it != end; ++it) {
        if (*it == ':') {
            break;
        }
    }
    return typename string<Tag>::type(boost::begin(user_info_range), it);
}

template <
    class Tag
    >
typename basic_uri<Tag>::string_type password(const basic_uri<Tag> &uri) {
    typename basic_uri<Tag>::const_range_type user_info_range = uri.user_info_range();
    typename basic_uri<Tag>::const_iterator_type it(boost::begin(user_info_range)), end(boost::end(user_info_range));
    for (; it != end; ++it) {
        if (*it == ':') {
            ++it;
            break;
        }
    }
    return typename string<Tag>::type(it, boost::end(user_info_range));
}

template <
    class Tag
    >
typename basic_uri<Tag>::string_type decoded_path(const basic_uri<Tag> &uri) {
    typename basic_uri<Tag>::const_range_type path_range = uri.path_range();
    typename basic_uri<Tag>::string_type decoded_path;
    decode(path_range, std::back_inserter(decoded_path));
    return decoded_path;
}

template <
    class Tag
    >
typename basic_uri<Tag>::string_type decoded_query(const basic_uri<Tag> &uri) {
    typename basic_uri<Tag>::const_range_type query_range = uri.query_range();
    typename basic_uri<Tag>::string_type decoded_query;
    decode(query_range, std::back_inserter(decoded_query));
    return decoded_query;
}

template <
    class Tag
    >
typename basic_uri<Tag>::string_type decoded_fragment(const basic_uri<Tag> &uri) {
    typename basic_uri<Tag>::const_range_type fragment_range = uri.fragment_range();
    typename basic_uri<Tag>::string_type decoded_fragment;
    decode(fragment_range, std::back_inserter(decoded_fragment));
    return decoded_fragment;
}
} // namespace uri
} // namespace network
} // namespace boost


#endif // __BOOST_NETWORK_URI_URI_ACCESSORS_INC__
