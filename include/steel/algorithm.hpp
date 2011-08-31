// Copyright (c) 2011 Alexander Poluektov (alexander.poluektov@gmail.com)
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef STEEL_ALGORITHM_HPP_INCLUDED_
#define STEEL_ALGORITHM_HPP_INCLUDED_

namespace steel
{

// applies function f to each element in range [first; last),
// but stops if f returns false
template <class InIt, class F>
inline
F for_each_while(InIt first, InIt last, F f)
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

} // namespace steel

#endif // STEEL_ALGORITHM_HPP_INCLUDED_
