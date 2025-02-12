#pragma once

#include "mirage/search/symbolic_graph/dim_var_assignments.h"
#include "mirage/utils/json_utils.h"
#include "z3++.h"

#include <memory>
#include <string>

namespace mirage {
namespace search {

class TensorDimExpr {
public:
  TensorDimExpr() = default;
  virtual ~TensorDimExpr() = default;

  virtual int get_value(DimVarAssignments const &assignments) const = 0;
  virtual z3::expr to_z3(z3::context &c, bool log_scaled = true) const = 0;
  virtual std::string to_string() const = 0;
  virtual bool is_var() const;
  virtual bool is_const() const;
  virtual bool is_add() const;
  virtual bool is_mul() const;
  virtual bool is_div() const;

  virtual size_t hash() const = 0;
  virtual operator json() const = 0;
  virtual bool same_expr_as(std::shared_ptr<TensorDimExpr>) const = 0;
};

class TensorDimVar : public TensorDimExpr {
public:
  TensorDimVar(tensor_dim_var_index_t index);
  tensor_dim_var_index_t index;

  int get_value(DimVarAssignments const &assignments) const override;
  z3::expr to_z3(z3::context &c, bool log_scaled) const override;
  std::string to_string() const override;
  bool is_var() const override;

  size_t hash() const override;
  operator json() const override;
  bool same_expr_as(std::shared_ptr<TensorDimExpr>) const override;
};

std::shared_ptr<TensorDimVar> dim_expr_make_var(tensor_dim_var_index_t index);

class TensorDimConst : public TensorDimExpr {
public:
  TensorDimConst(int value);
  int value;

  int get_value(DimVarAssignments const &assignments) const override;
  z3::expr to_z3(z3::context &c, bool log_scaled) const override;
  std::string to_string() const override;
  bool is_const() const override;

  size_t hash() const override;
  operator json() const override;
  bool same_expr_as(std::shared_ptr<TensorDimExpr>) const override;
};

std::shared_ptr<TensorDimConst> dim_expr_make_const(int value);

class TensorDimAdd : public TensorDimExpr {
public:
  TensorDimAdd(std::shared_ptr<TensorDimExpr> lhs,
               std::shared_ptr<TensorDimExpr> rhs);
  std::shared_ptr<TensorDimExpr> lhs, rhs;

  int get_value(DimVarAssignments const &assignments) const override;
  z3::expr to_z3(z3::context &c, bool log_scaled) const override;
  std::string to_string() const override;
  bool is_add() const override;

  size_t hash() const override;
  operator json() const override;
  bool same_expr_as(std::shared_ptr<TensorDimExpr>) const override;
};

std::shared_ptr<TensorDimAdd>
    dim_expr_make_add(std::shared_ptr<TensorDimExpr> lhs,
                      std::shared_ptr<TensorDimExpr> rhs);

class TensorDimMul : public TensorDimExpr {
public:
  TensorDimMul(std::shared_ptr<TensorDimExpr> lhs,
               std::shared_ptr<TensorDimExpr> rhs);
  std::shared_ptr<TensorDimExpr> lhs, rhs;

  int get_value(DimVarAssignments const &assignments) const override;
  z3::expr to_z3(z3::context &c, bool log_scaled) const override;
  std::string to_string() const override;
  bool is_mul() const override;

  size_t hash() const override;
  operator json() const override;
  bool same_expr_as(std::shared_ptr<TensorDimExpr>) const override;
};

std::shared_ptr<TensorDimMul>
    dim_expr_make_mul(std::shared_ptr<TensorDimExpr> lhs,
                      std::shared_ptr<TensorDimExpr> rhs);

class TensorDimDiv : public TensorDimExpr {
public:
  TensorDimDiv(std::shared_ptr<TensorDimExpr> lhs,
               std::shared_ptr<TensorDimExpr> rhs);
  std::shared_ptr<TensorDimExpr> lhs, rhs;

  int get_value(DimVarAssignments const &assignments) const override;
  z3::expr to_z3(z3::context &c, bool log_scaled) const override;
  std::string to_string() const override;
  bool is_div() const override;

  size_t hash() const override;
  operator json() const override;
  bool same_expr_as(std::shared_ptr<TensorDimExpr>) const override;
};

std::shared_ptr<TensorDimDiv>
    dim_expr_make_div(std::shared_ptr<TensorDimExpr> lhs,
                      std::shared_ptr<TensorDimExpr> rhs);

} // namespace search
} // namespace mirage
