
#ifndef COMMON_H
#define COMMON_H

#include "ascii.h"
#include "linktype.h"

// STL
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <map>

// BOOST
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/convenience.hpp>
#include <boost/function.hpp>
#include <boost/format.hpp>
#include <boost/bind.hpp>
#include <boost/any.hpp>
#include <boost/shared_ptr.hpp>

#ifdef VERBOSE
#define OUTPUT(a) std::cout << a << std::endl;
#else
#define OUTPUT(a)
#endif

#ifndef WIN32
#include <dlfcn.h>
#endif

#endif // !COMMON_H
