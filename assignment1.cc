/***********************************************************
 CSCI 340 - Assignment 1 - Spring 2018
 
 Progammer: Sam Piecz
 Z-ID: Z1732715
 Section: 1
 TA: 
 Date Due: January 29, 2018
 
 Purpose: Implement linear search and binary search on random
 integers stored within vectors.
 ************************************************************/

#include <algorithm>
#include <iostream>
#include <vector>
#include <iomanip>

using std::cout;
using std::endl;
using std::random_shuffle;
using std::vector;
using std::setw;

const int DATA_SIZE = 200;
const int DATA_RANGE = 200;
const int DATA_SEED = 9;
const int SEARCH_SEED = 17;

/***************************************************************
 linear_search 

 Use: Uses linear search to find integer stored within a vector. 

 Parameters: Constant reference to an int vector, const integer,
 and a reference to an int.

 Returns: Position of found element, or negative one. 
***************************************************************/
int linear_search(const vector<int>& inputVec, const int x, int& comparisons)
{
    comparisons = 0;
    for(size_t vectorIndex = 0; vectorIndex < inputVec.size(); vectorIndex++)
    {
        comparisons++;
        if(inputVec[vectorIndex] == x)
        {
            return vectorIndex;
        }
    }
    return -1;
}

/***************************************************************
 binary_search 

 Use: Takes far less time to find integer stored within vector.
 This function shows the amount of comparisons it takes when
 searching. 

 Parameters: A reference to a constant int vector, a constant
 int, and a reference to an int.

 Returns: The index of where the number has been found.
 Otherwise it returns negative one.
***************************************************************/
int binary_search(const vector<int>& inputVec, const int x, int& comparisons)
{
    int low, mid, high;
    low = 0;
    high = inputVec.size() -1;
    while (low < high)
    {
        mid = (low + high) / 2;
        if(inputVec[mid] == x)
        {
            comparisons++;
            return mid;
        }
        else if(x > inputVec[mid])
        {
            comparisons++;
            low = mid + 1;
        }
        else
        {
            comparisons++;
            high = mid - 1;
        }
    }
    return -1;
}

/***************************************************************
 print_vec 

 Use: Prints all items within a vector. 

 Parameters: A constant vector of type int. 

 Returns: Nothing. Just prints items in vector. 
***************************************************************/
void print_vec( const vector<int>& vec )
{
    const int ITEM_W = 4;
    const int NO_ITEMS = 8;
    vector<int>::const_iterator it;
    for (it = vec.begin(); it != vec.end(); it++)
    {
        cout << setw(ITEM_W) << *it;
        if ((it - vec.begin()) % NO_ITEMS == 7)
        {
            cout << endl;
        }
    }
}

void average_comparisons(const vector<int>& inputVec, const vector<int>& searchVec, int (*search)(const vector<int>&, const int, int&) )
{
    int i, comparison = 0, sum = 0, found = 0;
    int res = 0;
    for (i = 0; i < (int)searchVec.size(); i++)
    {
        res = search( inputVec, searchVec[i], comparison );
        sum += comparison;
        if ( res >= 0 )
        {
           found++;
        }
    }
    cout << found << " numbers are found. The average number of comparisons in each search: " << (double)sum/(double)searchVec.size() << endl << endl;
}

int random_number()
{
    return rand()%DATA_RANGE + 1;
}


int main ()
{

    // -------- create unique random numbers ------------------//
    vector<int> inputVec(DATA_SIZE);
    srand(DATA_SEED);
    generate(inputVec.begin(), inputVec.end(), random_number);
    sort(inputVec.begin(), inputVec.end());
    vector<int>::iterator it = unique(inputVec.begin(), inputVec.end());
    inputVec.resize( it - inputVec.begin() );
    random_shuffle( inputVec.begin(), inputVec.end() );

    cout << "------ Data source: " << inputVec.size() << " unique random numbers ------" << endl; 
    print_vec(inputVec);
    cout << endl;

    // -------- create random numbers to be searched ---------//
    vector<int> searchVec(DATA_SIZE/2);
    srand(SEARCH_SEED);
    generate(searchVec.begin(), searchVec.end(), random_number);

    cout << "------ " << searchVec.size() << " random numbers to be searched: ------" << endl;
    print_vec(searchVec);
    cout << endl;

    cout << "Linear search: ";
    average_comparisons(inputVec, searchVec, linear_search);
    cout << "Binary search: ";
    average_comparisons(inputVec, searchVec, binary_search);

    sort(inputVec.begin(), inputVec.end());
    cout << "------- numbers in data source are now sorted ---------" << endl << endl;
    cout << "Linear search: ";
    average_comparisons(inputVec, searchVec, linear_search);
    cout << "Binary search: ";
    average_comparisons(inputVec, searchVec, binary_search);

    return 0;

}


