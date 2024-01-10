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
    Parser::ParserScope scope = Parser::ParserScope::GLOBAL_SCOPE;

    for (int i = 0; i < tokens.size();)
    {
        // scope checking
        if (tokens[i].type == L_BRACE || tokens[i].type == L_PARENTHESES)
        {
            if (!isScopeClosed(tokens, i))
                return Parser::ParsingResult::unclosedScope(tokens[i].type, i);

            i++; // continue to inside of scope
            continue;
        }

        // now check for invalid sequences

        // CHECK FOR DECLARATIONS
        // def, and frames must be followed by an identifier, then followed by a scope
        // the scope should be left brace for def, and left parentheses for frames
        if (tokens[i].type == DEF)
        {
            if (tokens[i + 1].type != IDENTIFIER)
                return Parser::ParsingResult::invalidSequence(tokens[i].type, i, "Expected identifier after def");
            if (tokens[i + 2].type != L_BRACE)
                return Parser::ParsingResult::invalidSequence(tokens[i].type, i, "Expected scope after definition identifier");
        }

        // now check that the next scope is opened with the proper type
        if (tokens[i].type == DEF && tokens[i + 2].type != L_BRACE)
            return Parser::ParsingResult::invalidSequence(tokens[i].type, i, "Expected left brace after def");
        if (tokens[i].type == FRAME && tokens[i + 1].type != L_PARENTHESES)
            return Parser::ParsingResult::invalidSequence(tokens[i].type, i, "Expected left parentheses after frame");
        if (tokens[i].type == META && tokens[i + 1].type != L_BRACE)
            return Parser::ParsingResult::invalidSequence(tokens[i].type, i, "Expected left brace after meta");
        
        // now progress the index based on the scope type
        if (tokens[i].type == DEF)
        {
            std::cout << "Found valid def token, changing scope" << std::endl;
            scope = Parser::ParserScope::DATA_TYPE_SCOPE;
            i += 2;
            continue;
        }
        if (tokens[i].type == FRAME)
        {
            std::cout << "Found valid frame token, changing scope" << std::endl;
            scope = Parser::ParserScope::FRAME_SCOPE;
            i += 1;
            continue;
        }
        if (tokens[i].type == META)
        {
            std::cout << "Found valid meta token, changing scope" << std::endl;
            scope = Parser::ParserScope::META_SCOPE;
            i += 1;
            continue;
        }

        std::cout << "Evaluating within scope: " << scope << std::endl;
        
        // CHECK FOR SCOPES
        switch (scope)
        {
        case Parser::ParserScope::GLOBAL_SCOPE:
            // we should not be in the global scope at this point of the code
            // only def, frame, and meta are allowed in the global scope
            return Parser::ParsingResult::invalidSequence(tokens[i].type, i, "Expected def, frame, or meta");
        case Parser::ParserScope::DATA_TYPE_SCOPE:
            // we should only be in the data type scope if we are in a def
            // the only valid tokens in this scope are identifiers, and data types
            if (tokens[i].type == R_BRACE)
            {
                scope = Parser::ParserScope::GLOBAL_SCOPE;
                i++;
                continue;
            }
            if (tokens[i].type != IDENTIFIER)
                return Parser::ParsingResult::invalidSequence(tokens[i].type, i, "Expected identifier type");
            if (tokens[i+1].type != IDENTIFIER)
                return Parser::ParsingResult::invalidSequence(tokens[i+1].type, i+1, "Expected identifier type");
            if (tokens[i+2].type != SEMICOLON)
                return Parser::ParsingResult::invalidSequence(tokens[i+2].type, i+2, "Expected semicolon");
            i += 3;
            continue;
        case Parser::ParserScope::META_SCOPE:
            // we should only be in the meta scope if we are in a meta
            // the only valid tokens in this scope are identifiers, and data types
            if (tokens[i].type == R_BRACE)
            {
                scope = Parser::ParserScope::GLOBAL_SCOPE;
                i++;
                continue;
            }
            if (tokens[i].type != IDENTIFIER)
                return Parser::ParsingResult::invalidSequence(tokens[i].type, i, "Expected identifier type");
            if (tokens[i+1].type != COLON)
                return Parser::ParsingResult::invalidSequence(tokens[i+1].type, i+1, "Expected colon");
            if (tokens[i+2].type < INT_LITERAL || tokens[i+2].type > VERSION_LITERAL)
                return Parser::ParsingResult::invalidSequence(tokens[i+2].type, i+2, "Expected a literal");
            if (tokens[i+3].type != SEMICOLON)
                return Parser::ParsingResult::invalidSequence(tokens[i+3].type, i+3, "Expected semicolon");
            i += 4;
            continue;
        case Parser::ParserScope::FRAME_SCOPE:
            if (tokens[i].type != IDENTIFIER)
                return Parser::ParsingResult::invalidSequence(tokens[i].type, i, "Expected identifier type");
            if (tokens[i+1].type != R_PARENTHESES)
                return Parser::ParsingResult::invalidSequence(tokens[i+1].type, i+1, "Expected right parentheses");
            i += 2;
            scope = Parser::ParserScope::POST_FRAME_SCOPE;
            continue;
        case Parser::ParserScope::POST_FRAME_SCOPE:
            if (tokens[i].type != END_OF_FILE)
                return Parser::ParsingResult::invalidSequence(tokens[i].type, i, "Expected end of file");
        default:
            return Parser::ParsingResult::invalidSequence(tokens[i].type, i, "Unknown scope");
        }
    }

    
    return Parser::ParsingResult::ok();
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