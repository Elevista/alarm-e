#include <afxinet.h>

class MultipartUpload{
	MultipartUpload(void);
	~MultipartUpload(void);
	public:
		static CString Upload(BYTE*,DWORD,CTime);
		static CString join(CString,CString);
		static CString ConvertUTF8toUnicode(char*);
};