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
// @Data:    2023/8/1 16:59
// @Version: 1.0

#ifndef LIGHTNING_TIME_LOGGING_HPP
#define LIGHTNING_TIME_LOGGING_HPP

#include <chrono>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <utility>

namespace lightning{
    namespace utils{

        using Time = std::chrono::steady_clock;

        // 每个类型的层执行时间消耗
        struct LayerTimeState{
            explicit LayerTimeState(long duration_time,
                                    std::string layer_name,
                                    std::string layer_type) :
              duration_time_(duration_time),
              layer_name_(std::move(layer_name)),
              layer_type_(std::move(layer_type)) { }

            long duration_time_;     // 时间消耗
            std::mutex time_mutex_;  // 修改duration_time_时，所需获取的锁
            std::string layer_name_; // 层的名称
            std::string layer_type_; // 层的类型
        };

        // 各类型层的时间消耗记录map类型
        using LayerTimeStatesCollector =
                std::map<std::string, std::shared_ptr<LayerTimeState>>;

        // 各类型层的时间消耗记录map指针类型
        using PtrLayerTimeStatesCollector =
                std::shared_ptr<LayerTimeStatesCollector>;

        class LayerTimeStatesSingleton{
        public:
            LayerTimeStatesSingleton() = default;

            // 初始化各类型层的时间消耗记录map
            static void LayerTimeStatesCollectorInit();

            // 初始化各类型层的时间消耗记录map
            static PtrLayerTimeStatesCollector SingletonInstance();
        private:
            static std::mutex mutex_; // 修改时间消耗记录map必须获取锁
            static PtrLayerTimeStatesCollector time_states_collector_; // 各类型层的时间消耗记录map
        };

        // 记录一个层的执行时间
        class LayerTimeLogging{
        public:
            // 记录一个层开始执行时间
            explicit LayerTimeLogging(std::string layer_name, std::string layer_type);
            // 记录一个层的结束执行时间
            ~LayerTimeLogging();
            // 输出所有类型层的运行执行时间
            static void SummaryLogging();
        private:
            std::string layer_name_;  // 层的名称
            std::string layer_type_;  // 层的类型
            std::chrono::steady_clock::time_point start_time_;  // 层的可以执行时间
        };

    } // namespace utils
} // namespace lightning
#endif //LIGHTNING_TIME_LOGGING_HPP
