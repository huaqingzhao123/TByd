// Copyright (c) 2005, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// ---
//
//
// A sparsetable is a random container that implements a sparse array,
// that is, an array that uses very little memory to store unassigned
// indices (in this case, between 1-2 bits per unassigned index).  For
// instance, if you allocate an array of size 5 and assign a[2] = <big
// struct>, then a[2] will take up a lot of memory but a[0], a[1],
// a[3], and a[4] will not.  Array elements that have a value are
// called "assigned".  Array elements that have no value yet, or have
// had their value cleared using erase() or clear(), are called
// "unassigned".
//
// Unassigned values seem to have the default value of T (see below).
// Nevertheless, there is a difference between an unassigned index and
// one explicitly assigned the value of T().  The latter is considered
// assigned.
//
// Access to an array element is constant time, as is insertion and
// deletion.  Insertion and deletion may be fairly slow, however:
// because of this container's memory economy, each insert and delete
// causes a memory reallocation.
//
// NOTE: You should not test(), get(), or set() any index that is
// greater than sparsetable.size().  If you need to do that, call
// resize() first.
//
// --- Template parameters
// PARAMETER   DESCRIPTION                           DEFAULT
// T           The value of the array: the type of   --
//             object that is stored in the array.
//
// GROUP_SIZE  How large each "group" in the table   48
//             is (see below).  Larger values use
//             a little less memory but cause most
//             operations to be a little slower
//
// Alloc:      Allocator to use to allocate memory.  libc_allocator_with_realloc
//
// --- Model of
// Random Access Container
//
// --- Type requirements
// T must be Copy Constructible. It need not be Assignable.
//
// --- Public base classes
// None.
//
// --- Members
// Type members
//
// MEMBER           WHERE DEFINED DESCRIPTION
// value_type       container     The type of object, T, stored in the array
// allocator_type   container     Allocator to use
// pointer          container     Pointer to p
// const_pointer    container     Const pointer to p
// reference        container     Reference to t
// const_reference  container     Const reference to t
// size_type        container     An unsigned integral type
// difference_type  container     A signed integral type
// iterator [*]     container     Iterator used to iterate over a sparsetable
// const_iterator   container     Const iterator used to iterate over a table
// reverse_iterator reversible    Iterator used to iterate backwards over
//                  container     a sparsetable
// const_reverse_iterator   reversible container   Guess
// nonempty_iterator [+]           sparsetable     Iterates over assigned
//                                                 array elements only
// const_nonempty_iterator         sparsetable     Iterates over assigned
//                                                 array elements only
// reverse_nonempty_iterator       sparsetable     Iterates backwards over
//                                                 assigned array elements only
// const_reverse_nonempty_iterator sparsetable     Iterates backwards over
//                                                 assigned array elements only
//
// [*] All iterators are const in a sparsetable (though nonempty_iterators
//     may not be).  Use get() and set() to assign values, not iterators.
//
// [+] iterators are random-access iterators.  nonempty_iterators are
//     bidirectional iterators.

// Iterator members
// MEMBER              WHERE DEFINED  DESCRIPTION
//
// iterator begin()    container      An iterator to the beginning of the table
// iterator end()      container      An iterator to the end of the table
// const_iterator      container      A const_iterator pointing to the
//   begin() const                    beginning of a sparsetable
// const_iterator      container      A const_iterator pointing to the
//   end() const                      end of a sparsetable
//
// reverse_iterator          reversable     Points to beginning of a reversed
//   rbegin()                container      sparsetable
// reverse_iterator          reversable     Points to end of a reversed table
//   rend()                  container
// const_reverse_iterator    reversable     Points to beginning of a
//   rbegin() const          container      reversed sparsetable
// const_reverse_iterator    reversable     Points to end of a reversed table
//   rend() const            container
//
// nonempty_iterator         sparsetable    Points to first assigned element
//    begin()                               of a sparsetable
// nonempty_iterator         sparsetable    Points past last assigned element
//    end()                                 of a sparsetable
// const_nonempty_iterator   sparsetable    Points to first assigned element
//    begin() const                         of a sparsetable
// const_nonempty_iterator   sparsetable    Points past last assigned element
//    end() const                           of a sparsetable
//
// reverse_nonempty_iterator sparsetable    Points to first assigned element
//    begin()                               of a reversed sparsetable
// reverse_nonempty_iterator sparsetable    Points past last assigned element
//    end()                                 of a reversed sparsetable
// const_reverse_nonempty_iterator sparsetable    Points to first assigned
//    begin() const                               elt of a reversed sparsetable
// const_reverse_nonempty_iterator sparsetable    Points past last assigned
//    end() const                                 elt of a reversed sparsetable
//
//
// Other members
// MEMBER                      WHERE DEFINED  DESCRIPTION
// sparsetable()               sparsetable    A table of size 0; must resize()
//                                            before using.
// sparsetable(size_type size) sparsetable    A table of size size.  All
//                                            indices are unassigned.
// sparsetable(
//    const sparsetable &tbl)  sparsetable    Copy constructor
// ~sparsetable()              sparsetable    The destructor
// sparsetable &operator=(     sparsetable    The assignment operator
//    const sparsetable &tbl)
//
// void resize(size_type size) sparsetable    Grow or shrink a table to
//                                            have size indices [*]
//
// void swap(sparsetable &x)   sparsetable    Swap two sparsetables
// void swap(sparsetable &x,   sparsetable    Swap two sparsetables
//           sparsetable &y)                  (global, not member, function)
//
// size_type size() const      sparsetable    Number of "buckets" in the table
// size_type max_size() const  sparsetable    Max allowed size of a sparsetable
// bool empty() const          sparsetable    true if size() == 0
// size_type num_nonempty() const  sparsetable  Number of assigned "buckets"
//
// const_reference get(        sparsetable    Value at index i, or default
//    size_type i) const                      value if i is unassigned
// const_reference operator[]( sparsetable    Identical to get(i) [+]
//    difference_type i) const
// reference set(size_type i,  sparsetable    Set element at index i to
//    const_reference val)                    be a copy of val
// bool test(size_type i)      sparsetable    True if element at index i
//    const                                   has been assigned to
// bool test(iterator pos)     sparsetable    True if element pointed to
//    const                                   by pos has been assigned to
// void erase(iterator pos)    sparsetable    Set element pointed to by
//                                            pos to be unassigned [!]
// void erase(size_type i)     sparsetable    Set element i to be unassigned
// void erase(iterator start,  sparsetable    Erases all elements between
//            iterator end)                   start and end
// void clear()                sparsetable    Erases all elements in the table
//
// I/O versions exist for both FILE* and for File* (Google2-style files):
// bool write_metadata(FILE *fp) sparsetable  Writes a sparsetable to the
// bool write_metadata(File *fp)              given file.  true if write
//                                            completes successfully
// bool read_metadata(FILE *fp) sparsetable   Replaces sparsetable with
// bool read_metadata(File *fp)               version read from fp.  true
//                                            if read completes sucessfully
// bool write_nopointer_data(FILE *fp)        Read/write the data stored in
// bool read_nopointer_data(FILE*fp)          the table, if it's simple
//
// bool operator==(            forward        Tests two tables for equality.
//    const sparsetable &t1,   container      This is a global function,
//    const sparsetable &t2)                  not a member function.
// bool operator<(             forward        Lexicographical comparison.
//    const sparsetable &t1,   container      This is a global function,
//    const sparsetable &t2)                  not a member function.
//
// [*] If you shrink a sparsetable using resize(), assigned elements
// past the end of the table are removed using erase().  If you grow
// a sparsetable, new unassigned indices are created.
//
// [+] Note that operator[] returns a const reference.  You must use
// set() to change the value of a table element.
//
// [!] Unassignment also calls the destructor.
//
// Iterators are invalidated whenever an item is inserted or
// deleted (ie set() or erase() is used) or when the size of
// the table changes (ie resize() or clear() is used).
//
// See doc/sparsetable.html for more information about how to use this class.

// Note: this uses STL style for naming, rather than Google naming.
// That's because this is an STL-y container

#ifndef UTIL_GTL_SPARSETABLE_H_
#define UTIL_GTL_SPARSETABLE_H_

#include "internal/sparseconfig.h"
#include <stdlib.h>             // for malloc/free
#include <stdio.h>              // to read/write tables
#include <string.h>             // for memcpy
#ifdef HAVE_STDINT_H
#include <stdint.h>         // the normal place uint16_t is defined
#endif
#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>      // the normal place u_int16_t is defined
#endif
#ifdef HAVE_INTTYPES_H
#include <inttypes.h>       // a third place for uint16_t or u_int16_t
#endif
#include <assert.h>             // for bounds checking
#include <iterator>             // to define reverse_iterator for me
#include <algorithm>            // equal, lexicographical_compare, swap,...
#include <memory>               // uninitialized_copy, uninitialized_fill
#include <vector>               // a sparsetable is a vector of groups
#include "type_traits.h"
#include "internal/hashtable-common.h"
#include "internal/libc_allocator_with_realloc.h"

// A lot of work to get a type that's guaranteed to be 16 bits...
#ifndef HAVE_U_INT16_T
# if defined HAVE_UINT16_T
    typedef uint16_t u_int16_t;    // true on solaris, possibly other C99 libc's
# elif defined HAVE___UINT16
    typedef __int16 int16_t;       // true on vc++7
    typedef unsigned __int16 u_int16_t;
# else
    // Cannot find a 16-bit integer type.  Hoping for the best with "short"...
    typedef short int int16_t;
    typedef unsigned short int u_int16_t;
# endif
#endif

_START_GOOGLE_NAMESPACE_

namespace base {   // just to make google->opensource transition easier
using GOOGLE_NAMESPACE::true_type;
using GOOGLE_NAMESPACE::false_type;
using GOOGLE_NAMESPACE::integral_constant;
using GOOGLE_NAMESPACE::has_trivial_copy;
using GOOGLE_NAMESPACE::has_trivial_destructor;
using GOOGLE_NAMESPACE::is_same;
}


// The smaller this is, the faster lookup is (because the group bitmap is
// smaller) and the faster insert is, because there's less to move.
// On the other hand, there are more groups.  Since group::size_type is
// a short, this number should be of the form 32*x + 16 to avoid waste.
static const u_int16_t DEFAULT_SPARSEGROUP_SIZE = 48;   // fits in 1.5 words


// Our iterator as simple as iterators can be: basically it's just
// the index into our table.  Dereference, the only complicated
// thing, we punt to the table class.  This just goes to show how
// much machinery STL requires to do even the most trivial tasks.
//
// A NOTE ON ASSIGNING:
// A sparse table does not actually allocate memory for entries
// that are not filled.  Because of this, it becomes complicated
// to have a non-const iterator: we don't know, if the iterator points
// to a not-filled bucket, whether you plan to fill it with something
// or whether you plan to read its value (in which case you'll get
// the default bucket value).  Therefore, while we can define const
// operations in a pretty 'normal' way, for non-const operations, we
// define something that returns a helper object with operator= and
// operator& that allocate a bucket lazily.  We use this for table[]
// and also for regular table iterators.

template <class tabletype>
class table_element_adaptor {
 public:
  typedef typename tabletype::value_type value_type;
  typedef typename tabletype::size_type size_type;
  typedef typename tabletype::reference reference;
  typedef typename tabletype::pointer pointer;

  table_element_adaptor(tabletype *tbl, size_type p)
    : table(tbl), pos(p) { }
  table_element_adaptor& operator= (const value_type &val) {
    table->set(pos, val);
    return *this;
  }
  operator value_type() { return table->get(pos); }   // we look like a value
  pointer operator& () { return &table->mutating_get(pos); }

 private:
  tabletype* table;
  size_type pos;
};

// Our iterator as simple as iterators can be: basically it's just
// the index into our table.  Dereference, the only complicated
// thing, we punt to the table class.  This just goes to show how
// much machinery STL requires to do even the most trivial tasks.
//
// By templatizing over tabletype, we have one iterator type which
// we can use for both sparsetables and sparsebins.  In fact it
// works on any class that allows size() and operator[] (eg vector),
// as long as it does the standard STL typedefs too (eg value_type).

template <class tabletype>
class table_iterator {
 public:
  typedef table_iterator iterator;

  typedef std::random_access_iterator_tag iterator_category;
  typedef typename tabletype::value_type value_type;
  typedef typename tabletype::difference_type difference_type;
  typedef typename tabletype::size_type size_type;
  typedef table_element_adaptor<tabletype> reference;
  typedef table_element_adaptor<tabletype>* pointer;

  // The "real" constructor
  table_iterator(tabletype *tbl, size_type p)
    : table(tbl), pos(p) { }
  // The default constructor, used when I define vars of type table::iterator
  table_iterator() : table(NULL), pos(0) { }
  // The copy constructor, for when I say table::iterator foo = tbl.begin()
  // The default destructor is fine; we don't define one
  // The default operator= is fine; we don't define one

  // The main thing our iterator does is dereference.  If the table entry
  // we point to is empty, we return the default value type.
  // This is the big different function from the const iterator.
  reference operator*()              {
    return table_element_adaptor<tabletype>(table, pos);
  }
  pointer operator->()               { return &(operator*()); }

  // Helper function to assert things are ok; eg pos is still in range
  void check() const {
    assert(table);
    assert(pos <= table->size());
  }

  // Arithmetic: we just do arithmetic on pos.  We don't even need to
  // do bounds checking, since STL doesn't consider that its job.  :-)
  iterator& operator+=(size_type t) { pos += t; check(); return *this; }
  iterator& operator-=(size_type t) { pos -= t; check(); return *this; }
  iterator& operator++()            { ++pos; check(); return *this; }
  iterator& operator--()            { --pos; check(); return *this; }
  iterator operator++(int)          { iterator tmp(*this);     // for x++
                                      ++pos; check(); return tmp; }
  iterator operator--(int)          { iterator tmp(*this);     // for x--
                                      --pos; check(); return tmp; }
  iterator operator+(difference_type i) const  { iterator tmp(*this);
                                                 tmp += i; return tmp; }
  iterator operator-(difference_type i) const  { iterator tmp(*this);
                                                 tmp -= i; return tmp; }
  difference_type operator-(iterator it) const {      // for "x = it2 - it"
    assert(table == it.table);
    return pos - it.pos;
  }
  reference operator[](difference_type n) const {
    return *(*this + n);            // simple though not totally efficient
  }

  // Comparisons.
  bool operator==(const iterator& it) const {
    return table == it.table && pos == it.pos;
  }
  bool operator<(const iterator& it) const {
    assert(table == it.table);              // life is bad bad bad otherwise
    return pos < it.pos;
  }
  bool operator!=(const iterator& it) const { return !(*this == it); }
  bool operator<=(const iterator& it) const { return !(it < *this); }
  bool operator>(const iterator& it) const { return it < *this; }
  bool operator>=(const iterator& it) const { return !(*this < it); }

  // Here's the info we actually need to be an iterator
  tabletype *table;              // so we can dereference and bounds-check
  size_type pos;                 // index into the table
};

// support for "3 + iterator" has to be defined outside the class, alas
template<class T>
table_iterator<T> operator+(typename table_iterator<T>::difference_type i,
                            table_iterator<T> it) {
  return it + i;               // so people can say it2 = 3 + it
}

template <class tabletype>
class const_table_iterator {
 public:
  typedef table_iterator<tabletype> iterator;
  typedef const_table_iterator const_iterator;

  typedef std::random_access_iterator_tag iterator_category;
  typedef typename tabletype::value_type value_type;
  typedef typename tabletype::difference_type difference_type;
  typedef typename tabletype::size_type size_type;
  typedef typename tabletype::const_reference reference;  // we're const-only
  typedef typename tabletype::const_pointer pointer;

  // The "real" constructor
  const_table_iterator(const tabletype *tbl, size_type p)
    : table(tbl), pos(p) { }
  // The default constructor, used when I define vars of type table::iterator
  const_table_iterator() : table(NULL), pos(0) { }
  // The copy constructor, for when I say table::iterator foo = tbl.begin()
  // Also converts normal iterators to const iterators
  const_table_iterator(const iterator &from)
    : table(from.table), pos(from.pos) { }
  // The default destructor is fine; we don't define one
  // The default operator= is fine; we don't define one

  // The main thing our iterator does is dereference.  If the table entry
  // we point to is empty, we return the default value type.
  reference operator*() const       { return (*table)[pos]; }
  pointer operator->() const        { return &(operator*()); }

  // Helper function to assert things are ok; eg pos is still in range
  void check() const {
    assert(table);
    assert(pos <= table->size());
  }

  // Arithmetic: we just do arithmetic on pos.  We don't even need to
  // do bounds checking, since STL doesn't consider that its job.  :-)
  const_iterator& operator+=(size_type t) { pos += t; check(); return *this; }
  const_iterator& operator-=(size_type t) { pos -= t; check(); return *this; }
  const_iterator& operator++()            { ++pos; check(); return *this; }
  const_iterator& operator--()            { --pos; check(); return *this; }
  const_iterator operator++(int)          { const_iterator tmp(*this); // for x++
                                            ++pos; check(); return tmp; }
  const_iterator operator--(int)          { const_iterator tmp(*this); // for x--
                                            --pos; check(); return tmp; }
  const_iterator operator+(difference_type i) const  { const_iterator tmp(*this);
                                                       tmp += i; return tmp; }
  const_iterator operator-(difference_type i) const  { const_iterator tmp(*this);
                                                       tmp -= i; return tmp; }
  difference_type operator-(const_iterator it) const {   // for "x = it2 - it"
    assert(table == it.table);
    return pos - it.pos;
  }
  reference operator[](difference_type n) const {
    return *(*this + n);            // simple though not totally efficient
  }

  // Comparisons.
  bool operator==(const const_iterator& it) const {
    return table == it.table && pos == it.pos;
  }
  bool operator<(const const_iterator& it) const {
    assert(table == it.table);              // life is bad bad bad otherwise
    return pos < it.pos;
  }
  bool operator!=(const const_iterator& it) const { return !(*this == it); }
  bool operator<=(const const_iterator& it) const { return !(it < *this); }
  bool operator>(const const_iterator& it) const { return it < *this; }
  bool operator>=(const const_iterator& it) const { return !(*this < it); }

  // Here's the info we actually need to be an iterator
  const tabletype *table;        // so we can dereference and bounds-check
  size_type pos;                 // index into the table
};

// support for "3 + iterator" has to be defined outside the class, alas
template<class T>
const_table_iterator<T> operator+(typename
                                  const_table_iterator<T>::difference_type i,
                                  const_table_iterator<T> it) {
  return it + i;               // so people can say it2 = 3 + it
}


// ---------------------------------------------------------------------------


/*
// This is a 2-D iterator.  You specify a begin and end over a list
// of *containers*.  We iterate over each container by iterating over
// it.  It's actually simple:
// VECTOR.begin() VECTOR[0].begin()  --------> VECTOR[0].end() ---,
//     |          ________________________________________________/
//     |          \_> VECTOR[1].begin()  -------->  VECTOR[1].end() -,
//     |          ___________________________________________________/
//     v          \_> ......
// VECTOR.end()
//
// It's impossible to do random access on one of these things in constant
// time, so it's just a bidirectional iterator.
//
// Unfortunately, because we need to use this for a non-empty iterator,
// we use nonempty_begin() and nonempty_end() instead of begin() and end()
// (though only going across, not down).
*/

#define TWOD_BEGIN_      nonempty_begin
#define TWOD_END_        nonempty_end
#define TWOD_ITER_       nonempty_iterator
#define TWOD_CONST_ITER_ const_nonempty_iterator

template <class containertype>
class two_d_iterator {
 public:
  typedef two_d_iterator iterator;

  typedef std::bidirectional_iterator_tag iterator_category;
  // apparently some versions of VC++ have trouble with two ::'s in a typename
  typedef typename containertype::value_type _tmp_vt;
  typedef typename _tmp_vt::value_type value_type;
  typedef typename _tmp_vt::difference_type difference_type;
  typedef typename _tmp_vt::reference reference;
  typedef typename _tmp_vt::pointer pointer;

  // The "real" constructor.  begin and end specify how many rows we have
  // (in the diagram above); we always iterate over each row completely.
  two_d_iterator(typename containertype::iterator begin,
                 typename containertype::iterator end,
                 typename containertype::iterator curr)
    : row_begin(begin), row_end(end), row_current(curr), col_current() {
    if ( row_current != row_end ) {
      col_current = row_current->TWOD_BEGIN_();
      advance_past_end();                 // in case cur->begin() == cur->end()
    }
  }
  // If you want to start at an arbitrary place, you can, I guess
  two_d_iterator(typename containertype::iterator begin,
                 typename containertype::iterator end,
                 typename containertype::iterator curr,
                 typename containertype::value_type::TWOD_ITER_ col)
    : row_begin(begin), row_end(end), row_current(curr), col_current(col) {
    advance_past_end();                 // in case cur->begin() == cur->end()
  }
  // The default constructor, used when I define vars of type table::iterator
  two_d_iterator() : row_begin(), row_end(), row_current(), col_current() { }
  // The default destructor is fine; we don't define one
  // The default operator= is fine; we don't define one

  // Happy dereferencer
  reference operator*() const    { return *col_current; }
  pointer operator->() const     { return &(operator*()); }

  // Arithmetic: we just do arithmetic on pos.  We don't even need to
  // do bounds checking, since STL doesn't consider that its job.  :-)
  // NOTE: this is not amortized constant time!  What do we do about it?
  void advance_past_end() {          // used when col_current points to end()
    while ( col_current == row_current->TWOD_END_() ) {  // end of current row
      ++row_current;                                // go to beginning of next
      if ( row_current != row_end )                 // col is irrelevant at end
        col_current = row_current->TWOD_BEGIN_();
      else
        break;                                      // don't go past row_end
    }
  }

  iterator& operator++() {
    assert(row_current != row_end);                 // how to ++ from there?
    ++col_current;
    advance_past_end();                 // in case col_current is at end()
    return *this;
  }
  iterator& operator--() {
    while ( row_current == row_end ||
            col_current == row_current->TWOD_BEGIN_() ) {
      assert(row_current != row_begin);
      --row_current;
      col_current = row_current->TWOD_END_();             // this is 1 too far
    }
    --col_current;
    return *this;
  }
  iterator operator++(int)       { iterator tmp(*this); ++*this; return tmp; }
  iterator operator--(int)       { iterator tmp(*this); --*this; return tmp; }


  // Comparisons.
  bool operator==(const iterator& it) const {
    return ( row_begin == it.row_begin &&
             row_end == it.row_end &&
             row_current == it.row_current &&
             (row_current == row_end || col_current == it.col_current) );
  }
  bool operator!=(const iterator& it) const { return !(*this == it); }


  // Here's the info we actually need to be an iterator
  // These need to be public so we convert from iterator to const_iterator
  typename containertype::iterator row_begin, row_end, row_current;
  typename containertype::value_type::TWOD_ITER_ col_current;
};

// The same thing again, but this time const.  :-(
template <class containertype>
class const_two_d_iterator {
 public:
  typedef const_two_d_iterator iterator;

  typedef std::bidirectional_iterator_tag iterator_category;
  // apparently some versions of VC++ have trouble with two ::'s in a typename
  typedef typename containertype::value_type _tmp_vt;
  typedef typename _tmp_vt::value_type value_type;
  typedef typename _tmp_vt::difference_type difference_type;
  typedef typename _tmp_vt::const_reference reference;
  typedef typename _tmp_vt::const_pointer pointer;

  const_two_d_iterator(typename containertype::const_iterator begin,
                       typename containertype::const_iterator end,
                       typename containertype::const_iterator curr)
    : row_begin(begin), row_end(end), row_current(curr), col_current() {
    if ( curr != end ) {
      col_current = curr->TWOD_BEGIN_();
      advance_past_end();                 // in case cur->begin() == cur->end()
    }
  }
  const_two_d_iterator(typename containertype::const_iterator begin,
                       typename containertype::const_iterator end,
                       typename containertype::const_iterator curr,
                       typename containertype::value_type::TWOD_CONST_ITER_ col)
    : row_begin(begin), row_end(end), row_current(curr), col_current(col) {
    advance_past_end();                 // in case cur->begin() == cur->end()
  }
  const_two_d_iterator()
    : row_begin(), row_end(), row_current(), col_current() {
  }
  // Need this explicitly so we can convert normal iterators to const iterators
  const_two_d_iterator(const two_d_iterator<containertype>& it) :
    row_begin(it.row_begin), row_end(it.row_end), row_current(it.row_current),
    col_current(it.col_current) { }

  typename containertype::const_iterator row_begin, row_end, row_current;
  typename containertype::value_type::TWOD_CONST_ITER_ col_current;


  // EVERYTHING FROM HERE DOWN IS THE SAME AS THE NON-CONST ITERATOR
  reference operator*() const    { return *col_current; }
  pointer operator->() const     { return &(operator*()); }

  void advance_past_end() {          // used when col_current points to end()
    while ( col_current == row_current->TWOD_END_() ) {  // end of current row
      ++row_current;                                // go to beginning of next
      if ( row_current != row_end )                 // col is irrelevant at end
        col_current = row_current->TWOD_BEGIN_();
      else
        break;                                      // don't go past row_end
    }
  }
  iterator& operator++() {
    assert(row_current != row_end);                 // how to ++ from there?
    ++col_current;
    advance_past_end();                 // in case col_current is at end()
    return *this;
  }
  iterator& operator--() {
    while ( row_current == row_end ||
            col_current == row_current->TWOD_BEGIN_() ) {
      assert(row_current != row_begin);
      --row_current;
      col_current = row_current->TWOD_END_();             // this is 1 too far
    }
    --col_current;
    return *this;
  }
  iterator operator++(int)       { iterator tmp(*this); ++*this; return tmp; }
  iterator operator--(int)       { iterator tmp(*this); --*this; return tmp; }

  bool operator==(const iterator& it) const {
    return ( row_begin == it.row_begin &&
             row_end == it.row_end &&
             row_current == it.row_current &&
             (row_current == row_end || col_current == it.col_current) );
  }
  bool operator!=(const iterator& it) const { return !(*this == it); }
};

// We provide yet another version, to be as frugal with memory as
// possible.  This one frees each block of memory as it finishes
// iterating over it.  By the end, the entire table is freed.
// For understandable reasons, you can only iterate over it once,
// which is why it's an input iterator
template <class containertype>
class destructive_two_d_iterator {
 public:
  typedef destructive_two_d_iterator iterator;

  typedef std::input_iterator_tag iterator_category;
  // apparently some versions of VC++ have trouble with two ::'s in a typename
  typedef typename containertype::value_type _tmp_vt;
  typedef typename _tmp_vt::value_type value_type;
  typedef typename _tmp_vt::difference_type difference_type;
  typedef typename _tmp_vt::reference reference;
  typedef typename _tmp_vt::pointer pointer;

  destructive_two_d_iterator(typename containertype::iterator begin,
                             typename containertype::iterator end,
                             typename containertype::iterator curr)
    : row_begin(begin), row_end(end), row_current(curr), col_current() {
    if ( curr != end ) {
      col_current = curr->TWOD_BEGIN_();
      advance_past_end();                 // in case cur->begin() == cur->end()
    }
  }
  destructive_two_d_iterator(typename containertype::iterator begin,
                             typename containertype::iterator end,
                             typename containertype::iterator curr,
                             typename containertype::value_type::TWOD_ITER_ col)
    : row_begin(begin), row_end(end), row_current(curr), col_current(col) {
    advance_past_end();                 // in case cur->begin() == cur->end()
  }
  destructive_two_d_iterator()
    : row_begin(), row_end(), row_current(), col_current() {
  }

  typename containertype::iterator row_begin, row_end, row_current;
  typename containertype::value_type::TWOD_ITER_ col_current;

  // This is the part that destroys
  void advance_past_end() {          // used when col_current points to end()
    while ( col_current == row_current->TWOD_END_() ) {  // end of current row
      row_current->clear();                         // the destructive part
      // It would be nice if we could decrement sparsetable->num_buckets here
      ++row_current;                                // go to beginning of next
      if ( row_current != row_end )                 // col is irrelevant at end
        col_current = row_current->TWOD_BEGIN_();
      else
        break;                                      // don't go past row_end
    }
  }

  // EVERYTHING FROM HERE DOWN IS THE SAME AS THE REGULAR ITERATOR
  reference operator*() const    { return *col_current; }
  pointer operator->() const     { return &(operator*()); }

  iterator& operator++() {
    assert(row_current != row_end);                 // how to ++ from there?
    ++col_current;
    advance_past_end();                 // in case col_current is at end()
    return *this;
  }
  iterator operator++(int)       { iterator tmp(*this); ++*this; return tmp; }

  bool operator==(const iterator& it) const {
    return ( row_begin == it.row_begin &&
             row_end == it.row_end &&
             row_current == it.row_current &&
             (row_current == row_end || col_current == it.col_current) );
  }
  bool operator!=(const iterator& it) const { return !(*this == it); }
};

#undef TWOD_BEGIN_
#undef TWOD_END_
#undef TWOD_ITER_
#undef TWOD_CONST_ITER_




// SPARSE-TABLE
// ------------
// The idea is that a table with (logically) t buckets is divided
// into t/M *groups* of M buckets each.  (M is a constant set in
// GROUP_SIZE for efficiency.)  Each group is stored sparsely.
// Thus, inserting into the table causes some array to grow, which is
// slow but still constant time.  Lookup involves doing a
// logical-position-to-sparse-position lookup, which is also slow but
// constant time.  The larger M is, the slower these operations are
// but the less overhead (slightly).
//
// To store the sparse array, we store a bitmap B, where B[i] = 1 iff
// bucket i is non-empty.  Then to look up bucket i we really look up
// array[# of 1s before i in B].  This is constant time for fixed M.
//
// Terminology: the position of an item in the overall table (from
// 1 .. t) is called its "location."  The logical position in a group
// (from 1 .. M ) is called its "position."  The actual location in
// the array (from 1 .. # of non-empty buckets in the group) is
// called its "offset."

template <class T, u_int16_t GROUP_SIZE, class Alloc>
class sparsegroup {
 private:
  typedef typename Alloc::template rebind<T>::other value_alloc_type;

 public:
  // Basic types
  typedef T value_type;
  typedef Alloc allocator_type;
  typedef typename value_alloc_type::reference reference;
  typedef typename value_alloc_type::const_reference const_reference;
  typedef typename value_alloc_type::pointer pointer;
  typedef typename value_alloc_type::const_pointer const_pointer;

  typedef table_iterator<sparsegroup<T, GROUP_SIZE, Alloc> > iterator;
  typedef const_table_iterator<sparsegroup<T, GROUP_SIZE, Alloc> >
      const_iterator;
  typedef table_element_adaptor<sparsegroup<T, GROUP_SIZE, Alloc> >
      element_adaptor;
  typedef u_int16_t size_type;                  // max # of buckets
  typedef int16_t difference_type;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
  typedef std::reverse_iterator<iterator> reverse_iterator;   // from iterator.h

  // These are our special iterators, that go over non-empty buckets in a
  // group.  These aren't const-only because you can change non-empty bcks.
  typedef pointer nonempty_iterator;
  typedef const_pointer const_nonempty_iterator;
  typedef std::reverse_iterator<nonempty_iterator> reverse_nonempty_iterator;
  typedef std::reverse_iterator<const_nonempty_iterator> const_reverse_nonempty_iterator;

  // Iterator functions
  iterator begin()                      { return iterator(this, 0); }
  const_iterator begin() const          { return const_iterator(this, 0); }
  iterator end()                        { return iterator(this, size()); }
  const_iterator end() const            { return const_iterator(this, size()); }
  reverse_iterator rbegin()             { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
  reverse_iterator rend()               { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

  // We'll have versions for our special non-empty iterator too
  nonempty_iterator nonempty_begin()             { return group; }
  const_nonempty_iterator nonempty_begin() const { return group; }
  nonempty_iterator nonempty_end() {
    return group + settings.num_buckets;
  }
  const_nonempty_iterator nonempty_end() const {
    return group + settings.num_buckets;
  }
  reverse_nonempty_iterator nonempty_rbegin() {
    return reverse_nonempty_iterator(nonempty_end());
  }
  const_reverse_nonempty_iterator nonempty_rbegin() const {
    return const_reverse_nonempty_iterator(nonempty_end());
  }
  reverse_nonempty_iterator nonempty_rend() {
    return reverse_nonempty_iterator(nonempty_begin());
  }
  const_reverse_nonempty_iterator nonempty_rend() const {
    return const_reverse_nonempty_iterator(nonempty_begin());
  }


  // This gives us the "default" value to return for an empty bucket.
  // We just use the default constructor on T, the template type
  const_reference default_value() const {
    static value_type defaultval = value_type();
    return defaultval;
  }


 private:
  // We need to do all this bit manipulation, of course.  ick
  static size_type charbit(size_type i)  { return i >> 3; }
  static size_type modbit(size_type i)   { return 1 << (i&7); }
  int bmtest(size_type i) const    { return bitmap[charbit(i)] & modbit(i); }
  void bmset(size_type i)          { bitmap[charbit(i)] |= modbit(i); }
  void bmclear(size_type i)        { bitmap[charbit(i)] &= ~modbit(i); }

  pointer allocate_group(size_type n) {
    pointer retval = settings.allocate(n);
    if (retval == NULL) {
      // We really should use PRIuS here, but I don't want to have to add
      // a whole new configure option, with concomitant macro namespace
      // pollution, just to print this (unlikely) error message.  So I cast.
      fprintf(stderr, "sparsehash FATAL ERROR: failed to allocate %lu groups\n",
              static_cast<unsigned long>(n));
      exit(1);
    }
    return retval;
  }

  void free_group() {
    if (!group)  return;
    pointer end_it = group + settings.num_buckets;
    for (pointer p = group; p != end_it; ++p)
      p->~value_type();
    settings.deallocate(group, settings.num_buckets);
    group = NULL;
  }

  static size_type bits_in_char(unsigned char c) {
    // We could make these ints.  The tradeoff is size (eg does it overwhelm
    // the cache?) vs efficiency in referencing sub-word-sized array elements.
    static const char bits_in[256] = {
      0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
      1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
      1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
      2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
      1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
      2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
      2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
      3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
      1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
      2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
      2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
      3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
      2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
      3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
      3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
      4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8,
    };
    return bits_in[c];
  }

 public:                         // get_iter() in sparsetable needs it
  // We need a small function that tells us how many set bits there are
  // in positions 0..i-1 of the bitmap.  It uses a big table.
  // We make it static so templates don't allocate lots of these tables.
  // There are lots of ways to do this calculation (called 'popcount').
  // The 8-bit table lookup is one of the fastest, though this
  // implementation suffers from not doing any loop unrolling.  See, eg,
  //   http://www.dalkescientific.com/writings/diary/archive/2008/07/03/hakmem_and_other_popcounts.html
  //   http://gurmeetsingh.wordpress.com/2008/08/05/fast-bit-counting-routines/
  static size_type pos_to_offset(const unsigned char *bm, size_type pos) {
    size_type retval = 0;

    // [Note: condition pos > 8 is an optimization; convince yourself we
    // give exactly the same result as if we had pos >= 8 here instead.]
    for ( ; pos > 8; pos -= 8 )                   // bm[0..pos/8-1]
      retval += bits_in_char(*bm++);              // chars we want *all* bits in
    return retval + bits_in_char(*bm & ((1 << pos)-1));    // char including pos
  }

  size_type pos_to_offset(size_type pos) const {  // not static but still const
    return pos_to_offset(bitmap, pos);
  }

  // Returns the (logical) position in the bm[] array, i, such that
  // bm[i] is the offset-th set bit in the array.  It is the inverse
  // of pos_to_offset.  get_pos() uses this function to find the index
  // of an nonempty_iterator in the table.  Bit-twiddling from
  // http://hackersdelight.org/basics.pdf
  static size_type offset_to_pos(const unsigned char *bm, size_type offset) {
    size_type retval = 0;
    // This is sizeof(this->bitmap).
    const size_type group_size = (GROUP_SIZE-1) / 8 + 1;
    for (size_type i = 0; i < group_size; i++) {   // forward scan
      const size_type pop_count = bits_in_char(*bm);
      if (pop_count > offset) {
        unsigned char last_bm = *bm;
        for (; offset > 0; offset--) {
          last_bm &= (last_bm-1);  // remove right-most set bit
        }
        // Clear all bits to the left of the rightmost bit (the &),
        // and then clear the rightmost bit but set all bits to the
        // right of it (the -1).
        last_bm = (last_bm & -last_bm) - 1;
        retval += bits_in_char(last_bm);
        return retval;
      }
      offset -= pop_count;
      retval += 8;
      bm++;
    }
    return retval;
  }

  size_type offset_to_pos(size_type offset) const {
    return offset_to_pos(bitmap, offset);
  }


 public:
  // Constructors -- default and copy -- and destructor
  explicit sparsegroup(allocator_type& a) :
      group(0), settings(alloc_impl<value_alloc_type>(a)) {
    memset(bitmap, 0, sizeof(bitmap));
  }
  sparsegroup(const sparsegroup& x) : group(0), settings(x.settings) {
    if ( settings.num_buckets ) {
      group = allocate_group(x.settings.num_buckets);
      std::uninitialized_copy(x.group, x.group + x.settings.num_buckets, group);
    }
    memcpy(bitmap, x.bitmap, sizeof(bitmap));
  }
  ~sparsegroup() { free_group(); }

  // Operator= is just like the copy constructor, I guess
  // TODO(austern): Make this exception safe. Handle exceptions in value_type's
  // copy constructor.
  sparsegroup &operator=(const sparsegroup& x) {
    if ( &x == this ) return *this;                    // x = x
    if ( x.settings.num_buckets == 0 ) {
      free_group();
    } else {
      pointer p = allocate_group(x.settings.num_buckets);
      std::uninitialized_copy(x.group, x.group + x.settings.num_buckets, p);
      free_group();
      group = p;
    }
    memcpy(bitmap, x.bitmap, sizeof(bitmap));
    settings.num_buckets = x.settings.num_buckets;
    return *this;
  }

  // Many STL algorithms use swap instead of copy constructors
  void swap(sparsegroup& x) {
    std::swap(group, x.group);                // defined in <algorithm>
    for ( int i = 0; i < sizeof(bitmap) / sizeof(*bitmap); ++i )
      std::swap(bitmap[i], x.bitmap[i]);      // swap not defined on arrays
    std::swap(settings.num_buckets, x.settings.num_buckets);
    // we purposefully don't swap the allocator, which may not be swap-able
  }

  // It's always nice to be able to clear a table without deallocating it
  void clear() {
    free_group();
    memset(bitmap, 0, sizeof(bitmap));
    settings.num_buckets = 0;
  }

  // Functions that tell you about size.  Alas, these aren't so useful
  // because our table is always fixed size.
  size_type size() const           { return GROUP_SIZE; }
  size_type max_size() const       { return GROUP_SIZE; }
  bool empty() const               { return false; }
  // We also may want to know how many *used* buckets there are
  size_type num_nonempty() const   { return settings.num_buckets; }


  // get()/set() are explicitly const/non-const.  You can use [] if
  // you want something that can be either (potentially more expensive).
  const_reference get(size_type i) const {
    if ( bmtest(i) )           // bucket i is occupied
      return group[pos_to_offset(bitmap, i)];
    else
      return default_value();  // return the default reference
  }

  // TODO(csilvers): make protected + friend
  // This is used by sparse_hashtable to get an element from the table
  // when we know it exists.
  const_reference unsafe_get(size_type i) const {
    assert(bmtest(i));
    return group[pos_to_offset(bitmap, i)];
  }

  // TODO(csilvers): make protected + friend
  reference mutating_get(size_type i) {    // fills bucket i before getting
    if ( !bmtest(i) )
      set(i, default_value());
    return group[pos_to_offset(bitmap, i)];
  }

  // Syntactic sugar.  It's easy to return a const reference.  To
  // return a non-const reference, we need to use the assigner adaptor.
  const_reference operator[](size_type i) const {
    return get(i);
  }

  element_adaptor operator[](size_type i) {
    return element_adaptor(this, i);
  }

 private:
  // Create space at group[offset], assuming value_type has trivial
  // copy constructor and destructor, and the allocator_type is
  // the default libc_allocator_with_alloc.  (Really, we want it to have
  // "trivial move", because that's what realloc and memmove both do.
  // But there's no way to capture that using type_traits, so we
  // pretend that move(x, y) is equivalent to "x.~T(); new(x) T(y);"
  // which is pretty much correct, if a bit conservative.)
  void set_aux(size_type offset, base::true_type) {
    group = settings.realloc_or_die(group, settings.num_buckets+1);
    // This is equivalent to memmove(), but faster on my Intel P4,
    // at least with gcc4.1 -O2 / glibc 2.3.6.
    for (size_type i = settings.num_buckets; i > offset; --i)
      // cast to void* to prevent compiler warnings about writing to an object
      // with no trivial copy-assignment
      memcpy(static_cast<void*>(group + i), group + i-1, sizeof(*group));
  }

  // Create space at group[offset], without special assumptions about value_type
  // and allocator_type.
  void set_aux(size_type offset, base::false_type) {
    // This is valid because 0 <= offset <= num_buckets
    pointer p = allocate_group(settings.num_buckets + 1);
    std::uninitialized_copy(group, group + offset, p);
    std::uninitialized_copy(group + offset, group + settings.num_buckets,
                            p + offset + 1);
    free_group();
    group = p;
  }

 public:
  // This returns a reference to the inserted item (which is a copy of val).
  // TODO(austern): Make this exception safe: handle exceptions from
  // value_type's copy constructor.
  reference set(size_type i, const_reference val) {
    size_type offset = pos_to_offset(bitmap, i);  // where we'll find (or insert)
    if ( bmtest(i) ) {
      // Delete the old value, which we're replacing with the new one
      group[offset].~value_type();
    } else {
      typedef base::integral_constant<bool,
          (base::has_trivial_copy<value_type>::value &&
           base::has_trivial_destructor<value_type>::value &&
           base::is_same<
               allocator_type,
               libc_allocator_with_realloc<value_type> >::value)>
          realloc_and_memmove_ok; // we pretend mv(x,y) == "x.~T(); new(x) T(y)"
      set_aux(offset, realloc_and_memmove_ok());
      ++settings.num_buckets;
      bmset(i);
    }
    // This does the actual inserting.  Since we made the array using
    // malloc, we use "placement new" to just call the constructor.
    new(&group[offset]) value_type(val);
    return group[offset];
  }

  // We let you see if a bucket is non-empty without retrieving it
  bool test(size_type i) const {
    return bmtest(i) != 0;
  }
  bool test(iterator pos) const {
    return bmtest(pos.pos) != 0;
  }

 private:
  // Shrink the array, assuming value_type has trivial copy
  // constructor and destructor, and the allocator_type is the default
  // libc_allocator_with_alloc.  (Really, we want it to have "trivial
  // move", because that's what realloc and memmove both do.  But
  // there's no way to capture that using type_traits, so we pretend
  // that move(x, y) is equivalent to ""x.~T(); new(x) T(y);"
  // which is pretty much correct, if a bit conservative.)
  void erase_aux(size_type offset, base::true_type) {
    // This isn't technically necessary, since we know we have a
    // trivial destructor, but is a cheap way to get a bit more safety.
    group[offset].~value_type();
    // This is equivalent to memmove(), but faster on my Intel P4,
    // at lesat with gcc4.1 -O2 / glibc 2.3.6.
    assert(settings.num_buckets > 0);
    for (size_type i = offset; i < settings.num_buckets-1; ++i)
      // cast to void* to prevent compiler warnings about writing to an object
      // with no trivial copy-assignment
      // hopefully inlined!
      memcpy(static_cast<void*>(group + i), group + i+1, sizeof(*group));
    group = settings.realloc_or_die(group, settings.num_buckets-1);
  }

  // Shrink the array, without any special assumptions about value_type and
  // allocator_type.
  void erase_aux(size_type offset, base::false_type) {
    // This is valid because 0 <= offset < num_buckets. Note the inequality.
    pointer p = allocate_group(settings.num_buckets - 1);
    std::uninitialized_copy(group, group + offset, p);
    std::uninitialized_copy(group + offset + 1, group + settings.num_buckets,
                            p + offset);
    free_group();
    group = p;
  }

 public:
  // This takes the specified elements out of the group.  This is
  // "undefining", rather than "clearing".
  // TODO(austern): Make this exception safe: handle exceptions from
  // value_type's copy constructor.
  void erase(size_type i) {
    if ( bmtest(i) ) {                         // trivial to erase empty bucket
      size_type offset = pos_to_offset(bitmap,i); // where we'll find (or insert)
      if ( settings.num_buckets == 1 ) {
        free_group();
        group = NULL;
      } else {
        typedef base::integral_constant<bool,
            (base::has_trivial_copy<value_type>::value &&
             base::has_trivial_destructor<value_type>::value &&
             base::is_same<
                 allocator_type,
                 libc_allocator_with_realloc<value_type> >::value)>
            realloc_and_memmove_ok; // pretend mv(x,y) == "x.~T(); new(x) T(y)"
        erase_aux(offset, realloc_and_memmove_ok());
      }
      --settings.num_buckets;
      bmclear(i);
    }
  }

  void erase(iterator pos) {
    erase(pos.pos);
  }

  void erase(iterator start_it, iterator end_it) {
    // This could be more efficient, but to do so we'd need to make
    // bmclear() clear a range of indices.  Doesn't seem worth it.
    for ( ; start_it != end_it; ++start_it )
      erase(start_it);
  }


  // I/O
  // We support reading and writing groups to disk.  We don't store
  // the actual array contents (which we don't know how to store),
  // just the bitmap and size.  Meant to be used with table I/O.

  template <typename OUTPUT> bool write_metadata(OUTPUT *fp) const {
    // we explicitly set to u_int16_t
    assert(sizeof(settings.num_buckets) == 2);
    if ( !sparsehash_internal::write_bigendian_number(fp, settings.num_buckets,
                                                      2) )
      return false;
    if ( !sparsehash_internal::write_data(fp, bitmap, sizeof(bitmap)) )
      return false;
    return true;
  }

  // Reading destroys the old group contents!  Returns true if all was ok.
  template <typename INPUT> bool read_metadata(INPUT *fp) {
    clear();
    if ( !sparsehash_internal::read_bigendian_number(fp, &settings.num_buckets,
                                                     2) )
      return false;
    if ( !sparsehash_internal::read_data(fp, bitmap, sizeof(bitmap)) )
      return false;
    // We'll allocate the space, but we won't fill it: it will be
    // left as uninitialized raw memory.
    group = allocate_group(settings.num_buckets);
    return true;
  }

  // Again, only meaningful if value_type is a POD.
  template <typename INPUT> bool read_nopointer_data(INPUT *fp) {
     for ( nonempty_iterator it = nonempty_begin();
           it != nonempty_end(); ++it ) {
       if ( !sparsehash_internal::read_data(fp, &(*it), sizeof(*it)) )
         return false;
     }
     return true;
  }

  // If your keys and values are simple enough, we can write them
  // to disk for you.  "simple enough" means POD and no pointers.
  // However, we don't try to normalize endianness.
  template <typename OUTPUT> bool write_nopointer_data(OUTPUT *fp) const {
    for ( const_nonempty_iterator it = nonempty_begin();
          it != nonempty_end(); ++it ) {
      if ( !sparsehash_internal::write_data(fp, &(*it), sizeof(*it)) )
        return false;
    }
    return true;
  }


  // Comparisons.  We only need to define == and < -- we get
  // != > <= >= via relops.h (which we happily included above).
  // Note the comparisons are pretty arbitrary: we compare
  // values of the first index that isn't equal (using default
  // value for empty buckets).
  bool operator==(const sparsegroup& x) const {
    return ( settings.num_buckets == x.settings.num_buckets &&
             memcmp(bitmap, x.bitmap, sizeof(bitmap)) == 0 &&
             std::equal(begin(), end(), x.begin()) );    // from <algorithm>
  }

  bool operator<(const sparsegroup& x) const {      // also from <algorithm>
    return std::lexicographical_compare(begin(), end(), x.begin(), x.end());
  }
  bool operator!=(const sparsegroup& x) const { return !(*this == x); }
  bool operator<=(const sparsegroup& x) const { return !(x < *this); }
  bool operator>(const sparsegroup& x) const { return x < *this; }
  bool operator>=(const sparsegroup& x) const { return !(*this < x); }

 private:
  template <class A>
  class alloc_impl : public A {
   public:
    typedef typename A::pointer pointer;
    typedef typename A::size_type size_type;

    // Convert a normal allocator to one that has realloc_or_die()
    alloc_impl(const A& a) : A(a) { }

    // realloc_or_die should only be used when using the default
    // allocator (libc_allocator_with_realloc).
    pointer realloc_or_die(pointer /*ptr*/, size_type /*n*/) {
      fprintf(stderr, "realloc_or_die is only supported for "
                      "libc_allocator_with_realloc\n");
      exit(1);
      return NULL;
    }
  };

  // A template specialization of alloc_impl for
  // libc_allocator_with_realloc that can handle realloc_or_die.
  template <class A>
  class alloc_impl<libc_allocator_with_realloc<A> >
      : public libc_allocator_with_realloc<A> {
   public:
    typedef typename libc_allocator_with_realloc<A>::pointer pointer;
    typedef typename libc_allocator_with_realloc<A>::size_type size_type;

    alloc_impl(const libc_allocator_with_realloc<A>& a)
        : libc_allocator_with_realloc<A>(a) { }

    pointer realloc_or_die(pointer ptr, size_type n) {
      pointer retval = this->reallocate(ptr, n);
      if (retval == NULL) {
        fprintf(stderr, "sparsehash: FATAL ERROR: failed to reallocate "
                "%lu elements for ptr %p", static_cast<unsigned long>(n), ptr);
        exit(1);
      }
      return retval;
    }
  };

  // Package allocator with num_buckets to eliminate memory needed for the
  // zero-size allocator.
  // If new fields are added to this class, we should add them to
  // operator= and swap.
  class Settings : public alloc_impl<value_alloc_type> {
   public:
    Settings(const alloc_impl<value_alloc_type>& a, u_int16_t n = 0)
        : alloc_impl<value_alloc_type>(a), num_buckets(n) { }
    Settings(const Settings& s)
        : alloc_impl<value_alloc_type>(s), num_buckets(s.num_buckets) { }

    u_int16_t num_buckets;                    // limits GROUP_SIZE to 64K
  };

  // The actual data
  pointer group;                              // (small) array of T's
  Settings settings;                          // allocator and num_buckets
  unsigned char bitmap[(GROUP_SIZE-1)/8 + 1]; // fancy math is so we round up
};

// We need a global swap as well
template <class T, u_int16_t GROUP_SIZE, class Alloc>
inline void swap(sparsegroup<T,GROUP_SIZE,Alloc> &x,
                 sparsegroup<T,GROUP_SIZE,Alloc> &y) {
  x.swap(y);
}

// ---------------------------------------------------------------------------


template <class T, u_int16_t GROUP_SIZE = DEFAULT_SPARSEGROUP_SIZE,
          class Alloc = libc_allocator_with_realloc<T> >
class sparsetable {
 private:
  typedef typename Alloc::template rebind<T>::other value_alloc_type;
  typedef typename Alloc::template rebind<
      sparsegroup<T, GROUP_SIZE, value_alloc_type> >::other vector_alloc;

 public:
  // Basic types
  typedef T value_type;                        // stolen from stl_vector.h
  typedef Alloc allocator_type;
  typedef typename value_alloc_type::size_type size_type;
  typedef typename value_alloc_type::difference_type difference_type;
  typedef typename value_alloc_type::reference reference;
  typedef typename value_alloc_type::const_reference const_reference;
  typedef typename value_alloc_type::pointer pointer;
  typedef typename value_alloc_type::const_pointer const_pointer;
  typedef table_iterator<sparsetable<T, GROUP_SIZE, Alloc> > iterator;
  typedef const_table_iterator<sparsetable<T, GROUP_SIZE, Alloc> >
      const_iterator;
  typedef table_element_adaptor<sparsetable<T, GROUP_SIZE, Alloc> >
      element_adaptor;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
  typedef std::reverse_iterator<iterator> reverse_iterator;   // from iterator.h

  // These are our special iterators, that go over non-empty buckets in a
  // table.  These aren't const only because you can change non-empty bcks.
  typedef two_d_iterator< std::vector< sparsegroup<value_type, GROUP_SIZE,
                                                   value_alloc_type>,
                                  vector_alloc> >
     nonempty_iterator;
  typedef const_two_d_iterator< std::vector< sparsegroup<value_type,
                                                         GROUP_SIZE,
                                                         value_alloc_type>,
                                        vector_alloc> >
     const_nonempty_iterator;
  typedef std::reverse_iterator<nonempty_iterator> reverse_nonempty_iterator;
  typedef std::reverse_iterator<const_nonempty_iterator> const_reverse_nonempty_iterator;
  // Another special iterator: it frees memory as it iterates (used to resize)
  typedef destructive_two_d_iterator< std::vector< sparsegroup<value_type,
                                                               GROUP_SIZE,
                                                               value_alloc_type>,
                                              vector_alloc> >
     destructive_iterator;

  // Iterator functions
  iterator begin()                      { return iterator(this, 0); }
  const_iterator begin() const          { return const_iterator(this, 0); }
  iterator end()                        { return iterator(this, size()); }
  const_iterator end() const            { return const_iterator(this, size()); }
  reverse_iterator rbegin()             { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
  reverse_iterator rend()               { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

  // Versions for our special non-empty iterator
  nonempty_iterator nonempty_begin()             {
    return nonempty_iterator(groups.begin(), groups.end(), groups.begin());
  }
  const_nonempty_iterator nonempty_begin() const {
    return const_nonempty_iterator(groups.begin(),groups.end(), groups.begin());
  }
  nonempty_iterator nonempty_end() {
    return nonempty_iterator(groups.begin(), groups.end(), groups.end());
  }
  const_nonempty_iterator nonempty_end() const {
    return const_nonempty_iterator(groups.begin(), groups.end(), groups.end());
  }
  reverse_nonempty_iterator nonempty_rbegin() {
    return reverse_nonempty_iterator(nonempty_end());
  }
  const_reverse_nonempty_iterator nonempty_rbegin() const {
    return const_reverse_nonempty_iterator(nonempty_end());
  }
  reverse_nonempty_iterator nonempty_rend() {
    return reverse_nonempty_iterator(nonempty_begin());
  }
  const_reverse_nonempty_iterator nonempty_rend() const {
    return const_reverse_nonempty_iterator(nonempty_begin());
  }
  destructive_iterator destructive_begin() {
    return destructive_iterator(groups.begin(), groups.end(), groups.begin());
  }
  destructive_iterator destructive_end() {
    return destructive_iterator(groups.begin(), groups.end(), groups.end());
  }

  typedef sparsegroup<value_type, GROUP_SIZE, allocator_type> group_type;
  typedef std::vector<group_type, vector_alloc > group_vector_type;

  typedef typename group_vector_type::reference GroupsReference;
  typedef typename group_vector_type::const_reference GroupsConstReference;
  typedef typename group_vector_type::iterator GroupsIterator;
  typedef typename group_vector_type::const_iterator GroupsConstIterator;

  // How to deal with the proper group
  static size_type num_groups(size_type num) {   // how many to hold num buckets
    return num == 0 ? 0 : ((num-1) / GROUP_SIZE) + 1;
  }

  u_int16_t pos_in_group(size_type i) const {
    return static_cast<u_int16_t>(i % GROUP_SIZE);
  }
  size_type group_num(size_type i) const {
    return i / GROUP_SIZE;
  }
  GroupsReference which_group(size_type i) {
    return groups[group_num(i)];
  }
  GroupsConstReference which_group(size_type i) const {
    return groups[group_num(i)];
  }

 public:
  // Constructors -- default, normal (when you specify size), and copy
  explicit sparsetable(size_type sz = 0, Alloc alloc = Alloc())
      : groups(vector_alloc(alloc)), settings(alloc, sz) {
    groups.resize(num_groups(sz), group_type(settings));
  }
  // We can get away with using the default copy constructor,
  // and default destructor, and hence the default operator=.  Huzzah!

  // Many STL algorithms use swap instead of copy constructors
  void swap(sparsetable& x) {
    std::swap(groups, x.groups);              // defined in stl_algobase.h
    std::swap(settings.table_size, x.settings.table_size);
    std::swap(settings.num_buckets, x.settings.num_buckets);
  }

  // It's always nice to be able to clear a table without deallocating it
  void clear() {
    GroupsIterator group;
    for ( group = groups.begin(); group != groups.end(); ++group ) {
      group->clear();
    }
    settings.num_buckets = 0;
  }

  // ACCESSOR FUNCTIONS for the things we templatize on, basically
  allocator_type get_allocator() const {
    return allocator_type(settings);
  }


  // Functions that tell you about size.
  // NOTE: empty() is non-intuitive!  It does not tell you the number
  // of not-empty buckets (use num_nonempty() for that).  Instead
  // it says whether you've allocated any buckets or not.
  size_type size() const           { return settings.table_size; }
  size_type max_size() const       { return settings.max_size(); }
  bool empty() const               { return settings.table_size == 0; }
  // We also may want to know how many *used* buckets there are
  size_type num_nonempty() const   { return settings.num_buckets; }

  // OK, we'll let you resize one of these puppies
  void resize(size_type new_size) {
    groups.resize(num_groups(new_size), group_type(settings));
    if ( new_size < settings.table_size) {
      // lower num_buckets, clear last group
      if ( pos_in_group(new_size) > 0 )     // need to clear inside last group
        groups.back().erase(groups.back().begin() + pos_in_group(new_size),
                            groups.back().end());
      settings.num_buckets = 0;                   // refigure # of used buckets
      GroupsConstIterator group;
      for ( group = groups.begin(); group != groups.end(); ++group )
        settings.num_buckets += group->num_nonempty();
    }
    settings.table_size = new_size;
  }


  // We let you see if a bucket is non-empty without retrieving it
  bool test(size_type i) const {
    assert(i < settings.table_size);
    return which_group(i).test(pos_in_group(i));
  }
  bool test(iterator pos) const {
    return which_group(pos.pos).test(pos_in_group(pos.pos));
  }
  bool test(const_iterator pos) const {
    return which_group(pos.pos).test(pos_in_group(pos.pos));
  }

  // We only return const_references because it's really hard to
  // return something settable for empty buckets.  Use set() instead.
  const_reference get(size_type i) const {
    assert(i < settings.table_size);
    return which_group(i).get(pos_in_group(i));
  }

  // TODO(csilvers): make protected + friend
  // This is used by sparse_hashtable to get an element from the table
  // when we know it exists (because the caller has called test(i)).
  const_reference unsafe_get(size_type i) const {
    assert(i < settings.table_size);
    assert(test(i));
    return which_group(i).unsafe_get(pos_in_group(i));
  }

  // TODO(csilvers): make protected + friend element_adaptor
  reference mutating_get(size_type i) {    // fills bucket i before getting
    assert(i < settings.table_size);
    typename group_type::size_type old_numbuckets = which_group(i).num_nonempty();
    reference retval = which_group(i).mutating_get(pos_in_group(i));
    settings.num_buckets += which_group(i).num_nonempty() - old_numbuckets;
    return retval;
  }

  // Syntactic sugar.  As in sparsegroup, the non-const version is harder
  const_reference operator[](size_type i) const {
    return get(i);
  }

  element_adaptor operator[](size_type i) {
    return element_adaptor(this, i);
  }

  // Needed for hashtables, gets as a nonempty_iterator.  Crashes for empty bcks
  const_nonempty_iterator get_iter(size_type i) const {
    assert(test(i));    // how can a nonempty_iterator point to an empty bucket?
    return const_nonempty_iterator(
      groups.begin(), groups.end(),
      groups.begin() + group_num(i),
      (groups[group_num(i)].nonempty_begin() +
       groups[group_num(i)].pos_to_offset(pos_in_group(i))));
  }
  // For nonempty we can return a non-const version
  nonempty_iterator get_iter(size_type i) {
    assert(test(i));    // how can a nonempty_iterator point to an empty bucket?
    return nonempty_iterator(
      groups.begin(), groups.end(),
      groups.begin() + group_num(i),
      (groups[group_num(i)].nonempty_begin() +
       groups[group_num(i)].pos_to_offset(pos_in_group(i))));
  }

  // And the reverse transformation.
  size_type get_pos(const const_nonempty_iterator& it) const {
    difference_type current_row = it.row_current - it.row_begin;
    difference_type current_col = (it.col_current -
                                   groups[current_row].nonempty_begin());
    return ((current_row * GROUP_SIZE) +
            groups[current_row].offset_to_pos(current_col));
  }


  // This returns a reference to the inserted item (which is a copy of val)
  // The trick is to figure out whether we're replacing or inserting anew
  reference set(size_type i, const_reference val) {
    assert(i < settings.table_size);
    typename group_type::size_type old_numbuckets = which_group(i).num_nonempty();
    reference retval = which_group(i).set(pos_in_group(i), val);
    settings.num_buckets += which_group(i).num_nonempty() - old_numbuckets;
    return retval;
  }

  // This takes the specified elements out of the table.  This is
  // "undefining", rather than "clearing".
  void erase(size_type i) {
    assert(i < settings.table_size);
    typename group_type::size_type old_numbuckets = which_group(i).num_nonempty();
    which_group(i).erase(pos_in_group(i));
    settings.num_buckets += which_group(i).num_nonempty() - old_numbuckets;
  }

  void erase(iterator pos) {
    erase(pos.pos);
  }

  void erase(iterator start_it, iterator end_it) {
    // This could be more efficient, but then we'd need to figure
    // out if we spanned groups or not.  Doesn't seem worth it.
    for ( ; start_it != end_it; ++start_it )
      erase(start_it);
  }


  // We support reading and writing tables to disk.  We don't store
  // the actual array contents (which we don't know how to store),
  // just the groups and sizes.  Returns true if all went ok.

 private:
  // Every time the disk format changes, this should probably change too
  typedef unsigned long MagicNumberType;
  static const MagicNumberType MAGIC_NUMBER = 0x24687531;

  // Old versions of this code write all data in 32 bits.  We need to
  // support these files as well as having support for 64-bit systems.
  // So we use the following encoding scheme: for values < 2^32-1, we
  // store in 4 bytes in big-endian order.  For values > 2^32, we
  // store 0xFFFFFFF followed by 8 bytes in big-endian order.  This
  // causes us to mis-read old-version code that stores exactly
  // 0xFFFFFFF, but I don't think that is likely to have happened for
  // these particular values.
  template <typename OUTPUT, typename IntType>
  static bool write_32_or_64(OUTPUT* fp, IntType value) {
    if ( value < 0xFFFFFFFFULL ) {        // fits in 4 bytes
      if ( !sparsehash_internal::write_bigendian_number(fp, value, 4) )
        return false;
    } else {
      if ( !sparsehash_internal::write_bigendian_number(fp, 0xFFFFFFFFUL, 4) )
        return false;
      if ( !sparsehash_internal::write_bigendian_number(fp, value, 8) )
        return false;
    }
    return true;
  }

  template <typename INPUT, typename IntType>
  static bool read_32_or_64(INPUT* fp, IntType *value) {  // reads into value
    MagicNumberType first4 = 0;   // a convenient 32-bit unsigned type
    if ( !sparsehash_internal::read_bigendian_number(fp, &first4, 4) )
      return false;
    if ( first4 < 0xFFFFFFFFULL ) {
      *value = first4;
    } else {
      if ( !sparsehash_internal::read_bigendian_number(fp, value, 8) )
        return false;
    }
    return true;
  }

 public:
  // read/write_metadata() and read_write/nopointer_data() are DEPRECATED.
  // Use serialize() and unserialize(), below, for new code.

  template <typename OUTPUT> bool write_metadata(OUTPUT *fp) const {
    if ( !write_32_or_64(fp, MAGIC_NUMBER) )  return false;
    if ( !write_32_or_64(fp, settings.table_size) )  return false;
    if ( !write_32_or_64(fp, settings.num_buckets) )  return false;

    GroupsConstIterator group;
    for ( group = groups.begin(); group != groups.end(); ++group )
      if ( group->write_metadata(fp) == false )  return false;
    return true;
  }

  // Reading destroys the old table contents!  Returns true if read ok.
  template <typename INPUT> bool read_metadata(INPUT *fp) {
    size_type magic_read = 0;
    if ( !read_32_or_64(fp, &magic_read) )  return false;
    if ( magic_read != MAGIC_NUMBER ) {
      clear();                        // just to be consistent
      return false;
    }

    if ( !read_32_or_64(fp, &settings.table_size) )  return false;
    if ( !read_32_or_64(fp, &settings.num_buckets) )  return false;

    resize(settings.table_size);                    // so the vector's sized ok
    GroupsIterator group;
    for ( group = groups.begin(); group != groups.end(); ++group )
      if ( group->read_metadata(fp) == false )  return false;
    return true;
  }

  // This code is identical to that for SparseGroup
  // If your keys and values are simple enough, we can write them
  // to disk for you.  "simple enough" means no pointers.
  // However, we don't try to normalize endianness
  bool write_nopointer_data(FILE *fp) const {
    for ( const_nonempty_iterator it = nonempty_begin();
          it != nonempty_end(); ++it ) {
      if ( !fwrite(&*it, sizeof(*it), 1, fp) )  return false;
    }
    return true;
  }

  // When reading, we have to override the potential const-ness of *it
  bool read_nopointer_data(FILE *fp) {
    for ( nonempty_iterator it = nonempty_begin();
          it != nonempty_end(); ++it ) {
      if ( !fread(reinterpret_cast<void*>(&(*it)), sizeof(*it), 1, fp) )
        return false;
    }
    return true;
  }

  // INPUT and OUTPUT must be either a FILE, *or* a C++ stream
  //    (istream, ostream, etc) *or* a class providing
  //    Read(void*, size_t) and Write(const void*, size_t)
  //    (respectively), which writes a buffer into a stream
  //    (which the INPUT/OUTPUT instance presumably owns).

  typedef sparsehash_internal::pod_serializer<value_type> NopointerSerializer;

  // ValueSerializer: a functor.  operator()(OUTPUT*, const value_type&)
  template <typename ValueSerializer, typename OUTPUT>
  bool serialize(ValueSerializer serializer, OUTPUT *fp) {
    if ( !write_metadata(fp) )
      return false;
    for ( const_nonempty_iterator it = nonempty_begin();
          it != nonempty_end(); ++it ) {
      if ( !serializer(fp, *it) )  return false;
    }
    return true;
  }

  // ValueSerializer: a functor.  operator()(INPUT*, value_type*)
  template <typename ValueSerializer, typename INPUT>
  bool unserialize(ValueSerializer serializer, INPUT *fp) {
    clear();
    if ( !read_metadata(fp) )
      return false;
    for ( nonempty_iterator it = nonempty_begin();
          it != nonempty_end(); ++it ) {
      if ( !serializer(fp, &*it) )  return false;
    }
    return true;
  }

  // Comparisons.  Note the comparisons are pretty arbitrary: we
  // compare values of the first index that isn't equal (using default
  // value for empty buckets).
  bool operator==(const sparsetable& x) const {
    return ( settings.table_size == x.settings.table_size &&
             settings.num_buckets == x.settings.num_buckets &&
             groups == x.groups );
  }

  bool operator<(const sparsetable& x) const {
    return std::lexicographical_compare(begin(), end(), x.begin(), x.end());
  }
  bool operator!=(const sparsetable& x) const { return !(*this == x); }
  bool operator<=(const sparsetable& x) const { return !(x < *this); }
  bool operator>(const sparsetable& x) const { return x < *this; }
  bool operator>=(const sparsetable& x) const { return !(*this < x); }


 private:
  // Package allocator with table_size and num_buckets to eliminate memory
  // needed for the zero-size allocator.
  // If new fields are added to this class, we should add them to
  // operator= and swap.
  class Settings : public allocator_type {
   public:
    typedef typename allocator_type::size_type size_type;

    Settings(const allocator_type& a, size_type sz = 0, size_type n = 0)
        : allocator_type(a), table_size(sz), num_buckets(n) { }

    Settings(const Settings& s)
        : allocator_type(s),
          table_size(s.table_size), num_buckets(s.num_buckets) { }

    size_type table_size;          // how many buckets they want
    size_type num_buckets;         // number of non-empty buckets
  };

  // The actual data
  group_vector_type groups;        // our list of groups
  Settings settings;               // allocator, table size, buckets
};

// We need a global swap as well
template <class T, u_int16_t GROUP_SIZE, class Alloc>
inline void swap(sparsetable<T,GROUP_SIZE,Alloc> &x,
                 sparsetable<T,GROUP_SIZE,Alloc> &y) {
  x.swap(y);
}

_END_GOOGLE_NAMESPACE_

#endif  // UTIL_GTL_SPARSETABLE_H_
