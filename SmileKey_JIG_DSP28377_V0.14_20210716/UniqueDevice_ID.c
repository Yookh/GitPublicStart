/*
 * UniqueDevice_ID.c
 *
 *  Created on: 2021. 6. 23.
 *      Author: YooKH
 */

#define F2837x          1
#define F2806x          0
#define F2803x          0
#define F280x           0

#if(F2837x)
#define __UNIQUE_MSW       0x0703CD
#define __UNIQUE_LSW       0x0703CC
#elif(F2806x)
#define __UNIQUE_MSW       0x000901
#define __UNIQUE_LSW       0x000900
#elif(F2803x)
#define __UNIQUE_MSW       0x000901
#define __UNIQUE_LSW       0x000900
#elif(F280x)
#define __UNIQUE_MSW       0x000809
#define __UNIQUE_LSW       0x000808
#endif

#define   UNIQUE_ID_MS(data)     \
    data = *(int *)__UNIQUE_MSW


#define   UNIQUE_ID_LS(data)     \
    data = *(int *)__UNIQUE_LSW


long GetUniqueID ( void )
{
    int lsw, msw;
    long UniqueID;

    UNIQUE_ID_LS(lsw);
    UNIQUE_ID_MS(msw);

    UniqueID = ((long)msw <<16) | lsw;
    return UniqueID;
}
