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

}


bool GateControl::addAuthorization(CardNumber number, const string& name, const string& startTime, const string& endTime)
{
	
	//	TO DO

}


bool GateControl::changeAuthorization(CardNumber number, const string& name, const string& startTime, const string& endTime)
{
	
	//	TO DO

}


bool GateControl::deleteAuthorization(CardNumber number)
{
	
	//	TO DO

}


void GateControl::getAllAuthorizations(AuthorizationVector& authorizationVector)
{
	
	//	TO DO	

}


void GateControl::getAllTransactions(TransactionVector& transactionVector)
{
	
	//	TO DO

}


bool GateControl::getCardAuthorization(CardNumber number, Authorization& authorization)
{

	//	TO DO

}


void GateControl::getCardTransactions(CardNumber number, TransactionVector& transactionVector)
{
	
	//	TO DO

}
