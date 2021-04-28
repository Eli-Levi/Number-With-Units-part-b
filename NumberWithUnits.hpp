#pragma once
#include <iostream>
#include <string>
namespace ariel
{
    class NumberWithUnits
    {
        double numeric_value;
        std::string measure_type;

        static double conversion(std::string first_unit, std::string second_unit, double value);
        static void multicasting(const std::string &str1, const std::string &str2);


    public:
        NumberWithUnits(double number, const std::string measure);
        static void read_units(std::ifstream& instructions);

        NumberWithUnits operator+(const NumberWithUnits& a) const;
        NumberWithUnits operator-(const NumberWithUnits& a) const;
        friend NumberWithUnits operator*(const double a, const NumberWithUnits& b);
        NumberWithUnits operator*(double b);
        NumberWithUnits &operator+=(const NumberWithUnits& other);
        NumberWithUnits &operator-=(const NumberWithUnits& other);
        NumberWithUnits &operator*=(const NumberWithUnits& other);
        NumberWithUnits &operator+(); // unary +
        NumberWithUnits &operator-(); // unary -

        bool operator<(const NumberWithUnits& other) const;
        bool operator<=(const NumberWithUnits& other) const;
        bool operator>(const NumberWithUnits& other) const;
        bool operator>=(const NumberWithUnits& other) const;
        bool operator==(const NumberWithUnits& other) const;
        bool operator!=(const NumberWithUnits& other) const;

        NumberWithUnits &operator++();    // i.e ++i
        NumberWithUnits &operator--();    // i.e --i
        NumberWithUnits &operator++(int); // i.e i++
        NumberWithUnits &operator--(int); // i.e i--

        friend std::ostream &operator<<(std::ostream &output, const NumberWithUnits& a);
        friend std::istream &operator>>(std::istream &input, NumberWithUnits& a);
    };
};