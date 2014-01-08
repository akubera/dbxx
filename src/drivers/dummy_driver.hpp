/* 
 * File:   dummy_driver.hpp
 * Author: andrewkubera
 *
 * Created on January 8, 2014, 6:16 PM
 */

#ifndef DUMMY_DRIVER_HPP
#define	DUMMY_DRIVER_HPP

#include "../driver.hpp"

class dummy_driver : public cppdb::Driver {
public:
    dummy_driver();
    dummy_driver(const dummy_driver& orig);
    virtual ~dummy_driver();
private:

};

#endif	/* DUMMY_DRIVER_HPP */

