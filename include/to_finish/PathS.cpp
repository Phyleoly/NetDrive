#include "include/PathS.h"
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

PathS::PathS(const std::string &path)
{
    m_path = path;
}

std::string PathS::string()
{
    return m_path;
}

std::string PathS::filename()
{
    size_t pos = m_path.find_last_of("/");
    if (pos != std::string::npos)
    {
        return m_path.substr(pos + 1);
    }
    return m_path;
}

std::string PathS::extension()
{
    size_t pos = m_path.find_last_of(".");
    if (pos != std::string::npos)
    {
        return m_path.substr(pos + 1);
    }
    return "";
}

std::string PathS::parent_path()
{
    size_t pos = m_path.find_last_of("/");
    if (pos != std::string::npos)
    {
        return m_path.substr(0, pos);
    }
    return "";
}

bool PathS::isAbsolute()
{
    return m_path.front() == '/';
}

bool PathS::isRelative()
{
    return !isAbsolute();
}

bool PathS::exists()
{
    
}

bool PathS::isDirectory()
{
    
}

bool PathS::isRegularFile()
{
   
}

// PathS PathS::current_path()
// {
//     char buffer[PATH_MAX];
//     if (getcwd(buffer, sizeof(buffer)) != NULL)
//     {
//         return PathS(buffer);
//     }
//     return PathS("");
// }

// PathS PathS::temp_directory_path()
// {
//     const char *tempDir = getenv("TMPDIR");
//     if (tempDir != NULL)
//     {
//         return PathS(tempDir);
//     }
//     return PathS("/tmp");
// }

bool PathS::create_directory(const std::string &path)
{
    return mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == 0;
}

bool PathS::remove(const std::string &path)
{
    return unlink(path.c_str()) == 0;
}

bool PathS::copy(const std::string &source, const std::string &destination)
{
    std::ifstream src(source, std::ios::binary);
    std::ofstream dst(destination, std::ios::binary);
    dst << src.rdbuf();
    return true;
}

bool PathS::rename(const std::string &old_path, const std::string &new_path)
{
    return std::rename(old_path.c_str(), new_path.c_str()) == 0;
}

bool PathS::is_empty(const std::string &path)
{
    DIR *dir = opendir(path.c_str());
    if (dir != NULL)
    {
        struct dirent *ent;
        while ((ent = readdir(dir)) != NULL)
        {
            if (std::string(ent->d_name) != "." && std::string(ent->d_name) != "..")
            {
                closedir(dir);
                return false;
            }
        }
        closedir(dir);
        return true;
    }
    return false;
}

bool PathS::remove_all(const std::string &path)
{
    DIR *dir = opendir(path.c_str());
    if (dir != NULL)
    {
        struct dirent *ent;
        while ((ent = readdir(dir)) != NULL)
        {
            std::string entryName = ent->d_name;
            if (entryName != "." && entryName != "..")
            {
                std::string fullPath = path + "/" + entryName;
                if (is_directory())
                {
                    remove_all(fullPath);
                }
                else
                {
                    remove(fullPath);
                }
            }
        }
        closedir(dir);
    }
    return rmdir(path.c_str()) == 0;
}

bool PathS::create_directories(const std::string &path)
{
    std::string currentPath;
    std::string remainingPath = path;

    while (!remainingPath.empty())
    {
        size_t pos = remainingPath.find_first_of("/");
        if (pos != std::string::npos)
        {
            currentPath += remainingPath.substr(0, pos);
            remainingPath = remainingPath.substr(pos + 1);
        }
        else
        {
            currentPath += remainingPath;
            remainingPath = "";
        }

        if (!currentPath.empty() && !exists(currentPath))
        {
            if (!create_directory(currentPath))
            {
                return false;
            }
        }

        currentPath += "/";
    }

    return true;
}

bool PathS::create_hard_link(const std::string &existing_path, const std::string &new_path)
{
    return link(existing_path.c_str(), new_path.c_str()) == 0;
}

bool PathS::create_symlink(const std::string &existing_path, const std::string &new_path)
{
    return symlink(existing_path.c_str(), new_path.c_str()) == 0;
}