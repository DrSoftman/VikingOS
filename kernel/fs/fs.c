#include "fs.h"

unsigned char fs_memory[BLOCK_SIZE * 1024]; // 512KB filesystem.

// Pointers to the filesystem sections, see (Global variables).
superblock_t *sb;
inode_t *inodes;
unsigned char *data_blocks;
unsigned char *free_inode_bitmap;
unsigned char *free_data_bitmap;

void fs_init() {

    //Init superblock at the start.
    sb = (superblock_t *)fs_memory; 
    sb->magic = FS_MAGIC;

    //Assign the right values.
    sb->total_blocks = 1024;
    sb->inode_blocks = 16;
    sb->data_blocks = 1008;
    
    //Calculate the bitmap pos.
    sb->free_inode_bitmap = sizeof(superblock_t); //Calculate the pos for the inodes.
    sb->free_data_bitmap = sb->free_inode_bitmap + sb->inode_blocks; // Calculate the pos for the data.
    
    //Set up the pointers to the diffrent parts.
    inodes = (inode_t *)(fs_memory + sb->free_inode_bitmap + sb->inode_blocks); //Create inode_t struct with the memory + the offset of the free_inode_bitmap + the location of the blocks.
    data_blocks = fs_memory + BLOCK_SIZE * (sb->free_data_bitmap + sb->data_blocks); //Create data blocks with the size of the mem with the block size and with the offset and the location.
    free_inode_bitmap = fs_memory + sb->free_inode_bitmap; //Make a pointer to the already defined method.
    free_data_bitmap = fs_memory + sb->free_data_bitmap; //Make a pointer to the already defined method.

    //Make memsets to and set every block to 0 (free).
    memset(free_inode_bitmap, 0, sb->inode_blocks);
    memset(free_data_bitmap, 0, sb->data_blocks);
}

