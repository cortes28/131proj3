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

	//	TO DO

	bool condition = false;
	TransactionVector temp;

	for(int i = 0; i < transactionVector_.size(); ++i)
	{
			if(transactionVector_[i].number_ == number)
			{
				temp.push_back(transactionVector_[i]);
			}
	}

		if(temp[0].date_ == gCurrentDate && authorizationMap_[number].startTime_ == gCurrentTime)
		{
			condition = true;
			transactionVector_.push_back(Transaction(number, authorizationMap_[number].name_, gCurrentDate, gCurrentTime, condition));
			return condition;
		}
	transactionVector_.push_back(Transaction(number, authorizationMap_[number].name_, gCurrentDate, gCurrentTime, condition));


	return condition;

}


bool GateControl::addAuthorization(CardNumber number, const string& name, const string& startTime, const string& endTime)
{

	//	TO DO

	bool success = true;

	if(authorizationMap_.count(number))
	{
		success = false;

		return success;
	}

	//auto found = authorizationMap_.find(number);

	//if(found == authorizationMap_.end())
	//{
	//	return false;
	//}

	//authorizationMap_.insert(std::pair<CardNumber, Authorization>(number, Authorization(number, name, startTime, endTime)));

  authorizationMap_[number] = Authorization(number, name, startTime, endTime);

	return success;

}


bool GateControl::changeAuthorization(CardNumber number, const string& name, const string& startTime, const string& endTime)
{

	//	TO DO
	if(!authorizationMap_.count(number)) { return false; }
	//
	// auto node = authorizationMap_.extract(number);
	// node.Authorization(number, name, startTime, endTime);
	// authorizationMap_.insert(std::move(node));

	authorizationMap_[number] = Authorization(number, name, startTime, endTime);

	return true;

}


bool GateControl::deleteAuthorization(CardNumber number)
{

	//	TO DO
	if(!authorizationMap_.count(number)) { return false; }

	authorizationMap_.erase(number);

	return true;

}


void GateControl::getAllAuthorizations(AuthorizationVector& authorizationVector)
{

	//	TO DO
	if(!authorizationMap_.empty()) { authorizationVector.clear(); }

	//for(int i = 0; i < authorizationMap_.size(); ++i)
	//{
	//	authorizationVector.push_back(authorizationMap_[i]);
	//}

	for(auto elem :authorizationMap_)
	{
		authorizationVector.push_back(elem.second);
	}

}


void GateControl::getAllTransactions(TransactionVector& transactionVector)
{

	//	TO DO
	if(transactionVector_.empty()) { transactionVector.clear(); }

	for(int i = 0; i < transactionVector_.size(); ++i)
	{
		transactionVector.push_back(transactionVector_[i]);
	}

}


bool GateControl::getCardAuthorization(CardNumber number, Authorization& authorization)
{

	//	TO DO
	if(!authorizationMap_.count(number)) { return false; }
//changnig authorizationVector_ to authorizationMap_ since adding to the authorization record

	//authorizationMap_.insert(std::pair<CardNumber,Authorization>(number, authorization)); // Authorization(authorization.number_, authorization.name_, authorization.startTime, authorization.endTime)
	authorization = Authorization(authorizationMap_[number].number_, authorizationMap_[number].name_, authorizationMap_[number].startTime_, authorizationMap_[number].endTime_);
	return true;

}


void GateControl::getCardTransactions(CardNumber number, TransactionVector& transactionVector)
{

	//	TO DO

	if(transactionVector_.empty()) { transactionVector.clear(); }
	//first to get the transactions from the number_
	for(int i = 0; i < transactionVector_.size(); ++i)
	{
		if(transactionVector_[i].number_ == number)
		{
			transactionVector.push_back(transactionVector_[i]);
		}
	}

}
