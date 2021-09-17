rock_library(dispatcher_base
    SOURCES Output.cpp Input.cpp SingleDispatch.cpp Dispatcher.cpp
    HEADERS Output.hpp Input.hpp SingleDispatch.hpp Dispatcher.hpp ElementSelection.hpp
    DEPS_PKGCONFIG base-types)

