//
// Copyright (C) 2022 by Oliver John Hitchcock - github.com/c0rp3n
//
// Distributed under the Boost Software License, Version 1.0.
//

#include "mntaRecyclingArena.hpp"

#include "mntaMacros.hpp"

template <mnta::Allocable T, std::size_t BlockSize>
MNTA_FORCEINLINE
mnta::RecyclingArena<T, BlockSize>::RecyclingArena(arena&& arena) noexcept
    : m_arena(std::move(arena))
{}

template <mnta::Allocable T, std::size_t BlockSize>
MNTA_FORCEINLINE T* mnta::RecyclingArena<T, BlockSize>::get() noexcept
{
    if (not m_free.empty()) [[likely]]
    {
        T* const ret = m_free.back();
        m_free.pop_back();

        return ret;
    }

    return m_arena.alligned_alloc();
}

template <mnta::Allocable T, std::size_t BlockSize>
MNTA_FORCEINLINE void mnta::RecyclingArena<T, BlockSize>::put(T* ptr) noexcept
{
    m_free.push_back(ptr);
}
