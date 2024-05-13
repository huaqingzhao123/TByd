/*
 * Copyright (c) 1991-1994 by Xerox Corporation.  All rights reserved.
 * Copyright (c) 1996-1999 by Silicon Graphics.  All rights reserved.
 * Copyright (c) 2003-2011 Hewlett-Packard Development Company, L.P.
 *
 *
 * THIS MATERIAL IS PROVIDED AS IS, WITH ABSOLUTELY NO WARRANTY EXPRESSED
 * OR IMPLIED.  ANY USE IS AT YOUR OWN RISK.
 *
 * Permission is hereby granted to use or copy this program
 * for any purpose, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */

AO_INLINE unsigned/**/char
AO_char_fetch_and_add(volatile unsigned/**/char *addr, unsigned/**/char incr)
{
  return __atomic_fetch_add(addr, incr, __ATOMIC_RELAXED);
}
#define AO_HAVE_char_fetch_and_add

AO_INLINE void
AO_char_and(volatile unsigned/**/char *addr, unsigned/**/char value)
{
  (void)__atomic_and_fetch(addr, value, __ATOMIC_RELAXED);
}
#define AO_HAVE_char_and

AO_INLINE void
AO_char_or(volatile unsigned/**/char *addr, unsigned/**/char value)
{
  (void)__atomic_or_fetch(addr, value, __ATOMIC_RELAXED);
}
#define AO_HAVE_char_or

AO_INLINE void
AO_char_xor(volatile unsigned/**/char *addr, unsigned/**/char value)
{
  (void)__atomic_xor_fetch(addr, value, __ATOMIC_RELAXED);
}
#define AO_HAVE_char_xor
/*
 * Copyright (c) 1991-1994 by Xerox Corporation.  All rights reserved.
 * Copyright (c) 1996-1999 by Silicon Graphics.  All rights reserved.
 * Copyright (c) 2003-2011 Hewlett-Packard Development Company, L.P.
 *
 *
 * THIS MATERIAL IS PROVIDED AS IS, WITH ABSOLUTELY NO WARRANTY EXPRESSED
 * OR IMPLIED.  ANY USE IS AT YOUR OWN RISK.
 *
 * Permission is hereby granted to use or copy this program
 * for any purpose, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */

AO_INLINE unsigned/**/short
AO_short_fetch_and_add(volatile unsigned/**/short *addr, unsigned/**/short incr)
{
  return __atomic_fetch_add(addr, incr, __ATOMIC_RELAXED);
}
#define AO_HAVE_short_fetch_and_add

AO_INLINE void
AO_short_and(volatile unsigned/**/short *addr, unsigned/**/short value)
{
  (void)__atomic_and_fetch(addr, value, __ATOMIC_RELAXED);
}
#define AO_HAVE_short_and

AO_INLINE void
AO_short_or(volatile unsigned/**/short *addr, unsigned/**/short value)
{
  (void)__atomic_or_fetch(addr, value, __ATOMIC_RELAXED);
}
#define AO_HAVE_short_or

AO_INLINE void
AO_short_xor(volatile unsigned/**/short *addr, unsigned/**/short value)
{
  (void)__atomic_xor_fetch(addr, value, __ATOMIC_RELAXED);
}
#define AO_HAVE_short_xor
/*
 * Copyright (c) 1991-1994 by Xerox Corporation.  All rights reserved.
 * Copyright (c) 1996-1999 by Silicon Graphics.  All rights reserved.
 * Copyright (c) 2003-2011 Hewlett-Packard Development Company, L.P.
 *
 *
 * THIS MATERIAL IS PROVIDED AS IS, WITH ABSOLUTELY NO WARRANTY EXPRESSED
 * OR IMPLIED.  ANY USE IS AT YOUR OWN RISK.
 *
 * Permission is hereby granted to use or copy this program
 * for any purpose, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */

AO_INLINE unsigned
AO_int_fetch_and_add(volatile unsigned *addr, unsigned incr)
{
  return __atomic_fetch_add(addr, incr, __ATOMIC_RELAXED);
}
#define AO_HAVE_int_fetch_and_add

AO_INLINE void
AO_int_and(volatile unsigned *addr, unsigned value)
{
  (void)__atomic_and_fetch(addr, value, __ATOMIC_RELAXED);
}
#define AO_HAVE_int_and

AO_INLINE void
AO_int_or(volatile unsigned *addr, unsigned value)
{
  (void)__atomic_or_fetch(addr, value, __ATOMIC_RELAXED);
}
#define AO_HAVE_int_or

AO_INLINE void
AO_int_xor(volatile unsigned *addr, unsigned value)
{
  (void)__atomic_xor_fetch(addr, value, __ATOMIC_RELAXED);
}
#define AO_HAVE_int_xor
/*
 * Copyright (c) 1991-1994 by Xerox Corporation.  All rights reserved.
 * Copyright (c) 1996-1999 by Silicon Graphics.  All rights reserved.
 * Copyright (c) 2003-2011 Hewlett-Packard Development Company, L.P.
 *
 *
 * THIS MATERIAL IS PROVIDED AS IS, WITH ABSOLUTELY NO WARRANTY EXPRESSED
 * OR IMPLIED.  ANY USE IS AT YOUR OWN RISK.
 *
 * Permission is hereby granted to use or copy this program
 * for any purpose, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */

AO_INLINE AO_t
AO_fetch_and_add(volatile AO_t *addr, AO_t incr)
{
  return __atomic_fetch_add(addr, incr, __ATOMIC_RELAXED);
}
#define AO_HAVE_fetch_and_add

AO_INLINE void
AO_and(volatile AO_t *addr, AO_t value)
{
  (void)__atomic_and_fetch(addr, value, __ATOMIC_RELAXED);
}
#define AO_HAVE_and

AO_INLINE void
AO_or(volatile AO_t *addr, AO_t value)
{
  (void)__atomic_or_fetch(addr, value, __ATOMIC_RELAXED);
}
#define AO_HAVE_or

AO_INLINE void
AO_xor(volatile AO_t *addr, AO_t value)
{
  (void)__atomic_xor_fetch(addr, value, __ATOMIC_RELAXED);
}
#define AO_HAVE_xor
/*
 * Copyright (c) 1991-1994 by Xerox Corporation.  All rights reserved.
 * Copyright (c) 1996-1999 by Silicon Graphics.  All rights reserved.
 * Copyright (c) 2003-2011 Hewlett-Packard Development Company, L.P.
 *
 *
 * THIS MATERIAL IS PROVIDED AS IS, WITH ABSOLUTELY NO WARRANTY EXPRESSED
 * OR IMPLIED.  ANY USE IS AT YOUR OWN RISK.
 *
 * Permission is hereby granted to use or copy this program
 * for any purpose, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */

AO_INLINE unsigned/**/char
AO_char_fetch_and_add_acquire(volatile unsigned/**/char *addr, unsigned/**/char incr)
{
  return __atomic_fetch_add(addr, incr, __ATOMIC_ACQUIRE);
}
#define AO_HAVE_char_fetch_and_add_acquire

AO_INLINE void
AO_char_and_acquire(volatile unsigned/**/char *addr, unsigned/**/char value)
{
  (void)__atomic_and_fetch(addr, value, __ATOMIC_ACQUIRE);
}
#define AO_HAVE_char_and_acquire

AO_INLINE void
AO_char_or_acquire(volatile unsigned/**/char *addr, unsigned/**/char value)
{
  (void)__atomic_or_fetch(addr, value, __ATOMIC_ACQUIRE);
}
#define AO_HAVE_char_or_acquire

AO_INLINE void
AO_char_xor_acquire(volatile unsigned/**/char *addr, unsigned/**/char value)
{
  (void)__atomic_xor_fetch(addr, value, __ATOMIC_ACQUIRE);
}
#define AO_HAVE_char_xor_acquire
/*
 * Copyright (c) 1991-1994 by Xerox Corporation.  All rights reserved.
 * Copyright (c) 1996-1999 by Silicon Graphics.  All rights reserved.
 * Copyright (c) 2003-2011 Hewlett-Packard Development Company, L.P.
 *
 *
 * THIS MATERIAL IS PROVIDED AS IS, WITH ABSOLUTELY NO WARRANTY EXPRESSED
 * OR IMPLIED.  ANY USE IS AT YOUR OWN RISK.
 *
 * Permission is hereby granted to use or copy this program
 * for any purpose, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */

AO_INLINE unsigned/**/short
AO_short_fetch_and_add_acquire(volatile unsigned/**/short *addr, unsigned/**/short incr)
{
  return __atomic_fetch_add(addr, incr, __ATOMIC_ACQUIRE);
}
#define AO_HAVE_short_fetch_and_add_acquire

AO_INLINE void
AO_short_and_acquire(volatile unsigned/**/short *addr, unsigned/**/short value)
{
  (void)__atomic_and_fetch(addr, value, __ATOMIC_ACQUIRE);
}
#define AO_HAVE_short_and_acquire

AO_INLINE void
AO_short_or_acquire(volatile unsigned/**/short *addr, unsigned/**/short value)
{
  (void)__atomic_or_fetch(addr, value, __ATOMIC_ACQUIRE);
}
#define AO_HAVE_short_or_acquire

AO_INLINE void
AO_short_xor_acquire(volatile unsigned/**/short *addr, unsigned/**/short value)
{
  (void)__atomic_xor_fetch(addr, value, __ATOMIC_ACQUIRE);
}
#define AO_HAVE_short_xor_acquire
/*
 * Copyright (c) 1991-1994 by Xerox Corporation.  All rights reserved.
 * Copyright (c) 1996-1999 by Silicon Graphics.  All rights reserved.
 * Copyright (c) 2003-2011 Hewlett-Packard Development Company, L.P.
 *
 *
 * THIS MATERIAL IS PROVIDED AS IS, WITH ABSOLUTELY NO WARRANTY EXPRESSED
 * OR IMPLIED.  ANY USE IS AT YOUR OWN RISK.
 *
 * Permission is hereby granted to use or copy this program
 * for any purpose, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */

AO_INLINE unsigned
AO_int_fetch_and_add_acquire(volatile unsigned *addr, unsigned incr)
{
  return __atomic_fetch_add(addr, incr, __ATOMIC_ACQUIRE);
}
#define AO_HAVE_int_fetch_and_add_acquire

AO_INLINE void
AO_int_and_acquire(volatile unsigned *addr, unsigned value)
{
  (void)__atomic_and_fetch(addr, value, __ATOMIC_ACQUIRE);
}
#define AO_HAVE_int_and_acquire

AO_INLINE void
AO_int_or_acquire(volatile unsigned *addr, unsigned value)
{
  (void)__atomic_or_fetch(addr, value, __ATOMIC_ACQUIRE);
}
#define AO_HAVE_int_or_acquire

AO_INLINE void
AO_int_xor_acquire(volatile unsigned *addr, unsigned value)
{
  (void)__atomic_xor_fetch(addr, value, __ATOMIC_ACQUIRE);
}
#define AO_HAVE_int_xor_acquire
/*
 * Copyright (c) 1991-1994 by Xerox Corporation.  All rights reserved.
 * Copyright (c) 1996-1999 by Silicon Graphics.  All rights reserved.
 * Copyright (c) 2003-2011 Hewlett-Packard Development Company, L.P.
 *
 *
 * THIS MATERIAL IS PROVIDED AS IS, WITH ABSOLUTELY NO WARRANTY EXPRESSED
 * OR IMPLIED.  ANY USE IS AT YOUR OWN RISK.
 *
 * Permission is hereby granted to use or copy this program
 * for any purpose, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */

AO_INLINE AO_t
AO_fetch_and_add_acquire(volatile AO_t *addr, AO_t incr)
{
  return __atomic_fetch_add(addr, incr, __ATOMIC_ACQUIRE);
}
#define AO_HAVE_fetch_and_add_acquire

AO_INLINE void
AO_and_acquire(volatile AO_t *addr, AO_t value)
{
  (void)__atomic_and_fetch(addr, value, __ATOMIC_ACQUIRE);
}
#define AO_HAVE_and_acquire

AO_INLINE void
AO_or_acquire(volatile AO_t *addr, AO_t value)
{
  (void)__atomic_or_fetch(addr, value, __ATOMIC_ACQUIRE);
}
#define AO_HAVE_or_acquire

AO_INLINE void
AO_xor_acquire(volatile AO_t *addr, AO_t value)
{
  (void)__atomic_xor_fetch(addr, value, __ATOMIC_ACQUIRE);
}
#define AO_HAVE_xor_acquire
/*
 * Copyright (c) 1991-1994 by Xerox Corporation.  All rights reserved.
 * Copyright (c) 1996-1999 by Silicon Graphics.  All rights reserved.
 * Copyright (c) 2003-2011 Hewlett-Packard Development Company, L.P.
 *
 *
 * THIS MATERIAL IS PROVIDED AS IS, WITH ABSOLUTELY NO WARRANTY EXPRESSED
 * OR IMPLIED.  ANY USE IS AT YOUR OWN RISK.
 *
 * Permission is hereby granted to use or copy this program
 * for any purpose, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */

AO_INLINE unsigned/**/char
AO_char_fetch_and_add_release(volatile unsigned/**/char *addr, unsigned/**/char incr)
{
  return __atomic_fetch_add(addr, incr, __ATOMIC_RELEASE);
}
#define AO_HAVE_char_fetch_and_add_release

AO_INLINE void
AO_char_and_release(volatile unsigned/**/char *addr, unsigned/**/char value)
{
  (void)__atomic_and_fetch(addr, value, __ATOMIC_RELEASE);
}
#define AO_HAVE_char_and_release

AO_INLINE void
AO_char_or_release(volatile unsigned/**/char *addr, unsigned/**/char value)
{
  (void)__atomic_or_fetch(addr, value, __ATOMIC_RELEASE);
}
#define AO_HAVE_char_or_release

AO_INLINE void
AO_char_xor_release(volatile unsigned/**/char *addr, unsigned/**/char value)
{
  (void)__atomic_xor_fetch(addr, value, __ATOMIC_RELEASE);
}
#define AO_HAVE_char_xor_release
/*
 * Copyright (c) 1991-1994 by Xerox Corporation.  All rights reserved.
 * Copyright (c) 1996-1999 by Silicon Graphics.  All rights reserved.
 * Copyright (c) 2003-2011 Hewlett-Packard Development Company, L.P.
 *
 *
 * THIS MATERIAL IS PROVIDED AS IS, WITH ABSOLUTELY NO WARRANTY EXPRESSED
 * OR IMPLIED.  ANY USE IS AT YOUR OWN RISK.
 *
 * Permission is hereby granted to use or copy this program
 * for any purpose, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */

AO_INLINE unsigned/**/short
AO_short_fetch_and_add_release(volatile unsigned/**/short *addr, unsigned/**/short incr)
{
  return __atomic_fetch_add(addr, incr, __ATOMIC_RELEASE);
}
#define AO_HAVE_short_fetch_and_add_release

AO_INLINE void
AO_short_and_release(volatile unsigned/**/short *addr, unsigned/**/short value)
{
  (void)__atomic_and_fetch(addr, value, __ATOMIC_RELEASE);
}
#define AO_HAVE_short_and_release

AO_INLINE void
AO_short_or_release(volatile unsigned/**/short *addr, unsigned/**/short value)
{
  (void)__atomic_or_fetch(addr, value, __ATOMIC_RELEASE);
}
#define AO_HAVE_short_or_release

AO_INLINE void
AO_short_xor_release(volatile unsigned/**/short *addr, unsigned/**/short value)
{
  (void)__atomic_xor_fetch(addr, value, __ATOMIC_RELEASE);
}
#define AO_HAVE_short_xor_release
/*
 * Copyright (c) 1991-1994 by Xerox Corporation.  All rights reserved.
 * Copyright (c) 1996-1999 by Silicon Graphics.  All rights reserved.
 * Copyright (c) 2003-2011 Hewlett-Packard Development Company, L.P.
 *
 *
 * THIS MATERIAL IS PROVIDED AS IS, WITH ABSOLUTELY NO WARRANTY EXPRESSED
 * OR IMPLIED.  ANY USE IS AT YOUR OWN RISK.
 *
 * Permission is hereby granted to use or copy this program
 * for any purpose, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */

AO_INLINE unsigned
AO_int_fetch_and_add_release(volatile unsigned *addr, unsigned incr)
{
  return __atomic_fetch_add(addr, incr, __ATOMIC_RELEASE);
}
#define AO_HAVE_int_fetch_and_add_release

AO_INLINE void
AO_int_and_release(volatile unsigned *addr, unsigned value)
{
  (void)__atomic_and_fetch(addr, value, __ATOMIC_RELEASE);
}
#define AO_HAVE_int_and_release

AO_INLINE void
AO_int_or_release(volatile unsigned *addr, unsigned value)
{
  (void)__atomic_or_fetch(addr, value, __ATOMIC_RELEASE);
}
#define AO_HAVE_int_or_release

AO_INLINE void
AO_int_xor_release(volatile unsigned *addr, unsigned value)
{
  (void)__atomic_xor_fetch(addr, value, __ATOMIC_RELEASE);
}
#define AO_HAVE_int_xor_release
/*
 * Copyright (c) 1991-1994 by Xerox Corporation.  All rights reserved.
 * Copyright (c) 1996-1999 by Silicon Graphics.  All rights reserved.
 * Copyright (c) 2003-2011 Hewlett-Packard Development Company, L.P.
 *
 *
 * THIS MATERIAL IS PROVIDED AS IS, WITH ABSOLUTELY NO WARRANTY EXPRESSED
 * OR IMPLIED.  ANY USE IS AT YOUR OWN RISK.
 *
 * Permission is hereby granted to use or copy this program
 * for any purpose, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */

AO_INLINE AO_t
AO_fetch_and_add_release(volatile AO_t *addr, AO_t incr)
{
  return __atomic_fetch_add(addr, incr, __ATOMIC_RELEASE);
}
#define AO_HAVE_fetch_and_add_release

AO_INLINE void
AO_and_release(volatile AO_t *addr, AO_t value)
{
  (void)__atomic_and_fetch(addr, value, __ATOMIC_RELEASE);
}
#define AO_HAVE_and_release

AO_INLINE void
AO_or_release(volatile AO_t *addr, AO_t value)
{
  (void)__atomic_or_fetch(addr, value, __ATOMIC_RELEASE);
}
#define AO_HAVE_or_release

AO_INLINE void
AO_xor_release(volatile AO_t *addr, AO_t value)
{
  (void)__atomic_xor_fetch(addr, value, __ATOMIC_RELEASE);
}
#define AO_HAVE_xor_release
/*
 * Copyright (c) 1991-1994 by Xerox Corporation.  All rights reserved.
 * Copyright (c) 1996-1999 by Silicon Graphics.  All rights reserved.
 * Copyright (c) 2003-2011 Hewlett-Packard Development Company, L.P.
 *
 *
 * THIS MATERIAL IS PROVIDED AS IS, WITH ABSOLUTELY NO WARRANTY EXPRESSED
 * OR IMPLIED.  ANY USE IS AT YOUR OWN RISK.
 *
 * Permission is hereby granted to use or copy this program
 * for any purpose, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */

AO_INLINE unsigned/**/char
AO_char_fetch_and_add_full(volatile unsigned/**/char *addr, unsigned/**/char incr)
{
  return __atomic_fetch_add(addr, incr, __ATOMIC_SEQ_CST);
}
#define AO_HAVE_char_fetch_and_add_full

AO_INLINE void
AO_char_and_full(volatile unsigned/**/char *addr, unsigned/**/char value)
{
  (void)__atomic_and_fetch(addr, value, __ATOMIC_SEQ_CST);
}
#define AO_HAVE_char_and_full

AO_INLINE void
AO_char_or_full(volatile unsigned/**/char *addr, unsigned/**/char value)
{
  (void)__atomic_or_fetch(addr, value, __ATOMIC_SEQ_CST);
}
#define AO_HAVE_char_or_full

AO_INLINE void
AO_char_xor_full(volatile unsigned/**/char *addr, unsigned/**/char value)
{
  (void)__atomic_xor_fetch(addr, value, __ATOMIC_SEQ_CST);
}
#define AO_HAVE_char_xor_full
/*
 * Copyright (c) 1991-1994 by Xerox Corporation.  All rights reserved.
 * Copyright (c) 1996-1999 by Silicon Graphics.  All rights reserved.
 * Copyright (c) 2003-2011 Hewlett-Packard Development Company, L.P.
 *
 *
 * THIS MATERIAL IS PROVIDED AS IS, WITH ABSOLUTELY NO WARRANTY EXPRESSED
 * OR IMPLIED.  ANY USE IS AT YOUR OWN RISK.
 *
 * Permission is hereby granted to use or copy this program
 * for any purpose, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */

AO_INLINE unsigned/**/short
AO_short_fetch_and_add_full(volatile unsigned/**/short *addr, unsigned/**/short incr)
{
  return __atomic_fetch_add(addr, incr, __ATOMIC_SEQ_CST);
}
#define AO_HAVE_short_fetch_and_add_full

AO_INLINE void
AO_short_and_full(volatile unsigned/**/short *addr, unsigned/**/short value)
{
  (void)__atomic_and_fetch(addr, value, __ATOMIC_SEQ_CST);
}
#define AO_HAVE_short_and_full

AO_INLINE void
AO_short_or_full(volatile unsigned/**/short *addr, unsigned/**/short value)
{
  (void)__atomic_or_fetch(addr, value, __ATOMIC_SEQ_CST);
}
#define AO_HAVE_short_or_full

AO_INLINE void
AO_short_xor_full(volatile unsigned/**/short *addr, unsigned/**/short value)
{
  (void)__atomic_xor_fetch(addr, value, __ATOMIC_SEQ_CST);
}
#define AO_HAVE_short_xor_full
/*
 * Copyright (c) 1991-1994 by Xerox Corporation.  All rights reserved.
 * Copyright (c) 1996-1999 by Silicon Graphics.  All rights reserved.
 * Copyright (c) 2003-2011 Hewlett-Packard Development Company, L.P.
 *
 *
 * THIS MATERIAL IS PROVIDED AS IS, WITH ABSOLUTELY NO WARRANTY EXPRESSED
 * OR IMPLIED.  ANY USE IS AT YOUR OWN RISK.
 *
 * Permission is hereby granted to use or copy this program
 * for any purpose, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */

AO_INLINE unsigned
AO_int_fetch_and_add_full(volatile unsigned *addr, unsigned incr)
{
  return __atomic_fetch_add(addr, incr, __ATOMIC_SEQ_CST);
}
#define AO_HAVE_int_fetch_and_add_full

AO_INLINE void
AO_int_and_full(volatile unsigned *addr, unsigned value)
{
  (void)__atomic_and_fetch(addr, value, __ATOMIC_SEQ_CST);
}
#define AO_HAVE_int_and_full

AO_INLINE void
AO_int_or_full(volatile unsigned *addr, unsigned value)
{
  (void)__atomic_or_fetch(addr, value, __ATOMIC_SEQ_CST);
}
#define AO_HAVE_int_or_full

AO_INLINE void
AO_int_xor_full(volatile unsigned *addr, unsigned value)
{
  (void)__atomic_xor_fetch(addr, value, __ATOMIC_SEQ_CST);
}
#define AO_HAVE_int_xor_full
/*
 * Copyright (c) 1991-1994 by Xerox Corporation.  All rights reserved.
 * Copyright (c) 1996-1999 by Silicon Graphics.  All rights reserved.
 * Copyright (c) 2003-2011 Hewlett-Packard Development Company, L.P.
 *
 *
 * THIS MATERIAL IS PROVIDED AS IS, WITH ABSOLUTELY NO WARRANTY EXPRESSED
 * OR IMPLIED.  ANY USE IS AT YOUR OWN RISK.
 *
 * Permission is hereby granted to use or copy this program
 * for any purpose, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */

AO_INLINE AO_t
AO_fetch_and_add_full(volatile AO_t *addr, AO_t incr)
{
  return __atomic_fetch_add(addr, incr, __ATOMIC_SEQ_CST);
}
#define AO_HAVE_fetch_and_add_full

AO_INLINE void
AO_and_full(volatile AO_t *addr, AO_t value)
{
  (void)__atomic_and_fetch(addr, value, __ATOMIC_SEQ_CST);
}
#define AO_HAVE_and_full

AO_INLINE void
AO_or_full(volatile AO_t *addr, AO_t value)
{
  (void)__atomic_or_fetch(addr, value, __ATOMIC_SEQ_CST);
}
#define AO_HAVE_or_full

AO_INLINE void
AO_xor_full(volatile AO_t *addr, AO_t value)
{
  (void)__atomic_xor_fetch(addr, value, __ATOMIC_SEQ_CST);
}
#define AO_HAVE_xor_full
