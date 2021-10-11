rock_library(dispatcher_base
    SOURCES "" #Output.cpp Input.cpp SingleDispatch.cpp Dispatcher.cpp
    HEADERS Output_impl.hpp Input_impl.hpp SingleDispatch_impl.hpp Dispatcher_impl.hpp Output.hpp Input.hpp SingleDispatch.hpp Dispatcher.hpp ElementSelection.hpp
    DEPS_PKGCONFIG base-types)

