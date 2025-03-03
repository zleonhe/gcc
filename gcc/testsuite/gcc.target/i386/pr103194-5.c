/* { dg-do compile { target { ! ia32 } } } */
/* { dg-options "-O2" } */
#include <stdatomic.h>
#include <stdbool.h>

#define FOO(RTYPE,TYPE)							\
  __attribute__((noinline,noclone)) RTYPE				\
  atomic_fetch_or_##TYPE##_##MASK (_Atomic TYPE* a, TYPE MASK)		\
  {									\
    TYPE mask = 1ll << MASK;						\
    return __atomic_fetch_or (a, mask, __ATOMIC_RELAXED) & mask;	\
  }									\
  __attribute__((noinline,noclone)) RTYPE				\
  atomic_fetch_xor_##TYPE##_##MASK (_Atomic TYPE* a, TYPE MASK)		\
  {									\
    TYPE mask = 1ll << MASK;						\
    return __atomic_fetch_xor (a, mask, __ATOMIC_RELAXED) & mask;	\
  }									\
  __attribute__((noinline,noclone)) RTYPE				\
  atomic_xor_fetch_##TYPE##_##MASK (_Atomic TYPE* a, TYPE MASK)		\
  {									\
    TYPE mask = 1ll << MASK;						\
    return __atomic_xor_fetch (a, mask, __ATOMIC_RELAXED) & mask;	\
  }									\
  __attribute__((noinline,noclone)) RTYPE				\
  atomic_fetch_and_##TYPE##_##MASK (_Atomic TYPE* a, TYPE MASK)		\
  {									\
    TYPE mask = 1ll << MASK;						\
    return __atomic_fetch_and (a, ~mask, __ATOMIC_RELAXED) & mask;	\
  }									\
  __attribute__((noinline,noclone)) RTYPE				\
  sync_fetch_and_or_##TYPE##_##MASK (_Atomic TYPE* a, TYPE MASK)	\
  {									\
    TYPE mask = 1ll << MASK;						\
    return __sync_fetch_and_or (a, mask) & mask;			\
  }									\
  __attribute__((noinline,noclone)) RTYPE				\
  sync_fetch_and_xor_##TYPE##_##MASK (_Atomic TYPE* a, TYPE MASK)	\
  {									\
    TYPE mask = 1ll << MASK;						\
    return __sync_fetch_and_xor (a, mask) & mask;			\
  }									\
  __attribute__((noinline,noclone)) RTYPE				\
  sync_xor_and_fetch_##TYPE##_##MASK (_Atomic TYPE* a, TYPE MASK)	\
  {									\
    TYPE mask = 1ll << MASK;						\
    return __sync_xor_and_fetch (a, mask) & mask;			\
  }									\
  __attribute__((noinline,noclone)) RTYPE				\
  sync_fetch_and_and_##TYPE##_##MASK (_Atomic TYPE* a, TYPE MASK)	\
  {									\
    TYPE mask = 1ll << MASK;						\
    return __sync_fetch_and_and (a, ~mask) & mask;			\
  }									\

FOO(int, long);

/* { dg-final { scan-assembler-times "lock;?\[ \t\]*bts" 2 } } */
/* { dg-final { scan-assembler-times "lock;?\[ \t\]*btc" 4 } } */
/* { dg-final { scan-assembler-times "lock;?\[ \t\]*btr" 2 } } */
/* { dg-final { scan-assembler-not "cmpxchg" } } */
