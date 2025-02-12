#pragma once

#include "mirage/utils/hash_utils.h"
#include "mirage/utils/json_utils.h"
#include "mirage/search/symbolic_graph/tensor_dim_constraint.h"
#include "z3++.h"
#include <memory>
#include <mutex>
#include <shared_mutex>
#include <unordered_map>
#include <unordered_set>

namespace mirage {
namespace search {

class AbstractExpr {
public:
  AbstractExpr() = default;
  virtual ~AbstractExpr() = default;

  virtual z3::expr to_z3(z3::context &c) const = 0;
  bool subexpr_to(AbstractExpr const &other, std::unordered_set<TensorDimConstraint> const &constraints = {}) const;
  bool operator==(AbstractExpr const &other) const;
  virtual std::shared_ptr<AbstractExpr> simplify() const = 0;
  virtual std::string to_string() const = 0;
};

class Var : public AbstractExpr {
public:
  Var(std::string const &name);
  z3::expr to_z3(z3::context &c) const override;
  std::string to_string() const override;
  std::shared_ptr<AbstractExpr> simplify() const override;
  std::string name;
};

std::shared_ptr<AbstractExpr> abstract_expr_make_var(std::string const &name);

class Add : public AbstractExpr {
public:
  Add(std::shared_ptr<AbstractExpr> lhs, std::shared_ptr<AbstractExpr> rhs);
  z3::expr to_z3(z3::context &c) const override;
  std::string to_string() const override;
  std::shared_ptr<AbstractExpr> simplify() const override;
  std::shared_ptr<AbstractExpr> lhs, rhs;
};

std::shared_ptr<AbstractExpr>
    abstract_expr_make_add(std::shared_ptr<AbstractExpr> lhs,
                           std::shared_ptr<AbstractExpr> rhs);

class Mul : public AbstractExpr {
public:
  Mul(std::shared_ptr<AbstractExpr> lhs, std::shared_ptr<AbstractExpr> rhs);
  z3::expr to_z3(z3::context &c) const override;
  std::string to_string() const override;
  std::shared_ptr<AbstractExpr> simplify() const override;
  std::shared_ptr<AbstractExpr> lhs, rhs;
};

std::shared_ptr<AbstractExpr>
    abstract_expr_make_mul(std::shared_ptr<AbstractExpr> lhs,
                           std::shared_ptr<AbstractExpr> rhs);

class Div : public AbstractExpr {
public:
  Div(std::shared_ptr<AbstractExpr> lhs, std::shared_ptr<AbstractExpr> rhs);
  z3::expr to_z3(z3::context &c) const override;
  std::string to_string() const override;
  std::shared_ptr<AbstractExpr> simplify() const override;
  std::shared_ptr<AbstractExpr> lhs, rhs;
};

std::shared_ptr<AbstractExpr>
    abstract_expr_make_div(std::shared_ptr<AbstractExpr> lhs,
                           std::shared_ptr<AbstractExpr> rhs);

class Exp : public AbstractExpr {
public:
  Exp(std::shared_ptr<AbstractExpr> exponent);
  z3::expr to_z3(z3::context &c) const override;
  std::string to_string() const override;
  std::shared_ptr<AbstractExpr> simplify() const override;
  std::shared_ptr<AbstractExpr> exponent;
};

std::shared_ptr<AbstractExpr>
    abstract_expr_make_exp(std::shared_ptr<AbstractExpr> exponent);

class Silu : public AbstractExpr {
public:
  Silu(std::shared_ptr<AbstractExpr> a);
  z3::expr to_z3(z3::context &c) const override;
  std::string to_string() const override;
  std::shared_ptr<AbstractExpr> simplify() const override;
  std::shared_ptr<AbstractExpr> a;
};

std::shared_ptr<AbstractExpr>
    abstract_expr_make_silu(std::shared_ptr<AbstractExpr> a);

// Note(@Mengdi): Replace it with Sqr and Sqrt once we have related algebraic
// transformation
class RMS : public AbstractExpr {
public:
  RMS(std::shared_ptr<TensorDimExpr> reduction_degree, std::shared_ptr<AbstractExpr> elems);
  z3::expr to_z3(z3::context &c) const override;
  std::string to_string() const override;
  std::shared_ptr<AbstractExpr> simplify() const override;
  std::shared_ptr<TensorDimExpr> reduction_degree;
  std::shared_ptr<AbstractExpr> elems;
};

std::shared_ptr<AbstractExpr>
    abstract_expr_make_rms(int reduction_degree, std::shared_ptr<AbstractExpr> elems);
std::shared_ptr<AbstractExpr>
    abstract_expr_make_rms(std::shared_ptr<TensorDimExpr> reduction_degree, std::shared_ptr<AbstractExpr> elems);
std::shared_ptr<AbstractExpr>
    abstract_expr_make_rms(SymbolicTensorDim const &reduction_dim, std::shared_ptr<AbstractExpr> elems);

class Red : public AbstractExpr {
public:
  Red(std::shared_ptr<TensorDimExpr> reduction_degree, std::shared_ptr<AbstractExpr> summand);
  z3::expr to_z3(z3::context &c) const override;
  std::string to_string() const override;
  std::shared_ptr<AbstractExpr> simplify() const override;
  std::shared_ptr<TensorDimExpr> reduction_degree;
  std::shared_ptr<AbstractExpr> summand;
};

std::shared_ptr<AbstractExpr>
    abstract_expr_make_red(int reduction_degree, std::shared_ptr<AbstractExpr> summand);

std::shared_ptr<AbstractExpr>
    abstract_expr_make_red(std::shared_ptr<TensorDimExpr> reduction_degree, std::shared_ptr<AbstractExpr> summand);

std::shared_ptr<AbstractExpr>
    abstract_expr_make_red(SymbolicTensorDim const &reduction_dim, std::shared_ptr<AbstractExpr> summand);

} // namespace search
} // namespace mirage