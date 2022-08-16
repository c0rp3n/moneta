//
// Copyright (C) 2022 by Oliver John Hitchcock - github.com/c0rp3n
//
// Distributed under the Boost Software License, Version 1.0.
//

#ifndef mntaMemoryBlock_hpp
#define mntaMemoryBlock_hpp

#pragma once

#include "mntaNamespace.hpp"
#include "mntaAllocable.hpp"
#include "mntaMacros.hpp"

#include <cstdlib>
#include <memory>

MNTA_BEGIN_NAMESPACE

template<std::size_t Size = 1024>
using MemoryBlock = std::unique_ptr<std::byte[Size]>;

template <std::size_t Size>
MNTA_FORCEINLINE MemoryBlock<Size> create_memory_block() noexcept
{
    return {reinterpret_cast<std::byte*>(std::aligned_alloc(Size, Size))};
}

template<mnta::Allocable T, std::size_t Size = 1024>
class ActiveMemoryBlock
{
public:
    using memory_block = MemoryBlock<Size>;

    MNTA_FORCEINLINE MemoryBlock() noexcept
        : m_memory(create_memory_block<Size>()), m_current(m_memory.get())
    {}

    MNTA_FORCEINLINE std::byte* begin() const noexcept
    {
        return m_memory.get();
    }

    MNTA_FORCEINLINE std::byte* end() const noexcept
    {
        return begin() + BlockSize;
    }

    MNTA_FORCEINLINE T* get() noexcept
    {
        T* const result = alloc_cast<T>(
            std::align(alignof(T),
                       sizeof(T),
                       reinterpret_cast<void*>(m_current),
                       std::distance(current, end())));
        current += sizeof(T);

        return result;
    }

    MNTA_FORCEINLINE memory_block refresh()
    {
        memory_block ret = std::move(m_memory);
        m_memory  = memory_block{};
        m_current = m_memory.get();

        return std::move(ret);
    }

private:
    memory_block m_memory;
    std::byte*   m_current;
};

MNTA_END_NAMESPACE

#endif // mntaMemoryBlock_hpp
