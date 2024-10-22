#ifndef UTILS_H
#define UTILS_H

#include <sys/types.h>

/*
 * Hàm formatHumanReadableSize
 * Chuyển đổi kích thước tệp từ đơn vị byte sang định dạng dễ đọc hơn (B, K, M, G, ...).

 */
char *formatHumanReadableSize(off_t size);

#endif // UTILS_H

