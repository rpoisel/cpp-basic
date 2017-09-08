#include "basic_commands.h"
#include "basic_interpreter.h"
#include "basic_lexer.h"

namespace Lang
{
namespace Basic
{

class PrintCommand: public Command
{
public:
  constexpr PrintCommand() :
      Command(PRINT_TYPE)
  {
  }
  RC execute(Interpreter* const interpreter) const;
};

RC PrintCommand::execute(Interpreter* const interpreter) const
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

class LetCommand: public Command
{
public:
  constexpr LetCommand() :
      Command(LET_TYPE)
  {
  }
  RC execute(Interpreter* const interpreter) const;
};

RC LetCommand::execute(Interpreter* const interpreter) const
    {
  interpreter->consume();
  if (!(interpreter->LA(1).getType() == VAR_TYPE))
  {
    return RC_ERROR;
  }
  char varName = *(interpreter->LA(1)).getText();
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
  RC rcSetVarValue = interpreter->setVarValue(varName, interpreter->expression(rc));
  return RC_SUCCEEDED(rc) ? (RC_SUCCEEDED(rcSetVarValue) ? RC_OK : rcSetVarValue) : rc;
}

class GotoCommand: public Command
{
public:
  constexpr GotoCommand() :
      Command(GOTO_TYPE)
  {
  }
  RC execute(Interpreter* const interpreter) const;
};

RC GotoCommand::execute(Interpreter* const interpreter) const
    {
  interpreter->consume();
  return RC_SUCCEEDED(interpreter->jump(interpreter->LA(1))) ? RC_CONTINUE : RC_ERROR;
}

class RemCommand: public Command
{
public:
  constexpr RemCommand() :
      Command(REM_TYPE)
  {
  }
  RC execute(Interpreter* const interpreter) const;
};

RC RemCommand::execute(Interpreter* const interpreter) const
    {
  while (!(interpreter->LA(1).getType() == NEWLINE_TYPE))
  {
    interpreter->consume();
  }
  return RC_OK;;
}

class WhileCommand: public Command
{
public:
  constexpr WhileCommand() :
      Command(WHILE_TYPE)
  {
  }
  RC execute(Interpreter* const interpreter) const;
};

RC WhileCommand::execute(Interpreter* const interpreter) const
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
    } while (RC_SUCCEEDED(rc) && !(interpreter->LA(1).getType() == WEND_TYPE));
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
  while (!(interpreter->LA(1).getType() == WEND_TYPE))
  {
    interpreter->consume();
  }
  interpreter->consume();
  return RC_OK;
}

class IfCommand: public Command
{
public:
  constexpr IfCommand() :
      Command(IF_TYPE)
  {
  }
  RC execute(Interpreter* const interpreter) const;
};

RC IfCommand::execute(Interpreter* const interpreter) const
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

  while (!(interpreter->LA(1).getType() == NEWLINE_TYPE))
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

const CommandRegistry commandRegistry;

constexpr static Command const* const basicCommands[] = {
    &whileCommand,
    &ifCommand,
    &remCommand,
    &gotoCommand,
    &letCommand,
    &printCommand,
};

RC CommandRegistry::handleStatement(Interpreter* const interpreter) const
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

}
}
