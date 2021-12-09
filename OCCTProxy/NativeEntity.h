#pragma once

#include <vector>
class NativeEntity {
private:
    std::vector<double> myVec;
public:
    NativeEntity();
    std::vector<double> GetVec() { return myVec; }
};




public ref class ManagedEntity {
public:
    ManagedEntity();
    ~ManagedEntity();

    array<double>^ GetVec();
private:
    NativeEntity* nativeObj;
};





