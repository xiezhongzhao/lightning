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
// @Data:    2023/7/20 19:49
// @Version: 1.0

#ifndef LIGHTNING_LAYER_HPP
#define LIGHTNING_LAYER_HPP

#include <glog/logging.h>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include "lightning/data/tensor.hpp"
#include "lightning/utils/status_code.hpp"

namespace lightning{

    class RuntimeOperator;

    class Layer{
    public:
        explicit Layer(std::string layer_name): layer_name_(std::move(layer_name)){}
        virtual ~Layer() = default;

        virtual InferStatus Forward(
                const std::vector<std::shared_ptr<Tensor<float>>>& inputs,
                std::vector<std::shared_ptr<Tensor<float>>>& outputs);

        virtual InferStatus Forward();

        virtual const std::vector<std::shared_ptr<Tensor<float>>>& weights() const;

        virtual const std::vector<std::shared_ptr<Tensor<float>>>& bias() const;

        virtual void set_weights(const std::vector<std::shared_ptr<Tensor<float>>>& weights);

        virtual void set_bias(const std::vector<std::shared_ptr<Tensor<float>>>& bias);

        virtual void set_weights(const std::vector<float>& weights);

        virtual void set_bias(const std::vector<float>& bias);

        virtual const std::string& layer_name() const {return this->layer_name_;}

        void set_rumtime_operator(const std::shared_ptr<RuntimeOperator>& runtimeOperator);

    protected:
        std::weak_ptr<RuntimeOperator> runtime_operator_;
        std::string layer_name_;
    };
}
#endif //LIGHTNING_LAYER_HPP
