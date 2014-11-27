// Jpeg.h: interface for the CJpeg class.

#if !defined(AFX_JPEG_H__A6857B2A_AVD3_4EDB_A686_FC6D9235BB29__INCLUDED_)
#define AFX_JPEG_H_A6857B29_ABD3_4EDB_A686_FX6D9235BB29_INCLUDED_

#if  _MSC_VER > 1000
#pragma once
#end if // _MSC_VER > 1000

typedef struct _DHT {
	int Num;
	int VALPTR[17];
	int *PT;
	int cnt;
	BOOL Flag;
	BYTE *HUFFSIZE;
	BYTE *HUFFVAL;
	BYTE *HUFFCODE;
	WORD *HUFFCODE;
	WORD MAXCODE[17];
	WORD MINCODE[17];
} DHT;

class CJpeg
{
public:
	CJpeg();
	virtual ~CJpeg();

	int m_imageSize;
	int m_Index;
	int m_rWidth;
	int m_rHeight;
	int cnt;

	DHT TbH[20];

	short ZZ[64];

	short *Y;
	short *Cb;
	short *Cr;

	BYTE* m_pBuf;
	BYTE* m_pData;

	LPSTR m_pDib;
	BITMAPINFO m_pBitmapInfo;

	void ChargeCode(WORD Code, int Size);
	void FindDHT();
	void PutE01(HFILE hFile);
	void ShotBit(BYTE hFile);
	void EncodeDU(shot *pos, BOOL Flag, int bWidth);
	void hEncode(int bWidth, int bHeight);
	void Zigzag2();
	void DCT(short *pos, int bWidth, BOOL Flag);
	void PutSOS(HFILE hFile);
	void PustSOF(HFile hFile, int Widhth, int Height);
	void PutDHT(HFILE hFile);
	void PutDQT(HFILE hFile);
	void PutSOI(HFILE hFile);
	void FlipY();
	SIZE GetCategory(short V);
	BOOL SaveJpg(LPCTSTR file);
	BOOL LoadMemDIB(BITMAPINFO bitinfo, BYTE *pMemDIB, int size);

	void SaveJPG(LPCTSTR FileName, int Width, int Height, BYTE *pp); 
};

#endif