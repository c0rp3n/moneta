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

struct AlignedDeleter
{
    MNTA_FORCEINLINE void operator()(std::byte* ptr) const
    {
#ifdef _WIN32
        _aligned_free(ptr);
#else
        std::free(ptr);
#endif
    }
};

using MemoryBlock = std::unique_ptr<std::byte[], AlignedDeleter>;

namespace detail
{

    template <std::size_t Size>
    MNTA_FORCEINLINE MemoryBlock create_memory_block() noexcept
    {
    #ifdef _WIN32
        return MemoryBlock{reinterpret_cast<std::byte*>(_aligned_malloc(Size, Size))};
    #else
        return MemoryBlock{reinterpret_cast<std::byte*>(std::aligned_alloc(Size, Size))};
    #endif
    }

}

template<mnta::Allocable T, std::size_t Size = 1024>
class ActiveMemoryBlock
{
public:
    using memory_block = MemoryBlock;

    MNTA_FORCEINLINE ActiveMemoryBlock() noexcept
        : m_memory(detail::create_memory_block<Size>()), m_current(m_memory.get())
    {}

    MNTA_FORCEINLINE std::byte* begin() const noexcept
    {
        return m_memory.get();
    }

    MNTA_FORCEINLINE std::byte* end() const noexcept
    {
        return begin() + Size;
    }

    MNTA_FORCEINLINE T* get() noexcept
    {
        void* current = reinterpret_cast<void*>(m_current);
        size_t size = end() - m_current;

        T* const result = alloc_cast<T>(
            std::align(alignof(T),
                       sizeof(T),
                       current,
                       size));
        m_current += sizeof(T);

        return result;
    }

    MNTA_FORCEINLINE memory_block refresh()
    {
        memory_block ret = std::move(m_memory);
        m_memory  = detail::create_memory_block<Size>();
        m_current = m_memory.get();

        return ret;
    }

private:
    memory_block m_memory;
    std::byte*   m_current;
};

MNTA_END_NAMESPACE

#endif // mntaMemoryBlock_hpp
