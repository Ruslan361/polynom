#pragma once
#include "monom.h"
#include "tsinglelinkedlist.h"
#include <string>
#include <algorithm>
#include <map>


bool AreNamesEqual(const std::vector<std::string>& names1, const std::vector<std::string>& names2)
{
    if (names1.size() != names2.size())
        return false;

    size_t size = names1.size();
    for (size_t i = 0; i < size; i++)
    {
        if (names1[i] != names2[i])
            return false;
    }
    return true;
}


template <typename T>
class Polynom
{

private:
    TSingleLinkedList<Monom<T>> list_monom;
    std::vector<std::string> names_of_variables;
public:
    Polynom(const TSingleLinkedList<Monom<T>>& monoms, const std::vector<std::string>& variables) : list_monom(monoms)
    {   
        names_of_variables = variables;
        std::sort(names_of_variables.begin(), names_of_variables.end());
    }
    Polynom(const std::vector<std::string> variables) : names_of_variables(variables), list_monom() {}
    std::vector<std::string> GetNamesOfVariables() const
    {
        return names_of_variables;
    }


    bool operator==(const Polynom& polynom) const
    {
        return (names_of_variables == polynom.names_of_variables) && (list_monom == polynom.list_monom);
    }

    friend std::ostream& operator<< (std::ostream& stream, const Polynom& polynom)
    {
        for (Iterator<Monom<T>> it = polynom.list_monom.begin(); it != polynom.list_monom.end(); it++)
        {
            auto degrees = (*it).GetDegrees();
            if ((*it).coeff >= 0)
                stream << "+" << (*it).coeff;
            else
                stream << (*it).coeff;
            for (size_t i = 0; i < degrees.size(); i++)
            {
                stream << polynom.names_of_variables[i] << '^' << degrees[i];
            }
        }
        return stream;
    }

    Polynom operator+(const Polynom<T> polynom) const;
    Polynom operator-(const Polynom<T> polynom) const;
    int MaxDegree(size_t num)
    {
        int max_power = INT_MIN;
        for (Iterator<Monom<T>> it = list_monom.begin(); it != list_monom.end(); it++)
        {
            int degree = (*it).GetDegree(num)
            if (degree > max_power)
            {
                max_power = degree;
            }
        }
        return max_power;
    }
    int MinDegree(size_t num)
    {
        int min_power = INT_MAX;
        for (Iterator<Monom<T>> it = list_monom.begin(); it != list_monom.end(); it++)
        {
            int degree = (*it).GetDegree(num)
            if (degree < min_power)
            {
                min_power = degree;
            }
        }
        return min_power;
    }
    Polynom BringingSimiliar()
    {
        size_t number_of_variables = names_of_variables.size();
        std::vector<int> max_degrees(number_of_variables);
        std::vector<int> min_degrees(number_of_variables);
        std::vector<int> size_degrees(number_of_variables);
        int length = 0;
        for (size_t i = 0; i < number_of_variables; i++)
        {
            max_degrees[i] = MaxDegree(i);
            min_degrees[i] = MinDegree(i);
            size_degrees[i] = max_degrees - min_degrees + 1;
            length += size_degrees[i];
        }
        
        std::vector<int> current_degrees(length);
        for (Iterator<Monom<T>> it = list_monom.begin(); it != list_monom.end(); it++)
        {
            Monom<T> monom = *it;
            std::vector<int> degr = monom.GetDegrees();
            int addres = 0;
            for (size_t i = 0; i < number_of_variables; i++)
            {
                addres += degr[i] * size_degrees[i];
            }
        }
    }
};

template <typename T>
Polynom<T> Polynom<T>::operator-(const Polynom<T> polynom) const
{
    if (!AreNamesEqual(names_of_variables, polynom.names_of_variables))
        throw std::invalid_argument("names of variables are different");

    TSingleLinkedList<Monom<T>> new_list_monom;

    TSingleLinkedList<Monom<T>> polynom_copy(polynom.list_monom);

    for (Iterator<Monom<T>> it = list_monom.begin(); it != list_monom.end(); it++)
    {
        bool flag = false;
        for (Iterator<Monom<T>> it2 = polynom_copy.begin(); it2 != polynom_copy.end(); )
        {
            if ((*it).IsEqualDegrees(*it2))
            {
                new_list_monom.Add(*it - *it2);
                polynom_copy.Remove(it2);
                flag = true;
                break;
            }
            else
            {
                it2++;
            }
        }
        if (!flag)
        {
            new_list_monom.Add(*it);
        }
    }
    for (Iterator<Monom<T>> it2 = polynom_copy.begin(); it2 != polynom_copy.end(); it2++)
    {
        new_list_monom.Add(*it2 * T(-1));
    }
    return Polynom(new_list_monom, names_of_variables);
}

template <typename T>
Polynom<T> Polynom<T>::operator+(const Polynom<T> polynom) const
{
    if (!AreNamesEqual(names_of_variables, polynom.names_of_variables))
        throw std::invalid_argument("names of variables are different");

    TSingleLinkedList<Monom<T>> new_list_monom;

    TSingleLinkedList<Monom<T>> polynom_copy(polynom.list_monom);

    for (Iterator<Monom<T>> it = list_monom.begin(); it != list_monom.end(); it++)
    {
        bool flag = false;
        for (Iterator<Monom<T>> it2 = polynom_copy.begin(); it2 != polynom_copy.end(); )
        {
            if ((*it).IsEqualDegrees(*it2))
            {
                new_list_monom.Add(*it + *it2);
                polynom_copy.Remove(it2);
                flag = true;
                break;
            }
            else
            {
                it2++;
            }
        }
        if (!flag)
        {
            new_list_monom.Add(*it);
        }
    }
    for (Iterator<Monom<T>> it2 = polynom_copy.begin(); it2 != polynom_copy.end(); it2++)
    {
        new_list_monom.Add(*it2);
    }
    return Polynom(new_list_monom, names_of_variables);
}