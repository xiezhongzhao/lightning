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
// @Data:    2023/8/4 17:48
// @Version: 1.0

#include <gtest/gtest.h>
#include <glog/logging.h>

TEST(test_net, test_glog1){

    int value = 15;

    CHECK(value > 5) << "Value is not greater than 5 " << value;
    CHECK_EQ(value, 15) << "Value is not equal to 15 ";
    CHECK_NE(value, 16) << "Value is equal to 16";
    CHECK_GE(value, 0) << "Value is not less than 0";
    CHECK_LT(value, 16);

    const char* str = "hello";
    CHECK_STREQ(str, "hello") << "String are not equal";

    double pi = 3.14159;
    CHECK_DOUBLE_EQ(pi, 3.14159);

    CHECK_ERR(value);

    ASSERT_EQ(12, 12);

}