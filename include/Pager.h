#pragma once
#include <fstream>
#include <string>

class Pager
{
public:
    // We will define this constant here
    static const int PAGE_SIZE = 4096;

    // 1. The Constructor: Sets up the file connection
    Pager(const std::string &filename);

    // 2. The Destructor: Cleans up (closes file)
    ~Pager();

    // 3. The Core Function: Asking for a specific page
    // Returns a pointer to a block of 4096 bytes
    char *get_page(int page_num);

    // 4. The Writer: Saves a specific page back to disk
    void flush(int page_num, char *page);

    int get_file_length();

    static const int TABLE_MAX_PAGES = 100;

private:
    std::fstream file_descriptor;
    std::string file_name;
    char *pages[TABLE_MAX_PAGES];
};