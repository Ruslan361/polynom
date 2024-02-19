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
    void TaskSum(const Polynom<T> polynom, TSingleLinkedList<Monom<T>>& new_list_monom, const Monom<T>& monom) const
    {
        Iterator<Monom<T>> it_polynom;
        for (it_polynom = polynom.list_monom.begin(); it_polynom != polynom.list_monom.end(); it_polynom++)
        {
            if ((monom).IsEqualDegrees(*it_polynom))
            {
                //new_list_monom.Add(Monom<T>((*it).coeff + (*it_polynom).coeff, (*it).GetDegrees()));
                new_list_monom.Add(monom + *it_polynom);
                break;
            }
        }
        /*
        if (it_polynom == polynom.list_monom.end())
        {
            if ((monom).IsEqualDegrees(*it_polynom))
            {
                //new_list_monom.Add(Monom<T>((*it).coeff + (*it_polynom).coeff, (*it).GetDegrees()));
                new_list_monom.Add(monom + *it_polynom);
            }
        }
        else
        {
            new_list_monom.Add(monom);
        }
        */
    }

    void TaskSub(const Polynom<T> polynom, TSingleLinkedList<Monom<T>>& new_list_monom, const Monom<T>& monom) const
    {
        Iterator<Monom<T>> it_polynom;
        for (it_polynom = polynom.list_monom.begin(); it_polynom != polynom.list_monom.end(); it_polynom++)
        {
            if ((monom).IsEqualDegrees(*it_polynom))
            {
                //new_list_monom.Add(Monom<T>((*it).coeff + (*it_polynom).coeff, (*it).GetDegrees()));
                new_list_monom.Add(monom - *it_polynom);
                break;
            }
        }
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

    Polynom operator+(const Polynom<T> polynom) const
    {
        if (!AreNamesEqual(names_of_variables, polynom.names_of_variables))
            throw std::invalid_argument("names of variables are different");
        
        TSingleLinkedList<Monom<T>> new_list_monom;

        for (Iterator<Monom<T>> it = list_monom.begin(); it != list_monom.end(); it++)
        {
            TaskSum(polynom, new_list_monom, *it);
        }
        //Task(polynom, new_list_monom, *(list_monom.end()));
        return Polynom(new_list_monom, names_of_variables);
    }

    Polynom operator-(const Polynom<T> polynom) const
    {
        if (!AreNamesEqual(names_of_variables, polynom.names_of_variables))
            throw std::invalid_argument("names of variables are different");
        
        TSingleLinkedList<Monom<T>> new_list_monom;

        for (Iterator<Monom<T>> it = list_monom.begin(); it != list_monom.end(); it++)
        {
            TaskSub(polynom, new_list_monom, *it);
        }
        //Task(polynom, new_list_monom, *(list_monom.end()));
        return Polynom(new_list_monom, names_of_variables);
    }
};

