====
dbxx
====

A database interface library using modern C++ (C++11 and later) features.

With the use of variadic templates, type-safe database queries can be made
using C++11. This library tries to make use of this feature and provide an
interface to multiple database backends.

This project was originally called c11db, and was meant to implement the 
database connections directly, loading driver objects dynamically.
The structure was changed to be only headers which define template classes and
functions that work with other standardized connection libraries, such as ODBC.
This reorganization was renamed to dbxx, and    is a header only 

Installation
------------

As a header-only library, dbxx only requires you to place the `dbxx` directory
anywhere your build system looks for header file.

Using
-----

.. code:: cpp

  // include main dbxx file
  #include <dbxx/dbxx.hpp>


Testing
-------

If you want to help develop dbxx, please write some tests for your code in the
`test` directory. This requires the C++ test framework bandit_ to be installed
on your system.
The Makefile in the test directory requires the `BANDIT_HEADER_DIR` environment
variable to point to the bandit directory containing `bandit.h`, which defaults
to the test directory.

To install bandit and run tests run this: 

.. code::

   git clone --recursive --depth=1 --branch=v2.0.0 https://github.com/joakimkarlsson/bandit
   mv bandit/bandit test
   rm -rf bandit

   cd test
   make


More information on developing/testing will come later.


License
-------

This library is dual-licensed under the MIT & Apache v2.0 licenses; this makes it
compliant with many open source licenses, including copyleft licenses with GPL.

Dbxx is developed using the git versioning system, with branch 'master' being the
stable releases, 'dev' being the semi-stable development branch, and very-unstable
feature branches should be created with the name 'feature/foo'.

Contributions are welcome! 


.. _bandit: http://banditcpp.org

