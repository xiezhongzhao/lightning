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
// @Data:    2023/7/26 14:09
// @Version: 1.0

#ifndef LIGHTNING_PARAM_LAYER_HPP
#define LIGHTNING_PARAM_LAYER_HPP

#include <lightning/layer/layer.hpp>

namespace lightning{

    class ParamLayer : public Layer{
    public:
        explicit ParamLayer(const std::string &layer_name);

        // initialize the weight params
        void InitWeightParam(const uint32_t param_count, const uint32_t param_channel,
                             const uint32_t param_height, const uint32_t param_width);
        // initialize the bias params
        void InitBiasParam(const uint32_t param_count, const uint32_t param_channel,
                           const uint32_t param_height, const uint32_t param_width);

        // return the weight params
        const std::vector<std::shared_ptr<Tensor<float>>> &weights() const override;
        // return the bias params
        const std::vector<std::shared_ptr<Tensor<float>>> &bias() const override;

        // set the weight params
        void set_weights(const std::vector<float> &weights) override;
        // set the bias params
        void set_bias(const std::vector<float> &bias) override;

        // set the weight params
        void set_weights(const std::vector<std::shared_ptr<Tensor<float>>> &weights) override;
        // set the bias params
        void set_bias(const std::vector<std::shared_ptr<Tensor<float>>> &bias) override;

    protected:
        std::vector<std::shared_ptr<Tensor<float>>> weights_;
        std::vector<std::shared_ptr<Tensor<float>>> bias_;
    };

} // namespace lightning

#endif //LIGHTNING_PARAM_LAYER_HPP
