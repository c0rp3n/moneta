//
// Copyright (C) 2022 by Oliver John Hitchcock - github.com/c0rp3n
//
// Distributed under the Boost Software License, Version 1.0.
//

#ifndef mntaArena_hpp
#define mntaArena_hpp

#pragma once

#include "mntaNamespace.hpp"
#include "mntaAllocable.hpp"
#include "mntaMemoryBlock.hpp"

#include <forward_list>
#include <memory>
#include <typeinfo>

MNTA_BEGIN_NAMESPACE

template<Allocable T, std::size_t BlockSize = 1024>
class Arena
{
public:
    using value_type   = T;
    using pointer_type = T*;

    using active_block = ActiveMemoryBlock<value_type, BlockSize>;
    using memory_block = typename active_block::memory_block;
    using block_list   = std::forward_list<memory_block>;

    Arena()                        = default;
    Arena(const Arena&)            = delete;
    Arena(Arena&&)                 = default;
    ~Arena()                       = default;

    Arena& operator=(const Arena&) = delete;
    Arena& operator=(Arena&&)      = delete;

    pointer_type alligned_alloc() noexcept;

    MNTA_FORCEINLINE friend T* get(Arena& arena) noexcept
    {
        return arena.alligned_alloc();
    }

    MNTA_FORCEINLINE friend void put(Arena& arena, pointer_type ptr) noexcept
    {
        // do nothing
    }

private:
    active_block m_current;
    block_list   m_blocks;
};

MNTA_END_NAMESPACE

#include "mntaArena.ipp"

#endif // mntaArena_hpp