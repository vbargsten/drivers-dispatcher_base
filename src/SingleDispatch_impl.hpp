#pragma once
#include <dispatcher_base/SingleDispatch.hpp>
#include <dispatcher_base/Output.hpp>
#include <base/Time.hpp>

using namespace dispatcher_base;
using namespace std;

template <typename T>
SingleDispatch<T>::SingleDispatch()
    : output_channel(0) {}

template <typename T>
void SingleDispatch<T>::resolveInputNames(base::NamedVector<T> const& sample)
{
    input.resolveNames(sample);
}

template <typename T>
void SingleDispatch<T>::write(base::NamedVector<T> const& sample, base::Time time)
{
    for (size_t i = 0; i < input.size(); ++i)
    {
        size_t outputIdx = output.byIndex[i];
        output_channel->updateJoint(outputIdx, time, sample[input.byIndex[i]], !defer_output);
    }
}

