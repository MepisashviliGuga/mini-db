#include <Pager.h>
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
}

char* Pager::get_page(int page_num)
{
    if (page_num < 0) return nullptr;

    char* arrptr = new char[PAGE_SIZE];
    memset(arrptr, 0, PAGE_SIZE);

    std::streamoff offset = static_cast<std::streamoff>(page_num) * PAGE_SIZE;

    file_descriptor.seekg(offset, std::ios::beg);
    file_descriptor.read(arrptr, PAGE_SIZE);

    if (file_descriptor.fail())
        file_descriptor.clear();

    return arrptr;
}

