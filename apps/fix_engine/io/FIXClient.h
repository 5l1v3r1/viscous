/*
 * FIXClient.h
 *
 *  Created on: 1 Sep 2014
 *      Author: Wei Liew (wei@onesixeightsolutions.com)
 *
 *  Copyright Wei Liew 2012 - 2014.
 *  Distributed under the Boost Software License, Version 1.0.
 *  (See http://www.boost.org/LICENSE_1_0.txt)
 *
 */

#ifndef FIXCLIENT_H_
#define FIXCLIENT_H_

#include "FIXTraits.h"
#include "FIXSession.h"

#include <type_traits>

using namespace vf_common;

namespace vf_fix
{

template<typename FIXTraitsType = DefaultFIXInitiatorTraits>
class FIXClient : public FIXSession<FIXClient<FIXTraitsType>, FIXTraitsType>
{
public:
    typedef FIXSession<FIXClient<FIXTraitsType>, FIXTraitsType> BaseType;

    // message type traits
    typedef typename FIXTraitsType::MsgTraitsType::LogonMsgType         LogonMsgType;
    typedef typename FIXTraitsType::MsgTraitsType::LogoutMsgType        LogoutMsgType;
    typedef typename FIXTraitsType::MsgTraitsType::HeartbeatMsgType     HeartbeatMsgType;

    FIXClient()
    : BaseType(*this)
    {
    }

    virtual ~FIXClient()
    {
    }

    void onAppData(typename FIXTraitsType::BufferPtrType msg)
    {
    }

    bool setLogonMsg(LogonMsgType& msg)
    {
        setupFIXMsg(msg);

        return true;
    }

    bool setLogoutMsg(LogoutMsgType& msg)
    {
        setupFIXMsg(msg);

        return true;
    }

    bool setHeartbeatMsg(HeartbeatMsgType& msg)
    {
        setupFIXMsg(msg);

        return true;
    }

    void onLogon()
    {
    }

    void onLogout()
    {
    }

    void onHeartBeat()
    {
    }

    void onConnect()
    {
    }

    void onDisconnect()
    {
    }

private:
    template<typename MsgType>
    void setupFIXMsg(MsgType& msg)
    {
        // TODO - set up comp ids etc

    }

};


} // namespace vf_fix

#endif /* FIXCLIENT_H_ */
