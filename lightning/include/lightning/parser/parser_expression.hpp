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

#ifndef LIGHTNING_PARSER_EXPRESSION_HPP
#define LIGHTNING_PARSER_EXPRESSION_HPP

#include <string>
#include <utility>
#include <vector>
#include <memory>

namespace lightning{

    // 词语类型
    enum class TokenType{
       TokenUnknown = -9,
       TokenInputNumber = -8,
       TokenComma = -7,
       TokenAdd = -6,
       TokenMul = -5,
       TokenLeftBracket = -4,
       TokenRightBracket = -3,
    };

    // 词语token
    struct Token{
        TokenType token_type = TokenType::TokenUnknown;
        int32_t start_pos = 0;  // 词语开始的位置
        int32_t end_pos = 0;    // 词语结束的位置
        Token(TokenType token_type, int32_t start_pos, int32_t end_pos)
            : token_type(token_type), start_pos(start_pos), end_pos(end_pos){

        }
    };

    // 语法树的节点
    struct TokenNode{
        int32_t num_index = -1;
        std::shared_ptr<TokenNode> left = nullptr;  // 语法树的左节点
        std::shared_ptr<TokenNode> right = nullptr; // 语法树的右节点
        TokenNode(int32_t num_index,
                  std::shared_ptr<TokenNode> left,
                  std::shared_ptr<TokenNode> right);
        TokenNode() = default;
    };

    // add
    class ExpressionParser{
    public:
        explicit ExpressionParser(std::string statement)
            : statement_(std::move(statement)){}
        // 词法分析
        void Tokenizer(bool retokenize = false);
        // 语法分析
        std::vector<std::shared_ptr<TokenNode>> Generate();
        // 返回词法分析的结果
        const std::vector<Token> &tokens() const;
        // 返回词语字符串
        const std::vector<std::string> &token_strs() const;

    private:
        std::shared_ptr<TokenNode> Generate_(int32_t &index);
        // 被分割的词语数组
        std::vector<Token> tokens_;
        // 被分割的字符串数组
        std::vector<std::string> token_strs_;
        // 待分割的表达式
        std::string statement_;

    };
}

#endif //LIGHTNING_PARSER_EXPRESSION_HPP
