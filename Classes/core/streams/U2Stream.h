//
//  CRemoteMsgManager.h
//  myGame
//
//  Created by jiang on 13-7-23.
//
//
#ifndef __U2Stream__
#define __U2Stream__


#include "U2Prerequisites.h"
#include "U2STLRedefined.h"


U2EG_NAMESPACE_BEGIN


class InStream
{
public:
    InStream();
    virtual ~InStream();

    //virtual std::streamsize read(u2::Char* s, std::streamsize n) = 0;

    /** Reads a single byte from this stream and returns it as an integer in the
        range from 0 to 255. Returns EOF if the end of the stream has been
        reached.
        */
    virtual u2int32 read() { return 0; };

    /** Reads up to {@code n} bytes from this stream and stores them in
        the byte array {@code s}.
        Returns the number of bytes actually read or EOF if the end of the stream
        has been reached.
    */
    virtual u2int32 read(u2byte* s, std::streamsize n);

    /** Skips at most {@code off} bytes in this stream. The number of actual
        bytes skipped may be anywhere between 0 and {@code off}. If
        {@code off} is negative, this method does nothing and returns 0, but
        some subclasses may throw.
    
        <p>Note the "at most" in the description of this method: this method may
        choose to skip fewer bytes than requested. Callers should <i>always</i>
        check the return value.
    
        <p>This default implementation reads bytes into a temporary buffer. Concrete
        subclasses should provide their own implementation.
        
        @return the number of bytes actually skipped.
    */
    virtual std::streamoff skip(std::streamoff off);

    //virtual stream_offset skip(stream_offset off, std::ios_base::seekdir way) = 0;

    //virtual std::streamsize readline(u2::Char* s, std::streamsize maxCount, const u2::Char* delim = _TT("\n")) = 0;

    virtual void close() {};

};


U2EG_NAMESPACE_END

#endif /* defined(__U2InStream__) */
