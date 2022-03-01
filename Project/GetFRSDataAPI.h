extern	"C"
{
    DWORD   WINAPI  GetCurrMonitData(unsigned char* FactolinkName, unsigned char* MonitDataBuffer, DWORD BufferSize);
    DWORD   WINAPI  GetCurrMonitDataEx(unsigned char* FactolinkName, unsigned char* MonitDataBuffer, DWORD BufferSize);
    DWORD   WINAPI  GetCurrMonitDataEx2(unsigned char* FactolinkName, unsigned char* MonitDataBuffer, DWORD BufferSize);
    DWORD   WINAPI  GetCurrMonitDataByID(DWORD dwMachineID, unsigned char* MonitDataBuffer, DWORD BufferSize);
    DWORD   WINAPI  GetCurrMonitDataByID2(DWORD dwMachineID, unsigned char* MonitDataBuffer, DWORD BufferSize);

    DWORD   WINAPI  GetCurrMoldFileName(unsigned char* FactolinkName, unsigned char* NameBuffer, DWORD NameBufferSize);
    DWORD   WINAPI  GetCurrMoldFileNameByID(DWORD dwMachineID, unsigned char* NameBuffer, DWORD NameBufferSize);

    DWORD   WINAPI  GetCurrParamData(unsigned char* FactolinkName, unsigned char** ParamDataBuffer, DWORD BufferSize);
}