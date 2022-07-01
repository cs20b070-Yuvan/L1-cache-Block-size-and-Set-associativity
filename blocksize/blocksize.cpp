#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <x86intrin.h>
#include <unistd.h>
#include <fstream>
using namespace std;

int main(void)
{
    uint32_t cycles_high=0, cycles_low=0;
    uint32_t cycles_high1=0,   cycles_low1=0;

    uint64_t totalTime = 0;

    int n = 200;
    int temp = 1;

    ofstream myfile;
    myfile.open ("output1.txt");

    int a[n];

    uint64_t etime;

    uint64_t strt,finish;

    for(int i =0; i<n; i++)
    {
        _mm_clflush(&a[i]);
    }

    for(int i=0; i<n; i++)
    {
        asm volatile ("CPUID\n\t"
                      "RDTSC\n\t"
                      "mov %%edx, %0\n\t"
                      "mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low)::
                      "%rax", "%rbx", "%rcx", "%rdx");
        temp = a[i];

        asm volatile("RDTSCP\n\t"
                     "mov %%edx, %0\n\t"
                     "mov %%eax, %1\n\t"
                     "CPUID\n\t": "=r" (cycles_high1), "=r" (cycles_low1)::
                     "%rax", "%rbx", "%rcx", "%rdx");

        strt = (((uint64_t)cycles_high) << 32) | cycles_low;
        finish = (((uint64_t)cycles_high1)   << 32) | cycles_low1;
        etime = (finish-strt);

        myfile << etime << "," << i << endl;
        totalTime += etime;
    }

    myfile.close();


    return 0;
}


