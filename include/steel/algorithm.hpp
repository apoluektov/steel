// Copyright (c) 2011 Alexander Poluektov (alexander.poluektov@gmail.com)
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef STEEL_ALGORITHM_HPP_INCLUDED_
#define STEEL_ALGORITHM_HPP_INCLUDED_

namespace steel
{

// Requires: f() returns value that is convertible to bool.
// Effects: Applies f to the result of dereferencing every iterator 
//    in the range [first, last), starting from first and proceeding
//    to iterator i such that f(*i) == false.
// Returns: f.
// Complexity: Applies f exactly last - first times.
template <class InputIterator, class F>
F for_each_while(InputIterator first, InputIterator last, F f);


// Returns: The first iterator i in the range [first, last) such that 
//    either !(v < *i) or for any iterator j in the range [first, last)
//    the following holds: !(*j < *i)
// Returns last if first == last.
// Complexity: Maximum 2*(last - first) applications of operator<.
template <class ForwardIterator, class T>
ForwardIterator
min_element_bounded(ForwardIterator first,
                    ForwardIterator last,
                    T const& v);


// Returns: The first iterator i in the range [first, last) such that 
//    either !comp(v < *i) or for any iterator j in the range [first, last)
//    the following holds: !comp(*j < *i)
// Returns last if first == last.
// Complexity: Maximum 2*(last - first) applications of comp.
template <class ForwardIterator, class Compare, class T>
ForwardIterator
min_element_bounded(ForwardIterator first,
                    ForwardIterator last,
                    Compare comp,
                    T const& v);


// Returns: The first iterator i in the range [first, last) such that 
//    either !(*i < v) or for any iterator j in the range [first, last)
//    the following holds: !(*i < *j)
// Returns last if first == last.
// Complexity: Maximum 2*(last - first) applications of operator<.
template <class ForwardIterator, class T>
ForwardIterator
max_element_bounded(ForwardIterator first,
                    ForwardIterator last,
                    T const& v);


// Returns: The first iterator i in the range [first, last) such that 
//    either !comp(*i, v) or for any iterator j in the range [first, last)
//    the following holds: !comp(*i, *j)
// Returns last if first == last.
// Complexity: Maximum 2*(last - first) applications of comp.
template <class ForwardIterator, class Compare, class T>
ForwardIterator
max_element_bounded(ForwardIterator first,
                    ForwardIterator last,
                    Compare comp,
                    T const& v);


// Implementation

template <class InputIterator, class F>
inline
F for_each_while(InputIterator first, InputIterator last, F f)
{
    for ( ; first != last; ++first)
        if (!f(*first))
            break;

    return f;
}

template <class ForwardIterator, class T>
inline
ForwardIterator
min_element_bounded(ForwardIterator first,
                    ForwardIterator last,
                    T const& v)
{
    if (first == last)
        return last;

    ForwardIterator lowest = first;
    if (!(v < *lowest))
        return lowest;

    while (++first != last) {
        if (*first < *lowest) { 
            lowest = first;
            if (!(v < *lowest))
                return lowest;
        }
    }
    return lowest;
}

template <class ForwardIterator, class Compare, class T>
inline
ForwardIterator
min_element_bounded(ForwardIterator first,
                    ForwardIterator last,
                    Compare comp,
                    T const& v)
{
    if (first == last)
        return last;

    ForwardIterator lowest = first;
    if (!comp(v, *lowest))
        return lowest;

    while (++first != last) {
        if (comp(*first, *lowest)) { 
            lowest = first;
            if (!comp(v, *lowest))
                return lowest;
        }
    }
    return lowest;
}

template <class ForwardIterator, class T>
inline
ForwardIterator
max_element_bounded(ForwardIterator first,
                    ForwardIterator last,
                    T const& v)
{
    if (first == last)
        return last;

    ForwardIterator largest = first;
    if (!(*largest < v))
        return largest;

    while (++first != last) {
        if (*largest < *first) { 
            largest = first;
            if (!(*largest < v))
                return largest;
        }
    }
    return largest;
}

template <class ForwardIterator, class Compare, class T>
inline
ForwardIterator
max_element_bounded(ForwardIterator first,
                    ForwardIterator last,
                    Compare comp,
                    T const& v)
{
    if (first == last)
        return last;

    ForwardIterator largest = first;
    if (!comp(*largest, v))
        return largest;

    while (++first != last) {
        if (comp(*largest, *first)) { 
            largest = first;
            if (!comp(*largest, v))
                return largest;
        }
    }
    return largest;
}

} // namespace steel

#endif // STEEL_ALGORITHM_HPP_INCLUDED_
