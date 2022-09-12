//
// Copyright (C) 2022 by Oliver John Hitchcock - github.com/c0rp3n
//
// Distributed under the Boost Software License, Version 1.0.
//

#include "mntaArena.hpp"
#include "mntaMacros.hpp"

template <mnta::Allocable T, std::size_t BlockSize>
MNTA_FORCEINLINE T* mnta::Arena<T, BlockSize>::alligned_alloc() noexcept
{
    if (T* const ret = m_current.get()) [[likely]] { return ret; }
    else [[unlikely]]
    {
        // slow path as we do not have any memory free at the moment

        m_blocks.emplace_front(std::move(m_current.refresh()));

        return m_current.get();
    }

}
