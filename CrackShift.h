#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "PoolThread.h"
#include "BruteForceJob.h"
#include "AJob.h"
#include <chrono>

class CrackShift
{
    public:
        CrackShift();
        virtual ~CrackShift();

        bool GetEncryptText(string name);
        bool GetAlphabet(string name);
        void WriteText(string name);
        void Crack();
        vector<int> find_length_key();
    private:
        string text;
        vector<string> alphabet;
        string ctext;
        PoolThread* PTObj;
};
