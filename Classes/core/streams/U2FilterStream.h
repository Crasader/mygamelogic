//
//  CRemoteMsgManager.h
//  myGame
//
//  Created by jiang on 13-7-23.
//
//
#ifndef __U2FilterStream__
#define __U2FilterStream__


#include "U2Prerequisites.h"
#include "U2STLRedefined.h"
#include "U2Stream.h"


U2EG_NAMESPACE_BEGIN


class FilterInStream : public InStream
{
public:
    FilterInStream(InStream* in);
    virtual ~FilterInStream();

    virtual u2int32 read() override;

    virtual u2int32 read(u2byte* s, std::streamsize n) override;

    virtual std::streamoff skip(std::streamoff off) override;

    virtual void close() override;

protected:
    std::unique_ptr<InStream> m_pIn;

};


U2EG_NAMESPACE_END

#endif /* defined(__U2FilterStream__) */
