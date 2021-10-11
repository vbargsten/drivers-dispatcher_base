#pragma once
#include <dispatcher_base/Input.hpp>
#include <dispatcher_base/SingleDispatch_impl.hpp>

using namespace dispatcher_base;

template <typename T>
Input<T>::Input(std::string const& name)
    : mName(name) {}
    
template <typename T>
std::string Input<T>::getName() const
{
    return mName;
}

template <typename T>
void Input<T>::write(base::NamedVector<T> const& sample, base::Time time)
{
    // Never written or names changed, resolve names on the dispatches
    if ( mLastUpdate.isNull() || 
        inputNames.size() != sample.names.size() ||
        inputNames != sample.names ) 
    {
        for (size_t i = 0; i < dispatches.size(); ++i)
            dispatches[i].resolveInputNames(sample);
        
        inputNames = sample.names;
    }

    for (size_t i = 0; i < dispatches.size(); ++i)
        dispatches[i].write(sample, time);

    mLastUpdate = time;
}

template <typename T>
void Input<T>::reset()
{
    mLastUpdate = base::Time();
}

