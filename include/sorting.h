#ifndef SORTING_H
#define SORTING_H

#include "lsprogram.h"

/*
 * Hàm sortEntries
 * Sắp xếp danh sách tên tệp tin hoặc thư mục dựa trên các tùy chọn chỉ định.
 
 */
void sortEntries(char **names, int count, const LsOptions *options, const char *dirPath);

/*
 * Hàm compareEntries
 * So sánh hai phần tử trong danh sách tên tệp tin hoặc thư mục.
 * Trả về giá trị âm, dương, hoặc 0 tùy thuộc vào thứ tự sắp xếp của hai phần tử.
 */
int compareEntries(const void *a, const void *b);  // Loại bỏ tham số thứ ba `arg`

#endif // SORTING_H

