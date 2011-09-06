#ifndef __BOOST_NETWORK_URI_DIRECTIVES_INC__
# define __BOOST_NETWORK_URI_DIRECTIVES_INC__


# include <boost/network/uri/uri.hpp>
# include <boost/network/uri/directives/scheme.hpp>
# include <boost/network/uri/directives/user_info.hpp>
# include <boost/network/uri/directives/host.hpp>
# include <boost/network/uri/directives/port.hpp>
# include <boost/network/uri/directives/authority.hpp>
# include <boost/network/uri/directives/path.hpp>
# include <boost/network/uri/directives/query.hpp>
# include <boost/network/uri/directives/fragment.hpp>


namespace boost {
namespace network {
namespace uri {
template <
    class String
    >
inline
basic_uri<String> &operator << (basic_uri<String> &uri, const basic_uri<String> &root_uri) {
    if (empty(uri) && valid(root_uri)) {
        uri.append(boost::begin(root_uri), boost::end(root_uri));
    }
    return uri;
}

template <
    class String
  , class Directive
    >
inline
basic_uri<String> &operator << (basic_uri<String> &uri, const Directive &directive) {
    directive(uri);
    return uri;
}
} // namespace uri
} // namespace network
} // namespace boost


#endif // __BOOST_NETWORK_URI_DIRECTIVES_INC__
