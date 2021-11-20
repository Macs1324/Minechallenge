#ifndef WORLDGEN_C
#define WORLDGEN_C

#include <cglm/cglm.h>
#include <ecs/ecs.h>
#include <GL/glew.h>
#include "worldgen.h"
#include <perlin/perlin.h>

const int CHUNK_WIDTH = 16;
const int CHUNK_DEPTH = 16;
const int CHUNK_HEIGHT = 256;

void appendVertex(float v[8], float* vertices, int* nrVertices, int* capVertices, unsigned int* indices, int* nrIndices, int* capIndices)
{
    for(int i = 0; i < 8; i++)
    {
        while(*nrVertices + i > *capVertices)
        {
            vertices = realloc(vertices, *capVertices * sizeof(float) * 2);
            *capVertices *= 2;
            printf("%d\n", *capVertices * sizeof(float) * 2);
            if(vertices)
            {
                printf("Vertices realloc-d successfully\n");
            }
            else
            {
                printf("Failed to realloc vertices\n");
            }
        }
        vertices[(*nrVertices + i)] = v[i];
    }
    *nrVertices += 8;
}

void genFace(float w, float h, float d, float* vertices, int* nrVertices, int* capVertices, 
    unsigned int* indices, int* nrIndices, int* CapIndices, faces faceId, int blockId, int nrBlocks)
{
    float ID = (float)blockId;
    switch(faceId)
    {                    //         |        position        |               UV                  |        NORMAL       |
        case BLOCK_FACE_TOP:
            appendVertex((float[8]){w + 0.5, h + 0.5, d + 0.5, (ID + 1.0) / nrBlocks, 6.0 / 6.0,       0.0, 1.0, 0.0}, vertices, nrVertices, capVertices, indices, nrIndices, CapIndices);
            appendVertex((float[8]){w + 0.5, h + 0.5, d - 0.5, (ID + 1.0) / nrBlocks, 5.0 / 6.0,       0.0, 1.0, 0.0,}, vertices, nrVertices, capVertices, indices, nrIndices, CapIndices);
            appendVertex((float[8]){w - 0.5, h + 0.5, d - 0.5, ID / nrBlocks,         5.0 / 6.0,       0.0, 1.0, 0.0}, vertices, nrVertices, capVertices, indices, nrIndices, CapIndices);
            appendVertex((float[8]){w - 0.5, h + 0.5, d + 0.5, ID / nrBlocks,         6.0 / 6.0,       0.0, 1.0, 0.0}, vertices, nrVertices, capVertices, indices, nrIndices, CapIndices);
            break;                 
        case BLOCK_FACE_LEFT:
            appendVertex((float[8]){w - 0.5, h + 0.5, d - 0.5, (ID + 1.0) / nrBlocks, 5.0 / 6.0,       -1.0, 0.0, 0.0}, vertices, nrVertices, capVertices, indices, nrIndices, CapIndices);
            appendVertex((float[8]){w - 0.5, h - 0.5, d - 0.5, (ID + 1.0) / nrBlocks, 4.0 / 6.0,       -1.0, 0.0, 0.0}, vertices, nrVertices, capVertices, indices, nrIndices, CapIndices);
            appendVertex((float[8]){w - 0.5, h - 0.5, d + 0.5, ID / nrBlocks,         4.0 / 6.0,       -1.0, 0.0, 0.0}, vertices, nrVertices, capVertices, indices, nrIndices, CapIndices);
            appendVertex((float[8]){w - 0.5, h + 0.5, d + 0.5, ID / nrBlocks,         5.0 / 6.0,       -1.0, 0.0, 0.0}, vertices, nrVertices, capVertices, indices, nrIndices, CapIndices);
            break;
        case BLOCK_FACE_FRONT:
            appendVertex((float[8]){w + 0.5, h + 0.5, d - 0.5, (ID + 1.0) / nrBlocks, 4.0 / 6.0,       0.0, 0.0, -1.0}, vertices, nrVertices, capVertices, indices, nrIndices, CapIndices);
            appendVertex((float[8]){w + 0.5, h - 0.5, d - 0.5, (ID + 1.0) / nrBlocks, 3.0 / 6.0,       0.0, 0.0, -1.0}, vertices, nrVertices, capVertices, indices, nrIndices, CapIndices);
            appendVertex((float[8]){w - 0.5, h - 0.5, d - 0.5, ID / nrBlocks,         3.0 / 6.0,       0.0, 0.0, -1.0}, vertices, nrVertices, capVertices, indices, nrIndices, CapIndices);
            appendVertex((float[8]){w - 0.5, h + 0.5, d - 0.5, ID / nrBlocks,         4.0 / 6.0,       0.0, 0.0, -1.0}, vertices, nrVertices, capVertices, indices, nrIndices, CapIndices);
            break;

        case BLOCK_FACE_RIGHT:
            appendVertex((float[8]){w + 0.5, h + 0.5, d + 0.5, (ID + 1.0) / nrBlocks, 3.0 / 6.0,       1.0, 0.0, 0.0}, vertices, nrVertices, capVertices, indices, nrIndices, CapIndices);
            appendVertex((float[8]){w + 0.5, h - 0.5, d + 0.5, (ID + 1.0) / nrBlocks, 2.0 / 6.0,       1.0, 0.0, 0.0}, vertices, nrVertices, capVertices, indices, nrIndices, CapIndices);
            appendVertex((float[8]){w + 0.5, h - 0.5, d - 0.5, ID / nrBlocks,         2.0 / 6.0,       1.0, 0.0, 0.0}, vertices, nrVertices, capVertices, indices, nrIndices, CapIndices);
            appendVertex((float[8]){w + 0.5, h + 0.5, d - 0.5, ID / nrBlocks,         3.0 / 6.0,       1.0, 0.0, 0.0}, vertices, nrVertices, capVertices, indices, nrIndices, CapIndices);
            break; 
        case BLOCK_FACE_BOTTOM:
            appendVertex((float[8]){w + 0.5, h - 0.5, d - 0.5, (ID + 1.0) / nrBlocks, 2.0 / 6.0,       0.0, -1.0, 0.0}, vertices, nrVertices, capVertices, indices, nrIndices, CapIndices);
            appendVertex((float[8]){w + 0.5, h - 0.5, d + 0.5, (ID + 1.0) / nrBlocks, 1.0 / 6.0,       0.0, -1.0, 0.0}, vertices, nrVertices, capVertices, indices, nrIndices, CapIndices);
            appendVertex((float[8]){w - 0.5, h - 0.5, d + 0.5, ID / nrBlocks,         1.0 / 6.0,       0.0, -1.0, 0.0}, vertices, nrVertices, capVertices, indices, nrIndices, CapIndices);
            appendVertex((float[8]){w - 0.5, h - 0.5, d - 0.5, ID / nrBlocks,         2.0 / 6.0,       0.0, -1.0, 0.0}, vertices, nrVertices, capVertices, indices, nrIndices, CapIndices);
            break;

        case BLOCK_FACE_BACK:
            appendVertex((float[8]){w + 0.5, h - 0.5, d + 0.5, (ID + 1.0) / nrBlocks, 0.0 / 6.0,       0.0, 0.0, 1.0}, vertices, nrVertices, capVertices, indices, nrIndices, CapIndices);
            appendVertex((float[8]){w + 0.5, h + 0.5, d + 0.5, (ID + 1.0) / nrBlocks, 1.0 / 6.0,       0.0, 0.0, 1.0}, vertices, nrVertices, capVertices, indices, nrIndices, CapIndices);
            appendVertex((float[8]){w - 0.5, h + 0.5, d + 0.5, ID / nrBlocks,         1.0 / 6.0,       0.0, 0.0, 1.0}, vertices, nrVertices, capVertices, indices, nrIndices, CapIndices);
            appendVertex((float[8]){w - 0.5, h - 0.5, d + 0.5, ID / nrBlocks,         0.0 / 6.0,       0.0, 0.0, 1.0}, vertices, nrVertices, capVertices, indices, nrIndices, CapIndices);
            break;
    };

    float newIndices[] = {
        0, 1, 2,
        0, 2, 3
    };

    while(*nrIndices + 6 > *CapIndices)
    {
        indices = realloc(indices, *CapIndices * sizeof(unsigned int) * 2);
        *CapIndices *= 2;

        if(vertices)
            {
                printf("Indices realloc-d successfully\n");
            }
            else
            {
                printf("Failed to realloc indices\n");
            }
    }

    for(int i = 0; i < 6; i++)
    {
        indices[*nrIndices + i] = (*nrVertices / 8.0) - 4 + newIndices[i];
    }

    *nrIndices += 6;
}

cMesh genChunkMesh(int chunkData[CHUNK_HEIGHT][CHUNK_WIDTH][CHUNK_DEPTH], vec2 chunkPos, int nrBlocks)
{
    cMesh r;
    float* vertices;
    unsigned long int nrVertices = 0;
    unsigned long int capVertices = 8 * 8 * CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_DEPTH;

    int* indices;
    unsigned long int nrIndices = 0;
    unsigned long int capIndices = 6000000;

    vertices = malloc(capVertices * sizeof(float));
    indices = malloc(capIndices * sizeof(int));

    for(int h = 0; h < CHUNK_HEIGHT; h++)
    {
        for(int w = 0; w < CHUNK_WIDTH; w++)
        {
           for(int d = 0; d < CHUNK_DEPTH; d++)
            {
                int x = w + (CHUNK_WIDTH * chunkPos[0]);
                int y = h;
                int z = d + (CHUNK_DEPTH * chunkPos[1]);
                if(chunkData[h][w][d] >= 0)
                {
                    if(h == 0)
                    {
                        genFace(x, y, z, vertices, &nrVertices, &capVertices, indices, &nrIndices, &capIndices, BLOCK_FACE_BOTTOM, chunkData[h][w][d], nrBlocks);
                        if(chunkData[h + 1][w][d] < 0)
                        {
                            genFace(x, y, z, vertices, &nrVertices, &capVertices, indices, &nrIndices, &capIndices, BLOCK_FACE_TOP, chunkData[h][w][d], nrBlocks);
                        }
                    }
                    else if(h == CHUNK_HEIGHT - 1)
                    {
                        genFace(x, y, z, vertices, &nrVertices, &capVertices, indices, &nrIndices, &capIndices, BLOCK_FACE_TOP, chunkData[h][w][d], nrBlocks);
                        if(chunkData[h - 1][w][d] < 0)
                        {
                            genFace(x, y, z, vertices, &nrVertices, &capVertices, indices, &nrIndices, &capIndices, BLOCK_FACE_BOTTOM, chunkData[h][w][d], nrBlocks);
                        }
                    }
                    else
                    {
                        if(chunkData[h + 1][w][d] < 0)
                        {
                            genFace(x, y, z, vertices, &nrVertices, &capVertices, indices, &nrIndices, &capIndices, BLOCK_FACE_TOP, chunkData[h][w][d], nrBlocks);
                        }

                        if(chunkData[h - 1][w][d] < 0)
                        {
                            genFace(x, y, z, vertices, &nrVertices, &capVertices, indices, &nrIndices, &capIndices, BLOCK_FACE_BOTTOM, chunkData[h][w][d], nrBlocks);
                        }
                    }

                    if(w == 0)
                    {
                        genFace(x, y, z, vertices, &nrVertices, &capVertices, indices, &nrIndices, &capIndices, BLOCK_FACE_LEFT, chunkData[h][w][d], nrBlocks);
                        if(chunkData[h][w + 1][d] < 0)
                        {
                            genFace(x, y, z, vertices, &nrVertices, &capVertices, indices, &nrIndices, &capIndices, BLOCK_FACE_RIGHT, chunkData[h][w][d], nrBlocks);
                        }
                    }
                    else if(w == CHUNK_WIDTH - 1)
                    {
                        genFace(x, y, z, vertices, &nrVertices, &capVertices, indices, &nrIndices, &capIndices, BLOCK_FACE_RIGHT, chunkData[h][w][d], nrBlocks);
                        if(chunkData[h][w - 1][d] < 0)
                        {
                            genFace(x, y, z, vertices, &nrVertices, &capVertices, indices, &nrIndices, &capIndices, BLOCK_FACE_LEFT, chunkData[h][w][d], nrBlocks);
                        }
                    }
                    else
                    {
                        if(chunkData[h][w + 1][d] < 0)
                        {
                            genFace(x, y, z, vertices, &nrVertices, &capVertices, indices, &nrIndices, &capIndices, BLOCK_FACE_RIGHT, chunkData[h][w][d], nrBlocks);
                        }

                        if(chunkData[h][w - 1][d] < 0)
                        {
                            genFace(x, y, z, vertices, &nrVertices, &capVertices, indices, &nrIndices, &capIndices, BLOCK_FACE_LEFT, chunkData[h][w][d], nrBlocks);
                        }
                    }

                    if(d == 0)
                    {
                        genFace(x, y, z, vertices, &nrVertices, &capVertices, indices, &nrIndices, &capIndices, BLOCK_FACE_FRONT, chunkData[h][w][d], nrBlocks);
                        if(chunkData[h][w][d + 1] < 0)
                        {
                            genFace(x, y, z, vertices, &nrVertices, &capVertices, indices, &nrIndices, &capIndices, BLOCK_FACE_BACK, chunkData[h][w][d], nrBlocks);
                        }                    
                    
                    }
                    else if(d == CHUNK_DEPTH - 1)
                    {
                        genFace(x, y, z, vertices, &nrVertices, &capVertices, indices, &nrIndices, &capIndices, BLOCK_FACE_BACK, chunkData[h][w][d], nrBlocks);
                        if(chunkData[h][w][d - 1] < 0)
                        {
                            genFace(x, y, z, vertices, &nrVertices, &capVertices, indices, &nrIndices, &capIndices, BLOCK_FACE_FRONT, chunkData[h][w][d], nrBlocks);
                        }
                    }
                    else
                    {
                        if(chunkData[h][w][d + 1] < 0)
                        {
                            genFace(x, y, z, vertices, &nrVertices, &capVertices, indices, &nrIndices, &capIndices, BLOCK_FACE_BACK, chunkData[h][w][d], nrBlocks);
                        }

                        if(chunkData[h][w][d - 1] < 0)
                        {
                            genFace(x, y, z, vertices, &nrVertices, &capVertices, indices, &nrIndices, &capIndices, BLOCK_FACE_FRONT, chunkData[h][w][d], nrBlocks);
                        }
                    }
                }
            }
        }
    }

    cMeshLoadVertices(&r, vertices, nrVertices, indices, nrIndices);
    free(vertices);
    free(indices);

    return r;
}

cMesh genChunk(Ecs* ecs, vec2 chunkPos, int nrBlocks)
{
    int chunkData[CHUNK_HEIGHT][CHUNK_WIDTH][CHUNK_DEPTH];
    for(int h = 0; h < CHUNK_HEIGHT; h++)
    {
        for(int w = 0; w < CHUNK_WIDTH; w++)
        {
            for(int d = 0; d < CHUNK_DEPTH; d++)
            {
                chunkData[h][w][d] = -1;
            }
        }
    }

    for(int h = 0; h < CHUNK_HEIGHT; h++)
    {
        for(int w = 0; w < CHUNK_WIDTH; w++)
        {
            for(int d = 0; d < CHUNK_DEPTH; d++)
            {
                if(h < 40)
                {
                    float y = (float)h;
                    
                    float n = perlin2d(w + (chunkPos[0] * CHUNK_WIDTH), d + (chunkPos[1] * CHUNK_DEPTH), 0.01, 4) * 100;
                    // printf("%f\n", n);
                    y += n;
                    chunkData[(int)y][w][d] = 0;
                    if(h < 33)
                    {
                        n = perlin2d(w + (chunkPos[0] * CHUNK_WIDTH), d + (chunkPos[1] * CHUNK_DEPTH), 0.08, 4) * 10;
                        // printf("%f\n", n);
                        y -= n;
                        chunkData[(int)y][w][d] = 2;
                    }
                }
            }
        }
    }

    for(int h = 0; h < CHUNK_HEIGHT - 1; h++)
    {
        for(int w = 0; w < CHUNK_WIDTH; w++)
        {
            for(int d = 0; d < CHUNK_DEPTH; d++)
            {
                if(chunkData[h][w][d] >= 0 && chunkData[h + 1][w][d] < 0)
                {
                    chunkData[h][w][d] = 1;
                } 
            }
        }
    }

    cMesh r = genChunkMesh(chunkData, chunkPos, nrBlocks);

    return r;
}

#endif