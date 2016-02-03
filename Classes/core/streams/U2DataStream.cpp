//
//  CRemoteMsgManager.cpp
//  myGame
//
//  Created by jiang on 13-7-23.
//
//

#include "U2DataStream.h"

#include "U2Stream.h"
#include "U2CodeCvt.h"


//---------------------------------------------------------------------
//---------------------------------------------------------------------
void flipEndian(void * pData, size_t size, size_t count)
{
    //#if U2_ENDIAN == U2_ENDIAN_BIG
    for (unsigned int index = 0; index < count; index++)
    {
        flipEndian((void *)((long)pData + (index * size)), size);
    }
    //#endif
}
//---------------------------------------------------------------------
void flipEndian(void * pData, size_t size)
{
    //#if U2_ENDIAN == U2_ENDIAN_BIG
    char swapByte;
    for (unsigned int byteIndex = 0; byteIndex < size / 2; byteIndex++)
    {
        swapByte = *(char *)((long)pData + byteIndex);
        *(char *)((long)pData + byteIndex) = *(char *)((long)pData + size - byteIndex - 1);
        *(char *)((long)pData + size - byteIndex - 1) = swapByte;
    }
    //#endif
}



U2EG_NAMESPACE_USING



//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
DataInStream::DataInStream(InStream* in, u2int32 endian)
: FilterInStream(in)
, m_nEndian(endian)
{
}
//-----------------------------------------------------------------------
DataInStream::~DataInStream()
{
}
//-----------------------------------------------------------------------
void DataInStream::_flipEndian(void * pData, size_t size, size_t count)
{
    if (m_nEndian != U2_ENDIAN)
    {
        flipEndian(pData, size, count);
    }
}
//-----------------------------------------------------------------------
bool DataInStream::readBool()
{
    u2int32 val = m_pIn->read();
    if (val < 0)
    {
        assert(0);
    }
    return val > 0;
}
//-----------------------------------------------------------------------
u2int8 DataInStream::readInt8()
{
    u2int32 val = m_pIn->read();
    if (val < 0)
    {
        assert(0);
    }
    return (u2int8)val;
}
//-----------------------------------------------------------------------
u2int16 DataInStream::readInt16()
{
    u2int16 val = 0;
    u2int32 nResult = m_pIn->read((u2byte*)(&val), sizeof(u2int16));
    if (nResult < 0)
    {
        assert(0);
    }
    _flipEndian(&val, sizeof(u2int16), 1);
    return val;
}
//-----------------------------------------------------------------------
u2int32 DataInStream::readInt32()
{
    u2int32 val = 0;
    u2int32 nResult = m_pIn->read((u2byte*)(&val), sizeof(u2int32));
    if (nResult < 0)
    {
        assert(0);
    }
    _flipEndian(&val, sizeof(u2int32), 1);
    return val;
}
//-----------------------------------------------------------------------
u2int64 DataInStream::readInt64()
{
    u2int64 val = 0;
    u2int64 nResult = m_pIn->read((u2byte*)(&val), sizeof(u2int64));
    if (nResult < 0)
    {
        assert(0);
    }
    _flipEndian(&val, sizeof(u2int64), 1);
    return val;
}
//-----------------------------------------------------------------------
u2uint8 DataInStream::readUint8()
{
    u2int32 val = m_pIn->read();
    if (val < 0)
    {
        assert(0);
    }
    return (u2uint8)val;
}
//-----------------------------------------------------------------------
u2uint16 DataInStream::readUint16()
{
    u2uint16 val = 0;
    u2int32 nResult = m_pIn->read((u2byte*)(&val), sizeof(u2uint16));
    if (nResult < 0)
    {
        assert(0);
    }
    _flipEndian(&val, sizeof(u2uint16), 1);
    return val;
}
//-----------------------------------------------------------------------
u2uint32 DataInStream::readUint32()
{
    u2uint32 val = 0;
    u2int32 nResult = m_pIn->read((u2byte*)(&val), sizeof(u2uint32));
    if (nResult < 0)
    {
        assert(0);
    }
    _flipEndian(&val, sizeof(u2uint32), 1);
    return val;
}
//-----------------------------------------------------------------------
u2uint64 DataInStream::readUint64()
{
    u2uint64 val = 0;
    u2int32 nResult = m_pIn->read((u2byte*)(&val), sizeof(u2uint64));
    if (nResult < 0)
    {
        assert(0);
    }
    _flipEndian(&val, sizeof(u2uint64), 1);
    return val;
}
//-----------------------------------------------------------------------
float DataInStream::readFloat()
{
    float val = 0;
    u2int32 nResult = m_pIn->read((u2byte*)(&val), sizeof(float));
    if (nResult < 0)
    {
        assert(0);
    }
    return val;
}
//-----------------------------------------------------------------------
double DataInStream::readDouble()
{
    double val = 0;
    u2int32 nResult = m_pIn->read((u2byte*)(&val), sizeof(double));
    if (nResult < 0)
    {
        assert(0);
    }
    return val;
}
//-----------------------------------------------------------------------
u2::Char DataInStream::readChar()
{
    size_t byteCount = sizeof(Char);
    if (byteCount == 4)
    {
        return readInt32();
    }
    else if (byteCount == 2)
    {
        return readInt16();
    }
    else
    {
        assert(0);
        return -1;
    }
}
//-----------------------------------------------------------------------
u2int32 DataInStream::readUTFChar(u2char* utf)
{
    utf[0] = readInt8();
    u2int32 nLen = CodeCvt::utf8_charlen((const char*)utf);
    u2int32 i = 1;
    for (; i < nLen; i++)
    {
        utf[i] = readInt8();
    }
    return i;
}
//-----------------------------------------------------------------------
u2::String DataInStream::readUTFString()
{
    u2uint32 usLen = readUint16();

    u2char* szStr = U2_MALLOC(6 * usLen * sizeof(u2char), MEMCATEGORY_GENERAL);
    size_t pos = 0;
    for (u2uint32 i = 0; i < usLen; i++)
    {
        szStr[pos++] = readInt8();

        u2int32 nByteCount = CodeCvt::utf8_charlen((const char*)(szStr + pos - 1));
        for (u2int32 j = 1; j < nByteCount; j++)
        {
            szStr[pos++] = readInt8();
        }
    }

    size_t byteCount = sizeof(Char);
    if (byteCount == 4 || byteCount == 2)
    {
        u2::Char* wszStr = U2_MALLOC(6 * usLen * sizeof(u2::Char), MEMCATEGORY_GENERAL);
        return CodeCvt::mbstowcs(wszStr, szStr, usLen);
    }
    else
    {
        return szStr;
    }
}