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
// @Data:    2023/7/27 9:30
// @Version: 1.0

#ifndef LIGHTNING_RELU_HPP
#define LIGHTNING_RELU_HPP

#include <lightning/layer/non_param_layer.hpp>

namespace lightning{

    class ReluLayer : public NonParamLayer{
    public:
        ReluLayer() : NonParamLayer("Relu") {}
        InferStatus Forward(
                const std::vector<std::shared_ptr<Tensor<float>>>& inputs,
                std::vector<std::shared_ptr<Tensor<float>>>& outputs) override;

        static ParseParameterAttrStatus GetInstance(
                const std::shared_ptr<RuntimeOperator>& op,
                std::shared_ptr<Layer>& relu_layer);
    };
} // namespace lightning

#endif //LIGHTNING_RELU_HPP
