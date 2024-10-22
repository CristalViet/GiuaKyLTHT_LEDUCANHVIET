#ifndef FILEINFO_H
#define FILEINFO_H

#include <sys/stat.h> 
#include "lsprogram.h" 

/*
 * Hàm listDirectory
 * Liệt kê tất cả các tập tin và thư mục trong một thư mục cụ thể dựa trên các tùy chọn được cung cấp.

 */
void listDirectory(const char *path, const LsOptions *options);

/*
 * Hàm printFileInfo
 * Hiển thị thông tin chi tiết của một tập tin hoặc thư mục, như kích thước, quyền truy cập, và thời gian sửa đổi.

 */
void printFileInfo(const char *path, const char *name, const struct stat *fileStat, const LsOptions *options);

#endif // FILEINFO_H

