#ifndef WORLDGEN_H
#define WORLDGEN_H

#include <cglm/cglm.h>
#include <ecs/ecs.h>



typedef enum
{
    BLOCK_FACE_TOP,
    BLOCK_FACE_LEFT,
    BLOCK_FACE_FRONT,
    BLOCK_FACE_RIGHT,
    BLOCK_FACE_BOTTOM,
    BLOCK_FACE_BACK
}faces;

// cMesh genChunkMesh(int chunkData[CHUNK_HEIGHT][CHUNK_WIDTH][CHUNK_DEPTH]);
void noise(vec2 chunkPos, vec3 blockPos);
void genFace(float w, float h, float d, float* vertices, int* nrVertices, int* capVertices, 
    unsigned int* indices, int* nrIndices, int* CapIndices, faces faceId);
cMesh genChunk(Ecs* ecs, vec2 chunkPos);

#endif