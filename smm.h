#pragma once

constexpr unsigned int CHUNK_LINK_SIZE;

class SimpleMemoryPoolManager
{
private:
	unsigned char **m_Pools;
	unsigned char *m_Head;
	unsigned int m_PoolsSize;

	unsigned int m_ChunkSize;
	unsigned int m_NumChunksInPool;

	unsigned char *AllocateMemoryBlock();
	bool IncrementPoolArray();

	unsigned char *GetNext(unsigned char *Chunk);
	void SetNext(unsigned char * Current, unsigned char *NewNext);

public:
	SimpleMemoryPoolManager();
	~SimpleMemoryPoolManager();
	SimpleMemoryPoolManager(SimpleMemoryPoolManager &) = delete;
	SimpleMemoryPoolManager &operator=(SimpleMemoryPoolManager &) = delete;
	SimpleMemoryPoolManager &operator=(SimpleMemoryPoolManager &&) = delete;
	SimpleMemoryPoolManager(SimpleMemoryPoolManager &&) = delete;

	bool Init(unsigned int ChunkSize, unsigned int ChunkNumber);
	void *Alloc();
	void Free(void *Memory);
	void Destruct();

	inline unsigned int GetChunkSize() const { return m_ChunkSize; }
	inline unsigned int GetChunkNumber() const { return m_NumChunksInPool; }

protected:
};
