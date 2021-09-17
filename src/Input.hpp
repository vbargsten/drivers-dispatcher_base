#ifndef DISPATCHER_BASE_INPUT_HPP
#define DISPATCHER_BASE_INPUT_HPP

#include <string>
#include <base/NamedVector.hpp>
#include <dispatcher_base/SingleDispatch.hpp>

namespace dispatcher_base
{
    /** Configuration of an input on Dispatcher
     */
    template <typename T> 
    class Input
    {
        std::string mName;
        base::Time mLastUpdate;
        std::vector<std::string> inputNames;

    public:
        Input(std::string const& name = "");

        std::string getName() const;

        /** The list of dispatches that use this input
         */
        std::vector<SingleDispatch<T>> dispatches;

        /** Write a new sample on this input
         */
        void write(base::NamedVector<T> const& sample);

        /** Resets the internal tracking state, without changing the
         * configuration
         */
        void reset();
    };
}

#endif

