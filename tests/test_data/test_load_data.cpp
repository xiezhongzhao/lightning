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
// @Data:    2023/7/21 13:37
// @Version: 1.0

#include <gtest/gtest.h>
#include <glog/logging.h>
#include <lightning/data/load_data.hpp>

std::string root_dir = "/mnt/e/WorkSpace/CPlusPlus/lightning/tmp/";

TEST(test_load, load_csv_data) {
    using namespace lightning;
    std::string csv = root_dir + "data_loader/data1.csv";
    const arma::fmat &data = CSVDataLoader::LoadData(csv);
    ASSERT_NE(data.empty(), true);
    ASSERT_EQ(data.n_rows, 3);
    ASSERT_EQ(data.n_cols, 4);
    const uint32_t rows = data.n_rows;
    const uint32_t cols = data.n_cols;
    for (uint32_t i = 0; i < rows; ++i) {
        for (uint32_t j = 0; j < cols; ++j) {
            ASSERT_EQ(data.at(i, j), 1);
        }
    }
}






