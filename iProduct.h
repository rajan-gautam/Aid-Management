

#include <fstream>

#ifndef AMA_IPRODUCT_H
#define AMA_IPRODUCT_H

namespace AMA {

	class iProduct
	{
	public:
		//	virtual ~iProduct() = 0;		
			//query

		virtual std::fstream& store(std::fstream& file, bool newLine = true) const = 0;

		//modifier

		virtual std::fstream& load(std::fstream& file) = 0;

		//query

		virtual std::ostream& write(std::ostream& os, bool linear) const = 0;

		//modifier

		virtual std::istream& read(std::istream& is) = 0;


		virtual bool operator==(const char*) const = 0;

		//return the cost of a single unit of an iProduct with taxes included
		//
		virtual double total_cost() const = 0;

		//return the address of a C-style null-terminated string containing the name of an iProduct
		//
		virtual const char* name() const = 0;

		//receive an integer holding the number of units of an iProduct that are currently available
		//
		virtual void quantity(int) = 0;

		//return the number of units of an iProduct that are needed
		//

		virtual int qtyNeeded() const = 0;

		//return the number of units of an iProduct that are currently available.
		//
		virtual int quantity() const = 0;

		//receive an integer identifying the number of units to be added to the iProduct
		//and return the updated number of units 
		//
		virtual int operator+=(int) = 0;

		//return true if the current object is greater than the referenced iProduct object; false otherwise
		//
		virtual bool operator>(const iProduct&) const = 0;

		//HELPER FUNCTIONs
		//
	};
	//
	std::ostream& operator<<(std::ostream&, const iProduct&);
	std::istream& operator>>(std::istream&, iProduct&);
	double operator+=(double&, const iProduct&);
	iProduct* CreateProduct();
	iProduct* CreatePerishable();


}
#endif // !1
