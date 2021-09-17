#ifndef DISPATCHER_BASE_ELEMENT_SELECTION_HPP
#define DISPATCHER_BASE_ELEMENT_SELECTION_HPP

#include <vector>
#include <string>
#include <base/NamedVector.hpp>

namespace dispatcher_base
{
    /** This represents a subset of elements from a base::NamedVector<T>
     */
    template <typename T>
    struct ElementSelection
    {
        std::vector<int> byIndex;
        std::vector<std::string> byName;

        size_t size() const { return byIndex.size(); };

        void resolveNames(base::NamedVector<T> const& sample)
        {
            if (!byName.empty())
            {
                byIndex.resize(byName.size());
                for (size_t i = 0; i < byName.size(); ++i)
                    byIndex[i] = sample.mapNameToIndex(byName[i]);
            }
        }
    };
}

#endif

