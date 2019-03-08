

#include<iostream>
#include "Date.h"

using namespace std;
namespace AMA {

	// number of days in month mon_ and year year_
	int Date::mdays(int mon, int year)const {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int month = mon >= 1 && mon <= 12 ? mon : 13;
		month--;
		return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}
	//Default Constructor
	//nitializes the object to a safe empty state and sets the error state to NO_ERROR
	Date::Date() {
		year = 0;
		month = 0;
		day = 0;
		errCode(NO_ERROR);
		comparator = 0;
	}
	//sets the error state variable to one of the values defined in macros.
	void Date::errCode(int errorCode) {
		error = errorCode;
	}

	//validate year/month/day
	bool Date::validate_year(int yr) {

		if (yr < min_year || yr > max_year) {
			error = YEAR_ERROR;
			return false;
		}
		else {
			return true;
		}
	}
	bool Date::validate_month(int mn) {
		if (mn < 1 || mn > 12) {
			error = MON_ERROR;
			return false;
		}
		else {
			return true;
		}

	}
	//validating day
	bool Date::validate_day(int dy) {
		//cout << "validate_day month , year: " << month << "," << year << endl;
		//cout << "validate_day before if: " << dy <<"<=" <<mdays(month, year) << endl;
		if (dy < 1 || dy > mdays(month, year)) { //calling the mday(int, int)
			error = DAY_ERROR;
			//cout << "validate_day into the if:" << error << endl;
			return false;
		}
		else {
			return true;
		}
	}

	//parameterized constructor// 3 para.
	Date::Date(int year_, int month_, int day_) {
		if (validate_year(year_)) {
			year = year_;
		}
		else {
			errCode(YEAR_ERROR);
		}
		if (validate_month(month_)) {
			month = month_;
		}
		else {
			errCode(MON_ERROR);
		}

		if (validate_day(day_)) {
			day = day_;
		}
		else {
			errCode(DAY_ERROR);
		}

		if (validate_year(year_) && validate_month(month_) && validate_day(day_)) {
			comparator = year * 372 + month * 13 + day;
		}
		else {
			*this = Date();
		}

	}
	
	//reads the date from the console in the following format: YYYY?MM?DD
	std::istream& Date::read(std::istream& istr) {
		Date temp;

		istr >> temp.year;
		if (istr.fail()) {
			errCode(CIN_FAILED);
		}
		else {
			istr.ignore();
			istr >> temp.month;
			if (istr.fail()) {
				errCode(CIN_FAILED);
				return istr;
			}
			else {
				istr.ignore();
				istr >> temp.day;
				if (!istr.fail()) {
					if (!validate_year(temp.year)) {
						temp.errCode(YEAR_ERROR);
					}
					if (!validate_month(temp.month)) {
						temp.errCode(MON_ERROR);
					}
					if (temp.error != MON_ERROR && temp.error != YEAR_ERROR) {


						if (!temp.validate_day(temp.day)) {
							//cout << "mdays: " << mdays(temp.month, temp.year) << endl;
							//int i = (temp.day < 1 || temp.day > mdays(temp.month, temp.year)) ? 1 : 0;
							//cout << "read, validate day: " << i << "-" << temp.day;
							temp.errCode(DAY_ERROR);
							errCode(DAY_ERROR);
						}
					}
				}
				else {
					temp.errCode(CIN_FAILED);
				}

				if (temp.error == NO_ERROR) {
					year = temp.year;
					month = temp.month;
					day = temp.day;
					comparator = year * 372 + month * 13 + day;
				}
			}

		}
		return istr;

	}

	//write
	//This query writes the date YYYY/MM/DD, and then returns a reference to the std::ostream object.
	std::ostream& Date::write(std::ostream& ostr)const {

		ostr << year;
		ostr << '/';
		ostr.width(2);
		ostr.fill('0');
		ostr << month;
		ostr << '/';
		ostr.width(2);
		ostr << day;
		//ostr << day << std::endl;
		ostr.fill(' ');
		return ostr;


	}

	//bool functions
	// member functions
	int Date::errCode() const {
		return error;
	}

	bool Date::bad() const {
		return errCode() != NO_ERROR;
	}

	// operators
	bool Date::operator==(const Date& date_) const {

		return comparator == date_.comparator;
	}

	bool Date::operator!=(const Date& date_) const {

		return !(comparator == date_.comparator);
	}

	bool Date::operator<(const Date& date_) const {

		return comparator < date_.comparator;
	}
	bool Date::operator>(const Date& date_) const {

		return comparator > date_.comparator;
	}

	bool Date::operator<=(const Date& date_) const {

		return comparator <= date_.comparator;
	}

	bool Date::operator>=(const Date& date_) const {
		return comparator >= date_.comparator;

	}

	// non-memeber operator overloads
	std::ostream& operator<<(std::ostream& os, const Date& date_) {
		return date_.write(os);
	}

	std::istream& operator>>(std::istream& is, Date& date_) {
		return date_.read(is);
	}
}

