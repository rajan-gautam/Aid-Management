//Final Project
//Perishable.cpp
//Rajan Gautam
//#128485166
//rgautam4@myseneca.ca
//OOP244 SCC
//Milestone5
//2018.08.07
//

#include"Perishable.h"
using namespace std;

namespace AMA {
	//passes file record tag for a perishable product (‘P’) to base class constructor
	//
	Perishable::Perishable() :Product('P') { }

	//calls its base class version passing as arguments a reference to fsream obj & false flag
	//
	std::fstream& Perishable::store(std::fstream& file, bool newLine) const
	{
		Product::store(file, false);
		file << ","; //inserts a comma into the file record 
		file << expiryDate; //appends the expiry date to the file record.
		if (newLine) //if newLine is true, inserts '\n' before exiting.
			file << "\n";

		return file;
	}

	std::fstream& Perishable::load(std::fstream& file) {
		//calls its base class version
		Product::load(file);

		//loads expiry date from file record using read() fuct of Date object
		expiryDate.read(file);
		return file;
	}

	std::ostream& Perishable::write(std::ostream& os, bool linear) const {

		//calls its base class version passing arguments to ostrem obj and bool flag
		Product::write(os, linear);

		if (!isClear())//if not in safe empty state
			return os;
		if (linear)
			expiryDate.write(os); //if linear, adds the expiry date on the same line 
		else
		{
			os << endl << " Expiry date: ";
			expiryDate.write(os);
		}
		return os;
	}

	//populates the current object with the data extracted from the istream object
	//
	std::istream& Perishable::read(std::istream& is)
	{
		is.clear();
		Product::read(is);
		if (isClear())
		{
			cout << " Expiry date (YYYY/MM/DD): ";
			//if temp object in an error state, stores the appropriate error msg
			//and set istream obj to failed state.
			Date temp;
			temp.read(is);
			if (temp.bad())
			{
				switch (temp.errCode())
				{
				case 1: message("Invalid Price Entry");
					break;
				case 2: message("Invalid Year in Date Entry");
					break;
				case 3: message("Invalid Month in Date Entry");
					break;
				case 4: message("Invalid Day in Date Entry");
				}
				is.setstate(std::ios::failbit);
			}
			if (!is.fail())
				expiryDate = temp;
		}
		return is;
	}

	//query
	//returns the expiry date for the perishable product
	//

	const Date & Perishable::expiry() const
	{
		return expiryDate;
	}
}
