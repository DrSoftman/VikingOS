#ifndef FS_H
#define FS_H

#include "../core/util.h"

#define BLOCK_SIZE 512 
#define MAX_FILES 256
#define MAX_FILENAME_LENGTH 32
#define FS_MAGIC 0xABCD1234
#define MAX_DATA_BLOCKS 1008
#define MAX_PATH_LENGTH 4096 

// Superblock Structure
typedef struct {
    u32 magic;           // Magic number to identify filesystem
    u32 total_blocks;    // Total number of blocks
    u32 inode_blocks;    // Number of inode blocks
    u32 data_blocks;     // Number of data blocks
    u32 free_inode_bitmap; // Position of inode bitmap
    u32 free_data_bitmap;  // Position of data bitmap
} superblock_t;

// Inode Structure
typedef struct {
    u32 size;                 // File size
    u32 data_block_indices[12]; // Indices of data blocks
} inode_t;

// Directory Entry Structure
typedef struct {
    char filename[MAX_FILENAME_LENGTH]; // Filename
    u32 inode_index;               // Index of corresponding inode
} dir_entry_t;

void fs_init();

// "Fops" is a shortening of "File operations"
struct Fops {
    int (*create)(const char *path);
    int (*read)(int fd, void *buffer, unsigned int count);
    int (*write)(int fd, const void *buffer, unsigned int count);
};

#endif // FS_H
