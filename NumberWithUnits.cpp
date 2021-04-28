#include "NumberWithUnits.hpp"
#include <fstream>
#include <stdexcept>
#include <cmath>
#include <map>
using namespace std;
using namespace ariel;
#define SIGN_FLIP -1

namespace ariel
{
    const double EPSILONE = 0.001;
    static map<string, map<string, double>> coversion_map;

    NumberWithUnits::NumberWithUnits(double value, const string measure)
    {
        if (value == 0)
        {
            throw "invalid number";
        }
        if (coversion_map.find(measure) == coversion_map.end())
        {
            throw "invalid unit measure";
        }
        this->numeric_value = value;
        this->measure_type = measure;
    }

    double NumberWithUnits::conversion(string first_unit, string second_unit, double value)
    {
        {
            if (first_unit == second_unit)
            {
                return value;
            }
            if (coversion_map[second_unit].find(first_unit) == coversion_map[second_unit].end())
            {
                throw "The numbers need to be of the same type";
            }
            return (value * coversion_map[second_unit][first_unit]);
        }
    }

    void NumberWithUnits::multicasting(const string &string1, const string &string2)
    {
        for (auto &p : coversion_map[string1])
        {
            double cast = coversion_map[string2][string1] * p.second;
            coversion_map[string2][p.first] = cast;
            coversion_map[p.first][string2] = 1 / cast;
        }
    }

    // TODO write Output function & read units
    void NumberWithUnits::read_units(ifstream &instructions)
    {
        string first_unit, second_unit, eq_catcher;
        double num1 = 0, num2 = 0;
        while (!instructions.eof())
        {
            instructions >> num1 >> first_unit >> eq_catcher >> num2 >> second_unit;
            coversion_map[first_unit][second_unit] = num2;
            coversion_map[second_unit][first_unit] = num1 / num2;
            multicasting(first_unit, second_unit);
            multicasting(second_unit, first_unit);
        }
    }

    NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits &a) const
    {
        if ((this->measure_type.compare(a.measure_type) == 0))
        {
            NumberWithUnits ans(this->numeric_value + a.numeric_value, this->measure_type);
            return ans;
        }
        else
        {
            throw __throw_runtime_error;
        }
    }

    NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits &a) const
    {
        if ((this->measure_type.compare(a.measure_type) == 0))
        {
            NumberWithUnits ans(this->numeric_value - a.numeric_value, this->measure_type);
            return ans;
        }
        else
        {
            throw __throw_runtime_error;
        }
    }

    NumberWithUnits operator*(const double a, const NumberWithUnits &b)
    {
        if (a != 0)
        {
            NumberWithUnits ans(b.numeric_value * a, b.measure_type);
            return ans;
        }
        else
        {
            throw "don't multiply by 0!";
        }
    }

    NumberWithUnits NumberWithUnits::operator*(double b)
    {
        if (b != 0)
        {
            NumberWithUnits ans(this->numeric_value * b, this->measure_type);
            return ans;
        }
        else
        {
            throw "don't multiply by 0!";
        }
    }

    NumberWithUnits &NumberWithUnits::operator+=(const NumberWithUnits &other)
    {
        if ((this->measure_type.compare(other.measure_type) == 0))
        {
            this->numeric_value = this->numeric_value * other.numeric_value;
            return *this;
        }
        else
        {
            throw __throw_runtime_error;
        }
        return *this;
    }

    NumberWithUnits &NumberWithUnits::operator-=(const NumberWithUnits &other)
    {
        if ((this->measure_type.compare(other.measure_type) == 0))
        {
            this->numeric_value = this->numeric_value - other.numeric_value;
            return *this;
        }
        else
        {
            throw __throw_runtime_error;
        }
        return *this;
    }

    NumberWithUnits &NumberWithUnits::operator*=(const NumberWithUnits &other)
    {
        if ((this->measure_type.compare(other.measure_type) == 0))
        {
            this->numeric_value = this->numeric_value * other.numeric_value;
            return *this;
        }
        else
        {
            throw __throw_runtime_error;
        }
    }

    NumberWithUnits &NumberWithUnits::operator+()
    {
        return *this;
    }

    NumberWithUnits &NumberWithUnits::operator-()
    {
        this->numeric_value = this->numeric_value * SIGN_FLIP;
        return *this;
    }

    bool NumberWithUnits::operator<(const NumberWithUnits &other) const
    {
        if (this->numeric_value < other.numeric_value && (this->measure_type.compare(other.measure_type) == 0))
        {
            return true;
        }
        return false;
    }

    bool NumberWithUnits::operator<=(const NumberWithUnits &other) const
    {
        if (this->numeric_value <= other.numeric_value && (this->measure_type.compare(other.measure_type) == 0))
        {
            return true;
        }
        return false;
    }
    bool NumberWithUnits::operator>(const NumberWithUnits &other) const
    {
        if (this->numeric_value > other.numeric_value && (this->measure_type.compare(other.measure_type) == 0))
        {
            return true;
        }
        return false;
    }
    bool NumberWithUnits::operator>=(const NumberWithUnits &other) const
    {
        if (this->numeric_value >= other.numeric_value && (this->measure_type.compare(other.measure_type) == 0))
        {
            return true;
        }
        return false;
    }
    bool NumberWithUnits::operator==(const NumberWithUnits &other) const
    {
        if (this->measure_type.compare(other.measure_type) == 0 && abs(this->numeric_value - other.numeric_value) < EPSILONE)
        {
            return true;
        }
        return false;
    }
    bool NumberWithUnits::operator!=(const NumberWithUnits &other) const
    {
        if (!(this->measure_type.compare(other.measure_type) == 0 && this->numeric_value == other.numeric_value))
        {
            return true;
        }
        return false;
    }

    NumberWithUnits &NumberWithUnits::operator++()
    {
        this->numeric_value = this->numeric_value + 1;
        return *this;
    }
    NumberWithUnits &NumberWithUnits::operator--()
    {
        this->numeric_value = this->numeric_value - 1;
        return *this;
    }
    NumberWithUnits &NumberWithUnits::operator++(int)
    {
        this->numeric_value = this->numeric_value + 1;
        return *this;
    }
    NumberWithUnits &NumberWithUnits::operator--(int)
    {
        this->numeric_value = this->numeric_value - 1;
        return *this;
    }

    ostream &operator<<(ostream &output, const NumberWithUnits &a)
    {
        return (output << a.numeric_value << '[' << a.measure_type << ']');
    }
    istream &operator>>(istream &input, NumberWithUnits &a)
    {
        double number_input = 0;
        string unit_input;
        char c = '\0';
        input >> number_input >> c;
        while (c != ']')
        {
            if (c != '[')
            {
                unit_input.insert(unit_input.end(), c);
            }
            input >> c;
        }
        if (coversion_map.count(unit_input) > 0)
        {
            a.numeric_value = number_input;
            a.measure_type = unit_input;
        }
        else
        {
            throw "wrong measure unit!";
        }
        return input;
    }

};