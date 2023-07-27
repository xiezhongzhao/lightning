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
// @Data:    2023/7/20 19:50
// @Version: 1.0

#include "lightning/layer/layer.hpp"

namespace lightning{

    const std::vector<std::shared_ptr<Tensor<float>>>& Layer::weights() const {
        LOG(FATAL) << this->layer_name_ << "layer not implement yet !";
    }

    const std::vector<std::shared_ptr<Tensor<float>>>& Layer::bias() const{
        LOG(FATAL) << this->layer_name_ << "layer not implement yet !";
    }

    void Layer::set_bias(const std::vector<float>& bias){
        LOG(FATAL) << this->layer_name_ << "layer not implement yet !";
    }

    void Layer::set_bias(const std::vector<std::shared_ptr<Tensor<float>>>& bias){
        LOG(FATAL) << this->layer_name_ << "layer not implement yet !";
    }

    void Layer::set_weights(const std::vector<float>& weights){
        LOG(FATAL) << this->layer_name_ << "layer not implement yet !";
    }

    void Layer::set_weights(const std::vector<std::shared_ptr<Tensor<float>>>& bias){
        LOG(FATAL) << this->layer_name_ << "layer not implement yet !";
    }

    InferStatus Layer::Forward(
            const std::vector<std::shared_ptr<Tensor<float>>>& inputs,
            std::vector<std::shared_ptr<Tensor<float>>>& outputs
            ){
        LOG(FATAL) << this->layer_name_ << "layer not implement yet !";
        return InferStatus::kInferLayerNotImplement;
    }

    InferStatus Layer::Forward(){
        LOG_IF(FATAL, this->runtime_operator_.expired())
            << "Runtime operator is expired or nullptr";
        const auto& runtime_operator = this->runtime_operator_.lock();

        std::vector<std::shared_ptr<Tensor<float>>> layer_input_datas;
        // ??????????
        return InferStatus::kInferLayerNotImplement;
    }

    void Layer::set_rumtime_operator(
            const std::shared_ptr<RuntimeOperator>& runtime_operator
            ){
        CHECK(runtime_operator != nullptr);
        this->runtime_operator_ = runtime_operator;
    }
}