//Final Project
//Perishable.h
//Rajan Gautam
//#128485166
//#rgautam4@myseneca.ca
//OOP244 SCC
//Milestone_5
//2018.08.07
//

#ifndef AMA_PERISHABLE_H
#define AMA_PERISHABLE_H

#include "Product.h"
#include "Date.h"

namespace AMA {


	class Perishable : public Product
	{
		Date expiryDate;
	public:
		//passes the file record tag for a perishable product (‘P’) to the base class constructor
		//sets the current object to a safe empty state
		//
		Perishable();
		//
		std::fstream&store(std::fstream& file, bool newLine = true) const;
		//
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear) const;
		std::istream& read(std::istream& is);
		const Date& expiry() const;

	};

}
#endif
