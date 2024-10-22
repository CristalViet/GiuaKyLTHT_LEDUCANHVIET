#include <stdio.h>
#include "utils.h"

/*
 * Hàm formatHumanReadableSize
 * Chuyển đổi kích thước từ byte thành chuỗi biểu diễn kích thước theo đơn vị dễ đọc hơn
 */
char *formatHumanReadableSize(off_t size)
{
    static char buffer[20]; // Mảng tĩnh để chứa chuỗi kết quả
    const char *units[] = {"B", "K", "M", "G", "T", "P", "E", "Z", "Y"}; // Các đơn vị từ byte đến yottabyte
    int i = 0; // Chỉ số của đơn vị hiện tại
    double dsize = size; // Kích thước được chuyển sang kiểu double để tính toán

    // Vòng lặp để chia kích thước cho 1024 và chuyển đổi đơn vị
    while (dsize >= 1024 && i < 8)
    {
        dsize /= 1024; // Giảm kích thước bằng cách chia cho 1024
        i++;           // Chuyển sang đơn vị lớn hơn
    }

    // Định dạng kết quả vào buffer dưới dạng chuỗi với 1 chữ số thập phân và đơn vị tương ứng
    snprintf(buffer, sizeof(buffer), "%.1f%s", dsize, units[i]);
    return buffer; // Trả về chuỗi chứa kích thước dễ đọc
}

