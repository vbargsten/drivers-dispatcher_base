#ifndef DISPATCHER_BASE_OUTPUT_HPP
#define DISPATCHER_BASE_OUTPUT_HPP

#include <vector>
#include <string>
#include <base/Time.hpp>
#include <base/NamedVector.hpp>

namespace dispatcher_base
{
    /** Configuration of an output on Dispatcher
     */
    template <typename T> class Output
    {
        /** The output name
         */
        std::string mName;

        base::NamedVector<T> mState;
        base::Time mLatestUpdateTime;
        
        /** If true, this output should be exported the next time
         * Dispatcher::read is called for it
         */
        bool mIsNew;
        /** If true, all elements in mState have been updated at least once.
         * isNew will return false until it is the case
         */
        bool mFullyInitialized;
        /** A count of elements that need to be updated before the element has been
         * fully updated
         */
        size_t mFullUpdateCounter;
        /** A element-by-element flag marking the elements as having been updated
         * since the last call to Dispatcher::read or not
         */
        std::vector<bool> mUpdatedElements;
        /** A element-by-element update flag
         */
        std::vector<base::Time> mUpdateTime;

    public:
        Output(std::string const& name = "");

        std::string getName() const;

        /** Updates a element on this output */
        void updateJoint(size_t elementIdx, base::Time const& time, T const& sample, bool needsRead=true);

        /** Read the current element state, resetting all the 'new' flags */
        base::NamedVector<T> read();

        bool read(base::NamedVector<T>&, base::Time&);

        /** The list of element names */
        std::vector<std::string> getNames() const;

        /** Returns the list of indexes that correspond to the requested names
         *
         * @throws base::NamedVector<T>::InvalidName if one of the names does not exist
         */
        std::vector<size_t> mapNamesToIndex(std::vector<std::string> const& names) const;

        /** The count of elements */
        size_t size() const;

        /** Resize while setting the list of element names at the same time */
        void resize(std::vector<std::string> const& elementNames);

        /** Declares the number of elements this output will generate */
        void resize(size_t size);

        /** Resets the internal tracking state to pristine, without changing
         * configuration
         */
        void reset();

        /** Returns true if the current sample is new, i.e. if it has been
         * updated since the last call to read()
         */
        bool isNew() const;

        /** Returns true if all elements of the current sample have been updated
         * since the last call to read()
         */
        bool isFullyUpdated() const;
    };
    
    
}

#endif

