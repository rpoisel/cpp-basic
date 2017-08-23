#include "basic_commands.h"
#include "basic_interpreter.h"
#include "basic_lexer.h"

class BasicCommand
{
public:
    constexpr BasicCommand(TokenIdType const& tokenId) : tokenId(tokenId) {}
    virtual RC execute(BasicInterpreter* const interpreter) const = 0;
    constexpr TokenIdType const& getTokenId() const { return tokenId; }
private:
    TokenIdType const& tokenId;
};

class PrintCommand : public BasicCommand
{
public:
    constexpr PrintCommand() : BasicCommand(PRINT_TYPE) {}
    RC execute(BasicInterpreter* const interpreter) const;
};

RC PrintCommand::execute(BasicInterpreter* const interpreter) const
{
    interpreter->consume();
    RC rc;
    BasicVariant result = interpreter->expressionList(rc);
    if (RC_SUCCEEDED(rc))
    {
        interpreter->getFacilities().print(result);
        return RC_OK;
    }
    return RC_ERROR;
}

class LetCommand : public BasicCommand
{
public:
    constexpr LetCommand() : BasicCommand(LET_TYPE) {}
    RC execute(BasicInterpreter* const interpreter) const;
};

RC LetCommand::execute(BasicInterpreter* const interpreter) const
{
    interpreter->consume();
    if (!(interpreter->LA(1).getType() == VAR_TYPE))
    {
        return RC_ERROR;
    }
    char varName = *(interpreter->LA(1)).getText();
    if (BasicLexer::isUppercaseLetter(varName))
    {
        varName = (varName - 'A') + 'a';
    }
    interpreter->consume();
    if (!(interpreter->LA(1).getType() == EQUAL_TYPE))
    {
        return RC_ERROR;
    }
    interpreter->consume();
    if (!interpreter->isExpression(1))
    {
        return RC_ERROR;
    }
    RC rc;
    interpreter->setVarValue(static_cast<size_t>(varName), interpreter->expression(rc));
    return rc;
}

class GotoCommand : public BasicCommand
{
public:
    constexpr GotoCommand() : BasicCommand(GOTO_TYPE) {}
    RC execute(BasicInterpreter* const interpreter) const;
};

RC GotoCommand::execute(BasicInterpreter* const interpreter) const
{
    interpreter->consume();
    char const* pos = interpreter->searchLine(interpreter->LA(1));
    if (!pos)
    {
        return RC_ERROR;
    }
    interpreter->reset(pos);

    return RC_CONTINUE;
}

class RemCommand : public BasicCommand
{
public:
    constexpr RemCommand() : BasicCommand(REM_TYPE) {}
    RC execute(BasicInterpreter* const interpreter) const;
};

RC RemCommand::execute(BasicInterpreter* const interpreter) const
{
    while(!(interpreter->LA(1).getType() == NEWLINE_TYPE))
    {
        interpreter->consume();
    }
    return RC_OK;;
}

class WhileCommand : public BasicCommand
{
public:
    constexpr WhileCommand() : BasicCommand(WHILE_TYPE) {}
    RC execute(BasicInterpreter* const interpreter) const;
};

RC WhileCommand::execute(BasicInterpreter* const interpreter) const
{
    interpreter->consume();
    char const* conditionPosition = interpreter->LA(1).getText();
    RC rc;
    bool conditionResult = interpreter->condition(rc);

    if (RC_FAILED(rc))
    {
        return rc;
    }

    rc = interpreter->match(NEWLINE_TYPE);
    if (RC_FAILED(rc))
    {
        return rc;
    }

    while (conditionResult)
    {
        do
        {
            rc = interpreter->line();
            if (rc == RC_CONTINUE)
            {
                return RC_CONTINUE;
            }
        } while(RC_SUCCEEDED(rc) && !(interpreter->LA(1).getType() == WEND_TYPE));
        interpreter->reset(conditionPosition);
        conditionResult = interpreter->condition(rc);
        if (RC_FAILED(rc))
        {
            return rc;
        }
        rc = interpreter->match(NEWLINE_TYPE);
        if (RC_FAILED(rc))
        {
            return rc;
        }
    }
    while(!(interpreter->LA(1).getType() == WEND_TYPE))
    {
        interpreter->consume();
    }
    interpreter->consume();
    return RC_OK;
}

class IfCommand : public BasicCommand
{
public:
    constexpr IfCommand() : BasicCommand(IF_TYPE) {}
    RC execute(BasicInterpreter* const interpreter) const;
};

RC IfCommand::execute(BasicInterpreter* const interpreter) const
{
    interpreter->consume();
    RC rc;

    bool conditionResult = interpreter->condition(rc);

    if (RC_FAILED(rc))
    {
        return rc;
    }

    if (conditionResult)
    {
        if (!(interpreter->LA(1).getType() == THEN_TYPE))
        {
            rc = RC_ERROR;
            return false;
        }
        interpreter->consume();
        return interpreter->statement();
    }

    while(!(interpreter->LA(1).getType() == NEWLINE_TYPE))
    {
        interpreter->consume();
    }
    return RC_OK;
}

constexpr static const LetCommand letCommand;
constexpr static const PrintCommand printCommand;
constexpr static const GotoCommand gotoCommand;
constexpr static const RemCommand remCommand;
constexpr static const WhileCommand whileCommand;
constexpr static const IfCommand ifCommand;

constexpr const BasicCommandRegistry basicCommandRegistry;

constexpr static BasicCommand const* const basicCommands[] = {
    &whileCommand,
    &ifCommand,
    &remCommand,
    &gotoCommand,
    &letCommand,
    &printCommand,
};

RC BasicCommandRegistry::handleStatement(BasicInterpreter* const interpreter) const
{
    for (auto command : basicCommands)
    {
        if (command->getTokenId() == interpreter->LA(1).getType())
        {
            return command->execute(interpreter);
        }
    }
    return RC_ERROR;
}

