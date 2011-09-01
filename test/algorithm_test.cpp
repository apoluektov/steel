// Copyright (c) 2011 Alexander Poluektov (alexander.poluektov@gmail.com)
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/auto_unit_test.hpp>

#include <steel/algorithm.hpp>

#include <vector>
#include <algorithm>
#include <boost/assign.hpp>

using namespace std;
using namespace boost::assign;

namespace aux
{

template <class T>
struct always_false
{
    bool operator()(T const&) const { return false; }
};

template <class T>
struct always_true
{
    bool operator()(T const&) const { return true; }
};

template <class T>
struct first_n
{
    explicit first_n(size_t n) : n(n), c(0) { }
    bool operator()(T const&) { return ++c < n; }
    size_t const n;
    size_t c;
};

template <class F, class P, class T>
struct composer
{
    composer(F f, P p) : f(f), p(p) { }

    bool operator()(T& t)
    {
        f(t);
        return p(t);
    }

    F f;
    P p;
};

struct change_in_place
{
    void operator()(int& i)
    {
        i = -i;
    }
};


template <class T, class F, class P>
composer<F, P, T> compose(F f, P p) { return composer<F, P, T>(f, p); }

}

using namespace aux;

BOOST_AUTO_TEST_SUITE(for_each_while);

BOOST_AUTO_TEST_CASE(always_false_non_empty)
{
    vector<int> v;
    v += 1, 2, 3, 4, 5;

    vector<int> v2(v);
    v2[0] = -1;

    steel::for_each_while(v.begin(), v.end(),
                          compose<int>(change_in_place(), always_false<int>()));

    BOOST_CHECK(std::equal(v.begin(), v.end(), v2.begin()));
}

BOOST_AUTO_TEST_CASE(always_false_empty)
{
    vector<int> v;

    steel::for_each_while(v.begin(), v.end(),
                          compose<int>(change_in_place(), always_false<int>()));

    BOOST_CHECK(v.empty());
}

BOOST_AUTO_TEST_CASE(always_true_non_empty)
{
    vector<int> v;
    v += 1, 2, 3, 4, 5;

    vector<int> v2(v);
    v2[0] = -1;
    v2[1] = -2;
    v2[2] = -3;
    v2[3] = -4;
    v2[4] = -5;

    steel::for_each_while(v.begin(), v.end(),
                          compose<int>(change_in_place(), always_true<int>()));

    BOOST_CHECK(std::equal(v.begin(), v.end(), v2.begin()));
}

BOOST_AUTO_TEST_CASE(always_true_empty)
{
    vector<int> v;

    steel::for_each_while(v.begin(), v.end(),
                          compose<int>(change_in_place(), always_true<int>()));

    BOOST_CHECK(v.empty());
}

BOOST_AUTO_TEST_CASE(first_3)
{    
    vector<int> v;
    v += 1, 2, 3, 4, 5;

    vector<int> v2(v);
    v2[0] = -1;
    v2[1] = -2;
    v2[2] = -3;

    steel::for_each_while(v.begin(), v.end(),
                          compose<int>(change_in_place(), first_n<int>(3)));

    BOOST_CHECK(std::equal(v.begin(), v.end(), v2.begin()));
}

BOOST_AUTO_TEST_CASE(first_3_empty)
{    
    vector<int> v;

    steel::for_each_while(v.begin(), v.end(),
                          compose<int>(change_in_place(), first_n<int>(3)));

    BOOST_CHECK(v.empty());
}

BOOST_AUTO_TEST_SUITE_END();

namespace aux
{

struct tester
{
    explicit tester(int v) : v(v) { }
    int v;
};

bool compare(tester const& lhs, tester const& rhs)
{
    return lhs.v > rhs.v;
}

}

BOOST_AUTO_TEST_SUITE(min_element_bounded);

BOOST_AUTO_TEST_CASE(less_works)
{
    std::vector<int> v;
    v += 2, 3, 5, 1, 8, 0;

    {
    std::vector<int>::const_iterator it =
        steel::min_element_bounded(v.begin(), v.end(), 1);

    BOOST_CHECK(*it == 1);
    }

    {
    std::vector<int>::const_iterator it =
        steel::min_element_bounded(v.begin(), v.end(), 0);

    BOOST_CHECK(*it == 0);
    }

    {
    std::vector<int>::const_iterator it =
        steel::min_element_bounded(v.begin(), v.end(), -42);

    BOOST_CHECK(*it == 0);
    }
}

BOOST_AUTO_TEST_CASE(less_works_empty)
{
    std::vector<int> v;

    std::vector<int>::const_iterator it =
        steel::min_element_bounded(v.begin(), v.end(), 1);

    BOOST_CHECK(it == v.end());
}

BOOST_AUTO_TEST_CASE(comp_works)
{
    typedef aux::tester t;

    std::vector<t> v;
    v += t(2), t(3), t(5), t(1), t(8), t(0);

    {
    std::vector<t>::const_iterator it =
        steel::min_element_bounded(v.begin(), v.end(), aux::compare, t(5));

    BOOST_CHECK(it->v == 5);
    }

    {
    std::vector<t>::const_iterator it =
        steel::min_element_bounded(v.begin(), v.end(), aux::compare, t(8));

    BOOST_CHECK(it->v == 8);
    }


    {
    std::vector<t>::const_iterator it =
        steel::min_element_bounded(v.begin(), v.end(), aux::compare, t(11));

    BOOST_CHECK(it->v == 8);
    }
}

BOOST_AUTO_TEST_CASE(comp_works_empty)
{
    typedef aux::tester t;
    std::vector<t> v;

    std::vector<t>::const_iterator it =
        steel::min_element_bounded(v.begin(), v.end(), aux::compare, t(5));

    BOOST_CHECK(it == v.end());
}

BOOST_AUTO_TEST_SUITE_END();


BOOST_AUTO_TEST_SUITE(max_element_bounded);

BOOST_AUTO_TEST_CASE(less_works)
{
    std::vector<int> v;
    v += 2, 3, 5, 1, 8, 0;

    {
    std::vector<int>::const_iterator it =
        steel::max_element_bounded(v.begin(), v.end(), 5);

    BOOST_CHECK(*it == 5);
    }

    {
    std::vector<int>::const_iterator it =
        steel::max_element_bounded(v.begin(), v.end(), 8);

    BOOST_CHECK(*it == 8);
    }

    {
    std::vector<int>::const_iterator it =
        steel::max_element_bounded(v.begin(), v.end(), 42);

    BOOST_CHECK(*it == 8);
    }
}

BOOST_AUTO_TEST_CASE(less_works_empty)
{
    std::vector<int> v;

    std::vector<int>::const_iterator it =
        steel::max_element_bounded(v.begin(), v.end(), 8);

    BOOST_CHECK(it == v.end());
}

BOOST_AUTO_TEST_CASE(comp_works)
{
    typedef aux::tester t;

    std::vector<t> v;
    v += t(2), t(3), t(5), t(1), t(8), t(0);

    {
    std::vector<t>::const_iterator it =
        steel::max_element_bounded(v.begin(), v.end(), aux::compare, t(5));

    BOOST_CHECK(it->v == 2);
    }

    {
    std::vector<t>::const_iterator it =
        steel::max_element_bounded(v.begin(), v.end(), aux::compare, t(0));

    BOOST_CHECK(it->v == 0);
    }

    {
    std::vector<t>::const_iterator it =
        steel::max_element_bounded(v.begin(), v.end(), aux::compare, t(-42));

    BOOST_CHECK(it->v == 0);
    }
}

BOOST_AUTO_TEST_CASE(comp_works_empty)
{
    typedef aux::tester t;
    std::vector<t> v;

    std::vector<t>::const_iterator it =
        steel::max_element_bounded(v.begin(), v.end(), aux::compare, t(5));

    BOOST_CHECK(it == v.end());
}

BOOST_AUTO_TEST_SUITE_END();
