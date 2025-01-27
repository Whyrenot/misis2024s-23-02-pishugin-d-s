//#ifndef RATIONAL_HPP
//#define RATIONAL_HPP
//
//#include <iostream>
//#include <string>
//#include <cmath>
//
//class Rational {
//public:
//	Rational() {};
//	Rational(int64_t numerator, int64_t denominator);
//	explicit Rational(const int64_t numerator);
//	~Rational() = default;
//
//	Rational& operator=(const Rational& rhs) = default;
//
//	[[nodiscard]] bool operator==(const Rational& rhs) { return num_ * rhs.den_ == rhs.num_ * den_; }
//	[[nodiscard]] bool operator!=(const Rational& rhs) { return !(operator==(rhs)); }
//
//	[[nodiscard]] bool operator>(const Rational& rhs) { return num_ * rhs.den_ > rhs.num_ * den_; }
//	[[nodiscard]] bool operator<(const Rational& rhs) { return num_ * rhs.den_ < rhs.num_ * den_; }
//	[[nodiscard]] bool operator>=(const Rational& rhs) { return num_ * rhs.den_ >= rhs.num_ * den_; }
//	[[nodiscard]] bool operator<=(const Rational& rhs) { return num_ * rhs.den_ <= rhs.num_ * den_; }
//
//	Rational& operator+=(const Rational& rhs);
//	Rational& operator-=(const Rational& rhs);
//	Rational& operator*=(const Rational& rhs);
//	Rational& operator/=(const Rational& rhs);
//
//	int64_t numerator() { return num_; }
//	int64_t denominator() { return den_; }
//
//	std::ostream& writeTo(std::ostream& ostrm) const;
//	std::istream& readFrom(std::istream& istrm);
//
//	static const char separator{ '/' };
//
//private:
//	int64_t num_ = 0;
//	int64_t den_ = 1;
//
//	void check();
//	void reducing_fractions();
//};
//
//
//Rational operator+(Rational& lhs, Rational& rhs);
//Rational operator-(Rational& lhs, Rational& rhs);
//Rational operator*(Rational& lhs, Rational& rhs);
//Rational operator/(Rational& lhs, Rational& rhs);
//
//
//inline std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs)
//{
//	return rhs.writeTo(ostrm);
//}
//
//inline std::istream& operator>>(std::istream& istrm, Rational& rhs)
//{
//	return rhs.readFrom(istrm);
//}
//
//#endif

#pragma once
#ifndef RATIONAL_HPP
#define RATIONAL_HPP

#include <sstream>
#include <iostream>
#include <cmath>
#include <cstdint>
#include <algorithm>
#include <iosfwd>
#include <stdexcept>
#include <string>

class Rational {
public:
    [[nodiscard]] Rational() = default;
    [[nodiscard]] Rational(const Rational&) = default;
    [[nodiscard]] explicit Rational(const std::int64_t num) : Rational(num, 1) {}
    [[nodiscard]] Rational(const std::int64_t num, const std::int64_t den);

    ~Rational() = default;

    [[nodiscard]] std::int64_t num() const { return num_; }
    [[nodiscard]] std::int64_t den() const { return den_; }

    [[nodiscard]] Rational& operator=(const Rational& r) = default;
    Rational& operator*=(const Rational& r) noexcept;
    Rational& operator*=(const std::int64_t d) noexcept { return operator*=(Rational(d)); }
    Rational& operator+=(const Rational& r) noexcept;
    Rational& operator+=(const std::int64_t d) noexcept { return operator+=(Rational(d)); }
    Rational& operator-=(const Rational& r) noexcept;
    Rational& operator-=(const std::int64_t d) noexcept { return operator-=(Rational(d)); }
    Rational& operator/=(const Rational& r);
    Rational& operator/=(const std::int64_t d) { return operator/=(Rational(d)); }
    Rational pow(const std::int64_t n);
    Rational abs() noexcept;
    Rational operator-() noexcept;

    Rational& round() noexcept;
    std::int64_t evkl(const Rational& r) noexcept { return evkl(r.num_, r.den_); }
    std::int64_t evkl(const std::int64_t c1, const std::int64_t c2) noexcept;

    [[nodiscard]] std::ostream& writeTo(std::ostream& ostrm) const;
    [[nodiscard]] std::istream& readFrom(std::istream& isdtrm);

    static const char sl{ '/' };

private:
    std::int64_t num_ = 0;
    std::int64_t den_ = 1;
};

[[nodiscard]] Rational operator+(const Rational& r1, const Rational& r2) noexcept;
[[nodiscard]] Rational operator+(const Rational& r1, const std::int64_t c) noexcept;
[[nodiscard]] Rational operator+(const std::int64_t c, const Rational& r2) noexcept;
[[nodiscard]] Rational operator-(const Rational& r1, const Rational& r2) noexcept;
[[nodiscard]] Rational operator-(const Rational& r1, const std::int64_t c) noexcept;
[[nodiscard]] Rational operator-(const std::int64_t c, const Rational& r2) noexcept;
[[nodiscard]] Rational operator*(const Rational& r1, const Rational& r2) noexcept;
[[nodiscard]] Rational operator*(const Rational& r1, const std::int64_t c) noexcept;
[[nodiscard]] Rational operator*(const std::int64_t c, const Rational& r2) noexcept;
[[nodiscard]] Rational operator/(const Rational& r1, const Rational& r2);
[[nodiscard]] Rational operator/(const Rational& r1, const std::int64_t c);
[[nodiscard]] Rational operator/(const std::int64_t c, const Rational& r2);
[[nodiscard]] bool operator==(const Rational& r1, const Rational& r2) noexcept;
[[nodiscard]] bool operator==(const std::int64_t c, const Rational& r2) noexcept;
[[nodiscard]] bool operator==(const Rational& r1, const std::int64_t c) noexcept;
[[nodiscard]] bool operator!=(const Rational& r1, const Rational& r2) noexcept;
[[nodiscard]] bool operator!=(const std::int64_t c, const Rational& r2) noexcept;
[[nodiscard]] bool operator!=(const Rational& r1, const std::int64_t c) noexcept;
[[nodiscard]] bool operator>(const Rational& r1, const Rational& r2) noexcept;
[[nodiscard]] bool operator>(const std::int64_t c, const Rational& r2) noexcept;
[[nodiscard]] bool operator>(const Rational& r1, const std::int64_t c) noexcept;
[[nodiscard]] bool operator<(const Rational& r1, const Rational& r2) noexcept;
[[nodiscard]] bool operator<(const std::int64_t c, const Rational& r2) noexcept;
[[nodiscard]] bool operator<(const Rational& r1, const std::int64_t c) noexcept;
[[nodiscard]] bool operator>=(const Rational& r1, const Rational& r2) noexcept;
[[nodiscard]] bool operator>=(const std::int64_t c, const Rational& r2) noexcept;
[[nodiscard]] bool operator>=(const Rational& r1, const std::int64_t c) noexcept;
[[nodiscard]] bool operator<=(const Rational& r1, const Rational& r2) noexcept;
[[nodiscard]] bool operator<=(const std::int64_t c, const Rational& r2) noexcept;
[[nodiscard]] bool operator<=(const Rational& r1, const std::int64_t c) noexcept;

inline std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs)
{
    return rhs.writeTo(ostrm);
}

inline std::istream& operator>>(std::istream& istrm, Rational& rhs)
{
    return rhs.readFrom(istrm);
}
#endif