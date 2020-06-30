#pragma once
#include <string>

using namespace std;

class AJob {
public:
    virtual ~AJob() = default;
	virtual void ExecJob()=0;
	virtual string GetResult()=0;
};



