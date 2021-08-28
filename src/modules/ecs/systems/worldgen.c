#ifndef WORLDGEN_C
#define WORLDGEN_C

#include <cglm/cglm.h>
#include <ecs/ecs.h>
#include <GL/glew.h>
#include "worldgen.h"
// #include <fastnoise.h>

const int CHUNK_WIDTH = 8;
const int CHUNK_DEPTH = 8;
const int CHUNK_HEIGHT = 32;

void appendVertex(float v[5], float* vertices, int* nrVertices, int* capVertices, unsigned int* indices, int* nrIndices, int* capIndices)
{
    for(int i = 0; i < 5; i++)
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
    *nrVertices += 5;
}

void genFace(float w, float h, float d, float* vertices, int* nrVertices, int* capVertices, 
    unsigned int* indices, int* nrIndices, int* CapIndices, faces faceId)
{
    switch(faceId)
    {
        case BLOCK_FACE_TOP:
            appendVertex((float[5]){w + 0.5, h + 0.5, d + 0.5, 1.0, 1.0}, vertices, nrVertices, capVertices, indices, nrIndices, CapIndices);
            appendVertex((float[5]){w + 0.5, h + 0.5, d - 0.5, 1.0, 0.0}, vertices, nrVertices, capVertices, indices, nrIndices, CapIndices);
            appendVertex((float[5]){w - 0.5, h + 0.5, d - 0.5, 0.0, 0.0}, vertices, nrVertices, capVertices, indices, nrIndices, CapIndices);
            appendVertex((float[5]){w - 0.5, h + 0.5, d + 0.5, 0.0, 1.0}, vertices, nrVertices, capVertices, indices, nrIndices, CapIndices);
            break;
        case BLOCK_FACE_LEFT:
            appendVertex((float[5]){w - 0.5, h + 0.5, d - 0.5, 1.0, 1.0}, vertices, nrVertices, capVertices, indices, nrIndices, CapIndices);
            appendVertex((float[5]){w - 0.5, h - 0.5, d - 0.5, 1.0, 0.0}, vertices, nrVertices, capVertices, indices, nrIndices, CapIndices);
            appendVertex((float[5]){w - 0.5, h - 0.5, d + 0.5, 0.0, 0.0}, vertices, nrVertices, capVertices, indices, nrIndices, CapIndices);
            appendVertex((float[5]){w - 0.5, h + 0.5, d + 0.5, 0.0, 1.0}, vertices, nrVertices, capVertices, indices, nrIndices, CapIndices);
            break;
        case BLOCK_FACE_FRONT:
            appendVertex((float[5]){w + 0.5, h + 0.5, d - 0.5, 1.0, 1.0}, vertices, nrVertices, capVertices, indices, nrIndices, CapIndices);
            appendVertex((float[5]){w + 0.5, h - 0.5, d - 0.5, 1.0, 0.0}, vertices, nrVertices, capVertices, indices, nrIndices, CapIndices);
            appendVertex((float[5]){w - 0.5, h - 0.5, d - 0.5, 0.0, 0.0}, vertices, nrVertices, capVertices, indices, nrIndices, CapIndices);
            appendVertex((float[5]){w - 0.5, h + 0.5, d - 0.5, 0.0, 1.0}, vertices, nrVertices, capVertices, indices, nrIndices, CapIndices);
            break;

        case BLOCK_FACE_RIGHT:
            appendVertex((float[5]){w + 0.5, h + 0.5, d + 0.5, 1.0, 1.0}, vertices, nrVertices, capVertices, indices, nrIndices, CapIndices);
            appendVertex((float[5]){w + 0.5, h - 0.5, d + 0.5, 1.0, 0.0}, vertices, nrVertices, capVertices, indices, nrIndices, CapIndices);
            appendVertex((float[5]){w + 0.5, h - 0.5, d - 0.5, 0.0, 0.0}, vertices, nrVertices, capVertices, indices, nrIndices, CapIndices);
            appendVertex((float[5]){w + 0.5, h + 0.5, d - 0.5, 0.0, 1.0}, vertices, nrVertices, capVertices, indices, nrIndices, CapIndices);
            break;
        case BLOCK_FACE_BOTTOM:
            appendVertex((float[5]){w + 0.5, h - 0.5, d - 0.5, 1.0, 1.0}, vertices, nrVertices, capVertices, indices, nrIndices, CapIndices);
            appendVertex((float[5]){w + 0.5, h - 0.5, d + 0.5, 1.0, 0.0}, vertices, nrVertices, capVertices, indices, nrIndices, CapIndices);
            appendVertex((float[5]){w - 0.5, h - 0.5, d + 0.5, 0.0, 0.0}, vertices, nrVertices, capVertices, indices, nrIndices, CapIndices);
            appendVertex((float[5]){w - 0.5, h - 0.5, d - 0.5, 0.0, 1.0}, vertices, nrVertices, capVertices, indices, nrIndices, CapIndices);
            break;

        case BLOCK_FACE_BACK:
            appendVertex((float[5]){w + 0.5, h - 0.5, d + 0.5, 1.0, 1.0}, vertices, nrVertices, capVertices, indices, nrIndices, CapIndices);
            appendVertex((float[5]){w + 0.5, h + 0.5, d + 0.5, 1.0, 0.0}, vertices, nrVertices, capVertices, indices, nrIndices, CapIndices);
            appendVertex((float[5]){w - 0.5, h + 0.5, d + 0.5, 0.0, 0.0}, vertices, nrVertices, capVertices, indices, nrIndices, CapIndices);
            appendVertex((float[5]){w - 0.5, h - 0.5, d + 0.5, 0.0, 1.0}, vertices, nrVertices, capVertices, indices, nrIndices, CapIndices);
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
        indices[*nrIndices + i] = (*nrVertices / 5.0) - 4 + newIndices[i];
    }

    *nrIndices += 6;
}

cMesh genChunkMesh(int chunkData[CHUNK_HEIGHT][CHUNK_WIDTH][CHUNK_DEPTH])
{
    cMesh r;
    float* vertices;
    unsigned long int nrVertices = 0;
    unsigned long int capVertices = 5000000;

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
                if(chunkData[h][w][d] >= 0)
                {
                    if(h == 0)
                    {
                        genFace(w, h, d, vertices, &nrVertices, &capVertices, indices, &nrIndices, &capIndices, BLOCK_FACE_BOTTOM);
                        if(chunkData[h + 1][w][d] < 0)
                        {
                            genFace(w, h, d, vertices, &nrVertices, &capVertices, indices, &nrIndices, &capIndices, BLOCK_FACE_TOP);
                        }
                    }
                    else if(h == CHUNK_HEIGHT - 1)
                    {
                        genFace(w, h, d, vertices, &nrVertices, &capVertices, indices, &nrIndices, &capIndices, BLOCK_FACE_TOP);
                        if(chunkData[h - 1][w][d] < 0)
                        {
                            genFace(w, h, d, vertices, &nrVertices, &capVertices, indices, &nrIndices, &capIndices, BLOCK_FACE_BOTTOM);
                        }
                    }
                    else
                    {
                        if(chunkData[h + 1][w][d] < 0)
                        {
                            genFace(w, h, d, vertices, &nrVertices, &capVertices, indices, &nrIndices, &capIndices, BLOCK_FACE_TOP);
                        }

                        if(chunkData[h - 1][w][d] < 0)
                        {
                            genFace(w, h, d, vertices, &nrVertices, &capVertices, indices, &nrIndices, &capIndices, BLOCK_FACE_BOTTOM);
                        }
                    }

                    if(w == 0)
                    {
                        genFace(w, h, d, vertices, &nrVertices, &capVertices, indices, &nrIndices, &capIndices, BLOCK_FACE_LEFT);
                        if(chunkData[h][w + 1][d] < 0)
                        {
                            genFace(w, h, d, vertices, &nrVertices, &capVertices, indices, &nrIndices, &capIndices, BLOCK_FACE_RIGHT);
                        }
                    }
                    else if(w == CHUNK_WIDTH - 1)
                    {
                        genFace(w, h, d, vertices, &nrVertices, &capVertices, indices, &nrIndices, &capIndices, BLOCK_FACE_RIGHT);
                        if(chunkData[h][w - 1][d] < 0)
                        {
                            genFace(w, h, d, vertices, &nrVertices, &capVertices, indices, &nrIndices, &capIndices, BLOCK_FACE_LEFT);
                        }
                    }
                    else
                    {
                        if(chunkData[h][w + 1][d] < 0)
                        {
                            genFace(w, h, d, vertices, &nrVertices, &capVertices, indices, &nrIndices, &capIndices, BLOCK_FACE_RIGHT);
                        }

                        if(chunkData[h][w - 1][d] < 0)
                        {
                            genFace(w, h, d, vertices, &nrVertices, &capVertices, indices, &nrIndices, &capIndices, BLOCK_FACE_LEFT);
                        }
                    }

                    if(d == 0)
                    {
                        genFace(w, h, d, vertices, &nrVertices, &capVertices, indices, &nrIndices, &capIndices, BLOCK_FACE_FRONT);
                        if(chunkData[h][w][d + 1] < 0)
                        {
                            genFace(w, h, d, vertices, &nrVertices, &capVertices, indices, &nrIndices, &capIndices, BLOCK_FACE_BACK);
                        }                    
                    
                    }
                    else if(d == CHUNK_DEPTH - 1)
                    {
                        genFace(w, h, d, vertices, &nrVertices, &capVertices, indices, &nrIndices, &capIndices, BLOCK_FACE_BACK);
                        if(chunkData[h][w][d - 1] < 0)
                        {
                            genFace(w, h, d, vertices, &nrVertices, &capVertices, indices, &nrIndices, &capIndices, BLOCK_FACE_FRONT);
                        }
                    }
                    else
                    {
                        if(chunkData[h][w][d + 1] < 0)
                        {
                            genFace(w, h, d, vertices, &nrVertices, &capVertices, indices, &nrIndices, &capIndices, BLOCK_FACE_BACK);
                        }

                        if(chunkData[h][w][d - 1] < 0)
                        {
                            genFace(w, h, d, vertices, &nrVertices, &capVertices, indices, &nrIndices, &capIndices, BLOCK_FACE_FRONT);
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

cMesh genChunk(Ecs* ecs, vec2 chunkPos)
{
    int chunkData[CHUNK_HEIGHT][CHUNK_WIDTH][CHUNK_DEPTH];
    // fnl_state noise = fnlCreateState();
    // noise.noise_type = FNL_NOISE_OPENSIMPLEX2;
    // float heightMap[128 * 128];
    // int index = 0;

    // for (int y = 0; y < 128; y++)
    // {
    //     for (int x = 0; x < 128; x++) 
    //     {
    //         heightMap[index++] = fnlGetNoise2D(&noise, x, y);
    //     }
    // }

    for(int h = 0; h < CHUNK_HEIGHT; h++)
    {
        for(int w = 0; w < CHUNK_WIDTH; w++)
        {
            for(int d = 0; d < CHUNK_DEPTH; d++)
            {
                // chunkData[ (int)(heightMap[ (int)((int)(w * 128) + (int)(d % 128)) ] * 100) ][w][d] = 0;
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
                if(h < 2)
                {
                    chunkData[h][w][d] = 0;
                }
            }
        }
    }

    for(int i = 0; i < 200; i++)
    {
        int x = rand() % CHUNK_WIDTH;
        int y = rand() % CHUNK_HEIGHT;
        int z = rand() % CHUNK_DEPTH;

        chunkData[x][y][z] = 0;
    }

    cMesh r = genChunkMesh(chunkData);

    return r;
}

#endif