

#ifndef AMA_PRODUCT_H
#define AMA_PRODUCT_H

#include "ErrorState.h"
#include "iProduct.h"


namespace AMA {
	const int max_sku_length = 7;
	const int max_unit_length = 10;
	const int max_name_length = 75;
	const double current_TaxRate = 13;

	//
	class Product : public iProduct {
		char productType;
		char _sku[max_sku_length + 1];
		char productUnit[max_unit_length + 1];
		char* productName;
		int CurrentQuantity;
		int neededQuantity;
		double priceSansTax;
		bool isTaxable;
		ErrorState errorState;

	protected:
		void name(const char*);
		const char* name() const;
		const char* sku() const;
		const char* unit() const;
		bool taxed() const;
		double price() const;
		double cost() const;
		void message(const char*);
		bool isClear() const;

	public:

		//Zero-One argument constructor
		//
		Product(const char type = 'N');

		//Seven argument Constructor with default values
		//
		Product(const char*, const char*, const char*, int CurQty = 0, bool taxStatus = true, double priceBefTax = 0.0, int neededQty = 0);

		//copy constructor
		Product(const Product&);

		//copy assignment operator
		Product& operator= (const Product&);

		//destructor
		~Product();
		//
		std::fstream& store(std::fstream& file, bool newLine = true) const;
		//
		std::fstream& load(std::fstream& file);

		std::ostream& write(std::ostream& os, bool linear) const;

		std::istream& read(std::istream& is);
		bool operator==(const char*) const;
		double total_cost() const;
		void quantity(int);
		bool isEmpty() const;
		int qtyNeeded() const;
		int quantity() const;
		bool operator>(const char*) const;
		bool operator> (const iProduct&) const;
		int operator+=(int);

	};
	//helper functions
	std::ostream& operator<<(std::ostream&, const iProduct&);
	std::istream& operator>>(std::istream&, iProduct&);
	double operator+=(double&, const iProduct&);

}
#endif
