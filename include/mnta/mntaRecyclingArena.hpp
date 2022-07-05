//
// Copyright (C) 2022 by Oliver John Hitchcock - github.com/c0rp3n
//

#ifndef mntaRecyclingArena_hpp
#define mntaRecyclingArena_hpp

#pragma once

#include "mntaNamespace.hpp"
#include "mntaAllocable.hpp"
#include "mntaArena.hpp"

#include <vector>

MNTA_BEGIN_NAMESPACE

template<Allocable T, std::size_t BlockSize = 1024>
class RecyclingArena
{
public:
    using value_type   = T;
    using pointer_type = T*;

    using free_vec = std::vector<T*>;
    using arena    = Arena<T, BlockSize>;

    RecyclingArena()                                 = default;
    RecyclingArena(const RecyclingArena&)            = delete;
    RecyclingArena(RecyclingArena&&)                 = default;
    ~RecyclingArena()                                = default;

    RecyclingArena(arena&& arena) noexcept;

    RecyclingArena& operator=(const RecyclingArena&) = delete;
    RecyclingArena& operator=(RecyclingArena&&)      = default;

    pointer_type get() noexcept;
    void         put(pointer_type ptr) noexcept;

private:
    arena    m_arena;
    free_vec m_free;
};

MNTA_END_NAMESPACE

#include "mntaRecyclingArena.ipp"

#endif // mntaRecyclingArena_hpp