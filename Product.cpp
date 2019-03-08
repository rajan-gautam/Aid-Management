

#define _CRT_SECURE_NO_WARNINGS
#include "Product.h"
#include "ErrorState.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;


namespace AMA {

	//stores the name in dynamically allocated memory
	//replaces any name previously stored
	//If the incoming parameter holds the nullptr address,
	//removes the name of the product, if any, from memory.

	void Product::name(const char* _name) {
		int size = strlen(_name) + 1;
		if (_name != nullptr)
		{
			if (productName != nullptr)
			{
				delete[] productName;
				productName = nullptr;
			}
			//dynamic allocation
			productName = new char[size];
			strcpy(productName, _name);
		}
		else
			productName = nullptr;
	}

	// QUERIES
	//
	//returns the address of the C-style string that holds the name of the product.
	//if the product has no name, this query returns nullptr.
	//
	const char* Product::name() const	{
		return (productName != nullptr) ? productName : nullptr;
	}

	//returns sku;
	//
	const char* Product::sku() const { return  _sku; }

	//returns unit
	//
	const char* Product::unit() const { return productUnit; }

	//returns tax_status
	//
	bool Product::taxed() const { return isTaxable; }

	//returns price before tax
	double Product::price() const { return priceSansTax; }

	//returns the price of a single item of
	//the product plus any tax that applies to the product
	//
	double Product::cost() const {
		return (isTaxable) ? (priceSansTax * (((double)current_TaxRate / 100) + 1)) : priceSansTax;
	}

	//receives the address of a C-style null-terminated
	//string holding an error message
	//and stores that message in the ErrorState object. 
	//
	void Product::message(const char* ErrorMsg) {
		errorState.message(ErrorMsg);
	}

	//query returns true if the ErrorState object is clear; 
	//false otherwise
	//
	bool Product::isClear() const	{
		return (errorState.isClear()) ? true : false;
	}
	//public
	//Zero-One argument constructor	optionally receives a character that identifies the product type.
	//The default value is ‘N’.
	//sets the current object to a safe recognizable empty state
	//
	Product::Product(const char prodType)	{
		productType = prodType;
		_sku[0] = '\0';
		productUnit[0] = '\0';
		productName = nullptr;
		CurrentQuantity = -1;
		neededQuantity = -1;
		priceSansTax = -1;
		isTaxable = false;
		errorState.ErrorState::clear();
	}

	//Seven argument Constructor
	// receives data and sets the data to the current object.
	//
	Product::Product(const char* SKU, const char* ProdName, const char* Prod_unit, int CurQty, bool taxStatus, double priceBefTax, int neededQty)	{

		if (SKU != nullptr) // && nm != nullptr && unit != nullptr) {
		{
			strncpy(_sku, SKU, strlen(SKU));
			_sku[strlen(SKU)] = '\0';
		}
		productName = nullptr;
		name(ProdName);
		strncpy(productUnit, Prod_unit, strlen(Prod_unit));
		productUnit[strlen(Prod_unit)] = '\0';

		CurrentQuantity = CurQty;
		isTaxable = taxStatus;
		priceSansTax = priceBefTax;
		neededQuantity = neededQty;
	}

	//copy constructor
	//
	Product::Product(const Product& object)	{
		productName = nullptr;
		*this = object; //calls copy assignment operator
	}

	//copy assignment operator
	//replaces the current object with a copy of the object referenced
	//
	Product& Product::operator=(const Product& obj)	{
		if (this != &obj){  //check for self-assignment
			productType = obj.productType; //type
			strncpy(_sku, obj._sku, strlen(obj._sku));//sku
			_sku[strlen(obj._sku)] = '\0';

			strncpy(productUnit, obj.productUnit, strlen(obj.productUnit)); //unit
			productUnit[strlen(obj.productUnit)] = '\0';

			CurrentQuantity = obj.CurrentQuantity; //quanitity present

			neededQuantity = obj.neededQuantity; //neededQuantity

			priceSansTax = obj.priceSansTax;//tax status

			isTaxable = obj.isTaxable;//tax status

			delete[] productName; //delete previously allocated dynamic memory
			productName = nullptr;
			name(obj.productName); //name
		}
		return *this;
	}

	// Destructor: deallocates dynamically allocated memory
	//
	Product::~Product()	{
		delete[] productName;
		productName = nullptr;
	}

	//returns true if the string is identical to the sku of the current object; 
	//false otherwise
	//
	bool Product::operator==(const char* sku_) const {
		//return strcmp(_sku, sku_)
		return (sku() == sku_) ? true : false;
	}

	//returns the total cost of all items of the product on hand, taxes included.
	//
	double Product::total_cost() const {
		return cost()*CurrentQuantity;
	}

	//receives an integer holding the number of units of the Product that are on hand.
	//
	void Product::quantity(int noOfUnits) {
		CurrentQuantity = noOfUnits;
	}

	//returns true if the object in a safe empty state; false otherwise.
	//
	bool Product::isEmpty()const {
		if (((CurrentQuantity == -1) && (_sku[0] == '\0') &&
			(productName == nullptr) && (neededQuantity == -1) &&
			(neededQuantity == -1) && (priceSansTax == -1) && (isTaxable == 0)))
			return true;
		else
			return false;
	}

	// returns the number of products that are needed
	int Product::qtyNeeded() const {
		return neededQuantity;
	}

	// returns the number of product that are on hand
	int Product::quantity() const {
		return CurrentQuantity;
	}

	//returns true if the sku of the current object is greater
	//than the string stored at the received address 
	//
	bool Product::operator>(const char* rcvdAddress) const {
		return sku() > rcvdAddress;
		//return (strcmp(_sku, rcvdAddress) > 0) ? true : false;
	}

	//receives an unmodifiable reference to a Product object;
	//returns true if the name of the current object is greater than the name of the referenced Product object 
	//
	bool Product::operator>(const iProduct& object) const {
		return (strlen(productName) > strlen(object.name()));
	}

	//If the integer received is positive - valued,
	//adds it to the quantity on hand. if negative or zero, does nothing and 
	//returns the quantity on hand (without modification).
	//
	int Product::operator+=(int add) {
		if (add > 0)
			CurrentQuantity += add;
		return CurrentQuantity;
	}

	//store query
	//inserts into the fstream object the character that identifies the product type as the first field in the record.  
	//inserts into the fstream object the data for the current object in comma separated fields.
	// if the bool parameter is true, inserts a newline at the end of the record.
	//
	std::fstream& Product::store(std::fstream& file, bool newLine) const {
		//if (file.is_open()) {
		file << productType << "," << _sku << "," << productName << ",";
		file << productUnit << "," << isTaxable << "," << priceSansTax << ",";
		file << CurrentQuantity << "," << neededQuantity;

		//}
		if (newLine)
			file << endl;

		return file;
	}

	//load query
	//extracts the fields for a single record from the fstream object
	//creates a temporary object from the extracted field data
	//copy assigns the temporary object to the current object
	//
	std::fstream& Product::load(std::fstream& file) {

		Product temp; //temporary object

		char prodName[max_name_length + 1];
		char taxStatus_;

		file.getline(temp._sku, max_sku_length, ',');

		file.getline(prodName, max_name_length + 1, ',');;
		temp.name(prodName);
		file.getline(temp.productUnit, max_unit_length, ',');

		file >> taxStatus_;

		if (taxStatus_ == '1')
			temp.isTaxable = true;
		else if (taxStatus_ == '0')
			temp.isTaxable = false;

		file.ignore();
		file >> temp.priceSansTax;
		file.ignore();
		file >> temp.CurrentQuantity;
		file.ignore();
		file >> temp.neededQuantity;
		file.ignore();

		//copy assigns the temp obj to current obj
		*this = temp;

		return file;
	}

	//receives a reference to an ostream object
	//and a bool and returns a reference to the ostream object.
	//
	std::ostream& Product::write(std::ostream& os, bool linear) const {
		if (!errorState.isClear()){
			os << errorState.message();
			return os;
		}

		if (linear) {//if true output is on a single line
			//sku
			os.fill(' ');
			os.width(max_sku_length);
			os.setf(ios::left);
			//os << setw(max_sku_length);
			os << _sku << "|";

			//name
			os.fill(' ');
			os.width(20);
			os.fill(' ');
			os << productName << "|";
			os.unsetf(ios::left);

			//cost
			os.fill(' ');
			os.setf(ios::fixed);
			os.width(7);
			os.precision(2);
			os << cost() << "|";

			//Current Quantity
			os.fill(' ');
			os.width(4);
			os << CurrentQuantity << "|";

			//unit
			os.setf(ios::left);
			os.fill(' ');
			os.width(10);
			os << unit() << "|";

			//needed quantity
			os.unsetf(ios::left);
			os.fill(' ');
			os.width(4);
			os << neededQuantity << "|";
			os.setf(ios::fixed);
		}
		else{
			os << " Sku: " << sku() << endl;
			os << " Name (no spaces): " << name() << endl;
			os << " Price: " << price() << endl;
			if (taxed())
				//os << "either of:" << endl;
				os << " Price after tax: " << cost() << endl;
			else
				os << " Price after tax: " << "N/A" << endl;

			os << " Quantity on Hand: " << CurrentQuantity << ' ' << unit() << endl;
			os << " Quantity needed: " << neededQuantity;
		}
		return os;
	}

	// extracts the data from istream
	//
	std::istream& Product::read(std::istream& is)
	{
		errorState.clear();
		char SKU_[max_sku_length + 1];
		char prodNm[max_name_length + 1];
		char unit_[max_unit_length + 1];
		int  cur_quanity;
		int qty_Needed;
		double price_;
		char isTaxed;
		//bool taxStatus;// = false;
		bool validator = false;

		while (validator == false)
		{
			validator = true;
			cout << " Sku: "; //sku
			is >> SKU_;
			cout << " Name (no spaces): ";
			is >> prodNm; //name
			cout << " Unit: ";
			is >> unit_; //unit
			cout << " Taxed? (y/n): ";
			is >> isTaxed; //taxed??
			if (isTaxed != 'y' && isTaxed != 'Y' && isTaxed != 'n' && isTaxed != 'N'){
				errorState.message("Only (Y)es or (N)o are acceptable");
				is.setstate(std::ios::failbit);
				break;
			}
			cout << " Price: "; //price
			is >> price_;
			if (is.fail()) {
				errorState.message("Invalid Price Entry");
				is.setstate(std::ios::failbit);
				break;
			}
			cout << " Quantity on hand: "; //current quanity
			is >> cur_quanity;
			if (is.fail()) {
				errorState.message("Invalid Quantity Entry");
				is.setstate(std::ios::failbit);
				break;
			}
			cout << " Quantity needed: "; //needed quantity
			is >> qty_Needed;
			if (is.fail()) {
				errorState.message("Invalid Quantity Needed Entry");
				break;
			}
			is.clear();    // Restore input stream to working state
			is.ignore();
		}

		if (!is.fail() && errorState.isClear()) {
			strcpy(_sku, SKU_); //sku
			(*this).name(prodNm);//name
			strcpy(productUnit, unit_); //unit
			CurrentQuantity = cur_quanity;
			if (isTaxed == 'y' || isTaxed == 'Y')
				isTaxable = true;
			else if (isTaxed == 'n' || isTaxed == 'N')
				isTaxable = false;
			priceSansTax = price_;
			neededQuantity = qty_Needed;
		}
		return is;
	}

	//helper functions
	//receives a ref to ostream object and unmodifiable ref to Product object
	//returns a ref to the ostream object
	//
	ostream& operator<<(std::ostream& os, const iProduct& object) {
		return object.write(os, true); //write(ostream&, bool = true)
	}

	//receives a reference to an istream object and a reference to a Product object 
	//and returns a reference to the istream object
	//
	istream& operator>>(istream& is, iProduct& object) {
		return object.read(is);
	}

	//receives a reference to a double
	//returns the updated double
	//
	double operator+=(double& total, const iProduct& object) {
		//cout << total << endl;
		total += object.total_cost();
		return total;
	}
}
