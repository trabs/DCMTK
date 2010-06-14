// Module:  Log4CPLUS
// File:    pointer.cxx
// Created: 6/2001
// Author:  Tad E. Smith
//
//
// Copyright (C) Tad E. Smith  All rights reserved.
//
// This software is published under the terms of the Apache Software
// License version 1.1, a copy of which has been included with this
// distribution in the LICENSE.APL file.
//

#include "dcmtk/oflog/streams.h"
#include "dcmtk/oflog/helpers/pointer.h"
#include "dcmtk/oflog/helpers/threads.h"
//#include <assert.h>
#define INCLUDE_CASSERT
#include "dcmtk/ofstd/ofstdinc.h"


namespace log4cplus { namespace helpers {


///////////////////////////////////////////////////////////////////////////////
// log4cplus::helpers::SharedObject dtor
///////////////////////////////////////////////////////////////////////////////

SharedObject::~SharedObject()
{
    assert(count == 0);
    LOG4CPLUS_MUTEX_FREE( access_mutex );
}



///////////////////////////////////////////////////////////////////////////////
// log4cplus::helpers::SharedObject public methods
///////////////////////////////////////////////////////////////////////////////

void
SharedObject::addReference() const
{
    LOG4CPLUS_BEGIN_SYNCHRONIZE_ON_MUTEX( access_mutex )
        assert (count >= 0);
        ++count;
    LOG4CPLUS_END_SYNCHRONIZE_ON_MUTEX;
}


void
SharedObject::removeReference() const
{
    bool destroy = false;
    LOG4CPLUS_BEGIN_SYNCHRONIZE_ON_MUTEX( access_mutex );
        assert (count > 0);
        if (--count == 0)
            destroy = true;
    LOG4CPLUS_END_SYNCHRONIZE_ON_MUTEX;
    if (destroy)
        delete this;
}


} } // namespace log4cplus { namespace helpers
