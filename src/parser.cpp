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
#include <queue>
#include <climits>

#include "tokenizer.hpp"
#include "parser.hpp"

using namespace daqser::impl;

Parser::ParsingResult Parser::isValidSequence(const std::vector<Token> &tokens)
{
    Parser::ParserScope scope = Parser::ParserScope::GLOBAL_SCOPE;

    // check for multiple meta tokens -- only one is allowed
    int metaCount = 0;
    for (int i = 0; i < tokens.size(); i++)
    {
        Token token = tokens[i];
        if (token.type == META)
            metaCount++;

        if (metaCount > 1)
            return Parser::ParsingResult::duplicateDefinition(META, i);
    }

    if (metaCount == 0)
        return Parser::ParsingResult::missingMeta();

    // check for multiple frame tokens -- only one is allowed
    int frameCount = 0;
    for (int i = 0; i < tokens.size(); i++)
    {
        Token token = tokens[i];
        if (token.type == FRAME)
            frameCount++;

        if (frameCount > 1)
            return Parser::ParsingResult::duplicateDefinition(FRAME, i);
    }

    if (frameCount == 0)
        return Parser::ParsingResult::missingFrame();

    for (int i = 0; i < tokens.size();)
    {
        // scope checking
        if (tokens[i].type == L_BRACE || tokens[i].type == L_PARENTHESES)
        {
            if (!_isScopeClosed(tokens, i))
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
            // std::cout << "Found valid def token, changing scope" << std::endl;
            scope = Parser::ParserScope::DATA_TYPE_SCOPE;
            i += 2;
            continue;
        }
        if (tokens[i].type == FRAME)
        {
            // std::cout << "Found valid frame token, changing scope" << std::endl;
            scope = Parser::ParserScope::FRAME_SCOPE;
            i += 1;
            continue;
        }
        if (tokens[i].type == META)
        {
            // std::cout << "Found valid meta token, changing scope" << std::endl;
            scope = Parser::ParserScope::META_SCOPE;
            i += 1;
            continue;
        }

        // std::cout << "Evaluating within scope: " << scope << std::endl;

        // CHECK FOR SCOPES
        switch (scope)
        {
        case Parser::ParserScope::GLOBAL_SCOPE:
            // we should not be in the global scope at this point of the code
            // only def, frame, and meta are allowed in the global scope
            if (tokens[i].type == END_OF_FILE)
                // we have reached the end of the file, so we are done -- but we haven't found a frame
                return Parser::ParsingResult::ok("No frame found in file, but file is valid");
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
            if (tokens[i + 1].type != IDENTIFIER)
                return Parser::ParsingResult::invalidSequence(tokens[i + 1].type, i + 1, "Expected identifier type");
            if (tokens[i + 2].type != SEMICOLON)
                return Parser::ParsingResult::invalidSequence(tokens[i + 2].type, i + 2, "Expected semicolon");
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
            if (tokens[i + 1].type != COLON)
                return Parser::ParsingResult::invalidSequence(tokens[i + 1].type, i + 1, "Expected colon");
            if (tokens[i + 2].type < INT_LITERAL || tokens[i + 2].type > VERSION_LITERAL)
                return Parser::ParsingResult::invalidSequence(tokens[i + 2].type, i + 2, "Expected a literal");
            if (tokens[i + 3].type != SEMICOLON)
                return Parser::ParsingResult::invalidSequence(tokens[i + 3].type, i + 3, "Expected semicolon");
            i += 4;
            continue;
        case Parser::ParserScope::FRAME_SCOPE:
            if (tokens[i].type != IDENTIFIER)
                return Parser::ParsingResult::invalidSequence(tokens[i].type, i, "Expected identifier type");
            if (tokens[i + 1].type != R_PARENTHESES)
                return Parser::ParsingResult::invalidSequence(tokens[i + 1].type, i + 1, "Expected right parentheses");
            i += 2;
            scope = Parser::ParserScope::POST_FRAME_SCOPE;
            continue;
        case Parser::ParserScope::POST_FRAME_SCOPE:
            if (tokens[i].type != SEMICOLON)
                return Parser::ParsingResult::invalidSequence(tokens[i].type, i, "Expected semicolon");
            if (tokens[i + 1].type != END_OF_FILE)
                return Parser::ParsingResult::invalidSequence(tokens[i + 1].type, i + 1, "Expected end of file");
            i += 2;
            continue;
        default:
            std::stringstream ss;
            ss << "Unknown scope: " << scope;
            return Parser::ParsingResult::invalidSequence(tokens[i].type, i, ss.str());
        }
    }

    return Parser::ParsingResult::ok();
}

bool Parser::_isScopeClosed(const std::vector<Token> &tokens, int openingScopeIndex) const
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

Parser::ParsingResult Parser::buildSchema(const std::vector<Token> &tokens, Schema &out, bool onlyMeta)
{
    // first check if the sequence is valid
    Parser::ParsingResult result = isValidSequence(tokens);
    if (!result.isValid)
        return result;

    // now we can build the schema
    Schema schema;
    Parser::ParserScope scope = Parser::ParserScope::GLOBAL_SCOPE;

    // copy the tokens to a queue
    std::queue<Token> tokenQueue;
    for (auto token : tokens)
        tokenQueue.push(token);

    std::map<std::string, DataType> dataTypes;                                             // holds the data types that have been defined
    std::map<std::string, std::vector<std::tuple<std::string, std::string>>> dependencies; // holds the dependencies for each data type, maps from data type to a vector of dependencies

    while (!tokenQueue.empty())
    {
        // fetch the current scope
        Token currentToken = tokenQueue.front();
        tokenQueue.pop();

        std::cout << "Evaluting token in global scope: " << Tokenizer::tokenTypeToString(currentToken.type) << std::endl;

        // scope checking
        switch (currentToken.type)
        {
        case META:
            scope = Parser::ParserScope::META_SCOPE;
            break;
        case DEF:
            scope = Parser::ParserScope::DATA_TYPE_SCOPE;
            break;
        case FRAME:
            scope = Parser::ParserScope::FRAME_SCOPE;
            break;
        case END_OF_FILE:
            continue;
        default:
            // this should have been caught by the isValidSequence function
            return Parser::ParsingResult::invalidToken(currentToken.type, 0);
        }

        // now we want to interpret the tokens based on the scope
        switch (scope)
        {
        case Parser::ParserScope::META_SCOPE:
        {
            // we need to read the meta data
            // we can assume that the next token is an identifier
            // either ".schema" or ".version"

            // eat the left brace
            tokenQueue.pop();

            // now build identifier-value pairs
            std::map<std::string, Token> pairs;

            std::cout << "Reading meta data" << std::endl;

            while (tokenQueue.front().type != R_BRACE)
            {
                // we expect an identifier : literal pair
                // this should be validated by the isValidSequence function
                Token identifier = tokenQueue.front();
                tokenQueue.pop();
                std::string identifierStr = identifier.value;

                tokenQueue.pop(); // eat the colon

                Token value = tokenQueue.front();
                tokenQueue.pop();

                std::cout << "Meta eval: " << identifierStr << " : " << value.value << std::endl;

                // now we can add the pair to the map
                // first check if the identifier is not already in the map
                if (pairs.find(identifierStr) != pairs.end())
                    return Parser::ParsingResult::invalidSequence(identifier.type, 0, "Duplicate identifier in meta data");

                pairs[identifierStr] = value;

                // eat the semicolon
                tokenQueue.pop();
            }

            // eat the right brace
            tokenQueue.pop();

            // now validate the pairs
            ParsingResult metaPairValidation = this->_validateMetaFields(pairs);

            if (!metaPairValidation.isValid)
                return metaPairValidation;

            // now we can add the meta data to the schema
            schema.schemaName = pairs.at(".schema").value;
            schema.versionNumber = this->_parseVersion(pairs.at(".version").value);

            if (onlyMeta)
            {
                out = schema;
                return Parser::ParsingResult::ok();
            }

            break;
        }
        case Parser::ParserScope::DATA_TYPE_SCOPE:
        {
            // we need to read the data type
            // eat the left brace
            Token definition = tokenQueue.front();
            tokenQueue.pop();
            std::string definitionStr = definition.value;
            std::cout << "Reading data type: " << definitionStr << std::endl;

            // check if the data type has already been defined
            if (dataTypes.find(definitionStr) != dataTypes.end())
                return Parser::ParsingResult::duplicateTypeDefinition(definitionStr);

            DataType dataType(definitionStr);

            // eat the left brace
            tokenQueue.pop();

            while (tokenQueue.front().type != R_BRACE)
            {
                if (onlyMeta)
                {
                    // just eat the tokens
                    tokenQueue.pop();
                    continue;
                }

                // our token sequence should be IDENTIFIER IDENTIFIER SEMICOLON
                Token typeName = tokenQueue.front();
                tokenQueue.pop();
                std::string typeNameStr = typeName.value;

                Token name = tokenQueue.front();
                tokenQueue.pop();
                std::string nameStr = name.value;

                std::cout << "Data type eval: " << typeNameStr << " " << nameStr << std::endl;

                // check if this is a primitive type
                if (this->_isPrimative(typeNameStr))
                {
                    // add the primitive type to the data type
                    std::cout << "Adding primative field to data type " << definitionStr << " : " << nameStr << std::endl;
                    Field field = this->_createPrimativeField(typeNameStr, nameStr);
                    dataType.addField(field);
                }
                else
                {
                    // this is a custom data type
                    // we will skip it for now, and add it to the dependencies later
                    std::cout << "Adding custom field to data type " << definitionStr << " : " << nameStr << std::endl;
                    if (dependencies.find(definitionStr) == dependencies.end())
                        dependencies[definitionStr] = std::vector<std::tuple<std::string, std::string>>{std::make_tuple(typeNameStr, nameStr)};
                    else
                        dependencies[definitionStr].push_back(std::make_tuple(typeNameStr, nameStr));
                }

                // eat the semicolon
                tokenQueue.pop();
            }

            // add this to the data types
            dataTypes[definitionStr] = dataType;

            // eat the right brace
            tokenQueue.pop();
            break;
        }
        case Parser::ParserScope::FRAME_SCOPE:
        {
            if (onlyMeta)
            {
                // just eat the tokens
                tokenQueue.pop();
                continue;
            }

            // we need to read the frame
            // eat the left parentheses
            tokenQueue.pop();

            // now we can assume that the next token is an identifier
            Token frameName = tokenQueue.front();
            tokenQueue.pop();
            std::string frameNameStr = frameName.value;
            std::cout << "Reading frame: " << frameNameStr << std::endl;

            // lets see if the type has been defined
            if (dataTypes.find(frameNameStr) == dataTypes.end())
                return Parser::ParsingResult::undefinedType(frameNameStr);

            // we need to determine the order to resolve dependencies
            // we should resolve the dependencies in the order from those with the least dependencies to those with the most (after resolving the least)
            // we can do this by sorting the dependencies by the number of dependencies
            std::map<std::string, std::vector<std::tuple<std::string, std::string>>> depCopy = dependencies;
            std::vector<std::string> orderedDependencies;

            // add in all the types that have no dependencies into the depCopy
            for (auto &dataType : dataTypes)
            {
                std::cout << "Adding data type to depCopy: " << dataType.first << std::endl;
                if (depCopy.find(dataType.first) == depCopy.end())
                    depCopy[dataType.first] = std::vector<std::tuple<std::string, std::string>>();
            }

            // make sure that each dependency does not directly depend on itself, if so, throw a parser error
            for (auto &dep : depCopy)
            {
                for (auto &dependency : dep.second)
                {
                    if (dep.first == std::get<0>(dependency))
                    {
                        std::vector<std::string> depNames;
                        for (auto &dep : depCopy)
                            depNames.push_back(dep.first);
                        return Parser::ParsingResult::cyclicDependency(depNames);
                    }
                }
            }

            while (!depCopy.empty())
            {
                std::string leastDependent;
                int leastDependentCount = INT_MAX;
                for (auto &dep : depCopy)
                {
                    if (dep.second.size() < leastDependentCount)
                    {
                        leastDependent = dep.first;
                        leastDependentCount = dep.second.size();
                    }
                }
                std::cout << "Least dependent: " << leastDependent << std::endl;
                // std::cout << "Least dependent count: " << leastDependentCount << std::endl;

                if (leastDependentCount != 0)
                {
                    std::vector<std::string> depNames;
                    for (auto &dep : depCopy)
                        depNames.push_back(dep.first);
                    return Parser::ParsingResult::cyclicDependency(depNames);
                }

                // now remove the least dependent from every dependency list
                for (auto &dep : depCopy)
                {
                    // std::cout << "Attempting to remove " << leastDependent << " from " << dep.first << std::endl;
                    // std::cout << "Dependency list size: " << dep.second.size() << std::endl;
                    std::vector<std::tuple<std::string, std::string>> &dependencyList = dep.second;

                    if (dependencyList.empty())
                        continue;

                    if (dep.first == leastDependent) // these cyclic dependencies have already detected
                        continue;

                    std::cout << "Removing " << leastDependent << " from " << dep.first << std::endl;

                    dependencyList.erase(std::remove_if(dependencyList.begin(), dependencyList.end(), [leastDependent](std::tuple<std::string, std::string> &dep)
                                                        { return std::get<0>(dep) == leastDependent; }),
                                         dependencyList.end());

                    depCopy[dep.first] = dependencyList;
                }

                std::cout << "Adding " << leastDependent << " to ordered dependencies" << std::endl;

                orderedDependencies.push_back(leastDependent);
                if (depCopy.find(leastDependent) != depCopy.end())
                    depCopy.erase(leastDependent);
            }

            std::cout << "Ordered dependencies! " << std::endl;

            for (auto &dep : orderedDependencies)
                std::cout << dep << std::endl;

            // now we can resolve the dependencies in the correct order
            for (std::string dependentType : orderedDependencies)
            {
                // skip it if it has no dependencies
                if (dependencies.find(dependentType) == dependencies.end())
                    continue;

                std::cout << "Resolving dependencies for " << dependentType << std::endl;
                std::vector<std::tuple<std::string, std::string>> dependencyList = dependencies.at(dependentType);
                DataType dependentDataType = dataTypes[dependentType];

                // lets try to resolve the dependencies
                for (auto &dependency : dependencyList)
                {
                    std::string dependencyType = std::get<0>(dependency);
                    std::string dependencyName = std::get<1>(dependency);

                    DataType dependencyDataType = dataTypes.at(dependencyType);
                    std::cout << "Resolving dependency for " << dependentType << ": " << dependencyType << " " << dependencyName << std::endl;
                    dependentDataType.addCustomField(dependencyName, dependencyDataType);

                    // std::cout << dependentDataType.toString() << std::endl;
                }

                dataTypes[dependentType] = dependentDataType;
            }

            // now we can build the frame using the data type
            schema.frameTemplate = std::make_shared<FrameTemplate>(dataTypes.at(frameNameStr));

            // eat the right parentheses
            tokenQueue.pop();

            // eat the semicolon
            tokenQueue.pop();
            break;
        }
        }
    }

    out = schema;
    return Parser::ParsingResult::ok();
}

int Parser::_levensteinDistance(const std::string &word1, const std::string &word2) const
{
    int size1 = word1.size();
    int size2 = word2.size();
    int verif[size1 + 1][size2 + 1]; // Verification matrix i.e. 2D array which will store the calculated distance.

    // If one of the words has zero length, the distance is equal to the size of the other word.
    if (size1 == 0)
        return size2;
    if (size2 == 0)
        return size1;

    // Sets the first row and the first column of the verification matrix with the numerical order from 0 to the length of each word.
    for (int i = 0; i <= size1; i++)
        verif[i][0] = i;
    for (int j = 0; j <= size2; j++)
        verif[0][j] = j;

    // Verification step / matrix filling.
    for (int i = 1; i <= size1; i++)
    {
        for (int j = 1; j <= size2; j++)
        {
            // Sets the modification cost.
            // 0 means no modification (i.e. equal letters) and 1 means that a modification is needed (i.e. unequal letters).
            int cost = (word2[j - 1] == word1[i - 1]) ? 0 : 1;

            // Sets the current position of the matrix as the minimum value between a (deletion), b (insertion) and c (substitution).
            // a = the upper adjacent value plus 1: verif[i - 1][j] + 1
            // b = the left adjacent value plus 1: verif[i][j - 1] + 1
            // c = the upper left adjacent value plus the modification cost: verif[i - 1][j - 1] + cost
            verif[i][j] = std::min(
                std::min(verif[i - 1][j] + 1, verif[i][j - 1] + 1),
                verif[i - 1][j - 1] + cost);
        }
    }

    // The last position of the matrix will contain the Levenshtein distance.
    return verif[size1][size2];
}

Parser::ParsingResult Parser::_validateMetaFields(std::map<std::string, Token> &metaFields) const
{
    std::vector<std::string> missingFields;
    for (auto const &field : this->_EXPECTED_META_FIELDS)
    {
        if (metaFields.find(field.first) == metaFields.end())
            missingFields.push_back(field.first);
    }

    for (auto const &field : metaFields)
    {
        if (this->_EXPECTED_META_FIELDS.find(field.first) == this->_EXPECTED_META_FIELDS.end())
        {
            // check for a close match
            std::string closestMatch;
            int closestDistance = INT_MAX;
            for (auto const &expectedField : this->_EXPECTED_META_FIELDS)
            {
                int distance = _levensteinDistance(field.first, expectedField.first);
                if (distance < closestDistance)
                {
                    closestMatch = expectedField.first;
                    closestDistance = distance;
                }
            }

            std::stringstream ss;
            ss << "Invalid meta field: " << field.first << ". Did you mean " << closestMatch << "?";
            return Parser::ParsingResult::invalidSequence(field.second.type, 0, ss.str());
        }

        if (metaFields[field.first].type != this->_EXPECTED_META_FIELDS.at(field.first))
        {
            std::stringstream ss;
            ss << "Invalid type for meta field: " << Tokenizer::tokenTypeToString(field.second.type)
               << ". Expected " << Tokenizer::tokenTypeToString(this->_EXPECTED_META_FIELDS.at(field.first));
            return Parser::ParsingResult::invalidDataType(field.second.type, 0, ss.str());
        }

        // now mark the field as found
        missingFields.erase(std::remove(missingFields.begin(), missingFields.end(), field.first), missingFields.end());
    }

    if (!missingFields.empty())
    {
        return Parser::ParsingResult::missingMetaInformation(missingFields);
    }

    return Parser::ParsingResult::ok();
}

int *Parser::_parseVersion(const std::string &versionString) const
{
    std::regex versionRegex("([0-9]+)\\.([0-9]+)\\.([0-9]+)");
    std::smatch match;
    if (!std::regex_match(versionString, match, versionRegex))
        return nullptr;

    int *version = new int[3];
    version[0] = std::stoi(match[1]);
    version[1] = std::stoi(match[2]);
    version[2] = std::stoi(match[3]);

    return version;
}