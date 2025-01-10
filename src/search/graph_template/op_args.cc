#include "mirage/search/graph_template/op_args.h"

namespace mirage {
namespace search {

KNInputOpArgs::KNInputOpArgs(std::vector<size_t> input_strides, int3 input_map)
    : input_strides(input_strides), input_map(input_map) {}

KNOutputOpArgs::KNOutputOpArgs(std::vector<size_t> output_strides,
                                 int3 output_map)
    : output_strides(output_strides), output_map(output_map) {}

KNReductionOpArgs::KNReductionOpArgs(int reduction_dim_idx,
                                         int reduction_dim_size)
    : reduction_dim_idx(reduction_dim_idx),
      reduction_dim_size(reduction_dim_size) {}

KNRMSNormOpArgs::KNRMSNormOpArgs(int normalized_size) : normalized_size(normalized_size) {}

KNCustomizedOpArgs::KNCustomizedOpArgs(SymbolicTBGraph tb_graph_template)
    : tb_graph_template(tb_graph_template) {}

TBInputOpArgs::TBInputOpArgs(SymbolicDTensor dtensor, int3 input_map, int forloop_dim)
    : dtensor(dtensor), input_map(input_map), forloop_dim(forloop_dim) {}

TBOutputOpArgs::TBOutputOpArgs(SymbolicDTensor dtensor, int3 output_map, int forloop_dim, mirage::type::TBEpilogueType epilogue)
    : dtensor(dtensor), output_map(output_map), forloop_dim(forloop_dim), epilogue(epilogue) {}

TBConcatOpArgs::TBConcatOpArgs(int concat_dim) : concat_dim(concat_dim) {}

TBElementUnaryOpArgs::TBElementUnaryOpArgs(mirage::type::TBOperatorType op_type, float scalar)
    : op_type(op_type), scalar(scalar) {}

TBElementBinaryOpArgs::TBElementBinaryOpArgs(
    mirage::type::TBOperatorType op_type)
    : op_type(op_type) {}

TBReductionOpArgs::TBReductionOpArgs(int reduce_dim, int reduce_size)
    : reduce_dim(reduce_dim),
      reduce_size(reduce_size) {}

}  // namespace search
}  // namespace mirage