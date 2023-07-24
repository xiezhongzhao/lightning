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
// @Data:    2023/7/20 16:26
// @Version: 1.0

#ifndef LIGHTNING_TENSOR_UTIL_HPP
#define LIGHTNING_TENSOR_UTIL_HPP

#include <lightning/data/tensor.hpp>

namespace lightning{
    //extend the tensor
    std::tuple<sftensor, sftensor> TensorBroadcast(const sftensor& tensor1,
                                                   const sftensor& tensor2);

    // pad the tensor
    std::shared_ptr<Tensor<float>> TensorPadding(const std::shared_ptr<Tensor<float>>& tensor,
                                                 const std::vector<uint32_t>& pads,
                                                 float padding_value);
    // compare the tensors
    bool TensorIsSame(const std::shared_ptr<Tensor<float>>& a,
                      const std::shared_ptr<Tensor<float>>& b,
                      float threshold = 1e-5f);

    // add tensors
    std::shared_ptr<Tensor<float>> TensorElementAdd(const std::shared_ptr<Tensor<float>>& tensor1,
                                                    const std::shared_ptr<Tensor<float>>& tensor2);

    // output the result of adding the tensors
    void TensorElementAdd(const std::shared_ptr<Tensor<float>>& tensor1,
                          const std::shared_ptr<Tensor<float>>& tensor2,
                          const std::shared_ptr<Tensor<float>>& output_tensor);

    // multiply the tensors
    void TensorElementMultiply(const std::shared_ptr<Tensor<float>>& tensor1,
                               const std::shared_ptr<Tensor<float>>& tensor2,
                               const std::shared_ptr<Tensor<float>>& output_tensor);

    std::shared_ptr<Tensor<float>> TensorElementMultiply(const std::shared_ptr<Tensor<float>>& tensor1,
                                                         const std::shared_ptr<Tensor<float>>& tensor2);

    // create the new tensor
    std::shared_ptr<Tensor<float>> TensorCreate(uint32_t channels, uint32_t rows, uint32_t cols);

    std::shared_ptr<Tensor<float>> TensorCreate(const std::vector<uint32_t>& shapes);

    // deepcopy the tensor
    std::shared_ptr<Tensor<float>> TensorClone(std::shared_ptr<Tensor<float>> tensor);
}

#endif //LIGHTNING_TENSOR_UTIL_HPP
