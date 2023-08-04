// MIT License
// Copyright (c) 2022 - 谢中朝
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// @Author:  xiezhongzhao
// @Email:   2234309583@qq.com
// @Data:    2023/7/26 17:57
// @Version: 1.0

#ifndef LIGHTNING_STORE_ZIP_HPP
#define LIGHTNING_STORE_ZIP_HPP

#include <map>
#include <string>
#include <vector>
#include <cstdint>

namespace pnnx{

    class StoreZipReader{
    public:
        StoreZipReader();
        ~StoreZipReader();

        int open(const std::string& path);
        size_t get_file_size(const std::string& name);
        int read_file(const std::string& name, char* data);
        int close();

    private:
        FILE* fp;
        struct StoreZipMeta{
            size_t offset;
            size_t size;
        };
        std::map<std::string, StoreZipMeta> filemetas;
    };

    class StoreZipWriter{
    public:
        StoreZipWriter();
        ~StoreZipWriter();

        int open(const std::string& path);
        int write_file(const std::string& name,
                       const char* data,
                       size_t size);
        int close();
    private:
        FILE* fp;
        struct StoreZipMeta{
            std::string name;
            size_t lfh_offset;
            uint32_t crc32;
            uint32_t size;
        };

        std::vector<StoreZipMeta> filemetas;
    };
}

#endif //LIGHTNING_STORE_ZIP_HPP
