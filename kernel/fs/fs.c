#include "fs.h"

unsigned char fs_memory[BLOCK_SIZE * 1024]; // 512KB filesystem.

// Pointers to the filesystem sections, see (Global variables).
superblock_t *sb;
inode_t *inodes;
unsigned char *data_blocks;
unsigned char *free_inode_bitmap;
unsigned char *free_data_bitmap;

// File system initializer
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


//==========================================================
//                     FILE OPERATIONS
//==========================================================

// TODO: Add more file operations and write more descriptive comments

int create(const char *path) {
    // Find a free inode
    for (u32 i = 0; i < sb->inode_blocks; i++) {
        // If a free inode is found, set it to "1" to mark that it is occupied   
        if (free_inode_bitmap[i] == 0) { 
            free_inode_bitmap[i] = 1;
            inodes[i].size = 0; // Set the inode's size to 0 to tell the file system that the inode (file) is empty and contains no data

            // Set all 12 data block indices in the new inode to empty (0xFFFFFFFF)
            for (int j = 0; j < 12; j++) inodes[i].data_block_indices[j] = 0xFFFFFFFF;
           
            // Find a free directory entry
            dir_entry_t *dir = (dir_entry_t *)data_blocks; // assuming root dir at start
            for (u32 d = 0; d < MAX_FILES; d++) {
                if (dir[d].filename[0] == '\0') {
                    // Add directory entry
                    strncpy(dir[d].filename, path, MAX_FILENAME_LENGTH);
                    dir[d].inode_index = i;
                    return 0; // Success
                }
            }
            return -2; // No space in directory
        }
    }
    return -1; // No free inode
}

int read(int fd, void *buffer, unsigned int count) {
    
    // Ensures the file descriptor is valid (within inode table limits).
    if (fd < 0 || fd >= sb->inode_blocks) return -1;
    
    inode_t *inode = &inodes[fd]; // Store the mem addr of the file descriptor within a pointer (*inode) 
    unsigned int bytes_to_read = (count > inode->size) ? inode->size : count;
    unsigned int bytes_read = 0; 
    unsigned int blk = 0;
    while (bytes_read < bytes_to_read && blk < 12 && inode->data_block_indices[blk] != 0xFFFFFFFF) {
        unsigned char *src = data_blocks + inode->data_block_indices[blk] * BLOCK_SIZE;
        unsigned int chunk = (bytes_to_read - bytes_read > BLOCK_SIZE) ? BLOCK_SIZE : (bytes_to_read - bytes_read);
        memcpy((unsigned char *)buffer + bytes_read, src, chunk);
        bytes_read += chunk;
        blk++;
    }
    return bytes_read;
}

int write(int fd, const void *buffer, unsigned int count) {
    if (fd < 0 || fd >= sb->inode_blocks) return -1;
    inode_t *inode = &inodes[fd];
    unsigned int bytes_written = 0;
    unsigned int blk = 0;
    while (bytes_written < count && blk < 12) {
        if (inode->data_block_indices[blk] == 0xFFFFFFFF) {
            // Find a free data block
            for (u32 db = 0; db < sb->data_blocks; db++) {
                if (free_data_bitmap[db] == 0) {
                    free_data_bitmap[db] = 1;
                    inode->data_block_indices[blk] = db;
                    break;
                }
            }
            if (inode->data_block_indices[blk] == 0xFFFFFFFF) break; // No free data block
        }
        unsigned char *dst = data_blocks + inode->data_block_indices[blk] * BLOCK_SIZE;
        unsigned int chunk = (count - bytes_written > BLOCK_SIZE) ? BLOCK_SIZE : (count - bytes_written);
        memcpy(dst, (unsigned char *)buffer + bytes_written, chunk);
        bytes_written += chunk;
        blk++;
    }
    inode->size = bytes_written;
    return bytes_written;
}
