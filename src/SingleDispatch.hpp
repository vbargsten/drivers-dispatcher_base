#ifndef DISPATCHER_BASE_SINGLE_DISPATCH_HPP
#define DISPATCHER_BASE_SINGLE_DISPATCH_HPP

#include <dispatcher_base/ElementSelection.hpp>
#include <base/Time.hpp>
#include <base/NamedVector.hpp>

namespace dispatcher_base
{
    template <typename T> class Output;

    /** Configuration of a single dispatch on Dispatcher
     */
    template <typename T>
    struct SingleDispatch
    {
        /** The joint selection on the input */
        ElementSelection<T> input;
        /** The output channel */
        Output<T>* output_channel;
        /** The joint selection on the output */
        ElementSelection<T> output;
        /** When true, do not set output's flag for new data needing to be read */
        bool defer_output = false;
        
        SingleDispatch<T>();

        void resolveInputNames(base::NamedVector<T> const& input_sample);

        void write(base::NamedVector<T> const& input, base::Time time=base::Time::now());
    };
}

#endif
