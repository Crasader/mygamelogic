//
//  CRemoteMsgManager.cpp
//  myGame
//
//  Created by jiang on 13-7-23.
//
//

#include "U2Stream.h"



U2EG_NAMESPACE_USING


//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
InStream::InStream()
{
}
//-----------------------------------------------------------------------
InStream::~InStream()
{
}
//-----------------------------------------------------------------------
u2int32 InStream::read(u2byte* s, std::streamsize n)
{
    for (std::streamoff i = 0; i < n; ++i)
    {
        u2int32 c = read();
        if (c == EOF)
        {
            return i == 0 ? EOF : i;
        }
        
        s[i] = (u2byte)c;
    }
    return n;
}
//-----------------------------------------------------------------------
std::streamoff InStream::skip(std::streamoff off)
{
    for (std::streamoff i = 0; i < off; ++i)
    {
        u2int32 c = read();
        if (c == EOF)
        {
            return i == 0 ? EOF : i;
        }
    }
    return off;
}