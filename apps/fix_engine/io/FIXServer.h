/*
 * FIXServer.h
 *
 *  Created on: 1 Sep 2014
 *      Author: Wei Liew (wei@onesixeightsolutions.com)
 *
 *  Copyright Wei Liew 2012 - 2014.
 *  Distributed under the Boost Software License, Version 1.0.
 *  (See http://www.boost.org/LICENSE_1_0.txt)
 *
 */

#ifndef FIXSERVER_H_
#define FIXSERVER_H_

#include <logging/StdoutSink.h>
#include <logging/Log.h>
#include <signals/StaticSignal.h>
#include <buffers/MessageBuilder.h>

#include "apps/fix_engine/message/FIXMessagePoolDefs.h"
#include "apps/fix_engine/io/FIXAcceptor.h"
#include "FIXServerSession.h"
#include <io/TcpAcceptorHandler.h>
#include "FIXTraits.h"

#include <type_traits>

using namespace vf_common;

namespace vf_fix
{

template<typename FIXTraitsType = DefaultFIXAcceptorTraits>
class FIXServer
{
public:
    typedef TcpAcceptorHandler<FIXServerSession<FIXTraitsType>> AcceptorHandlerType;
    typedef typename AcceptorHandlerType::AcceptorPtrType       AcceptorPtrType;

    FIXServer(const std::string& senderCompId,
              const std::string& targetCompId,
              const std::string& senderSubId = std::string(),
              const std::string& targetSubId = std::string())
    : _handlerWork(_io)
    , _logger(_logSink, LogDebug) // TODO - configurable ?
    , _acceptorHandler(_io, _logger)
    , _senderCompId(senderCompId)
    , _targetCompId(targetCompId)
    , _senderSubId(senderSubId)
    , _targetSubId(targetSubId)
    {
        _acceptorHandler.newAcceptorSignal().subscribe(this);
    }

    virtual ~FIXServer()
    {
    }

    void onData(AcceptorPtrType& acceptor)
    {
        acceptor->setSenderCompID(_senderCompId);
        acceptor->setTargetCompID(_targetCompId);
        acceptor->setSenderSubID(_senderSubId);
        acceptor->setTargetSubID(_targetSubId);
    }

    bool run(const std::string& host, const std::string& port, bool blocking = false)
    {
        if(_handlerThread)
        {
            return false;
        }

        if(blocking)
        {
            _acceptorHandler.start(host, port);
            _io.run();
        }
        else
        {
            _handlerThread.reset(new std::thread([this](){
                _io.run();
            }));
            _handlerThread->detach();
            return _acceptorHandler.start(host, port);
        }

        return false;
    }

private:
    std::unique_ptr<std::thread>            _handlerThread;
    boost::asio::io_service                 _io;
    boost::asio::io_service::work           _handlerWork;
    typename FIXTraitsType::LogSinkType     _logSink;
    typename FIXTraitsType::LoggerType      _logger;
    AcceptorHandlerType                     _acceptorHandler;
    std::string                             _senderCompId;
    std::string                             _targetCompId;
    std::string                             _senderSubId;
    std::string                             _targetSubId;
};

} // vf_fix



#endif /* FIXSERVER_H_ */
