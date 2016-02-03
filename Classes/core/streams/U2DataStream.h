//
//  CRemoteMsgManager.h
//  myGame
//
//  Created by jiang on 13-7-23.
//
//
#ifndef __U2DataStream__
#define __U2DataStream__


#include "U2Prerequisites.h"
#include "U2STLRedefined.h"
#include "U2FilterStream.h"



static void flipEndian(void * pData, size_t size, size_t count);
static void flipEndian(void * pData, size_t size);



U2EG_NAMESPACE_BEGIN


class DataInStream : public FilterInStream
{
public:
    DataInStream(InStream* in, u2int32 endian = U2_ENDIAN_LITTLE);
    virtual ~DataInStream();

    virtual bool readBool();

    virtual u2int8 readInt8();
    virtual u2int16 readInt16();
    virtual u2int32 readInt32();
    virtual u2int64 readInt64();

    virtual u2uint8 readUint8();
    virtual u2uint16 readUint16();
    virtual u2uint32 readUint32();
    virtual u2uint64 readUint64();

    virtual float readFloat();
    virtual double readDouble();

    virtual u2::Char readChar();
    virtual u2int32 readUTFChar(u2char* utf);
    virtual u2::String readUTFString();

protected:
    void _flipEndian(void * pData, size_t size, size_t count);
    
    


protected:
    u2int32     m_nEndian;
};


U2EG_NAMESPACE_END

#endif /* defined(__U2FilterStream__) */
