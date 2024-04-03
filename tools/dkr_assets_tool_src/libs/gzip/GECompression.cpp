//#include "StdAfx.h"
#include "GECompression.h"
#include <math.h>

#define TABLE1 0
#define TABLE2 1
#define VARIABLETABLE 2
#define WORDTABLEBEGIN 3
#define WORDTABLEEND 4


GECompression::GECompression()
{
//	inputBuffer = NULL;
	compressedBuffer = NULL;
//	inputBufferSize = 0;
	compressedBufferSize = 0;
	wordTable = NULL;
	unpackTable = NULL;
	game = GOLDENEYE;

	unpackTable = new tableEntry[0xFFFF];
}

GECompression::~GECompression(void)
{
	if (unpackTable != NULL)
	{
		delete [] unpackTable;
		unpackTable = NULL;
	}
	if (wordTable != NULL)
	{
		delete [] wordTable;
		wordTable = NULL;
	}
	if (compressedBuffer != NULL)
	{
		delete [] compressedBuffer;
		compressedBuffer = NULL;
	}
}

unsigned char GECompression::bt1Table1[288] =
{
8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8
};
unsigned char GECompression::bt1Table2[30] =
{
5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5
};

unsigned short GECompression::bt12Table1S[0x20] =
{
	0x0003, 0x0004, 0x0005, 0x0006, 0x0007, 0x0008, 0x0009, 0x000a,
	0x000b, 0x000d, 0x000f, 0x0011, 0x0013, 0x0017, 0x001b, 0x001f,
	0x0023, 0x002b, 0x0033, 0x003b, 0x0043, 0x0053, 0x0063, 0x0073,
	0x0083, 0x00a3, 0x00c3, 0x00e3, 0x0102, 0x0000, 0x0000, 0x0000
};

unsigned short GECompression::bt12Table1B[0x20] = 
{
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x02,
	0x03, 0x03, 0x03, 0x03, 0x04, 0x04, 0x04, 0x04,
	0x05, 0x05, 0x05, 0x05, 0x00, 0x63, 0x63, 0x00
};

unsigned short GECompression::bt12Table2S[0x20] =
{
	0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0007, 0x0009, 0x000d,
	0x0011, 0x0019, 0x0021, 0x0031, 0x0041, 0x0061, 0x0081, 0x00c1,
	0x0101, 0x0181, 0x0201, 0x0301, 0x0401, 0x0601, 0x0801, 0x0c01,
	0x1001, 0x1801, 0x2001, 0x3001, 0x4001, 0x6001, 0x0000, 0x0000	

};

unsigned short GECompression::bt12Table2B[0x20] = 
{
	0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x02, 0x02,
	0x03, 0x03, 0x04, 0x04, 0x05, 0x05, 0x06, 0x06,
	0x07, 0x07, 0x08, 0x08, 0x09, 0x09, 0x0a, 0x0a,
	0x0b, 0x0b, 0x0c, 0x0c, 0x0d, 0x0d, 0x00, 0x00
};

unsigned char GECompression::bt2Table1B[0x13] = 
{
	0x10,0x11,0x12,0x00, 0x08,0x07,0x09,0x06, 0x0a,0x05,0x0b,0x04, 0x0c,0x03,0x0d,0x02, 0x0e,0x01,0x0f
};

/*
void GECompression::SetPath(CString directory)
{
	mainFolder = directory;
}
*/

void GECompression::SetGame(int replaceGame)
{
	game = replaceGame;
}

/*void GECompression::SetInputBuffer(unsigned char* Buffer, int bufferSize)
{
	if (inputBuffer == NULL)
	{
		inputBuffer = new unsigned char[bufferSize];
	}
	else
	{
		delete [] inputBuffer;
		inputBuffer = new unsigned char[bufferSize];
	}

	for (int x = 0; x < bufferSize; x++)
	{
		inputBuffer[x] = Buffer[x];
	}
	inputBufferSize = bufferSize;
}*/

/*unsigned char* GECompression::OutputCompressed(int compressionType, int& fileSize)
{
	unsigned char* outputBuffer = NULL;
	fileSize = 0;
	if (compressionType == 1)
		outputBuffer = Compress(fileSize);
	return outputBuffer;
}*/





void GECompression::SetCompressedBuffer(unsigned char* Buffer, int bufferSize)
{
	if (compressedBuffer == NULL)
	{
		compressedBuffer = new unsigned char[bufferSize];
	}
	else
	{
		delete [] compressedBuffer;
		compressedBuffer = new unsigned char[bufferSize];
	}

	for (int x = 0; x < bufferSize; x++)
	{
		compressedBuffer[x] = Buffer[x];
	}

	compressedBufferSize = bufferSize;
}


unsigned long GECompression::GetNBits(int nBits)
{
	while (bitsRemain < nBits)
	{
		if (bytesIndex >= maxByteSize)
			return 0; // bad decompression
		if ((int)bytesIndex >= compressedBufferSize)
			return 0; // bad decompression
		bitsCache = ((bitsCache) | (compressedBuffer[bytesIndex] << bitsRemain));
		bitsRemain = bitsRemain + 8;
		bytesIndex++;
	}

	unsigned long result = (bitsCache & ((1 << nBits)-1));
	bitsCache = bitsCache >> nBits;
	bitsRemain = bitsRemain - nBits;
	return result;
}

unsigned long GECompression::GetNBitsAndPreserve(int nBits)
{
	while (bitsRemain < nBits)
	{
		if (bytesIndex >= maxByteSize)
			return 0; // bad decompression
		if ((int)bytesIndex >= compressedBufferSize)
			return 0; // bad decompression
		bitsCache = ((bitsCache) | (compressedBuffer[bytesIndex] << bitsRemain));
		bitsRemain = bitsRemain + 8;
		bytesIndex++;
	}

	unsigned long result = (bitsCache & ((1 << nBits)-1));
	return result;
}

/*
BOOL GECompression::hiddenExec (PTSTR pCmdLine, CString currentDirectory)
{
   STARTUPINFO si;
   PROCESS_INFORMATION processInfo;
   ZeroMemory(&si, sizeof(si));
   si.cb           = sizeof(si);
   si.dwFlags      = STARTF_USESHOWWINDOW;
   si.wShowWindow  = SW_HIDE;
   ZeroMemory(&processInfo, sizeof(processInfo));
   CreateProcess(0, pCmdLine, 0, 0, FALSE, 0, 0, currentDirectory, &si, &processInfo);
   WaitForSingleObject(processInfo.hProcess, 20000);
   DWORD exitCode;
   if (GetExitCodeProcess(processInfo.hProcess, &exitCode))
   {
        if (exitCode == STILL_ACTIVE)
		{
            std::cout << "For some reason GZip Failed" << std::endl;
			TerminateProcess(processInfo.hProcess, exitCode);
			return false;
		}
   }   
   return true;
};

BOOL GECompression::IsFileExist(LPSTR lpszFilename)
{
	DWORD dwAttr = GetFileAttributes(lpszFilename);
	if (dwAttr == 0xffffffff)
		return FALSE;
	else 
		return TRUE;
}

bool GECompression::CompressGZipFile(CString inputFile, CString outputFile, bool byteFlipCompressed)
{
	CString gzipFileName = (mainFolder + "gzip.exe");
	char tempFileExistName[1000];
	strcpy(tempFileExistName, (mainFolder + "gzip.exe"));
	if (IsFileExist(tempFileExistName) == false)
	{
        std::cout << "gzip.exe not found!" << std::endl;
		return false;
	}

	strcpy(tempFileExistName, inputFile);
	if (IsFileExist(tempFileExistName))
	{
		FILE* tempInputFile = fopen(inputFile, "rb");
		fseek(tempInputFile, 0, SEEK_END);
		unsigned long size = ftell(tempInputFile);

		unsigned char* tempBuffer;
		tempBuffer = new unsigned char[size + 0x10];
		for (int x = 0; x < (size + 0x10); x++)
			tempBuffer[x] = 0;

		fseek(tempInputFile, 0, SEEK_SET);


		fread(tempBuffer, 1, size, tempInputFile);


		FILE* tempOutputFile = fopen((mainFolder+"tempgh9.bin"), "wb");
		if (tempOutputFile == 0)
		{
			fclose(tempInputFile);
			delete [] tempBuffer;
            std::cout << "Cannot Write Temporary File" << std::endl;
			return false;
		}

		unsigned long compressedSize = size;

		if ((game != BANJOTOOIE) && (game != CONKER))
		{
			if (((compressedSize % 0x10) != 0))
				compressedSize = ((compressedSize - (compressedSize % 0x10)) + 0x10);
		}

		fwrite(tempBuffer, 1, compressedSize, tempOutputFile);	

		fclose(tempInputFile);
		fclose(tempOutputFile);

		delete [] tempBuffer;

		::SetCurrentDirectory(mainFolder);
		CString tempStr = ("gzip.exe -f -q -9 tempgh9.bin");
		hiddenExec(_T(tempStr.GetBuffer()), (mainFolder));
		CString outputGZippedName = (mainFolder+"TEMPGH9.BIZ");

		strcpy(tempFileExistName, outputGZippedName);
		if (!IsFileExist(tempFileExistName))
		{
			outputGZippedName = (mainFolder+"tempgh9.bin.gz");;
		}

		strcpy(tempFileExistName, outputGZippedName);
		if (IsFileExist(tempFileExistName))
		{
			FILE* inputFileName = fopen(outputGZippedName, "rb");
			int sizeNew = 0;
			fseek(inputFileName, 0, SEEK_END);
			sizeNew = ftell(inputFileName);
			fseek(inputFileName, 0, SEEK_SET);

			unsigned char* tempBufferNew;
			tempBufferNew = new unsigned char[sizeNew];
			fread(tempBufferNew, 1, sizeNew, inputFileName);

			fclose(inputFileName);
			DeleteFile((mainFolder+"TEMPGH9.BIZ"));
			FILE* outputFileName = fopen(outputFile, "wb");
			if (outputFileName == NULL)
			{
				delete [] tempBufferNew;
                std::cout << "Error opening temp output file" << std::endl;
				return false;
			}

			unsigned long start = 0x16;
			if ((game == GOLDENEYE) || (game == KILLERINSTINCT))
			{
				start = start - 2;
				tempBufferNew[start] = 0x11;
				tempBufferNew[start+1] = 0x72;
			}
			else if (game == PD)
			{
				start = start - 5;
				tempBufferNew[start] = 0x11;
				tempBufferNew[start+1] = 0x73;
				tempBufferNew[start+2] = ((size >> 16) & 0xFF);
				tempBufferNew[start+3] = ((size >> 8) & 0xFF);
				tempBufferNew[start+4] = ((size) & 0xFF);
			}
			else if (game == BANJOKAZOOIE)
			{
				start = start - 6;
				tempBufferNew[start] = 0x11;
				tempBufferNew[start+1] = 0x72;
				tempBufferNew[start+2] = ((size >> 24) & 0xFF);
				tempBufferNew[start+3] = ((size >> 16) & 0xFF);
				tempBufferNew[start+4] = ((size >> 8) & 0xFF);
				tempBufferNew[start+5] = ((size) & 0xFF);
			}
			else if ((game == DONKEYKONG64) || (game == BLASTCORPS))
			{
				start = start - 0xA;
				tempBufferNew[start] = 0x1F;
				tempBufferNew[start+1] = 0x8B;
				tempBufferNew[start+2] = 0x08;
				tempBufferNew[start+3] = 0x00;
				tempBufferNew[start+4] = 0x00;
				tempBufferNew[start+5] = 0x00;
				tempBufferNew[start+6] = 0x00;
				tempBufferNew[start+7] = 0x00;
				tempBufferNew[start+8] = 0x02;
				tempBufferNew[start+9] = 0x03;
			}
			else if (game == DONKEYKONG64KIOSK)
			{
				start = start - 0x12;
				tempBufferNew[start] = 0x1F;
				tempBufferNew[start+1] = 0x8B;
				tempBufferNew[start+2] = 0x08;
				tempBufferNew[start+3] = 0x08;
				tempBufferNew[start+4] = 0x03;
				tempBufferNew[start+5] = 0x45;
				tempBufferNew[start+6] = 0x75;
				tempBufferNew[start+7] = 0x37;
				tempBufferNew[start+8] = 0x00;
				tempBufferNew[start+9] = 0x03;
				tempBufferNew[start+0xA] = 0x74;
				tempBufferNew[start+0xB] = 0x6D;
				tempBufferNew[start+0xC] = 0x70;
				tempBufferNew[start+0xD] = 0x2E;
				tempBufferNew[start+0xE] = 0x62;
				tempBufferNew[start+0xF] = 0x69;
				tempBufferNew[start+0x10] = 0x6E;
				tempBufferNew[start+0x11] = 0x00;
			}
			else if (game == BANJOTOOIE)
			{

				start = start - 2;
				// is this checksum, not sure?
				float roundedSize = ceil((float)size / (float)0x10);
				unsigned short roundedSizeShort = (unsigned short)roundedSize;
				tempBufferNew[start] = ((roundedSizeShort >> 8) & 0xFF);
				tempBufferNew[start+1] = ((roundedSizeShort) & 0xFF);
			}
			else if (game == CONKER)
			{
				start = start - 4;
				tempBufferNew[start] = ((size >> 24) & 0xFF);
				tempBufferNew[start+1] = ((size >> 16) & 0xFF);
				tempBufferNew[start+2] = ((size >> 8) & 0xFF);
				tempBufferNew[start+3] = ((size) & 0xFF);
			}
			else if (game == TOPGEARRALLY)
			{
				start = start - 0xE;
				// compressed
				tempBufferNew[start] = (((sizeNew-(start + 8)) >> 24) & 0xFF);
				tempBufferNew[start+1] = (((sizeNew-(start + 8)) >> 16) & 0xFF);
				tempBufferNew[start+2] = (((sizeNew-(start + 8)) >> 8) & 0xFF);
				tempBufferNew[start+3] = (((sizeNew-(start + 8))) & 0xFF);
				// uncompressed
				tempBufferNew[start+4] = ((size >> 24) & 0xFF);
				tempBufferNew[start+5] = ((size >> 16) & 0xFF);
				tempBufferNew[start+6] = ((size >> 8) & 0xFF);
				tempBufferNew[start+7] = ((size) & 0xFF);
				// ?
				tempBufferNew[start+8] = 0x0;
				tempBufferNew[start+9] = 0x0;
				tempBufferNew[start+0xA] = 0x0;
				tempBufferNew[start+0xB] = 0x0;
				tempBufferNew[start+0xC] = 0x0;
				tempBufferNew[start+0xD] = 0x0;
			}
			else if (game == MILO)
			{
				start = start - 2;
				tempBufferNew[start] = 0x78;
				tempBufferNew[start+1] = 0x9C;
			}
			else if ((game == JFG) || (game == JFGKIOSK))
			{
				// unknown 5 bytes
				start = start - 5;
				tempBufferNew[start] = 0x04;
				tempBufferNew[start+1] = 0x03;
				tempBufferNew[start+2] = 0x00;
				tempBufferNew[start+3] = 0x00;
				tempBufferNew[start+4] = 0x09;
			}
			else if (game == DKR)
			{
				// unknown 5 bytes
				start = start - 5;
				tempBufferNew[start] = 0x04;
				tempBufferNew[start+1] = 0x03;
				tempBufferNew[start+2] = 0x00;
				tempBufferNew[start+3] = 0x00;
				tempBufferNew[start+4] = 0x09;
			}
			else if (game == MICKEYSPEEDWAY)
			{
				// unknown 5 bytes
				start = start - 5;
				tempBufferNew[start] = 0x04;
				tempBufferNew[start+1] = 0x03;
				tempBufferNew[start+2] = 0x00;
				tempBufferNew[start+3] = 0x00;
				tempBufferNew[start+4] = 0x09;
			}
			else if (game == STUNTRACER64)
			{
				start = start - 2;
				tempBufferNew[start] = 0x78;
				tempBufferNew[start+1] = 0xDA;
			}
			else if (game == RESIDENTEVIL2)
			{
				start = start - 2;
				tempBufferNew[start] = 0x68;
				tempBufferNew[start+1] = 0xDE;
			}
			else if (game == ZLB)
			{
				start = start - 0x12;
				tempBufferNew[start] = 0x5A;
				tempBufferNew[start] = 0x4C;
				tempBufferNew[start] = 0x42;
				tempBufferNew[start] = 0x00;
				tempBufferNew[start] = 0x00;
				tempBufferNew[start] = 0x00;
				tempBufferNew[start] = 0x00;
				tempBufferNew[start] = 0x01;
				tempBufferNew[start] = 0x00;
				tempBufferNew[start] = 0x00;
				tempBufferNew[start] = 0x02;
				tempBufferNew[start] = 0x60;
				tempBufferNew[start] = 0x00;
				tempBufferNew[start] = 0x00;
				tempBufferNew[start] = 0x00;
				tempBufferNew[start] = 0xC6;
				tempBufferNew[start] = 0x58;
				tempBufferNew[start] = 0x85;
			}



			if (byteFlipCompressed == true)
			{
				if ((sizeNew%2) == 1)
				{
					tempBufferNew[sizeNew-0x8] = 0;
					sizeNew++;
				}

				for (int x = 0; x < sizeNew; x=x+2)
				{
					unsigned char tempSpot = tempBufferNew[x];
					tempBufferNew[x] = tempBufferNew[x+1];
					tempBufferNew[x+1] = tempSpot;
				}
			}

			fwrite(&tempBufferNew[start], 1, (sizeNew-(start + 8)), outputFileName);	

			if (game != CONKER)
			{
				unsigned long fileSizeNew = (sizeNew-(start + 8));
				if ((fileSizeNew % 0x8) != 0)
				{
					for (int x = 0; x < (0x8-(fileSizeNew % 0x8)); x++)
					{
						if ((game == BANJOKAZOOIE) || (game == BANJOTOOIE))
						{
							unsigned char tempZero = 0xAA;
							fwrite(&tempZero, 1, 1, outputFileName);
						}
						else
						{
							unsigned char tempZero = 0;
							fwrite(&tempZero, 1, 1, outputFileName);
						}
					}
				}
			}
		

			delete [] tempBufferNew;
			fflush(outputFileName);
			fclose(outputFileName);
			return true;
		}
		else
		{
            std::cout << "Error Compressing - GZip didn't spit out a file" << std::endl;
			return false;
		}
	}
}
*/

unsigned char* GECompression::OutputDecompressedBuffer(int& fileSize, int& compressedSize)
{
	compressedSize = 0;
	if ((compressedBuffer == NULL) || (compressedBufferSize < 3))
		return NULL;


	if ((((compressedBuffer[0] << 8) | compressedBuffer[1]) != 0x1172) && (((compressedBuffer[0] << 8) | compressedBuffer[1]) != 0x1173) && (((compressedBuffer[0] << 8) | compressedBuffer[1]) != 0x68DE)&& (((compressedBuffer[0] << 8) | compressedBuffer[1]) != 0x789C) && (((compressedBuffer[0] << 8) | compressedBuffer[1]) != 0x78DA) && (((compressedBuffer[0] << 24) | (compressedBuffer[1]<<16) | (compressedBuffer[2]<<8) | (compressedBuffer[3])) != 0x1F8B0800) && (((compressedBuffer[0] << 24) | (compressedBuffer[1]<<16) | (compressedBuffer[2]<<8) | (compressedBuffer[3])) != 0x1F8B0808) && (game != BLASTCORPS) && (game != BANJOTOOIE) && (game != CONKER)  && (game != TOPGEARRALLY) && (game != JFG) && (game != DKR) && (game != JFGKIOSK) && (game != MICKEYSPEEDWAY) && (game != ZLB))
	{
		//MessageBox(NULL, "Not 1172/1173/1F8B0800/1F8B0808 Compressed", "Error", NULL);
        std::cout << "Error: Not 1172/1173/1F8B0800/1F8B0808 Compressed" << std::endl;
		return NULL;
	}

	bitsCache = 0;
	bitsRemain = 0;
	if ((game == GOLDENEYE) || (game == KILLERINSTINCT) || (game == MILO) || (game == STUNTRACER64) || (game == RESIDENTEVIL2))
		bytesIndex = 2;
	else if (game == PD)
		bytesIndex = 5;
	else if (game == BANJOKAZOOIE)
		bytesIndex = 6;
	else if ((game == DONKEYKONG64) || (game == DONKEYKONG64KIOSK) || (game == BLASTCORPS))
		bytesIndex = 0xA;
	else if ((game == BANJOTOOIE))
		bytesIndex = 0x2;
	else if (game == CONKER)
		bytesIndex = 4;
	else if (game == TOPGEARRALLY)
		bytesIndex = 0xE;
	else if ((game == JFG) || (game == JFGKIOSK) || (game == DKR) || (game == MICKEYSPEEDWAY))
		bytesIndex = 0x5;
	else if (game == ZLB)
		bytesIndex = 0x12;


	if (((game == DONKEYKONG64) || (game == DONKEYKONG64KIOSK) || (game == BLASTCORPS)) && (((compressedBuffer[0] << 24) | (compressedBuffer[1]<<16) | (compressedBuffer[2]<<8) | (compressedBuffer[3])) == 0x1F8B0808))
	{
		while (compressedBuffer[bytesIndex] != 0)
			bytesIndex++;
		bytesIndex++;
	}
	unpackTableIndex = 0;
	for (int x = 0; x < 0xFFFF; x++)
	{
		unpackTable[x].bits = 0;
		unpackTable[x].flags = 0;
		unpackTable[x].nextIndex = 0;
		unpackTable[x].wordValue = 0;
	}

	unsigned char* returnBuffer;
	returnBuffer = new unsigned char[maxByteSize];


	bool done = false;
	unsigned char compressionType;
	fileSize = 0;

	iterationCounter = 0;

	do
	{
		if (iterationCounter > 268435455)
		{
			fileSize = 0;
			if (returnBuffer != NULL)
				delete [] returnBuffer;
			return NULL;
		}
		iterationCounter++;
		done = GetNBits(1);
		if (bytesIndex >= maxByteSize)
		{
			fileSize = 0;
			if (returnBuffer != NULL)
				delete [] returnBuffer;
			return NULL;
		}
		compressionType = GetNBits(2);
		if (compressionType == 0)
		{
			if (!UncompressType0(returnBuffer, fileSize))
			{
				fileSize = 0;
				if (returnBuffer != NULL)
					delete [] returnBuffer;
				return NULL;
			}
		}
		else if (compressionType == 1)
		{
			if (!UncompressType1(returnBuffer, fileSize))
			{
				fileSize = 0;
				if (returnBuffer != NULL)
					delete [] returnBuffer;
				return NULL;
			}
		}
		else if (compressionType == 2)
		{
			if (!UncompressType2(returnBuffer, fileSize))
			{
				fileSize = 0;
				if (returnBuffer != NULL)
					delete [] returnBuffer;
				return NULL;
			}
		}
		else
		{
			fileSize = 0;
				if (returnBuffer != NULL)
					delete [] returnBuffer;
				return NULL;
		}
	} while (done != 1);

	compressedSize = bytesIndex;
	return returnBuffer;	
}

bool GECompression::UncompressType0(unsigned char* returnBuffer, int& fileSize)
{
	// discard bits

	unsigned long discardBits = bitsRemain & 0x7;
	GetNBits(discardBits); // discard begins

	unsigned short copyLen = GetNBits(16);
	GetNBits(16); // discarded

	for (int x = 0; x < copyLen; x++)
	{
		if (fileSize >= maxByteSize)
		{
			fileSize = 0;
			return false;
		}
		returnBuffer[fileSize] = GetNBits(8);
		fileSize++;

		if (iterationCounter > 268435455)
		{
			fileSize = 0;
			return false;
		}
		iterationCounter++;
	}

	return true;
}

bool GECompression::UncompressType1(unsigned char* returnBuffer, int& fileSize)
{
	bool returnValue1, returnValue2;
	int numBits1, numBits2;
	int startIndex1, startIndex2;
	CreateGlobalDecompressionTable(0, 0x101, 0, 0, 7, returnValue1, numBits1, startIndex1);
	CreateGlobalDecompressionTable(1, 0, 1, 1, 5, returnValue2, numBits2, startIndex2);
	return DecompressBasedOnTable(startIndex1, startIndex2, numBits1, numBits2, returnBuffer, fileSize);
}

bool GECompression::UncompressType2(unsigned char* returnBuffer, int& fileSize)
{
	try
	{

	for (int x = 0; x < 0x13; x++)
	{
		variableTable[x] = 0;
	}

	tableSize = (GetNBits(5)+0x101);
	fiveBits = GetNBits(5)+0x1;
	unsigned char fourBits = GetNBits(4)+0x4;

	for (int index = 0; index < fourBits; index++)
	{
		unsigned char threeBits = GetNBits(3);
		variableTable[bt2Table1B[index]] = threeBits;
	}

	bool returnValue1;
	int numBits1;
	int startIndex1;

	CreateGlobalDecompressionTable(2, 0x13, 2, 2, 7, returnValue1, numBits1, startIndex1);

	if (wordTable != NULL)
	{
		delete [] wordTable;
		wordTable = NULL;
	}
	wordTable = new unsigned long[0xFFFF];

	int wordTableSpot = 0;

	unsigned long lastWritten = 0;
	while (wordTableSpot < (tableSize + fiveBits))
	{

		if (iterationCounter > 268435455)
		{
			fileSize = 0;
			return false;
		}
		iterationCounter++;

		unsigned long tableIndex = GetNBitsAndPreserve(numBits1);
		if ((startIndex1 + tableIndex) > 0xFFFF)
		{
			fileSize = 0;
			return false;
		}
		int numBits2 = unpackTable[startIndex1 + tableIndex].bits;
		if (bytesIndex >= maxByteSize)
		{
			fileSize = 0;
			return false;
		}
		GetNBits(numBits2);
		unsigned long wordValue = unpackTable[startIndex1 + tableIndex].wordValue;
		if (unpackTable[startIndex1 + tableIndex].nextIndex == 0)
		{
			if (wordValue < 0x10)
			{
				lastWritten = wordValue;
				wordTable[wordTableSpot] = wordValue;
				wordTableSpot++;
			}
			else if (wordValue == 0x10)
			{
				int repeatLen = (GetNBits(2) + 3);
				for (int index = 0; index < repeatLen; index++)
				{
					wordTable[wordTableSpot] = lastWritten;
					wordTableSpot++;
				}
			}
			else if (wordValue == 0x11)
			{
				int repeatLen = (GetNBits(3) + 3);
				for (int index = 0; index < repeatLen; index++)
				{
					wordTable[wordTableSpot] = 0;
					wordTableSpot++;					
				}
			}
			else
			{
				int repeatLen = (GetNBits(7) + 0xB);
				for (int index = 0; index < repeatLen; index++)
				{
					wordTable[wordTableSpot] = 0;
					wordTableSpot++;					
				}
			}
		}
	}
	bool returnValue2, returnValue3;
	int numBits2, numBits3;
	int startIndex2, startIndex3;

	CreateGlobalDecompressionTable(3, 0x101, 0, 0, 9, returnValue2, numBits2, startIndex2);

	CreateGlobalDecompressionTable(4, 0, 1, 1, 6, returnValue3, numBits3, startIndex3);
	DecompressBasedOnTable(startIndex2, startIndex3, numBits2, numBits3, returnBuffer, fileSize);
	if (wordTable != NULL)
	{
		delete [] wordTable;
		wordTable = NULL;
	}
	} catch (...)
	{
		fileSize = 0;
		return false;
	}
	return true;
}

void GECompression::CreateGlobalDecompressionTable(int bit1TableChoice, int size2, int bit12STableSChoice, int bit12BTableChoice, int numBits, bool& returnValue, int& numReturnBits, int& returnStartIndex)
{
	//if (bit1TableChoice == 0) bt1Table1 else bt1Table2
	//if (bit12STableSChoice == 0) bt12Table1S else bt12Table2S
	//if (bit12BTableChoice == 0) bt12Table1B else bt12Table2B
	CString temp; // temp var del later

	tableEntry localTableEntry;
	localTableEntry.bits = 0;
	localTableEntry.flags = 0;
	localTableEntry.nextIndex = 0;
	localTableEntry.wordValue = 0;

	int table1Size = 0;

	int returnIndex = -1;

	unsigned long seventeenints1[17];
	for (int x = 0; x < 17; x++)
		seventeenints1[x] = 0;

	if (bit1TableChoice == TABLE1)
	{
		table1Size = 288;
		for (int x = 0; x < 288; x++)
		{
			seventeenints1[bt1Table1[x]]++;
		}
	}
	else if (bit1TableChoice == TABLE2)
	{
		table1Size = 30;
		for (int x = 0; x < 30; x++)
		{
			seventeenints1[bt1Table2[x]]++;
		}
	}
	else if (bit1TableChoice == VARIABLETABLE)
	{
		table1Size = 0x13;		
		for (int x = 0; x < 0x13; x++)
		{
			seventeenints1[variableTable[x]]++;			
		}
	}
	else if (bit1TableChoice == WORDTABLEBEGIN)
	{
		table1Size = tableSize;		
		for (int x = 0; x < table1Size; x++)
		{
			seventeenints1[wordTable[x]]++;			
		}
	}
	else if (bit1TableChoice == WORDTABLEEND)
	{
		table1Size = ((tableSize + fiveBits) - tableSize);
		for (int x = 0; x < table1Size; x++)
		{
			seventeenints1[wordTable[tableSize + x]]++;			
		}
	}

	int firstBit = 1;
	while (seventeenints1[firstBit] == 0)
		firstBit++;

	int lastBit = 16;	
	while (seventeenints1[lastBit] == 0)
		lastBit--;

	if (numBits < firstBit)
		numBits = firstBit;
	if (numBits > lastBit)
		numBits = lastBit;

	unsigned long v1temp = (1<<firstBit);
	if (firstBit != lastBit)
	{
		for (int bitNum = firstBit; bitNum < lastBit; bitNum++)
		{
			v1temp = ((v1temp - seventeenints1[bitNum])*2);
		}	
	}

	int oldLastBitCount = seventeenints1[lastBit];
	seventeenints1[lastBit] = v1temp;
	v1temp = v1temp - oldLastBitCount;

	unsigned long seventeenints2[17];
	for (int x = 0; x < 17; x++)
		seventeenints2[x] = 0;

	int accumulator = 0;
	for (int index = 1; index < lastBit; index++)
	{
		accumulator = accumulator + seventeenints1[index];
		seventeenints2[index+1] = accumulator;
	}


	unsigned long* moreWords;
	moreWords = new unsigned long[table1Size];
	int moreWordsIndex = 0;
	int index = 0;

	for (int x = 0; x < table1Size; x++)
	{
		moreWords[x] = 0;
	}

	for (int x = 0; x < table1Size; x++)
	{

		if (bit1TableChoice == TABLE1)
		{
			if ((bt1Table1[x]) != 0)
			{
				moreWords[seventeenints2[bt1Table1[x]]] = index;
				seventeenints2[bt1Table1[x]]++;
			}
		}
		else if (bit1TableChoice == TABLE2)
		{
			if ((bt1Table2[x]) != 0)
			{
				moreWords[seventeenints2[bt1Table2[x]]] = index;
				seventeenints2[bt1Table2[x]]++;
			}
		}
		else if (bit1TableChoice == VARIABLETABLE)
		{
			if ((variableTable[x]) != 0)
			{
				moreWords[seventeenints2[variableTable[x]]] = index;
				seventeenints2[variableTable[x]]++;	
			}
		}
		else if (bit1TableChoice == WORDTABLEBEGIN)
		{
			if ((wordTable[x]) != 0)
			{
				moreWords[seventeenints2[wordTable[x]]] = index;
				seventeenints2[wordTable[x]]++;
			}
		}
		else if (bit1TableChoice == WORDTABLEEND)
		{
			if ((wordTable[tableSize + x]) != 0)
			{
				moreWords[seventeenints2[wordTable[tableSize + x]]] = index;
				seventeenints2[wordTable[tableSize + x]]++;
			}
		}
		index++;
	}

	int stemp2_v1 = -numBits;
	int blockNum = -1;
	int bitPattern = 0;

	int unpackTableStarts[0x20000];
	int unpackTableStartsIndex = -1;

	unsigned long temp_a3 = 0;
	int thisTableStart = 0;

	for (int bitNum = firstBit; bitNum < (lastBit+1); bitNum++)
	{
		int iterationsLeft = seventeenints1[bitNum];
		unsigned long lv34 = (1<<(bitNum-1));
		int moreWordsIndex2 = table1Size;

		while (iterationsLeft)
		{
			if (iterationsLeft < 0)
				break;
			stemp2_v1 = stemp2_v1 + numBits;
			while (stemp2_v1 < bitNum)
			{
				blockNum++;

				unsigned long temp_t0 = 0;

				if (numBits < (lastBit-stemp2_v1))
					temp_t0=numBits;
				else
					temp_t0 = lastBit-stemp2_v1;

				temp_a3 = bitNum - stemp2_v1;

				if (iterationsLeft < (1<<temp_a3))
				{
					unsigned long another_var_v1= ((1 << temp_a3) - iterationsLeft);
					temp_a3++;

					index = bitNum + 1;
					while (temp_a3 < temp_t0)
					{
						if (seventeenints1[index] < (another_var_v1*2))
						{
							temp_a3++;
							another_var_v1 = another_var_v1*2 - seventeenints1[index];
						}
						index++;
					}
				}
				if (returnIndex==-1)
					returnIndex=unpackTableIndex + 1;
				
				unpackTableStartsIndex++;
				unpackTableStarts[unpackTableStartsIndex] = (unpackTableIndex+1);
				
				thisTableStart = unpackTableIndex + 1;

				if (blockNum != 0)
				{
					seventeenints2[blockNum] = bitPattern;
					localTableEntry.bits = numBits;
					localTableEntry.flags = temp_a3 + 0x10;
					localTableEntry.nextIndex= unpackTableIndex + 1;
					localTableEntry.wordValue = -1;
					unpackTable[(bitPattern>>(stemp2_v1-numBits))+unpackTableStarts[blockNum-1]].bits = localTableEntry.bits;
					unpackTable[(bitPattern>>(stemp2_v1-numBits))+unpackTableStarts[blockNum-1]].flags = localTableEntry.flags;
					unpackTable[(bitPattern>>(stemp2_v1-numBits))+unpackTableStarts[blockNum-1]].wordValue = localTableEntry.wordValue;
					unpackTable[(bitPattern>>(stemp2_v1-numBits))+unpackTableStarts[blockNum-1]].nextIndex = localTableEntry.nextIndex;
				}

				unpackTableIndex=unpackTableIndex + ((1<<temp_a3)+1);
				stemp2_v1+=numBits;
			}
			stemp2_v1 = stemp2_v1 - numBits;

			localTableEntry.bits = bitNum - stemp2_v1;
			localTableEntry.nextIndex = 0;
			if (moreWordsIndex >= moreWordsIndex2)
				localTableEntry.flags = 0x63;
			else
			{
				unsigned long tempWord = moreWords[moreWordsIndex];
				if (tempWord<(unsigned long)size2)
				{
					if (tempWord >= 0x100)
						localTableEntry.flags = 0xf;
					else
						localTableEntry.flags = 0x10;
					localTableEntry.wordValue = tempWord;
				}
				else
				{
					if (bit12STableSChoice == TABLE1)
					{
						localTableEntry.flags = bt12Table1B[moreWords[moreWordsIndex]-size2];
						localTableEntry.wordValue = bt12Table1S[moreWords[moreWordsIndex]-size2];
					}
					else if (bit12STableSChoice == TABLE2)
					{
						localTableEntry.flags = bt12Table2B[moreWords[moreWordsIndex]-size2];
						localTableEntry.wordValue = bt12Table2S[moreWords[moreWordsIndex]-size2];
					}
					else if (bit12STableSChoice == VARIABLETABLE)
					{
						// shouldn't happen

					}
				}
				moreWordsIndex++;
			}
		
			unsigned long nu_accum_a3 = (bitPattern >> stemp2_v1);
			unsigned long stride_v0 = (1<<(bitNum - stemp2_v1));
			/*if (thisTableStart==744)
			{
				if thisTableStart+nu_accum_a3==758
				{
					if stride_v0==16:
					{
						debugIt=1
					}
				}
			}*/
			while ((unsigned long)(1<<temp_a3) > nu_accum_a3)
			{
				if ((thisTableStart+nu_accum_a3) > 0xFFFF)
				{
					delete [] moreWords;
					return;
				}
				unpackTable[thisTableStart+nu_accum_a3].bits = localTableEntry.bits;
				unpackTable[thisTableStart+nu_accum_a3].flags = localTableEntry.flags;
				unpackTable[thisTableStart+nu_accum_a3].wordValue = localTableEntry.wordValue;
				unpackTable[thisTableStart+nu_accum_a3].nextIndex = localTableEntry.nextIndex;
				nu_accum_a3 = nu_accum_a3 + stride_v0;
			}

			unsigned long tempLv=lv34;
			
			while (bitPattern & tempLv)
			{
				bitPattern = bitPattern ^ tempLv;
				tempLv = tempLv >> 1;
			}
			bitPattern = bitPattern ^ tempLv;
			while((unsigned long)(bitPattern & ((1 << stemp2_v1)-1)) != seventeenints2[blockNum])
			{
				blockNum = blockNum- 1;
				stemp2_v1=0;
			}

			iterationsLeft = iterationsLeft - 1;
		}
	}
	delete [] moreWords;
	if (v1temp > 0)
	{
		returnValue = (0<(lastBit^1));
		numReturnBits = numBits;
		returnStartIndex = returnIndex;
	}
	else
	{
		returnValue = 0;
		numReturnBits = numBits;
		returnStartIndex = returnIndex;
	}
}

bool GECompression::DecompressBasedOnTable(int startIndex1, int startIndex2, int bitLen1, int bitLen2, unsigned char* returnBuffer, int& fileSize)
{
	unsigned long index = 0;
	bool exitFlag = 1;

	try
	{

	while (exitFlag)
	{

		if (iterationCounter > 268435455)
		{
			fileSize = 0;
			return false;
		}
		iterationCounter++;

		if (bytesIndex >= maxByteSize)
		{
			fileSize = 0;
			return false;
		}
		index = GetNBitsAndPreserve(bitLen1);
		if ((startIndex1 + index) > 0xFFFF)
		{
			fileSize = 0;
			return false;
		}
		tableEntry entry = unpackTable[startIndex1 + index];

		while (entry.flags > 0x10)
		{
			if (iterationCounter > 268435455)
			{
				fileSize = 0;
				return false;
			}
			iterationCounter++;

			if (bytesIndex >= maxByteSize)
			{
				fileSize = 0;
				return false;
			}
			GetNBits(entry.bits); // discard
			index = GetNBitsAndPreserve(entry.flags-0x10);
			if ((entry.nextIndex+index) > 0xFFFF)
			{
				fileSize = 0;
				return false;
			}
			entry = unpackTable[entry.nextIndex+index];
		}
		if (bytesIndex >= maxByteSize)
		{
			fileSize = 0;
			return false;
		}
		GetNBits(entry.bits); // discard
		
		if (entry.flags==0x10)
		{
			if (fileSize >= maxByteSize)
			{
				fileSize = 0;
				return false;
			}
			returnBuffer[fileSize] = entry.wordValue;
			fileSize++;
		}
		else if (entry.flags < 0xf)
		{
			unsigned long copyLen = entry.wordValue + GetNBits(entry.flags);
			unsigned long index2 = GetNBitsAndPreserve(bitLen2);
			if ((startIndex2+index2) > 0xFFFF)
			{
				fileSize = 0;
				return false;
			}
			tableEntry entry2 = unpackTable[startIndex2+index2];
			while (entry2.flags>0x10)
			{

				if (iterationCounter > 268435455)
				{
					fileSize = 0;
					return false;
				}
				iterationCounter++;

				if (bytesIndex >= maxByteSize)
				{
					fileSize = 0;
					return false;
				}
				GetNBits(entry2.bits); // discard
				index2 = GetNBitsAndPreserve(entry2.flags-0x10);
				if ((entry2.nextIndex+index2) > 0xFFFF)
				{
					fileSize = 0;
					return false;
				}
				entry2 = unpackTable[entry2.nextIndex+index2];
			}
			if (bytesIndex >= maxByteSize)
			{
				fileSize = 0;
				return false;
			}
			GetNBits(entry2.bits); // discard

			unsigned long endOffset1 = entry2.wordValue;
			unsigned long endOffset2 = GetNBits(entry2.flags);
			unsigned long start = fileSize-endOffset1-endOffset2;
			unsigned long end = start + copyLen;
			for (unsigned long x = start; x < end; x++)
			{
				if ((((signed long) start) < 0) || ((((signed long) end) < 0)) || ((start > maxByteSize)) || ((end > maxByteSize)))
				{
					fileSize = 0;
					return false;
				}
				returnBuffer[fileSize] = returnBuffer[x];
				fileSize++;
			}
		}
		else
			exitFlag = 0;
	}

	} catch (...)
	{
		return false;
	}
	return true;
}
