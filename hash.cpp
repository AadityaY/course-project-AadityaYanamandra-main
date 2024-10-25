// CPP program to implement hashing with chaining
#include <iostream>
#include "hash.hpp"
#include <sstream>
#include <fstream>

using namespace std;
//comment

node* HashTable::createNode(string restaurantName, node* next)
{
    return new node{restaurantName, PriorityQ(50), next};
}

HashTable::HashTable(int bsize)
{
    tableSize=bsize;
    numCollision=0;
    table=new node*[tableSize];
    for (int i=0; i<tableSize; i++) {
        table[i]=nullptr;
    }
    return;
}

HashTable::~HashTable()
{
    node* temp1=nullptr;
    node* temp2=nullptr;
    for (int i=0; i<tableSize; i++) {
        temp1=table[i];
        while (temp1) {
            temp2=temp1->next;
            delete temp1;
            temp1=temp2;
        }
    }
    delete [] table;
    return;
}

void HashTable::displayTable()
{
    node* temp=nullptr;
    for (int i=0; i<tableSize; i++) {
        temp=table[i];
        cout << i << "|";
        while (temp) {
            cout << temp->restaurantName << "-->";
            temp=temp->next;
        }
        cout << "NULL" << endl;
    }
}

unsigned int HashTable::hashFunction(string restaurantName)
{
    long int nums=0;
    for (int i=0; i<restaurantName.length(); i++) {
        nums+=(int)restaurantName[i];
    }
    return nums%tableSize;
}

node* HashTable::searchItem(string restaurantName)
{
    int hf = hashFunction(restaurantName);
    node* temp = table[hf];
    while (temp) {
        if (temp->restaurantName==restaurantName) {
            return temp;
        }
        temp=temp->next;
    }
    return nullptr;
}

void HashTable::insertItem(ReviewInfo restaurant) {
    node* rest = searchItem(restaurant.restaurantName);
    if (rest!=nullptr) {
        rest->pq.insertElement(restaurant);
        return;
    }
    int hf = hashFunction(restaurant.restaurantName);
    if (table[hf]==nullptr) {
        rest=createNode(restaurant.restaurantName, nullptr);
        rest->pq.insertElement(restaurant);
        table[hf]=rest;
    } else {
        rest=createNode(restaurant.restaurantName, table[hf]);
        rest->pq.insertElement(restaurant);
        numCollision++;
        table[hf]=rest;
    }
    return;
}


void HashTable::setup(string fname) {
    ifstream inFile;
    string restaurant, review, name, time;
    inFile.open(fname);
    while (getline(inFile, restaurant, ';')) {
        getline(inFile, review, ';');
        getline(inFile, name, ';');
        getline(inFile, time, '\n');
        ReviewInfo rest = {restaurant, review, name, stoi(time)};
        insertItem(rest);
    }
    return;
}