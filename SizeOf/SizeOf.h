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
#include <map>
#include <set>
#include <list>
#include <deque>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
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
struct IsSupportedContainer {
    static constexpr bool value = false;
};

template <template<typename...> class C, typename... Ts>
std::enable_if_t<IsSupportedContainer<C>::value && std::is_trivial<typename C<Ts...>::value_type>::value, size_t> SizeOf(const C<Ts...>& c) {
    size_t s = sizeof(c); // base size
    s += c.size() * sizeof(typename C<Ts...>::value_type);
    return s;
}

template <template<typename...> class C, typename... Ts>
std::enable_if_t<IsSupportedContainer<C>::value && !std::is_trivial<typename C<Ts...>::value_type>::value, size_t> SizeOf(const C<Ts...>& c) {
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

template <typename C>
struct HasSizeOfMethod {
    template <typename T>
    static typename std::is_same<decltype(std::declval<const T>().SizeOf()), size_t>::type check(std::nullptr_t);

    template <typename>
    static constexpr std::false_type check(...);

    static constexpr bool value = decltype(check<C>(nullptr))::value;
};

template <typename T>
std::enable_if_t<HasSizeOfMethod<T>::value, size_t> SizeOf(const T& t) {
    return t.SizeOf();
}

#define REGISTER_SUPPORTED_CONTAINER(C) \
template<> \
struct IsSupportedContainer<C> { \
    static constexpr bool value = true; \
}

REGISTER_SUPPORTED_CONTAINER(std::set);
REGISTER_SUPPORTED_CONTAINER(std::map);
REGISTER_SUPPORTED_CONTAINER(std::list);
REGISTER_SUPPORTED_CONTAINER(std::deque);
REGISTER_SUPPORTED_CONTAINER(std::vector);
REGISTER_SUPPORTED_CONTAINER(std::unordered_set);
REGISTER_SUPPORTED_CONTAINER(std::unordered_map);

#endif /* SizeOf_h */
