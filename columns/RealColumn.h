#pragma once
class RealColumn {
public:
    RealColumn ();
    ~RealColumn ();

private:
    bool isUnsigned;
    unsigned int mLimit;
    unsigned int mPrecision;
};

