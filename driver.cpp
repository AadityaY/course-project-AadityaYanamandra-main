#include <iostream>
#include "hash.hpp"
#include "PriorityQueue.hpp"
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;
//comment

void displayMenu() // do not modify
{
    cout << "------------------" << endl;
    cout << "1: Build the data structure (execute this option one time)" << endl;
    cout << "2: Add a review" << endl;
    cout << "3: Retrieve most recent review for a restaurant" << endl;
    cout << "4: Pop most recent review for a restaurant" << endl;
    cout << "5: Print reviews for a restaurant" << endl;
    cout << "6: Display number of collisions" << endl;
    cout << "7: Display table results" << endl;
    cout << "8: Exit" << endl;
    cout << "------------------" << endl;
}

int main(int argc, char* argv[])
{
    if (argc <3)
    {
        cout<<"need correct number of arguments"<<endl;
    }
	
    string fname = argv[1];
    int tableSize = stoi(argv[2]);
    int ch = 0;
    string chs;
    //HashTable ht(5);
    HashTable ht(tableSize);
	
    while(ch!=8)
    {
        displayMenu();
        cout << "Enter your choice >>";
        getline(cin, chs);
        ch = stoi(chs);
        switch (ch)
        {
            case 1:
			{
				ht.setup(fname);
				break;
            }
            case 2:
			{
                string restaurant, customer, review, time;
                cout << "Restaurant Name: ";
                getline(cin, restaurant);
                cout << "Customer: ";
                getline(cin, customer);
                cout << "Review: ";
                getline(cin, review);
                cout << "Time: ";
                getline(cin, time);
                ReviewInfo rev = {restaurant, review, customer, stoi(time)};
                ht.insertItem(rev);
				break;
            }
            case 3:
			{
                string restaurant;
                cout << "Restaurant name:";
                getline(cin, restaurant);
                node* temp = ht.searchItem(restaurant);
                if (!temp || temp->pq.isEmpty()) {
                    cout << "no record found" << endl;
                } else {
                    cout << "retrieved result" << endl;
                    ReviewInfo rev = temp->pq.peek();
                    cout << "Restaurant Name: " << rev.restaurantName << "\nCustomer:" << rev.customer << "\nReview:" << rev.review << "\nTime:" << rev.time << endl;
                }
				break;
            }
            case 4:
			{
                string restaurant;
                cout << "Restaurant Name:";
                getline(cin, restaurant);
                node* temp = ht.searchItem(restaurant);
                if (!temp) {
                    cout << "no record found" << endl;
                } else {
                    temp->pq.pop();
                }
				break;
            }
            case 5:
			{
				string restaurant;
                cout << "Restaurant Name:";
                getline(cin, restaurant);
                node* temp = ht.searchItem(restaurant);
                if (!temp) {
                    cout << "no record found" << endl;
                } else {
                    cout << "Restaurant: " << temp->restaurantName << endl;
                    temp->pq.print();
                }
				break;
			}
            case 6:
                cout << "Number of collisions:" << ht.getNumCollision() << endl;
                break;
            case 7:
                ht.displayTable();
                break;
            case 8:
                break;
            default:
                cout << "Enter a valid option." << endl;
                break;
        }
    }
    
}
