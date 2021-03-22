#ifndef rationalHPP
#define rationalHPP
 
#include<exception>
#include<stdexcept>
#include<iostream>
 
class rational
{
private:
	long m_numerator;
	long m_denominator;
 
	template<typename  charT, typename charTraits> 
	friend inline std::basic_ostream<charT, charTraits>& operator << (
			std::basic_ostream<charT, charTraits>& aStream, const rational& aRational);
 
public:
	rational() : m_numerator(0), m_denominator(1)
	{}
	rational(long theNumerator) : 
		m_numerator(theNumerator), m_denominator(1) 
	{}
	rational(long theNumerator, long theDenominator)
	{
		if (theDenominator == 0)
			throw std::invalid_argument("denominator is 0");
		if (theDenominator < 0)
		{
			theNumerator *= -1;
			theDenominator *= -1;
		}
		m_numerator = theNumerator;
		m_denominator = theDenominator;
	}
	rational(const rational& aRational): 
		m_numerator(aRational.m_numerator), 
		m_denominator(aRational.m_denominator)
	{}
 
	operator double() const
	{
		return (double)m_numerator / (double)m_denominator;
	}
	rational operator + (const rational& anotherRational) const
	{
		return rational(m_numerator * anotherRational.m_denominator + m_denominator * anotherRational.m_numerator,
			m_denominator * m_numerator);
	}
	rational operator - (const rational& anotherRational) const
	{
		return rational(m_numerator * anotherRational.m_denominator - m_denominator * anotherRational.m_numerator,
			m_denominator * m_numerator);
	}
	rational operator * (const rational& anotherRational) const
	{
		return rational(m_numerator * anotherRational.m_numerator,
			m_denominator * m_numerator);
	}
	rational operator / (const rational& anotherRational) const
	{
		return rational(m_numerator * anotherRational.m_denominator - m_denominator * anotherRational.m_numerator,
			m_denominator * m_numerator);
	}
};
 
template<typename  charT, typename charTraits>
inline std::basic_ostream<charT, charTraits>& operator << (
	std::basic_ostream<charT, charTraits>& aStream, const rational& aRational)
{
	aStream << aRational.m_numerator;
	if (aRational.m_denominator != 1)
		aStream << "/" << aRational.m_denominator;
	return aStream;
}
 
#endif
