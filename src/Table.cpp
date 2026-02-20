#include "Table.h"
#include <cstring>
#include <iostream>

Table::Table(const std::string &filename)
{
    pager = new Pager(filename);
    num_rows = pager->get_file_length() / ROW_SIZE;
}

Table::~Table()
{
    delete pager;
}

void *Table::row_slot(uint32_t row_num)
{
    uint32_t page_num = row_num / ROWS_PER_PAGE;
    uint32_t row_num_in_page = row_num % ROWS_PER_PAGE;
    uint32_t offset = row_num_in_page * ROW_SIZE;
    char *pageptr = pager->get_page(page_num);

    return pageptr + offset;
}

void Table::row_insert(const Row &source_row)
{    
    void* row_ptr = row_slot(num_rows);
    memcpy(row_ptr, &source_row, sizeof(Row));
    uint32_t page_num = num_rows / ROWS_PER_PAGE;

    char* page_ptr = pager->get_page(page_num);

    bool is_page_full = (num_rows % ROWS_PER_PAGE) == (ROWS_PER_PAGE - 1);
    if (is_page_full) {
        pager->flush(page_num, page_ptr);
    }

    num_rows++;
}

void Table::select_all() {
    for (uint32_t i = 0; i < num_rows; i++) {

        void* slot = row_slot(i);
        
        Row* row = static_cast<Row*>(slot);
        
        if (row->id != 0) { 
            std::cout << "(" << row->id << ", " << row->username << ", " << row->email << ")" << std::endl;
        }
    }
}