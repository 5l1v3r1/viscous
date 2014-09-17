/*
 * FIXClient_test.cpp
 *
 *  Created on: 2 Sep 2014
 *      Author: Wei Liew (wei@onesixeightsolutions.com)
 *
 *  Copyright Wei Liew 2012 - 2014.
 *  Distributed under the Boost Software License, Version 1.0.
 *  (See http://www.boost.org/LICENSE_1_0.txt)
 *
 */

#define BOOST_TEST_MODULE Io_test
#include <boost/test/included/unit_test.hpp>
#include <sys/syscall.h>
#include <stdio.h>
#include <thread>

#include "apps/fix_engine/message/FIXMessageDecoder.h"
#include "apps/fix_engine/static_dictionary/gen/FieldDefsGen44.h"
#include "apps/fix_engine/io/FIXClient.h"

using namespace vf_common;
using namespace vf_fix;

BOOST_AUTO_TEST_CASE( FIXClient_test_1 )
{
    BOOST_TEST_MESSAGE("Running test case FIXClient_test_1");

    FIXClient<DefaultFIXTraits> client1;

}

