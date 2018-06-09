//
//  SizeOf.h
//  SizeOf
//
//  Created by Lin Luo on 6/8/18.
//  Copyright © 2018 Linfinity. All rights reserved.
//

#pragma once

#ifndef SizeOf_h
#define SizeOf_h

#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <map>
#include <set>
#include <string>
#include <memory>
#include <utility>

template <typename T>
std::enable_if_t<std::is_fundamental<T>::value, size_t> SizeOf(T t) {
    return sizeof(t);
}

template <typename T>
size_t SizeOf(T* p) {
    return sizeof(p);
}

template <typename T>
size_t SizeOf(const std::unique_ptr<T>& p) {
    return SizeOf(*p); // std::unique_ptr means ownership, so let's count the actual object
}

template <typename Ch>
size_t SizeOf(const std::basic_string<Ch>& s) {
    return sizeof(s) + s.size() * sizeof(Ch);
}

// forward declaration for std::pair<>
template <typename K, typename V>
size_t SizeOf(const std::pair<K, V>& p);

template <template<typename...> class C>
struct IsContainer {
    static constexpr bool value = false;
};

// TODO: if the element type is POD, then it should be .size() * sizeof(T)!
// or this function is only for element type that is another container
template <template<typename...> class C, typename... Ts>
std::enable_if_t<IsContainer<C>::value, size_t> SizeOf(const C<Ts...>& c) {
    size_t s = sizeof(c); // base size
    for (const auto& e : c) {
        s += SizeOf(e);
    }
    return s;
}

template <typename K, typename V>
size_t SizeOf(const std::pair<K, V>& p) {
    return SizeOf(p.first) + SizeOf(p.second);
}

template <typename T, size_t N>
size_t SizeOf(const std::array<T, N>& a) {
    return sizeof(a);
}

//template <typename T>
//struct HasSizeOf {
//    static constexpr bool value = false;
//};
//
//template<typename C>
//struct HasSizeOf {
//private:
//    template<typename T>
//    static constexpr auto check(T*) ->
//        typename std::is_same<
//            decltype( std::declval<T>().SizeOf( std::declval<Args>()... ) ),
//            Ret
//        >::type;
//
//    template<typename>
//    static constexpr std::false_type check(...);
//
//    typedef decltype(check<C>(0)) type;
//
//public:
//    static constexpr bool value = type::value;
//};

struct TestHasSizeOfMethod {
    template <typename T>
    static auto apply(const T* p) -> typename std::is_same<decltype(p->SizeOf()), size_t>::type;

    template <typename>
    static constexpr std::false_type apply(...);
};

template <typename T>
struct HasSizeOfMethod : decltype(TestHasSizeOfMethod::apply<T>(nullptr)) {};

template <typename T>
std::enable_if_t<HasSizeOfMethod<T>::value, size_t> SizeOf(const T& t) {
    return t.SizeOf();
}

template<>
struct IsContainer<std::vector> {
    static constexpr bool value = true;
};

template<>
struct IsContainer<std::map> {
    static constexpr bool value = true;
};

#endif /* SizeOf_h */
