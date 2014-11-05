/*
변환이 되면 변환된 한글이 리턴
변환이 안되면 error 스트링이 리턴.
*/

extern "C" __declspec(dllexport)
	char* EngToHanCovert(char* szInput, int nLen);