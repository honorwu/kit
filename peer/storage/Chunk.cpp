#include "Chunk.h"

namespace peer
{
    void Chunk::SetPiece(unsigned int piece_index, std::shared_ptr<kit::Buffer> buffer)
    {
        if (!pieces_[piece_index])
        {
            pieces_[piece_index] = buffer;
        }
    }

    std::shared_ptr<kit::Buffer> Chunk::GetPiece(unsigned int piece_index)
    {
        return pieces_[piece_index];
    }

    unsigned int Chunk::GetChunkSize()
    {
        return pieces_.size();
    }
}