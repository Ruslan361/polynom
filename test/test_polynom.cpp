#include "polynom.h"
#include <gtest.h>

TEST(Polynom, can_create_polynom)
{
    std::vector<std::string> names = {"x", "y", "z"};
    TSingleLinkedList<Monom<int>> monoms;
    monoms.Add(Monom<int>(5, std::vector<int>({1, 1, 1})));
    Polynom<int> (monoms, names);
    ASSERT_NO_THROW(Polynom<int> (monoms, names));
}