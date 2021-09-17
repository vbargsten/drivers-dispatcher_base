#include <dispatcher_base/Dispatcher.hpp>

using namespace dispatcher_base;

template <typename T>
typename  Dispatcher<T>::ChannelID Dispatcher<T>::addInput(std::string const& name)
{
    mInputs.push_back(Input<T>(name));
    return mInputs.size() - 1;
}

template <typename T>
typename Dispatcher<T>::ChannelID Dispatcher<T>::addOutput(std::string const& name, size_t size)
{
    mOutputs.push_back(Output<T>(name));
    mOutputs.back().resize(size);
    return mOutputs.size() - 1;
}

template <typename T>
typename Dispatcher<T>::ChannelID Dispatcher<T>::addOutput(std::string const& name, std::vector<std::string> const& elementNames)
{
    mOutputs.push_back(Output<T>(name));
    mOutputs.back().resize(elementNames);
    return mOutputs.size() - 1;
}

template <typename T>
typename Dispatcher<T>::ChannelID Dispatcher<T>::getInputByName(std::string const& name) const
{
    for (size_t i = 0; i < mInputs.size(); ++i)
        if (mInputs[i].getName() == name)
            return i;
    throw std::runtime_error("there is no declared input named " + name);
}

template <typename T>
typename Dispatcher<T>::ChannelID Dispatcher<T>::getOutputByName(std::string const& name) const
{
    for (size_t i = 0; i < mOutputs.size(); ++i)
        if (mOutputs[i].getName() == name)
            return i;
    throw std::runtime_error("there is no declared output named " + name);
}

template <typename T>
Output<T>& Dispatcher<T>::getOutput(ChannelID id)
{
    return mOutputs[id];
}

template <typename T>
void Dispatcher<T>::addDispatch(
        ChannelID input,  ElementSelection<T> const& inputElements,
        ChannelID output, ElementSelection<T> const& outputElements,
        bool defer_output)
{
    if (input >= mInputs.size())
        throw std::out_of_range("given input channel ID is out of bounds");
    if (output >= mOutputs.size())
        throw std::out_of_range("given output channel ID is out of bounds");

    SingleDispatch<T> dispatch;
    dispatch.input = inputElements;
    dispatch.output_channel = &mOutputs[output];
    dispatch.output = outputElements;
    // The names should be resolv-able right now
    dispatch.output.resolveNames(mOutputs[output].read());
    dispatch.defer_output = defer_output;
    mInputs[input].dispatches.push_back(dispatch);
}

template <typename T>
void Dispatcher<T>::addDispatch(
        std::string const& input, ElementSelection<T> const& inputElements,
        std::string const& output, ElementSelection<T> const& outputElements,
        bool defer_output)
{
    return addDispatch(
        getInputByName(input), 
        inputElements,
        getOutputByName(output),
        outputElements,
        defer_output
    );
}

template <typename T>
void Dispatcher<T>::write(ChannelID input, base::NamedVector<T> const& sample)
{
    if (input >= mInputs.size())
        throw std::out_of_range("given input channel ID is out of bounds");

    mInputs[input].write(sample);
}

template <typename T>
void Dispatcher<T>::write(std::string const& input, base::NamedVector<T> const& sample)
{
    write(getInputByName(input), sample);
}

template <typename T>
bool Dispatcher<T>::read(ChannelID output, base::NamedVector<T>& sample)
{
    if (output >= mOutputs.size())
        throw std::out_of_range("given output channel ID is out of bounds");

    if (mOutputs[output].isNew())
    {
        sample = mOutputs[output].read();
        return true;
    }

    else
    {
        return false;
    }

}

template <typename T>
bool Dispatcher<T>::read(std::string const& name, base::NamedVector<T>& sample)
{
    return read(getOutputByName(name), sample);
}

template <typename T>
void Dispatcher<T>::reset()
{
    for (size_t i = 0; i < mInputs.size(); ++i)
        mInputs[i].reset();
    for (size_t i = 0; i < mOutputs.size(); ++i)
        mOutputs[i].reset();
}


