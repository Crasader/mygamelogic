//
//  CRemoteMsgManager.cpp
//  myGame
//
//  Created by jiang on 13-7-23.
//
//

#include "U2FilterStream.h"



U2EG_NAMESPACE_USING


//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
FilterInStream::FilterInStream(InStream* in)
: InStream()
{
    m_pIn = std::make_unique<InStream>();
}
//-----------------------------------------------------------------------
FilterInStream::~FilterInStream()
{
}
//-----------------------------------------------------------------------
u2int32 FilterInStream::read()
{
    assert(m_pIn.get());
    return m_pIn->read(); 
}
//-----------------------------------------------------------------------
u2int32 FilterInStream::read(u2byte* s, std::streamsize n)
{
    assert(m_pIn.get());
    return m_pIn->read(s, n);
}
//-----------------------------------------------------------------------
std::streamoff FilterInStream::skip(std::streamoff off)
{
    assert(m_pIn.get());
    return m_pIn->skip(off);
}
//-----------------------------------------------------------------------
void FilterInStream::close()
{
    assert(m_pIn.get());
    return m_pIn->close();
}