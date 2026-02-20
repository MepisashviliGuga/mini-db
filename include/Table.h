#pragma once
#include <cstdint>
#include "Pager.h"
#include "Row.h"

class Table
{
public:
    // 1. Open the database (creates the Pager)
    Table(const std::string &filename);

    // 2. Clean up (flushes cache, closes Pager)
    ~Table();

    // 3. The Main API
    // "Cursor" abstraction: Where do we read/write?
    // For now, we'll keep it simple:
    void cursor_advance();

    // The specific logic to save a row
    void row_insert(const Row &source_row);

    // The specific logic to read all rows
    void select_all();


private:
    Pager *pager;
    uint32_t num_rows;

    // THE MATH CONSTANTS
    // We calculate these based on the other classes. No hardcoding!

    // 1. How big is one row? (Ask the Row struct)
    static const uint32_t ROW_SIZE = sizeof(Row);

    // 2. How many rows fit in a page? (Ask the Pager)
    static const uint32_t ROWS_PER_PAGE = Pager::PAGE_SIZE / ROW_SIZE;

    // 3. How many rows per table? (Arbitrary limit for now)
    static const uint32_t TABLE_MAX_ROWS = ROWS_PER_PAGE * 100;

    // CALCULATING WHERE A ROW LIVES
    // This is the math part!
    // Give me a row index (0, 1, 2...), I give you the memory address in RAM.
    void *row_slot(uint32_t row_num);
};