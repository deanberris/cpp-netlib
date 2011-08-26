#ifndef __BOOST_NETWORK_URI_DIRECTIVES_PATH_INC__
# define __BOOST_NETWORK_URI_DIRECTIVES_PATH_INC__


namespace boost {
namespace network {
namespace uri {
template <
    class ValueType
    >
struct path_directive {

    explicit path_directive(const ValueType &value)
        : value(value)
    {}

    template <
        class Tag
      , template <class> class Uri
        >
    typename enable_if<is_pod<Tag>, void>::type
    operator () (Uri<Tag> &uri) const {
        uri.append(value);
    }

    template <
        class Tag
      , template <class> class Uri
        >
    typename enable_if<mpl::not_<is_pod<Tag> >, void>::type
    operator () (Uri<Tag> &uri) const {
        uri.append(value);
    }

    const ValueType &value;

};

template <
    class T
    >
inline
path_directive<T> path(const T &value)  {
    return path_directive<T>(value);
}
} // namespace uri
} // namespace network
} // namespace boost


#endif // __BOOST_NETWORK_URI_DIRECTIVES_PATH_INC__
