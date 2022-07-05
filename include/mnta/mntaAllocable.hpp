//
// Copyright (C) 2022 by Oliver John Hitchcock - github.com/c0rp3n
//

#ifndef mntaAllocable_hpp
#define mntaAllocable_hpp

#pragma once

#include "mntaNamespace.hpp"

#include <concepts>
#include <typeinfo>

MNTA_BEGIN_NAMESPACE

template<class T>
concept Allocable = requires (T* a)
{
    std::is_trivially_constructible_v<T>;
    std::is_trivially_destructible_v<T>;
    std::is_trivially_move_assignable_v<T>;
};

template<mnta::Allocable T>
constexpr T* alloc_cast(void* ptr) noexcept
{
    return reinterpret_cast<T*>(ptr);
}

MNTA_END_NAMESPACE

#endif // mntaAllocable_hpp