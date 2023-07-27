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

#ifndef LIGHTNING_TENSOR_HPP
#define LIGHTNING_TENSOR_HPP

#include <armadillo>
#include <memory>
#include <vector>

namespace lightning{
    template <typename T = float>
    class Tensor {};

    template <>
    class Tensor<uint8_t>{
        //...... not done
    };

    template <>
    class Tensor<float>{
    public:
        explicit Tensor() = default;

        // create tensor
        explicit Tensor(uint32_t channels, uint32_t rows, uint32_t cols);

        // create the one dimension, size stands for the num of elements
        explicit Tensor(uint32_t size);

        // create the two dimension
        explicit Tensor(uint32_t rows, uint32_t cols);

        // create the tensor of certain shape
        explicit Tensor(const std::vector<uint32_t>& shapes);

        // return the rows of tensor
        uint32_t rows() const;

        // return the cols of tensor
        uint32_t cols() const;

        // return the channels of tensor
        uint32_t channels() const;

        // return the num of elements of tensor
        uint32_t size() const;

        // set the data
        void set_data(const arma::fcube& data);

        // set the data
        void set_data(arma::fcube&& data);

        bool empty() const;

        // return the index element of tensor
        float index(uint32_t offset) const;

        float& index(uint32_t offset);

        // reutrn the shape of tensor
        std::vector<uint32_t> shapes() const;

        // the real shape of tensor
        const std::vector<uint32_t>& raw_shapes() const;

        // return the data of tensor
        arma::fcube& data();

        const arma::fcube& data() const;

        // return the index channel elements of tensor
        arma::fmat& slice(uint32_t channel);

        const arma::fmat& slice(uint32_t channel) const;

        // return the (row, col) element of tensor
        float at(uint32_t channel, uint32_t row, uint32_t col) const;

        float& at(uint32_t channel, uint32_t row, uint32_t col);

        // padding
        void Padding(const std::vector<uint32_t>& pads, float padding_value);

        // initialize the tensor with value
        void Fill(float value);

        void Fill(const std::vector<float>& values, bool row_major=true);

        // return the all data
        std::vector<float> values(bool row_major = true);

        // initialize the tensor with val one
        void Ones();

        // print the tensor
        void Rand();

        // print the tensor
        void Show();

        // reshape the tensor
        void Reshape(const std::vector<uint32_t>& shapes, bool row_major = false);

        // unroll the tensor
        void Flatten(bool row_major = false);

        // filter the elements of the tensor
        void Transform(const std::function<float(float)>& filter);

        // return the raw pointer
        float* raw_ptr();

        // return the raw pointer with offset
        float* raw_ptr(uint32_t offset);

        // return the address of the index matrix
        float* matrix_raw_ptr(uint32_t index);

    private:
        std::vector<uint32_t> raw_shapes_; // tensor shape
        arma::fcube data_; // tensor data
    };
    using ftensor = Tensor<float>;
    using sftensor = std::shared_ptr<Tensor<float>>;

} // namespace lightning

#endif //LIGHTNING_TENSOR_HPP
