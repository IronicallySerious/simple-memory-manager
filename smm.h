#pragma once

constexpr unsigned int CHUNK_LINK_SIZE;

class SimpleMemoryManager
{
private:
	unsigned char **m_Pool;
	unsigned char *m_Head;
	unsigned int m_PoolSize;

	unsigned int m_ChunkSize;
	unsigned int m_ChunkNumber;

	bool IncrementBlockStock();

public:
	SimpleMemoryManager();
	~SimpleMemoryManager();
	SimpleMemoryManager(SimpleMemoryManager &) = delete;
	SimpleMemoryManager &operator=(SimpleMemoryManager &) = delete;
	SimpleMemoryManager &operator=(SimpleMemoryManager &&) = delete;
	SimpleMemoryManager(SimpleMemoryManager &&) = delete;

	bool Init(unsigned int ChunkSize, unsigned int ChunkNumber);
	void *Alloc();
	void Free(void *Memory);
	void Destruct();

	inline unsigned int GetChunkSize() const { return m_ChunkSize; }
	inline unsigned int GetChunkNumber() const { return m_ChunkNumber; }

protected:
};
