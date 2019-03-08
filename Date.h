

#ifndef AMA_DATE_H
#define AMA_DATE_H
#include <iostream>

//error states
#define NO_ERROR 0
#define CIN_FAILED 1
#define YEAR_ERROR 2
#define MON_ERROR 3
#define DAY_ERROR 4

namespace AMA {
	//pre-defined constants.
	const int min_year = 2000;
	const int max_year = 2030;

	class Date {
		int year;
		int month;
		int day;
		int error;
		int comparator;

		//private member fuctions
		int mdays(int month, int year)const;
		void errCode(int errorCode);
		// int comparator() const;
		bool validate_year(int yr);
		bool validate_month(int mn);
		bool validate_day(int dy);
	public:
		//constrctors
		Date();

		Date(int year, int month, int day);

		//operator overloads
		bool operator == (const Date& rhs) const;
		bool operator!=(const Date& rhs) const;
		bool operator <(const Date& rhs) const;
		bool operator>(const Date& rhs) const;
		bool operator <= (const Date& rhs) const;
		bool operator >= (const Date& rhs) const;

		//Queries and Modifiers
		int errCode() const;
		bool bad() const;


		std::istream& read(std::istream& istr);
		std::ostream& write(std::ostream& ostr) const;
	};
	//opeartor << and >> overloads
	std::ostream& operator<<(std::ostream& os, const Date& _date);
	std::istream& operator>>(std::istream& is, Date& _date);

}
#endif
