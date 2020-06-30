#include "AJob.h"
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

class BruteForceJob: public AJob
{
    private:
        string ctext;
        vector<string> alphabet;
        int key_size;
        string result;

    public:
        BruteForceJob(string ctext, vector<string> alphabet, int ksize);
        ~BruteForceJob();
        void ExecJob() override;
        string GetResult() override;
};
