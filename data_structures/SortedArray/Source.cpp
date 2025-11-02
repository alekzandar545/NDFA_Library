/******************************************************************
*  Sample code to the course "Data Structures And Algorithms", FMI
*
* A template class for sorted dynamic array.
* Illustrate the proxy design pattern
* and sample unit testing with GoogleTest framework
*
* (cc) Petar Armyanov, FMI, 2024
*******************************************************************/

#include "SortedArray.h"
using fmi::sdp::SortedArray;

int main(int argc, char **argv)
{
    SortedArray<int> arr;
    arr.add(1);
    arr.add(2);
    arr.add(3);
    arr.add(4);
    arr.add(5);
    arr.add(6);
    for (size_t i = 0; i < 7; i++)
    {
        std::cout << arr[i] << ' ';
    }
    
}
