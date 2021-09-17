#include <boost/test/unit_test.hpp>
#include <dispatcher_base/Dispatcher.hpp>

using namespace dispatcher_base;

BOOST_AUTO_TEST_CASE(it_should_be_able_to_resolve_the_names)
{
    base::NamedVector<T> joints;
    joints.names.push_back("0");
    joints.names.push_back("1");
    joints.names.push_back("2");

    ElementSelection sel;
    sel.byName.push_back("2");
    sel.byName.push_back("0");
    sel.resolveNames(joints);
    BOOST_REQUIRE_EQUAL(2, sel.byIndex.size());
    BOOST_REQUIRE_EQUAL(2, sel.byIndex[0]);
    BOOST_REQUIRE_EQUAL(0, sel.byIndex[1]);

}

