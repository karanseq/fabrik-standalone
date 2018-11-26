#include "Util\FileUtils.h"

// Library includes
#include <windows.h>

// Engine includes
#include "Assert\Assert.h"
#include "Common\HelperMacros.h"
#include "Logger\Logger.h"
#include "Memory\AllocatorOverrides.h"
#include "Memory\UniquePointer.h"

namespace engine {
namespace util {

// static member initialization
FileUtils* FileUtils::instance_ = nullptr;

FileUtils::FileUtils()
{
    // TODO: Make this better
    InitWorkingDirectory();
}

FileUtils::~FileUtils()
{
    ClearFileCache();
}

FileUtils* FileUtils::Create()
{
    if (FileUtils::instance_ == nullptr)
    {
        FileUtils::instance_ = new FileUtils();
    }
    return FileUtils::instance_;
}

void FileUtils::Destroy()
{
    SAFE_DELETE(FileUtils::instance_);
    LOG("FileUtils destroyed");
}

const FileUtils::FileData FileUtils::ReadFile(const engine::data::PooledString& i_file_name, bool i_cache_file)
{
    // validate inputs
    ASSERT(i_file_name.GetLength() > 0);

    // get a hash for the file name
    unsigned int hash = engine::data::HashedString::Hash(i_file_name);

    // check if the file is in the cache
    if (IsFileCached(hash))
    {
        return file_cache_[hash];
    }

    // read the file
    FILE * file = nullptr;

    const size_t full_file_name_length = working_directory_.GetLength() + i_file_name.GetLength() + 1;
    engine::memory::UniquePointer<char> full_file_name = static_cast<char*>(engine::memory::Malloc(full_file_name_length));
    sprintf_s(full_file_name.Get(), full_file_name_length, "%s%s", working_directory_.GetString(), i_file_name.GetString());

    errno_t fopen_error = fopen_s(&file, full_file_name.Get(), "rb");
    if (fopen_error != 0)
    {
        LOG_ERROR("Could not open '%s' Error code:%d", i_file_name, fopen_error);
        return FileData();
    }

    ASSERT(file != nullptr);

    int file_IOError = fseek(file, 0, SEEK_END);
    ASSERT(file_IOError == 0);

    long file_size = ftell(file);
    ASSERT(file_size >= 0);

    file_IOError = fseek(file, 0, SEEK_SET);
    ASSERT(file_IOError == 0);

    uint8_t * buffer = new uint8_t[file_size + 1];
    ASSERT(buffer);

    size_t file_read = fread(buffer, 1, file_size, file);
    ASSERT(file_read == file_size);

    buffer[file_read] = '\0';
    fclose(file);

    // another thread might have added this file since the last time we checked
    if (IsFileCached(hash))
    {
        // delete the buffer and return the cached file
        delete[] buffer;
        return file_cache_[hash];
    }
    else
    {
        std::lock_guard<std::mutex> lock(file_cache_mutex_);

        // prepare outputs
        FileData file_data(i_file_name, buffer, static_cast<size_t>(file_size));

        // add the file to the cache
        if (i_cache_file)
        {
            file_cache_.insert(std::pair<unsigned int, FileData>(hash, file_data));
            LOG("FileUtils added '%s' to the cache", i_file_name);
        }

        return file_data;
    }
}

bool FileUtils::WriteFile(const engine::data::PooledString& i_file_name, const char* i_file_contents) const
{
    return false;
}

void FileUtils::ClearFileCache()
{
    std::lock_guard<std::mutex> lock(file_cache_mutex_);

    for (auto i : file_cache_)
    {
        delete i.second.file_contents;
    }
    file_cache_.clear();
    LOG("FileUtils file cache cleared");
}

void FileUtils::InitWorkingDirectory()
{
    static constexpr size_t BUFFER_SIZE = 1000;
    char buffer[BUFFER_SIZE];
    const size_t num_characters_copied = GetModuleFileName(NULL, buffer, BUFFER_SIZE);
    ASSERT(num_characters_copied > 0);

    size_t index = num_characters_copied - 1;
    while (index > 0)
    {
        if (buffer[index] == '\\')
        {
            break;
        }
        --index;
    }

    if (index > 0)
    {
        buffer[index + 1] = '\0';
        working_directory_ = engine::data::PooledString(buffer);
#ifdef BUILD_DEBUG
        LOG("%s '%s'", __FUNCTION__, working_directory_.GetString());
#endif
    }
}

} // namespace util
} // namespace engine
