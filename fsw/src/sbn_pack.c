/************************************************************************
 * NASA Docket No. GSC-19,200-1, and identified as "cFS Draco"
 *
 * Copyright (c) 2023 United States Government as represented by the
 * Administrator of the National Aeronautics and Space Administration.
 * All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License. You may obtain
 * a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ************************************************************************/

#include "sbn_pack.h"
#include <string.h> /* memcpy */

bool SBN_Pack_Init(SBN_Pack_t *PackPtr, void *Buf, size_t BufSz, bool ClearFlag)
{
    PackPtr->Buf     = Buf;
    PackPtr->BufSz   = BufSz;
    PackPtr->BufUsed = 0;
    if (ClearFlag)
    {
        memset(Buf, 0, BufSz);
    } /* end if */
    return true;
} /* end SBN_Pack_Init() */

bool SBN_Pack_Data(SBN_Pack_t *PackPtr, void *DataBuf, size_t DataBufSz)
{
    if (PackPtr->BufUsed + DataBufSz > PackPtr->BufSz)
    {
        /* print an error? */
        return false;
    }

    memcpy((uint8 *)PackPtr->Buf + PackPtr->BufUsed, DataBuf, DataBufSz);
    PackPtr->BufUsed += DataBufSz;

    return true;
} /* end SBN_Pack_Data() */

bool SBN_Pack_UInt8(SBN_Pack_t *PackPtr, uint8 Data)
{
    return SBN_Pack_Data(PackPtr, &Data, sizeof(Data));
} /* end SBN_Pack_UInt8() */

bool SBN_Pack_UInt16(SBN_Pack_t *PackPtr, uint16 Data)
{
    uint16 D = CFE_MAKE_BIG16(Data);
    return SBN_Pack_Data(PackPtr, &D, sizeof(D));
} /* end SBN_Pack_UInt16() */

bool SBN_Pack_Int16(SBN_Pack_t *PackPtr, int16 Data)
{
    int16 D = CFE_MAKE_BIG16(Data);
    return SBN_Pack_Data(PackPtr, &D, sizeof(D));
} /* end SBN_Pack_Int16() */

bool SBN_Pack_UInt32(SBN_Pack_t *PackPtr, uint32 Data)
{
    uint32 D = CFE_MAKE_BIG32(Data);
    return SBN_Pack_Data(PackPtr, &D, sizeof(D));
} /* end SBN_Pack_UInt32() */

bool SBN_Pack_Time(SBN_Pack_t *PackPtr, OS_time_t Data)
{
    return SBN_Pack_Data(PackPtr, &Data, sizeof(Data));
} /* end SBN_Pack_Time() */

bool SBN_Pack_MsgID(SBN_Pack_t *PackPtr, CFE_SB_MsgId_t Data)
{
    uint32 D;
    D = CFE_MAKE_BIG32(CFE_SB_MsgIdToValue(Data));
    return SBN_Pack_Data(PackPtr, &D, sizeof(D));
} /* end SBN_Pack_MsgID() */

bool SBN_Unpack_Data(SBN_Pack_t *PackPtr, void *DataBuf, size_t Sz)
{
    if (PackPtr->BufUsed + Sz > PackPtr->BufSz)
    {
        return false;
    }

    memcpy(DataBuf, (uint8 *)PackPtr->Buf + PackPtr->BufUsed, Sz);

    PackPtr->BufUsed += Sz;

    return true;
} /* end SBN_Unpack_Data() */

bool SBN_Unpack_UInt8(SBN_Pack_t *PackPtr, uint8 *DataBuf)
{
    return SBN_Unpack_Data(PackPtr, DataBuf, sizeof(*DataBuf));
} /* end SBN_Unpack_UInt8() */

bool SBN_Unpack_UInt16(SBN_Pack_t *PackPtr, uint16 *DataBuf)
{
    uint16 D;
    if (!SBN_Unpack_Data(PackPtr, &D, sizeof(D)))
    {
        return false;
    }
    *DataBuf = CFE_MAKE_BIG16(D);
    return true;
} /* end SBN_Unpack_UInt16() */

bool SBN_Unpack_Int16(SBN_Pack_t *PackPtr, int16 *DataBuf)
{
    int16 D;
    if (!SBN_Unpack_Data(PackPtr, &D, sizeof(D)))
    {
        return false;
    }
    *DataBuf = CFE_MAKE_BIG16(D);
    return true;
} /* end SBN_Unpack_Int16() */

bool SBN_Unpack_UInt32(SBN_Pack_t *PackPtr, uint32 *DataBuf)
{
    uint32 D;
    if (!SBN_Unpack_Data(PackPtr, &D, sizeof(D)))
    {
        return false;
    }
    *DataBuf = CFE_MAKE_BIG32(D);
    return true;
} /* end SBN_Unpack_UInt32() */

bool SBN_Unpack_Time(SBN_Pack_t *PackPtr, OS_time_t *DataBuf)
{
    OS_time_t D;
    if (!SBN_Unpack_Data(PackPtr, &D, sizeof(D)))
    {
        return false;
    }
    *DataBuf = D;
    return true;
} /* end SBN_Unpack_Time() */

bool SBN_Unpack_MsgID(SBN_Pack_t *PackPtr, CFE_SB_MsgId_t *DataBuf)
{
    uint32 D;
    if (!SBN_Unpack_Data(PackPtr, &D, sizeof(D)))
    {
        return false;
    }
    *DataBuf = CFE_SB_ValueToMsgId(CFE_MAKE_BIG32(D));
    return true;
} /* end SBN_Unpack_MsgID() */
