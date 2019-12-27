/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: William Boyd
 *
 * Created on December 26, 2019, 12:23 AM
 */

#include <cstdlib>
#include <iostream>
#include <cmath>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    int longSize;
    longSize = sizeof(unsigned long);
    int longLongBits = sizeof(unsigned long long) * 8;
    unsigned long long part1, part2, part3;
    ///////
    part1 = pow(2, 63);
    part1 -= 1;
    part1 <<= 1;
    part1 += 1;
    part2 = 0;
    part3 = 0;
//    unsigned long long maxLong = part1 + part2 + part3;
    std::cout << "Maximum unsigned long: " << part1 << ".\n";
//    cout << "Number of bits: " << longLongBits << ".\n";
    return 0;
}

