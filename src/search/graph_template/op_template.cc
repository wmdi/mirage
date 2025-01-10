#include "mirage/search/graph_template/symbolic_op.h"
#include "mirage/search/graph_template/op_args.h"

namespace mirage {
namespace search {

SymbolicKNOp::SymbolicKNOp(type::KNOperatorType op_type, std::shared_ptr<OpArgs> args) : op_type(op_type), args(args) {}

SymbolicKNOp::SymbolicKNOp(type::KNOperatorType op_type) : op_type(op_type), args(std::make_shared<EmptyOpArgs>()) {}

SymbolicTBOp::SymbolicTBOp(type::TBOperatorType op_type, std::shared_ptr<OpArgs> args) : op_type(op_type), args(args) {}

SymbolicTBOp::SymbolicTBOp(type::TBOperatorType op_type) : op_type(op_type), args(std::make_shared<EmptyOpArgs>()) {}

}
}
