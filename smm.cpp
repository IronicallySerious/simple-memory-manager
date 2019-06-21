#include "smm.h"

#include <stdlib.h>

bool SimpleMemoryPoolManager::IncrementPoolArray()
{
	unsigned char **NewPoolArray = (unsigned char **) malloc((m_PoolsSize + 1) * sizeof(unsigned char *));

	if (!NewPoolArray)
	{
		return false;
	}

	for (unsigned int i = 0; i < m_PoolsSize; i++)
	{
		NewPoolArray[i] = m_Pools[i];
	}

	m_Pools[m_PoolsSize] = AllocateMemoryBlock();

	if (m_Head)
	{
		unsigned char * Current = m_Head;
		unsigned char * Next = GetNext(m_Head);

		while (Next)
		{
			Current = Next;
			Next = GetNext(Next);
		}
		SetNext(Current, NewPoolArray[m_PoolsSize]);
	}
	else
	{
		m_Head = NewPoolArray[m_PoolsSize];
	}

	if (m_Pools)
	{
		free(m_Pools);
	}

	m_Pools = NewPoolArray;
	m_PoolsSize++;

	return true;
}

unsigned char * SimpleMemoryPoolManager::GetNext(unsigned char * Chunk)
{
	return Chunk + m_ChunkSize;
}

void SimpleMemoryPoolManager::SetNext(unsigned char * Current, unsigned char * NewNext)
{
	unsigned char *NextPointer = Current + m_ChunkSize + CHUNK_LINK_SIZE;
	NextPointer = NewNext;
}

SimpleMemoryPoolManager::SimpleMemoryPoolManager()
{
}

SimpleMemoryPoolManager::~SimpleMemoryPoolManager()
{
}

bool SimpleMemoryPoolManager::Init(unsigned int ChunkSize, unsigned int ChunkNumber)
{
	m_Pools = NULL;
	m_Head = NULL;
	m_PoolsSize = 0;

	m_ChunkSize = ChunkSize;
	m_NumChunksInPool = ChunkNumber;

	return IncrementPoolArray();
}

unsigned char *SimpleMemoryPoolManager::AllocateMemoryBlock()
{
	size_t blockSize = m_ChunkSize + CHUNK_LINK_SIZE;
	size_t blockByteSize = blockSize * m_NumChunksInPool;

	unsigned char *newPool = (unsigned char *)malloc(blockByteSize);
	if (!newPool)
	{
		return NULL;
	}

	unsigned char * NewBlock = (unsigned char *)malloc(blockByteSize);
	if (!NewBlock)
	{
		return false;
	}

	// WIP
}

void * SimpleMemoryPoolManager::Alloc()
{
}

void SimpleMemoryPoolManager::Free(void * Memory)
{
}

void SimpleMemoryPoolManager::Destruct()
{
}
