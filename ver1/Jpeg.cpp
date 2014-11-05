#include "stdafx.h"
#include "alarm-e.h"
#include "Jpeg.h"

#include <atlconv.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]= __ FILE __ ;
#define new DEBUG_NEW
#endif

////////////////////////////////////////////////////////////////
//Construction Destruction
////////////////////////////////////////////////////////////////
CJpeg::CJpeg()
{
	m_pData = NULL;
	for(int i=0; i<20; i++)
		TbH[i].Flag= FALSE;
}

CJpeg::~CJpeg()
{
	if(m_pData !=NULL)
		delete[] m_pData;

	for(int i=0; i<20; i++)
	{
		if(TbH[i].FIag)
		{
			delete[] TbH[i].HUFFCODE;
			delete[] TbH[i].HUFFSIZE;
			delete[] TbH[i].HUFFVAL;
		}
	}
	if (m_pDib)
		delete[] m_pDib;
}


BOOL CJpeg::LoadMemDIB(BITMAPINFO bitinfo, BYTE *pMemDIB, int size)
{
	m_pBitmaplnfo = bitinfo;
	m_imageSize = size;

	m_pDib =new char [size];
	::memcpy(m_pDib, pMemDIB, size);

	//////////////////////////////////////////////////////////////////////

	return TRUE;
}
void CJpeg::SaveJPG(LPCTSTR FileName, int Width, int Height, BYTE *pp)
{
	m_rWidth =Width;
	m_rHeight =Height;

	int BMPWidth = (Width * 3 + 3) / 4 * 4;
	int bWidth =Width;
	int bHeight =Height;

	if(Width% 8 != 0)
		bWidth = (Widthl8 + 1)*8;
	if(Height% 8 != 0)
		bHeight = (Height/8 + 1)*8; 

	int i,j,k;

	for(i=0; i<20; i++)
		if(TbH[i].FIag)
		{
			delete[] TbH[i].HUFFCODE;
			delete[] TbH[i].HUFFSIZE;
			delete[] TbH[i].HUFFVAL;
		}
		char szMult[MAX_PATH];

		USES_CONVERSION;
		strcpy(szMult, W2A(FileName));
		//_tcscpy(szWide , A2W(szMult)); 

		HFILE hFiIe = _ Icreat(szMuIt, 0);

		PutSOI(hFiIe);
		PutDQT(hFiIe);
		PutDHT(hFiIe);
		PutSOF(hFiIe,Width,Height);
		PutSOS(hFiIe);

		if(m_pData !=NULL)
			delete[] m_pData;
		m_pData = new BYTE[(bWidth * 3) * bHeight];

		memset(m_pData, 0, (bWidth * 3) * bHeight); 

		for (i=0; i<Height; i++)
			memcpy(&m_pData[i*(bWidth*3)], &pp[i*BMPWidth], BMPWidth);

		float R, G, B;
		fIoat y, cb, cr;
		BYTE *pos;

		for(i=0; i<Height; i++)
		{
			pos = &m_pData[i*(bWidth*3)];
			for(j=0; j<Width; j++)
			{
				/////////////////
				B = (float)*POS;
				G = (float)*(pos+1);
				R = (float)*(pos+2);

				y = 0.299f * R + 0.587f * G + 0.114f * B;
				cb = -0.1687f * R- 0.3313f * G + 0.5f * B + 128;
				cr = 0.5f*R - 0.4187f*G - 0.0813f*B + 128;

				//y = (77 * R + 150 * G + 29 * B)>>8 ;
				//cb = (B - y) + 128;
				//cr = (R - y) + 128;

				if(y>255.) y = 255.; if(y<O.) y = 0.;
				if(cb>255.) cb = 255.; if(cb<O.) cb = 0.;
				if(cr>255.) cr = 255.; if(cr<O.) cr = 0.:

				*pos = (BYTE)y;
				*(pos+1) = (BYTE)cb;
				*(pos+2) = (BYTE)cr;

				pos = pos + 3;
			}
		}

		Y = new short[bWidth * bHeight];
		memset(Y, 0, sizeof(short) * bWidth * bHeight);
		Cb = new short[bWidth * bHeight];
		memset(Cb, 0, sizeof(short) * bWidth * bHeight);
		Cr =new short[bWidth * bHeight];
		memset(Cr, 0, sizeof(short) * bWidth * bHeight);

		int idx1, idx2;


		for(i=0; i<Height; i++)
		{
			for(j=0; j<Width; j++)
			{
				idx1 = i*bWidth+j;
				idx2 = i*(bWidth*3)+j*3;

				Y[idx1] = m_pData[idx2] - 128;
				Cb[idx1] = m_pData[idx2+1] - 128;
				Cr[idx1] = m_pData[idx2+2] - 128;
			}
		}

		for(i=0; i<bHeight; i = i + 8)
		{
			for (j=0; j<bWidth; j = j + 8)
			{
				DCT(&Y[i*bWidth+j], bWidth, FALSE);
				DCT(&Cb[i*bWidth+j], bWidth, TRUE);
				DCT(&Cr[i*bWidth+j], bWidth, TRUE);
			}
		}
		////////////////////////////////////
		//Differential DC Process 

		int Num_X = bWidth/8;
		int Num_Y = bHeight/8;
		int idx = 0;

		short *DC1 =new short[Num_X * Num_Y];
		short *DC2 =new short[Num_X * Num_Y];
		short *DC3 =new short[Num_X * Num_Y];

		for (i=0; i<bHeight; i = i + 8)
		{
			for (j=0; j<bWidth; j = j + 8)
			{
				DC1[idx] = Y[i*bWidth+j];
				DC2[idx] = Cb[i*bWidth+j];
				DC3[idx] = Cr[i*bWidth+j);
				idx++;
			}
		}

		for(i=Num_X * Num_Y - 1; i>O; i--)
		{
			DC1[i] = DC1[i]- DC1[i-1];
			DC2[i] = DC2[i]- DC2[i-1];
			DC3[i] = DC3[i]- DC3[i-1];
		}

		idx = O;

		for(i=0; i<bHeight; i = i + 8)
		{
			for(j=0; j<bWidth; j = j + 8)
			{
				Y[i*bWidth+j] = DC1[idx];
				Cb[i*bWidth+j] = DC2[idx];
				Cr[i*bWidth+j] = DC3[idx];
				idx++;
			}
		}

		delete[] DC1;
		delete[] DC2;
		delete[] DC3;

		int Num , iTh[4] = {16, 17}, Th, key;

		for (i=0; i<2; i++)
		{
			Th = iTh[i];
			Num = TbH[Th] .Num ;
			TbH[Th].PT =new int[251];
			for(k=O ; k<251; k++)
			{
				key = -9999;
				for(j=O; j<Num; j++)
				{
					if(TbH[Th].HUFFVAL[j] == k)
					{
						/////////////////////////////////////////////
						key = j;
						break;
					}
				}
				TbH[Th].PT[k] =key;
			}
		}

		/* HUFFMAN CODE ENCODEINGI! */

		m_pBuf =new BYTE[bWidth * bHeight * 3); 
		m_lndex = 0; II <c ! "2.1";
			en t = 0; 
		hEneode(bWidth, bHeight);
		whiIe(cnt != 0)
			ShotBit(O);

		_lwrite(hFile, (LPSTR)m_pBuf, m_lndex);

		delete[] m_pBuf;

		PutEOI(hFile);

		for(i=0; i<2; i++)
		{
			Th = iTh[i];
			delete[] TbH[Th].PT;
		}
		for(i=O; i<bHeight; i++)
			for(j=O; j<bWidth; j++)
			{
				idx1 = i*bWidth*3 + i*3;
				m_pData[idx1] = (BYTE)Y[i*bWidth+j];
				m_pData[idx1+1] = (BYTE)Cb[i*bWidth+j];
				m_pData[idx1+2] = (BYTE)Cr[i*bWidth+j];
			}

			delete[] Y;
			delete[] Cb;
			delete[] Cr;

			_lclose(hFiIe);
}

BOOL CJpeg::SaveJpg(LPCTSTR file)
{
	FlipY();

	SaveJPG(file, GetSize().cx, GetSize().cy, (BYTE*)m_pDib);

	//////////////////////////////////
	return TRUE;
}


void CJpeg::FIipY()
{
	int ReaiWidth = (GetSize().ex* 3 + 3) / 4 * 4;

	int Height = GetSize() .cy;

	BYTE *pLine =new BYTE[RealWidth *Height];

	for(int i=0; i<Height/2; i++)
	{
		memcpy(pline, &m_pDib[i * RealWidth], RealWidth);

		memcpy(&m_pDib[i * ReaiWidth], &m_pDib[(Height - 1- i) * ReaiWidth], ReaiWidth);

		memcpy(&m_pDib[(Height - 1- i) * RealWidth], pLine, RealWidth);
	}
	delete[] pLine;

	SIZE CJpeg::GetSize()
	{
		SIZE size;
		size.cx=m_pBitmaplnfo.bmiHeader.biWidth;
		size.cy=m_pBitmaplnfo.bmiHeader.biHeight;

		return size;
	}

	void CJpeg::PutSOI(HFILE hFile)
	{
		WORD Marker= (Oxd8 << 8) I Oxff;
		_lwrite(hFile, (LPSTR)&Marker, 2);
		void CJpeg::PutDQT(HFILE hFile)
		{
			WORD Marker, SegSize;
			BYTE c;
			//Luminance Quantization Table 
			BYTE QtbO[64] = {16, 11 , 12, 14, 12, 1 0, 16, 14,
				13, 14, 18, 17, 16, 19, 24, 40,
				26, 24, 22, 22, 24, 49, 36, 37,
				29, 40, 58, 51, 61, 60, 57, 51,
				56, 55, 64, 72, 92, 78, 64, 68,
				87, 69, 66, 57, 80, 109, 81, 87,
				95, 98, 103, 104, 103, 62, 77, 113,
				121, 112, 100, 120, 92, 101, 103, 99};

			/////////////////////////////////////
			//Chrominance Quantization Table 
			BYTE Qtb1[64] = {17, 18, 18, 24, 21, 24, 47, 26,
				26, 47, 99, 66, 56, 66, 99, 99,
				99, 99, 99, 99, 99, 99, 99, 99,
				99, 99, 99, 99, 99, 99, 99, 99,
				99, 99, 99, 99, 99, 99, 99, 99,
				99, 99, 99, 99, 99, 99, 99, 99,
				99, 99, 99, 99, 99, 99, 99, 99,
				99, 99, 99, 99, 99, 99, 99, 99 };

			Marker =(Oxdb«B) I Oxff;
			_lwrite(hFile, (LPSTR)&Marker, 2); 

			SegSize = 67; SegSize = (SegSize << 8) I (SegSize >> 8);
			_lwrite(hFile, (LPSTR)&SegSize, 2); 

			c = O; _lwrite(hFile, (LPSTR)&c, 1); 
			_lwrite(hFile, (LPSTR)QtbO, 64); 

			Marker= (Oxdb « 8) I Oxff;
			_lwrite(hFile, (LPSTR)&Marker, 2); 

			SegSize = 67; SegSize = (SegSize << 8) I (SegSize >> 8);
			_lwrite(hFile, (LPSTR)&SegSize, 2);

			c = 1; _lwrite(hFi le , (LPSTR)&c, 1); 
			_lwrite(hFile, (LPSTR)Qtb1, 64); 
		}

		void CJpeg::PutDHT(HFILE hFi le)
		{
			m_pBuf =new BYTE[421];
			BYTE HuffTb[421] = {255 , 196, 1, 162, 0, 0, 1, 5, 1, 1, 1, 
				1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2,
				3, 4, 5, 6, 7, 8, 9, 10, 11, 16, 0, 2,
				1, 3, 3, 2, 4, 3, 5, 5, 4, 4, 0, 0, 1,
				125, 1, 2, 3, 0, 4, 17, 5, 18, 33, 49,
				65, 6, 19, 81, 97, 7, 34, 113, 20, 50,
				129, 145, 161, 8, 35, 66, 177, 193, 21,
				82, 209, 240, 36, 51, 98, 114, 130, 9,
				10, 22, 23, 24, 25, 26, 37, 38, 39, 40,
				41, 42, 52, 53, 54, 55, 56, 57, 58, 67,
				68, 69, 70, 71, 72, 73, 74, 83, 84, 85,
				86, 87, 88, 89, 90, 99, 100, 101, 102,
				103, 104, 105, 106, 115, 116, 117 ,118,
				119, 120, 121, 122, 131, 132, 133, 134,
				135, 136, 137, 138, 146, 147, 148, 149,
				150, 151, 152, 153, 154, 162, 163, 164,
				165, 166, 167, 168, 169, 170, 178, 179,
				180, 181, 182, 183, 184, 185, 186, 194,
				195, 196, 197, 198, 199, 200, 201, 202,
				210, 211, 212, 213, 214, 215, 216, 217,
				218, 225, 226, 227, 228, 229, 230, 231,
				232, 233, 234, 241, 242, 243, 244, 245,
				246, 247, 248, 249, 250, 1, 0, 3, 1, 1,
				1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
				1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 17,
				0, 2, 1, 2, 4, 4, 3, 4, 7, 5, 4, 4, 0,
				1, 2, 119, 0, 1, 2, 3, 17, 4, 5, 33, 49,
				6, 18, 65, 81, 7, 97, 113, 19, 34, 50,
				129, 8, 20, 66, 145, 161, 177, 193, 9,
				35, 51, 82, 240, 21, 98, 114, 209, 10,
				22, 36, 52, 225, 37, 241, 23, 24, 25, 26,
				38, 39, 40, 41, 42, 53, 54, 55, 56, 57,
				58, 67, 68, 69, 70, 71, 72, 73, 74, 83,
				84, 85, 86, 87, 88, 89, 90, 99, 100, 101,
				102, 103, 104, 105, 106, 115, 116, 117,
				118, 119, 120, 121, 122, 130, 131, 132,
				133, 134, 135, 136, 137, 138, 146, 147,
				148, 149, 150, 151, 152, 153, 154, 162,
				163, 164, 165, 166, 167, 168, 169, 170,
				178, 179, 180, 181, 182, 183, 184, 185,
				186, 194, 195, 196, 197, 198, 199, 200,
				201, 202, 210, 211, 212, 213, 214, 215,
				216, 217, 218, 226, 227, 228, 229, 230,
				231, 232, 233, 234, 242, 243, 244, 245,
				246, 247, 248, 249, 250, 255};
			memcpy(m_pBuf, HuffTb, 421);
			m_lndex = O; 
			FindDHT();
			_lwrite(hFile, (LPSTR)m_pBuf, 420);
			delete[] m_pBuf;
		}
		void CJpeg::PutSOF(HFILE hFile, int Width, int Height)
		{
			WORD Marker, SegSize , w;
			BYTE c;
			int i;

			Marker= (OxcO << 8) I Oxff;
			_lwrite(hFile, (LPSTR)&Marker , 2);

			SegSize = 17; SegSize = (SegSize << 8) I (SegSize >> 8);
			_lwrite(hFile ,(LPSTR)&SegSize, 2);

			c = 8; _lwrite(hFile, (LPSTR)&c, 1);

			w = (WORD)Height; w = (w << 8) I (w >> 8);
			_lwrite(hFile, (LPSTR)&w, 2); II Number of Y Line

				w = (WORD)Width; w = (w << 8) I (w >> 8);
			_lwrite(hFi le, (LPSTR)&w , 2); II Number of Y Line

				c = 3; _lwr i te(hFile, (LPSTR)&c, 1); I I Nf = 3
				for(i=1; i<=3; i++)
				{
					c = (BYTE) i; _lwrite(hFile, (LPSTR)&c, 1);
					c = 17; _lwrite(hFile, (LPSTR)&c, 1); 
					if(i==1)
						c=O;
					else
						c=1;
					_lwrite(hFile, (LPSTR)&c, 1); 
				}
		}
		void CJpeg::PutSOS(HFILE hFile)
		{
			WORD Marker , SegSize;
			BYTE c;
			i nt i ;
			/////////////////////////

			Marker= (Oxda << 8) I Oxff;
			_lwrite(hFile, (LPSTR)&Marker, 2);

			SegSize = 12; SegSize = (SegSize << 8) I (SegSize >> 8);
			_lwrite(hFile, (LPSTR)&SegSize, 2); 
			c = 3; _lwrite(hFile, (LPSTR)&c , 1); 
			for(i=1; i<=3; i++)
			{
				c = (BYTE)i; _lwrite(hFile, (LPSTR)&c, 1); 
				if(i == 1)
					c=O ;
				else
					c=Ox11 ;
				_lwrite(hFile, (LPSTR)&c, 1); 

				c = O; _lwrite(hFile, (LPSTR)&c, 1); 
				c = Ox3f ; _lwrite(hFi le, (LPSTR)&c, 1); 
				c = O; _lwrite(hFile, (LPSTR)&c, 1);
			}

			void CJpeg: :DCT(short *pos, int bWidth , BOOL Flag)
			{
				BYTE QtbO[64] ={16, 11 , 12 , 14 , 12 , 1 0 , 16, 14,
					13, 14, 18, 17, 16, 19, 24, 40,
					26, 24, 22, 22, 24, 49, 36, 37,
					29, 40, 58, 51, 61, 60, 57, 51,
					56, 55, 64, 72, 92, 78, 64, 68,
					87, 69, 66, 57, 80, 109, 81, 87,
					95, 98, 103, 104, 103, 62, 77, 113,
					121, 112, 100, 120, 92, 101, 103, 99};

				BYTE Qtb1[64] ={17, 18, 18, 24 , 21, 24 , 47, 26,
					26, 47, 99, 66, 56, 66, 99, 99,
					99, 99, 99, 99, 99, 99, 99, 99,
					99, 99, 99, 99, 99, 99, 99, 99,
					99, 99, 99, 99, 99, 99, 99, 99,
					99, 99, 99, 99, 99, 99, 99, 99,
					99, 99, 99, 99, 99, 99, 99, 99,
					99, 99, 99, 99, 99, 99, 99, 99};


				int i,j;
				int x, y, u, v;
				float Cu, Cv;
				float Sum;
				float dct_coeff[8][8] =
				{
					+1.Of,    +1.Of,    +1.0f,   +1.Of,     +1.0f,    +1.Of,    +1.0f,     +1.Of,
					+0.9808f, +0.8315f, +0.5556f, +0.1951f, -0.1951f, -0.5556f, -0.8315f, -0.9808f,
					+0.9239f, +0.3827f, -0.3827f, -0.9239f, -0.9239f, -0.3827f, +0.3827f, +0.9239f,
					+0.8315f, -0.1951f, -0.9808f, -0.5556f, +0.5556f, +0.9808f, +0.1951f, -0.8315f,
					+0.7071f, -0.7071f, -0.7071f, +0.7071f, +0.7071f, -0.7071f, -0.7071f, +0.7071f,
					+0.5556f, -0.9808f, +0.1951f, +0.8315f, -0.8315f, -0.1951f, +0.9808f, -0.5556f,
					+0.3827f, -0.9239f, +0.9239f, -0.3827f, -0.3827f, +0.9239f, -0.9239f, +0.3827f,
					+0.1951f, -0.5556f, +0.8315f, -0.9808f, +0.9808f, -0.8315f, +0.5556f, -0.1951f
					for(v=O; v<B ; v++)
					{
						for(u=O; u<B; u++)


							//////////////////////////////
						{
							Sum = 0;
							for(y=O ; y<8; y++)
								for(x=O ; x<8 ; x++)
									Sum= Sum+ pos[(int)(y*bWidth+x)] * dct_coeff[u][x] * dct_coeff[v][y];

							Cu = 1.; if (u == 0) Cu = 0. 7071f;
							Cv = 1.; if (v == 0) Cv = 0. 7071f;
							ZZ[(int)(v*8+u)] = (short)(Cu * Cv *Sum / 4.);
						}
					}

					Zigzag2();

					if(Fiag) // TRUE : Chrominance, FALSE Luminance
						for(i=0; i<64; i++)
							ZZ[i] = ZZ[i] / Qtb1[i];

					else
						for(i=0; i<64; i++)
							ZZ[i] = ZZ[i] / Qtb1[i];


					for(i=0; i<8; i++)
						for(j=O; j<B; j++)
							pos[i*bWidth+j] = ZZ[i*B+j];
				}

				void CJpeg::Zigzag2()
				{
					int Index [64] =
					{0, 1, 5, 6, 14, 15, 27, 28,
					2, 4, 7, 13, 16, 26, 29, 42,
					3, 8, 12, 17, 25, 30, 41, 43,
					9, 11, 18, 24, 31, 40, 44, 53,
					10, 19, 23, 32, 39, 45, 52, 54,
					20, 22, 33, 38, 46, 51, 55, 60,
					21, 34, 37, 47, 50, 56, 59, 61,
					35, 36, 48, 49, 57, 58, 62, 63};

					short Temp[64];
					memcpy(Temp, ZZ, 64 * sizeof(short));

					int i, j, idx;
					for(i=0; i<8; i++)
						for(j=O; j<B; j++)
						{
							idx = (i<<3)+j;
							ZZ[Index[idx]] =Temp[idx];
						}
				}
				void CJpeg::hEncode(int bWidth ,int bHeight)
				{
					int i, j;
					for(i=0; i<bHeight; i = i + 8)
					{
						for (j=0; j<bWidth; j = j + 8)
						{
							EncodeDU(&Y[i*bWidth+j ], FALSE, bWidth) ;
							EncodeDU(&Cb[i*bWidth+j ], TRUE, bWidth);
							EncodeDU(&Cr[i*bWidth+j ], TRUE, bWidth) ;
						}
						///////////////////////////////////////////////////
					}
				}
				void CJpeg::EncodeDU(short *pos, BOOL Flag, int bWidth)
				{
					WORD Code;
					BYTE Val, Size;
					BYTE SSSS , Rs;
					short XX[64], DIFF;
					BYTE ThDC, ThAC;
					int idx = 0;
					int i, j;

					ThDC = O; ThAC = 16;
					if(Flag)
					{
						ThDC = 1; ThAC = 17;
					}
					for(i=0; i<8; i++)
					{
						for(j=O; j<8; j++)
						{
							XX[idx] = pos[i*bWidth+j];
							idx++;
						}
					}

					DIFF = XX[O];
					Val = GetCategory(DIFF);
					Code= TbH[ThDC].HUFFCODE[Val];
					Size= TbH[ThDC].HUFFSIZE[Val];
					if(DIFF < 0)
						DIFF--;
					ChargeCode(Code, Size) ;
					ChargeCode((WORD)DIFF, Val);

					BYTE k = 0, R = O;
					whiIe(TRUE)
					{
						k++;
						if(XX[k] == 0)
						{
							if (k==63)
							{
								Rs = OxOO;
								Code= TbH[ThAC].HUFFCODE[TbH[ThAC] .PT[Rs]] ;
								Size= TbH[ThAC].HUFFSIZE[TbH[ThAC].PT[Rs]] ;
								ChargeCode((WORD)Code , Size);
								break;
							}
							else
								R++;
						}
						else
						{
							whiIe(R>15)
							{
								Rs = OxfO;
								Code= TbH[ThAC].HUFFCODE[TbH[ThAC].PT[Rs]];
								Size= TbH[ThAC].HUFFSIZE[TbH[ThAC].PT[Rs]];

								/////////////////////////////////////
								ChargeCode((WORD)Code, Size);
								R = R - 16;
								SSSS = GetCategory(XX[k]);
								//Rs = (R << 4) I SSSS;
								Rs = (R * 16) + SSSS;
								Code= TbH[ThAC].HUFFCODE[TbH[ThAC].PT[Rs]];
								Size= TbH[ThAC].HUFFSIZE[TbH[ThAC].PT[Rs]];
								ChargeCode((WORD)Code, Size);
								DIFF = XX[k];
								if(DIFF < 0)
									DIFF = DIFF - 1;
								ChargeCode((WORD)DIFF, SSSS);
								R = 0;

								if(k==63)
									break;
							}
						}
					}
					void CJpeg::ShotBit(BYTE Bit)
					{
						static BYTE Bullet= O;

						Bit= Bit<< (7-cnt);

						BuIIet = BuIIetIBit;

						cnt++;

						if (cnt == 8)
						{
							cnt = 0;
							m_pBuf[m_lndex] =Bullet;
							m_lndex++;
							if(Bullet == Oxff) 
							{
								m_pBuf[m_lndex] = OxOO;
								m_lndex++;
							}
							BuIlet = 0;
						}
					}
					void CJpeg::PutEOI(HFILE hFile)
					{
						WORD Marker = (Oxd9<<8) I Oxff;
						_lwrite(hFile,(LPSTR)&Marker, 2);
					}

					void CJpeg::FindDHT()
					{
						if((m_pBuf[m_lndex] == Oxff) && (m_pBuf[m_lndex+1] == Oxc4))
						{
							WORD SegSize = m_pBuf[m_lndex+2]*256 + m_pBuf[m_lndex+3];

							BYTE *P = &m_pBuf[m_lndex+4];
							do
							{
								int i, j, k, LASTK;
								//////////////////////////////////
								int Num = O;
								BYTE BITS[17];
								BYTE Th = *p; 
								memcpy(BITS, p, 17);
								p = p + 17;

								for(i=1; i<17; i++)
									Num = Num +BITS[i];

								TbH[Th].Flag =TRUE;

								TbH[Th].HUFFCODE =new WORD[Num+1];
								TbH[Th].HUFFSIZE =new BYTE[Num+1];
								TbH[Th].HUFFVAL =new BYTE[Num+1];

								memcpy(TbH[Th].HUFFVAL, p, Num);

								p = p + Num;

								//Generation of table of Huffman code sizes//
								i=1; j=1; k=O;
								while(i<=16)
								{
									whiIe(j<=BITS[i])
									{
										TbH[Th].HUFFSIZE[k] = (BYTE)i;
										k++;
										j++;
									}

									i++;
									j=1;
								}
								TbH[Th].HUFFSIZE[k] = O;
								LASTK = k;


								//Generation of table of Huffman codes
								k=O;
								WORD CODE = O;
								BYTE Sl = TbH[Th].HUFFSIZE[O];

								whiIe( TRUE)
								{
									do
									{
										TbH[Th].HUFFCODE[k] =CODE;
										CODE++;
										k++;
									}while(TbH[Th].HUFFSIZE[k] == Sl);
									if(TbH[Th] .HUFFSIZE[k] == 0)
										break;
									do
									{
										CODE= CODE<< 1;
										Sl++;
									}while(TbH[Th].HUFFSIZE[k] != Sl);
								}

								i=O; j=O;
								whiIe(TRUE)
								{
									///////////////////////////
									do
									{
										i++;
										if(i>16)
											break;
										if(BITS[i] == 0)
											TbH[Th].MAXCODE[i] = -1;
									}whi le(BITS[ i] == 0);
									if(i>16)
										break;
									TbH[Th].VALPTR[i] = j;
									TbH[Th].MINCODE[i] = TbH[Th].HUFFCODE[j ];
									j = j + BITS[i]- 1;
									TbH[Th].MAXCODE[i] = TbH[Th] .HUFFCODE[j ];
									j++;
								}
								TbH[Th].Num = Num;
							}whi le(*p != Oxff);

							m_lndex = m_lndex + SegSize + 2;
						}
					}

					BYTE CJpeg::GetCategory(short V)
					{
						BYTE Num = O;
						if(V<O)
							V = -V;
						while(V != 0)
						{
							V=V>>1;
							Num++;
						}
						return Num;
					}

					void CJpeg::ChargeCode(WORD Code, int Size)
					{
						i nt i;
						BYTE Bit;
						for (i=0; i<Size; i++)
						{
							Bit= (Code >> (Size- 1 - i)) & Ox01;
							Shot Bit(Bit);
						}
					}
