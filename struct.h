#ifndef STRUCT_H
#define STRUCT_H

#include "common.h"

typedef struct {
  char* buffer;
  size_t buffer_length;
  ssize_t input_length;
} InputBuffer;

typedef enum {
  EXECUTE_SUCCESS,
  EXECUTE_DUPLICATE_KEY,
} ExecuteResult;

typedef enum {
  META_COMMAND_SUCCESS,
  META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;

typedef enum {
  PREPARE_SUCCESS,
  PREPARE_NEGATIVE_ID,
  PREPARE_STRING_TOO_LONG,
  PREPARE_SYNTAX_ERROR,
  PREPARE_UNRECOGNIZED_STATEMENT
} PrepareResult;

typedef enum { STATEMENT_INSERT, STATEMENT_SELECT } StatementType;

typedef struct {
  uint32_t id;
  char username[COLUMN_USERNAME_SIZE + 1];
  char email[COLUMN_EMAIL_SIZE + 1];
} Row;

typedef struct {
  StatementType type;
  Row row_to_insert;  // only used by insert statement
} Statement;

#define size_of_attribute(Struct, Attribute) sizeof(((Struct*)0)->Attribute)

const static uint32_t ID_SIZE = size_of_attribute(Row, id);
const static uint32_t USERNAME_SIZE = size_of_attribute(Row, username);
const static uint32_t EMAIL_SIZE = size_of_attribute(Row, email);
const static uint32_t ID_OFFSET = 0;
const static uint32_t USERNAME_OFFSET = ID_OFFSET + ID_SIZE;
const static uint32_t EMAIL_OFFSET = USERNAME_OFFSET + USERNAME_SIZE;
const static uint32_t ROW_SIZE = ID_SIZE + USERNAME_SIZE + EMAIL_SIZE;

const static uint32_t PAGE_SIZE = 4096;

typedef struct {
  int file_descriptor;
  uint32_t file_length;
  uint32_t num_pages;
  void* pages[TABLE_MAX_PAGES];
} Pager;

typedef struct {
  Pager* pager;
  uint32_t root_page_num;
} Table;

typedef struct {
  Table* table;
  uint32_t page_num;
  uint32_t cell_num;
  bool end_of_table;  // Indicates a position one past the last element
} Cursor;

typedef enum { NODE_INTERNAL, NODE_LEAF } NodeType;

static void print_row(Row* row) 
{
    printf("(%d, %s, %s)\n", row->id, row->username, row->email);
}

void serialize_row(Row* source, void* destination);
void deserialize_row(void* source, Row* destination);

/*
 * Common Node Header Layout
 */
const static uint32_t NODE_TYPE_SIZE = sizeof(uint8_t);
const static uint32_t NODE_TYPE_OFFSET = 0;
const static uint32_t IS_ROOT_SIZE = sizeof(uint8_t);
const static uint32_t IS_ROOT_OFFSET = NODE_TYPE_SIZE;
const static uint32_t PARENT_POINTER_SIZE = sizeof(uint32_t);
const static uint32_t PARENT_POINTER_OFFSET = IS_ROOT_OFFSET + IS_ROOT_SIZE;
const static uint8_t COMMON_NODE_HEADER_SIZE =
    NODE_TYPE_SIZE + IS_ROOT_SIZE + PARENT_POINTER_SIZE;

/*
 * Internal Node Header Layout
 */
const static uint32_t INTERNAL_NODE_NUM_KEYS_SIZE = sizeof(uint32_t);
const static uint32_t INTERNAL_NODE_NUM_KEYS_OFFSET = COMMON_NODE_HEADER_SIZE;
const static uint32_t INTERNAL_NODE_RIGHT_CHILD_SIZE = sizeof(uint32_t);
const static uint32_t INTERNAL_NODE_RIGHT_CHILD_OFFSET =
    INTERNAL_NODE_NUM_KEYS_OFFSET + INTERNAL_NODE_NUM_KEYS_SIZE;
const static uint32_t INTERNAL_NODE_HEADER_SIZE = COMMON_NODE_HEADER_SIZE +
                                           INTERNAL_NODE_NUM_KEYS_SIZE +
                                           INTERNAL_NODE_RIGHT_CHILD_SIZE;

/*
 * Internal Node Body Layout
 */
const static uint32_t INTERNAL_NODE_KEY_SIZE = sizeof(uint32_t);
const static uint32_t INTERNAL_NODE_CHILD_SIZE = sizeof(uint32_t);
const static uint32_t INTERNAL_NODE_CELL_SIZE =
    INTERNAL_NODE_CHILD_SIZE + INTERNAL_NODE_KEY_SIZE;
/* Keep this small for testing */
const static uint32_t INTERNAL_NODE_MAX_CELLS = 3;

/*
 * Leaf Node Header Layout
 */
const static uint32_t LEAF_NODE_NUM_CELLS_SIZE = sizeof(uint32_t);
const static uint32_t LEAF_NODE_NUM_CELLS_OFFSET = COMMON_NODE_HEADER_SIZE;
const static uint32_t LEAF_NODE_NEXT_LEAF_SIZE = sizeof(uint32_t);
const static uint32_t LEAF_NODE_NEXT_LEAF_OFFSET =
    LEAF_NODE_NUM_CELLS_OFFSET + LEAF_NODE_NUM_CELLS_SIZE;
const static uint32_t LEAF_NODE_HEADER_SIZE = COMMON_NODE_HEADER_SIZE +
                                       LEAF_NODE_NUM_CELLS_SIZE +
                                       LEAF_NODE_NEXT_LEAF_SIZE;

/*
 * Leaf Node Body Layout
 */
const static uint32_t LEAF_NODE_KEY_SIZE = sizeof(uint32_t);
const static uint32_t LEAF_NODE_KEY_OFFSET = 0;
const static uint32_t LEAF_NODE_VALUE_SIZE = ROW_SIZE;
const static uint32_t LEAF_NODE_VALUE_OFFSET =
    LEAF_NODE_KEY_OFFSET + LEAF_NODE_KEY_SIZE;
const static uint32_t LEAF_NODE_CELL_SIZE = LEAF_NODE_KEY_SIZE + LEAF_NODE_VALUE_SIZE;
const static uint32_t LEAF_NODE_SPACE_FOR_CELLS = PAGE_SIZE - LEAF_NODE_HEADER_SIZE;
const static uint32_t LEAF_NODE_MAX_CELLS =
    LEAF_NODE_SPACE_FOR_CELLS / LEAF_NODE_CELL_SIZE;
const static uint32_t LEAF_NODE_RIGHT_SPLIT_COUNT = (LEAF_NODE_MAX_CELLS + 1) / 2;
const static uint32_t LEAF_NODE_LEFT_SPLIT_COUNT =
    (LEAF_NODE_MAX_CELLS + 1) - LEAF_NODE_RIGHT_SPLIT_COUNT;

#endif