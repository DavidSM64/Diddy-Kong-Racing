// GE Recompression C++ Class
// Painstakingly done by Henry Ford (mrhtford_ps2dev@hotmail.com)
// Ported to C++ Class by SubDrag (subdrag@rarewitchproject.com) July 13, 2005
// Compression Games Added April 03, 2007


#pragma once
#include <iostream>
#include <string>

#define maxByteSize 0x800000

#define GOLDENEYE 0
#define PD 1
#define BANJOKAZOOIE 2
#define KILLERINSTINCT 3
#define DONKEYKONG64 4
#define BLASTCORPS 5
#define BANJOTOOIE 6
#define DONKEYKONG64KIOSK 7
#define CONKER 8
#define TOPGEARRALLY 9
#define MILO 10
#define JFG 11
#define DKR 12
#define JFGKIOSK 13
#define MICKEYSPEEDWAY 14
#define MORTALKOMBAT 15
#define STUNTRACER64 16
#define ZLB 17
#define RESIDENTEVIL2 18

#define BOOL bool
#define TRUE true
#define FALSE false
#define DWORD int
#define CString std::string
#define PTSTR std::string
#define LPSTR std::string

struct tableEntry {
	unsigned long bits;
	unsigned char flags;
	int nextIndex;
	unsigned long wordValue;
};

class GECompression
{
public:
	GECompression();
	~GECompression(void);
	void SetCompressedBuffer(unsigned char* Buffer, int bufferSize);
	unsigned char* OutputDecompressedBuffer(int& fileSize, int& compressedSize);
	//bool CompressGZipFile(CString inputFile, CString outputFile, bool byteFlipCompressed);
	int game;
	CString mainFolder;
	void SetGame(int replaceGame);
	//void SetPath(CString directory);
	//old stuff
	//unsigned char* Compress(int& compressedSize);
	//unsigned char* OutputCompressed(int compressionType, int& fileSize);
	//void SetInputBuffer(unsigned char* Buffer, int bufferSize);

	BOOL hiddenExec (PTSTR pCmdLine, CString currentDirectory);
	BOOL IsFileExist(LPSTR lpszFilename);

private:
	static unsigned char bt1Table1[288];
	static unsigned char bt1Table2[30];

	static unsigned short bt12Table1S[0x20];
	static unsigned short bt12Table1B[0x20];
	static unsigned short bt12Table2S[0x20];
	static unsigned short bt12Table2B[0x20];

	static unsigned char bt2Table1B[0x13];

	tableEntry* unpackTable;
	int unpackTableIndex;

	unsigned long bitsCache;
	int bitsRemain;
	unsigned long bytesIndex;

	//unsigned char* inputBuffer;
	//int inputBufferSize;
	unsigned char* compressedBuffer;
	int compressedBufferSize;

	unsigned long GetNBits(int nBits);
	unsigned long GetNBitsAndPreserve(int nBits);

	bool UncompressType0(unsigned char* returnBuffer, int& fileSize);
	bool UncompressType1(unsigned char* returnBuffer, int& fileSize);
	bool UncompressType2(unsigned char* returnBuffer, int& fileSize);

	void CreateGlobalDecompressionTable(int bit1TableChoice, int size2, int bit12STableSChoice, int bit12BTableChoice, int numBits, bool& returnValue, int& numReturnBits, int& returnStartIndex);
	bool DecompressBasedOnTable(int startIndex1, int startIndex2, int bitLen1, int bitLen2, unsigned char* returnBuffer, int& fileSize);

	unsigned char variableTable[0x13];
	unsigned short tableSize;
	unsigned char fiveBits;
	unsigned long* wordTable;

	// old stuff
	/*void FlipBits(unsigned char* indexes, int sizeBytes, int offset);
	bool* StringToBits(CString bitString, int& lengthBool);
	static CString dictionaryFirstStr[0x10];
	static CString dictionarySecondStr[0x10];
	CString EncodeLZBitPart(int backAmt);
	CString EncodeRLEBitPart(int repeatAmt);
	CString HexToBits(int hexNum, int outLength);
	CString FlipStringBits(CString inputString);*/

	// better compression way



	unsigned long iterationCounter;
};
