#ifndef AST_H_
#define AST_H_

#include <string>
#include <vector>

#include "loc.h"
#include "string_piece.h"

using namespace std;

class Evaluator;
struct Value;

enum struct AssignOp {
  EQ,
  COLON_EQ,
  PLUS_EQ,
  QUESTION_EQ,
};

enum struct AssignDirective {
  NONE,
  OVERRIDE,
  EXPORT,
};

enum struct CondOp {
  IFEQ,
  IFNEQ,
  IFDEF,
  IFNDEF,
};

struct AST {
 public:
  virtual ~AST();

  Loc loc() const { return loc_; }
  void set_loc(Loc loc) { loc_ = loc; }
  StringPiece orig() const { return orig_; }

  virtual void Eval(Evaluator* ev) const = 0;

  virtual string DebugString() const = 0;

 protected:
  AST();

 private:
  Loc loc_;
  StringPiece orig_;
};

struct RuleAST : public AST {
  Value* expr;
  char term;
  Value* after_term;

  virtual ~RuleAST();

  virtual void Eval(Evaluator* ev) const;

  virtual string DebugString() const;
};

struct AssignAST : public AST {
  Value* lhs;
  Value* rhs;
  AssignOp op;
  AssignDirective directive;

  virtual ~AssignAST();

  virtual void Eval(Evaluator* ev) const;

  virtual string DebugString() const;
};

struct CommandAST : public AST {
  Value* expr;

  virtual ~CommandAST();

  virtual void Eval(Evaluator* ev) const;

  virtual string DebugString() const;
};

struct IfAST : public AST {
  CondOp op;
  Value* lhs;
  Value* rhs;
  vector<AST*> true_stmts;
  vector<AST*> false_stmts;

  virtual ~IfAST();

  virtual void Eval(Evaluator* ev) const;

  virtual string DebugString() const;
};

struct IncludeAST : public AST {
  Value* expr;
  bool should_exist;

  virtual ~IncludeAST();

  virtual void Eval(Evaluator* ev) const;

  virtual string DebugString() const;
};

struct ExportAST : public AST {
  Value* expr;
  bool is_export;

  virtual ~ExportAST();

  virtual void Eval(Evaluator* ev) const;

  virtual string DebugString() const;
};

#endif  // AST_H_