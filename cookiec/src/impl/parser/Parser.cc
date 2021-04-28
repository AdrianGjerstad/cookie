#include "../../include/parser/Parser.h"

#include <vector>
#include <memory>
#include <iostream>

#include "../../include/structs/ParserResult.h"
#include "../../include/ast/Node.h"
#include "../../include/lexer/Token.h"
#include "../../include/lexer/TokenType.h"

// And now ... literally every single node type listed out at once!
#include "../../include/ast/AbstractSyntaxTree.h"
#include "../../include/ast/BinaryOperationNode.h"
#include "../../include/ast/UnaryOperationNode.h"
#include "../../include/ast/LiteralNode.h"
#include "../../include/ast/CodeBodyNode.h"
#include "../../include/ast/NoOperationNode.h"
#include "../../include/ast/FunctionNode.h"
#include "../../include/ast/ArgumentListNode.h"
#include "../../include/ast/SymbolReferenceNode.h"
#include "../../include/ast/SymbolDefinitionNode.h"
#include "../../include/ast/ReturnNode.h"
#include "../../include/ast/GlobalDefinitionNode.h"
#include "../../include/ast/FunctionCallNode.h"
#include "../../include/ast/ConditionalNode.h"
#include "../../include/ast/ForLoopNode.h"
#include "../../include/ast/WhileLoopNode.h"

#include "../../include/errors/SyntaxError.h"

namespace cookie {

Parser::Parser() {
  // Nothing to do
}

ParserResult Parser::parse(const std::vector<Token>* tokens) const {
  unsigned int index = 0;
  ParserResult result = globalbody_(tokens, &index);

  if (tokens->size() > index &&
      tokens->at(index).type() != TokenType::END_OF_FILE) {
    return result.failure(SyntaxError(
      tokens->at(index).pstart(), tokens->at(index).pend(),
      "Expected EOF"
    ));
  }

  return result;
}

const Token& Parser::advance_(
    const std::vector<Token>* tokens,
    unsigned int* index) const {
  unsigned int& idx_ref = (*index);
  if(tokens->size() == idx_ref + 1) return tokens->at(*index);

  ++idx_ref;

  return tokens->at(*index);
}

ParserResult Parser::globalbody_(
    const std::vector<Token>* tokens,
    unsigned int* index) const {
  ParserResult result;

  std::shared_ptr<AbstractSyntaxTree> tree =
      std::shared_ptr<AbstractSyntaxTree>(new AbstractSyntaxTree());

  while (tokens->at(*index).type() != TokenType::END_OF_FILE) {
    std::shared_ptr<Node> item = result.use(globalitem_(tokens, index));
    if (result.errors.size()) return result;
    if (item->type() == Node::FUNCTION) {
      tree->push_function(item);
    } else {
      tree->push_global(item);
    }
  }

  return result.success(tree);
}

ParserResult Parser::globalitem_(
    const std::vector<Token>* tokens,
    unsigned int* index) const {
  ParserResult result;
  Token export_token = Token(
      tokens->at(*index).pstart(), tokens->at(*index).pend(),
      TokenType::NULL_TOKEN);

  if (tokens->at(*index).type() == TokenType::KW_EXPORT) {
    export_token = tokens->at(*index);
    advance_(tokens, index);
  }

  Token const_token = Token(
      tokens->at(*index).pstart(), tokens->at(*index).pend(),
      TokenType::NULL_TOKEN);

  if (tokens->at(*index).type() == TokenType::KW_CONST) {
    const_token = tokens->at(*index);
    advance_(tokens, index);
  }

  const Token& data_type = tokens->at(*index);

  if (data_type.type() != TokenType::KW_VOID &&
      data_type.type() != TokenType::KW_DATA_TYPE) {
    return result.failure(SyntaxError(
      data_type.pstart(), data_type.pend(),
      "Expected data type"
    ));
  }

  advance_(tokens, index);

  const Token& name = tokens->at(*index);

  if (name.type() != TokenType::IDENTIFIER) {
    return result.failure(SyntaxError(
      name.pstart(), name.pend(),
      "Expected identifier"
    ));
  }

  advance_(tokens, index);

  if (tokens->at(*index).type() == TokenType::LEFT_PARENTHESIS) {
    std::shared_ptr<Node> arglist = result.use(arglist_(tokens, index));
    if (result.errors.size()) return result;

    if (tokens->at(*index).type() != TokenType::LEFT_BRACE) {
      return result.failure(SyntaxError(
        tokens->at(*index).pstart(), tokens->at(*index).pend(),
        "Expected '{'"
      ));
    }

    advance_(tokens, index);

    std::shared_ptr<Node> body = result.use(codebody_(tokens, index));
    if (result.errors.size()) return result;

    if (tokens->at(*index).type() != TokenType::RIGHT_BRACE) {
      return result.failure(SyntaxError(
        tokens->at(*index).pstart(), tokens->at(*index).pend(),
        "Expected '}'"
      ));
    }

    advance_(tokens, index);

    std::shared_ptr<Node> result_node = std::shared_ptr<Node>(
        new FunctionNode(export_token, const_token, data_type, name, arglist,
            body));
    return result.success(result_node);
  } else if (tokens->at(*index).type() == TokenType::EQUALS) {
    if (data_type.type() == TokenType::KW_VOID) {
      return result.failure(SyntaxError(
        data_type.pstart(), data_type.pend(),
        "Cannot define global variable as void"
      ));
    }

    advance_(tokens, index);

    std::shared_ptr<Node> expr = result.use(expression_(tokens, index));
    if (result.errors.size()) return result;

    if (tokens->at(*index).type() != TokenType::SEMICOLON) {
      return result.failure(SyntaxError(
        tokens->at(*index).pstart(), tokens->at(*index).pend(),
        "Expected ';'"
      ));
    }

    advance_(tokens, index);

    return result.success(std::shared_ptr<Node>(
        new GlobalDefinitionNode(export_token, const_token, data_type, name,
            expr)));
  } else {
    return result.failure(SyntaxError(
      tokens->at(*index).pstart(), tokens->at(*index).pend(),
      "Expected '(' or '=' after identifier"
    ));
  }
}

ParserResult Parser::arglist_(
    const std::vector<Token>* tokens,
    unsigned int* index) const {
  ParserResult result;

  if (tokens->at(*index).type() != TokenType::LEFT_PARENTHESIS) {
    return result.failure(SyntaxError(
      tokens->at(*index).pstart(), tokens->at(*index).pend(),
      "Expected '('"
    ));
  }

  advance_(tokens, index);

  std::vector<Token> types;
  std::vector<Token> names;

  if (tokens->at(*index).type() == TokenType::RIGHT_PARENTHESIS) {
    advance_(tokens, index);
    std::shared_ptr<Node> result_node = std::shared_ptr<Node>(
        new ArgumentListNode(types, names));
    return result.success(result_node);
  }

  if (tokens->at(*index).type() != TokenType::KW_DATA_TYPE) {
    return result.failure(SyntaxError(
      tokens->at(*index).pstart(), tokens->at(*index).pend(),
      "Expected parameter type"
    ));
  }

  types.push_back(tokens->at(*index));
  advance_(tokens, index);

  if (tokens->at(*index).type() != TokenType::IDENTIFIER) {
    names.push_back(Token(
        tokens->at(*index).pstart(), tokens->at(*index).pend(),
        TokenType::NULL_TOKEN));
  } else {
    names.push_back(tokens->at(*index));
    advance_(tokens, index);
  }

  while (tokens->at(*index).type() != TokenType::RIGHT_PARENTHESIS) {
    if (tokens->at(*index).type() != TokenType::COMMA) {
      return result.failure(SyntaxError(
        tokens->at(*index).pstart(), tokens->at(*index).pend(),
        "Expected ','"
      ));
    }

    advance_(tokens, index);

    if (tokens->at(*index).type() != TokenType::KW_DATA_TYPE) {
      return result.failure(SyntaxError(
        tokens->at(*index).pstart(), tokens->at(*index).pend(),
        "Expected parameter type"
      ));
    }

    types.push_back(tokens->at(*index));
    advance_(tokens, index);

    if (tokens->at(*index).type() != TokenType::IDENTIFIER) {
      names.push_back(Token(
          tokens->at(*index).pstart(), tokens->at(*index).pend(),
          TokenType::NULL_TOKEN));
    } else {
      names.push_back(tokens->at(*index));
      advance_(tokens, index);
    }
  }

  advance_(tokens, index);

  return result.success(std::shared_ptr<Node>(
      new ArgumentListNode(types, names)));
}

ParserResult Parser::codebody_(
    const std::vector<Token>* tokens,
    unsigned int* index) const {
  ParserResult result;

  std::shared_ptr<CodeBodyNode> body = std::shared_ptr<CodeBodyNode>(
      new CodeBodyNode());

  while (tokens->at(*index).type() != TokenType::RIGHT_BRACE) {
    std::shared_ptr<Node> stmt = result.use(statement_(tokens, index));
    if (result.errors.size()) return result;

    body->push_back(stmt);
  }

  return result.success(body);
}

ParserResult Parser::statement_(
    const std::vector<Token>* tokens,
    unsigned int* index) const {
  ParserResult result;

  if (tokens->at(*index).type() == TokenType::SEMICOLON) {
    advance_(tokens, index);
    return result.success(std::shared_ptr<Node>(
        new NoOperationNode()));
  }

  Token is_const = Token(
      tokens->at(*index).pstart(), tokens->at(*index).pend(),
      TokenType::NULL_TOKEN);

  if (tokens->at(*index).type() == TokenType::KW_CONST) {
    is_const = tokens->at(*index);
    advance_(tokens, index);
  }

  if (tokens->at(*index).type() == TokenType::KW_DATA_TYPE) {
    const Token& type = tokens->at(*index);
    advance_(tokens, index);

    if (tokens->at(*index).type() != TokenType::IDENTIFIER) {
      return result.failure(SyntaxError(
        tokens->at(*index).pstart(), tokens->at(*index).pend(),
        "Expected identifier"
      ));
    }

    const Token& name = tokens->at(*index);
    advance_(tokens, index);

    if (tokens->at(*index).type() == TokenType::SEMICOLON) {
      advance_(tokens, index);
      return result.success(std::shared_ptr<Node>(
          new SymbolDefinitionNode(is_const, type, name, Token(
              tokens->at(*index).pstart(), tokens->at(*index).pend(),
              TokenType::NULL_TOKEN),
              std::shared_ptr<Node>(
              new NoOperationNode()))));
    }

    if (tokens->at(*index).type() != TokenType::EQUALS) {
      return result.failure(SyntaxError(
        tokens->at(*index).pstart(), tokens->at(*index).pend(),
        "Expected '='"
      ));
    }

    const Token& op = tokens->at(*index);

    advance_(tokens, index);

    std::shared_ptr<Node> expr = result.use(expression_(tokens, index));
    if (result.errors.size()) return result;

    if (tokens->at(*index).type() != TokenType::SEMICOLON) {
      return result.failure(SyntaxError(
        tokens->at(*index).pstart(), tokens->at(*index).pend(),
        "Expected ';'"
      ));
    }

    advance_(tokens, index);

    return result.success(std::shared_ptr<Node>(
        new SymbolDefinitionNode(is_const, type, name, op, expr)));
  }

  if (is_const.type() != TokenType::NULL_TOKEN) {
    return result.failure(SyntaxError(
      is_const.pstart(), is_const.pend(),
      "Unexpeced keyword 'const'"
    ));
  }

  if (tokens->at(*index).type() == TokenType::KW_RETURN) {
    advance_(tokens, index);

    if (tokens->at(*index).type() != TokenType::SEMICOLON) {
      std::shared_ptr<Node> expr = result.use(expression_(tokens, index));
      if (result.errors.size()) return result;

      if (tokens->at(*index).type() != TokenType::SEMICOLON) {
        return result.failure(SyntaxError(
          tokens->at(*index).pstart(), tokens->at(*index).pend(),
          "Expected ';'"
        ));
      }

      advance_(tokens, index);

      return result.success(std::shared_ptr<Node>(
          new ReturnNode(expr)));
    }

    advance_(tokens, index);

    return result.success(std::shared_ptr<Node>(
        new ReturnNode(std::shared_ptr<Node>(new NoOperationNode()))));
  }

  if (tokens->at(*index).type() == TokenType::KW_IF) {
    std::shared_ptr<Node> cond = result.use(conditional_(tokens, index));
    if (result.errors.size()) return result;
    return result.success(cond);
  }

  if (tokens->at(*index).type() == TokenType::KW_FOR ||
      tokens->at(*index).type() == TokenType::KW_WHILE ||
      tokens->at(*index).type() == TokenType::KW_DO) {
    std::shared_ptr<Node> loop = result.use(loop_(tokens, index));
    if (result.errors.size()) return result;
    return result.success(loop);
  }

  std::shared_ptr<Node> expr = result.use(expression_(tokens, index));
  if (result.errors.size()) return result;

  if (tokens->at(*index).type() != TokenType::SEMICOLON) {
    advance_(tokens, index);
    return result.failure(SyntaxError(
      tokens->at((*index)-1).pstart(), tokens->at((*index)-1).pend(),
      "Expected ';'"
    ));
  }

  advance_(tokens, index);

  return result.success(expr);
}

ParserResult Parser::conditional_(
    const std::vector<Token>* tokens,
    unsigned int* index) const {
  ParserResult result;

  if (tokens->at(*index).type() != TokenType::KW_IF) {
    return result.failure(SyntaxError(
      tokens->at(*index).pstart(), tokens->at(*index).pend(),
      "Expected 'if'"
    ));
  }

  advance_(tokens, index);

  if (tokens->at(*index).type() != TokenType::LEFT_PARENTHESIS) {
    return result.failure(SyntaxError(
      tokens->at(*index).pstart(), tokens->at(*index).pend(),
      "Expected '(' after 'if' token"
    ));
  }

  advance_(tokens, index);

  std::shared_ptr<Node> cond = result.use(expression_(tokens, index));
  if (result.errors.size()) return result;

  if (tokens->at(*index).type() != TokenType::RIGHT_PARENTHESIS) {
    return result.failure(SyntaxError(
      tokens->at(*index).pstart(), tokens->at(*index).pend(),
      "Expected ')' after conditional expression"
    ));
  }

  advance_(tokens, index);

  if (tokens->at(*index).type() == TokenType::LEFT_BRACE) {
    advance_(tokens, index);

    std::shared_ptr<Node> body = result.use(codebody_(tokens, index));
    if (result.errors.size()) return result;

    if (tokens->at(*index).type() != TokenType::RIGHT_BRACE) {
      return result.failure(SyntaxError(
        tokens->at(*index).pstart(), tokens->at(*index).pend(),
        "Expected '}' after code body"
      ));
    }

    advance_(tokens, index);

    if (tokens->at(*index).type() == TokenType::KW_ELSE) {
      advance_(tokens, index);

      if (tokens->at(*index).type() == TokenType::LEFT_BRACE) {
        advance_(tokens, index);

        std::shared_ptr<Node> elsebody = result.use(codebody_(tokens, index));
        if (result.errors.size()) return result;

        if (tokens->at(*index).type() != TokenType::RIGHT_BRACE) {
          return result.failure(SyntaxError(
            tokens->at(*index).pstart(), tokens->at(*index).pend(),
            "Expected '}' after code body"
          ));
        }

        advance_(tokens, index);

        return result.success(std::shared_ptr<Node>(
            new ConditionalNode(cond, body, elsebody)));
      }

      std::shared_ptr<Node> elsebody = result.use(statement_(tokens, index));
      if (result.errors.size()) return result;

      return result.success(std::shared_ptr<Node>(
          new ConditionalNode(cond, body, elsebody)));
    }

    return result.success(std::shared_ptr<Node>(
        new ConditionalNode(cond, body, std::shared_ptr<Node>(
            new NoOperationNode()))));
  } else {
    std::shared_ptr<Node> body = result.use(statement_(tokens, index));
    if (result.errors.size()) return result;

    if (tokens->at(*index).type() == TokenType::KW_ELSE) {
      advance_(tokens, index);

      if (tokens->at(*index).type() == TokenType::LEFT_BRACE) {
        advance_(tokens, index);

        std::shared_ptr<Node> elsebody = result.use(codebody_(tokens, index));
        if (result.errors.size()) return result;

        if (tokens->at(*index).type() != TokenType::RIGHT_BRACE) {
          return result.failure(SyntaxError(
            tokens->at(*index).pstart(), tokens->at(*index).pend(),
            "Expected '}' after code body"
          ));
        }

        advance_(tokens, index);

        return result.success(std::shared_ptr<Node>(
            new ConditionalNode(cond, body, elsebody)));
      }

      std::shared_ptr<Node> elsebody = result.use(statement_(tokens, index));
      if (result.errors.size()) return result;

      return result.success(std::shared_ptr<Node>(
          new ConditionalNode(cond, body, elsebody)));
    }

    return result.success(std::shared_ptr<Node>(
        new ConditionalNode(cond, body, std::shared_ptr<Node>(
            new NoOperationNode()))));
  }
}

ParserResult Parser::loop_(
    const std::vector<Token>* tokens,
    unsigned int* index) const {
  ParserResult result;

  if (tokens->at(*index).type() == TokenType::KW_FOR) {
    advance_(tokens, index);

    if (tokens->at(*index).type() != TokenType::LEFT_PARENTHESIS) {
      return result.failure(SyntaxError(
        tokens->at(*index).pstart(), tokens->at(*index).pend(),
        "Expected '(' after 'for' keyword"
      ));
    }

    advance_(tokens, index);

    std::shared_ptr<Node> init_expr = result.use(statement_(tokens, index));
    if (result.errors.size()) return result;

    std::shared_ptr<Node> check_expr = result.use(expression_(tokens, index));
    if (result.errors.size()) return result;

    if (tokens->at(*index).type() != TokenType::SEMICOLON) {
      return result.failure(SyntaxError(
        tokens->at(*index).pstart(), tokens->at(*index).pend(),
        "Expected ';' after expression"
      ));
    }

    advance_(tokens, index);

    std::shared_ptr<Node> post_expr = result.use(expression_(tokens, index));
    if (result.errors.size()) return result;

    if (tokens->at(*index).type() != TokenType::RIGHT_PARENTHESIS) {
      return result.failure(SyntaxError(
        tokens->at(*index).pstart(), tokens->at(*index).pend(),
        "Expected ')' after expression"
      ));
    }

    advance_(tokens, index);

    if (tokens->at(*index).type() == TokenType::LEFT_BRACE) {
      advance_(tokens, index);

      std::shared_ptr<Node> body = result.use(codebody_(tokens, index));
      if (result.errors.size()) return result;

      if (tokens->at(*index).type() != TokenType::RIGHT_BRACE) {
        return result.failure(SyntaxError(
          tokens->at(*index).pstart(), tokens->at(*index).pend(),
          "Expected '}' after body"
        ));
      }

      advance_(tokens, index);

      return result.success(std::shared_ptr<Node>(
          new ForLoopNode(init_expr, check_expr, post_expr, body)));
    } else {
      std::shared_ptr<Node> body = result.use(statement_(tokens, index));
      if (result.errors.size()) return result;

      return result.success(std::shared_ptr<Node>(
          new ForLoopNode(init_expr, check_expr, post_expr, body)));
    }
  } else if (tokens->at(*index).type() == TokenType::KW_WHILE) {
    advance_(tokens, index);

    if (tokens->at(*index).type() != TokenType::LEFT_PARENTHESIS) {
      return result.failure(SyntaxError(
        tokens->at(*index).pstart(), tokens->at(*index).pend(),
        "Expected '(' after 'while' keyword"
      ));
    }

    advance_(tokens, index);

    std::shared_ptr<Node> check_expr = result.use(expression_(tokens, index));
    if (result.errors.size()) return result;

    if (tokens->at(*index).type() != TokenType::RIGHT_PARENTHESIS) {
      return result.failure(SyntaxError(
        tokens->at(*index).pstart(), tokens->at(*index).pend(),
        "Expected ')' after expression"
      ));
    }

    advance_(tokens, index);

    if (tokens->at(*index).type() == TokenType::LEFT_BRACE) {
      advance_(tokens, index);

      std::shared_ptr<Node> body = result.use(codebody_(tokens, index));
      if (result.errors.size()) return result;

      if (tokens->at(*index).type() != TokenType::RIGHT_BRACE) {
        return result.failure(SyntaxError(
          tokens->at(*index).pstart(), tokens->at(*index).pend(),
          "Expected '}' after body"
        ));
      }

      advance_(tokens, index);

      return result.success(std::shared_ptr<Node>(
          new WhileLoopNode(true, check_expr, body)));
    } else {
      std::shared_ptr<Node> body = result.use(statement_(tokens, index));
      if (result.errors.size()) return result;

      return result.success(std::shared_ptr<Node>(
          new WhileLoopNode(true, check_expr, body)));
    }
  } else if (tokens->at(*index).type() == TokenType::KW_DO) {
    advance_(tokens, index);

    if (tokens->at(*index).type() != TokenType::LEFT_BRACE) {
      return result.failure(SyntaxError(
        tokens->at(*index).pstart(), tokens->at(*index).pend(),
        "Expected '{' after 'do' keyword"
      ));
    }

    advance_(tokens, index);

    std::shared_ptr<Node> body = result.use(codebody_(tokens, index));
    if (result.errors.size()) return result;

    if (tokens->at(*index).type() != TokenType::RIGHT_BRACE) {
      return result.failure(SyntaxError(
        tokens->at(*index).pstart(), tokens->at(*index).pend(),
        "Expected '}' after body"
      ));
    }

    advance_(tokens, index);

    if (tokens->at(*index).type() != TokenType::KW_WHILE) {
      return result.failure(SyntaxError(
        tokens->at(*index).pstart(), tokens->at(*index).pend(),
        "Expected 'while' after '}'"
      ));
    }

    advance_(tokens, index);

    if (tokens->at(*index).type() != TokenType::LEFT_PARENTHESIS) {
      return result.failure(SyntaxError(
        tokens->at(*index).pstart(), tokens->at(*index).pend(),
        "Expected '(' after 'while' keyword"
      ));
    }

    advance_(tokens, index);

    std::shared_ptr<Node> check_expr = result.use(expression_(tokens, index));
    if (result.errors.size()) return result;

    if (tokens->at(*index).type() != TokenType::RIGHT_PARENTHESIS) {
      return result.failure(SyntaxError(
        tokens->at(*index).pstart(), tokens->at(*index).pend(),
        "Expected ')' after expression"
      ));
    }

    advance_(tokens, index);

    if (tokens->at(*index).type() != TokenType::SEMICOLON) {
      return result.failure(SyntaxError(
        tokens->at(*index).pstart(), tokens->at(*index).pend(),
        "Expected ';' after while atom"
      ));
    }

    advance_(tokens, index);

    return result.success(std::shared_ptr<Node>(
        new WhileLoopNode(false, check_expr, body)));
  } else {
    return result.failure(SyntaxError(
      tokens->at(*index).pstart(), tokens->at(*index).pend(),
      "Expected 'for', 'while', or 'do' keyword"
    ));
  }
}

ParserResult Parser::expression_(
    const std::vector<Token>* tokens,
    unsigned int* index) const {
  ParserResult result;

  std::shared_ptr<Node> left = result.use(condexpr_(tokens, index));
  if (result.errors.size()) return result;

  while (tokens->at(*index).type() == TokenType::DOUBLE_AMPERSAND ||
      tokens->at(*index).type() == TokenType::DOUBLE_PIPE ||
      tokens->at(*index).type() == TokenType::DOUBLE_CARET) {
    const Token& op = tokens->at(*index);
    advance_(tokens, index);

    std::shared_ptr<Node> right = result.use(condexpr_(tokens, index));
    if (result.errors.size()) return result;

    left = std::shared_ptr<Node>(new BinaryOperationNode(left, op, right));
  }

  return result.success(left);
}

ParserResult Parser::condexpr_(
    const std::vector<Token>* tokens,
    unsigned int* index) const {
  ParserResult result;

  std::shared_ptr<Node> left = result.use(bitexpr_(tokens, index));
  if (result.errors.size()) return result;

  while (tokens->at(*index).type() == TokenType::DOUBLE_EQUALS ||
      tokens->at(*index).type() == TokenType::BANG_EQUALS ||
      tokens->at(*index).type() == TokenType::LESS ||
      tokens->at(*index).type() == TokenType::GREATER ||
      tokens->at(*index).type() == TokenType::LESS_EQUALS ||
      tokens->at(*index).type() == TokenType::GREATER_EQUALS) {
    const Token& op = tokens->at(*index);
    advance_(tokens, index);

    std::shared_ptr<Node> right = result.use(bitexpr_(tokens, index));
    if (result.errors.size()) return result;

    left = std::shared_ptr<Node>(new BinaryOperationNode(left, op, right));
  }

  return result.success(left);
}

ParserResult Parser::bitexpr_(
    const std::vector<Token>* tokens,
    unsigned int* index) const {
  ParserResult result;

  std::shared_ptr<Node> left = result.use(bitshexpr_(tokens, index));
  if (result.errors.size()) return result;

  while (tokens->at(*index).type() == TokenType::AMPERSAND ||
      tokens->at(*index).type() == TokenType::PIPE ||
      tokens->at(*index).type() == TokenType::CARET) {
    const Token& op = tokens->at(*index);
    advance_(tokens, index);

    std::shared_ptr<Node> right = result.use(bitshexpr_(tokens, index));
    if (result.errors.size()) return result;

    left = std::shared_ptr<Node>(new BinaryOperationNode(left, op, right));
  }

  return result.success(left);
}

ParserResult Parser::bitshexpr_(
    const std::vector<Token>* tokens,
    unsigned int* index) const {
  ParserResult result;

  std::shared_ptr<Node> left = result.use(arithexpr_(tokens, index));
  if (result.errors.size()) return result;

  while (tokens->at(*index).type() == TokenType::DOUBLE_LESS ||
      tokens->at(*index).type() == TokenType::DOUBLE_GREATER) {
    const Token& op = tokens->at(*index);
    advance_(tokens, index);

    std::shared_ptr<Node> right = result.use(arithexpr_(tokens, index));
    if (result.errors.size()) return result;

    left = std::shared_ptr<Node>(new BinaryOperationNode(left, op, right));
  }

  return result.success(left);
}

ParserResult Parser::arithexpr_(
    const std::vector<Token>* tokens,
    unsigned int* index) const {
  ParserResult result;

  std::shared_ptr<Node> left = result.use(term_(tokens, index));
  if (result.errors.size()) return result;

  while (tokens->at(*index).type() == TokenType::PLUS ||  // Arithmetic: Add
      tokens->at(*index).type() == TokenType::MINUS) {    // Arithmetic: Sub
    const Token& op = tokens->at(*index);
    advance_(tokens, index);

    std::shared_ptr<Node> right = result.use(term_(tokens, index));
    if (result.errors.size()) return result;

    left = std::shared_ptr<Node>(new BinaryOperationNode(left, op, right));
  }

  return result.success(left);
}

ParserResult Parser::term_(
    const std::vector<Token>* tokens,
    unsigned int* index) const {
  ParserResult result;

  std::shared_ptr<Node> left = result.use(factor_(tokens, index));
  if (result.errors.size()) return result;

  while (tokens->at(*index).type() == TokenType::STAR ||  // Arithmetic: Mult
      tokens->at(*index).type() == TokenType::SLASH ||    // Arithmetic: Divide
      tokens->at(*index).type() == TokenType::PERCENT) {  // Arithmetic: Mod
    const Token& op = tokens->at(*index);
    advance_(tokens, index);

    std::shared_ptr<Node> right = result.use(factor_(tokens, index));
    if (result.errors.size()) return result;

    left = std::shared_ptr<Node>(new BinaryOperationNode(left, op, right));
  }


  return result.success(left);
}

ParserResult Parser::factor_(
    const std::vector<Token>* tokens,
    unsigned int* index) const {
  ParserResult result;

  if (tokens->at(*index).type() == TokenType::LEFT_PARENTHESIS) {
    advance_(tokens, index);

    std::shared_ptr<Node> expression = result.use(expression_(tokens, index));
    if (result.errors.size()) return result;

    if (tokens->at(*index).type() == TokenType::RIGHT_PARENTHESIS) {
      advance_(tokens, index);
      return result.success(expression);
    } else {
      result.failure(SyntaxError(
        tokens->at(*index).pstart(), tokens->at(*index).pend(),
        "Expected ')'"
      ));
    }
  }

  const TokenType next_type = tokens->at((*index) + 1).type();
  if (tokens->at(*index).type() == TokenType::IDENTIFIER && (
      next_type == TokenType::EQUALS ||
      next_type == TokenType::PLUS_EQUALS ||
      next_type == TokenType::MINUS_EQUALS ||
      next_type == TokenType::STAR_EQUALS ||
      next_type == TokenType::SLASH_EQUALS ||
      next_type == TokenType::PERCENT_EQUALS ||
      next_type == TokenType::AMPERSAND_EQUALS ||
      next_type == TokenType::PIPE_EQUALS ||
      next_type == TokenType::CARET_EQUALS ||
      next_type == TokenType::DOUBLE_LESS_EQUALS ||
      next_type == TokenType::DOUBLE_GREATER_EQUALS)) {
    const Token& name = tokens->at(*index);
    advance_(tokens, index);
    const Token& op = tokens->at(*index);
    advance_(tokens, index);

    std::shared_ptr<Node> expr = result.use(expression_(tokens, index));
    if (result.errors.size()) return result;

    const Token& nultok = Token(
        tokens->at(*index).pstart(), tokens->at(*index).pend(),
        TokenType::NULL_TOKEN);
    return result.success(std::shared_ptr<Node>(
        new SymbolDefinitionNode(nultok, nultok, name, op, expr)));
  }

  // Not a grouped expression, just check for literals
  TokenType type = tokens->at(*index).type();
  if (type == TokenType::INT32 ||
      type == TokenType::UINT32 ||
      type == TokenType::INT64 ||
      type == TokenType::UINT64 ||
      type == TokenType::FLOAT32 ||
      type == TokenType::FLOAT64 ||
      type == TokenType::BOOLEAN) {
    std::shared_ptr<Node> literal =
        std::shared_ptr<Node>(new LiteralNode(tokens->at(*index)));
    advance_(tokens, index);
    return result.success(literal);
  } else if (type == TokenType::IDENTIFIER) {
    const Token& name = tokens->at(*index);
    advance_(tokens, index);

    if (tokens->at(*index).type() == TokenType::LEFT_PARENTHESIS) {
      advance_(tokens, index);

      if (tokens->at(*index).type() == TokenType::RIGHT_PARENTHESIS) {
        advance_(tokens, index);
        return result.success(std::shared_ptr<Node>(
            new FunctionCallNode(name, {})));
      } else {
        std::vector<std::shared_ptr<Node>> args;

        args.push_back(result.use(expression_(tokens, index)));
        if (result.errors.size()) return result;

        while (tokens->at(*index).type() == TokenType::COMMA) {
          advance_(tokens, index);

          args.push_back(result.use(expression_(tokens, index)));
          if (result.errors.size()) return result;
        }

        if (tokens->at(*index).type() != TokenType::RIGHT_PARENTHESIS) {
          return result.failure(SyntaxError(
            tokens->at(*index).pstart(), tokens->at(*index).pend(),
            "Expected ')' before token"
          ));
        }

        advance_(tokens, index);

        return result.success(std::shared_ptr<Node>(
            new FunctionCallNode(name, args)));
      }
    } else {
      std::shared_ptr<Node> var =
          std::shared_ptr<Node>(new SymbolReferenceNode(name));
      return result.success(var);
    }
  } else if (type == TokenType::PLUS ||  // Arithmetic: Addition (prepended nop)
      type == TokenType::MINUS ||        // Arithmetic: Subtraction (invert)
      type == TokenType::TILDE ||        // Bitwise: Negation
      type == TokenType::BANG) {         // Logic: Inversion
    const Token& token = tokens->at(*index);
    advance_(tokens, index);

    std::shared_ptr<Node> factor = result.use(factor_(tokens, index));
    if (result.errors.size()) return result;

    std::shared_ptr<Node> unop = std::shared_ptr<Node>(
        new UnaryOperationNode(token, factor));

    return result.success(unop);
  } else {
    return result.failure(SyntaxError(
      tokens->at(*index).pstart(), tokens->at(*index).pend(),
      "Expected an integer or float"
    ));
  }
}

}  // namespace cookie

