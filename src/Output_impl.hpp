#pragma once
#include <dispatcher_base/Output.hpp>

using namespace dispatcher_base;
using namespace std;

    
template <typename T>
Output<T>::Output(std::string const& name)
    : mName(name)
    , mIsNew(false)
    , mFullyInitialized(false) {};
    
template <typename T>
std::string Output<T>::getName() const
{
    return mName;
}

template <typename T>
size_t Output<T>::size() const
{
    return mState.size();
}

template <typename T>
vector<string> Output<T>::getNames() const
{
    return mState.names;
}

template <typename T>
vector<size_t> Output<T>::mapNamesToIndex(vector<string> const& names) const
{
    vector<size_t> result(names.size());
    for (size_t nameIdx = 0; nameIdx < names.size(); ++nameIdx)
        result[nameIdx] = mState.mapNameToIndex(names[nameIdx]);
    return result;
}

template <typename T>
void Output<T>::resize(vector<string> const& elementNames)
{
    resize(elementNames.size());
    mState.names = elementNames;
}

template <typename T>
void Output<T>::resize(size_t size)
{
    mState.resize(size);
    mUpdatedElements.resize(size);
    mUpdateTime.resize(size);
    reset();
}

template <typename T>
void Output<T>::reset()
{
    fill(mUpdatedElements.begin(), mUpdatedElements.end(), false);
    fill(mUpdateTime.begin(), mUpdateTime.end(), base::Time());
    mLatestUpdateTime = base::Time();
    mFullUpdateCounter = mState.size();
    mFullyInitialized = false;
    mIsNew = false;
}

template <typename T>
bool Output<T>::isNew() const
{
    return mFullyInitialized && mIsNew;
}

template <typename T>
bool Output<T>::isFullyUpdated() const
{
    return mFullUpdateCounter == 0;
}

template <typename T>
void Output<T>::updateJoint(size_t elementIdx, base::Time const& time, T const& sample, bool needsRead)
{
    if (elementIdx >= size())
        throw std::out_of_range("given element index is out of bounds");

    if (needsRead)
        mIsNew = true;

    mState[elementIdx] = sample;
    if (mLatestUpdateTime < time)
        mLatestUpdateTime = time;
    mUpdateTime[elementIdx] = time;
    if (!mUpdatedElements[elementIdx])
    {
        mUpdatedElements[elementIdx] = true;
        mFullUpdateCounter--;
        if (mFullUpdateCounter == 0)
            mFullyInitialized = true;
    }
}

template <typename T>
base::NamedVector<T> Output<T>::read()
{
    mIsNew = false;
    fill(mUpdatedElements.begin(), mUpdatedElements.end(), false);
    mFullUpdateCounter = mUpdatedElements.size();
    return mState;
}

template <typename T>
bool Output<T>::read(base::NamedVector<T>& sample, base::Time& time) 
{
    sample = mState;
    time = mLatestUpdateTime;
    bool wasNew = mIsNew;
    
    mIsNew = false;
    fill(mUpdatedElements.begin(), mUpdatedElements.end(), false);
    mFullUpdateCounter = mUpdatedElements.size();
    return wasNew;
}
