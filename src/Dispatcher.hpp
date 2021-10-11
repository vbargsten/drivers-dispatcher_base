#ifndef DISPATCHER_BASE_DISPATCHER_HPP
#define DISPATCHER_BASE_DISPATCHER_HPP

#include <vector>
#include <dispatcher_base/Input.hpp>
#include <dispatcher_base/Output.hpp>

namespace dispatcher_base
{
    /** Implementation of mux/demux logic for base::NamedVector<T>
     *
     * This class allows to transfer arbitrary sets of elements on inputs to other
     * sets on outputs. It allows to 
     */
    template <typename T>
    class Dispatcher
    {
        std::vector<Input<T>>  mInputs;
        std::vector<Output<T>> mOutputs;

    public:
        typedef size_t ChannelID;

        /** This declares an input to the dispatcher
         *
         * @param name the input name. This is mostly used for debugging /
         *   status purposes
         * @return the ID of the created input
         */
        ChannelID addInput(std::string const& name = "");

        /** This declares an output to the dispatcher, as well as the element names
         * for this output
         *
         * @param name the output name. This can be left empty.
         */
        ChannelID addOutput(std::string const& name, std::vector<std::string> const& elementNames);

        /** This declares an output to the dispatcher, as well as the expected
         * number of elements.
         *
         * If non-zero, the number of elements is used for (1) consistency
         * checking and (2) pre-allocating the needed arrays.
         */
        ChannelID addOutput(std::string const& name = "", size_t size = 0);

        /** Returns the ID of an input from its name
         */
        ChannelID getInputByName(std::string const& name) const;

        /** Returns the ID of an output from its name
         */
        ChannelID getOutputByName(std::string const& name) const;

        /** Returns the Output object associated with the given ID
         */
        Output<T> &getOutput(ChannelID id);
        
        /** This declares a mapping from some elements on a given input and some
         * elements on a given output
         */
        void addDispatch(
                ChannelID input,  ElementSelection<T> const& inputElements,
                ChannelID output, ElementSelection<T> const& outputElements,
                bool defer_output=false);

        /** @overload
         */
        void addDispatch(std::string const& input,
                ElementSelection<T> const& inputElements,
                std::string const& output,
                ElementSelection<T> const& outputElements,
                bool defer_output=false);

        /** Pushes a sample on a given input
         *
         * The outputs for which there is a dispatch are going to be updated
         */
        void write(ChannelID input,
                base::NamedVector<T> const& sample, base::Time time=base::Time::now());

        /** @overload
         */
        void write(std::string const& input,
                base::NamedVector<T> const& sample, base::Time time=base::Time::now());

        /** Reads a given output channel
         *
         * @return true if this channel had been updated since the last read,
         *   and false otherwise. The sample is not modified if the channel was
         *   not updated
         */
        bool read(ChannelID output, base::NamedVector<T>& sample);
        bool read(ChannelID output, base::NamedVector<T>& sample, base::Time& time);

        /** @overload
         */
        bool read(std::string const& name, base::NamedVector<T>& sample);
        bool read(std::string const& name, base::NamedVector<T>& sample, base::Time& time);

        /** Resets the internal tracking state without changing the
         * configuration state
         */
        void reset();
    };
}

#endif

