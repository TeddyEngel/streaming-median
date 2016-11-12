//
//  main.cpp
//  StreamingMedian
//
//  Expects as first argument a number n that specifies how many numbers will be given on stdin,
//  then n integer numbers on stdin. Will print out the running median after each stdin.
//  Example input:
//  3 
//  1
//  2
//  3
//
//  Created by Teddy Engel on 12/11/2016.
//  Copyright (c) 2016 Teddy Engel. All rights reserved.
//
#include <iostream>
#include <iomanip>
#include <queue>
#include <algorithm>
using namespace std;

void print_median(float median)
{
    cout << std::fixed << std::setprecision(1) << median << std::endl;
}

int main()
{
    int n;
    cin >> n;
    
    int tmp;
    
    std::priority_queue<int> max_heap; // All numbers less or equal to current median
    std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap; // All numbers above or equal to current median
    
    float streaming_median = -1.0f;
    
    // The first number in the input sequence is added to one of the heaps, it doesn’t matter which, and returned as the first streaming median.
    if (n > 0)
    {
        cin >> tmp;
        max_heap.push(tmp);
        streaming_median = tmp;
        print_median(streaming_median);
    }
    
    // The second number in the input sequence is then added to the other heap, if the root of the right heap is less than the root of the left heap the two heaps are swapped, and the average of the two numbers is returned as the second streaming median.
    if (n > 1)
    {
        cin >> tmp;
        min_heap.push(tmp);
        
        if (min_heap.top() < max_heap.top())
        {
            int min_heap_value = min_heap.top();
            min_heap.pop();
            int max_heap_value = max_heap.top();
            max_heap.pop();
            min_heap.push(max_heap_value);
            max_heap.push(min_heap_value);
        }
        streaming_median = (streaming_median + tmp) / 2.0f;
        print_median(streaming_median);
    }
    
    // Each subsequent number in the input sequence is compared to the current median, and added to the left heap if it is less than the current median or to the right heap if it is greater than the current median; 
    for(int i = 2; i < n; i++)
    {
        cin >> tmp;
        
        if (tmp < streaming_median)
            max_heap.push(tmp);
        else if (tmp > streaming_median)
            min_heap.push(tmp);
        else
        {
            //if the input number is equal to the current median, it is added to whichever heap has the smaller count, or to either heap arbitrarily if they have the same count.
            if (max_heap.size() <= min_heap.size())
                max_heap.push(tmp);
            else
                min_heap.push(tmp);
        }
        
        // If that causes the counts of the two heaps to differ by more than 1, the root of the larger heap is removed and inserted in the smaller heap.
        if (abs(max_heap.size() - min_heap.size()) > 1)
        {
            if (max_heap.size() > min_heap.size())
            {
                min_heap.push(max_heap.top());
                max_heap.pop();
            }
            else
            {
                max_heap.push(min_heap.top());
                min_heap.pop();
            }
        }
        
        
        // Then the current median is computed as the root of the larger heap, if they differ in count, or the average of the roots of the two heaps, if they are the same size.
        if (max_heap.size() > min_heap.size())
            streaming_median = max_heap.top();
        else if (min_heap.size() > max_heap.size())
            streaming_median = min_heap.top();
        else
            streaming_median = (max_heap.top() + min_heap.top()) / 2.0f;
        
        print_median(streaming_median);
    }
    return 0;
}
