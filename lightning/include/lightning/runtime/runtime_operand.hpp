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
// @Data:    2023/7/26 17:56
// @Version: 1.0

#ifndef LIGHTNING_RUNTIME_OPERAND_HPP
#define LIGHTNING_RUNTIME_OPERAND_HPP

#include <vector>
#include <string>
#include <memory>

#include <lightning/utils/status_code.hpp>
#include <lightning/runtime/runtime_datatype.hpp>
#include <lightning/data/tensor.hpp>

namespace lightning{
    // 计算节点输入输出的操作数
    struct RuntimeOperand{
        std::string name;  // 操作数的名称
        std::vector<int32_t> shapes;  // 操作数的形状
        std::vector<std::shared_ptr<Tensor<float>>> datas;  // 存储操作数
        RuntimeDataType type = RuntimeDataType::kTypeUnknown; // 操作数的类型
    };
}

#endif //LIGHTNING_RUNTIME_OPERAND_HPP
