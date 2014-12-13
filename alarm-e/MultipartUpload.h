#include <afxinet.h>

class MultipartUpload{
	MultipartUpload(void);
	~MultipartUpload(void);
	public:
		static void Upload(BYTE*,DWORD);
		static CString join(CString,CString);
		static CString ConvertUTF8toUnicode(char*);
		static UINT UploadThread(LPVOID lpParam);
};