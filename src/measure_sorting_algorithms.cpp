#include <rtw/algorithm/insertion_sort.hpp>
#include <rtw/algorithm/intro_sort.hpp>
#include <rtw/algorithm/heap.hpp>
#include <rtw/algorithm/merge_sort.hpp>
#include <rtw/algorithm/quick_sort.hpp>

#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <string>

enum SortingAlgorithm{
    INSERTION_SORT = 0, 
    INTRO_SORT = 1, 
    HEAP_SORT = 2, 
    MERGE_SORT = 3, 
    QUICK_SORT = 4, 
    STD_HEAP_SORT = 5, 
    STD_STABLE_SORT = 6, 
    STD_SORT = 7, 
    SIZE
};

const std::vector<std::string> names{ "insertion_sort", "intro_sort", "heap_sort", "merge_sort", "quick_sort", "std::sort_heap", "std::stable_sort", "std::sort" };

inline void pre_sort(const std::vector<int>& original, std::vector<std::vector<int>>& data, std::chrono::system_clock::time_point& start)
{
    for(std::vector<int>& one_data : data){
        std::copy(original.begin(), original.end(), one_data.begin());
    }
    start = std::chrono::system_clock::now();
}

inline void post_sort(const std::chrono::system_clock::time_point& start, std::chrono::system_clock::time_point& end, std::vector<std::vector<int>>& result, SortingAlgorithm algorithm)
{
    end = std::chrono::system_clock::now();
    int elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    result[algorithm].push_back(elapsed);
}

void measure_sorting_algorithms()
{
    // size array
    int exp = 15;
    std::vector<int> size_array;
    for(int i = 0; i < exp; i++){
        size_array.push_back(std::pow(2, i + 1));
    }

    // result
    std::vector<std::vector<int>> result(SortingAlgorithm::SIZE);

    // sort
    for(int size : size_array){
        // generate random data
        std::random_device rnd;
        std::mt19937 mt(rnd());
        std::vector<int> original(size);
        for(int i = 0; i < size; i++){
            original[i] = mt();
        }

        // iteration
        int iteration = 1000;
        std::vector<std::vector<int>> data(iteration);
        for(std::vector<int>& one_data : data){
            one_data.resize(size);
        }

        // timer
        std::chrono::system_clock::time_point start, end;

        // insertion sort
        pre_sort(original, data, start);
        for(int i = 0; i < iteration; i++){
            rtw::insertion_sort(data[i].begin(), data[i].end());
        }
        post_sort(start, end, result, SortingAlgorithm::INSERTION_SORT);

        // intro sort
        pre_sort(original, data, start);
        for(int i = 0; i < iteration; i++){
            rtw::intro_sort(data[i].begin(), data[i].end());
        }
        post_sort(start, end, result, SortingAlgorithm::INTRO_SORT);

        // heap sort
        pre_sort(original, data, start);
        for(int i = 0; i < iteration; i++){
            rtw::make_heap(data[i].begin(), data[i].end());
            rtw::sort_heap(data[i].begin(), data[i].end());
        }
        post_sort(start, end, result, SortingAlgorithm::HEAP_SORT);

        // merge sort
        pre_sort(original, data, start);
        for(int i = 0; i < iteration; i++){
            rtw::merge_sort(data[i].begin(), data[i].end());
        }
        post_sort(start, end, result, SortingAlgorithm::MERGE_SORT);

        // quick sort
        pre_sort(original, data, start);
        for(int i = 0; i < iteration; i++){
            rtw::quick_sort(data[i].begin(), data[i].end());
        }
        post_sort(start, end, result, SortingAlgorithm::QUICK_SORT);

        // std heap sort
        pre_sort(original, data, start);
        for(int i = 0; i < iteration; i++){
            std::make_heap(data[i].begin(), data[i].end());
            std::sort_heap(data[i].begin(), data[i].end());
        }
        post_sort(start, end, result, SortingAlgorithm::STD_HEAP_SORT);

        // std stable sort
        pre_sort(original, data, start);
        for(int i = 0; i < iteration; i++){
            std::stable_sort(data[i].begin(), data[i].end());
        }
        post_sort(start, end, result, SortingAlgorithm::STD_STABLE_SORT);

        // stds sort
        pre_sort(original, data, start);
        for(int i = 0; i < iteration; i++){
            std::sort(data[i].begin(), data[i].end());
        }
        post_sort(start, end, result, SortingAlgorithm::STD_SORT);
    }

    // file out
    std::ofstream ofs("result.csv");
    if(ofs.is_open()){
        ofs << "size,";
        for(int size : size_array){
            ofs << size << ",";
        }
        ofs << std::endl;
        for(auto data = result.begin(); data != result.end(); ++data){
            ofs << names[std::distance(result.begin(), data)] << ",";
            for(int elapsed : *data){
                ofs << elapsed << ",";
            }
            ofs << std::endl;
        }
        ofs.close();
    }
}