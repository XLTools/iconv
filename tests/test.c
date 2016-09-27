#include <iconv.h>

int main()
{
    iconv_t conv = iconv_open("UTF-8", "UTF-8");
    iconv_close(conv);
    return 0;
}
