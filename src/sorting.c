#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "sorting.h"

// Biến toàn cục để lưu thông tin cần thiết cho hàm compareEntries
// Lưu các tùy chọn và đường dẫn thư mục hiện tại
static struct {
    const LsOptions *options; // Tùy chọn cho lệnh ls (ví dụ: sắp xếp theo kích thước, thời gian)
    const char *dirPath;      // Đường dẫn đến thư mục hiện tại để lấy thông tin file
} sortArg;

/*
 * Hàm sortEntries
 * Sắp xếp các tệp theo các tiêu chí đã chỉ định trong `options` (kích thước, thời gian, tên)
 * Sử dụng qsort để thực hiện sắp xếp dựa trên hàm so sánh `compareEntries`.
 */
void sortEntries(char **fileNames, int count, const LsOptions *options, const char *dirPath)
{
    // Lưu các thông tin cần thiết vào biến toàn cục `sortArg` để sử dụng trong hàm so sánh
    sortArg.options = options;
    sortArg.dirPath = dirPath;

    // Gọi qsort để sắp xếp các tệp dựa trên hàm `compareEntries`
    qsort(fileNames, count, sizeof(char *), compareEntries);
}

/*
 * Hàm compareEntries
 * So sánh hai tệp dựa trên các tùy chọn sắp xếp (kích thước, thời gian, tên).
 * Hàm này được sử dụng bởi qsort để sắp xếp các tệp.
 */
int compareEntries(const void *a, const void *b)
{
    const char *name1 = *(const char **)a; // Tên tệp thứ nhất
    const char *name2 = *(const char **)b; // Tên tệp thứ hai
    struct stat st1, st2;                  // Cấu trúc chứa thông tin về tệp
    char fullpath1[PATH_MAX], fullpath2[PATH_MAX]; // Đường dẫn đầy đủ đến tệp

    // Tạo đường dẫn đầy đủ đến tệp bằng cách nối `dirPath` với tên tệp
    snprintf(fullpath1, PATH_MAX, "%s/%s", sortArg.dirPath, name1);
    snprintf(fullpath2, PATH_MAX, "%s/%s", sortArg.dirPath, name2);

    // Lấy thông tin tệp cho hai tệp bằng hàm lstat
    // Nếu lstat thất bại cho một trong hai tệp, so sánh tên tệp theo bảng chữ cái
    if (lstat(fullpath1, &st1) == -1 || lstat(fullpath2, &st2) == -1)
    {
        return strcmp(name1, name2); // So sánh tên tệp theo thứ tự bảng chữ cái nếu lstat thất bại
    }

    int result;

    // Nếu tùy chọn sắp xếp theo kích thước được bật, so sánh theo kích thước tệp
    if (sortArg.options->sortBySize)
    {
        result = st2.st_size - st1.st_size; // So sánh kích thước tệp
    }
    // Nếu tùy chọn sắp xếp theo thời gian được bật, so sánh theo thời gian tệp (truy cập, thay đổi, sửa đổi)
    else if (sortArg.options->sortByTime)
    {
        // Chọn loại thời gian dựa trên tùy chọn (truy cập, thay đổi hoặc sửa đổi)
        time_t time1 = sortArg.options->useAccessTime ? st1.st_atime : sortArg.options->useChangeTime ? st1.st_ctime : st1.st_mtime;
        time_t time2 = sortArg.options->useAccessTime ? st2.st_atime : sortArg.options->useChangeTime ? st2.st_ctime : st2.st_mtime;
        result = time2 - time1; // So sánh thời gian
    }
    // Nếu không có tùy chọn sắp xếp đặc biệt, so sánh tên tệp theo bảng chữ cái
    else
    {
        result = strcmp(name1, name2);
    }

    // Nếu tùy chọn sắp xếp ngược thứ tự được bật, đảo ngược kết quả so sánh
    return sortArg.options->reverseOrder ? -result : result;
}

