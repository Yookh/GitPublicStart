/*******************************************************************
 *
 *    DESCRIPTION: MRI G-AMP 장비의 프로그램에 사용되는 각종 파라메터 상수들을 관리하는 파일.
 *				   최대한 퍼포먼스를 올려야 하는 프로그램이기에 상수 계산 값을 미리 정의해 둔다.
 *
 *    AUTHOR: K.H.Yoo
 *
 *    HISTORY:  2014.01.20 coding Start
 *				2014.01.22 real parameter added
 *				2016.05.04 Log data added
 *******************************************************************/
#define PROFILE_NUMBER		20
#define LOG_BUFFER_SIZE		400

// byte_Order : little endian.
struct VAR_Word32
{
	Uint32	wordL:16;
	Uint32	wordH:16;
};

union BIT_CON_2WORD
{
	Uint32		all;
	struct 		VAR_Word32	word;
};

typedef struct Prof
{
	Uint16 On_time[PROFILE_NUMBER];
	Uint16 Off_time[PROFILE_NUMBER];
	long   Po_ref[PROFILE_NUMBER];
	Uint16 Split_num;
	long	   Gradiant[PROFILE_NUMBER];
}_profile;

typedef struct DebugData
{
	Uint16	log1[LOG_BUFFER_SIZE];
	Uint16	log2[LOG_BUFFER_SIZE];
	Uint16	log3[LOG_BUFFER_SIZE];
	Uint16	LogIndex;
	Uint16	logEndIdx;
}DebugingVar;

typedef struct c1_local
{
	int 	ej_global_test, ej_global_test2;
	int 	BUFF[SET_NUMBER];
    unsigned int adc_count;
    int 	run_flag, reset_flag;
    long	ADC_Buf[ADC_NUMBER];
    int 	ADC_Avg[ADC_NUMBER];
    int		Vo_result, Io_result;
    int		AD_read_flag;
    long long	PoBuf[2];
    long	fault_status;
    Uint16	Po_cnt[2];
    Uint16	Calc_flag;
    Uint16  ArcCheckEna;

    union BIT_CON_2WORD	LogMap1, LogMap2, LogMap3;
    union BIT_CON_2WORD VarMap;

    Uint32 VarWRData;
    Uint16 VarReqflag;
    Uint16 VarWrflag;

    Uint16 LogAccess;

    _profile profile;
}C1_2;

typedef struct c2_local
{
	int		ADC_Avg[3];
	Uint32	fault_status;
	int     Ir_Con_Avg[3];
	int		ej_test[3];
	Uint16	prof_Po_Ref;
	Uint16  prof_Po_slop;
	Uint16	poBufIdx;
	DebugingVar DebugLog;
	Uint16	VarReturn;
	Uint16 	ArcManagementFlag;
	Uint16 	ArcCount;
	Uint16	ArcTotalCnt;

}C2_1;

typedef struct C_DATA
{
	int sys_status;
	int	vo_data;
	int fault_st;
	int warning_st;
	int operation_cmd;
	Uint16 vo_ref_can;
	int io_data;
	int comm_check;
	Uint16 io_ref_can;
	Uint16 Alive;
} comm_Data;




