#include "Pager.h"
#include <cstring>

Pager::Pager(const std::string &filename) : file_name(filename)
{
    file_descriptor.open(file_name, std::ios::in | std::ios::out | std::ios::binary);
    if (!file_descriptor)
    {
        file_descriptor.open(file_name, std::ios::out | std::ios::binary);
        file_descriptor.close();
        file_descriptor.open(file_name, std::ios::in | std::ios::out | std::ios::binary);
    }

    for (char* &page : pages)
    {
        page = nullptr;
    }
}

char *Pager::get_page(int page_num)
{
    if (page_num > TABLE_MAX_PAGES)
        return nullptr;

    if (page_num < 0)
        return nullptr;

    if (pages[page_num] != nullptr)
        return pages[page_num];
    else
    {
        char *arrptr = new char[PAGE_SIZE];
        memset(arrptr, 0, PAGE_SIZE);

        std::streamoff offset = static_cast<std::streamoff>(page_num) * PAGE_SIZE;

        file_descriptor.seekg(offset, std::ios::beg);
        file_descriptor.read(arrptr, PAGE_SIZE);

        if (file_descriptor.fail())
            file_descriptor.clear();
        pages[page_num] = arrptr;
        return arrptr;
    }
}
Pager::~Pager()
{
    for (int i = 0; i < TABLE_MAX_PAGES; i++)
    {
        if (pages[i] != nullptr)
        {
            flush(i, pages[i]);
            delete[] pages[i];
            pages[i] = nullptr;
        }
    }
    if (file_descriptor.is_open())
    {
        file_descriptor.close();
    }
}
void Pager::flush(int page_num, char *page)
{
    if (page_num < 0)
        return;

    std::streamoff offset = static_cast<std::streamoff>(page_num) * PAGE_SIZE;
    file_descriptor.seekp(offset, std::ios::beg);
    file_descriptor.write(page, PAGE_SIZE);
    file_descriptor.flush();

    if (file_descriptor.fail())
        file_descriptor.clear();
}

int Pager::get_file_length()
{
    auto current = file_descriptor.tellg();
    file_descriptor.seekg(0, std::ios::end);
    int length = file_descriptor.tellg();
    file_descriptor.seekg(current);
    return length;
}
