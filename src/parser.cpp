#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <variant>
#include <sstream>
#include <exception>
#include <regex>
#include <sstream>

#include "tokenizer.hpp"
#include "parser.hpp"

Parser::ParsingResult Parser::isValidSequence(const std::vector<Token> &tokens)
{
    for(int i = 0; i < tokens.size();)
    {
        if(tokens[i].type == L_BRACE || tokens[i].type == L_PARENTHESES)
        {
            if(!isScopeClosed(tokens, i))
                return Parser::ParsingResult::unclosedScope(tokens[i].type, i);
        }

        // now check for invalid sequences
        // def, and frames must be followed by an identifier, then followed by a scope
        // the scope should be left brace for def, and left parentheses for frames
        if(tokens[i].type == DEF || tokens[i].type == FRAME)
        {
            if(tokens[i + 1].type != IDENTIFIER)
                return Parser::ParsingResult::invalidSequence(tokens[i].type, i, "Expected identifier after def or frame");
            if(tokens[i + 2].type != L_BRACE && tokens[i + 2].type != L_PARENTHESES)
                return Parser::ParsingResult::invalidSequence(tokens[i].type, i, "Expected scope after definition/frame identifier");
        }

        // continue parsing 
        
        return Parser::ParsingResult::ok();
    }
}

bool Parser::isScopeClosed(const std::vector<Token> &tokens, int openingScopeIndex)
{
    TokenType openType = tokens[openingScopeIndex].type;
    if (openType != L_BRACE && openType != L_PARENTHESES)
        throw std::invalid_argument("Invalid opening scope type");

    int scopeCount = 0;
    bool isParentheses = openType == L_PARENTHESES;

    TokenType openingScopeType = isParentheses ? L_PARENTHESES : L_BRACE;
    TokenType closingScopeType = isParentheses ? R_PARENTHESES : R_BRACE;

    for (int i = openingScopeIndex; i < tokens.size(); i++)
    {
        if (tokens[i].type == openingScopeIndex)
            scopeCount++;
        else if (tokens[i].type == closingScopeType)
            scopeCount--;

        if (scopeCount == 0)
            return true;
    }

    return false;
}