#include "polynom.h"
#include <gtest.h>

TEST(Polynom, can_create_polynom)
{
    std::vector<std::string> names = {"x", "y", "z"};
    TSingleLinkedList<Monom<int>> monoms;
    monoms.Add(Monom<int>(5, std::vector<int>({1, 1, 1})));
    ASSERT_NO_THROW(Polynom<int> (monoms, names));
}

TEST(Polynom, can_sum_polynom)
{
    std::vector<std::string> names = {"x", "y", "z"};
    TSingleLinkedList<Monom<int>> monoms;
    monoms.Add(Monom<int>(5, std::vector<int>({1, 1, 1})));
    ASSERT_NO_THROW(Polynom<int> (monoms, names) + Polynom<int> (monoms, names));
}

TEST(Polynom, is_sum_polynom_correct)
{
    std::vector<std::string> names = {"x", "y", "z"};
    TSingleLinkedList<Monom<int>> monoms;
    monoms.Add(Monom<int>(5, std::vector<int>({1, 1, 1})));
    Polynom<int> pol = Polynom<int> (monoms, names) + Polynom<int> (monoms, names);
    
    TSingleLinkedList<Monom<int>> result;
    result.Add(Monom<int>(10, std::vector<int>({1, 1, 1})));

    EXPECT_EQ(Polynom<int>(result, names), pol);
}

TEST(Polynom, can_sub_polynom)
{
    std::vector<std::string> names = {"x", "y", "z"};
    TSingleLinkedList<Monom<int>> monoms;
    monoms.Add(Monom<int>(5, std::vector<int>({1, 1, 1})));
    ASSERT_NO_THROW(Polynom<int> (monoms, names) - Polynom<int> (monoms, names));
}

TEST(Polynom, is_sub_polynom_correct)
{
    std::vector<std::string> names = {"x", "y", "z"};
    TSingleLinkedList<Monom<int>> monoms;
    monoms.Add(Monom<int>(5, std::vector<int>({1, 1, 1})));
    Polynom<int> pol = Polynom<int> (monoms, names) - Polynom<int> (monoms, names);
    
    TSingleLinkedList<Monom<int>> result;
    result.Add(Monom<int>(0, std::vector<int>({1, 1, 1})));

    EXPECT_EQ(Polynom<int>(result, names), pol);
}

TEST(Polynom, is_mul_polynom_with_scalar_correct)
{
    std::vector<std::string> names = { "x", "y", "z" };
    TSingleLinkedList<Monom<int>> monoms;
    monoms.Add(Monom<int>(5, std::vector<int>({ 1, 1, 1 })));
    Polynom<int> pol = Polynom<int>(monoms, names) * 3;

    TSingleLinkedList<Monom<int>> result;
    result.Add(Monom<int>(15, std::vector<int>({ 1, 1, 1 })));

    EXPECT_EQ(Polynom<int>(result, names), pol);
}

TEST(Polynom, is_mul_polynom_correct)
{
    std::vector<std::string> names = { "x", "y", "z" };
    TSingleLinkedList<Monom<int>> monoms;
    monoms.Add(Monom<int>(5, std::vector<int>({ 1, 1, 1 })));
    Polynom<int> pol = Polynom<int>(monoms, names) * Polynom<int>(monoms, names);

    TSingleLinkedList<Monom<int>> result;
    result.Add(Monom<int>(25, std::vector<int>({ 2, 2, 2 })));

    EXPECT_EQ(Polynom<int>(result, names), pol);
}

TEST(Polynom, is_mul_polynom_and_scalar_correct)
{
    std::vector<std::string> names = { "x", "y", "z" };
    TSingleLinkedList<Monom<int>> monoms;
    monoms.Add(Monom<int>(5, std::vector<int>({ 1, 1, 1 })));
    Polynom<int> pol = Polynom<int>(monoms, names) * 5;

    TSingleLinkedList<Monom<int>> result;
    result.Add(Monom<int>(25, std::vector<int>({ 1, 1, 1 })));

    EXPECT_EQ(Polynom<int>(result, names), pol);
}

TEST(Polynom, is_div_polynom_and_scalar_correct)
{
    std::vector<std::string> names = { "x", "y", "z" };
    TSingleLinkedList<Monom<int>> monoms;
    monoms.Add(Monom<int>(5, std::vector<int>({ 1, 1, 1 })));
    Polynom<int> pol = Polynom<int>(monoms, names) / 5;

    TSingleLinkedList<Monom<int>> result;
    result.Add(Monom<int>(1, std::vector<int>({ 1, 1, 1 })));

    EXPECT_EQ(Polynom<int>(result, names), pol);
}