//
// Copyright (C) 2022 by Oliver John Hitchcock - github.com/c0rp3n
//

#ifndef mntaMacros_hpp
#define mntaMacros_hpp

#pragma once

// Faster than std::forward
#define MNTA_FWD(...) static_cast<decltype(__VA_ARGS__) &&>(__VA_ARGS__)

// Force a function to be inline
#if defined(MNTA_FWD_NO_FORCEINLINE)
#  define MNTA_FORCEINLINE inline
#else
#  if defined(_MSC_VER)
#    define MNTA_FORCEINLINE __forceinline
#  elif defined(__GNUC__) && __GNUC__ > 3
#    define MNTA_FORCEINLINE inline __attribute__((__always_inline__))
#  else
#    define MNTA_FORCEINLINE inline
#  endif
#endif

#endif // mntaMacros_hpp
