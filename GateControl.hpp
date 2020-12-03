#pragma once


#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

typedef size_t CardNumber;

typedef size_t GateNumber;



struct Authorization
{
	Authorization() { }

	Authorization(CardNumber number, const string& name, const string& startTime, const string& endTime)
	: number_(number), name_(name), startTime_(startTime), endTime_(endTime) { }

	CardNumber number_;

	string name_;

	string startTime_;

	string endTime_;
};

typedef map<CardNumber, Authorization> AuthorizationMap;
typedef	AuthorizationMap::iterator AuthorizationMapIterator;

typedef	vector<Authorization> AuthorizationVector;

struct Transaction
{
	Transaction() { }

	Transaction(CardNumber number, const string& name, const string& date, const string& time, bool accessAllowed)
	: number_(number), name_(name), date_(date), time_(time), accessAllowed_(accessAllowed) { }

	CardNumber number_;

	string name_;

	string date_;

	string time_;

	bool accessAllowed_;
};

typedef	vector<Transaction> TransactionVector;
typedef	TransactionVector::iterator TransactionVectorIterator;

class	GateControl
{
	public:
		bool accessAllowed(CardNumber number);

		bool addAuthorization(CardNumber number, const string& name, const string& startTime, const string& endTime);

		bool changeAuthorization(CardNumber number, const string& name, const string& startTime, const string& endTime);

		bool deleteAuthorization(CardNumber number);

		void getAllAuthorizations(AuthorizationVector& authorizationVector);

		void getAllTransactions(TransactionVector& transactionVector);

		bool getCardAuthorization(CardNumber number, Authorization& authorization);

		void getCardTransactions(CardNumber number, TransactionVector& transactionVector);

	private:
		AuthorizationMap authorizationMap_;

		TransactionVector transactionVector_;
};



extern string gCurrentDate;

extern string gCurrentTime;



//****************************************************************************************
//
//	TO DO
//
//****************************************************************************************
bool GateControl::accessAllowed(CardNumber number)
{

	//if by chance the number is not found, then we will send the number that was attempted
	//to log in and since the number is nonexistent, we push "***" as the name and the rest of the
	//arguments as normal with it resulting as false.
	if(!authorizationMap_.count(number))
	{
		transactionVector_.push_back(Transaction(number, "***", gCurrentDate, gCurrentTime, false));
	}

	//if they correspond with the times, it will record true and if not it will record as false.
	else if(authorizationMap_[number].endTime_ >= gCurrentTime && authorizationMap_[number].startTime_ <= gCurrentTime)
	{
	//	condition = true;
		transactionVector_.push_back(Transaction(number, authorizationMap_[number].name_, gCurrentDate, gCurrentTime, true));
		return true;
	}

	else
		transactionVector_.push_back(Transaction(number, authorizationMap_[number].name_, gCurrentDate, gCurrentTime, false));

	return false;
}


bool GateControl::addAuthorization(CardNumber number, const string& name, const string& startTime, const string& endTime)
{

	//	TO DO
	// if the number is found then we return false, cannot add same keys!
	if(authorizationMap_.count(number)) { return false; }

		//add it if there is no similar key and return true.
		authorizationMap_.insert(std::pair(number, Authorization(number, name, startTime, endTime)));

	return true;
}


bool GateControl::changeAuthorization(CardNumber number, const string& name, const string& startTime, const string& endTime)
{

	//	TO DO
	//if the number is NOT found, then we return false indicating a change could not
	//occur.
	if(!authorizationMap_.count(number)) { return false; }

	//we chance the values of that specific card number with the arguments passed.
	//and return true.
	authorizationMap_[number] = Authorization(number, name, startTime, endTime);

	return true;
}


bool GateControl::deleteAuthorization(CardNumber number)
{

	//	TO DO
	//if the number was not found, return false as you cannot delete something that
	//is not there.
	if(!authorizationMap_.count(number)) { return false; }

	//erasing the corresponding key.
	authorizationMap_.erase(number);

	return true;
}

//missing all authorization records code?//maybe copy the authorizationMap_ into a vector (loop)
void GateControl::getAllAuthorizations(AuthorizationVector& authorizationVector)
{

	//	TO DO
	//if the vector is not empty, then we clear it
	if(!authorizationVector.empty()) { authorizationVector.clear(); }

	//pushing elements into the vector.
	for(auto elem : authorizationMap_)
	{
		authorizationVector.push_back(elem.second);
	}

}

//maybe copy the transactionsvector_ (one noted on top)
void GateControl::getAllTransactions(TransactionVector& transactionVector)
{

	//	TO DO
	//i vector is NOT empty, then we clear the transaction vector.
	if(!transactionVector.empty()) { transactionVector.clear(); }

	//push the contents of our vector.
	for(int i = 0; i < transactionVector_.size(); ++i)
	{
		transactionVector.push_back(transactionVector_[i]);
	}

}


bool GateControl::getCardAuthorization(CardNumber number, Authorization& authorization)
{

	//	TO DO
	//if the number is not found, then we return false.
		if(!authorizationMap_.count(number)) { return false; }

	//we push the corresponding authorization into the 'authorization'.
	authorization = Authorization(authorizationMap_[number].number_, authorizationMap_[number].name_, authorizationMap_[number].startTime_, authorizationMap_[number].endTime_);
	return true;
}


void GateControl::getCardTransactions(CardNumber number, TransactionVector& transactionVector)
{

	//	TO DO

	//check if the vector is empty.
	if(transactionVector.empty()) { transactionVector.clear(); }
	//first to get the transactions from the number_
	for(int i = 0; i < transactionVector_.size(); ++i)
	{
		//push the matching numbers into the vector.
		if(transactionVector_[i].number_ == number)
		{
			transactionVector.push_back(transactionVector_[i]);
		}
	}

}
