#ifndef BTREE_H
#define BTREE_H

#include "struct.h"

NodeType get_node_type(void* node);
void set_node_type(void* node, NodeType type);

bool is_node_root(void* node);
void set_node_root(void* node, bool is_root);

uint32_t* node_parent(void* node);

uint32_t* internal_node_num_keys(void* node);
uint32_t* internal_node_right_child(void* node);
uint32_t* internal_node_cell(void* node, uint32_t cell_num);
uint32_t* internal_node_child(void* node, uint32_t child_num);
uint32_t* internal_node_key(void* node, uint32_t key_num);

uint32_t* leaf_node_num_cells(void* node);
uint32_t* leaf_node_next_leaf(void* node);
void* leaf_node_cell(void* node, uint32_t cell_num);
uint32_t* leaf_node_key(void* node, uint32_t cell_num);
void* leaf_node_value(void* node, uint32_t cell_num);

uint32_t get_node_max_key(void* node);
void* get_page(Pager* pager, uint32_t page_num);

void initialize_leaf_node(void* node);
void initialize_internal_node(void* node);

Cursor* leaf_node_find(Table* table, uint32_t page_num, uint32_t key);
uint32_t internal_node_find_child(void* node, uint32_t key);

Cursor* internal_node_find(Table* table, uint32_t page_num, uint32_t key);

uint32_t get_unused_page_num(Pager* pager);
void create_new_root(Table* table, uint32_t right_child_page_num);

void internal_node_insert(Table* table, uint32_t parent_page_num, uint32_t child_page_num);
void update_internal_node_key(void* node, uint32_t old_key, uint32_t new_key);
void leaf_node_split_and_insert(Cursor* cursor, uint32_t key, Row* value);
void leaf_node_insert(Cursor* cursor, uint32_t key, Row* value);

#endif

