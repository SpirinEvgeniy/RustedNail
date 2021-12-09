
#include "NativeEntity.h"

NativeEntity::NativeEntity() {
    myVec = { 33.654, 44.654, 55.654 , 121.54, 1234.453 }; 
}

ManagedEntity::ManagedEntity() {
    nativeObj = new NativeEntity();
}

ManagedEntity::~ManagedEntity() {
    delete nativeObj;

}

array<double>^ ManagedEntity::GetVec()
{
    std::vector<double> tempVec = nativeObj->GetVec();
    const int SIZE = tempVec.size();
    array<double>^ tempArr = gcnew array<double>(SIZE);
    for (int i = 0; i < SIZE; i++)
    {
        tempArr[i] = tempVec[i];
    }
    return tempArr;
}