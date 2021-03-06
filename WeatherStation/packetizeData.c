/*
 * Take all of the data that we sampled, and packetize it. Meaning that we send over a set packet of data.
 * A zero within the packet of data will represent that we did not sample and send the data.
 * This data will be put onto a circular buffer that takes in object/struct
 */
#include "packetizeData.h"
#include <stdlib.h>
#include <stdio.h>


struct Packet_Data{
	uint16_t temperature;
	uint16_t barometric_Pressure;
	uint16_t altitude;
	uint16_t daylight_Level;
}Weather_Packet;



void InitializeBuffer(CircBuf * buf, uint32_t length)
{
	buf->buffer = (uint8_t*)malloc(length);
	if(buf->buffer == NULL)
	{
	  return;
	}
	buf->head = buf-> buffer;
	buf->tail = buf-> buffer;
	buf->length = length;
	buf->num_items = 0;
}

int ClearBuffer(CircBuf * buf)
{
	if(buf->head != buf->tail)
	{
		uint8_t currentItem = RemoveItemFromBuffer(buf);
		return currentItem;
	}
	else
	{
		return 0;
	}
}
void DeleteBuffer(CircBuf * buf)
{
	free(buf);
}

int BufferFull(CircBuf * buf)
{
	if(buf->num_items == buf->length)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}
int BufferEmpty(CircBuf * buf)
{
	if(buf->head == buf->tail)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}
int AddItemToBuffer(CircBuf * buf, uint8_t item)
{
	int8_t err = BufferFull(buf);
	if(err == 0)
	{
		uint8_t temp = *(buf->head);
		*(buf->head) = item;
		buf->head = buf->head + 1;
		buf->num_items ++;
	}
	else
	{
		return err;
	}
}
int RemoveItemFromBuffer(CircBuf * buf)
{
	int8_t err = BufferEmpty(buf);
	if(err == 0)
	{
		uint8_t temp = *(buf->tail);
		uint8_t tail_1 = buf->tail;
		buf->tail = buf->tail + 1;
		tail_1 = 0;
		buf->num_items --;
		return y;
	}
	else
	{
		return err;
	}
}
