#include "smm.h"

#include <stdlib.h>

bool SimpleMemoryManager::IncrementBlockStock()
{
	unsigned char **NewPool = (unsigned char **) malloc((m_PoolSize + 1) * sizeof(unsigned char *));

	if (!NewPool)
	{
		return false;
	}

	for (unsigned int i = 0; i < m_PoolSize; i++)
	{
		NewPool[i] = m_Pool[i];
	}

	m_Pool = NewPool;
}

SimpleMemoryManager::SimpleMemoryManager()
{
}

SimpleMemoryManager::~SimpleMemoryManager()
{
}

bool SimpleMemoryManager::Init(unsigned int ChunkSize, unsigned int ChunkNumber)
{
	m_ChunkSize = ChunkSize;
	m_ChunkNumber = ChunkNumber;

	// 1 block = ChunkNumber of chunks, so we start with 1 block for a start
	m_Pool = (unsigned char **) malloc(1 * ChunkSize * ChunkNumber);

	if (!m_Pool)
	{
		m_PoolSize = 0;
		return false;
	}

	m_PoolSize = 1;
	return true;
}
