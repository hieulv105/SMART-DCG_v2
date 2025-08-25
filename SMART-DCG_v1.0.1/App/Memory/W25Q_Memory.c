/*
 * Memory.c
 *
 *  Created on: Aug 2, 2023
 *      Author: Admin
 */

#include "W25Q_Memory.h"

#define NUMBLOCK 			256		// number of total blocks for 16Mb flash, 32x16x16 pages and 32x16x16x256 Bytes
#define W25QXX_DUMMY_BYTE 	0xA5	// dummy byte to create dummy clock, to receiver data
#define FREE_RTOS 0

#if FREE_RTOS
#include "cmsis_os.h"
#define W25qxx_Delay(delay) osDelay(delay)
#else
#define W25qxx_Delay(delay) HAL_Delay(delay)
#endif


w25qxx_t w25qxx;


/**
 * @brief  This function to send commands and receive data
 * @param  pTxData: command to send
 * @retval pRxData: received data
 */
uint8_t W25qxx_Spi(uint8_t pTxData)
{
	uint8_t pRxData;
	HAL_SPI_TransmitReceive(&_W25QXX_SPI, &pTxData, &pRxData, 1, 100);
	return pRxData;	// return pointer to reception data buffer
}

/**
 * @brief  This functions to Read JEDEC ID (9Fh)
 * @param  None
 * @retval Return 24 bit of ID: MFN_ID-MEM_ID-CAPACITY_ID
 */
uint32_t W25qxx_ReadID(void)
{
	uint32_t iD;
	uint8_t Temp[3];

	W25Q_CS_LOW();
	W25qxx_Spi(0x9F);							// Send 1 byte Instruction
	Temp[0] = W25qxx_Spi(W25QXX_DUMMY_BYTE);	// Read 1 byte Manufacturer ID
	Temp[1] = W25qxx_Spi(W25QXX_DUMMY_BYTE);	// Read 1 byte Memory Type ID
	Temp[2] = W25qxx_Spi(W25QXX_DUMMY_BYTE);	// Read 1 byte Capacity ID
	W25Q_CS_HIGH();

	iD = (Temp[0] << 16) | (Temp[1] << 8) | Temp[2];	// Combine 3 byte ID
	return iD;
}

/**
 * @brief  This functions to Read Unique ID Number(4Bh)
 * @param  None
 * @retval None
 */
void W25qxx_ReadUniqID(void)
{
	W25Q_CS_LOW();
	W25qxx_Spi(0x4B);					// Send 1 byte Instruction
	for (uint8_t i = 0; i < 4; i++)		// Send 4 byte Dummy
		W25qxx_Spi(W25QXX_DUMMY_BYTE);
	for (uint8_t i = 0; i < 8; i++)		// Read 8 byte Unique ID (64-bit Unique Serial Number)
		w25qxx.UniqID[i] = W25qxx_Spi(W25QXX_DUMMY_BYTE);
	W25Q_CS_HIGH();
}

/**
 * @brief  This functions to Write Enable (06h)
 * @param  None
 * @retval None
 */
void W25qxx_WriteEnable(void)
{
	W25Q_CS_LOW();
	W25qxx_Spi(0x06);	// Write Enable
	W25Q_CS_HIGH();
}

/**
 * @brief  This functions to Write Disable (04h)
 * @param  None
 * @retval None
 */
void W25qxx_WriteDisable(void)
{
	W25Q_CS_LOW();
	W25qxx_Spi(0x04);	// Write Disable
	W25Q_CS_HIGH();
	W25qxx_Delay(5);	// 5ms delay
}

/**
 * @brief  This functions to Read Status Register
 * @param  Read Status Register-1 (05h)
 * @param  Read Status Register-2 (35h)
 * @param  Read Status Register-3 (15h)
 * @retval None
 */
uint8_t W25qxx_ReadStatusRegister(uint8_t SelectStatusRegister_1_2_3)
{
	uint8_t status = 0;
	W25Q_CS_LOW();
	if (SelectStatusRegister_1_2_3 == 1)
	{
		W25qxx_Spi(0x05);
		status = W25qxx_Spi(W25QXX_DUMMY_BYTE);
		w25qxx.StatusRegister1 = status;
	}
	else if (SelectStatusRegister_1_2_3 == 2)
	{
		W25qxx_Spi(0x35);
		status = W25qxx_Spi(W25QXX_DUMMY_BYTE);
		w25qxx.StatusRegister2 = status;
	}
	else
	{
		W25qxx_Spi(0x15);
		status = W25qxx_Spi(W25QXX_DUMMY_BYTE);
		w25qxx.StatusRegister3 = status;
	}
	W25Q_CS_HIGH();
	return status;
}

/**
 * @brief  This functions to Write Status Register
 * @param  Write Status Register-1 (01h)
 * @param  Write Status Register-2 (31h)
 * @param  Write Status Register-3 (11h)
 * @retval None
 */
void W25qxx_WriteStatusRegister(uint8_t SelectStatusRegister_1_2_3, uint8_t Data)
{
	W25Q_CS_LOW();
	if (SelectStatusRegister_1_2_3 == 1)
	{
		W25qxx_Spi(0x01);
		w25qxx.StatusRegister1 = Data;
	}
	else if (SelectStatusRegister_1_2_3 == 2)
	{
		W25qxx_Spi(0x31);
		w25qxx.StatusRegister2 = Data;
	}
	else
	{
		W25qxx_Spi(0x11);
		w25qxx.StatusRegister3 = Data;
	}
	W25qxx_Spi(Data);
	W25Q_CS_HIGH();
}

/**
 * @brief  This functions to
 * @param  None
 * @retval None
 */
bool W25qxx_WaitForWriteEnd(void)
{
	W25Q_CS_LOW();
	W25qxx_Spi(0x05);	// read status register 1
	w25qxx.StatusRegister1 = W25qxx_Spi(W25QXX_DUMMY_BYTE);
	W25Q_CS_HIGH();

	if ((w25qxx.StatusRegister1 & 0x01) == 0x01)
		return	false;
//	}
//	W25qxx_Delay(1);
//	W25Q_CS_LOW();
//	W25qxx_Spi(0x05);	// read status register 1
//	do
//	{
//		w25qxx.StatusRegister1 = W25qxx_Spi(W25QXX_DUMMY_BYTE);
//		W25qxx_Delay(1);
//	} while ((w25qxx.StatusRegister1 & 0x01) == 0x01);
//	W25Q_CS_HIGH();

	return	true;
}

/**
 * @brief  This functions to show some parameter of device
 * @param  None
 * @retval None
 */
uint16_t W25qxx_Check_Infomation(void)
{
	uint32_t id = W25qxx_ReadID();
	switch (id & 0x000000FF)
	{
		case 0x20: // 	w25q512
			w25qxx.ID = W25Q512;
			w25qxx.BlockCount = 1024;

			break;
		case 0x19: // 	w25q256
			w25qxx.ID = W25Q256;
			w25qxx.BlockCount = 512;

			break;
		case 0x18: // 	w25q128
			w25qxx.ID = W25Q128;
			w25qxx.BlockCount = 256;

			break;
		case 0x17: //	w25q64
			w25qxx.ID = W25Q64;
			w25qxx.BlockCount = 128;

			break;
		case 0x16: //	w25q32
			w25qxx.ID = W25Q32;
			w25qxx.BlockCount = 64;

			break;
		case 0x15: //	w25q16
			w25qxx.ID = W25Q16;
			w25qxx.BlockCount = 32;

			break;
		case 0x14: //	w25q80
			w25qxx.ID = W25Q80;
			w25qxx.BlockCount = 16;

			break;
		case 0x13: //	w25q40
			w25qxx.ID = W25Q40;
			w25qxx.BlockCount = 8;

			break;
		case 0x12: //	w25q20
			w25qxx.ID = W25Q20;
			w25qxx.BlockCount = 4;

			break;
		case 0x11: //	w25q10
			w25qxx.ID = W25Q10;
			w25qxx.BlockCount = 2;

			break;
		default:
			return false;
	}
	w25qxx.PageSize = 256;							// 256 bytes 
	w25qxx.SectorSize = 4096;						// 4kB * 1024 = 4096 bytes
	w25qxx.SectorCount = w25qxx.BlockCount * 16;	// 256 block * 16 sector/block = 4096 sector
	w25qxx.PageCount = (w25qxx.SectorCount * w25qxx.SectorSize)	/ w25qxx.PageSize;	// (4096 Sector * 4096 bytes) / 256 bytes = 65536
	w25qxx.BlockSize = w25qxx.SectorSize * 16;		// 4096 bytes * 16 = 65536 bytes (64kB)
	w25qxx.Capacity_In_KByte = (w25qxx.SectorCount * w25qxx.SectorSize) / 1024;		// 16384 Kbytes
	w25qxx.Capacity_In_MByte = w25qxx.Capacity_In_KByte / 1024;						// 16 Mbytes
	W25qxx_ReadUniqID();
	W25qxx_ReadStatusRegister(1);
	W25qxx_ReadStatusRegister(2);
	W25qxx_ReadStatusRegister(3);
	return true;
}

/**
 * @brief  This functions to Erase Chip (require 40s(typ), 200s(max))
 * @param  None
 * @retval None
 */
void W25qxx_EraseChip(void)
{
	W25qxx_WriteEnable();
	W25Q_CS_LOW();
	W25qxx_Spi(0xC7);
	W25Q_CS_HIGH();
}

/**
 * @brief  This functions to Erase Block (require 120ms(typ), 1600ms(max))
 * @param  Address of Block
 * @retval None
 */
void W25qxx_EraseBlock(uint32_t BlockAddr)
{
	W25qxx_WaitForWriteEnd();
	BlockAddr = BlockAddr * w25qxx.SectorSize * 16;
	W25qxx_WriteEnable();
	W25Q_CS_LOW();
	if (w25qxx.ID >= W25Q256)
	{
		W25qxx_Spi(0xDC);
		W25qxx_Spi((BlockAddr & 0xFF000000) >> 24);
	}
	else
	{
		W25qxx_Spi(0xD8);
	}
	W25qxx_Spi((BlockAddr & 0xFF0000) >> 16);
	W25qxx_Spi((BlockAddr & 0xFF00) >> 8);
	W25qxx_Spi(BlockAddr & 0xFF);
	W25Q_CS_HIGH();
	W25qxx_WaitForWriteEnd();

	W25qxx_Delay(150);
}

uint32_t W25qxx_PageToSector(uint32_t PageAddress) {
	return ((PageAddress * w25qxx.PageSize) / w25qxx.SectorSize);
}

uint32_t W25qxx_PageToBlock(uint32_t PageAddress) {
	return ((PageAddress * w25qxx.PageSize) / w25qxx.BlockSize);
}

uint32_t W25qxx_SectorToBlock(uint32_t SectorAddress) {
	return ((SectorAddress * w25qxx.SectorSize) / w25qxx.BlockSize);
}

uint32_t W25qxx_SectorToPage(uint32_t SectorAddress) {
	return (SectorAddress * w25qxx.SectorSize) / w25qxx.PageSize;
}

uint32_t W25qxx_BlockToPage(uint32_t BlockAddress) {
	return (BlockAddress * w25qxx.BlockSize) / w25qxx.PageSize;
}

/**
 * @brief  This functions to check Page is Empty
 * @param  None
 * @retval None
 */
bool W25qxx_IsEmptyPage(uint32_t Page_Address, uint32_t OffsetInByte, uint32_t NumByteToCheck_up_to_PageSize)
{
	uint32_t i;
	uint8_t pBuffer[32];
	uint32_t WorkAddress;
	if (((NumByteToCheck_up_to_PageSize + OffsetInByte) > w25qxx.PageSize) || (NumByteToCheck_up_to_PageSize == 0))
		NumByteToCheck_up_to_PageSize = w25qxx.PageSize - OffsetInByte;

	for (i = OffsetInByte; i < w25qxx.PageSize; i += sizeof(pBuffer))
	{
		HAL_GPIO_WritePin(_W25QXX_CS_GPIO, _W25QXX_CS_PIN, GPIO_PIN_RESET);
		WorkAddress = (i + Page_Address * w25qxx.PageSize);
		if (w25qxx.ID >= W25Q256)
		{
			W25qxx_Spi(0x0C);
			W25qxx_Spi((WorkAddress & 0xFF000000) >> 24);
		}
		else
		{
			W25qxx_Spi(0x0B);
		}
		W25qxx_Spi((WorkAddress & 0xFF0000) >> 16);
		W25qxx_Spi((WorkAddress & 0xFF00) >> 8);
		W25qxx_Spi(WorkAddress & 0xFF);
		W25qxx_Spi(0);
		HAL_SPI_Receive(&_W25QXX_SPI, pBuffer, sizeof(pBuffer), 100);
		W25Q_CS_HIGH();
		for (uint8_t x = 0; x < sizeof(pBuffer); x++)
		{
			if (pBuffer[x] != 0xFF)		return false;
		}
	}
	if ((w25qxx.PageSize + OffsetInByte) % sizeof(pBuffer) != 0)
	{
		i -= sizeof(pBuffer);
		for (; i < w25qxx.PageSize; i++)
		{
			W25Q_CS_LOW();
			WorkAddress = (i + Page_Address * w25qxx.PageSize);
			W25qxx_Spi(0x0B);
			if (w25qxx.ID >= W25Q256)
			{
				W25qxx_Spi(0x0C);
				W25qxx_Spi((WorkAddress & 0xFF000000) >> 24);
			}
			else
			{
				W25qxx_Spi(0x0B);
			}
			W25qxx_Spi((WorkAddress & 0xFF0000) >> 16);
			W25qxx_Spi((WorkAddress & 0xFF00) >> 8);
			W25qxx_Spi(WorkAddress & 0xFF);
			W25qxx_Spi(0);
			HAL_SPI_Receive(&_W25QXX_SPI, pBuffer, 1, 100);
			W25Q_CS_HIGH();
			if (pBuffer[0] != 0xFF)		return false;
		}
	}
	return true;
}

/**
 * @brief  This functions to check Sector is Empty
 * @param  None
 * @retval None
 */
bool W25qxx_IsEmptySector(uint32_t Sector_Address, uint32_t OffsetInByte, uint32_t NumByteToCheck_up_to_SectorSize)
{
	uint32_t i;
	uint8_t pBuffer[32];
	uint32_t WorkAddress;

	if ((NumByteToCheck_up_to_SectorSize > w25qxx.SectorSize) || (NumByteToCheck_up_to_SectorSize == 0))
		NumByteToCheck_up_to_SectorSize = w25qxx.SectorSize;

	for (i = OffsetInByte; i < w25qxx.SectorSize; i += sizeof(pBuffer))
	{
		W25Q_CS_LOW();
		WorkAddress = (i + Sector_Address * w25qxx.SectorSize);
		if (w25qxx.ID >= W25Q256)
		{
			W25qxx_Spi(0x0C);
			W25qxx_Spi((WorkAddress & 0xFF000000) >> 24);
		}
		else
		{
			W25qxx_Spi(0x0B);
		}
		W25qxx_Spi((WorkAddress & 0xFF0000) >> 16);
		W25qxx_Spi((WorkAddress & 0xFF00) >> 8);
		W25qxx_Spi(WorkAddress & 0xFF);
		W25qxx_Spi(0);
		HAL_SPI_Receive(&_W25QXX_SPI, pBuffer, sizeof(pBuffer), 100);
		W25Q_CS_HIGH();
		for (uint8_t x = 0; x < sizeof(pBuffer); x++)
		{
			if (pBuffer[x] != 0xFF)		return false;
		}
	}
	if ((w25qxx.SectorSize + OffsetInByte) % sizeof(pBuffer) != 0)
	{
		i -= sizeof(pBuffer);
		for (; i < w25qxx.SectorSize; i++)
		{
			W25Q_CS_LOW();
			WorkAddress = (i + Sector_Address * w25qxx.SectorSize);
			if (w25qxx.ID >= W25Q256)
			{
				W25qxx_Spi(0x0C);
				W25qxx_Spi((WorkAddress & 0xFF000000) >> 24);
			}
			else
			{
				W25qxx_Spi(0x0B);
			}
			W25qxx_Spi((WorkAddress & 0xFF0000) >> 16);
			W25qxx_Spi((WorkAddress & 0xFF00) >> 8);
			W25qxx_Spi(WorkAddress & 0xFF);
			W25qxx_Spi(0);
			HAL_SPI_Receive(&_W25QXX_SPI, pBuffer, 1, 100);
			W25Q_CS_HIGH();
			if (pBuffer[0] != 0xFF)		return false;
		}
	}
	return true;
}

/**
 * @brief  This functions to check Block is Empty
 * @param  None
 * @retval None
 */
bool W25qxx_IsEmptyBlock(uint32_t Block_Address, uint32_t OffsetInByte, uint32_t NumByteToCheck_up_to_BlockSize)
{
	uint32_t i;
	uint8_t pBuffer[32];
	uint32_t WorkAddress;

	if ((NumByteToCheck_up_to_BlockSize > w25qxx.BlockSize) || (NumByteToCheck_up_to_BlockSize == 0))
		NumByteToCheck_up_to_BlockSize = w25qxx.BlockSize;

	for (i = OffsetInByte; i < w25qxx.BlockSize; i += sizeof(pBuffer))
	{
		W25Q_CS_LOW();
		WorkAddress = (i + Block_Address * w25qxx.BlockSize);

		if (w25qxx.ID >= W25Q256)
		{
			W25qxx_Spi(0x0C);
			W25qxx_Spi((WorkAddress & 0xFF000000) >> 24);
		}
		else
		{
			W25qxx_Spi(0x0B);
		}
		W25qxx_Spi((WorkAddress & 0xFF0000) >> 16);
		W25qxx_Spi((WorkAddress & 0xFF00) >> 8);
		W25qxx_Spi(WorkAddress & 0xFF);
		W25qxx_Spi(0);
		HAL_SPI_Receive(&_W25QXX_SPI, pBuffer, sizeof(pBuffer), 100);
		W25Q_CS_HIGH();
		for (uint8_t x = 0; x < sizeof(pBuffer); x++)
		{
			if (pBuffer[x] != 0xFF)	return false;
		}
	}
	if ((w25qxx.BlockSize + OffsetInByte) % sizeof(pBuffer) != 0)
	{
		i -= sizeof(pBuffer);
		for (; i < w25qxx.BlockSize; i++)
		{
			W25Q_CS_LOW();
			WorkAddress = (i + Block_Address * w25qxx.BlockSize);

			if (w25qxx.ID >= W25Q256)
			{
				W25qxx_Spi(0x0C);
				W25qxx_Spi((WorkAddress & 0xFF000000) >> 24);
			}
			else
			{
				W25qxx_Spi(0x0B);
			}
			W25qxx_Spi((WorkAddress & 0xFF0000) >> 16);
			W25qxx_Spi((WorkAddress & 0xFF00) >> 8);
			W25qxx_Spi(WorkAddress & 0xFF);
			W25qxx_Spi(0);
			HAL_SPI_Receive(&_W25QXX_SPI, pBuffer, 1, 100);
			W25Q_CS_HIGH();
			if (pBuffer[0] != 0xFF)	return false;
		}
	}
	return true;
}

/**
 * @brief  This functions to Write Byte
 * @param  None
 * @retval None
 */
void W25qxx_WriteByte(uint8_t pBuffer, uint32_t WriteAddr_inBytes)
{
	W25qxx_WaitForWriteEnd();
	W25qxx_WriteEnable();

	if (w25qxx.ID >= W25Q256)
	{
		W25qxx_Spi(0x12);
		W25qxx_Spi((WriteAddr_inBytes & 0xFF000000) >> 24);
	}
	else
	{
		W25qxx_Spi(0x02);
	}
	W25qxx_Spi((WriteAddr_inBytes & 0xFF0000) >> 16);
	W25qxx_Spi((WriteAddr_inBytes & 0xFF00) >> 8);
	W25qxx_Spi(WriteAddr_inBytes & 0xFF);
	W25qxx_Spi(pBuffer);
	W25Q_CS_HIGH();
}

/**
 * @brief  This functions to Write Sector
 * @param  None
 * @retval None
 */
void W25qxx_WriteSector(uint8_t *pBuffer, uint32_t Sector_Address, uint32_t OffsetInByte, uint32_t NumByteToWrite_up_to_SectorSize)
{
	if ((NumByteToWrite_up_to_SectorSize > w25qxx.SectorSize) || (NumByteToWrite_up_to_SectorSize == 0))
		NumByteToWrite_up_to_SectorSize = w25qxx.SectorSize;

	if (OffsetInByte >= w25qxx.SectorSize)
	{
		return;
	}
	uint32_t StartPage;
	int32_t BytesToWrite;
	uint32_t LocalOffset;
	if ((OffsetInByte + NumByteToWrite_up_to_SectorSize) > w25qxx.SectorSize)
		BytesToWrite = w25qxx.SectorSize - OffsetInByte;
	else
		BytesToWrite = NumByteToWrite_up_to_SectorSize;
	StartPage = W25qxx_SectorToPage(Sector_Address) + (OffsetInByte / w25qxx.PageSize);
	LocalOffset = OffsetInByte % w25qxx.PageSize;
	do
	{
		W25qxx_WritePage(pBuffer, StartPage, LocalOffset, BytesToWrite);
		StartPage++;
		BytesToWrite -= w25qxx.PageSize - LocalOffset;
		pBuffer += w25qxx.PageSize - LocalOffset;
		LocalOffset = 0;
	} while (BytesToWrite > 0);
}

/**
 * @brief  This functions to Write Block
 * @param  None
 * @retval None
 */
void W25qxx_WriteBlock(uint8_t *pBuffer, uint32_t Block_Address, uint32_t OffsetInByte, uint32_t NumByteToWrite_up_to_BlockSize)
{
	if ((NumByteToWrite_up_to_BlockSize > w25qxx.BlockSize) || (NumByteToWrite_up_to_BlockSize == 0))
		NumByteToWrite_up_to_BlockSize = w25qxx.BlockSize;

	if (OffsetInByte >= w25qxx.BlockSize)
	{
		return;
	}
	uint32_t StartPage;
	int32_t BytesToWrite;
	uint32_t LocalOffset;
	if ((OffsetInByte + NumByteToWrite_up_to_BlockSize) > w25qxx.BlockSize)
		BytesToWrite = w25qxx.BlockSize - OffsetInByte;
	else
		BytesToWrite = NumByteToWrite_up_to_BlockSize;
	StartPage = W25qxx_BlockToPage(Block_Address) + (OffsetInByte / w25qxx.PageSize);
	LocalOffset = OffsetInByte % w25qxx.PageSize;
	do
	{
		W25qxx_WritePage(pBuffer, StartPage, LocalOffset, BytesToWrite);
		StartPage++;
		BytesToWrite -= w25qxx.PageSize - LocalOffset;
		pBuffer += w25qxx.PageSize - LocalOffset;
		LocalOffset = 0;
	} while (BytesToWrite > 0);
}

/**
 * @brief  This functions to Read byte
 * @param  None
 * @retval None
 */
void W25qxx_ReadByte(uint8_t *pBuffer, uint32_t Bytes_Address)
{
	W25Q_CS_LOW();
	if (w25qxx.ID >= W25Q256)
	{
		W25qxx_Spi(0x0C);
		W25qxx_Spi((Bytes_Address & 0xFF000000) >> 24);
	}
	else
	{
		W25qxx_Spi(0x0B);
	}
	W25qxx_Spi((Bytes_Address & 0xFF0000) >> 16);
	W25qxx_Spi((Bytes_Address & 0xFF00) >> 8);
	W25qxx_Spi(Bytes_Address & 0xFF);
	W25qxx_Spi(0);
	*pBuffer = W25qxx_Spi(W25QXX_DUMMY_BYTE);
	W25Q_CS_HIGH();
}

/**
 * @brief  This functions to Read Bytes
 * @param  None
 * @retval None
 */
void W25qxx_ReadBytes(uint8_t *pBuffer, uint32_t ReadAddr, uint32_t NumByteToRead)
{
	W25Q_CS_LOW();
	if (w25qxx.ID >= W25Q256)
	{
		W25qxx_Spi(0x0C);
		W25qxx_Spi((ReadAddr & 0xFF000000) >> 24);
	}
	else
	{
		W25qxx_Spi(0x0B);	// Fast Read
	}
	W25qxx_Spi((ReadAddr & 0xFF0000) >> 16);
	W25qxx_Spi((ReadAddr & 0xFF00) >> 8);
	W25qxx_Spi(ReadAddr & 0xFF);
	W25qxx_Spi(0);
	HAL_SPI_Receive(&_W25QXX_SPI, pBuffer, NumByteToRead, 2000);
	W25Q_CS_HIGH();
}

/**
 * @brief  This functions to Read Page
 * @param  None
 * @retval None
 */
void W25qxx_ReadPage(uint8_t *pBuffer, uint32_t Page_Address, uint32_t OffsetInByte, uint32_t NumByteToRead_up_to_PageSize)
{
	if ((NumByteToRead_up_to_PageSize > w25qxx.PageSize) || (NumByteToRead_up_to_PageSize == 0))
		NumByteToRead_up_to_PageSize = w25qxx.PageSize;
	if ((OffsetInByte + NumByteToRead_up_to_PageSize) > w25qxx.PageSize)
		NumByteToRead_up_to_PageSize = w25qxx.PageSize - OffsetInByte;

	Page_Address = Page_Address * w25qxx.PageSize + OffsetInByte;
	W25Q_CS_LOW();
	if (w25qxx.ID >= W25Q256)
	{
		W25qxx_Spi(0x0C);
		W25qxx_Spi((Page_Address & 0xFF000000) >> 24);
	}
	else
	{
		W25qxx_Spi(0x0B);
	}
	W25qxx_Spi((Page_Address & 0xFF0000) >> 16);
	W25qxx_Spi((Page_Address & 0xFF00) >> 8);
	W25qxx_Spi(Page_Address & 0xFF);
	W25qxx_Spi(0);
	HAL_SPI_Receive(&_W25QXX_SPI, pBuffer, NumByteToRead_up_to_PageSize, 100);
	W25Q_CS_HIGH();
}

/**
 * @brief  This functions to Read Sector
 * @param  None
 * @retval None
 */
void W25qxx_ReadSector(uint8_t *pBuffer, uint32_t Sector_Address, uint32_t OffsetInByte, uint32_t NumByteToRead_up_to_SectorSize)
{
	if ((NumByteToRead_up_to_SectorSize > w25qxx.SectorSize) || (NumByteToRead_up_to_SectorSize == 0))
	{
		NumByteToRead_up_to_SectorSize = w25qxx.SectorSize;
	}

	if (OffsetInByte >= w25qxx.SectorSize)
	{
		return;
	}

	uint32_t StartPage;
	int32_t BytesToRead;
	uint32_t LocalOffset;

	if ((OffsetInByte + NumByteToRead_up_to_SectorSize) > w25qxx.SectorSize)
	{
		BytesToRead = w25qxx.SectorSize - OffsetInByte;
	}
	else
	{
		BytesToRead = NumByteToRead_up_to_SectorSize;
	}

	StartPage = W25qxx_SectorToPage(Sector_Address) + (OffsetInByte / w25qxx.PageSize);
	LocalOffset = OffsetInByte % w25qxx.PageSize;
	do
	{
		W25qxx_ReadPage(pBuffer, StartPage, LocalOffset, BytesToRead);
		StartPage++;
		BytesToRead -= w25qxx.PageSize - LocalOffset;
		pBuffer += w25qxx.PageSize - LocalOffset;
		LocalOffset = 0;
	} while (BytesToRead > 0);
}

/**
 * @brief  This functions to Read Block
 * @param
 * @retval None
 */
void W25qxx_ReadBlock(uint8_t *pBuffer, uint32_t Block_Address,	uint32_t OffsetInByte, uint32_t NumByteToRead_up_to_BlockSize)
{
	if ((NumByteToRead_up_to_BlockSize > w25qxx.BlockSize) || (NumByteToRead_up_to_BlockSize == 0))
	{
		NumByteToRead_up_to_BlockSize = w25qxx.BlockSize;
	}
	if (OffsetInByte >= w25qxx.BlockSize)
	{
		return;
	}
	uint32_t StartPage;
	int32_t BytesToRead;
	uint32_t LocalOffset;

	if ((OffsetInByte + NumByteToRead_up_to_BlockSize) > w25qxx.BlockSize)
	{
		BytesToRead = w25qxx.BlockSize - OffsetInByte;
	}
	else
	{
		BytesToRead = NumByteToRead_up_to_BlockSize;
	}

	StartPage = W25qxx_BlockToPage(Block_Address) + (OffsetInByte / w25qxx.PageSize);
	LocalOffset = OffsetInByte % w25qxx.PageSize;
	do {
		W25qxx_ReadPage(pBuffer, StartPage, LocalOffset, BytesToRead);
		StartPage++;
		BytesToRead -= w25qxx.PageSize - LocalOffset;
		pBuffer += w25qxx.PageSize - LocalOffset;
		LocalOffset = 0;
	} while (BytesToRead > 0);
}

/**
 * @brief  This functions to Write Page
 * @param  None
 * @retval None
 */
uint16_t W25qxx_WritePage(uint8_t *pBuffer, uint16_t Page_Address, uint16_t OffsetInByte, uint16_t NumByteToWrite_up_to_PageSize)
{
	static	uint16_t	TimeOut = 0;

	if(W25qxx_WaitForWriteEnd()==false)
	{
		if(++TimeOut > 250)
		{
			TimeOut = 0;
			return	TIME_OUT;
		}
		else	return	BUZY;
	}
	else
	{
		W25qxx_WriteEnable();
		if (((NumByteToWrite_up_to_PageSize + OffsetInByte) > w25qxx.PageSize) || (NumByteToWrite_up_to_PageSize == 0))
			NumByteToWrite_up_to_PageSize = w25qxx.PageSize - OffsetInByte;
		if ((OffsetInByte + NumByteToWrite_up_to_PageSize) > w25qxx.PageSize)
			NumByteToWrite_up_to_PageSize = w25qxx.PageSize - OffsetInByte;

		Page_Address = (Page_Address * w25qxx.PageSize) + OffsetInByte;
		W25Q_CS_LOW();
		if (w25qxx.ID >= W25Q256)
		{
			W25qxx_Spi(0x12);
			W25qxx_Spi((Page_Address & 0xFF000000) >> 24);
		}
		else
		{
			W25qxx_Spi(0x02);
		}
		W25qxx_Spi((Page_Address & 0xFF0000) >> 16);
		W25qxx_Spi((Page_Address & 0xFF00) >> 8);
		W25qxx_Spi(Page_Address & 0xFF);
		TimeOut = HAL_SPI_Transmit(&_W25QXX_SPI, pBuffer, NumByteToWrite_up_to_PageSize, 100);

		W25Q_CS_HIGH();
		if(TimeOut==HAL_OK)		return	ACK_OK;
		else
		{
			TimeOut = 0;
			return	RETURN_ERROR;
		}
	}
	return	BUZY;
}


/**
 * @brief  This functions to Erase Sector (require 40ms(typ), 400ms(max))
 * @param  Address of Sector
 * @retval None
 */
uint16_t W25qxx_EraseSector(uint32_t SectorAddr)
{
	static	uint16_t	TimeOut = 0;

	if(W25qxx_WaitForWriteEnd()==false)
	{
		if(++TimeOut > 250)
		{
			TimeOut = 0;
			return	TIME_OUT;
		}
		else	return	BUZY;
	}
	else
	{
		W25qxx_WriteEnable();
		SectorAddr = SectorAddr * w25qxx.SectorSize;
		W25Q_CS_LOW();
		if (w25qxx.ID >= W25Q256)
		{
			W25qxx_Spi(0x21);
			W25qxx_Spi((SectorAddr & 0xFF000000) >> 24);
		}
		else
		{
			W25qxx_Spi(0x20);
		}
		W25qxx_Spi((SectorAddr & 0xFF0000) >> 16);
		W25qxx_Spi((SectorAddr & 0xFF00) >> 8);
		W25qxx_Spi(SectorAddr & 0xFF);
		TimeOut = 0;
		W25Q_CS_HIGH();
	}
	return ACK_OK;
}
