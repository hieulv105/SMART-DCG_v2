/*
 * Memory.h
 *
 *  Created on: Aug 2, 2023
 *      Author: Admin
 *      Device: W25Q128FVSG (128 M-bit)
 */

#ifndef W25Q_MEMORY_H_
#define W25Q_MEMORY_H_

#include "stdbool.h"

#include "main.h"
#include "spi.h"
#include "Utinity.h"


extern SPI_HandleTypeDef hspi1;

#define _W25QXX_SPI			hspi1
#define _W25QXX_CS_GPIO		FLSH_CS_GPIO_Port
#define _W25QXX_CS_PIN		FLSH_CS_Pin

// Chip Select
#define W25Q_CS_HIGH()	HAL_GPIO_WritePin(FLSH_CS_GPIO_Port, FLSH_CS_Pin, GPIO_PIN_SET)		// Un-select the slave Device
#define W25Q_CS_LOW()	HAL_GPIO_WritePin(FLSH_CS_GPIO_Port, FLSH_CS_Pin, GPIO_PIN_RESET)	// Select Device

/*
// Write Protect (or Data IO2 in QuadSPI)
#define W25Q_RW_HIGH()	HAL_GPIO_WritePin(FLSH_RW_GPIO_Port, FLSH_RW_Pin, GPIO_PIN_SET)		// Modify the flash
#define W25Q_RW_LOW()	HAL_GPIO_WritePin(FLSH_RW_GPIO_Port, FLSH_RW_Pin, GPIO_PIN_RESET)	// Disable the modification

// Hold or Reset (or Data IO3 in QuadSPI)
#define W25Q_RST_HIGH()	HAL_GPIO_WritePin(FLSH_RST_GPIO_Port, FLSH_RST_Pin, GPIO_PIN_SET)
#define W25Q_RST_LOW()	HAL_GPIO_WritePin(FLSH_RST_GPIO_Port, FLSH_RST_Pin, GPIO_PIN_RESET)
*/

typedef enum
{
	W25Q10 = 1,
	W25Q20,
	W25Q40,
	W25Q80,
	W25Q16,
	W25Q32,
	W25Q64,
	W25Q128, // 8
	W25Q256,
	W25Q512,
} W25QXX_ID_t;

typedef struct
{
	W25QXX_ID_t ID;
	uint8_t UniqID[8];
	uint16_t PageSize;
	uint32_t PageCount;
	uint32_t SectorSize;
	uint32_t SectorCount;
	uint32_t BlockSize;
	uint32_t BlockCount;
	uint32_t Capacity_In_KByte;
	uint8_t Capacity_In_MByte;
	uint8_t StatusRegister1;
	uint8_t StatusRegister2;
	uint8_t StatusRegister3;
} w25qxx_t;
extern w25qxx_t w25qxx;

uint32_t W25qxx_ReadID(void);
uint16_t W25qxx_Check_Infomation(void);
uint16_t W25qxx_EraseSector(uint32_t SectorAddr);
uint16_t W25qxx_WritePage(uint8_t *pBuffer, uint16_t Page_Address, uint16_t OffsetInByte, uint16_t NumByteToWrite_up_to_PageSize);

void W25qxx_EraseChip(void);
void W25qxx_EraseBlock(uint32_t BlockAddr);
uint32_t W25qxx_PageToSector(uint32_t PageAddress);
uint32_t W25qxx_PageToBlock(uint32_t PageAddress);
uint32_t W25qxx_SectorToBlock(uint32_t SectorAddress);
uint32_t W25qxx_SectorToPage(uint32_t SectorAddress);
uint32_t W25qxx_BlockToPage(uint32_t BlockAddress);
bool W25qxx_IsEmptyPage(uint32_t Page_Address, uint32_t OffsetInByte, uint32_t NumByteToCheck_up_to_PageSize);
bool W25qxx_IsEmptySector(uint32_t Sector_Address, uint32_t OffsetInByte, uint32_t NumByteToCheck_up_to_SectorSize);
bool W25qxx_IsEmptyBlock(uint32_t Block_Address, uint32_t OffsetInByte, uint32_t NumByteToCheck_up_to_BlockSize);
void W25qxx_WriteByte(uint8_t pBuffer, uint32_t Bytes_Address);
void W25qxx_WriteSector(uint8_t *pBuffer, uint32_t Sector_Address, uint32_t OffsetInByte, uint32_t NumByteToWrite_up_to_SectorSize);
void W25qxx_WriteBlock(uint8_t *pBuffer, uint32_t Block_Address, uint32_t OffsetInByte, uint32_t NumByteToWrite_up_to_BlockSize);
void W25qxx_ReadByte(uint8_t *pBuffer, uint32_t Bytes_Address);
void W25qxx_ReadBytes(uint8_t *pBuffer, uint32_t ReadAddr, uint32_t NumByteToRead);
void W25qxx_ReadPage(uint8_t *pBuffer, uint32_t Page_Address, uint32_t OffsetInByte, uint32_t NumByteToRead_up_to_PageSize);
void W25qxx_ReadSector(uint8_t *pBuffer, uint32_t Sector_Address, uint32_t OffsetInByte, uint32_t NumByteToRead_up_to_SectorSize);
void W25qxx_ReadBlock(uint8_t *pBuffer, uint32_t Block_Address, uint32_t OffsetInByte, uint32_t NumByteToRead_up_to_BlockSize);

#endif /* W25Q_MEMORY_H_ */
