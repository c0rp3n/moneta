//
// Copyright (C) 2022 by Oliver John Hitchcock - github.com/c0rp3n
//
// Distributed under the Boost Software License, Version 1.0.
//

#ifndef mntaLiterals_hpp
#define mntaLiterals_hpp

#pragma once

#include "mntaNamespace.hpp"

#include <cstddef>

#define MNTA_LITERALS_BEGIN_NAMESPACE namespace literals {
#define MNTA_LITERALS_END_NAMESPACE   } // literals

MNTA_BEGIN_NAMESPACE
MNTA_LITERALS_BEGIN_NAMESPACE

constexpr std::size_t operator""_KiB(unsigned long long int x)
{
  return 1024ULL * x;
}

constexpr std::size_t operator""_MiB(unsigned long long int x)
{
  return 1024_KiB * x;
}

constexpr std::size_t operator""_GiB(unsigned long long int x)
{
  return 1024_MiB * x;
}

MNTA_LITERALS_END_NAMESPACE
MNTA_END_NAMESPACE

#define MNTA_USE_LITERALS using namespace mnta::literals;

#endif // mntaLiterals_hpp